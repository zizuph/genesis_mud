/**********************************************************************
 * - board.c                                                        - *
 * -                                                                - *
 * - Created by Damaris@Genesis 3/2004                              - *
 **********************************************************************/

#include "../guild.h"
#include <stdproperties.h>
inherit GUILD_ROOM;
#define BOARD_DIR "/d/Raumdor/guilds/thanar/log/board_data"

public void
create_guild_room()
{
    object bb;
    set_short("a quiet board room");
    set_long("    This is the quiet board room of Thanar. "+
      "It is a small room that has parchment papers stacked neatly on a "+
      "marble countertop, with quills placed next to them. You see on the "+
      "upper edge of the countertop an inkwell that is quite full of ink.\n");
    add_item(({"room", "area"}), query_long);
    add_item(({"quill", "quills"}),
      "There are quills placed on a the marble countertop.\n");
    add_item(({"ink", "inkwell"}),
      "The inwell is sitting on the marble countertop and is quite full "+
      "of dark ink.\n");
    add_item(({"countertop", "marble countertop"}),
      "The marble countertop is placed here is attatched firmly to the wall "+
      "and parchment papers, quills, and an inkwell have been placed on it.\n");
    add_item(({"parchment", "parchment papers", "papers", "paper"}),
      "The parchment papers have been stacked neatly on the marble "+
      "countertop for posting on the board.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);

    add_exit("start", "south");
    add_exit("cboard", "up");


    setuid();
    seteuid(getuid());
    bb = clone_object("/std/board");
    bb->set_board_name(BOARD_DIR);
    bb->set_num_notes(50);
    bb->set_silent(0);
    bb->set_show_lvl(0);
    bb->move(this_object(), 1);
}
