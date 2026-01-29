inherit "/d/Gondor/common/room";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

object door;

create_room()
{
    set_short("Entry hall of a house in Minas Tirith");
    set_long("don't know yet");
    

    add_prop(ROOM_I_INSIDE,1);
    add_exit(MINAS_DIR +"houses/istair","north",0);
    add_exit(MINAS_DIR +"houses/idining","west",0);
    door = clone_object(MINAS_DIR+"obj/o_front_door");
    door->move(this_object());
}

