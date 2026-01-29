/* Smith's Hammer
 * 18 April 1995, Chaos
 */

inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>

create_weapon()
{
   set_name("hammer");
   set_adj("steel");
   set_adj("heavy");
   set_long("There is nothing special about this hammer other than "+
	"it's sturdy weight and fine craftsmanship.  It is used by "+
	"the smith to work the heated metal into the desired "+
	"shapes.\n");
   set_hit(9);
   set_pen(13);
   set_wt(W_CLUB);
   set_dt(W_BLUDGEON);
   set_hands(W_ANYH);


}
