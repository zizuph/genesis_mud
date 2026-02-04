

#include "/d/Terel/include/Terel.h"
inherit WHITE + "guild/keep_room";
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>
#include <stdproperties.h>



public void
create_terel_room()
{
    ::create_terel_room();
    set_short("an arched hallway");
    set_long("\n\n\n\n\n");
    INSIDE;


    add_exit(WHITE + "guild/hall_e3", "north", 0, 0);
    add_exit(WHITE + "guild/hall_e1", "south", 0, 0);

    reset_room();
}


