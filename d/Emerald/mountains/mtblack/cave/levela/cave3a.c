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
    set_short("Dead end cave");
    set_long("   " +
        "This cave has paintings on the wall. They are very " +
        "primitive, and look quite old. " +
        "There is a pile of straw in the corner, that looks as if " +
        "it has been slept on recently. It looks like you have " +
        "stumbled across the home of a caveman! " +
        "This is a dead end. The only exit you can see is back the way " +
        "that you came in.\n\n");

    add_item(({"walls","wall"}), 
        "The walls have simple scenes painted straight onto the volcanic " +
        "rock that these caves are made of. Pretty hard stuff it is, too.\n"
        );
    add_item(({"roof","ceiling"}), 
        "What little you can see above you suggests that the roof is made " +
        "of the same rock as the walls, volcanic rock. At least you can " +
        "be fairly sure the roof won't be falling down, as volcanic rock " +
        "is pretty tough stuff.\n");
    add_item(({"floor","ground"}),
        "The floor on which you are standing seems very firm, and is made " +
        "of volcanic rock. A pile of straw sits in the corner.\n");
    add_item(({"paintings","painting","scene","scenes"}),
        "These cave paintings show scenes of hunting and fishing. " +
        "It appears that these paintings are quite ancient.\n");
    add_item(({"straw","heap"}),
        "It is just a small heap of straw that is used as somewhere " +
        "to sleep by whoever lives in this cave.\n");

    add_exit(THIS_DIR+"cave4a", "east", 0, 1);
    reset_room();
}

public void
reset_room()
{
    if (!objectp(npc))
    {
        npc=clone_object(CAVE_DIR + "npc/caveman");
        npc->arm_me();
        npc->move_living("into a cave", this_object(), 1, 1);
    }

    return;
}
