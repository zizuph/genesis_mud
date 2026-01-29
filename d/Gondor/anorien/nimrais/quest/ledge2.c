inherit "/d/Gondor/anorien/nimrais/quest/wall.c";
#include "/d/Gondor/defs.h"
#include <ss_types.h>
#include "dirdefs.h".

#define DOWN_ROOM    "wall2"

create_room()
{
  area = "White Mountains";
  where = "on a narrow ledge high above the ground";
  extraline = "There is no chance to climb any higher from here since above you the " +
    "mountain wall is overhanging. The ledge continues to the east " +
    "and to the west. To the west, however, it seems to become even narrower " +
    "fast until it dwindles out a few yards from here. From where you are standing " +
    "you can make out that the rock wall is unbroken there. If you went there " +
    "you would probably fall down, in which case death would be more " +
    "than a remote possibility! So if you are sane, do not go there! " +
    "A chimney interrupts the rock wall here. ";
  add_item(({"chimney","wall","rock wall"}), BS(
    "A vertical opening interrupts the rock wall here. You might be able to squeeze " +
    "through the opening into the chimney. From where you are standing, you cannot make out " +
    "how far the chimney extends upwards.\n"));
  add_item(({"ledge"}), BSN(
    "The ledge is very narrow here and you can find support only with difficulty. " +
    "To the west, it becomes even narrower, and dwindles out only a few yards " +
    "from here. "));
  down_room = THIS_DIR + DOWN_ROOM;
  make_the_room();
  add_exit(THIS_DIR + "dead_end2", "west", "@@right_ledge", 5);
  add_exit(THIS_DIR + "rledge", "east", "@@left_ledge", 5);
}

right_ledge()
{
  int slip;
  if(TP->query_stat(SS_DIS) < 60)
  {
    write("You look again at the ledge to the west.\n" +
      "It looks rather dangerous to try following it.\n" +
      "You value your life too much to risk going there.\n");
    return 1;
  }
  write("Choosing your steps with great care on the narrow ledge, you follow the ledge to the west.\n");
  slip = random(15);
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

init()
{
  ::init();
  add_action("do_enter","enter");
  add_action("do_enter","squeeze");
}

do_enter(string str)
{
  string vb, s1, s2;

  vb = query_verb();

  if(vb == "enter") NF("Enter what?\n");
  else if(vb == "squeeze") NF("Squeeze through what?\n");

    if (!strlen(str))
        return 0;
  if(sscanf(str,"%s %s",s1,s2) == 2)
  {
    if((s1 == "into" || s1 == "through") && (s2 == "opening" || s2 == "chimney"))
    {
      enter_chimney();
      return 1;
    }
  }
  else if(str == "opening" || str == "chimney")
  {
    enter_chimney();
    return 1;
  }
  return 0;
}

enter_chimney()
{
  write("You squeeze yourself through the narrow opening into the chimney.\n");
  TP->move_living("into the chimney", THIS_DIR + "chimney1", 1);
  return;
}
