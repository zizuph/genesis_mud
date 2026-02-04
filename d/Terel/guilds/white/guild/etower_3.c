

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
    set_short("top of the eastern tower of the stronghold");
    set_long("\n\n\n\n\n");
    OUTSIDE;
    remove_prop(ROOM_I_INSIDE);
    add_exit(WHITE + "guild/etower_2", "down", 0, 0);

    reset_room();
}


