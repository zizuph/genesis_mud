/* -*- Mode: C -*-
 *
 * trade/streets/o-09.c
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
    clone_object(DOL_NPC + "citizen1")->move(DOL_OTHER + "gates/v-15");
    clone_object("/d/Gondor/common/npc/rat")->move(DOL_SEWER + "j-06");
}

public void
create_dol_amroth()
{
    set_short("a dirty street");
    set_extralines("The street goes right by the waterfront.");
    set_lastline("To the southwest a hill rises, and to the east some " +
        "finer houses rises.");

    set_no_of_lamps(2);
    set_alarm(5.0, 0.0, &delay());
    reset_room();

    bay_tells();
    street_tells();
    add_tell("Waves splashes against the road foundations.\n");

    add_exit(DOL_OTHER + "streets/n-08", "northwest", 0, 1);
    add_exit(DOL_TRADE + "streets/o-10", "south", 0, 1);
    add_exit(DOL_TRADE + "piers/p-08", "northeast", 0, 1);
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
    ob = clone_unique(DOL_NPC + "citizen3", 3);
    ob->move(this_object());
}


