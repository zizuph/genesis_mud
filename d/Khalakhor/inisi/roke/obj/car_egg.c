/*
 * car_egg.c
 *
 * Used in carisca/f8.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/food";

#include <stdproperties.h>

void
create_food()
{
    set_name("egg");
    set_short("white egg");
    set_adj("white");
    set_long("A white egg, most likely from a hen.\n");

    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 25);

    set_amount(50);
}
