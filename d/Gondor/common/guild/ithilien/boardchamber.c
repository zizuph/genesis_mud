/*
 * /d/Gondor/common/guild/ithilien/boardchamber.c
 *
 * Modifications:
 * 12-Oct-1998,Gnadnar:	tidy up, add items
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <std.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

#define	PARCHMENT_TEXT \
	"/--------------------------------------------------------------/ \n" + \
	"|                                                              |\n" + \
	"|  - Two of our scouts have been on lookout duty for           |\n" + \
	"|    days, watching the road towards the Morannon.             |\n" + \
	"|    They may be in need of provisions by now.                 |\n" + \
	"|                                                              |\n" + \
	"/--------------------------------------------------------------/\n"

/* prototypes */
public void	create_gondor();


/*
 * Function name:	create_gondor
 * Description	:	set up the room
 */
public void
create_gondor()
{
    object  board;

    set_short("the board chamber");
    set_long(BSN(
	"A wooden bulletin board, scarred by long use, just fits in this " +
	"small, dim chamber. The dark rock walls are close on all sides."));
    add_exit((RANGER_ITH_DIR + "erockchamber"), "south", 0);

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);

    add_item( ({ "cave", "chamber", }), long);
    add_item("floor", BSN(
	"The bare rock shows little signs of traffic. " +
	"Evidently the stone is quite hard."));
    add_item( ({ "wall", "walls",}), BSN(
	"The rock walls curve up to merge seamlessly with the low " +
	"roof.  A small parchment, easily overlooked, is fastened " +
	"to the south wall."));
    add_item( ({ "doorway", "opening", "south wall" }), BSN(
	"An opening in the wall leads south to a larger chamber. " +
	"A scrap of parchment is tacked to one side of the opening."));
    add_item( ({ "roof", "ceiling", }),
	"The roof is just high enough to clear the board.\n");
    add_item( ({ "rock", "stone", }), BSN(
	"Floor, walls and ceiling are all the same dark grey rock. " +
	"It appears quite hard, and shows no mark of chisel or " +
	"pick."));
    add_item( ({ "large chamber", "larger chamber", }),
	"The cave to the south appears much larger than this one.\n");
    add_item( ({ "scrap", "vellum", "parchment",  }),
	"The parchment is a mere scrap of old vellum. It reads:\n" +
	PARCHMENT_TEXT);

    add_cmd_item("parchment", "read", PARCHMENT_TEXT);

    FIX_EUID;
    board = clone_object("/std/board");
    board->set_board_name(BOARD_DIR + "ithilienboard");
    board->set_num_notes(40);
    board->set_silent(0);
    board->set_show_lvl(0);
    board->set_remove_lvl(WIZ_ARCH);
    board->set_remove_str("The note is firmly affixed to the board.");
    board->move(TO);
    clone_object(RANGER_DIR + "obj/crate")->move(TO);

} /* create_gondor */
