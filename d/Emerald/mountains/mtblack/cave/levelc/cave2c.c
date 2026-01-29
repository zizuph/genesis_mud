/* A part of the Emerald cave system. Recoded 25/03/97, Tulix III */

inherit "/std/room";

#include "default.h"
#include "/d/Emerald/mountains/mtblack/cave/lichen.h"

/* Global variable */
object npc;

/* Prototype function */
public void reset_room();

public void 
create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    set_short("A dark cave");    
    set_long("   "+
        "This cave is a dead end. There is evidence of Ogre activity " +
        "in this cave, as you can see Ogre droppings in the corner: " +
        "how charming. It is probably that Ogres sleep here, too. " +
        "Of course, its the perfect place for an ogre, being " +
        "dark, damp and smelly, just like this cave.\n\n");

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
    add_item(({"droppings","ogre droppings"}),
        "Not quite as bad as Goblin droppings but still not very nice.\n");
    
    add_exit(THIS_DIR+"cave5c", "northeast", 0, 1);
    
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

    return;
}
