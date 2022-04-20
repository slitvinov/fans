#include "saint-venant.h"

event init (t = 0) {
  foreach()
    h[] = 0.1 + 1.*exp(-200.*(x*x + y*y));
}

event end (i = 10) {
  printf ("i = %d t = %g\n", i, t);
}

event images (i++) {
  output_ppm (h);
}

int main() {
  origin (-0.5, -0.5);
  run();
}

