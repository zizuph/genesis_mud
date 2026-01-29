/*
 * Sparkle post office
 *
 * Revision History:
 *   - June 9, 2009 - Added ROOM_S_MAP_FILE and changed exits to integrate
 *                    into New Sparkle (Gorboth)
 * Newbie helper poster added by TAPAKAH, 25/05/2005
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";
inherit "/d/Genesis/lib/post";

#include <stdproperties.h>

#include "../defs.h"

void
create_room()
{
    set_short("The post office");
    set_long("\n"+
             "You are in the post office.\n"+
             "This is a place of great magic! From here you can reach people\n"+
             "all over the world with a written message! Quite amazing.\n"+
             "A few of the commands are:\n" +
             "\tfrom [new]       List all [unread] headers.\n"+
             "\tread             Start up the mailreader command mode.\n"+
             "\tread <message>   Read message number <message> from your mailbox.\n"+
             "\tmail <name>      Mail to player(s) <name>.\n"+
             "Examine the mail reader for more instructions.\n" +
             "\nThere is an office of some sort to the east.\n" +
             "");

    add_item(({"walls","wall" }),"The red walls are quite ordinary.\n");
    add_item(({"office","east" }),"To the east lies the sorting office of " +
        "the postmaster. It is not accessible for customers.\n");

    add_exit("/d/Sparkle/area/city/rooms/streets/center_a", "north");

    add_prop(ROOM_I_LIGHT, ALWAYS_LIGHT);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_city_genesis.txt");

}

void
init()
{
    ::init();

    post_init();
}

void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    post_leave_inv(ob, to);
}

void
mail_message(string text)
{
    string spaces = "          ";
    int len = (9 - strlen(text)) / 2;

    text = "    !" + spaces[..(len-1)] + "There is" + text +
        " mail for you in the Sparkle post office." +
	spaces[..(8-len-strlen(text))] + "!";

    write("\n"+
        "    +----------------------------------------------------------+\n"+
        text + "\n" +
        "    !  (North end of the road just inside the village gate.)   !\n"+
        "    +----------------------------------------------------------+\n\n");
}
