#include "Bandpass.h"
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846f /* pi */
#endif


void Bandpass::Init()
{
  _lpHist = 0.f;
  _hpHist = 0.f;
  _d0LP = 0.f;
  _d0HP = 0.f;
  _gainHS = 0.f;
};
float Bandpass::Process(const float in)
{
  float hp = in -	_lpHist;
  float out	=	(_lpHist += _d0LP * hp);
  out += _gainHS * in;
  _hpHist  += _d0HP * (out -=	_hpHist);	
  return out;			
}

void Bandpass::SetHighCut(float normFreq, float gainHighShelf)
{
  float	arg	=	float(M_PI * normFreq);			
  float	l		=	float(cosf(arg) / sinf(arg));
  _d0LP		  =	1.f / (1.f + l);   
  _gainHS   =  gainHighShelf;         
}

void Bandpass::SetLowCut(float normFreq)
{ 
  if(normFreq == 0.f)
    _d0HP = 0.f;
  else
  {
    float	arg	=	float(M_PI * normFreq);			
    float	l		=	float(cosf(arg) / sinf(arg));
    _d0HP		  =	1.f / (1.f + l);              
  }
}
