#include "default.h"
inherit PORT_ROOM;

void
create_port_room()
{
    add_prop(ROOM_NO_TIME_DESC,1);

    set_short("Small Pier");
    set_long("You are standing on a small wooden pier that sticks out "+
      "into the bay. Further to the north rises a massive cliff. The "+
      "wooden planks of the pier seem to creak and groan with the slightest "+
      "movement and the sound of water lapping gently against the supports enshrouds "+
      "your senses.\n");
    add_item(({"bay"}),"A beautiful expanse of water that sparkles with "+
      "an azure color.\n");
    add_item(({"massive cliff","cliff"}),"A towering edifice of rock, "+
      "the southern edge of a large plateau.\n");
    add_item(({"wooden planks","planks","wooden plank","plank"}),"Although "+
      "they groan and creak with your every movement, the weather-beaten "+
      "wood seems sturdy enough.\n");
    add_item(({"water"}),"It fills the bay.\n");
    add_item(({"supports","support"}),"Large wooden logs that hold the pier "+
      "above the water line.\n");
    add_exit(PORT + "s13", "west");
    add_exit(PORT + "s15", "east");
}

