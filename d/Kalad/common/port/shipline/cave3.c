#include "../default.h"
inherit PORT_ROOM;

void
create_port_room()
{
    set_hear_bell(0);

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,0);
    set_short("Cave");
    set_long("You are inside a damp and dismal cave.\n"+
      "From the little light available here you can barely make "+
      "out a set of carved stone stairs leading down into the darkness. To "+
      "the northeast is another dark passage. The ground is a bit slippery "+
      "here.\n");
    add_item(({"stairs"}),"A staircase thats been carved into the rock of "+
      "the cave, it leads down from here.\n");
    add_item(({"ground"}),"Its covered in some dark liquid, you can't tell "+
      "exactly what because of the inadequate light.\n");
    add_exit(PORT + "shipline/cave2", "down");
    add_exit(PORT + "shipline/cave4", "northeast");
}

