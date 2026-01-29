#include "defs.h"
#include <ss_types.h>

CONSTRUCT_ROOM
{
    set_short("In a warm hot stair-case");
    set_long("You are still climbing in a steep stair-case with a hot and " +
	     "damp, red-glowing steam surrounding. Watch out! It is quite " +
	     "slippery here!\n");
    add_item(({"steam", "ground", "air" }),
	     "The steam rises from the ground, heating the air in this place. "+
	     "You wonder what could make so much heat. The steam is so thick "+
	     "the ground is but a blur under (or is it over) your feet.");

    add_item(({"red glow","glow","eerie red glow","vision"}),
	     "The glow seems to echo off the steam like sound, bouncing across "+
	     "your field of vision. It is obviously not natural.");
    
    add_exit(THIS_DIR + "stair2", "down", "@@check_slip|10@@", 3);
    add_exit(THIS_DIR + "stair0", "up", "@@check_slip|50@@", 12);
}

int
check_slip(mixed diff)
{
    diff = atoi(diff);
    if (random(TP->query_skill(SS_CLIMB)) < random(diff)) {
	write("You slip on the stairs!!\n" +
	      "You start sliding down, tumbling into the darkness!!\n");
	say(QCTNAME(TP) + " slips on the stairs!!\n");
	TP->move_living("sliding down the stairs", THIS_DIR + "lair", 1, 1);
	TP->heal_hp(-random(120));
	if (TP->query_hp() <= 0) {
	    write("You land on your neck!!\n");
	    say(QCTNAME(TP) + " lands on " + HIS_HER(TP) + " neck!\n");
	    TP->do_die(TO);
	    return 0;
	}
	write("You survived the fall!\n");
	return 1;
    }
    else {
	write("You almost slip!\n");
	return 0;
    }
}
