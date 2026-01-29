/* created by Aridor 03/09/94 */

#include "../local.h"

inherit ROOM_BASE

/* DIR1 leads out of the mountain, DIR2 and DIR3 into it */
#define DIR1  "north"
#define DIR2  "southwest"
#define DIR3  "east"


void
create_thief_room()
{
  set_short("In a cavern");
  set_long("@@my_long");
  
  add_exit(THEIWAR + "r2",DIR1);
  add_exit(THEIWAR + "r4",DIR2);
  add_exit(THEIWAR + "r10",DIR3);

  DARK;
}


string
my_long()
{
  if (TP->query_race() == "dwarf")
    return "You notice excellent craftmanship here in these halls. " +
      "Only the best dwarven craftsmen were able to produce this  " +
      "fine, even and balanced work. You notice a ever so slight " +
      "dropping of the floor towards the "+DIR2+" and "+DIR3+" of the hall, indicating " +
      "that the exit to the "+DIR2+" and "+DIR3+" will lead further into the mountain, " +
      "whereas the "+DIR1+" exit will eventually lead to the dreaded " +
      "outside.\n";
  return "This is a normal hallway leading "+DIR1+", "+DIR2+" and "+DIR3+". You are " +
    "positive that this must be dwarven work, cutting into the hard " +
    "rock like this.\n";
}
