#include "../default.h"
inherit PORT_ROOM;

void
create_port_room()
{
    set_short("A dark, dismal prison cell");
    set_long("This is a dark, dismal prison cell. To the east, you can "+
      "see a bit more light than in the rest of this cell. From further "+
      "into the cell, you hear a slight moaning sound, whether from the "+
      "groan of the ship's wood or from prisoners, you cannot tell.\n");
    add_item(({"dark dismal prison cell","dark cell","dismal cell","prison cell","cell"}),
      "Filth lies scattered about the room, filling the air with a "+
      "disgusting smell.\n");
    add_item(({"filth"}),"A combination of human fecal waste and grime "+
      "blankets the cell floor.\n");
    add_item(({"cell floor","floor"}),"The bare wooden floor is covered in "+
      "filth.\n");

    add_prop(ROOM_I_INSIDE,1);

    add_exit(PORT + "seahawk/ba5", "north",0,0,4);
    add_exit(PORT + "seahawk/ba7", "south",0,0,4);
    clone_object(PORT + "seahawk/door1")->move(TO);
}

