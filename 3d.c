#include "embed.h"
#include "view.h"
#include "draw.h"
#include "navier-stokes/centered.h"

double Reynolds = 1000000.;
int maxlevel = 4;
face vector muv[];
face vector av[];
scalar omega[];

int main() {
  L0 = 2.;
  origin (-0.5, -L0/2.);
  N = 128;
  mu = muv;
  a = av;
  run();
}

event properties (i++)
{
  foreach_face()
    muv.x[] = fm.x[]*0.125/Reynolds;
}

u.n[left]  = dirichlet(1.0);
p[left]    = neumann(0.);

u.n[right] = neumann(0.);
p[right]   = dirichlet(0.);

u.n[embed] = neumann(0.0);
u.t[embed] = neumann(0.0);

event init (t = 0)
{
  foreach()
    u.x[] = 0.0;
}

event logfile (i++)
  fprintf (stderr, "%d %g %d %d\n", i, t, mgp.i, mgu.i);

event movies (i += 4; t <= 15.)
{
  char path[1024];

  vorticity (u, omega);
  sprintf(path, "vort.%05d.ppm", i);
  output_ppm (omega, file = path, box = {{-0.5,-0.5},{1.5,0.5}},
	      min = -20, max = 20, linear = true);
  view (width = 1400, height = 800, tx = -0.25, fov = 15);
  isosurface("omega", 10);
  isosurface("omega", -10);
  sprintf(path, "omega.%05d.ppm", i);
  save(path);
}

event acceleration (i++) {
  foreach_face(x) {
    if (fabs(z) < 0.1 && fabs(y - 0.25) < 0.1 && fabs(x + 0.25) < 0.1)
      av.x[] += 20.0;
    if (fabs(z) < 0.1 && fabs(y + 0.25) < 0.1 && fabs(x + 0.25) < 0.1)
      av.x[] += 10.0;
  }
}

event adapt (i++) {
  //adapt_wavelet ({cs,u}, (double[]){1e-2,3e-2,3e-2,3e-2}, maxlevel, 4);
}
