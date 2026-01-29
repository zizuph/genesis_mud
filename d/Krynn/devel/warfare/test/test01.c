
inherit "/d/Krynn/std/room";

#include "../warfare.h"

inherit (WAR_PATH + "recruit_base");

public void
create_krynn_room()
{
    set_short("test recruit room");
    set_long("A test recruit room.\n");

    set_army(KNIGHT_ARMY);
    
    add_exit("test02", "north");
    add_exit("test04", "east");
}

void
init()
{
    init_recruit();
    ::init();
}


  
