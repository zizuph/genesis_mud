/*
 * /d/Shire/cypress/guilds/wrunner/rooms/start_rm
 * Start Room for Wild Elves
 * By Finwe, July 2001
 *
 * Added rack to room
 * Finwe, September 2007
 */
 
#include "../wrunner_defs.h"
#include "/d/Shire/cypress/sys/defs.h"

#include <macros.h>
#include <stdproperties.h>
 
inherit "/d/Shire/cypress/guilds/wrunner/base_common_inside";

//int okay_to_start;
void create_room()
{
    set_short("An exquisite quiet room");
    set_long("This is a quiet, relaxing room where Wild elves " +
        "come to rest and retire. Cots are scattered throughout " +
        "the room where tired elves may lie down. Gentle light " +
        "filters in from the ceiling and from the lights " +
        "hanging from the ceiling. A silver plaque is attached " +
        "to a wall.\n");

    add_item(({"cot", "cots"}),
        "The cots are made from metal frames. In the frames rest " +
        "woven mats. The cots provide a place for the elves to " +
        "retire and rest.\n");
    add_item(({"metal frame", "metal frames", "frames", "frame"}),
        "They are forged from metal and sit low to the " +
        "ground. They hold a mat for elves to lie down on.\n");
    add_item("plaque",
        "The plaque is attached to a wall next to the door. " +
        "It is made of silver and on it is something written " +
        "in fine elvish lettering.\n");
    add_cmd_item("plaque","read","@@read_sign@@");
    set_add_column_bldg();
    room_add_object("/d/Shire/cypress/guilds/wrunner/obj/rack");

    add_exit(ROOM_DIR + "hall","northeast");
}

init()
{
  ::init();

    add_action("start", "start");

}


int start(string str)
{
    if(str == "here")
    {
        TP->set_default_start_location(ROOM_DIR + "start_rm");
        write("You will awaken here next time you awake.\n");
        return 1;

    }

    write("Do what?\n");
    return 1;
}


string
read_sign()
{
    return "\n\n"+
    "       +---------------------------------------------------+\n"+
    "       |                                                   |\n"+
    "       |   0                                           0   |\n"+
    "       |                                                   |\n"+
    "       |   When you are ready to relax, you may <start     |\n"+
    "       |   here>. Then you will begin your travels here    |\n"+
    "       |   next time you awake.                            |\n"+
    "       |                                                   |\n"+
    "       |   0                                           0   |\n"+
    "       |                                                   |\n"+
    "       +---------------------------------------------------+\n\n";
}
