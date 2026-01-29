/* Ashlar, 21 Aug 97 */

inherit "/std/armour";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("mail");
    add_name("chainmail");
    set_adj("rusty");
    add_adj("chain");
    set_short("rusty chainmail");
    set_ac(29);
    set_at(A_TORSO);
    set_long("This is a shirt of chainmail armour, heavily rusted " +
	"but well made.\n");
    add_prop(OBJ_I_VOLUME, 2000);
}
