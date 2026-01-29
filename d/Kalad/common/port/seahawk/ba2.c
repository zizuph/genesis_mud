#include "../default.h"
inherit PORT_ROOM;

string long;

void
create_port_room()
{
    set_short("This is the dark, dismal bottom of the ship");
    set_long("This is the dark, dismal bottom level of the ship. Greenish "+
      "mold clings to the walls and refuse is littered across the floor. "+
      "Side rooms seem to lie just to the north and south.\n");
    add_item(({"greenish mold","mold"}),"A sticky green substance that "+
      "is plastered all over the walls of this corridor.\n");
    add_item(({"walls","wall","corridor"}),"This narrow passageway continues "+
      "towards the west and east, while side rooms lead to the north and "+
      "south.\n");
    add_item(({"refuse"}),"A variety of discarded trash lies about the floor, "+
      "among the debris you can see useless pieces of wood, broken glass "+
      "and torn cloth.\n");
    add_item(({"useless wood","wood"}),"Its rotten completely through "+
      "and is totally worthless.\n");
    add_item(({"broken glass","glass"}),"It is scattered amongst the "+
      "other refuse, making you watch your footing to avoid cutting "+
      "yourself.\n");
    add_item(({"torn cloth","cloth"}),"It looks to have once been clothing "+
      "of some sort, now however, it is just a worthless pile of rags.\n");
    add_item(({"floor"}),"The floor is littered with refuse and is "+
      "in great need of repair.\n");
    add_item(({"side rooms","rooms","room"}),"They lies off of this "+
      "corridor on either side.\n");

    add_prop(ROOM_I_INSIDE,1);

    add_exit(PORT + "seahawk/ba3", "north",0,0,4);
    add_exit(PORT + "seahawk/ba1", "east",0,0,4);
    add_exit(PORT + "seahawk/ba4", "south",0,0,4);

    clone_object(PORT + "seahawk/door2")->move(TO);
}

void
init()
{
    ::init();
    write("You smell something rotten in the air.\n");
}

