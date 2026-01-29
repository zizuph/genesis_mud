/* Camp Guards Saber
 * Created 9 March 1995
 * by Chaos
 */

inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>

create_weapon()
{
   set_name("saber");
   set_adj("iron");
   set_adj("standard");
   set_long("This is a standard saber, issued to most soldiers "+
	"in the Khahan's army.\n");
   set_hit(19);
   set_pen(13);
   set_wt(W_SWORD);
   set_dt(W_SLASH);
   set_hands(W_ANYH);

   add_prop(OBJ_I_VALUE,95);

}
