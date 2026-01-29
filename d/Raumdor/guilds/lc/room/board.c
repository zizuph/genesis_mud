/*********************************************************************
 * - board.c                                                       - *
 * - Board room in the Ladies club.                                - *
 * - Created by Damaris@Genesis 5/2003                             - *
 *********************************************************************/
#pragma no_clone
#pragma no_inherit
#pragma strict_types

#include <stdproperties.h>  
#include "../guild.h"
#define BOARD_DIR (LOG + "board_data")
inherit CLUB;

string
query_sign()
{
    return
      "         +--------------------------------------+\n"+
      "         |            Instructions              |\n"+
      "         |--------------------------------------|\n"+
      "         |'note <title>'         To post a note.|\n"+
      "         |'read <number>'        To read a note.|\n"+
      "         |'remove <number>' To remove your note.|\n"+
      "         +--------------------------------------+\n";
} 

public void
create_guild_room()
{
    object bb;
    set_short("A small informal room");
    set_long("This is a small informal room that has parchment "+
        "papers stacked neatly on a dark cherry wood counter. There "+
        "are quills placed next to the light parchment papers. On "+
        "the upper edge of the counter there is an inkwell that is "+
        "half-full of black ink. There is also a small sign that has "+
        "been placed just above the counter.\n");
    add_item(({"room", "area"}), query_long);
    add_item(({"sign"}), query_sign);
    add_item(({"papers", "parchment papers", "paper", "parchment paper"}),
        "The light parchment papers are thin and neatly stacked on "+
        "the wooden countertop.\n");
    add_item(({"countertop", "wooden countertop", "counter"}),
        "The counter top is made from fine polished cherry wood.\n");
    add_item(({"quill", "quills"}),
        "The quills are neatly laid next to the parchment papers.\n");
    add_item(({"ink", "inkwell", "black ink"}),
        "The inkwell is half-full of black ink.\n");
    add_item(({"wood"}),
        "The wood is sturdy and dark. Perfect for flooring and countertops.\n");
    add_item(({"north", "northwest", "northeast", "southeast", "southwest",
        "west"}),
        "There is a wall in that direction.\n");
    add_item(({"east"}), "There is a doorway in that direction that leads " +
        "to the postal area.\n");
    add_item(({"north"}),
        "There is a doorway in that direction that leads back to the "+
        "lobby area.\n");
    add_item(({"stairs", "stairway"}),
        "These stairs lead upwards to a loft.\n");
    add_item(({"loft"}),
        "There is a loft overhead with stairs leading to it.\n");
    add_item(({"up"}),
        "There is a ceiling and a noticable loft in that direction.\n");
    add_exit("post", "east");
    add_exit("lobby", "north");
    add_exit("cboard","up");
    set_no_exit_msg(({"south", "west", "northeast", "northwest",
        "southeast", "southwest"}),
        "You walked into a wall!\n"+
        "Ouch! That's gotta hurt!\n");
    setuid();
    seteuid(getuid());
    bb = clone_object("/std/board");
    bb->set_board_name(BOARD_DIR);
    bb->set_num_notes(30);
    bb->set_silent(0);
    bb->set_show_lvl(0);
    bb->move(this_object(), 1);
}

/*********************************************************************
 * - Function name: do_read                                        - *
 * - Description:   If a player wants to know what instuctions can - *
 * -                be used.                                       - *
 * - Arguments:     str - string, hopefully "sign"                 - *
 * - Returns:       1/0                                            - *
 *********************************************************************/
int
do_read(string str)
{
    if (str != "sign")
    {
        notify_fail("Read what?\n");
        return 0;
    }

    write(query_sign());
    return 1;
}

void
init()
{
    ::init();
    add_action(do_read, "read");
}
