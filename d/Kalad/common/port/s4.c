#include "default.h"
inherit PORT_ROOM;

#include "/sys/ss_types.h"
#define HARD_TO_MOVE 10
#define DAMAGE 5
string long;

void
create_port_room()
{
    set_short("Street Corner");
    set_long("You find yourself at the base of a huge cliff that towers "+
      "far above you to the north, and continues east and west into the "+
      "distance. You are travelling along a narrow street along the base of "+
      "the cliff. The road turns here and heads south towards the harbor "+
      "and east further into the district. West from here is a small wooden "+
      "pier. The cobblestones beneath you are moist and covered with "+
      "greenish grime. To the southeast is a large wooden building.\n");
    add_item(({"base","huge cliff","cliff"}),"The sheer rock walls of the "+
      "cliff look extremely hard, if not impossible to climb.\n");
    add_item(({"narrow street","street"}),"A small cobblestoned roadway at the "+
      "base of the cliff.\n");
    add_item(({"cobblestones","cobblestone"}),"The pavement is worn and cracked, "+
      "and seems to be covered in a thin film of moisture.\n");
    add_item(({"greenish grime","grime"}),"Rootless plants, such as moss "+
      "and lichen cover the pavement, apparently sustained by the constant "+
      "amount of water present.\n");
    add_item(({"large wooden building","large building","wooden building","building"}),
      "A rather large structure made out of hardwood planks. It is most "+
      "likely some sort of warehouse.\n");
    add_item(({"small wooden pier","small pier","wooden pier","pier"}),
      "A place where a ship might dock, by the small size of it, the "+
      "connecting location must not be often travelled to.\n");
    add_exit(PORT + "s3", "west","@@move");
    add_exit(PORT + "s20", "south");
    add_exit(PORT + "s5", "east");
}

move()
{
    if(TP->query_skill(SS_SWIM) < random(HARD_TO_MOVE))
    {
	write("You fearfully step onto the pier...\n");
	write("You stumble backwards and hurt yourself for fear of falling off!\n");
	TP->heal_hp(-DAMAGE);
	say(QCTNAME(TP) + " stumbles backwards and gets hurt for fear of falling off the pier!\n");
	if(TP->query_hp() <= 0)
	    TP->do_die(TO);
	return 1;
    }

    write("You bravely step onto the pier.\n");
    return 0;
}

