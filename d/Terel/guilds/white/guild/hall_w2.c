

#include "/d/Terel/include/Terel.h"
inherit WHITE + "guild/keep_room";
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>
#include <stdproperties.h>

object door;

public void
create_terel_room()
{
    ::create_terel_room();
    set_short("an arched hallway");
    set_long("\n\n\n\n\n");
    INSIDE;

    door=clone_object(WHITE + "guild/lib_door2");
    door->move(TO);
    add_exit(WHITE + "guild/hall_w3", "north", 0, 0);
    add_exit(WHITE + "guild/hall_w1", "south", 0, 0);
    reset_room();
}


