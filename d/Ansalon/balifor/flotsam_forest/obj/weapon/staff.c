#pragma strict_types

inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

void create_weapon()
{
    set_name("staff");
    set_adj("wooden");
    add_adj("gnarled");
    set_short("gnarled wooden staff");
    set_pshort("gnarled wooden staves");
    set_long("This two-handed wooden staff is long and well " +
		"balanced for quick handling, while thick enough to cause " +
		"a headache for anyone at the receiving end of it.\n");
    set_default_weapon(40,20,W_POLEARM,W_BLUDGEON,W_BOTH);
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_WEIGHT, 2500);
}
