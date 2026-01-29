/* A part of the Emerald cave system. Recoded 25/03/97, Tulix III */

inherit "/std/room";

#include "default.h"
#include "/d/Emerald/mountains/mtblack/cave/lichen.h"

/* Global variables */
object npc, npc2;

/* Prototype function */
public void reset_room();

public void 
create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    set_short("This is a cold, wet, cave");    
    set_long("   " +
        "This part of the cave has puddles on the floor everywhere " +
        "that you look. There is the sound of water dripping down to " +
        "the west, and quite a lot of it, from what you can hear. " +
        "Although there is no ice here, there really ought to be, " +
         "considering how cold it is.\n\n");

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
    add_item(({"puddle","puddles"}),
        "You see several large puddles. They seem to contain lots " +
        "of cold, and very wet water.\n");

    add_exit(THIS_DIR+"cave5b", "west", 0, 1);
    add_exit(THIS_DIR+"cave7b", "east", 0, 1);
    add_exit(THIS_DIR+"cave9b", "northwest", 0, 1);
    
    reset_room();
}

public void
reset_room()
{
    if (!objectp(npc))
    {
        npc=clone_object(CAVE_DIR + "npc/kobold");
        npc->arm_me();
        npc->move_living("into a cave", this_object(), 1, 1);
    }
    
    if (!objectp(npc2))
    {
        npc2=clone_object(CAVE_DIR + "npc/kobold");
        npc2->arm_me();
        npc2->move_living("into a cave", this_object(), 1, 1);
    }

    return;
}
