/*
 *  /d/Gondor/minas/gate7.c
 *
 *  Outside 7th Gate
 *
 *  Original code by Elessar (1992)
 *
 *  Subsequent modifications by Olorin (29-Jan-1997)
 *      Changed inheritance
 *  Last modified by Alto, 06 April 2001
 *      Added room tells and revised descriptions
 *
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";


#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/std/tell.c"
#include "/d/Gondor/defs.h"

#define INNER_MINAS "/d/Gondor/minas"

static object *Guard = allocate(2);
object door;

public void
create_gondor()
{
    set_short("outside the Gate of the Citadel in Minas Tirith");
    set_long("At last you come out of shadow to the Seventh Gate. "
        + "Before you is the smooth Citadel wall with its rooted "
        + "pillars. Above the gate is a great arch with the keystone "
        + "carven in the likeness of a crowned and kingly head. "
        + "Behind you, a long tunnel leads east to the Sixth Circle.\n");

    add_exit(INNER_MINAS + "/tcrc7", "east", 0, 1);

    door = clone_object(INNER_MINAS + "/obj/gate_seven_out.c");
    door->move(TO);

    /* These items are mostly unique to this room, so I will not
     * inherit the street_func file.
     */

    add_item(({"sky", "clouds"}), "The walls and buildings block much of "
        + "the sky from view. The western sky, however, is dominated by "
        + "Mount Mindolluin. The eastern sky seems filled with black "
        + "clouds.\n");
    add_item(({"mountain", "mount mindolluin"}), "The city of Minas Tirith "
        + "is built upon its eastern knee. It dominates the western sky.\n");
    add_item(({"street", "stones"}), "The street is cobbled with large "
        + "smooth stones. Although the streets of Minas Tirith have endured "
        + "millenia of use, they are well-maintained.\n");
    add_item(({"pillar", "pillars", "trees"}), "Many tall pillars line the "
        + "smooth surface of the Citadel wall. They are shaped like great "
        + "trees, each with seven stars above it.\n");
    add_item(({"star", "stars"}), "Above the tree-shaped pillars are "
        + "seven many-rayed stars.\n");
    add_item(({"arch", "great arch"}), "The Seventh Gate is contained "
        + "beneath a towering arch. The craft of its making has been "
        + "lost in with the passing of the ages.\n");
    add_item(({"keystone", "head", "apex"}), "At the apex of "
        + "the great arch is "
        + "the keystone. It is carved to resemble a kingly head. The "
        + "Men of Gondor look to this keystone in hopes that once again "
        + "an heir of Elendil will come forth to reclaim the throne.\n");
    add_item(({"citadel wall", "citadel"}), "Before you, the great "
        + "wall of the Citadel "
        + "can be seen standing tall and smooth. The tall White Tower "
        + "of Ecthelion rises from within.\n");
    add_item(({"tower", "white tower", "tower of ecthelion"}), "From here "
        + "only the pinnacle of the Tower of Ecthelion can be seen.\n");
    add_item(({"pinnacle", "banner"}), "From the top of the tower flies "
        + "the great banner of the Stewards.\n");
    add_item(({"gates", "seventh gate", "gate"}), "The two doors look "
        + "well-made and very strong. During the day, those "
        + "involved in the business of the Steward must pass through "
        + "them to enter or exit the Citadel. At night, however, the "
        + "Tower Guard do not permit passage.\n");
    add_item(({"tunnel", "sixth circle"}), "To the east, the tunnel "
        + "into the rock of the bastion.  It opens onto the Sixth "
        + "Circle of the city.\n");
    add_item(({"bastion"}), "A towering bastion of stone, formed in part "
        + "from the primeval shaping of the mountain, but also by the "
        + "labour of old. It stands from behind the Seventh Gate, its "
        + "edge sharp as a ship-keel. The bastion rises up from the lowest "
        + "circle even to the topmost. It is crowned by a battlement.\n");
    add_item(({"battlement"}), "The battlement is perched atop the huge "
        + "bastion of rock, facing east.  From here it looks as though "
        + "someone standing upon it would be able to look down from it "
        + "sheer down upon the First Gate seven hundred feet below.\n");


    add_tell("Dark clouds drift across the sky from the east.\n");
    add_tell("Thunder rumbles in the distance.\n");
    add_tell("The low sounds of Minas Tirith rise from below the "
        + "encircling walls.\n");
    add_tell("Wind whistles from the tunnel behind you.\n");
    add_tell("A few drops of rain spatter here and there on "
        + "the street.\n");
    add_tell("Marching feet can be heard beyond the wall.\n");


    /* The gate to the citadel is outside the tunnel. */
    add_prop(ROOM_I_INSIDE, 0);
    reset_room();
}

public void
reset_room()
{
    clone_npcs(Guard, INNER_MINAS + "/npc/g7_guard_out", -1.0);
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



