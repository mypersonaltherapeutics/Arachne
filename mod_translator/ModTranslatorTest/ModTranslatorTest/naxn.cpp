#include "stdafx.h" 
 
#include <math.h> 
 
#include "naxn.h" 
 
namespace mod 
{ 
 
template <typename T> 
naxn<T>::naxn(T v, T ena, T celsius) 
{ 
    this->celsius = celsius; 
 
    this->_currents = std::vector<T*>(_numCurrents); 
    this->_currents[0] = &ina; 
 
    this->_states = std::vector<T*>(_numStates); 
    this->_states[0] = &m; 
    this->_states[1] = &h; 
 
    this->_derivatives = std::vector<T*>(_numStates); 
    this->_derivatives[0] = &m_rhp; 
    this->_derivatives[1] = &h_rhp; 
} 
 
// INITIAL 
template <typename T> 
void naxn<T>::init() 
{ 
    trates(v,sh); 
    m=minf; 
    h=hinf; 
} 
 
// DERIVATIVE 
template <typename T> 
void naxn<T>::states() 
{ 
    trates(v,sh); 
    m_rhp=(minf-m)/mtau; 
    h_rhp=(hinf-h)/htau; 
} 
 
// BREAKPOINT 
template <typename T> 
void naxn<T>::currents() 
{ 
    thegna=gbar*m*m*m*h; 
    ina=thegna*(v-ena); 
} 
 
// PROCEDURE(S) 
 
template <typename T> 
void naxn<T>::trates(T vm, T sh2) 
{ 
    // LOCAL 
        T  a, b, qt; 
 
        qt=q10*((celsius-(T)24)/(T)10); 
	a = trap0(vm,tha+sh2,Ra,qa); 
	b = trap0(-vm,-tha-sh2,Rb,qa); 
	mtau = (T)1/(a+b)/qt; 
        if (mtau<mmin) {mtau=mmin;} 
	minf = a/(a+b); 
	a = trap0(vm,thi1+sh2,Rd,qd); 
	b = trap0(-vm,-thi2-sh2,Rg,qg); 
	htau =  (T)1/(a+b)/qt; 
        if (htau<hmin) {htau=hmin;} 
	hinf = (T)1/((T)1+exp((vm-thinf-sh2)/qinf)); 
} 
 
// FUNCTION(S) 
 
template <typename T> 
T naxn<T>::trap0(T v, T th, T a, T q) 
{ 
    T _trap0; 
	if (fabs(v-th) > (T)1e-6) { 
	        _trap0 = a * (v - th) / ((T)1 - exp(-(v - th)/q)); 
	;} else { 
	        _trap0 = a * q; 
 	} 
    return _trap0; 
} 
 
template 
class naxn<float>; 
 
template 
class naxn<double>; 
 
} 
