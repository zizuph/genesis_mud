#include "default.h"
inherit PORT_ROOM;

void
create_port_room()
{
    add_prop(ROOM_NO_TIME_DESC,1);

    set_short("Wooden Platform");
    set_long("This is the northeastern end of a wooden platform that rests within the bay.\n"+
      "You have obviously reached a dead end, since nothing but water lies to the north and east. "+
      "Further north rises a massive cliff. A large building lies west from here. "+
      "The wooden planks of the platform "+
      "seem to creak and groan with the slightest movement and the sound "+
      "of water lapping gently against the supports enshrouds your senses.\n");
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
    add_item(({"water"}),"It fills the bay.\n");
    add_exit(PORT + "s32", "south");
}

