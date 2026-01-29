#include "default.h"
inherit PORT_ROOM;

void
create_port_room()
{
    add_prop(ROOM_NO_TIME_DESC,1);

    set_short("Small Pier");
    set_long("You are standing on a small wooden pier that sticks out "+
      "into the bay. The end of the pier lies just west from here. The "+
      "wooden planks of the pier seem to creak and groan with the slightest "+
      "movement and the sound of water roughly hitting against the supports awakens "+
      "your senses.\n");
    add_item(({"bay"}),"A beautiful expanse of water that sparkles with "+
      "an azure color.\n");
    add_item(({"wooden planks","planks","wooden plank","plank"}),"Although "+
      "they groan and creak with your every movement, the weather-beaten "+
      "wood seems sturdy enough.\n");
    add_item(({"water"}),"It fills the bay.\n");
    add_item(({"supports","support"}),"Large wooden logs that hold the pier "+
      "above the water line.\n");
    add_exit(PORT + "s66", "west");
    add_exit(PORT + "s68", "east");
}

block()
{
    write("Heavy construction seems to be taking place at the end of "+
      "the pier, as such, it is currently closed off. Come back later and "+
      "perhaps it will be open.\n");
    return 1;
}

