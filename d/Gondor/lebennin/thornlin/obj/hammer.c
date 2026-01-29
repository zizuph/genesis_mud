inherit "/std/weapon";
inherit "/lib/keep.c";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

void
create_weapon()
{
    set_name(({"heavy hammer","hammer","rusty hammer","heavy rusty hammer"}));
    add_name("_thornlin_ox_hammer_");
    set_adj(({"heavy","rusty"}));
    set_short("heavy rusty hammer");
    set_pshort("heavy rusty hammers");

    set_long("It is a heavy and rusty hammer, not for much use.\n");

    set_default_weapon(6+random(4),6+random(4),W_CLUB,W_BLUDGEON,0);

    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(OBJ_I_VOLUME, 5000);

    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(10,10) + random(100) - 75);
    // Make mystics able to do the quest...
    add_prop("mystic_weapon", 1);
}


