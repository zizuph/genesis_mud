/*
 * File: diddie.c
 * Description: A stout long sack with a strap worn over the shoulder
 * Date: 03/18/03
 */

#include "/d/Terel/include/Terel.h"
#include <wa_types.h>

inherit "/d/Genesis/std/wearable_pack";
inherit "/lib/keep";

public void
create_wearable_pack()
{
    ::create_wearable_pack();
    set_name("diddie");
    add_name(({"sack", "haversack"}));
    add_adj(({"stout", "black", "long"}));
    set_short("stout black haversack");
    set_long("The stout black haversack is made from some shiny black " +
             "scaly hide and is worn over the shoulder with a large " +
             "adjustable strap. The scaly hide has been treated to " +
             "maximize strength and durability. The strap, made from " +
             "the same material, has been fitted with ample padding to " +
             "reduce chaffing. At the top of the long sack, the opening " +
             "flap has several silver leaves worked into clasp. Lacing " +
             "is used to keep it secure.\n");

    add_prop(CONT_I_WEIGHT, 2500);            /* grams */
    add_prop(CONT_I_MAX_WEIGHT, 150000);      /* grams */
    add_prop(CONT_I_VOLUME, 8000);            /* ml */
    add_prop(CONT_I_MAX_VOLUME, 150000);      /* ml */
    add_prop(CONT_I_REDUCE_WEIGHT, 200);
    add_prop(CONT_I_REDUCE_VOLUME, 200);
    add_prop(OBJ_I_VALUE, 1050);               /* Worth 1050 cc */ 

    set_keep(1);
    set_mass_storage(1);
    set_slots(A_ANY_SHOULDER);
    set_layers(10);
    set_looseness(16);
}

string
query_recover()
{
    return MASTER + ":" + query_container_recover() + query_keep_recover();
}

public void
init_recover(string arg)
{
    init_container_recover(arg);
    init_keep_recover(arg); 
}
