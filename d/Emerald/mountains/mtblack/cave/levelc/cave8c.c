/* A part of the Emerald cave system. Recoded 25/03/97, Tulix III */

inherit "/std/room";

#include "default.h"
#include "/d/Emerald/mountains/mtblack/cave/lichen.h"

/* Global variable */
object npc;

/* Prototype function */
public void reset_room();
public int east_block();

public void 
create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    set_short("Another dark cave");    
    set_long("   "+
        "This cave is not the most natural one you have ever seen. " +
        "It looks like it has been dug out, and the floor is too " +
        "flat and smooth to be formed by nature.\nA cave-in has apparently " +
        "closed off a tunnel that once led to the east.\n");

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
 
    add_item(({ "east", "tunnel", "cave-in" }),
        "It appears that a tunnel once led eastward, but a cave-in has " +
        "closed it.\n");

    add_exit(THIS_DIR + "cave7c", "west", 0, 1);
    add_exit("", "east", east_block, 0, 1);
    
    reset_room();
}

public void
reset_room()
{
    if (!objectp(npc))
    {
        npc=clone_object(CAVE_DIR + "npc/small_ogre");
        npc->arm_me();
        npc->move_living("into a cave", this_object(), 1, 1);
    }

    return;
}
 
public int 
east_block()
{
    write("A cave-in has blocked the way east.\n");
    return 1;
}
 
