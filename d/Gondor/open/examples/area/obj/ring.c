/*
 * Random ring 
 * -- Finwe, April 2007
 */

#pragma save_binary

#include "/d/Gondor/defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>


inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/cmd/std/command_driver";

#define RING_NAME   "_random_ring_"
#define ADJ1        "elegant"
#define ADJ2        "polished"

void create_object()
{
    set_name("ring");
    set_adj("mithral");
    set_adj("woven");
    set_short("woven mithral ring");

    set_long("This is a " + short() + ". It was crafted from bands of " +
        "silver that has been woven together. It is polished and gleams " +
        "in the light. The ring looks valuable, and whoever lost it is " +
        "surely searching for it.\n");

    set_slots(A_ANY_FINGER);
    set_layers(0);
    set_looseness(2);

    add_prop(OBJ_I_WEIGHT,  20);
    add_prop(OBJ_I_VOLUME,  50);
    add_prop(OBJ_I_VALUE,  100);

}

enter_env(object dest,object old)
{
    seteuid(getuid());

    remove_name(RING_NAME);
    add_name(RING_NAME);
    if(living(E(TO)))
        dest->add_subloc(RING_NAME, this_object());
}

public void
leave_env(object from, object to)
{
    this_player()->remove_subloc(RING_NAME);
}

