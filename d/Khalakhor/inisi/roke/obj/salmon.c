/*
 * salmon.c
 *
 * Used in nyreese/cadu_inn.c
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
    set_short("raw spiced salmon");
    set_pshort("raw spiced salmons");
    set_name("salmon");
    add_name("fish");
    set_pname("salmons");
    set_adj("raw");
    set_long("It's a piece of raw salmon, carefully salted and spiced.\n");
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 220);
    set_amount(200);
}
