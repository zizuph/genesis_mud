

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
    set_long("@@sconce@@This is to test this.\n\n\n\n\n");
    INSIDE;

    door=clone_object(WHITE + "guild/temp_door2");
    door->move(TO);

    add_exit(WHITE + "guild/entry_hall", "south", 0, 0);
    add_exit(WHITE + "guild/hall_e1", "east", 0, 0);
    add_exit(WHITE + "guild/hall_w1", "west", 0, 0);
    reset_room();
}


