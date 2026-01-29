/*
 * fur.c
 *
 * Used in npc/troll.c npc/kobold3.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("fur");
    set_adj("smelly");
    set_short("smelly fur");
    set_long("This is an unprepared fur for some poor animal.\n");

    set_ac(10);
    set_am(({-1, 0, 1}));
    add_prop(OBJ_I_WEIGHT, 15000);
    add_prop(OBJ_I_VOLUME, 8000);
}
