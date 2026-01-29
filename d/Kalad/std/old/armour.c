inherit "/std/armour";
inherit "/lib/keep";
#include "/d/Kalad/defs.h"
#include "/sys/wa_types.h"

void
create_armour()
{
}

string
query_recover()
{
    return MASTER + ":" + query_arm_recover();
}

void
init_recover(string arg)
{
    init_arm_recover(arg);
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

