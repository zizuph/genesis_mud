/*
 * Missive from the prisoner in the Igard quest.
 *
 * IGARD_QUEST_OBJ + "prisoner_missive.c"
 *
 * Alto, 26 December 2001
 *
 */
#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

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
    add_name("_igard_prisoner_missive_");
    add_prop(OBJ_I_NO_DROP, do_destruct);

    set_long("The small missive reads: \n\n\n"
        + "\tTo his Greatness, Saruman the Wise,\n"
        + "\tMaster of Isengard and Lord of the West. \n\n"
        + "\tForgive the brevity of this note, Master, for time is of the\n"
        + "\tessence. The Golden Hall will be ripe for plucking on the night\n"
        + "\tthe crescent moon wanes. Soon we shall dance upon the bones\n"
        + "\tof Theoden and his curs!\n\n"
        + "\t\t\tYour humble servant,\n\n"
        + "\t\t\tGrima\n\n\n");

    add_prop(OBJ_I_VOLUME,      100);
    add_prop(OBJ_I_WEIGHT,      100);

}



