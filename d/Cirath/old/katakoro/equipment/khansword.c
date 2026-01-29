/* Khahan's Sword
 * 17 April 1995, Chaos
 */

#include "/d/Cirath/defs.h"
inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>

create_weapon()
{
   set_name("sword");
   set_adj("steel");
   set_adj("black");
   set_short("fine, black steel sword");
   set_adj("fine");
   set_long("This long straight sword was made as a gift for the Khahan "+
	"by the smith of the Encampent.  It is of a fine blackened steel "+
	"and is of excellent workmanship.\n");
   set_hit(38);
   set_pen(27);
   set_wt(W_SWORD);
   set_dt(W_SLASH);
   set_hands(W_RIGHT);

   add_prop(OBJ_I_VALUE,1350);

}
