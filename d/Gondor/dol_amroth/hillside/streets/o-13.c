/*
 * hillside/streets/o-13.c
 *
 * By Skippern 20(c)01
 *
 * A jatta jatta jatta
 */
#include "../../defs.h"

inherit DOL_STD + "city.c";
inherit "/lib/unique";

void
delay()
{
    clone_object(DOL_NPC + "citizen1")->move(DOL_CRAFT + "streets/b-04");
}

public void
create_dol_amroth()
{
    set_short("a paved road");
    set_extralines("The road goes uphill connecting the trade " +
		   "district with the fasionable mansions on the hillside.");
    set_lastline("The air is lighter here in the hight above the city.");

    set_sounds("The noise from the city is more distant and you feel " +
	       "a bit tranquile.");
    set_sound_detail("Birds sings from the trees in a nearby garden.");

    set_no_of_lamps(4);
    set_alarm(5.0, 0.0, &delay());
    reset_room();

    street_tells();

    add_exit(DOL_HILLS + "streets/n-13", "west", 0, 1);
    add_exit(DOL_TRADE + "streets/p-12", "northeast", 0, 1);
}

void
reset_room()
{
    object ob;
    ::reset_room();
    ob = clone_unique(DOL_NPC + "citizen1", 10);
    ob->move(this_object());
    ob = clone_unique(DOL_NPC + "citizen2", 3);
    ob->move(this_object());
}
