inherit "/d/Gondor/std/room.c";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"
#include "/d/Gondor/rohan/horn/hd_defs.h"

void create_gondor()
{
    object door;

    set_short("Inside the tower");
    set_long(BSN("Inside the small tower on Helm's Wall. "+
    "Beside the door stands an armsrack. On the other side of the door "+
    "a counter-clockwise spiral staircase leads up."));

    add_item("armsrack","The armsrack is empty.\n");

    add_exit(ROH_DIR + "horn/on_walls/wall_tower","up", 0, 3);
    add_prop(ROOM_I_INSIDE, 1);

    door = clone_object(ROH_DIR+"horn/doors/hw_tower_out"); 
    door->move(TO);
}
