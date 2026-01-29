/*
 * A vial for potions
 */
#pragma save_binary

inherit "/std/container";

#include <macros.h>
#include <stdproperties.h>

public void
create_container()
{
    set_name("vial");
    add_name(({"_std_potion_vial"}));

    set_adj("empty");

    set_long("An empty vial. You could fill a potion into it.\n");

    add_prop(CONT_I_MAX_VOLUME, 1100);
    add_prop(CONT_I_MAX_WEIGHT, 1250);
    add_prop(CONT_I_VOLUME, 100);
    add_prop(CONT_I_WEIGHT, 250);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_I_VALUE, 24);
}

public string
query_recover()
{
    return MASTER + ":";
}

