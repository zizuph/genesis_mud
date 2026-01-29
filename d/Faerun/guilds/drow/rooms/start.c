/*
 * Start room
 * By Finwe, May 2006
 */

#include "/d/Faerun/defs.h"
#include "/d/Faerun/guilds/drow/race/guild.h"
#include <stdproperties.h>
#include <const.h>

inherit "/d/Faerun/guilds/drow/rooms/base_room.c";

void
create_drow_room()
{
    add_prop(ROOM_S_MAP_FILE, "drow_guild_map.txt");

    set_short("Sleeping Cave");
    set_long(short() + ". The cave is large and where drow come to " +
        "retire after their patrols, journies, or travels to the surface. " +
        "Large cots are spread around where you may rest. Dark " +
        "veins of colored ore run through the walls. A sign hangs on " +
        "the wall.\n");

    add_item("sign", "It is made from a bone-white material. Flowing " +
        "letters are written on it, which seem to dance with an inner flame.\n");
    add_cmd_item(({"sign", "words", "letters"}), "read", "@@read_sign@@");

    add_item(({"cots", "cots"}),
        "They are simple beds on which you may lay down and rest.\n");

	add_object(OBJ_DIR + "drow_armoire");
		
    add_exit("train", "east");
    add_exit("board_pri", "west");
    add_exit("shop2", "south");
}

/*
 * Function name:	init
 * Description	:
 */
public void
init()
{
    ::init();
    add_action("start", "start");
}


string read_sign()
{
    return "On the sign you read:\n\n" +
    "Type <start here> to begin your journies here when you wake up.\n";
}

int
start(string str)
{
    if(str == "here")
    {
        TP->set_default_start_location("/d/Faerun/guilds/drow/rooms/start");
        write("You will awaken here when you return.\n");
        return 1;

    }

    write("Do what?\n");
    return 1;
}
