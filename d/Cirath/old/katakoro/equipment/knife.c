/* Khahan's knife
 * 17 April 1995, Chaos
 */

inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>

create_weapon()
{
   set_name("knife");
   set_adj("steel");
   set_adj("black");
   set_adj("fine");
   set_long("This long straight knife was made as a gift for the Khahan "+
	"by the smith of the Encampent.  It is of a fine blackened steel "+
	"identical to his sword and is of excellent workmanship.\n");
   set_hit(13);
   set_pen(14);
   set_wt(W_KNIFE);
   set_dt(W_SLASH);
   set_hands(W_LEFT);

   add_prop(OBJ_I_VALUE,590);

}
