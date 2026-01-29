/* Khahan's Robe
 * 17 April 1995, Chaos
 */

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>

create_armour()
{
   set_name("robe");
   set_adj("fur");
   set_adj("thick");
   set_long("This broad cuffed robe is lined with the finest, whitest  "+
	"ermine that could be found on the steppes.  It's leather is strong "+
	"and it looks to be very warm as well.\n");
   set_at(A_ROBE);
   set_ac(3);

   add_prop(OBJ_I_VALUE,100);

}
