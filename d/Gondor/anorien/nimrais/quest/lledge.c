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
    "mountain wall is overhanging. The ledge seems to continue to the east " +
    "and the west. To the east, though, it seems to become narrower " +
    "fast and it is dubious whether you would find hold there. If you were fool " +
    "enough to try continuing on this ledge to the east, you certainly " +
    "would need much more luck than you needed to come here  ...  and a " +
    "death wish! ";
    
  add_item(({"ledge"}), BSN(
    "The ledge is rather small here, and it doesn't give you much support. " +
    "To the east, it grows even smaller. "));
  down_room = THIS_DIR + DOWN_ROOM;
  make_the_room();
  add_exit(THIS_DIR + "ledge1", "west", "@@right_ledge", 5);
  add_exit(THIS_DIR + "dead_end", "east", "@@left_ledge", 5);
}

left_ledge()
{
  int slip;
  if(TP->query_stat(SS_DIS) < 60)
  {
    write("You look again at the ledge to the east.\n" +
      "It looks rather dangerous to try following it.\n" +
      "You value your life too much to risk going there.\n");
    return 1;
  }
  write("Choosing your steps with great care on the narrow ledge, you follow the ledge to the east.\n");
  slip = random(30);
  write("Your hold on the ledge is precarious. Only the tips of your toes are supported.\n");
  if(calc_cap() >= 80 + slip)
    return 0;
  write("\nSuddenly, you slip.\n\nDesperately you try to find a hold again...\n\n" +
    " ... clinging to the sheer rock wall ... \n\n" +
    " ... you are fighting for your life ... \n\n" +
    " ... now you start losing the hold with the other foot, too ... \n\n" +
    " ... the ledge is simply too narrow ... \n\n" +
    " ... why didn't you believe your eyes when you saw that it is not possible to climb here ... \n\n" +
    " ... finally, after a long struggle ... \n\n");
  if(calc_cap() < 25 + slip)
  {
    write(" ... you finally lose your last hold.\n\n");
    do_fall(TP,0);
    return 1;
  }
  else
  {
    write(" ... you just barely and with luck manage to find a foot hold again ... \n\n" +
      " ... escaping from a deep fall and certain death!\n\n");
  }
  return 0;
}

right_ledge()
{
  write("Staying close to the wall, you slowly move to the west on the ledge.\n");
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
