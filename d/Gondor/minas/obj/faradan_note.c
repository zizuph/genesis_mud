/*
 * The requisition for oats, to be given to Faradan the Farmer.
 *
 * /d/Gondor/minas/obj/faradan_note.c
 *
 * Alto, 29 April 2001
 *
 */
#pragma save_binary
#pragma strict_types


inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

#define INNER_MINAS "/d/Gondor/minas"

public void
destruct_me() 
{
    object room;
    if (living(room = environment()))
	     room = environment(room);
      tell_room(room, "The requisition blows away in a sudden gust of wind.\n");
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
    set_short("small requisition");
    set_name("requisition");
    add_name("paper");
    add_name("note");
    set_adj("small");
    add_name("_oat_quest_note_");
    add_prop(OBJ_I_NO_DROP, do_destruct);

    set_long("\n\nThe small requisition reads: \n\n\n"
        + "\tTo my dear brother Faradan,\n\n"
        + "\tPlease provide the bearer of this requisition\n"
        + "\tone bag of oats. \n\n\n"
        + "\t\tGratefully yours,\n\n"
        + "\t\tGeradan, Stablemaster of the Royal Stables\n\n\n");

    add_prop(OBJ_I_VOLUME,      100);
    add_prop(OBJ_I_WEIGHT,      100);

}

