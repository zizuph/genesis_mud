#include "/d/Krynn/common/defs.h"
#include "local.h"
#include <macros.h>
inherit "/d/Krynn/std/room";

create_room()
{
    set_short("Northern end of main cavern");

    set_long(BS("You are at the very northern end of a vast natural cavern " +
      	"Gnomish inventions of many types can be seen to the south amidst " +
      	"crowds of busy little engineers.  Some of the gnomish living " +
      	"quarters are off to the west from here, along with their " +
      	"cafeteria and a few other conveniences.  There is a bulletin board " +
      "here.  East lies the main guard room.\n", 70));

    add_item(({"cavern", "cave", "caves"}), "Formed through natural " +
	"erosion, this cavern is hundreds of meters long and\nabout " +
	"thirty meters high.  It is fairly narrow along its length, " +
	"though it\nis wider higher up.");

    INSIDE;
    LIGHT;
    add_exit(TDIR + "cavern8", "south", 0);
    add_exit(TDIR + "mailroom", "west", 0);
    add_exit(TDIR + "guard0", "east", 0);
    add_exit(TDIR + "cafeteria", "north", 0);
    boardme();
}

boardme()
{
    object board;
    board = clone_object("/std/board");
    board->set_board_name("/d/Krynn/gnome/log/bulletins");
    board->set_num_notes(25);
    board->set_silent(0);
    board->set_show_lvl(0);
    board->set_remove_lvl(15);
    board->set_remove_str("You must be a wizard to remove notes.  " +
	"Mail Grrrr if the board is cluttered");
    board->set_err_log("/d/Krynn/gnome/log/board_err");
    board->move(TO);
}

area() { return "Inthemaincaverns"; }
wayout() { return "east north south"; }
tohelp() { return "east "; }
fromhelp() { return "south"; }
