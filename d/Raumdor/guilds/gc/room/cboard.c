/*********************************************************************
 * - cboard.c                                                      - *
 * - Common board room in the Gentleman's club                     - *
 * - Created by Damaris 10/2001                                    - *
 *********************************************************************/

#pragma strict_types

#include <stdproperties.h>  
#include "../guild.h"

inherit CLUB;

string
query_sign()
{
    return
        "         +------------------------------+\n"+
        "         |            NOTICE            |\n"+
        "         +------------------------------+\n"+
        "         | Only Immortals can write on  |\n"+
        "         | this board. It is to help in |\n"+
        "         | the communication between    |\n"+
        "         | Immortals and mortals        |\n"+
        "         | concerning this realm.       |\n"+
        "         +------------------------------+\n";
} 

public void load_board();

public void
create_guild_room()
{
    set_short("A cozy loft");
    set_long("This is a small cozy loft, which contains the common "+
      "board. This board has been placed here by Immortals. There "+
      "is a large notice that is in front of the board.\n");
    add_item(({"room", "area", "loft"}), query_long);
    add_item(({"sign", "notice"}), query_sign);
    add_item(({"north", "south", "east", "west", "northest", "northwest",
        "southeast", "southwest"}), "There is a wall in that direction.\n");
    add_item(({"stairs", "stairway"}),
        "The stairs lead down from here.\n");
    add_item(({"down"}),
        "There is a stairway leading down.\n");
    add_item(({"wood"}),
        "The wood is sturdy and dark. Perfect for flooring.\n");
    add_item(({"up"}),
        "There is a ceiling there.\n");
    add_exit("board", "down");
    set_no_exit_msg(({"north", "south", "east", "west", "northeast",
        "northwest", "southeast", "southwest"}),
        "You walked into a wall!\n"+
        "Ouch! That's gotta hurt!\n");
    load_board();
}

public void
load_board()
{
    object bb;
    seteuid(getuid(this_object()));
    bb = clone_object("/d/Genesis/obj/board");
    bb->move(this_object());
    return;
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
    if((str == "sign") || (str == "notice"))
    {
        write(query_sign());
        return 1;	
    }
    else 
    {
        notify_fail("Read what?\n");
        return 0;
    }
}

void
init()
{
    ::init();
    add_action(do_read, "read");
}
