/* The entrance to the Emerald cave system. Recoded 25/03/97, Tulix III */

inherit "/std/room";
 
#include "default.h";
 
public void
create_room() 
{
    object ashes;
    
    add_prop(ROOM_I_INSIDE, 1);
    
    set_noshow_obvious(1);
    
    set_short("The mouth of a large cave.\n" +
        "There are four obvious exits: north, west, east, southwest");
    
    set_long("   " +
        "You are in the mouth of a large cave. There is light coming " +
        "from the south, but all the other exits look ominously dark. " +
        "There are the remains of a fire in the middle of the cave, " +
        "but who would want to light a fire here? Its not the most " +
        "obvious place to hold a barbeque! Mind you, this cave is " +
        "a good place to escape the rain if you have not got a coat.\n\n" +
        "There are four obvious exits: north, west, east, southwest.\n");
 
    add_item("lichen", 
        "There is lichen growing on the volcanic rock. It is very fragile, " +
        "and crumbles to dust when you touch it.\n");
    add_item(({"walls","wall"}), 
        "The walls are cold, and damp to touch. It seems to be volcanic " +
        "rock that these caves are made of. Pretty hard stuff it is, too.\n" +
        "There is some lichen growing on the wall.\n");
    add_item(({"roof","ceiling"}),
        "What little you can see above you suggests that the roof is made " +
        "of the same rock as the walls, volcanic rock. At least you can " +
        "be fairly sure the roof won't be falling down, as volcanic rock " +
        "is pretty tough stuff. There seems to be some traces of soot " +
        "on the roof of the cave, probably from the fire that was here.\n");
    add_item(({"floor","ground"}),
        "The floor on which you are standing seems very firm, and is made " +
        "of volcanic rock. It seems there is a way down through the ashes.\n");
    add_item("soot", "It looks like plain old soot. It is too high up to " +
        "examine closely.\n");

    add_exit("/d/Emerald/mountains/mtblack/road04", "southwest", 0, 1);
    add_exit(THIS_DIR + "cave7a", "north", 0, 1);
    add_exit(THIS_DIR + "cave1a", "west", 0, 1);
    add_exit(THIS_DIR + "cave2a", "east", 0, 1);
    add_exit(GRUNTS_DIR+ "room/secret_passage1b", "down", "@@down_we_go", 1);

    ashes=clone_object( CAVE_DIR + "obj/ashes");
    ashes->move(this_object());
}

public int
down_we_go()
{
    write("You tunnel your way down through the ashes.\n");
    return 0;
}

