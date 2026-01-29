/*
 *  /d/Gondor/minas/houses/fen_hollen.c
 *
 *  Square of the Fen Hollen of Minas Tirith
 *
 *  Original code by Elessar (1992)
 *
 *  Last modified by Alto, 08 April 2001
 *       Added new room descriptions and NPC.
 * Finwe April 2019: Fixed ring quest stage time so it calls rq_stage() 
 *   instead of rq_stage_stored.
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/lib/clock.h"

#define INNER_MINAS "/d/Gondor/minas"

static object Porter;
//int    rq_stage_stored = rq_stage();


public int
query_igard_broken()
{
//    if (rq_stage_stored < RQ_LEFT_HENNETH_ANNUN)
    if (rq_stage() < RQ_LEFT_HENNETH_ANNUN)
    {
        return 0;
    }

    return 1;
}


public void
create_gondor()
{
    set_short("The Square of the Fen Hollen");
    set_long("This small square lies against the rearward wall of "
        + "the Sixth Circle. Set into the sixth wall is the Fen "
        + "Hollen, which means the Closed Door. It is so named "
        + "because it is kept ever shut save at times of funeral. "
        + "Only the Lord of the City may pass that way, or those "
        + "who bear the token of the tombs and tend the Houses "
        + "of the Dead. A little house stands beside the door.\n");

    add_exit(INNER_MINAS + "/w2crc6", "south", 0, 0);
    add_exit(INNER_MINAS + "/w3crc6", "northeast", 0, 0);

    clone_object(INNER_MINAS + "/obj/fenhollenout")->move(TO);

    add_item(({"square", "small square"}), "All is silent in this "
        + "somber place. Two large trees stand on either side of the "
        + "door, but no birds can be seen or heard in the branches. "
        + "Above the door rises the sixth wall, beyond which looms "
        + "the great bulk of Mount Mindolluin.\n");
    add_item(({"tree", "trees"}), "Which one, there are two of them. One to "
        + "the left of the Fen Hollen, the other to the right.\n");
    add_item(({"left tree"}), "This is a large fir tree. It symbolizes "
        + "the unwavering vigilance of the Lords of the city because "
        + "it remains green throughout the year.\n");
    add_item(({"right tree"}), "This is a large oak tree. It symbolizes "
        + "the unbroken passing of King to King and Steward to Steward "
        + "as its old leaves wither each Fall only to be reborn "
        + "upon its branches each Spring. The Men of Gondor hold that "
        + "while this tree lives, there is hope that a King will return "
        + "to rule again.\n");
    add_item(({"branches"}), "The branches of the trees form an arch "
        + "above the door. There are no birds to be seen in them.\n");
    add_item(({"sky", "clouds"}), "The walls and buildings block much of "
        + "the sky from view. The western sky, however, is dominated by "
        + "Mount Mindolluin. The eastern sky seems filled with black "
        + "clouds.\n");
    add_item(({"mountain", "mount mindolluin"}), "The city of Minas Tirith "
        + "is built upon its eastern knee. It dominates the western sky.\n");
    add_item(({"wall", "walls"}), "Which one? To the west is the "
        + "sixth wall. To the "
        + "east, the Citadel wall rises behind the buildings.\n");
    add_item(({"sixth wall"}), "This is the sixth wall of Minas Tirith. "
        + "Unlike the "
        + "outer walls, this wall forms a complete circle around the "
        + "inner parts of the city.  There is a door set into it.\n");
    add_item(({"citadel wall", "citadel"}), "To the east, the great "
        + "wall of the Citadel "
        + "can be seen rising above the Sixth Circle. The tall White Tower "
        + "rises from within.\n");
    add_item(({"tower", "white tower", "tower of ecthelion"}), "From here "
        + "only the pinnacle of the Tower of Ecthelion can be seen.\n");
    add_item(({"pinnacle", "banner"}), "From the top of the tower flies "
        + "the great banner of the Stewards.\n");
    add_item(({"ground", "flagstones"}), "The flagstones covering the "
        + "square are smooth and unblemished. Very little traffic passes "
        + "here, save in times of funeral.\n");
    add_item(({"houses of the dead"}), "They cannot be seen from here. "
        + "Only those who bear the token of the tombs may pass the Fen "
        + "Hollen and travel down the Rath Dinen to the pale domes and "
        + "empty halls of the Houses of the Dead.\n");
    add_item(({"house", "little house"}), "This little house stands beside "
        + "the door and functions to shelter the Porter in rough weather.\n");


    reset_room();

}

public void
reset_room()
{
    /* This room was coded incorrectly. It assumes that there will
     * be an Armageddon each day (as there was at the time it was
     * originally coded.) Code should *never* count on a specific
     * time for Armageddon cycle length. What happened, as a
     * result, is that if the Ringquest cycle did not happen to
     * be a the correct stage when the room was first loaded, then
     * the quest would remain unavailable for the duration of the
     * Armageddon uptime, which has (at time of this writing) become
     * more than two weeks. The simple fix is to reclone the npc
     * each room reset, thus performing a fresh check for the
     * Ringquest stage. - Gorboth
     */
     
//    rq_stage_stored = rq_stage();
    
    Porter->remove_object();

    if (!query_igard_broken())
    {
       Porter = clone_npc(Porter, INNER_MINAS + "/npc/porter_noquest");
    }

    if (query_igard_broken())
    {
       Porter = clone_npc(Porter, INNER_MINAS + "/npc/porter");
    }
}


    




