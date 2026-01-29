#pragma strict_types

inherit "/d/Genesis/std/pack";
inherit "/lib/keep";

#include <macros.h>
#include <stdproperties.h>

public void
create_pack()
{
    set_keep();
    set_mass_storage(0);
    set_name("sack");
    add_name("_amelias_sack");
    add_name("equipment");
    remove_name("pack");
    add_adj("leather");
    add_adj("brown");
    set_short("brown leather sack");
    set_pshort("brown leather sacks");
    set_long("The sack is tooled from " +
        "brown leather and seems to be able to hold " +
        "quite a lot.\n");
    add_prop(CONT_I_WEIGHT, 1500);
    add_prop(CONT_I_VOLUME, 1700);
    add_prop(CONT_I_MAX_WEIGHT, 100000);
    add_prop(CONT_I_MAX_VOLUME, 100000);
    add_prop(OBJ_I_VALUE, 150);
}

public string
query_recover()
{
    return MASTER + ":" + query_container_recover();
}

public void
init_recover(string args)
{
    init_container_recover(args);
}
