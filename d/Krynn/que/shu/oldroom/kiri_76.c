
#include "../local.h"
inherit ATTACKROOM;
#include "/d/Krynn/common/random_meet.h"

object monster;

void
create_attack_room()
{
    set_short("West arena steps");
    set_long(BS("You stand on the west side of a massive arena."
      + " The arena is circular in shape with great stone steps"
      + " surrounding a sunken grassy center. The arena appears"
      + " large enough to seat the entire population of the village."
      + " As a small breeze picks up you can almost here the the"
      + " cheers and yells of past victories and defeats that"
      + " have occured within this very arena.",70 ));

    OUTSIDE;

    add_exit(ROOM + "kiri_65","northwest");
    add_exit(ROOM + "kiri_77","east");
    
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

