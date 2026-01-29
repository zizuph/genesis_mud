/*
 *  /d/Gondor/guilds/rangers/ithilien/boardchamber.c
 *
 * Modifications:
 * 12-Oct-1998,Gnadnar: tidy up, add items
 * 20-Jul-2001,Alto: more tidy up, change inheritance for new
 *                   rangers.
 */
inherit "/d/Gondor/std/room.c";
#include "../rangers.h"
inherit RANGERS_DIR + "election_base.c";
inherit RANGERS_ITH_DIR + "ith_funcs.c";
#include <macros.h>
#include <std.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "exit.c"

#define PARCHMENT_TEXT \
    "/-------------------------------------------------------------/ \n" + \
    "|                                                             |\n" + \
    "|  - Two of our scouts have been on lookout duty for          |\n" + \
    "|    days, watching the road towards the Morannon.            |\n" + \
    "|    They may be in need of provisions by now.                |\n" + \
    "|                                                             |\n" + \
    "/-------------------------------------------------------------/\n"

/* prototypes */
public void    create_gondor();
public string  long_desc();


string
long_desc()
{

    return "A wooden bulletin board, scarred by long use, just "
        + "fits in this small, dim chamber. An iron torch stand " 
        + "is mounted here, providing some small amount of light. "
        + "The dark rock walls are close on all sides. A small "
        + "alcove near the exit draws your attention.\n";
}


public void
create_gondor()
{
    object  board;

    set_short("the board chamber of Henneth Annun");
    set_long(&long_desc());

    add_exit((RANGERS_ITH_DIR + "start"), "south", &check_ranger(0));

    /* Add Ithilien add_items */
    ith_add_items();

    add_item(({"sentinel", "green-cloaked sentinel"}), "You are too late! "
        + "Whoever it was is gone.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);

    add_item(({"cave", "chamber", "rock chamber"}), &long_desc());
    add_item(({"doorway", "opening", "south wall"}), "An opening in the wall "
        + "leads south to a larger chamber. A scrap of parchment is tacked "
        + "to one side of the opening.\n");
    add_item( ({ "large chamber", "larger chamber", }),
        "The cave to the south appears much larger than this one.\n");
    add_item( ({ "scrap", "vellum", "parchment",  }),
        "The parchment is a mere scrap of old vellum. It reads:\n" +
        PARCHMENT_TEXT);
    add_item(({"alcove", "small alcove"}), "The small alcove near the "
        + "exit is designed to allow you to nominate candidates and vote "
        + "in company elections. You may also call for the impeachment "
        + "of your Captain in this room should circumstances be dark "
        + "enough to require it. See help rangers elections for details.\n");
    add_item(({"torch", "torch stand", "iron torch stand"}), "An iron " +
        "torch stand contains a lit torch that provides light for " +
        "reading.\n");

    add_cmd_item("parchment", "read", PARCHMENT_TEXT);
    add_prop(ROOM_M_NO_SCRY, "Your sight is clouded with a grey fog.\n");

    FIX_EUID;
    board = clone_object(STD_DIR + "board");
    board->set_board_name(RANGERS_BOARD + "roi_board");
    board->set_num_notes(50);
    board->set_silent(0);
    board->set_show_lvl(0);
    board->set_remove_lvl(WIZ_NORMAL);
    board->set_remove_str("The note is firmly affixed to the board.");
    board->move(TO);
} 

/*
 * Function name: init
 * Description  : Adds commands relevant to the inherited voting.
 */
public void
init()
{
    ::init();

    init_vote_actions();
}

