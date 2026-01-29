#include "/d/Shire/sys/defs.h"
#include "/d/Shire/guild/sindar_racial/sindar_racial.h"
inherit "/d/Shire/std/room";

void create_shire_room()
{
    set_short("A quiet room");

    set_long("This is where Sindar sleep.\n");

    add_exit(SINDAR_RACE_DIR + "join_rm","west");
}

init()
{
  ::init();

    add_action("start", "start");

}

int
start(string str)
{
    if(str == "here")
    {
        TP->set_default_start_location(SINDAR_RACE_DIR + "start_rm");
        write("This is where you shall awaken.\n");
        return 1;

    }

    write("Start here?\n");
    return 1;
}

