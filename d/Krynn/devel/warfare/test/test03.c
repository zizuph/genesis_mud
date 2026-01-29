
inherit "/d/Krynn/std/room";

#include "../warfare.h"

inherit (WAR_PATH + "conquer_base");

public void
create_krynn_room()
{
    set_short("test room");
    set_long("A test room.\n");

    set_area_name(WAR_AREA_SOLACE);
    
    add_exit("test04", "south");
    add_exit("test02", "west");
}

void
init()
{
    init_conquer();
    ::init();
}

void
reset_krynn_room()
{
    if (gAreaName)
	reset_conquer_room();
    else
	::reset_krynn_room();
}

  
