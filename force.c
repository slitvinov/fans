#include "embed.h"
#include "navier-stokes/centered.h"

double Reynolds = 160.;
int maxlevel = 9;
face vector muv[];
face vector av[];

int main() {
  L0 = 8.;
  origin (-0.5, -L0/2.);
  N = 512;
  mu = muv;
  a = av;
  periodic(right);
  run();
}

event properties (i++)
{
  foreach_face()
    muv.x[] = fm.x[]*0.125/Reynolds;
}

u.n[left]  = dirichlet(0.0);
p[left]    = neumann(0.0);

u.n[embed] = fabs(y) > 0.25 ? neumann(0.0) : dirichlet(0.0);
u.t[embed] = fabs(y) > 0.25 ? neumann(0.0) : dirichlet(0.0);

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
  foreach()
    m[] = cs[] - 0.5;
  char path[1024];
  sprintf(path, "vort.%05d.ppm", i);
  output_ppm (omega, file = path, box = {{-0.5,-0.5},{7.5,0.5}},
	      min = -10, max = 10, linear = true, mask = m);
  
  sprintf(path, "pressure.%05d.ppm", i);
  output_ppm (p, file = path, box = {{-0.5,-0.5},{7.5,0.5}},
	      min = -0.1, max = 0.1, linear = true, mask = m);  
}

event acceleration (i++) {
  foreach_face(x) {
    if (fabs(y) < 0.1 && fabs(x - 5.0) < 0.1)
      av.x[] += 20.0;
  }
}

event adapt (i++) {
  adapt_wavelet ({cs,u}, (double[]){1e-2,3e-2,3e-2,3e-2}, maxlevel, 4);
}