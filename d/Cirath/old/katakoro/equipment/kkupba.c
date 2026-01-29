/* Khahan's Kupba
 * 17 April 1995, Chaos
 */

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>

create_armour()
{
   set_name("kupba");
   set_adj("leather");
   set_long("This is a low cap with a band of thick sable on the brow.  "+
	"It is of the same design as commonly worn among the members of "+
	"the camp, but this one looks to be of a finer quality.\n");
   set_at(A_HEAD);
   set_ac(3);

   add_prop(OBJ_I_VALUE,44);

}
