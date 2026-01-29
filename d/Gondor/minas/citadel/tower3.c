/*
 *  /d/Gondor/minas/citadel/tower3.c
 *
 *  Hall of the White Tower of Ecthelion: Dais
 *
 *  Alto, 20 April 2001
 *  Finwe April 2019: Fixed ring quest stage time so it calls rq_stage() 
 *    instead of rq_stage_stored.
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/open/room_chairs/room_chairs";


#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/open/room_chairs/room_chairs.h"
#include "/d/Gondor/common/lib/clock.h"

#define INNER_MINAS "/d/Gondor/minas"

#define   CHAIR2_NAME     "stone chair"
#define   CHAIR_NAME      "throne"

public void    create_gondor();
public void    init();
public void    leave_inv(object ob, object dest);
public string  look_at(string arg);     /* VBFC for chairs */
// int            rq_stage_stored = rq_stage();

object door;
static object Steward;


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
    set_short("Dais in the hall of the White Tower");
    set_long("You stand before the great dais of the White Tower of "
        + "Ecthelion. Upon the dais is set a high throne under a canopy "
        + "of marble shaped like a crowned helm. There are deep windows in "
        + "the wide aisles at either side, beyond rows of tall pillars "
        + "that uphold the roof. No hangings nor storied webs, nor "
        + "any things of woven stuff or of wood, are to be seen in "
        + "this long solemn hall; but between the pillars there stands "
        + "a silent company of tall images graven in cold stone. "
        + "At the foot of the dais, upon the lowest step, there is a "
        + "stone chair, black and unadorned.\n");

    add_exit(INNER_MINAS + "/citadel/tower2", "east", check_sitting, 1);

    door = clone_object(INNER_MINAS + "/obj/throne_door_hall.c");
    door->move(TO);


    add_chair(CHAIR2_NAME,
     "[down] [in] / [on] [the] 'chair'", 1, "in");

    add_chair(CHAIR_NAME,
     "[down] [in] / [on] [the] 'throne'", 1, "in");

    add_item( ({ "throne", "high throne" }), &look_at(CHAIR_NAME) );

    add_item( ({ "chair", "lowest step", "stone chair", "black chair" }),
        &look_at(CHAIR2_NAME) );

    add_item(({"hall", "great hall", "tower", "white tower"}), "This is "
        + "a vast hall made entirely of native stone. Your footsteps ring "
        + "upon the stone floor and echo off the stone walls. The tall "
        + "statues between the pillars seem to stare down upon you in "
        + "disapproval of the noise.\n");
    add_item(({"stone", "native stone", "marble"}), "There are "
        + "two primary kinds "
        + "of stone from which the objects in the great hall are made. One "
        + "is the kind of gleaming white rock such as the seven walls of "
        + "the city are made from. The other is a shiny black marble. "
        + "Both are quarried from the foothills of Mount Mindolluin.\n");
    add_item(({"stone floor", "floor"}), "The floor is made from the "
        + "same black marble as the great monolithic pillars. "
        + "It is so highly polished that it reflects back the light of "
        + "the hall.\n");
    add_item(({"statue", "statues", "images", "company", "statue"}), "The "
        + "statues between the "
        + "great pillars comprise an avenue of kings long dead. Near the "
        + "dais are three statues you recognize as Elendil, Anarion and "
        + "Isildur, the first kings of Gondor.\n");
    add_item(({"elendil", "statue of elendil"}), "This is a likeness "
        + "of Elendil son of "
        + "Amandil, first High King of Arnor and Gondor. A great "
        + "mariner, he gathered his sons Isildur and Anarion from "
        + "Numenor and was blown to Middle Earth in the wake of "
        + "tempest. There is a mighty longsword at his side.\n");
    add_item(({"longsword", "longsword on statue", "elendil's longsword"}),
        "A stone likeness of the famous blade Narsil hangs from "
        + "the side of the statue of Elendil. It broke long ago beneath its "
        + "master when he fell with the elf king Gil-galad "
        + "in combat with Sauron on the slopes of Orodruin. Legend "
        + "speaks that it will one day be forged anew and an heir of the "
        + "House of Elendil will come forth to contest the Black Lord "
        + "of Mordor once again.\n");
    add_item(({"anarion", "statue of anarion"}), "Opposite the statue of "
        + "Elendil is the sculpted image of King Anarion, who with his "
        + "brother Isildur was the second king of Gondor. He died in "
        + "Mordor during the Last Alliance of Elves and Men when struck "
        + "by a stone hurled from the Barad-dur.\n");
    add_item(({"isildur", "statue of isildur"}), "Beside the statue "
        + "of Anarion is the sculpted image of his brother, King Isildur. "
        + "It was Isildur who recovered a sapling of Nimloth the Fair, "
        + "later planting a seedling in "
        + "memory of his brother. Following the defeat of Sauron, Isildur "
        + "ruled Gondor for two years, but later died under mysterious "
        + "circumstances as he travelled north to assume the rule of "
        + "Arnor.\n");
    add_item(({"windows", "walls", "north wall", "south wall"}), "The "
        + "windows are forty feet tall "
        + "and ten feet wide. They are set into the north and south walls "
        + "in such a way that every two pillars have a window between "
        + "them. They are cut deep, and ascend at such a steep angle that "
        + "you are unable to see outside through them.\n");
    add_item(({"aisles"}), "Beyond the great pillars, two wide aisles "
        + "line the north and south facing walls of the great hall.\n");
    add_item(({"rows", "pillars", "tall pillars", "monoliths", "pillar"}), 
        "Mighty pillars stand in two rows running the length of "
        + "the hall from west "
        + "to east. Monoliths of black marble, they rise to great capitals "
        + "carved in many strange figures of beasts and leaves. Between "
        + "each two pillars is a tall image carved in stone.\n");
    add_item(({"capital", "capitals", "figures", "beasts", "leaves"}), 
        "Great capitals can be seen at the top of each pillar where it "
        + "meets the roof. Each is elegantly sculpted with images of "
        + "beasts and leaves.\n");
    add_item(({"roof", "vaulting", "traceries"}), "Far above in shadow, "
        + "the wide vaulting "
        + "gleams with dull gold, inset with flowing traceries of many "
        + "colours.\n");
    add_item(({"dais", "steps", "lowest step"}), "Before you, upon a "
        + "dais of many steps, is set a high throne under a canopy of "
        + "marble shaped like a crowned helm; behind it is carved upon "
        + "the west wall, and set with gems, an image of a tree in flower. "
        + "At the foot of the dais, upon the lowest step, which is broad "
        + "and deep, there is a stone chair, black and unadorned.\n");
    add_item(({"canopy", "crowned helm", "helm"}), "A great canopy "
        + "of marble arches over the empty throne. It is fashioned after "
        + "the winged helm of the House of Elendil. Only the tower guard "
        + "wear such livery now.\n");
    add_item(({"tree", "gems", "west wall"}), "A great carving of a tree "
        + "in flower adorns the west wall. Its leaves are made of glittering "
        + "gems. It strikes you that this must be what the dead tree in the "
        + "Court of the Fountain must have looked like in its living years.\n");


    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_HIDE, -1);


    reset_room();
}

/*
 * Function name:   init
 * Description :    mask parent so we can call init_room_chairs()
 */
public void
init()
{
    ::init();
    init_room_chairs();  /* add chair verbs */
} /* init */

/*
 * Function name:   leave_inv
 * Description :    mask parent to be sure that departing players
 *             are removed from chair/sofa occupants
 */

public void
leave_inv(object ob, object dest)
{
    ::leave_inv(ob, dest);
    leave_inv_room_chairs(ob, dest);
} /* leave_inv */

/*
 * Function name:   look_at
 * Description :    VBFC to describe chair/sofa + occupants
 */

public string
look_at(string arg)
{
     if (arg == CHAIR_NAME)
    {
     return "This is where the King of "
        + "Gondor sat as he held court in the days after the fall of "
        + "Osgiliath. The throne has been vacant for many years, however. "
        + "Its empty grandeur paints a dash of sadness and loss against "
        + "the otherwise regal splendour of the great hall.\n" +
         sitting_on_chair(CHAIR_NAME, this_player(), 0);
    }

    if (arg == CHAIR2_NAME)
    { 
     return "On "
        + "the lowest step of the dais rests a small stone chair. Upon this "
        + "chair sat the Steward of the city whilst the King held court. "
        + "Although no King has walked this hall for many a year, the ruling "
        + "Steward remains here, at the foot of the dais, until the return "
        + "of the King.\n" +
         sitting_on_chair(CHAIR2_NAME, this_player(), 0);
    }
} /* look_at */



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
    Steward->remove_object();

    if (!query_igard_broken())
    {
       Steward = clone_npc(Steward, INNER_MINAS + "/npc/denethor_noquest");
    }

    if (query_igard_broken())
    {
       Steward = clone_npc(Steward, INNER_MINAS + "/npc/denethor");
    }
}



