/*
 * ale.c
 *
 * Used in nyreese/cadu_inn.c
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
    set_soft_amount(100);
    set_alco_amount(4);
    set_name("ale");
    set_adj("small");
    set_short("small ale");
    set_pshort("small ales");
    set_long("It's a small but refreshing ale.\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}
