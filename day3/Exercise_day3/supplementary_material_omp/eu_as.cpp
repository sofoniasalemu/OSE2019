/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 * This file contains routines to serially compute the call and
 * put price of an European option.
 *
 * Simon Scheidegger
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include <algorithm>    // Needed for the "max" function
#include <cmath>
#include <iostream>
#include <omp.h>

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 A simple implementation of the Box-Muller algorithm, used to
generate gaussian random numbers; necessary for the Monte Carlo
method below. */

double gaussian_box_muller() {
  double x = 0.0;
  double y = 0.0;
  double euclid_sq = 0.0;

  // Continue generating two uniform random variables
  // until the square of their "euclidean distance"
  // is less than unity
  do {
    x = 2.0 * rand() / static_cast<double>(RAND_MAX)-1;
    y = 2.0 * rand() / static_cast<double>(RAND_MAX)-1;
    euclid_sq = x*x + y*y;
  } while (euclid_sq >= 1.0);

  return x*sqrt(-2*log(euclid_sq)/euclid_sq);
}


struct result_str{
        double price;
        double time_elapsed;
};
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Pricing a Asian European vanilla call option with a Monte Carlo method

// ############################### CALL  ##############################
result_str monte_carlo_asian_call_price_par(const int& num_sims, const double& S, const double& K, const double&r, const double& v, const double& T) {
  double S_cur = 0.0;
  double payoff_sum = 0.0;
  double time=-omp_get_wtime();
  #pragma omp parallel for reduction(+:payoff_sum)
  for (int i=0; i<num_sims; i++)
  {
    double S_adjust =S;
    double S_av = S;
    for (int j=1; j<T; j++)
    {
        double gauss_bm = gaussian_box_muller();
        S_adjust = S_adjust * exp((r-0.5*v*v)+sqrt(v*v)*gauss_bm);
        S_av +=S_adjust;
    }
    S_cur=S_av / static_cast<double>(T);
    payoff_sum += std::max(S_cur - K, 0.0);
  }
  time+=omp_get_wtime();
  result_str result;
  result.price=(payoff_sum / static_cast<double>(num_sims)) * exp(-r*T);
  result.time_elapsed=time;
  return result;
}
result_str monte_carlo_asian_call_price(const int& num_sims, const double& S, const double& K, const double&r, const double& v, const double& T) {
  double S_cur = 0.0;
  double payoff_sum = 0.0;
  double time=-omp_get_wtime();
 
  for (int i=0; i<num_sims; i++)
  {
    double S_adjust =S;
    double S_av = S;
    for (int j=1; j<T; j++)
    {
        double gauss_bm = gaussian_box_muller();
        S_adjust = S_adjust * exp((r-0.5*v*v)+sqrt(v*v)*gauss_bm);
        S_av +=S_adjust;
    }
    S_cur=S_av / static_cast<double>(T);
    payoff_sum += std::max(S_cur - K, 0.0);
  }
  time+=omp_get_wtime();
  result_str result;
  result.price=(payoff_sum / static_cast<double>(num_sims)) * exp(-r*T);
  result.time_elapsed=time;
  return result;
}

// ########################  PUT    ####################################################
result_str monte_carlo_asian_put_price_par(const int& num_sims, const double& S, const double& K, const double&r, const double& v, const double& T) {
  double S_cur = 0.0;
  double payoff_sum = 0.0;
  double time=-omp_get_wtime();
  #pragma omp parallel for reduction(+:payoff_sum)
  for (int i=0; i<num_sims; i++)
  {
    double S_adjust =S;
    double S_av = S;
    for (int j=1; j<T; j++)
    {
        double gauss_bm = gaussian_box_muller();
        S_adjust = S_adjust * exp((r-0.5*v*v)+sqrt(v*v)*gauss_bm);
        S_av +=S_adjust;
    }
  
    S_cur=S_av / static_cast<double>(T);
    payoff_sum += std::max(K-S_cur, 0.0);
  }
  time+=omp_get_wtime();
  result_str result;
  result.price=(payoff_sum / static_cast<double>(num_sims)) * exp(-r*T);
  result.time_elapsed=time;
  return result;
}
result_str monte_carlo_asian_put_price(const int& num_sims, const double& S, const double& K, const double&r, const double& v, const double& T) {
  double S_cur = 0.0;
  double payoff_sum = 0.0;
  double time=-omp_get_wtime();

  for (int i=0; i<num_sims; i++)
  {
    double S_adjust =S;
    double S_av = S;
    for (int j=1; j<T; j++)
    {
        double gauss_bm = gaussian_box_muller();
        S_adjust = S_adjust * exp((r-0.5*v*v)+sqrt(v*v)*gauss_bm);
        S_av +=S_adjust;
    }

    S_cur=S_av / static_cast<double>(T);
    payoff_sum += std::max(K-S_cur, 0.0);
  }
  time+=omp_get_wtime();
  result_str result;
  result.price=(payoff_sum / static_cast<double>(num_sims)) * exp(-r*T);
  result.time_elapsed=time;
  return result;
}


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

int main(int argc, char **argv) {

  // Parameters
  int num_sims = 100000;   // Number of simulated asset paths
  double S = 100.0;  // Option price
  double K = 100.0;  // Strike price
  double r = 0.05;   // Risk-free rate (5%)
  double v = 0.2;    // Volatility of the underlying (20%)
  double T = 10.0;    // One year until expiry

  // Then we calculate the call/put values via Monte Carlo

  result_str asian_call = monte_carlo_asian_call_price(num_sims, S, K, r, v, T);
  result_str asian_put = monte_carlo_asian_put_price(num_sims, S, K, r, v, T);
  result_str asian_call_par = monte_carlo_asian_call_price_par(num_sims, S, K, r, v, T);
  result_str asian_put_par = monte_carlo_asian_put_price_par(num_sims, S, K, r, v, T);

  // Finally we output the parameters and prices
  std::cout << "Number of Paths: " << num_sims << std::endl;
  std::cout << "Underlying:      " << S << std::endl;
  std::cout << "Strike:          " << K << std::endl;
  std::cout << "Risk-Free Rate:  " << r << std::endl;
  std::cout << "Volatility:      " << v << std::endl;
  std::cout << "Maturity:        " << T << std::endl<<std::endl;

  std::cout <<"Asian call price: "<<asian_call.price << "computed in "<<asian_call.time_elapsed<< "seconds"<<std::endl;
  std::cout <<"Asian call price (paral): "<<asian_call_par.price << "computed in "<<asian_call_par.time_elapsed<< "seconds"<<std::endl<<std::endl;

  std::cout <<"Asian put price:"<<asian_put.price << "computed in "<<asian_put.time_elapsed<< "seconds"<<std::endl;
  std::cout <<"Asian put price (paral):"<<asian_put_par.price << "computed in "<<asian_put_par.time_elapsed<< "seconds"<<std::endl;

  
  

  return 0;
}
