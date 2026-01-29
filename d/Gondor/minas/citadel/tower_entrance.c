/*
 *  /d/Gondor/minas/citadel/tower_entrance.c
 *
 *  Doors before the White Tower of Ecthelion
 *
 *  Original code by Elessar
 *
 *  Last modified by Alto, 20 April 2001
 *    Added new room descriptions, room tells, and brushed up code.
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/tell.c"

#define INNER_MINAS "/d/Gondor/minas"

object door, guard1, guard2;

public void
create_gondor()
{
    set_short("The doors of the White Tower");
    set_long("You find yourself at the doors of the great hall beneath "
        + "the gleaming tower. If you have legitimate business with the "
        + "Lord of the city, you have only to ask to be admitted. If "
        + "your business is not worthy of the attention of the Steward, it "
        + "would be better to return east to the Court of the Fountain.\n");

    add_exit(INNER_MINAS + "/citadel/fountain", "east", 0, 0);

    door = clone_object(INNER_MINAS + "/obj/tower_door_out.c");
    door->move(TO);

    add_item(({"court of the fountain", "courtyard", "plaza"}), "Before "
        + "the White Tower stands a courtyard.  It is grand, and yet "
        + "sad in a distant way.\n");
    add_item(({"tower", "tower of ecthelion", "white tower"}), "The White "
        + "Tower of Ecthelion spikes fifty fathoms high into the sky. "
        + "It looks as though it is made "
        + "of pearl and silver, and its pinnacle glitters as if "
        + "wrought of crystals.\n");
    add_item(({"doors", "timbers", "plates"}), "Two massive doors made of wood "
        + "banded in great plates of iron. These doors have never been "
        + "broken, and gazing upon their might you wonder at the "
        + "kind of strength that would be required to even scratch "
        + "the huge timbers.\n");
    add_item(({"door"}), "Do you mean the great wooden door?\n");
    add_item(({"pinnacle"}), "With a sense of vertigo, your eyes rise "
        + "to the heights of the White Tower. Just before you look "
        + "away, you think you notice a strange flash of light from "
        + "inside its highest east-facing window.\n");
    add_item(({"window"}), "There are many windows about the courtyard. "
        + "The only one that catches your interest is the highest window "
        + "in the Tower of Ecthelion.\n");
    add_item(({"highest window"}), "There it is again, a strange flash "
        + "of bright light. Who knows what secrets are to be found in "
        + "the ancient rooms above?\n");
    add_item(({"mountain", "mount mindolluin"}), "Rising behind the "
        + "tower is the dark mass of Mount Mindolluin. The deep "
        + "purple shadows of its high glens and its tall face "
        + "are so large that you cannot take it all in at a single "
        + "glance.\n");
    add_item(({"glens", "face"}), "The mountain towers so huge about "
        + "the courtyard that you get dizzy looking up at it.\n");
    add_item(({"sky"}), "The sky is dominated by the tower rising before "
        + "you and the massive mountain behind and above it.\n");
    add_item(({"dove", "doves"}), "Blue-grey mourning doves can be seen "
        + "fluttering about the plaza.\n");
    add_item(({"banner", "banner of the stewards"}), "Far above you "
        + "the great banner of the Stewards is raised atop the pinnacle "
        + "of the tower. It floats a thousand feet above the plain "
        + "before the city.\n");
    add_item(({"plain"}), "The large open land before the city cannot "
        + "be seen over the encircling walls. A better view might be "
        + "gained on the battlement atop the great stone bastion east "
        + "of here.\n");
    add_item(({"wall", "walls"}), "This wall completely encloses the "
        + "Citadel. The dull murmer of city life rises from beyond it.\n");
    add_item(({"battlement", "bastion", "stairs"}), "Partly from the primeval "
        + "shaping of the hill, partly from the mighty craft and labour of "
        + "old, a towering bastion of stone stands up from the First Gate, "
        + "rising up even to the level of this, the Seventh Circle. It is "
        + "crowned with a great Battlement that can be reached by climbing "
        + "a long flight of stairs.\n");
    add_item(({"hall", "great hall"}), "It is on the other side of the "
        + "door and hence cannot be seen from here.\n");

    add_prop(ROOM_I_INSIDE, 0);

    set_tell_time(120);

    add_tell("A dove flutters across the courtyard.\n");
    add_tell("Dark clouds drift across the sky from the east.\n");
    add_tell("Crisp mountain wind whispers through the plaza.\n");
    add_tell("Thunder rumbles in the distance.\n");
    add_tell("The low sounds of Minas Tirith rise from below the "
        + "encircling walls.\n");
    add_tell("The banner of the Stewards snaps in the wind high "
        + "above.\n");
    add_tell("Marching feet can be heard from somewhere nearby.\n");
    add_tell("Lightning flashes in the distant east.\n");
    add_tell("A few raindrops strike your shoulders and head.\n");

    reset_room();
}


/*
 * This function enables the random room tells.
 */

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
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



