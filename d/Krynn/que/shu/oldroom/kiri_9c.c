
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
      + " tents and huts of the Que Kiri people. You can hear the cry"
      + " of a baby coming from one of the tents, wanting to be fed."
      + " While the smell of roasting gazelle starts to make your."
      + " mouth water, and you remember that its been some time"
      + " since you've eaten as well.", 70)); 

    OUTSIDE;

    add_exit(ROOM + "kiri_8d","northeast");
    add_exit(ROOM + "kiri_ab","southwest");

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

