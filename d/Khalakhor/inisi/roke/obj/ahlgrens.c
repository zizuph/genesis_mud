/*
 * ahlgrens.c
 *
 * Used in nyreese/cadu_inn.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/* A package of the world famous Ahlgrens bilar */

#pragma save_binary
#pragma strict_types

inherit "/std/food";

#include <stdproperties.h>

void
create_food()
{
    set_short("bag of ahlgrens stagecoaches");
    set_pshort("bags of ahlgrens stagecoaches");
    set_name("stagecoaches");
    add_name("coaches");
    add_name("ahlgrens");
    add_name("bag");
    set_long("This is a bag of the delicious stagecoaches from Ahlgrens.\n");
    add_prop(OBJ_I_WEIGHT, 120);
    add_prop(OBJ_I_VOLUME, 130);
    set_amount(114);
}
