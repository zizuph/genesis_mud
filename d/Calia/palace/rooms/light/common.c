/*
 * This room contains the common board for all players, mortals as well as
 * immortals. A player who enters this room can only go back to the room
 * he just left, so there are no normal exits from this room.
 *
 * Nick, 921223
 */

#pragma save_binary

inherit "/std/room";
#include <stdproperties.h>
#include "defs.h"

object this;

/*
 * Prototypes
 */
void    load_board();

void
create_room()
{
    set_short("In the common board room");
    set_long(
	"You are standing in the room where the common board is.  " +
	"It's common for all races in Genesis, immortals as well as " +
	"mortals.  " +
	"There is also a circular portal to the southwest.  " +
	"\n");

    add_exit(ROOM("light_trainroom"), "southwest", 0);

    add_item("portal",
	"The portal is encircled by a golden ring.  " +
	"It has a white sheet of light inside the ring that does not " +
	"shimmer.  " +
	"\n");

    add_prop(ROOM_I_INSIDE, 1); 
    add_prop(ROOM_M_NO_TELEPORT_TO, 1); 
    add_prop(ROOM_M_NO_STEAL, 1); 

    this = THIS;
    load_board();
}

void
load_board()
{
    seteuid(getuid(this));

    clone_object("/d/Genesis/obj/board")->move(this);
}

/*
 * Function: enter_inv
 * Description: block non-interactives from entering.
 */
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (living(ob) && !interactive(ob))
        ob->move(from);
}