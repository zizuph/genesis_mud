/*
 * IGARD_QUEST_OBJ + furn2_clue.c
 *
 * Clue to visit igard furnaces.
 *
 * Last modified by Alto, 04 December 2001
 *
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../../igard_defs.h"

public void
destruct_me() 
{
    object room;
    if (living(room = environment()))
	     room = environment(room);
      tell_room(room, "The work order blows away in a sudden gust of wind.\n");
      remove_object();
}

public void
do_destruct() 
{
    if (query_verb() == "drop")
	set_alarm(2.0, 0.0, destruct_me);
    return 0;
}

void
create_object()
{
   set_name("order");
   set_adj("work");
   set_short("work order");
    set_pshort("work orders");
    add_name("_igard_furn2_clue");
    add_prop(OBJ_I_NO_DROP, do_destruct);

    set_long("The work order reads: \n\n\n"
        + "\tGet to the southeast furnace double time!\n"
        + "\tIt needs service immediately! \n\n\n"
        + "\t\t\tFor the White Hand,\n\n"
        + "\t\t\tGrnschk, Sergeant.\n\n"
        + "\t\t\tP.S. The one at the green pebbles, idiot!\n\n");

    add_prop(OBJ_I_VOLUME,      100);
    add_prop(OBJ_I_WEIGHT,      100);

}
