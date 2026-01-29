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
      "light is available you can see bare stone walls and a dark passage "+
      "leading to the southwest.\n");
    add_item(({"walls","wall"}),"Roughly cut, they are just plain rock. In the "+
      "northeastern corner of this room, a small hole is visible in the "+
      "cave wall.\n");
    add_item(({"small hole","hole"}),"It looks just large enough for a "+
      "full grown human to crawl through. It lies to the northeast.\n");
    add_exit(PORT + "shipline/cave5", "southwest");
    add_cmd_item(({"hole", "northeast"}), "enter", "@@enter");
    add_cmd_item(({"hole", "into hole", "through hole", "northeast"}),
            "crawl", "@@enter");
}

enter()
{
    write("You squeeze yourself into the cramped hole.\n");
    set_dircmd("hole");
    TP->move_living("into the cramped hole", "/d/Kalad/common/caravan/lot/ur");
    return "You fall out of the hole and into a pile of refuse!\n";
}

