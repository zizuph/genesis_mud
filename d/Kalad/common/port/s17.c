#include "default.h"
inherit PORT_ROOM;

void
create_port_room()
{
    add_prop(ROOM_NO_TIME_DESC,1);

    set_short("Wooden Platform");
    set_long("This is the northwestern area of a wooden platform that rests within the bay.\n"+
      "Further north rises a massive cliff. A large building lies east from here. "+
      "The wooden planks of the platform "+
      "seem to creak and groan with the slightest movement and the sound "+
      "of water lapping gently against the supports enshrouds your senses. "+
      "A small pier leads west, connecting this platform with the mainland.\n");
    add_item(({"wooden platform","platform"}),"What you are standing on.\n");
    add_item(({"massive cliff","cliff"}),"A towering rock face that marks "+
      "the edge of the plateau upon which the rest of the city of Kabal lies.\n");
    add_item(({"wooden planks","wooden plank","planks","plank"}),
      "Made out of sturdy hardwood boards, they seem to be capable of "+
      "weathering even the strongest of storms.\n");
    add_item(({"large building","building"}),"A large warehouse-type "+
      "structure that sits in the center of this platform in the bay.\n");
    add_item(({"bay"}),"A beautiful expanse of water that sparkles with "+
      "an azure color.\n");
    add_item(({"supports","support"}),"Large wooden logs that hold the platform "+
      "above the water line.\n");
    add_item(({"small pier","pier"}),"A short, squat pier that connects the "+
      "mainland with this platform.\n");
    add_item(({"mainland"}),"You can see many buildings lining the shore.\n");
    add_item(({"water"}),"It fills the bay.\n");
    add_exit(PORT + "s16", "west");
    add_exit(PORT + "s30", "south");
}

