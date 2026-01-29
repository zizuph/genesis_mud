#include "default.h"
inherit PORT_ROOM;

void
create_port_room()
{
    add_prop(ROOM_NO_TIME_DESC,1);

    set_short("Small Pier");
    set_long("You are standing on a small wooden pier that sticks out "+
      "into the bay. The "+
      "wooden planks of the pier seem to creak and groan with the slightest "+
      "movement and the sound of water roughly hitting against the supports awakens "+
      "your senses. A small building sits here on an enlarged section of "+
      "the pier.\n");
    add_item(({"bay"}),"A beautiful expanse of water that sparkles with "+
      "an azure color.\n");
    add_item(({"wooden planks","planks","wooden plank","plank"}),"Although "+
      "they groan and creak with your every movement, the weather-beaten "+
      "wood seems sturdy enough.\n");
    add_item(({"water"}),"It fills the bay.\n");
    add_item(({"supports","support"}),"Large wooden logs that hold the pier "+
      "above the water line.\n");
    add_item(({"small building","building"}),"A moderate-sized building that is "+
      "rather plainly addorned, its sole decorations being a giant marlin "+
      "on one side and a sign on the other.\n");
    add_item(({"giant marlin","marlin"}),"A gigantic sporting fish, it "+
      "is hanging on the side of the small building looking, and smelling, "+
      "quite dead.\n");
    add_item(({"sign"}),"It has lots of legible words on it, perhaps you could "+
      "find the time to read it.\n");
    add_item(({"decorations","decoration"}),"Which one?\n");
    add_exit(PORT + "s78", "west");
    add_exit(PORT + "s79a", "in");
    add_exit(PORT + "s80", "east");
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
    "----------------+----------------------------+\n"+
    "----------------|~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ |\n"+
    "                |         Residence          |\n"+
    "                |             of             |\n"+
    "                |       Bassil Korahf        |\n"+
    "                |____________________________|\n"+
    "                 ()_________________________)\n"+
    "                   |    Head Shipwright    |\n"+
    "                   | of the Port District. |\n"+
    "                   +-----------------------+\n";
}

