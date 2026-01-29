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
    "mountain wall is overhanging. The ledge continues to the east " +
    "and the west. You can climb down here. ";
  add_item(({"ledge"}), BSN(
    "The ledge continues to the east and the west. To the west, however, " +
    "it seems to become narrower fast and it is dubious whether you would " +
    "find hold there. "));
  down_room = THIS_DIR + DOWN_ROOM;
  make_the_room();
  add_exit(THIS_DIR + "rledge", "west", "@@right_ledge", 5);
  add_exit(THIS_DIR + "lledge", "east", "@@left_ledge", 5);
}

right_ledge()
{
  int slip;
  if(TP->query_stat(SS_DIS) < 40)
  {
    write("You look again at the ledge to the west.\n" +
      "It looks rather dangerous to try following it.\n" +
      "You value your life too much to risk going there.\n");
    return 1;
  }
  write("Choosing your steps with great care on the narrow ledge, you follow the ledge to the west.\n");
  slip = random(15);
  write("Your hold on the ledge is precarious. Only the tips of your toes are supported.\n");
  if(calc_cap()  < 50 + slip)
  {
    write("\nSuddenly, you slip.\n\nDesperately you try to find a hold again...\n\n" +
      " ... and just barely and with much luck manage to keep your balance, " +
      "\nescaping a fall that probably would have been lethal.\n\n");
  }
  return 0;
}

left_ledge()
{
  int slip;
  slip = random(10);
  write("Staying close to the wall, you slowly move to the east on the ledge.\n");
  if(calc_cap() < 50 + slip)
  {
    write("\nSuddenly, you slip.\n\nDesperately you try to find a hold again...\n\n" +
      " ... and just barely and with much luck manage to keep your balance, " +
      "\nescaping a fall that probably would have been lethal.\n\n");
  }
  return 0;
}
