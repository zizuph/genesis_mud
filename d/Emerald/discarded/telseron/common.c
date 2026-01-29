/* 
 * This room contains a common board for the vampires to look at.
 * It was originally recoded on 21/08/95 by Tulix III and was
 * modified by Finwe for the vamps guild in August 1996
 */

#include "/d/Emerald/defs.h"
#include <stdproperties.h>
inherit "/std/room";
 
/* Prototype function */
public void load_board();
 
void
create_room()
{
    set_short("Telseron common board room");
    set_long(
        "This room contains the common board. Notes on it are read " +
        "by all players of the game. It contains general annoucements " +
        "for players. There is a notice posted beside the board.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_exit("board", "back", 0);
    add_prop(ROOM_I_NO_STEAL, 1);
    add_prop(ROOM_I_NO_TELEPORT, 1);
    add_prop(ROOM_I_NO_ATTACK, 1);
 
    load_board();
 
    add_item(("notice"),
    	"The notice reads:\n" +
        "Only immortals can write on this board at the moment. " +
        "The reason for this is that morons used to post messages " +
        "which were a waste of space, and not genuinely important.\n" +
        "Until further notice, mortals will not be able to post " +
	"notes here.\n");
 
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
