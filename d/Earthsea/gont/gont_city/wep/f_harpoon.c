/*
* Harpoon for the fishermen in Gont Port
* Coded by Porta 971130.
*/

#pragma strict_types

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>

public void
create_weapon()
{
    set_name("harpoon");
    set_pname("harpoons");
    add_adj(({"short-shafted", "barbed"}));
    set_short("short-shafted barbed harpoon");
    set_pshort("short-shafted barbed harpoons");
    set_long("This is a short-shafted harpoon with"+
        " nasty barbs under the sharp edge. In the end"+
        " of the wooden shaft is a loop of iron, where"+
        " the fisherman using it can tie a rope.\n");
    set_hit(14);
    set_hit(19);
    set_wt(W_POLEARM);
    set_dt(W_IMPALE);
    set_hands(W_BOTH);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(14, 19) - 30 + random(60));
    add_prop(OBJ_I_WEIGHT, 5000);
}
