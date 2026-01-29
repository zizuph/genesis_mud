/**********************************************************************
 * -  Removed boat information that was here to Emerald.            - *
 * -  Not sure when boat had orginally been removed. Damaris 5/2004 - *
 **********************************************************************/

#include "default.h"
inherit PORT_ROOM;

#include <ss_types.h>
#define HARD_TO_MOVE 10
#define DAMAGE 50
string long;

void
create_port_room()
{
    add_prop(ROOM_NO_TIME_DESC,1);

    set_short("Small Pier");
    set_long("You are standing at the end of a small wooden pier that "+
      "sticks out into the bay. Further north rises a massive cliff. The "+
      "wooden planks of the pier seem to creak and groan with the slightest "+
      "movement and the sound of water lapping gently against the supports "+
      "enshrouds your senses. A rocky path lies to the northwest.\n");
    add_item(({"bay"}),"A beautiful expanse of water that sparkles with "+
      "an azure color.\n");
    add_item(({"massive cliff","cliff"}),"A towering edifice of rock, "+
      "the southern edge of a large plateau.\n");
    add_item(({"wooden planks","planks","wooden plank","plank"}),"Although "+
      "they groan and creak with your every movement, the weather-beaten "+
      "wood seems sturdy enough.\n");
    add_item(({"water"}),"It fills the bay.\n");
    add_item(({"supports","support"}),"Large wooden logs that hold the pier "+
      "above the water line.\n");
    add_item(({"large sign","sign"}),"There is lots of legible writing on "+
      "it, maybe you should read it.\n");
    add_item(({"rocky path","path"}),"It lies at the base of the massive "+
      "cliff, strewn with rocks and slick with fresh seawater. A relatively "+
      "small gap seperates it from the pier.\n");
    add_item(({"rocks","rock"}),"You're too far away to get a good look "+
      "at them.\n");
    add_exit(PORT + "shipline/path3","northwest", "@@move");
    add_exit(PORT + "s2", "east");

}

int
move()
{
    if(TP->query_skill(SS_SWIM) < random(HARD_TO_MOVE))
    {
	write("You start running, preparing yourself for a jump...\n");
	write("You stop abruptly and fall forward, hurting yourself on the "+
	  "wooden planks of the pier.\n");
	TP->heal_hp(-DAMAGE);
	say(QCTNAME(TP) + " starts running, preparing " + TP->query_objective() +
	  "self for a jump...\n");
	say(QCTNAME(TP) + " stops abruptly and falls forward, hurting " + TP->query_objective() + "self on the wooden planks of the pier.\n");
	if(TP->query_hp() <= 0)
	    TP->do_die(TO);
	return 1;
    }

    write("You make a running leap and jump across the gap!\n");
    return 0;
}

