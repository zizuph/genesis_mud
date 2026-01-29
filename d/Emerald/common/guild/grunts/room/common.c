/* This room contains a common board for the Grunts to look at. */
/* Recoded on 21/08/95 by Tulix III.                            */

inherit "/std/room";

#include "default.h"

/* Prototype function */
public void load_board();

void
create_room()
{
    set_short("Grunts Common board room");
    set_long(
        "   This cave contains the common board, which is read by many of the " +
        "immortals as well as mortals. There is a large notice that is in " +
        "front of the board.\n\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_exit(THIS_DIR + "boardroom.c", "back", 0);
    add_prop(ROOM_I_NO_STEAL, 1);
    add_prop(ROOM_I_NO_TELEPORT, 1);
    add_prop(ROOM_I_NO_ATTACK, 1);

    load_board();

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

    add_item(("notice"),
        "The notice reads:\n" +
        "Only immortals can write on this board at the moment. " +
        "The reason for this is that morons used to put messages on here " +
        "that were just a waste of space, and not genuinely important.\n" +
        "Until further notice mortals will not be able to post notes here.\n");

}

public void
load_board()
{
    object bb;

    seteuid(getuid(this_object()));
    bb = clone_object("/d/Genesis/obj/board");
    bb->move(this_object());

    return;
}

