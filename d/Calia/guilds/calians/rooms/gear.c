/* Gear room in the crystalline palace
   Objects: history book and torch

   History: 30.11.94   book added, it was missing          Maniac
*/


#pragma save_binary

inherit "/std/room";
#include <stdproperties.h>
#include "defs.h"

object stand, history_book;

void
reset_room()
{
    if (present("torch", stand))
	return;
    clone_object(OBJECT("torch"))->move(stand);
    tell_room(THIS, "A calian warrior strolls in, puts a torch in the torch " +
	"stand, and then leaves.\n");
}

void
create_room()
{
    object this;

    set_short("The gear room");
    set_long(
	"You are climbing down a stair shaped like a huge, wide gear.  " +
	"Between the spokes of the gear there is adequate room for even a " +
	"large foot.  " +
	"As you descend you notice that you are always able to walk upright: " +
	" gravity is rotating as you descend.  " +
	"However, the gear stair does not seem to be moving.  " +
	"You also seem to have lost your sense of direction, although beams " +
	"of light approach from one direction while the other leads into " +
	"dimness.  " +
	"\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_exit(ROOM("light_stairs"), "light", 0);
    add_exit(ROOM("dark_stairs"), "dark", 0);
    add_item( ({ "gear", "stair", "stairs" }),
	"It looks like it might be part of a clock.\n");
    this = THIS;
    stand = clone_object(OBJECT("torch_stand"));
    stand->move(this);
    clone_object(OBJECT("torch"))->move(stand);
    call_out("reset_room", 1);
    history_book = clone_object(OBJECT("history_book"));
    history_book->move(this); 
}
