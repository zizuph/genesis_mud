#pragma strict_types

inherit "/d/Gondor/morgul/city/morgul.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"


public void
create_morgul_room()
{
  set_extraline("In this narrow passage, it is completely dark. Moreover, " +
    "the dark stones that make the walls seem to swallow any light " +
    "that comes down here. The passage continues west and east.");
    add_tunnel_ceiling();
    add_tunnel_wall();
    set_road(5);
    set_side("northeast");

    add_exit(MORGUL_DIR + "city/tunnels/base_ne2","east","@@check_exit",1);
    add_exit(MORGUL_DIR + "city/tunnels/pass02","west","@@check_exit",1);
    add_prop(ROOM_I_LIGHT,-1);
}

