/* created by Aridor 03/09/94 */

#include "../local.h"

inherit ROOM_BASE

/* DIR1 leads out of the mountain, DIR2 into it */
#define DIR1  "northeast"
#define DIR2  "south"

object dwarf;

void
create_thief_room()
{
  set_short("In a cavern");
  set_long("@@my_long");
  
  add_exit(THEIWAR + "r3",DIR1);
  add_exit(THEIWAR + "r5",DIR2);
  add_exit(THEIWAR + "r25","up");

  DARK;
}


string
my_long()
{
    string str = "This is a normal hallway leading "+DIR1+" and "+DIR2+". There " +
      "is an inclined plane leading upwards into a higher level from here, " +
      "allowing goods and heavier objects to be transported upwards as well.\n";
    if (TP->query_race() == "dwarf")
      return "You notice excellent craftmanship here in these halls. " +
	"Only the best dwarven craftsmen were able to produce this  " +
	"fine, even and balanced work. " + str;
    return str;
}
