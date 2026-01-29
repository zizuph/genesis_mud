
inherit "/std/room";

#include "/d/Cirath/common/defs.h"
public void reset_room();
create_room()
{
   object board;
   set_short("The Cabin of Cirath");
   set_long("A fire crackles in the corner of this cozy cabin, its dancing "+
            "light filling the room with an eerie glow. Near the only window "+
            "is the mounted carapace of some large insect, and "+
            "the hide of a fierce jungle barbarian is spread across the floor."+
             " A collection of weapons used by nomadic raiders is on the wall above "+
            "the fireplace, which crackles between a wooden sign and a "+
            "doorway to the north. Many other doors lead from this room, "+
            "each with a name engraved upon it.\n");
   add_item("fire","By some bizarre magic the fire is actually cold! It "+
            "just offsets the heat coming from outside perfectly.\n");
   add_item("window", "Outside is the stark beauty of endless desert and "+
            "barren plain. Glorious, yet deadly.\n");
   add_item("fireplace","It is quite large.\n");
   add_item(({"sign","wooden sign"}), "It has some beautiful "+
              "writing carved into it.\n");
   add_cmd_item("sign","read",
                "Welcome to the Cirath domain's workroom!\n"
              + "This is where one can place notes concerning "+
                "the domain or just code here.\n");
   add_exit("/w/mandos/workroom","mandos");
   add_exit("/w/luther/workroom", "luther");
	add_exit("/w/milashk/workroom", "milashk");
   add_exit("/d/Cirath/open/projects/ctower", "north");
   add_exit("/d/Genesis/wiz/domain","tower");
   add_exit("/d/Cirath/quest_handler/quest_handler.c","quest");
    add_exit("/w/azazel/workroom","azazel");
   reset_room();
}

reset_room()
{
   if (!present("board", TO))
      create_board();
}

static void
create_board()
{
   object board;
    if ((board = clone_object("/std/board")))
    {
        board->set_board_name("/d/Cirath/board");
        board->set_num_notes(30);
        board->set_silent(1);
        board->set_show_lvl(0);
        board->move(TO);
    }
    return 0;
}
