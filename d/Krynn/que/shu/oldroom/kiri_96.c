
#include "../local.h"
inherit ATTACKROOM;
#include "/d/Krynn/common/random_meet.h"

object monster;

void
create_attack_room()
{
    set_short("On grass path in Que Kiri");
    set_long(BS("You stand on a grass path near a stone building"
      + " used for storing animal hides. You remember seeing hides"
      + " such as the ones here being sold in some of the finer shops"
      + " of Solace. The path leads northeast towards the center"
      + " of the village and also to the southwest where"
      + " you can spot some tents and huts.", 70)); 

    OUTSIDE;

    add_exit(ROOM + "kiri_87","northeast");
    add_exit(ROOM + "kiri_a5","southwest");

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

