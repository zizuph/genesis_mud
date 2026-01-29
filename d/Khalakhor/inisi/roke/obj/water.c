/*
 * water.c
 *
 * Used in obj/questparcel.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/drink";

#include <stdproperties.h>

void
create_drink()
{
    set_name("water");
    set_adj("cold");
    add_adj("salt");
    set_short("small amount of cold salt water");
    set_long("This is a small amount of salt sea water.\n");
    set_soft_amount(330);
    add_prop(OBJ_I_WEIGHT, 330);
    add_prop(OBJ_I_VOLUME, 330);
    add_prop(OBJ_I_NO_GET,
             "And what do you want to carry it in?\n");
    add_prop(OBJ_I_NO_DROP,
             "If you dropped the water, it would vanish in the ground " +
             "immediately.\n");
    add_prop(OBJ_I_NO_GIVE,
             "Nobody can hold water with their bare hands, so you can't\n" +
             "give it away.\n");
}
