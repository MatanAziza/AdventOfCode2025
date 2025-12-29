
// Compile: gcc -O2 -Wall -Wextra -o find_rect find_rect.c
// Usage: ./find_rect input_file
// input_file: each line "X,Y\n" (integers, can be negative).

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include "../GNL/get_next_line_________________________.h"

#define NPOINTS 496

typedef long long ll;

typedef struct {
    ll x, y;
} Point;

/* ---------- utility: read points from GNL ---------- */
int read_points_from_file(const char *path, Point pts[], int n)
{
    int fd = open(path, O_RDONLY);
    if (fd < 0) { perror("open"); return -1; }

    for (int i = 0; i < n; i++) {
        char *line = get_next_line(fd);
        if (!line) {
            fprintf(stderr, "Unexpected EOF at line %d\n", i);
            close(fd);
            return -1;
        }
        // parse "x,y" robustly (allow negative)
        long long x = 0, y = 0;
        int sign = 1;
        int idx = 0;

        // parse x
        sign = 1;
        if (line[idx] == '-') { sign = -1; idx++; }
        if (line[idx] < '0' || line[idx] > '9') { free(line); close(fd); return -1; }
        x = 0;
        while (line[idx] >= '0' && line[idx] <= '9') {
            x = x * 10 + (line[idx++] - '0');
        }
        x *= sign;

        // skip comma
        if (line[idx] != ',') { free(line); close(fd); return -1; }
        idx++;

        // parse y
        sign = 1;
        if (line[idx] == '-') { sign = -1; idx++; }
        if (line[idx] < '0' || line[idx] > '9') { /* allow 0-length? */ }
        y = 0;
        while (line[idx] >= '0' && line[idx] <= '9') {
            y = y * 10 + (line[idx++] - '0');
        }
        y *= sign;

        pts[i].x = x;
        pts[i].y = y;
        free(line);
    }

    close(fd);
    return 0;
}

/* ---------- centroid and angle sort (heuristic) ---------- */

typedef struct {
    Point p;
    double angle;
} PAngle;

int cmp_pangle(const void *a, const void *b)
{
    const PAngle *pa = (const PAngle*)a;
    const PAngle *pb = (const PAngle*)b;
    if (pa->angle < pb->angle) return -1;
    if (pa->angle > pb->angle) return 1;
    return 0;
}

void order_points_by_angle(Point in[], Point out[], int n)
{
    // compute centroid (double)
    double cx = 0.0, cy = 0.0;
    for (int i = 0; i < n; i++) {
        cx += (double)in[i].x;
        cy += (double)in[i].y;
    }
    cx /= n;
    cy /= n;

    PAngle *arr = malloc(sizeof(PAngle) * n);
    if (!arr) { perror("malloc"); exit(1); }

    for (int i = 0; i < n; i++) {
        arr[i].p = in[i];
        arr[i].angle = atan2((double)in[i].y - cy, (double)in[i].x - cx);
    }

    qsort(arr, n, sizeof(PAngle), cmp_pangle);

    for (int i = 0; i < n; i++) out[i] = arr[i].p;

    free(arr);
}

/* ---------- shoelace area (returns absolute area as double) ---------- */
double polygon_area(Point poly[], int n)
{
    long double sum = 0.0L;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        sum += (long double)poly[i].x * (long double)poly[j].y
             - (long double)poly[j].x * (long double)poly[i].y;
    }
    if (sum < 0) sum = -sum;
    return (double)(sum / 2.0L);
}

/* ---------- point-in-polygon: ray casting (returns 1 if inside or on edge, 0 otherwise) ---------- */
int point_on_segment_ll(Point a, Point b, Point p)
{
    // check collinear
    long long cross = (b.x - a.x) * (p.y - a.y) - (b.y - a.y) * (p.x - a.x);
    if (cross != 0) return 0;
    // check within bounding box
    if ((p.x < (a.x < b.x ? a.x : b.x)) || (p.x > (a.x > b.x ? a.x : b.x))) return 0;
    if ((p.y < (a.y < b.y ? a.y : b.y)) || (p.y > (a.y > b.y ? a.y : b.y))) return 0;
    return 1;
}

int point_in_poly(Point p, Point poly[], int n)
{
    // First, check if point is exactly on an edge
    for (int i = 0, j = n-1; i < n; j = i++) {
        if (point_on_segment_ll(poly[j], poly[i], p)) return 1;
    }

    // Ray casting: count intersections of ray to the right
    int inside = 0;
    for (int i = 0, j = n-1; i < n; j = i++) {
        long long xi = poly[i].x, yi = poly[i].y;
        long long xj = poly[j].x, yj = poly[j].y;

        // Check if edge (j->i) crosses horizontal ray from p to +inf
        int intersect = ((yi > p.y) != (yj > p.y)) &&
                        ( (double)p.x < (double)(xj - xi) * (double)(p.y - yi) / (double)(yj - yi) + (double)xi );
        if (intersect) inside = !inside;
    }
    return inside;
}

/* ---------- segment intersection (robust orientation) ---------- */
int sign_ll(long long v) {
    if (v > 0) return 1;
    if (v < 0) return -1;
    return 0;
}

long long orient_ll(Point a, Point b, Point c) {
    // cross product (b-a) x (c-a)
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

int segments_intersect(Point a, Point b, Point c, Point d)
{
    long long o1 = orient_ll(a, b, c);
    long long o2 = orient_ll(a, b, d);
    long long o3 = orient_ll(c, d, a);
    long long o4 = orient_ll(c, d, b);

    int s1 = sign_ll(o1), s2 = sign_ll(o2), s3 = sign_ll(o3), s4 = sign_ll(o4);

    if (s1 == 0 && point_on_segment_ll(a, b, c)) return 1;
    if (s2 == 0 && point_on_segment_ll(a, b, d)) return 1;
    if (s3 == 0 && point_on_segment_ll(c, d, a)) return 1;
    if (s4 == 0 && point_on_segment_ll(c, d, b)) return 1;

    if (s1 != s2 && s3 != s4) return 1;
    return 0;
}

/* ---------- test whether rectangle defined by (x1,y1) and (x2,y2) is entirely inside poly ---------- */
int rect_inside_poly(Point r1, Point r2, Point poly[], int n)
{
    // rectangle corners (axis-aligned)
    ll x1 = r1.x, y1 = r1.y;
    ll x2 = r2.x, y2 = r2.y;
    if (x1 == x2 || y1 == y2) return 0; // degenerate

    ll xmin = (x1 < x2) ? x1 : x2;
    ll xmax = (x1 > x2) ? x1 : x2;
    ll ymin = (y1 < y2) ? y1 : y2;
    ll ymax = (y1 > y2) ? y1 : y2;

    Point c[4];
    c[0].x = xmin; c[0].y = ymin;
    c[1].x = xmin; c[1].y = ymax;
    c[2].x = xmax; c[2].y = ymax;
    c[3].x = xmax; c[3].y = ymin;

    // 1) all 4 corners inside polygon?
    for (int k = 0; k < 4; k++) {
        if (!point_in_poly(c[k], poly, n)) return 0;
    }

    // 2) check each rectangle edge against each polygon edge for intersection
    // rectangle edges: (0->1), (1->2), (2->3), (3->0)
    for (int re = 0; re < 4; re++) {
        Point ra = c[re];
        Point rb = c[(re + 1) % 4];
        for (int i = 0, j = n-1; i < n; j = i++) {
            Point pa = poly[j];
            Point pb = poly[i];
            if (segments_intersect(ra, rb, pa, pb)) {
                // If intersection is at rectangle corner and that corner equals polygon vertex,
                // it's OK (we already tested corner-on-edge in point_in_poly). To be safe,
                // treat any proper intersection as failing containment.
                // Here segments_intersect returned true for any intersection (including touching),
                // but touching at polygon vertex could correspond to rectangle lying exactly on boundary.
                // If you want to allow rectangles that touch the polygon boundary, you can adjust here.
                // For now, we consider any intersection means not strictly inside (but corners on boundary allowed).
                // To allow touching, you would need to filter cases where intersection is exactly at the corner.
                // Let's allow touching: if intersection is only because a rectangle corner equals a polygon vertex or lies on polygon edge, keep it.
                // So check whether the intersection is at the rectangle corner that is on polygon edge/vertex.
                // We'll detect the simple case: if any rectangle edge intersects polygon edge at a point that is not an endpoint
                // of both segments, reject. Otherwise allow.
                // For simplicity and safety, we reject any intersection here:
                return 0;
            }
        }
    }

    // passed both tests
    return 1;
}

/* ---------- main: read, order, shoelace, search rectangles ---------- */
int main(int ac, char **av)
{
    if (ac < 2) {
        fprintf(stderr, "Usage: %s input_file\n", av[0]);
        return 1;
    }

    Point pts[NPOINTS];
    if (read_points_from_file(av[ac-1], pts, NPOINTS) != 0) {
        fprintf(stderr, "Failed to read points\n");
        return 1;
    }

    // Make a copy and order by angle (heuristic)
    Point poly[NPOINTS];
    order_points_by_angle(pts, poly, NPOINTS);

    // Compute polygon area (shoelace)
    double poly_area = polygon_area(poly, NPOINTS);
    printf("Polygon area (shoelace on angle-ordered points) = %.0f\n", poly_area);

    // Now brute-force: for each pair of original points, build axis-aligned rectangle and test inclusion
    double max_area = 0.0;
    Point best_a = {0,0}, best_b = {0,0};
    for (int i = 0; i < NPOINTS - 1; i++) {
        for (int j = i + 1; j < NPOINTS; j++) {
            // rectangle defined by pts[i] and pts[j]
            if (pts[i].x == pts[j].x || pts[i].y == pts[j].y) continue;
            if (rect_inside_poly(pts[i], pts[j], poly, NPOINTS)) {
                double area = (double) llabs(pts[i].x - pts[j].x) * (double) llabs(pts[i].y - pts[j].y);
                if (area > max_area) {
                    max_area = area;
                    best_a = pts[i];
                    best_b = pts[j];
                }
            }
        }
    }

    printf("Max axis-aligned rectangle area (defined by two input points and fully inside polygon): %.0f\n", max_area);
    if (max_area > 0.0) {
        printf("Best rectangle corners: (%lld,%lld) and (%lld,%lld)\n",
               best_a.x, best_a.y, best_b.x, best_b.y);
    }

    return 0;
}
