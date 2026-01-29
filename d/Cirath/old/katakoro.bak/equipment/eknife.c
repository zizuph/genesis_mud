/* Empress' knife
 * 17 April 1995, Chaos
 */

inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>

create_weapon()
{
   set_name("knife");
   set_adj("steel");
   set_adj("fine");
   set_long("This long straight knife was made as a gift by the "+
	"Khahan's smith.  It is of a fine steel, probably stolen "+
	"during one of the many raids made by the Khahan's army.  "+
	"It is beautifully detailed and of excellent workmanship.\n");
   set_hit(12);
   set_pen(13);
   set_wt(W_KNIFE);
   set_dt(W_SLASH);
   set_hands(W_ANYH);


}
