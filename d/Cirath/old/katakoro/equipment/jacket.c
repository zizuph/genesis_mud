/* Khahan's Jacket
 * 17 April 1995, Chaos
 */

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>

create_armour()
{
   set_name("jacket");
   set_adj("silk");
   set_adj("blue");
   set_long("This blue silk jacket is of the finest quality.  The back is "+
	"embroidered with golden dragons which reach around and down the "+
	"arms.  It doesn't look like it would be effective armour but it "+
	"does look valuable.\n");
   set_at(A_BODY);
   set_ac(0);

   add_prop(OBJ_I_VALUE,250);

}
