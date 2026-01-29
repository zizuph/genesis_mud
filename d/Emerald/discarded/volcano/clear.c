// connects path from mount black to the volcano
//Emerald/mountains/volcano/clear.c
// checks for climb skill to get up the volcano here
// skill must equal 35 
// also connects to the pier area ( to the west)

inherit "/std/room";
#include "/d/Emerald/defs.h"

create_room()
{
    set_short("Clearing");
    set_long("   You stand just off the edge of the forest. As you look "+
      "up in the sky, you can see the side of a large volcano, not the " +
      "mountain you originally thought it to be. It looks steep but "+
      "climbable with a certain amount of skill. You notice that over "+
      "the top of the volcano, smoke looms in the air.\n\n");

    add_exit(MBLACK_DIR + "road09", "south", 0,1);
    add_exit(VOL + "pier1.c", "west");
}

climb()
{
    if(TP->query_skill(SS_CLIMB) < random(35))
    {
	write("You try to climb up the side of the volcano but your feet loose their grip and you slip and fall.\n");
	write("It hurts slightly as you hit the groupd with a thump.\n");
	TP->reduce_hit_point(7);
	say(QCTNAME(TP + " looses their footing and falls back down the side of the volcano\n"));
	return 1;
    }
    write("There is still too much rubble on the side of the volcano.  You might try again some other day.\n");
    return 1;

    /*
    * This exit is closed until the volcano is ready to open.
    write("You scramble up the side of the volcano.\n");
    */
}
