#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_hear_bell(1);

    add_prop(ROOM_I_INSIDE, 1);

    set_short("Grand Hallway");
    set_long("You are walking along the grand hallway.\n"+
      "This magnificent passageway, which stretches to the north and south "+
      "is lined with dozens of marbles busts. The floor is also made of "+
      "marble and looks to have been meticulously polished.\n");

    add_item(({ "busts" }),
      "There are dozens of them lining the hallway to the north and south, "+
      "reading a few inscriptions at the base of some busts you realize "+
      "that each of them depicts a former leader of the powerful Trading "+
      "Company.\n");

    add_exit(CVAN + "company/s26", "north");
    add_exit(CVAN + "company/s2", "south");
}
