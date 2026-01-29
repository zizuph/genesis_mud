/*
 * rose.c
 *
 * Used in npc/bard.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>

void decay_rose();

void
create_object()
{
    set_name("rose");
    set_pname("roses");
    set_short("red rose");
    set_pshort("red roses");
    set_long("It is a wonderful red rose.\n");
    set_adj("red");
    add_cmd_item(({ "rose", "flower" }), "smell", "It smells good.\n");
    add_prop(OBJ_I_VALUE, 29);
    add_prop(OBJ_I_WEIGHT, 50);
    set_alarm(500.0, 0.0, decay_rose);
}

void
decay_rose()
{
    object o;
    if (interactive(o = environment(this_object())))
        o->catch_msg("The once beautiful red rose withers away... "
                     +"without tender love it couldn't survive. \n");
    remove_object();
}
