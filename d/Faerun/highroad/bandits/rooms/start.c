/*
 * Bandit start location
 * -- Finwe, September 2006
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit BASE_CAVE;

void
create_cave()
{
    add_prop(ROOM_I_INSIDE,1);
    ALLOW_STEEDS;
    set_short("a dark cave");
    set_long("This cave is off the larger cave. It is darker than the " +
        "other. Dirty bedding is scattered around here where bandits " +
        "sleep. There are a few empty spaces for those who have purchased " +
        "a pillow to sleep here. The rough walls and low ceiling feel " +
        "confining here. There is some scrawlings on the wall.\n");

    add_item("scrawlings", "They are written crudely by someone who can't write well.\n");
    add_cmd_item("scrawlings", "read", "@@read_sign@@");

    add_exit(CAVE_DIR + "entr", "southeast");

}

void
init()
{
    ::init();
    add_action("start","sleep");
    add_action("start","start");

}

string read_sign()
{
    return "If you have a dirty pillow, you may sleep here. All you have to do is type <sleep here>. You will then wake up here, ready to burn and pillage travellers.\n";
}


int start(string str)
{
    object ob;

    if(!(ob=present("bandit_inn_key",TP)))
    {
        write("You don't have a pillow to sleep here!\n");
        return 1;
    }

    NF("Sleep where?\n");
    if(str != "here") return 0;

    ob->remove_object();

    TP->set_temp_start_location(CAVE_DIR + "start");
    LOG_FILE("bandit_start", "started in the Bandits temp location.");

     write("Looking around, you find a place to sleep. You will awake " +
        "here next time.\n");
    return 1;
}
