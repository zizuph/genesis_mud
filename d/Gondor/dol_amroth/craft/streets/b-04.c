/*
 * craft/streets/b-04.c
 *
 * By Skippern 20(c)01
 *
 * A pier where some military vessels dock.
 */
#include "../../defs.h"

inherit DOL_STD + "city.c";
inherit "/lib/unique";

void
delay()
{
    clone_object(DOL_NPC + "citizen1")->move(DOL_COMMON + "streets/g-05");
}

public void
create_dol_amroth()
{
    set_short("a dirty street");
    set_extralines("The street goes right by the waterfront.");
    set_lastline("the kkk took my baby away");

    set_no_of_lamps(1);
    set_alarm(5.0, 0.0, &delay());
    reset_room();

    pier_tells();
    bay_tells();
    street_tells();
    add_tell("Waves splashes against the road foundations.\n");

    add_exit(DOL_CRAFT + "piers/b-03", "north", 0, 1);
    add_exit(DOL_CRAFT + "streets/c-05", "southeast", 0, 1);
    add_exit(DOL_CRAFT + "streets/b-05", "south", 0, 1);
    clone_object(DOL_OBJ+"doors/b-04-door")->move(this_object());
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
