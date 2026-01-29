#include "../default.h"
inherit PORT_ROOM;

void
create_port_room()
{
    set_short("A dark, dismal prison cell");
    set_long("This is a dark and dismal prison cell. Conditions here are "+
      "absolutely horrid, for lying all over the floor are large amounts "+
      "of filth. This is true punishment for anyone imprisoned in this "+
      "hell hole.\n");
    add_item(({"dark dismal prison cell","dark cell","dismal cell","prison cell","cell"}),
      "The room is filled with the stench of human fecal matter, among other "+
      "disgusting filth.\n");
    add_item(({"disgusting filth","filth"}),"Human fecal waste, along "+
      "with dried urine and blood covers the cell floor.\n");
    add_item(({"cell floor","floor"}),"The ground is covered with "+
      "filth, filling the air with its rotting smell.\n");

    add_prop(ROOM_I_INSIDE,1);

    add_exit(PORT + "seahawk/ba8", "west",0,0,4);
    add_exit(PORT + "seahawk/ba6", "south",0,0,4);
}

