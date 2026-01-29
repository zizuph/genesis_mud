
#include "../local.h"

inherit SOLACE_ROOM_BASE;

object mino1;

void
reset_solace_room()
{
    if (mino1)
      return;
    mino1=clone_object(LIV + "minotaur3.c");
    mino1->move_living("xxx",TO);
}
 
void
create_solace_room() 
{
    set_short("Camp Entrance");
    set_long("You wade through the tall grass, following hints of passage: " +
	     "broken twigs and even a footprint or two. Before you know it, " +
	     "you have stumbled onto an encampment. At least you think " +
	     "it's an encampment, due to the amount of noise coming from " +
	     "the east.\n");
    add_item("encampment",
	     "There is smoke rising to your east, and there is a small " +
	     "path through the trees leading towards it.\n");
    add_item(({"twig","stick","footprint","twigs","sticks"}),
	     "The trail has lead you to the edge of an enemy camp!\n");
    add_item("grass",
	     "The grass is tall and green.");
    add_exit(ROOM + "lake11","west",0,3);
    add_exit(ROOM + "campfire","east","@@check_mino",3);
    add_exit(ROOM + "woods_n","northeast","@@check_mino",3);
    add_exit(ROOM + "woods_s","southeast","@@check_mino",3);
    reset_room();
}

int
check_mino()
{
    if (mino1 && CAN_SEE(mino1, TP)) 
      write("The minotaur stops you from going that way!\n");
    else
      return 0;
    return 1;
}
