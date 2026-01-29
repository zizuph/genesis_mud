inherit "/d/Gondor/anorien/nimrais/quest/wall.c";
#include "/d/Gondor/defs.h"
#include <ss_types.h>
#include "dirdefs.h".

#define DOWN_ROOM    "wall2"

create_room()
{
  area = "White Mountains";
  where = "a narrow ledge high above the ground";
  extraline = "There is no chance to climb any higher from here since above you the " +
    "mountain wall is overhanging. The ledge seems to continue to the east. " +
    "To the west, though, it ends abruptly less than " +
    "a foot from where you are standing. A single step in that direction, " +
    "and you will fall down, quite probably to your death! ";
  add_item(({"ledge"}), BSN(
    "The ledge is extremely narrow here, and you can just barely " +
    "find support for your toes on it. To the west, it ends " +
    "abruptly only a few feet from where you are standing. "));
  down_room = THIS_DIR + DOWN_ROOM;
  make_the_room();
  add_exit(THIS_DIR + "dead_end2", "west", "@@right_ledge", 5);
  add_exit(THIS_DIR + "ledge2", "east", "@@left_ledge", 5);
}

right_ledge()
{
  if(TP->query_stat(SS_DIS) < 80)
  {
    write("You look again at the ledge ending less than one foot to your right.\n" +
      "It is impossilbe to find any hold there.\n" +
      "You value your life too much to risk going there.\n");
    return 1;
  }
  write("You try to follow the ledge to the right.\n");
  write("But since the ledge ends there, you cannot find any foothold.\n");
  write("\nIn vain you try to cling to the sheer, vertical rock face.\n");
  if(random(2))
  {
    write("\nBut then, finally, you slip.\n\nDesperately you try to find a hold again...\n\n" +
      " ... but you fail.\n\n");
    do_fall(TP,0);
  }
  else
  {
    write("\nSuddenly, you slip.\n\nDesperately you try to find a hold again...\n\n" +
      " ... and with incredible luck you manage to return to the end of the ledge, " +
      "\nescaping a fall that probably would have been lethal.\n\n");
  }
  return 1;
}

left_ledge()
{
  write("Staying close to the wall, you slowly move to the east on the ledge.\n");
  return 0;
}
int
climb(string str)
{
  NF("Climb what?\n");
  if (str == "up")
  {
    write("You cannot climb up here.\n");
    return 1;
  }
  else if (str == "down")
  {
    write("You cannot climb down here.\n");
    return 1;
  }
  return 0;
}
