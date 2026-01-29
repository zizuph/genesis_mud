/*
 * /d/Rhovanion/common/rhun/camp/testdis.c
 *
 * A room to check if a player has high enough DIS
 * to enter the barbarian camp.
 */

inherit "/d/Rhovanion/common/rhun/camp/room";

#include <ss_types.h>
#include "/d/Rhovanion/defs.h"

#define MIN_DIS_LEVEL 80

void
create_camp()
{
  set_long("This is entrance to the evil camp. You notice there are " +
           "several guards to the north! They look pretty mean. They " +
           "also look like they will kill anyone who comes near. It " +
           "would probably be wise to turn back while you can.\n");
  set_short("The entrance to the camp");
  add_exit(CAMP_DIR + "guardpost", "north", "@@test_dis");
}

/*
 * Function name: test_dis
 * Description:   Tests if the player's DIS is >= MIN_DIS_LEVEL. 
 *                If not, he won't be able to enter the camp. Used 
 *                from add_exit in create_camp above.
 * Arguments:     (none)
 * Returns:       0 if it's ok to move, 1 if not.
 */

int
test_dis()
{
    if (TP->query_stat(SS_DIS) >= MIN_DIS_LEVEL)
    {
	write("This place gives you the creeps, but you bravely " +
	      "continue.\n");
	return 0;
    }

    write("Umm... No, it looks too dangerous.\n");
    return 1;
}



