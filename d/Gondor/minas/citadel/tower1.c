/*
 *  /d/Gondor/minas/citadel/tower1.c
 *
 *  Just inside the White Tower of Ecthelion
 *
 *  Alto, 20 April 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

#define INNER_MINAS "/d/Gondor/minas"

object door, guard1, guard2;

public void
create_gondor()
{
    set_short("Inside the doors of the White Tower");
    set_long("This place opens into a great hall to the west. From "
        + "here can be seen deep windows in the wide aisles on either "
        + "side, beyond rows of tall pillars that uphold the roof. "
        + "At the far end there is a great dais.\n");

    add_exit(INNER_MINAS + "/citadel/tower2", "west", 0, 0);

    door = clone_object(INNER_MINAS + "/obj/tower_door_in.c");
    door->move(TO);

    add_item(({"hall", "great hall", "tower", "white tower", "entrance"}), 
        "From what you can see, "
        + "standing here in the entrance, it is vast. For a better view, "
        + "however, you will need to walk further west.\n");
    add_item(({"windows", "walls"}), "It is hard to make out any "
        + "details about "
        + "them from here, but they certainly look huge.\n");
    add_item(({"north wall", "south wall"}), "The walls you can see from "
        + "here line the great hall to the north and the south.\n");
    add_item(({"aisles"}), "Beyond the great pillars, two wide aisles "
        + "line the north and south facing walls of the great hall.\n");
    add_item(({"rows", "pillars", "tall pillars"}), "Mighty pillars "
        + "stand in two rows running from this end of the hall down "
        + "to the dais at the far end.\n");
    add_item(({"roof"}), "It is hard to see clearly from here, but it "
        + "appears very colourful. The details would be easier to see "
        + "further west into the hall.\n");
    add_item(({"dais", "steps", "throne", "apex"}), "At the far end "
        + "of the hall is what "
        + "appears to be a dais of many steps. There seems to be a "
        + "throne at its apex, but it is difficult to make out "
        + "any of the details from this far away.\n");
    add_item(({"doors", "timbers", "plates"}), "Two massive doors made of wood "
        + "banded in great plates of iron. These doors have never been "
        + "broken, and gazing upon their might you wonder at the "
        + "kind of strength that would be required to even scratch "
        + "the huge timbers.\n");
    add_item(({"door"}), "Do you mean the great wooden door?\n");


    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_HIDE, -1);

    reset_room();
}


public void
reset_room() 
{
    if (!guard1) 
        {
        guard1 = clone_object(INNER_MINAS + "/npc/citadel_e_guard");
        guard1->move(TO);
        }

    if (!guard2) 
        {
        guard2 = clone_object(INNER_MINAS + "/npc/citadel_e_guard");
        guard2->move(TO);
        }
}



