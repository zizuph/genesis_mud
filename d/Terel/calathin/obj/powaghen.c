/*
 * File: powaghen.c
 * Description: A black leather pack worn around the waist
 * Date: 03/15/03
 */

#include "/d/Terel/include/Terel.h"
#include <wa_types.h>

inherit "/d/Genesis/std/wearable_pack";
inherit "/lib/keep";

public void
create_wearable_pack()
{
    ::create_wearable_pack();
    set_name("powaghen");
    add_name(({"belt", "pack", "beltpack"}));
    add_adj("leather");
    set_short("black beltpack");
    set_long("The black beltpack is constructed of a methodical design " +
             "held together at several points with mechanical clasps. " +
             "Hundreds of thinly-sliced dyed leather strips have been " +
             "closely knit together in a pattern spiraling back in on " +
             "itself. Cold-wrought silver leaves decorate the clasps " +
             "that close on two points on opposite sides of the belt. " +
             "Knotted in a secure fashion, lashing of the same leather " +
             "hold the pack tight.\n");

    add_prop(CONT_I_WEIGHT, 2500);            /* grams */
    add_prop(CONT_I_MAX_WEIGHT, 110000);      /* grams */
    add_prop(CONT_I_VOLUME, 8000);            /* ml */
    add_prop(CONT_I_MAX_VOLUME, 100000);      /* ml */
    add_prop(CONT_I_HOLDS_COMPONENTS, 1);
    add_prop(OBJ_I_VALUE, 450);               /* Worth 450 cc */ 

    set_keep(1);
    set_mass_storage(1);
    set_slots(A_WAIST);
    set_layers(8);
    set_looseness(8);
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
