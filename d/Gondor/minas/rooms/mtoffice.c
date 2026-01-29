/*
 * /d/Gondor/minas/rooms/mtoffice.c
 *
 * Original version by Elessar
 *
 * Modification log:
 *  4-Dec-1996, Olorin: General revision.
 */
#pragma strict_types

inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/common/lib/binbit.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

// Prototypes:
private int     check_npc();
private int     check_wiz();
private string  initiate_quest_hints();
public  string  long_func();

// Global variables:
static string *Tours;

public void
create_gondor()
{
    object  board;
    string  name;

    set_short("the Minas Tirith Administration Office");
    set_long(long_func);
    
    add_exit(MINAS_DIR + "rooms/common",   "north", check_npc, 0);
    add_exit(MINAS_DIR + "n2crc3",         "south", 0, 0);
    add_exit(MINAS_DIR + "rooms/adoffice", "west",  0, 0);
    add_exit("/d/Gondor/workroom",         "up",    check_wiz, 0);

    add_prop(ROOM_I_INSIDE,1);

    board = clone_object("/std/board");
    name = BOARD_DIR;
    if (file_size(name) != -2) 
	mkdir(name);
    board->set_board_name(name + "minasboard");
    board->set_num_notes(30);
    board->set_silent(0);
    board->set_show_lvl(0);
    board->set_remove_lvl(15);
    board->set_remove_str("The note is stuck, you can't do that.");
    board->move(TO);

    initiate_quest_hints();
}

public string
initiate_quest_hints()
{
    Tours = "/d/Gondor/common/quest/tours"->query_tours();
    return "Quest-hints initiated.\n";
}

public string
long_func()
{
    string  longtxt = 
	  "This is the office of the administration of Minas "
        + "Tirith, where travellers may contact the leaders of the "
        + "City. There is a bulletin board here, where the travellers "
        + "may put notes with messages for each other or the city "
	+ "maintainers. A stair leads up to the Maintainer's "
        + "Office. To the west is the office of the Master of "
        + "Advice, to the north the common board.";

    switch (tod())
    {
    case "night":
	longtxt += " Through the south door you see the streetlights "
	    + "in the street.";
	break;
    case "early morning":
	longtxt += " Through the south door you see long shadows cast "
	    + "by the rising sun.";
	break;
    case "morning":
    case "noon":
    case "afternoon":
	longtxt += " Through the south door daylight enters the "
	    + "hall.";
	break;
    case "evening":
	longtxt += " Through the south door you see the sky is colored golden red.";
	break;
    }
    return "The Administration office of Minas Tirith.\n" + BSN(longtxt);
}

private int
check_npc()
{
    return (TP->query_npc());
}

private int
check_wiz()
{
    if (TP->query_real_name() == "elessar")
    {
	write("Welcome, King Elessar!\n");
	say("The adminstration officer bows to "+QCTNAME(TP)
		+" and lets him pass.\n");
	say("The officer says: Welcome, King Elessar! Just pass.\n");
	return 0;
    }
    if (TP->query_wiz_level())
    {
	write("Welcome, wizard!");
	say("The administration officer bows to "+QCTNAME(TP)+".\n");
	return 0;
    }
    write("The administration officer stops you, and says: Sorry, that is only for\n"+
	  "             the King and his guests.\n");
    return 1;
}
