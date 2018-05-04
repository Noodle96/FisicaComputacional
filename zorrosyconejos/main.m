
%problema de los zorros y conejos con las ecuaciones de lotka y volterra

%constantes
a = 0.4;
b= 0.37;
c = 0.3;
d = 0.05;
tf = 100;
to = 0;
N = 10000;
delta = (tf-to) / N;

R(1) = 3;
F(1) = 1;

for e = 1 : 10000
  R(e+1) = R(e) + R(e)*(a-b*F(e)) * delta;  
  F(e+1) = F(e) + F(e) *(-c + d *R(e))* delta;
  
  printf("%d %d\n", R(e),F(e));
endfor

plot(R);
hold on;
plot(F);
grid