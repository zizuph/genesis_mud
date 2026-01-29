/* Kashik Sword
 * Created 15 March 1995
 * by Chaos
 */

inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>

create_weapon()
{
   set_name("sword");
   set_adj("fine");
   set_short("fine sword");
   set_pshort("fine swords");
   set_long("This is a long straight sword issued only to the "+
	"elite warriors of the Khahan, the Kashik.\n");
   set_hit(31);
   set_pen(29);
   set_wt(W_SWORD);
   set_dt(W_SLASH);
   set_hands(W_ANYH);

   add_prop(OBJ_I_VALUE,139);

}
