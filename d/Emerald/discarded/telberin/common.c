/*
 * The common board of Telberin
 * By Finwe 
 * January 1997
 */

#include "/d/Emerald/defs.h"
#include "default.h"
#include <stdproperties.h>
inherit "/std/room";
 
/* Prototype function */
public void load_board();
 
void
create_room()
{
    set_short("Common Board of Telberin");
    set_long("   This room contains the common board. Notes on " +
        "it are read by all players of the game. It contains " +
        "general annoucements for players. There is a notice " +
        "posted beside the board.\n");

    add_prop(ROOM_I_INSIDE, 1);
         add_exit(THIS_DIR + "adv_foyer", "back", 0);
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
