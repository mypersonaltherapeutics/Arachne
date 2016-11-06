#include "stdafx.h" 
 
#include <math.h> 
 
#include "hh.h" 
 
namespace mod 
{ 
 
template <typename T> 
hh<T>::hh(T v) 
{ 
    this->celsius = celsius; 
 
    this->_currents = std::vector<T*>(_numCurrents); 
    this->_currents[0] = &ina; 
    this->_currents[1] = &ik; 
    this->_currents[2] = &il; 
 
    this->_states = std::vector<T*>(_numStates); 
    this->_states[0] = &m; 
    this->_states[1] = &h; 
    this->_states[2] = &n; 
 
    this->_derivatives = std::vector<T*>(_numStates); 
    this->_derivatives[0] = &m_rhp; 
    this->_derivatives[1] = &h_rhp; 
    this->_derivatives[2] = &n_rhp; 
} 
 
// INITIAL 
template <typename T> 
void hh<T>::init() 
{ 
    rates(v); 
    m=minf; 
    h=hinf; 
    n=ninf; 
} 
 
// DERIVATIVE 
template <typename T> 
void hh<T>::states() 
{ 
    rates(v); 
    m_rhp=(minf-m)/mtau; 
    h_rhp=(hinf-h)/htau; 
    n_rhp=(ninf-n)/ntau; 
} 
 
// BREAKPOINT 
template <typename T> 
void hh<T>::currents() 
{ 
    gna=gnabar*m*m*m*h; 
    ina=gna*(v-ena); 
    gk=gkbar*n*n*n*n; 
    ik=gk*(v-ek); 
    il=gl*(v-el); 
} 
 
// PROCEDURE(S) 
 
template <typename T> 
void hh<T>::rates(T v) 
{ 
//Computes rate and other constants at current v. 
                      //Call once from HOC to initialize inf at resting v. 
    // LOCAL 
        T  alpha, beta, sum, q10; 
 
        q10 = (T)3*((celsius - (T)6.3)/(T)10); 
                //"m" sodium activation system 
        alpha = (T).1 * vtrap(-(v+(T)40),(T)10); 
        beta =  (T)4 * exp(-(v+(T)65)/(T)18); 
        sum = alpha + beta; 
	mtau = (T)1/(q10*sum); 
        minf = alpha/sum; 
                //"h" sodium inactivation system 
        alpha = (T).07 * exp(-(v+(T)65)/(T)20); 
        beta = (T)1 / (exp(-(v+(T)35)/(T)10) + (T)1); 
        sum = alpha + beta; 
	htau = (T)1/(q10*sum); 
        hinf = alpha/sum; 
                //"n" potassium activation system 
        alpha = (T).01*vtrap(-(v+(T)55),(T)10) ; 
        beta = (T).125*exp(-(v+(T)65)/(T)80); 
	sum = alpha + beta; 
        ntau = (T)1/(q10*sum); 
        ninf = alpha/sum; 
} 
 
// FUNCTION(S) 
 
template <typename T> 
T hh<T>::vtrap(T x, T y) 
{ 
    T _vtrap; 
//Traps for (T)0 in denominator of rate eqns. 
        if (fabs(x/y) < (T)1e-6) { 
                _vtrap = y*((T)1 - x/y/(T)2); 
        ;}else{ 
                _vtrap = x/(exp(x/y) - (T)1); 
        } 
    return _vtrap; 
} 
 
template 
class hh<float>; 
 
template 
class hh<double>; 
 
} 
