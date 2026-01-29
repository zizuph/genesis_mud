#include <formulas.h>

/*
 * this constant gives average time of combat expected
 * There must be such constant in order to calculate aid reasonably
 */
#define AVG_TIME  100


/*
 * function:  disarm_aid
 * arguments: chance - what is the chance of successfull disarm in %
 *            drop_chance - chance of making enemy drop when disarm 
 *                          successfull in %
 *            frequency - how often can we try in seconds
 *            duration - how long does it take while enemy wields again
 */
int
disarm_aid(int chance, int drop_chance, int frequency, int duration)
{
  int i, disarm_aid;
  float drop_ch, ch, result1, result2, nch, r, rr;

  ch = itof(chance - (chance * drop_chance / 100)) / 100.0;
  drop_ch = itof(chance * drop_chance / 100) / 100.0;


                            /*  standard unarmed values */
  disarm_aid = (F_PENMOD(40,100) - F_PENMOD(10,5)) * 100 / F_PENMOD(40,100);

  result1 = 1.0;
  result2 = 1.0;
  nch = 1.0;

  for(i=0; i < (AVG_TIME/frequency); i++)
  {
    nch = nch * (1.0 - drop_ch);
    result1 += nch * itof(AVG_TIME - ((i+1)*frequency)) / itof(AVG_TIME);
    result2 += nch;
  }
  result2 /= itof(1 + (AVG_TIME/frequency));

  /* drop aid */
  r = drop_ch * itof(disarm_aid) * result1;

  /* disarm aid */
  rr = ch * itof(disarm_aid) * result2 * itof(duration) / itof(frequency);

  write("*** C - ch = "+ftoi(ch*100.0)+"%\n");
  write("*** D - drop_ch = "+ftoi(drop_ch*100.0)+"%\n");
  write("*** A - disarm_aid = "+disarm_aid+"%\n");
  write("*** M1 - drop_modifier = "+ftoi(result1*100.0)+"/100\n");
  write("*** M2 - disarm_modifier = "+ftoi(result2*100.0)+"/100\n");
  write("*** DF - duration / frequency = "+ftoi(100.0*itof(duration)/itof(frequency))+"/100\n\n");

  write("*** drop aid = D*A*M1 = "+ftoi(r)+" ***\n");
  write("*** disarm aid = C*A*M2*DF = "+ftoi(rr)+" ***\n");

  return ftoi(r+rr);
}
