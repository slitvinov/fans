#include "embed.h"
#include "navier-stokes/centered.h"

double Reynolds = 10000.;
int maxlevel = 10;
face vector muv[];
face vector av[];

int main() {
  L0 = 8.;
  origin (-0.5, -L0/2.);
  N = 2048;
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
    u.x[] = 1.0;
}

event logfile (i++)
  fprintf (stderr, "%d %g %d %d\n", i, t, mgp.i, mgu.i);

event movies (i += 4; t <= 15.)
{
  scalar omega[], m[];
  vorticity (u, omega);
  char path[1024];
  sprintf(path, "vort.%05d.ppm", i);
  output_ppm (omega, file = path, box = {{-0.5,-0.5},{7.5,0.5}},
	      min = -100, max = 100, linear = true);
  
  sprintf(path, "pressure.%05d.ppm", i);
  output_ppm (p, file = path, box = {{-0.5,-0.5},{7.5,0.5}},
	      min = -0.1, max = 0.1, linear = true);
}

event acceleration (i++) {
  foreach_face(x) {
    if (fabs(y - 0.25) < 0.1 && fabs(x - 0.25) < 0.1)
      av.x[] += 20.0;
    if (fabs(y + 0.25) < 0.1 && fabs(x - 0.25) < 0.1)
      av.x[] += 10.0;
  }
}

event adapt (i++) {
  adapt_wavelet ({cs,u}, (double[]){1e-2,3e-2,3e-2,3e-2}, maxlevel, 4);
}
