inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include "/d/Krynn/icewall/castle2/local.h"

public void
create_weapon()
{
    set_name("hammer");
    add_name(({"weapon","club"}));
    set_pname("hammers");
    add_pname(({"weapons","clubs"}));
    set_adj("heavy");
    add_adj("blackened");
    set_short("heavy blackened hammer");
    set_pshort("heavy blackened hammers");
    set_long("A thick, steel forging hammer. It is blackened " +
        "with years of use and misuse, but the head of the " +
        "tool remains mostly intact.\n");
    set_default_weapon(23, 32, W_CLUB, W_BLUDGEON, W_ANYH);
    add_prop(OBJ_I_VOLUME, 4000);
    add_prop(OBJ_I_WEIGHT, 9000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(15,25));

}

