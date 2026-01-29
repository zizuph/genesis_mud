
inherit "/d/Shire/room";

#include "/d/Shire/clubs/sgc/gobdefs.h"
#include "/d/Shire/sys/defs.h"
#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include <std.h>


static void create_board();

create_room()
{
        object board;

   set_short("Da pasting board");
   set_long("This room stinks of dead animals.\n"
          + "You have arrived in a separate part of the caves. The "+
            "room is characterized by a large bulletin board. Feel "+
            "free to write, or attempt to write, anything you like "+
            "on it.\n");


   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 2);
    add_prop(ROOM_S_MAP_FILE, "smart_goblin_caves.txt");
   add_exit(SGC_DIR + "jcave","west");
   add_exit(SGC_DIR + "librm","east",0,1);
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

    if ((board = clone_object("/d/Shire/std/board")))
    {
      board->set_board_name("/d/Shire/clubs/sgc/board");
        board->set_num_notes(15);
        board->set_anonymous(0);
        board->set_silent(1);
        board->set_show_lvl(0);
        board->set_remove_rank(WIZ_NORMAL);
        board->set_remove_str("Sorry, mortals are not allowed to "+
        "remove notes.\n");
        board->move(TO);
    }
    return 0;
}
