/* Ashlar, 21 Aug 97 */

inherit "/std/armour";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("shirt");
    set_adj("studded");
    add_adj("leather");
    set_short("studded leather shirt");
    set_ac(14);
    set_at(A_TORSO);
    set_long("This is a shirt of thick leather with metal studs sewn " +
	"onto the leather. It is dirty and a bit torn along the edges.\n");
    add_prop(OBJ_I_VOLUME, 1600);
}

