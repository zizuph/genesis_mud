
#include "../local.h"
inherit ATTACKROOM;
#include "/d/Krynn/common/random_meet.h"

object monster;

void
create_attack_room()
{
    set_short("On a gravel path in Que Kiri");
    set_long(BS("You stand among some of the few stone buildings"
      + " of the village. Most of them seem to house stored food"
      + " or grain probably aquired through hunting or trading with"
      + " neighboring villages or towns. To the north you spot what"
      + " appears to be a great arena. While to your south the gravel"
      + " path leads to the entrance of the village.", 70)); 

    OUTSIDE;

    add_exit(ROOM + "kiri_87","north");
    add_exit(ROOM + "kiri_a7","south");

}

int
hook_change_room(int which)
{
    if (which == 0)
      {
	  if (monster)
	    return 0;
	  monster = RANDOM_MEET(TABLE);
	  monster->move_living("xx",TO);
	  return 1;
      }
    if (which == 1)
      if (monster)
	return 0;
    return 1;
}

