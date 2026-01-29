/*
 * The note for the guards in the Fen Hollen Porter quest.
 *
 * /d/Gondor/minas/obj/pippin_note.c
 *
 * Alto, 27 April 2001
 *
 */
#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

#define INNER_MINAS "/d/Gondor/minas"

public void
destruct_me() 
{
    object room;
    if (living(room = environment()))
	     room = environment(room);
      tell_room(room, "The missive blows away in a sudden gust of wind.\n");
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
    set_short("small missive");
    set_name("missive");
    add_name("paper");
    add_name("note");
    set_adj("small");
    add_name("_stable_quest_note_");
    add_prop(OBJ_I_NO_DROP, do_destruct);

    set_long("The small missive reads: \n\n\n"
        + "\tPlease admit the bearer of this missive\n"
        + "\tthrough the Seventh Gate. \n\n\n"
        + "\t\t\tIn Service to the Steward,\n\n"
        + "\t\t\tFergil, Porter of the Fen Hollen\n\n\n");

    add_prop(OBJ_I_VOLUME,      100);
    add_prop(OBJ_I_WEIGHT,      100);

}



