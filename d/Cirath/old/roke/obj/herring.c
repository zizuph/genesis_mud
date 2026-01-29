/*
 * herring.c
 *
 * Used in nyreese/cadu_inn.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/* a smoked herring */

#pragma save_binary
#pragma strict_types

inherit "/std/food";

#include <stdproperties.h>

void
create_food()
{
    set_name("herring");
    add_name("fish");
    set_adj("barbecued");
    set_short("barbecued herring");
    set_pshort("barbecued herrings");
    set_long("The herring smells wonderful, as all food in Cadu.\n");
    add_prop(OBJ_I_WEIGHT, 64);
    add_prop(OBJ_I_VOLUME, 80);
    set_amount(64);
}
