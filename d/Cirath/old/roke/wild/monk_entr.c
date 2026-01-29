/*
 * monk_entr.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <std.h>

string
sign()
{
    return "You study the sign:\n" +
            "If you want to join the Kaheda order, you should go to the library\n" +
            "east of here first, and borrow the books 'rules' and 'applying'.\n";
}

public void
create_room()
{
    set_short("entrance of the Kaheda monastery");

    set_long("You are in the entrance of the monastery. It is rather " +
             "dark here, just like in the rest of the house, and the " +
             "only source of light is some candles that are hanging high " +
             "up in the ceiling. In front of you is a small desk, and behind " +
             "it sits an old monk, guarding the entrance. Above the monk " +
             "a small sign and a plaque are nailed to the wall.\n");

    INSIDE;

    add_prop(ROOM_M_NO_ATTACK,
             "You can not do that while on Sacred ground.\n");
    add_item("candles", "The candles are burning with a bright light.\n");
    add_item("desk", "The desk looks very old, and is very dirty.\n");
    add_item("monk", "The monk stares suspiciously at you.\n");

    add_item("plaque", "@@plaquefun");

    add_item("sign", "@@sign");
    add_cmd_item("sign", "read", "@@sign");

    add_exit("monk_barber", "west");
    add_exit("monk_board", "east");
    add_exit("monk_train", "north");
    add_exit("p6", "out");
    add_exit("monk_h1", "up");
}

string
plaquefun()
{
    string str;
    int i;
    mixed s;

    str = "The Honorable Councilmembers are:\n";
    /*
    seteuid(getuid(TO));

    s = (SECRET)->query_council_list(1);

    for (i = 0; i < sizeof(s); i++)
        str += capitalize(s[i]) + "\n";
    */
    return str;
}
