
#include "../local.h"
inherit ATTACKROOM;
#include "/d/Krynn/common/random_meet.h"

object monster;

void
create_attack_room()
{
    set_short("On a grass path in Que Kiri");
    set_long(BS("You are standing in the middle of a grass path"
      + " within the Que Kiri village. Scattered around you are the"
      + " tents and huts of the Que Kiri people. As you walk among"
      + " the villagers, your surprised at how open and friendly"
      + " they are towards you. The women wave and smile, while the"
      + " children come up and hold your hand as if they had known"
      + " you for some time.", 70)); 

    OUTSIDE;

    add_exit(ROOM + "kiri_9c","northeast");
    add_exit(ROOM + "kiri_ba","southwest");

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

