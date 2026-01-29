/* A part of the Emerald cave system. Recoded 25/03/97, Tulix III */

inherit "/d/Emerald/std/room";

#include "default.h"
#include "/d/Emerald/mountains/mtblack/cave/lichen.h"

/* Global variables */
object npc, npc2, npc3;

/* Prototype function */
public void reset_room();

public void 
create_emerald_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    set_short("A dark cave");    
    set_long("   "+
        "This cave is a dead end. It looks like the abode of some Ogres. " +
        "It seems that these caves are absolutely crawling with them. " +
        "Its almost the equivalent of an Ogre town. Of course Ogres are " +
        "not the most social creatures, so an Ogre town is a bit of a " + 
        "strange concept.\n\n");

    add_item("lichen", 
        "There is lichen growing on the volcanic rock. It is very fragile, " +
        "and cumbles to dust when you touch it.\n");
    add_item(({"walls","wall"}), 
        "The walls are cold, and damp to touch. It seems to be volcanic " +
        "rock that these caves are made of. Pretty hard stuff it is, too.\n" +
        "There is some lichen growing on the wall.\n");
    add_item(({"roof","ceiling"}), 
        "What little you can see above you suggests that the roof is made " +
        "of the same rock as the walls, volcanic rock. At least you can " +
        "be fairly sure the roof won't be falling down, as volcanic rock " +
        "is pretty tough stuff.\n");
    add_item(({"floor","ground"}),
        "The floor on which you are standing seems very firm, and is made " +
        "of volcanic rock. There is some lichen growing on the floor.\n");
    
    add_exit(THIS_DIR+"cave18c", "south", 0, 1);
    
    reset_room();
}

public void
reset_room()
{
    if (!objectp(npc))
    {
        npc=clone_object(CAVE_DIR + "npc/nasty_ogre");
        npc->arm_me();
        npc->move_living("into a cave", this_object(), 1, 1);
    }
    
    if (!objectp(npc2))
    {
        npc2=clone_object(CAVE_DIR + "npc/large_ogre");
        npc2->arm_me();
        npc2->move_living("into a cave", this_object(), 1, 1);
    }
    
    if (!objectp(npc3))
    {
        npc3=clone_object(CAVE_DIR + "npc/large_ogre");
        npc3->arm_me();
        npc3->move_living("into a cave", this_object(), 1, 1);
    }

    return;
}
