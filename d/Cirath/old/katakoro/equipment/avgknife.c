 /* Average knife
 * 17 April 1995, Chaos
 */

inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>

create_weapon()
{
   set_name("knife");
   set_adj("iron");
   set_adj("rough");
   set_long("This is a knife commonly worn by everyone living in the "+
	"steppes.  There is nothing remarkable about it and looks to "+
	"be quite sturdy.\n");
   set_hit(3);
   set_pen(3);
   set_wt(W_KNIFE);
   set_dt(W_SLASH);
   set_hands(W_ANYH);


}
