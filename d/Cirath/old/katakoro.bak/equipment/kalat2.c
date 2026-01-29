/* Camp Guard Hide Armour
 * Created 9 March 1995
 * by Chaos
 */

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>

create_armour()
{
   set_name("kalat");
   set_adj("wool");
   set_adj("heavy");
   set_adj("foul-smelling");
   set_short("foul-smelling, heavy wool kalat");
   set_long("This is the normal form of armour worn by soldiers "+
	"in the Khahan's army.\n");
   set_at(A_ROBE);
   set_ac(8);
   
 }

