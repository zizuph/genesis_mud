inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("cloak");
    set_adj(({ "light", "black" }));

    set_long("A very plain black cloak.  The strange fabric seems to be " +
        "rather light despite its apparent strength.\n");

    set_ac(25);
    set_at(A_ROBE);

    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_WEIGHT, 3250);
    add_prop(OBJ_I_VALUE, 1200);
}

