#include "../default.h"
inherit PORT_ROOM;

object ob1;

void
create_port_room()
{
    set_short("Extremely dark and bleak room");
    set_long("This room is the darkest and bleakest area of the prison. "+
      "Not a trace of light filters into this room, so bleak and miserable "+
      "is its atmosphere, that it would seem light recoils from this "+
      "place as one would recoil from a nightmare. The cell's rotten walls bear "+
      "testament to the horrid conditions present in this jail.\n");
    add_item(({"room","jail","prison","cell","brig"}),"Putrid filth lies all "+
      "over the room, blanketing everything in its disgusting embrace, "+
      "filling the air with its poison, and making you feel sick to the "+
      "stomach.\n");
    add_item(({"rotten walls","walls","wall"}),"As if the filth lying about "+
      "the room were not torture enough, the sides of this area of the cell "+
      "look as if they may break at any moment, sending a torrent of water "+
      "into the cell, and slowly drowning anyone unfortunate enough to be "+
      "here.\n");
    add_item(({"filth"}),"Multiple layers of human feces along with rat feces "+
      "and spilled meals covers the room.\n");

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,0);

    add_exit(PORT + "seahawk/ba9", "north",0,4);
    add_exit(PORT + "seahawk/ba7", "east",0,4);

    reset_room();
}

reset_room()
{
    if(!ob1)
    {
	ob1 = clone_object(PORT + "npc/prisoner");
	ob1 -> move_living("xxx",TO);
    }
}

