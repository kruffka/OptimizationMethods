#include <stdio.h>
#include <math.h>


// Для одномерного поиска
#define f(x) x*x-6*x + 15
//x*x*x/3 - x*x/2-x-1
//x*x-6*x + 15

// Функции для двумерного поиска
// #define f2(x, y) (x*x-6*x+y*y+8*y)
// #define f2dx(x, y)  (2.0*x-6)
// #define f2dy(x, y) (2.0*y+8)

// #define f2(x, y) (x*x-6*x+2*y*y+8*y)
// #define f2dx(x, y)  (2.0*x-6)
// #define f2dy(x, y) (4.0*y+8)

#define f2(x, y) ((x-0.5)*(x-0.5)+(x-y)*(x-y))
#define f2dx(x, y)  (4.0*x-2*y-1)
#define f2dy(x, y) (-2.0*x+2.0*y)

int t1, g1;
double ternarySearchMin(double left, double right, double eps) { 

    double a, b;

    while (right - left > eps) {
        t1++;
        a = (left * 2 + right) / 3;
        b = (left + right * 2) / 3;

        if (f(a) < f(b))
            right = b;
        else
            left = a;
    }
    return (left + right) / 2;
}

double goldenSectionSearch(double a, double b, double eps) {
    double phi = (1 + sqrt(5)) / 2;
    double c, d;
    double yc, yd;

    c = b - (b - a) / phi;
    d = a + (b - a) / phi;
    yc = f(c);
    yd = f(d);

    while (b - a > eps) {
      g1++; 
      // printf("a %lf b %lf c %lf d %lf yc %lf yd %lf\n", a, b, c, d, yc, yd);

      if (yc < yd) {
        
        b = d;
        d = c;
        yd = yc;
        c = b - (b - a) / phi;
        yc = f(c);

      } else {
        
        a = c;
        c = d;
        yc = yd;
        d = a + (b - a) / phi;
        yd = f(d);
      }

    }

    if (yc < yd)
      return (a + d) / 2;
    else
      return (c + b) / 2;

}


void Gradient_Descent(double alfa, double eps, double *x_now) {

  // printf("Coord start: %.3f, %.3f\n", x_now[0], x_now[1]);

  double x_new[2];
	double distant;
	int k = 0, max_iter = 10;
  do {
		x_new[0] = x_now[0] - f2dx(x_now[0], x_now[1])*alfa;
		x_new[1] = x_now[1] - f2dy(x_now[0], x_now[1])*alfa;

		distant = sqrt(pow((x_new[0] - x_now[0]), 2) + pow((x_new[1] - x_now[1]), 2));
        
		x_now[0] = x_new[0];
		x_now[1] = x_new[1];

    // printf("[%d]  x = (%.3f, %.3f)  f(x1,x2)=%.3f\n", k, x_new[0], x_new[1], f2(x_new[0], x_new[1]));

    k++;

    if (k > max_iter) break;

  } while (distant > eps);

}


#define eps 0.001
#define left -10.0
#define right 10.0

int main() {


    printf("[ternarySearchMin]: %lf\n", ternarySearchMin(left, right, 2.0*eps));

    printf("[goldenSectionSearch]: %lf\n", goldenSectionSearch(left, right, 2.0*eps));

    printf("[Gradient_Descent]:\n");
    double x_now[2] = {1, 2};
    double alfa = 0.3;
    Gradient_Descent(alfa, 2.0*eps, x_now);
    
    printf("ternary operations: %d\ngolden operations: %d\n", t1, g1);    

    return 0;
}





