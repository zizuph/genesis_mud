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
    set_long("You are travelling along a street which borders the bay. "+
      "The road bends here and heads north and west. The moist cobblestones "+
      "beneath you are covered with grime. The beautiful bay spreads out "+
      "to your east and south, its beauty marred only by the squat pier "+
      "jutting out to the east. Along the pier is a small building. Another "+
      "structure, a large building, lies to your northwest.\n");
    add_item(({"street","road"}),"A cobblestoned roadway that winds its "+
      "way through the district.\n");
    add_item(({"moist cobblestones","cobblestones","moist cobblestone","cobblestone"}),
      "The pavement is covered with a green-colored grime.\n");
    add_item(({"green-colored grime","grime"}),"Moss, lichen and other rootless "+
      "plants cover the cobblestones.\n");
    add_item(({"beautiful bay","bay"}),"Colored a deep azure, its beauty "+
      "is matched only by the skies above.\n");
    add_item(({"skies","sky"}),"It mirrors the bay below.\n");
    add_item(({"squat pier","pier"}),"A small pier where ships might "+
      "land.\n");
    add_item(({"large building","structure"}),"A large structure built "+
      "out of hardwood planks. It looks like a warehouse.\n");
    add_item(({"small building"}),"A small wooden structure "+
      "built from hardwood planks. From here its hard to discern what purpose "+
      "it serves.\n");
    add_item(({"building"}),"Which building?\n");
    add_exit(PORT + "s77", "west");
    add_exit(PORT + "s65", "north");
    add_exit(PORT + "s79", "east","@@move");
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

