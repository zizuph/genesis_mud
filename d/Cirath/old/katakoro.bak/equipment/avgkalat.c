/* Average Kalat
 * 18 April 1995, Chaos
 */

#include "/d/Cirath/defs.h"
inherit "/std/armour";
#include <wa_types.h>

create_armour()
{
   set_name("kalat");
   set_adj("wool");
   set_adj("average");
   set_long("This is a simple wool kalat worn by most of the "+
	"residents of the steppes.  It is a wool tunic that reaches "+
   "to the knees and provides some protection from the cold.\n");
   set_at(A_BODY);
   set_ac(1);
   
 }


