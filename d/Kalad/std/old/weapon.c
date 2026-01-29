inherit "/std/weapon";
inherit "/lib/keep";
inherit "/d/Kalad/std/volume";
#include "/d/Kalad/defs.h"
#include "/sys/wa_types.h"

#define K_WEP_DRAWS   ({ ({5,10,8}), ({5,8,10}), ({5,8,4}), \
              ({5,10,8}), ({5,0,6}), ({5,1,12}), ({5,8,5}) })
/*
 * Weapon drawbacks for Kalad - more to my liking
 *
 * weapon		dull     corr     break
 * -------              ----     ----     -----
 * sword		  5       10         8
 * polearm		  5        8        10
 * axe                    5        8         4
 * knife		  5       10         8
 * club			  5        0         6
 * missile                5        1        12
 * javelin                5        8         5
 */

void
create_weapon()
{
    ::create_weapon();
}

void
set_wt(int type)
{
    int *likely;

    if (query_lock())
      return;           /*changes locked out*/

    if (type >= 0 && type < W_NO_T)
    {
      wep_wt = type;
      likely = K_WEP_DRAWS[type];
      likely_dull = likely[0];
      likely_corr = likely[1];
      likely_break = likely[2];
    }
}


mixed
kalc_vol(string str, int weight)
{
   switch(str)
   {
      case "steel":
         return (itof(weight) / 6.9);
         break;

      case "iron":
         return (itof(weight) / 7.9);
         break;

      case "aluminum":
         return (itof(weight) / 2.7);
         break;

      case "chrome":
         return (itof(weight) / 7.1);
         break;

      case "gold":
         return (itof(weight) / 19.3);
         break;

      case "lead":
         return (itof(weight) / 11.3);
         break;

      case "copper":
         return (itof(weight) / 8.9);
         break;

      case "platinum":
         return (itof(weight) / 21.4);
         break;

      case "tin":
         return (itof(weight) / 7.3);
         break;

      case "silver":
         return (itof(weight) / 10.5);
         break;

      case "bronze":
         return (itof(weight) / 8.9);
         break;

      case "cast iron":
         return (itof(weight) / 7.3);
         break;

      case "brass":
         return (itof(weight) / 8.5);
         break;

      default:
         return "bug";
    }
}

