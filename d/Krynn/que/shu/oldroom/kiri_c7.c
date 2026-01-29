
#include "../local.h"
inherit ATTACKROOM;
#include "/d/Krynn/common/random_meet.h"

object monster;

void
create_attack_room()
{
    set_short("On a gravel path in Que Kiri");
    set_long(BS("As you walk along the gravel path you notice"
      + " the great wall encircles the entire village. The only"
      + " exit out onto the plains is the main entrance through which" 
      + " you came from. After listening to the stories of large"
      + " armies roaming these plains you begin to wonder how"
      + " well such a wall would stand up to an orgainized body of"
      + " troops. These thoughts slip from your mind as the"
      + " activity of the villagers makes you forget your worries.", 70)); 

    OUTSIDE;

    add_exit(ROOM + "kiri_b7","north");
    add_exit(ROOM + "kiri_d7","south");

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

