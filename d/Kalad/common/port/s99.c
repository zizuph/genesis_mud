#include "default.h"
inherit PORT_ROOM;

void
create_port_room()
{
    add_prop(ROOM_NO_TIME_DESC,1);

    set_short("Long Pier");
    set_long("You are standing on a long wooden pier that sticks out "+
      "into the bay. The end of the pier lies just south from here. The "+
      "wooden planks of the pier seem to creak and groan with the slightest "+
      "movement and the sound of water roughly hitting against the supports assaults "+
      "your senses. The harsh cry of seagulls fills the air.\n");
    add_item(({"bay"}),"A beautiful expanse of water that sparkles with "+
      "an azure color.\n");
    add_item(({"wooden planks","planks","wooden plank","plank"}),"Although "+
      "they groan and creak with your every movement, the weather-beaten "+
      "wood seems sturdy enough.\n");
    add_item(({"water"}),"It fills the bay.\n");
    add_item(({"supports","support"}),"Large wooden logs that hold the pier "+
      "above the water line.\n");
    add_exit(PORT + "s98", "north");
    add_exit(PORT + "s100", "south");
}

block()
{
    write("The end of the pier seems to be undergoing some sort of "+
      "construction, perhaps you should come back later to see if its open.\n");
    return 1;
}

