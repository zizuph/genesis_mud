
#include "../local.h"
inherit ATTACKROOM;
#include "/d/Krynn/common/random_meet.h"

object monster;

void
create_attack_room()
{
    set_short("Temple of the Ancestors");
    set_long(BS("Theres not much on this side of the temple other"
      + " then a stone bench for people to sit and relax on. Looking"
      + " out through the stone columns you see Que Kiri people"
      + " working and going about their daily routines. The peace"
      + " and calm of the image reminds you of your own home"
      + " bringing on a small feeling of homesickness.", 70)); 

    OUTSIDE;

    add_exit(ROOM + "kiri_47","east");

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

