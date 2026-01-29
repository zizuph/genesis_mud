/* The Grunts Bulletin Board room. Recoded on 21/08/95 by Tulix III. */

inherit "/std/room";

#include "default.h"
#include "../guild.h"

public void
create_room()
{
    object board;

    set_short("Grunts Bulletin Board room");
    set_long(
        "   The cave in which you are standing in now is remarkable " +
        "only for its smell, and the fact that there is a bulletin board " +
        "on which your can write messages. Please note that this board " +
        "is intended for matters that are concerned with the guild. " +
        "Feel free to leave a message here for the benefit of " +
        "everyone else. There is an exit here to take you to the common " +
        "board.\n\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_exit(THIS_DIR + "main", "east", 0, 1);
    add_exit(THIS_DIR + "common", "common", 0);

    board = clone_object(GRUNTS_DIR + "obj/grunts_board");
    board-> move(this_object());


    add_item(({"walls","wall"}),
        "The walls are cold, and damp to touch. It seems to be volcanic " +
        "rock that these caves are made of. Pretty hard stuff it is, too.\n");
    
    add_item(({"roof","ceiling"}),
        "What little you can see above you suggests that the roof is made " +
        "of the same rock as the walls, volcanic rock. At least you can " +
        "be fairly sure the roof won't be falling down, as volcanic rock " +
        "is pretty tough stuff.\n");

    add_item(({"floor","ground"}),
        "The floor on which you are standing seems very firm, and is made " +
        "of volcanic rock.\n");

}
