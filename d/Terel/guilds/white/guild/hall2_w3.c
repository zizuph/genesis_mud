

#include "/d/Terel/include/Terel.h"
inherit WHITE + "guild/keep_room";
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>
#include <stdproperties.h>

object door, door2;

public void
create_terel_room()
{
    ::create_terel_room();
    set_short("an arched hallway");
    set_long("\n\n\n\n\n");
    INSIDE;

    door2=clone_object(WHITE + "guild/wtow2_door2");
    door2->move(TO);


    add_exit(WHITE + "guild/hall2_w2", "south", 0, 0);
    reset_room();
}


