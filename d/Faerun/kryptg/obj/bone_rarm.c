/*
 * Part of insect quest
 * -- Finwe August 2007
 */

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>

inherit "/std/object";
inherit "/cmd/std/command_driver";
inherit "/lib/keep";

#define ADJ1        "dwarven"
#define ADJ2        "right-arm"
#define OBJ_NAME    "bone"

public void do_destruct();

void create_object()
{
    set_name(OBJ_NAME);
    add_name(RARM);
    set_adj(ADJ1);
    set_adj(ADJ2);
    set_short(ADJ1 + " " + ADJ2 + " " + OBJ_NAME);
    set_long("This is a " + query_short() + ". It looks like it was ripped from the body of a dwarven corpse.\n");

    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 2);
    add_prop(OBJ_M_NO_STEAL, 0);
    add_prop(OBJ_I_NO_DROP, do_destruct);

    set_keep(1);
}

public void
destruct_me()
{
    object room;
    if (living(room = environment()))
        room = environment(room);
    tell_room(room, "The " + query_short() + " crumbles to dust, then blows away.\n");
    remove_object();
}

// we dont want these littering the realm, so they will self-destruct
// after 2 min if dropped.
public void do_destruct()
{
    if (query_verb() == "drop")
        set_alarm(120.0, 0.0, destruct_me);
    return 0;
}
