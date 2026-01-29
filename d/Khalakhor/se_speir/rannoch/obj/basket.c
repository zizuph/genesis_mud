/*
 * Ciara's basket
 *
 * Darragh 00-10-04 
 */
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>

inherit "/d/Khalakhor/common/obj/stdpack";
inherit "/lib/keep";
inherit "/lib/holdable_item";

public void
create_pack()
{
    set_name("basket");
    set_pname("baskets");
    set_adj("big");
    add_adj("wicker");
    set_short("big wicker basket");
    set_pshort("big wicker baskets");
    set_long("This is a simple wicker basket, not intended to hold " +
        "anything than berries, mushrooms or fruit.\n");

    set_wearable(1);
    set_mass_storage(1);
    set_keep(1);

    add_prop(CONT_I_WEIGHT, 500);       /* Weighs 4.5 kg empty */
    add_prop(CONT_I_MAX_WEIGHT, 10000); /* Weighs 100 kg max. */   
    add_prop(CONT_I_VOLUME, 800);       /* Volume = 8 litres empty. */
    add_prop(CONT_I_MAX_VOLUME, 10000); /* Volume = 100 litres max. */
    add_prop(OBJ_I_VALUE, 100);          /* Valued at 400 coppers. */
    add_prop("_port_macdunn_pack",1);
}

public string
query_recover()
{
    return MASTER + ":" + query_container_recover() +
        query_keep_recover();
}

public void
init_recover(string arg)
{
    init_container_recover(arg);
    init_keep_recover(arg);
}
