#include "../default.h"
inherit PORT_ROOM;

void
create_port_room()
{
    set_hear_bell(0);

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,0);
    set_short("Cave");
    set_long("You are inside a dark and dismal cave.\n"+
      "You can barely see the bare stone walls of this "+
      "cave. From what little light is available you can see a large "+
      "staircase that's been carved into the rock itself. It leads upwards "+
      "and down from here.\n");
    add_item(({"staircase"}),"It leads up and down into darkness.\n");
    add_item(({"walls","wall"}),"Naked, rough-textured stone.\n");
    add_exit(PORT + "shipline/cave1", "down");
    add_exit(PORT + "shipline/cave3", "up");
}

