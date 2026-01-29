/* A part of the Emerald cave system. Recoded 18/07/95, Tulix III */

inherit "/std/room";

#include "default.h"
#include "/d/Emerald/mountains/mtblack/cave/lichen.h"

/* Global variables */
object npc, npc2;

/* Prototype functions */
public void reset_room();
public string exa_quartz();

public void 
create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    set_short("A dark cave");    
    set_long("   "+
        "This cave is a dead end. It is a very different cave from the " +
        "rest, though. The smell of Ogres is the same, but the whole of " +
        "the northern wall of the cave is made of quartz. It glitters " +
        "silently in the light, and it is a shame that it is so dark " + 
        "down here, because it would be quite magnificent in the " +
        "sunlight.\n\n");

    add_item("lichen", 
        "There is lichen growing on the volcanic rock. It is very fragile, " +
        "and cumbles to dust when you touch it.\n");
    add_item(("walls"), 
        "The walls are cold, and damp to touch. It seems to be volcanic " +
        "rock that these caves are made of. Pretty hard stuff it is, too.\n" +
        "The northern wall appears to be made of quartz crystal.\n");
    add_item(({"roof","ceiling"}), 
        "What little you can see above you suggests that the roof is made " +
        "of the same rock as the walls, volcanic rock. At least you can " +
        "be fairly sure the roof won't be falling down, as volcanic rock " +
        "is pretty tough stuff.\n");
    add_item(({"floor","ground"}),
        "The floor on which you are standing seems very firm, and is made " +
        "of volcanic rock.\n");
    add_item(({"quartz","northern wall","north wall","quartz wall","wall",
        "crystal", "shield"}), "@@exa_quartz");

    add_exit(THIS_DIR+"cave22c", "south", 0, 1);
    
    reset_room();
}

public void
reset_room()
{
    if (!objectp(npc))
    {
        npc=clone_object(CAVE_DIR + "npc/large_ogre");
        npc->arm_me();
        npc->move_living("into a cave", this_object(), 1, 1);
    }
    
    if (!objectp(npc2))
    {
        npc2=clone_object(CAVE_DIR + "npc/nasty_ogre");
        npc2->arm_me();
        npc2->move_living("into a cave", this_object(), 1, 1);
    }

    return;
}

/* *************************************************************************
 * I don't want anyone with awareness less than 40 seeing anything in
 * the quartz. I paid a lot of money getting my awareness up to 50, so I 
 * don't see why everyone else shouldn't...
 */
public string
exa_quartz()
{
    if (this_player()->query_skill(SS_AWARENESS) >= 40)
    {
        return "You see the vague outline of a shield, " + 
               "that is somehow trapped in the rock!\n";
    }
    else
        return "Its looks nice, but you see nothing special in the quartz.\n";
}
