#include "default.h"
inherit PORT_ROOM;

#define BOAT PORT + "shipline6/ship"

/* Sept 25/96: Patched by Khail to prevent the master copy of the */
/* Line moved to Sparkle, Tapakah, 05/2009 */
/* ship from sailing. */
create_port_room()
{
    add_prop(ROOM_NO_TIME_DESC,1);

    set_short("Small Pier");
    set_long("You are standing at the end of a small wooden pier that sticks out "+
      "into the bay. A large sign has been planted here. The "+
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
    add_item(({"large sign","sign"}),"There is lots of legible writing "+
      "on it, maybe you should read it.\n");
    add_exit(PORT + "s103", "east");
    //clone_object(BOAT)->start_ship();
}

init()
{
    ::init();
    AA(read_sign,read);
}

string
sign()
{
    return "\n"+
    "                         @@@@@@@@@@@@@@@@@@@@@@@@@@\n"+
    "                         @                        @\n"+
    "                         @  Doogala  the Captain  @\n"+
    "                         @   of the Dreadnaught   @\n"+
    "                         @ now sails from Sparkle @\n"+
    "                         @                        @\n"+
    "                         @ --Genesis ShipLines    @\n"+
    "                         @      Company           @\n"+
    "                         @________________________@\n"+
    "                         @@@@@@@@@@@@@@@@@@@@@@@@@@\n";
}

