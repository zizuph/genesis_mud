

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
    add_exit(WHITE + "guild/hall2_w2", "north", 0, 0);
    add_exit(WHITE + "guild/hall2_1", "east", 0, 0);
    reset_room();
}


