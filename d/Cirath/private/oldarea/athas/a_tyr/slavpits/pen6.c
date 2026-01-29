inherit "std/room";
#include "/d/Roke/common/defs.h"
#include <stdproperties.h>

void
create_room()
{
	set_short("Slave pits of Tyr");
	set_long("You have entered the more dangerous parts "+
	   "of the slave pits. Here is where the king keeps "+
	   "his better slaves to fight against the gladiators. "+
	   "To the west is a large portcullis to keep the "+
	   "slaves from escaping. To the north and south are "+
	   "open cells that house slaves. To the east the hallway "+
	   "continues.\n");

   add_item(({"portcullis","gate","west"}),"The portcullis "+
	   "is down and, unfortunately, locked too strong for you to "+
	   "force open. To get out you will have to bang on it and "+
	   "hope the guard realizes you aren't a slave.\n");

	add_item(({"cells", "cell"}),"Even though the cells are "+
	   "dimly lit, you can tell they are quite dirty. They house "+
	   "the more dangerous slaves, destined to fight gladiators "+
	   "in the arena. Most of them used to be criminals or "+
	   "enemies of the crown and were sentenced to a life of "+
	   "slavery.\n");

	LIGHT

	add_exit(PEN_DIR+"pen5.c", "west", "@@gate");
	add_exit(PEN_DIR+"pen1.c", "north");
	add_exit(PEN_DIR+"pen7.c", "east");
	add_exit(PEN_DIR+"pen10.c", "south");
}
gate()
{
	write("Your way is blocked by a heavy portcullis. If only "+
	 "you were about six centimeters wide, you could go through it.\n");
   return 1;
}
