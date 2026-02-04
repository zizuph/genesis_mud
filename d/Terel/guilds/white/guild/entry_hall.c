

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
    set_short("grand entry hall");
    set_long("@@sconce@@This is to test this.\n\n\n\n\n");
    INSIDE;

    door=clone_object(WHITE + "guild/entry_door2");
    door->move(TO);
    add_exit(WHITE + "guild/hall_1","north",0,0);

    reset_room();
}


