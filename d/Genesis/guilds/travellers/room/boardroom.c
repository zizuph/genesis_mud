#pragma strict_types
#pragma save_binary

#include "../guild.h"

inherit TRAVELLERS_STD_DIR + "room_base";

#include <std.h>

void
create_traveller_room()
{
    string str;
    object board;
    
    set_short("Traveller Boardroom");
    set_long("You are in the traveller's guildhall. Here, guild members" +
        " sit to the early hours of the morning telling tales of their" +
        " travels and adventures. A large fireplace sits against the east" + 
        " wall, with a huge roaring fire. A pile of freshly cut logs" + 
        " sits neatly beside the fireplace. A thick leather bound" + 
        " book is chained to the wall.\n"); 
    
    add_item("fire","The fire brings heat to the hall.\n");

    add_item(({"paintings","pictures"}),"You see the pictures of three mighty"+
             " wizards. You see that\nthey are the wizards whose statues are "+
             "located at the town square.\n");
    add_item(({"fireplace"}),"The fireplace is a huge anitque, carved from" + 
        " a single block of stone.\nA mantlepiece above holds many relics" + 
        " from many places\nin the world.\n");
    add_item(({"relics","relic"}),"They are items gathered by guild members" +
        " as proof of their travels.\n");
    add_item(({"log","logs"}),"The logs are freshly cut and look like they"
        + " will burn well.\n");

    str = "Joining the guild is simple, all you need to do is\n" +
        "find another guild member and get him/her to get you\n" +
        "a badge of authorization, which allows passage to the\n" +
        "upper floor of the chateau.\n" +
        "Once there you can join the guild and be presented\n" +
        "with an insignia, which allows access to the other\n" +
        "rooms on the upper floor : the library and training\n" +
        "room.\n\n" +
        "Good Luck!\n";

    add_item("book", str);
    add_cmd_item("book", "read", str);

    add_exit("stairs", "east");
    add_exit("common", "common");

    setuid();
    seteuid(getuid());

    if ((board = clone_object("/std/board")))
    {
        board->set_board_name(TRAVELLERS_LOG_DIR + "board_data");
        board->set_num_notes(20);
        board->set_silent(1);
        board->set_show_lvl(0);
        board->set_remove_rank(WIZ_NORMAL);
        board->set_remove_str("Sorry, mortals are not allowed to remove " +
            "notes.\n");
        board->move(this_object(), 1);
    }
}
