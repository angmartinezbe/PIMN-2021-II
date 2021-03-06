#include <iostream>
#include <vector>
#include <cmath>

// constants
const double DELTA = 0.05;
const double LX = 1.479;
const double LY = 1.4*LX;
const int N = int(LX/DELTA)+1;
const int M = int(LY/DELTA)+1;
const int STEPS = 200;

typedef std::vector<double> Matrix; // alias

void initial_conditions(Matrix & m);
void boundary_conditions(Matrix & m);
void evolve(Matrix & m);
void print(const Matrix & m);
void init_gnuplot(void);
void plot_gnuplot(const Matrix & m);

int main(void)
{
  Matrix data(N*M);
  initial_conditions(data);
  boundary_conditions(data);

  init_gnuplot();
  for (int istep = 0; istep < STEPS; ++istep) {
    evolve(data);
    plot_gnuplot(data);
  }

  return 0;
}
void initial_conditions(Matrix & m)
{
  for(int ii=0; ii<N; ++ii) {
    for(int jj=0; jj<M; ++jj) {
      m[ii*M + jj] = 1.0;
    }
  }
}
void boundary_conditions(Matrix & m)
{
  int ii = 0, jj = 0;

  ii = 0;
  for (jj = 0; jj < M; ++jj)
    m[ii*M + jj] = 100;

  ii = N-1;
  for (jj = 0; jj < M; ++jj)
    m[ii*M + jj] = 0;

  jj = 0;
  for (ii = 1; ii < N-1; ++ii)
    m[ii*M + jj] = 0;

  jj = M-1;
  for (ii = 1; ii < N-1; ++ii)
    m[ii*M + jj] = 0;

  ii = N/3;
  for (jj = M/4; jj < M/4 + M/2; ++jj)
  m[ii*M + jj] = 75;

  ii = (2*N)/3;
  for (jj = M/4; jj < M/4 + M/2; ++jj)
  m[ii*M + jj] = -75;
}

void evolve(Matrix & m)
{
  for(int ii=0; ii<N; ++ii) {
    for(int jj=0; jj<M; ++jj) {
      // check if boundary
      if(ii == 0) continue;
      if(ii == N-1) continue;
      if(jj == 0) continue;
      if(jj == M-1) continue;
      if(ii == N/3 && jj>M/4 && jj<3*M/4) continue;
      if(ii == (2*N)/3 && jj>M/4 && jj<3*M/4) continue;
      // evolve non boundary
      m[ii*M+jj] = (m[(ii+1)*M + jj] +
                    m[(ii-1)*M + jj] +
                    m[ii*M + jj + 1] +
                    m[ii*M + jj - 1] )/4.0;
    }
  }
}

void print(const Matrix & m)
{
  for(int ii=0; ii<N; ++ii) {
    for(int jj=0; jj<M; ++jj) {
      std::cout << ii*DELTA << " " << jj*DELTA << " " <<  m[ii*M + jj] << "\n";
    }
    std::cout << "\n";
  }  
}

void init_gnuplot(void)
{
  std::cout << "set contour " << std::endl;
  std::cout << "set terminal gif animate " << std::endl;
  std::cout << "set out 'anim.gif' " << std::endl;
}

void plot_gnuplot(const Matrix & m)
{
  std::cout << "splot '-' w pm3d " << std::endl;
  print(m);
  std::cout << "e" << std::endl;
}
