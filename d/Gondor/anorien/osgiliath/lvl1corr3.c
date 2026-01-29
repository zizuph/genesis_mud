inherit "/d/Gondor/common/room";
inherit "/d/Gondor/anorien/osgiliath/osgiliath";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void   add_stuff();

void
create_room()
{
    set_short("in a dark corridor in the ruins of Central Osgiliath");
    set_long(BSN("You are in a rather dark and damp corridor with "
      + "stone walls. There is a little light coming from the "
      + "northeast, while only darkness is waiting to the southwest. "
      + "The walls of the corridor are smooth, never turning around "
      + "corners, but rather bending slightly in one direction as if "
      + "forming a circle."));
    add_prop(ROOM_M_NO_TELEPORT, check_teleport);
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,0);
    add_item("walls",BSN("The walls are made of smooth white stone, "
      + "though the passage of hundreds of years since repair have "
      + "left solid tracks."));
    add_exit(OSG_DIR+"lvl1corr2","southwest",0,1);
    add_exit(OSG_DIR+"e1archway","northeast",0,1);

    add_stuff();
}

void
add_stuff()
{
    object  tstand;

    tstand = clone_object(OBJ_DIR + "torchstand");
    tstand->set_torch_file(0);
    tstand->set_stand_desc("rusty torch stand");
    tstand->add_adj("rusty");
    tstand->set_long("The torch stand is made of metal rings that "
      + "can hold a torch.\n");
    tstand->move(TO);
}
