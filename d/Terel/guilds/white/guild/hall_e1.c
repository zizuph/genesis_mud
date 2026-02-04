

#include "/d/Terel/include/Terel.h"
inherit WHITE + "guild/keep_room";
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>
#include <stdproperties.h>

object door,door2;

public void
create_terel_room()
{
    ::create_terel_room();
    set_short("an arched hallway");
    set_long("\n\n\n\n\n");
    INSIDE;


    add_exit(WHITE + "guild/hall_e2", "north", 0, 0);
    add_exit(WHITE + "guild/hall_1", "west", 0, 0);
    door=clone_object(WHITE+"guild/tr_door2")->move(TO);
    door2=clone_object(WHITE+"guild/forge_door2")->move(TO);
    reset_room();
}


