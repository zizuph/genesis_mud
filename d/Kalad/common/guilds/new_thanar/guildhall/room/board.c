/**********************************************************************
 * - board.c                                                        - *
 * -                                                                - *
 * - Created by Damaris@Genesis 3/2004                              - *
 * - New Standrad file for new area for guild. Typos fixed.         - *
 * - by Mirandus@Genesis 01/2018                                    - *
 **********************************************************************/

#include "../guild.h"
#include <stdproperties.h>
inherit THANAR_STD_ROOM; 

/*
 * Function name: create_std_thanar()
 * Description  : Creates the room from standard room file
 */
public void
create_std_thanar()
{
    object bb;
    set_short("a quiet board room");
    set_long("This is the quiet board room of Thanar. "+
      "It is a small room that has parchment papers stacked neatly on a "+
      "marble counter top, with quills placed next to them. You see on the "+
      "upper edge of the counter top an inkwell that is quite full of ink.\n");
    add_item(({"room", "area"}), query_long);
    add_item(({"quill", "quills"}),
      "There are quills placed on a the marble counter top.\n");
    add_item(({"ink", "inkwell"}),
      "The inkwell is sitting on the marble counter top and is quite full "+
      "of dark ink.\n");
    add_item(({"counter top", "marble counter top"}),
      "The marble counter top is placed here is attached firmly to the wall "+
      "and parchment papers, quills, and an inkwell have been placed on it.\n");
    add_item(({"parchment", "parchment papers", "papers", "paper"}),
      "The parchment papers have been stacked neatly on the marble "+
      "counter top for posting on the board.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);

    add_exit("start", "south");
    add_exit("cboard", "north");

    setuid();
    seteuid(getuid());
    bb = clone_object("/std/board");
    bb->set_board_name(BOARD_DIR);
    bb->set_num_notes(50);
    bb->set_silent(0);
    bb->set_show_lvl(0);
    bb->move(this_object(), 1);
}
