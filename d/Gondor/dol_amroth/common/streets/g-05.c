/*
 * common/streets/g-05.c
 *
 * By Skippern 20(c)01
 *
 * A street in common district
 */
#include "../../defs.h"

inherit DOL_STD + "city.c";
inherit "/lib/unique";

void
delay()
{
    clone_object(DOL_NPC + "citizen1")->move(DOL_TRADE + "streets/o-09");
    clone_object(DOL_NPC + "assassin")->move(DOL_SEWER + "g-05");
}

public void
create_dol_amroth()
{
    set_short("a dirty street");
    set_extralines("The street goes right by the waterfront.");
    set_lastline("A pier goes out to the north.");

    set_no_of_lamps(2);
    set_alarm(5.0, 0.0, &delay());
    clone_object(DOL_NPC + "hagworth")->move(this_object());
    reset_room();

    bay_tells();
    street_tells();

    add_exit(DOL_COMMON + "piers/h-05", "east", 0, 1);
    add_exit(DOL_COMMON + "streets/g-06", "south", 0, 1);
    add_exit(DOL_COMMON + "piers/g-04", "north", 0, 1);
    add_exit(DOL_CRAFT + "piers/f-04", "northwest", 0, 1);
    set_grate("down", DOL_SEWER + "g-05");
}

void
reset_room()
{
    object ob;
    ::reset_room();
    ob = clone_unique(DOL_NPC + "citizen1", 10);
    ob->move(this_object());
    ob = clone_unique(DOL_NPC + "hagworth", 1);
    ob->move(this_object());
    ob = clone_unique(DOL_NPC + "citizen2", 3);
    ob->move(this_object());
}

