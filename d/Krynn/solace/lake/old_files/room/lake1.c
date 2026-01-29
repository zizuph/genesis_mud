/*   Crystalmir -  Lakeside Road #1 
     Splunge - Krynn  Jan. 20, 1994  */
 
#include "../local.h"

inherit SWIM_ROOM;

void
create_swim_room() 
{
    set_long("You are walking on a dirt road that follows alongside " +
	     "Crystalmir Lake.  The sounds of the water and the sights " +
	     "of mountains and wilderness soothe your soul, and set your " +
	     "mind at ease.  For an area rumored to be under the red dragon " +
	     "army's control, this seems pretty tame.\n");
    add_item("road",
	     "This rough dirt road follows alongside Crystalmir Lake. It " +
	     "seems like there has been a lot of traffic through here " +
	     "recently.\n");
    add_item("mountains",
	     "The mountains on the other side of the lake look majestic and " +
	     "inspiring. You sigh deeply, hoping beyond hope to LIVE to " +
	     "visit them some day.\n");
    add_item("wilderness",
	     "Just kidding about the wilderness soothing your soul. This " +
	     "place gives you the creeps. It's dark and nasty. The woods " +
	     "to the east of you seem to have eyes, and you walk along " +
	     "the path with your guard up.\n");
    add_exit(ROOM + "lake2","north",0);
    add_exit(NEAR_PIER, "south");
}

int
block()
{
    write("The tree village Solace is under attack by dragons and " +
	  "draconians. The wizards of Krynn, has yet again, gone into " +
	  "battle to defend their creation. The battle will go on for " +
	  "several hours, since the wizards are few and the dragons are " +
	  "many. The only thing you can do is to pray to the gods and " +
	  "give them all the support you can.\n");
    return 1;
}

