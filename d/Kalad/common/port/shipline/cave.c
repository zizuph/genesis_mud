#include "../default.h"
inherit PORT_ROOM;

void
create_port_room()
{
    set_hear_bell(0);

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,0);
    set_short("Cave");
    set_long("A dark and dismal-looking cave.\n"+
      "From what little light you have you can barely see a set of stairs "+
      "carved into the rock spiraling upwards. To the south a faint light "+
      "is visible.\n");
    add_item(({"stairs"}),"Carved into the rock they lead upwards.\n");
    add_item(({"light"}),"A small light in the distant south, the only "+
      "light in this cave besides your own. It looks to be a way out of "+
      "here.\n");
    add_exit(PORT + "shipline/cave1", "up");
    add_exit(PORT + "shipline/pier", "south");
}

