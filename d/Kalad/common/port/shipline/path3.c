#include "../default.h"
inherit PORT_ROOM;

#include <ss_types.h>
#define REQUIRED_MOVE_LEVEL 30
#define DAMAGE 75
string long;

void
create_port_room()
{
    add_prop(ROOM_NO_TIME_DESC,1);

    set_short("Path");
    set_long("This is a narrow and rocky path leading along the base of "+
      "a huge cliff, which towers above you in the north. The weatherbeaten "+
      "path travels through a massive stone arch in the west, while to your "+
      "southeast is a small wooden pier, and beyond that, a bustling port.\n");
    add_item(({"narrow rocky path","narrow path","rocky path","path","weatherbeaten path"}),
      "Strewn with rocks and slippery from the crashing waves of water, the "+
      "rocky pathway looks treacherous.\n");
    add_item(({"huge cliff","cliff"}),"A sheer rock face that rises hundreds "+
      "of feet above you, apparently just one edge of a gigantic plateau.\n");
    add_item(({"rocks","rock"}),"Sharp grey stones that have fallen from "+
      "the cliff or have been eroded by the breaking of the waves.\n");
    add_item(({"massive stone arch","massive arch","stone arch","arch"}),
      "A large rock formation here at the base of the cliff. Years of "+
      "constant erosion from wind and water have created a U-shaped arch of "+
      "rock that blocks your field of view in the west. However, the rocky "+
      "path travels through the arch, continuing west.\n");
    add_item(({"small wooden pier","small pier","wooden pier","pier"}),
      "A squat wooden pier that sticks out into the bay, marring its "+
      "beauty. A relatively small gap seperates it from the rocky path you "+
      "are standing on.\n");
    add_item(({"bay"}),"A sparkling vista of water that spreads out to "+
      "the south.\n");
    add_item(({"bustling port","port"}),"A large port area, filled with "+
      "many wooden buildings and ships bound for far off lands.\n");
    add_item(({"wooden buildings","buildings","building"}),"Large wooden "+
      "structures. From this distance, little detail can be made out.\n");
    add_item(({"ships","ship"}),"You're too far away to see anything "+
      "about them.\n");
    add_exit(PORT + "shipline/path2", "west");
    add_exit(PORT + "s1","southeast","@@move",-1);
}

move()
{
    int my_level;

    my_level = TP->query_skill(SS_ACROBAT) +
    TP->query_stat(SS_DEX);
    if (my_level < random(REQUIRED_MOVE_LEVEL))
    {
	write("You start running, preparing yourself for a jump...\n");
	write("You stop abruptly and fall forward, hurting yourself on the "+
	  "rocks of the path.\n");
	TP->heal_hp(-DAMAGE);
	say(QCTNAME(TP) + " starts running, preparing " + TP->query_objective() + "self for a jump...\n");
	say(QCTNAME(TP) + " stops abruptly and falls forward, hurting " + TP->query_objective() + "self on the rocks of the path.\n");
	if(TP->query_hp() <= 0)
	    TP->do_die(TO);
	return 1;
    }

    write("You make a running leap and jump across the gap!\n");
    return 0;
}

