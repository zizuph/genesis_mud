

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
    set_short("courtyard of the stronghold");
    set_long("@@sconce@@This is to test this.\n\n\n\n\n");
    remove_prop(ROOM_I_INSIDE);
    OUTSIDE;

    door=clone_object(WHITE + "guild/entry_door");
    door->move(TO);
    door2=clone_object(WHITE + "guild/stable_door")->move(TO);
    add_exit(WHITE + "guild/in_stronghold_gate","south",0);

    reset_room();
}


