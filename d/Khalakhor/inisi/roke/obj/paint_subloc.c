/*
 * paint_subloc.c
 *
 * Used in obj/can.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/* Subloc till paint can
* Made by: Jakob 950303
*
* Thanks to Glindor for assistance.
*
* Updatet:
*
*/

#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include "defs.h"
#include <macros.h>

object target;

void
create_object()
{
    seteuid(getuid());
    set_no_show();
    set_name("_the_paint_subloc");
    add_prop(OBJ_M_NO_DROP, 1);
    set_alarm(250.0, 0.0, "remove_paint");
}

void
init()
{
    target = ENV(TO);
    target->add_subloc("black_paint", TO);
}

void
remove_paint()
{
    target->remove_subloc("black_paint", TO);
    target->catch_msg("The black paint wears off a bit. \n");
    TO->remove_object();
}

string
show_subloc(string subloc, object on, object for_obj)
{
    string data;
    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    if (for_obj != on)
        data = (capitalize(ENV(TO)->query_pronoun()) + " is painted black! \n");
    else
        data = ("You are painted black!\n");

    return data;
}
