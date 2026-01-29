#include "../default.h"
inherit PORT_ROOM;

void
create_port_room()
{
    set_short("A dark, dismal room in the prison cell");
    set_long("A dark, dismal prison cell.\n"+
      "Very little light filters into this section of the jail, and there "+
      "seems to be even greater darkness to the west.\n"+
      "The decayed remains of some creature lies on the floor.\n");
    add_item(({"decayed remains","remains","creature"}),"The corpse "+
      "looks to have once been human, but you cannot be certain due to the "+
      "deterioration of the body.\n");
    add_item(({"floor"}),"It is covered with reeking piles of filth.\n");
    add_item(({"reeking piles of filth","reeking piles","piles","filth"}),
      "Dessicated human feces and dried urine blanket the jail floor, filling "+
      "the room with a horrid stench.\n");

    add_prop(ROOM_I_INSIDE,1);

    add_exit(PORT + "seahawk/ba10", "west",0,0,4);
    add_exit(PORT + "seahawk/ba6", "north",0,0,4);
}

