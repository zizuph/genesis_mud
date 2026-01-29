/*
 * /d/Gondor/anorien/nimrais/trolls/cave1.c
 *
 * Coder: Unknown
 *
 * Modification log:
 *
 * Gwyneth, 10/02/02: Modernized, cleaned up the code and changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/std/room";

#include "/d/Gondor/defs.h"

#include <macros.h>
#include <stdproperties.h>

object gTroll;

int blocked();
void reset_room();

void
create_gondor()
{
    set_short("A tunnel in a hill-troll lair");
    set_long("You stand in a dark tunnel in the lair of some " +
        "hill-trolls. A foul reek comes from a larger cave to the east, " +
        "where you think you can see a little light. The tunnel turns " +
        "slightly to the southwest here, and it seems a bit narrower in " +
        "that direction.\n");

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(NIMRAIS_DIR + "trolls/cave2", "southwest", &blocked());
    add_exit(NIMRAIS_DIR + "trolls/livcave", "east");

    add_item(({ "ground", "floor", "cavefloor" }), "You find bones and " +
        "broken bottles littered on the floor of the cave.\n");
    add_item("bones", "The bones are of varying size, some of them clearly " +
        "coming from small animals like rabbits, while others look like " +
        "human bones!\n");
    add_item("bottles", "There are empty and broken bottles here, and on a " +
        "few of them you manage to read the label: Dorwinion, 3012.\n");
    remove_prop(ROOM_I_LIGHT);
    reset_room();
}

int
blocked()
{
    object troll = present("troll", TO);

    if(objectp(troll) && CAN_SEE(troll, TP) && !TP->query_npc())
    {
        write("The " + troll->query_nonmet_name() + " blocks your way!\n");
        say(QCTNAME(this_player()) + " tries to leave, but the " + 
            troll->query_nonmet_name() + " stops " + TP->query_objective() +
            ".\n", TP);
        return 1;
    }

    return 0;
}

void
reset_room()
{
    ::reset_room();
    gTroll = clone_npc(gTroll, NPC_DIR + "hilltroll2");
}

