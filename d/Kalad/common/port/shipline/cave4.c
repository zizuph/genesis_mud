#include "../default.h"
inherit PORT_ROOM;

void
create_port_room()
{
    set_hear_bell(0);

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,0);
    set_short("Cave");
    set_long("You are in a dark and dismal cave.\n"+
      "You can barely make out this room. From what little "+
      "light is available you can see bare stone walls and dark passages "+
      "leading to the southwest and northeast.\n");
    add_item(({"walls","wall"}),"Roughly cut, they are just plain rock.\n");
    add_exit(PORT + "shipline/cave3", "southwest");
    add_exit(PORT + "shipline/cave5", "northeast");
}

