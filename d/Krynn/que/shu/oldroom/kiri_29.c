
#include "../local.h"
inherit ATTACKROOM;
#include "/d/Krynn/common/random_meet.h"

object monster;

void
create_attack_room()
{
    set_short("On a grass path in Que Kiri");
    set_long(BS("You are standing in the middle of a grass path"
      + " within the Que Kiri village. Around you are the stone"
      + " houses of the village's council elders. The fact that they"
      + " live in stone structures atones to their importance within"
      + " the community. Further north you spot a rather imposing stone"
      + " building.", 70));
  set_change_long(1,BS(BURN_MACD+BURN_MACL+BURN_SCREAMF
     + "Piles of rubble now sit where the houses of the council "
     + "once stood. "+BURN_SHAPESG,70));

    OUTSIDE;

    add_exit(ROOM + "kiri_18","northwest");
    add_exit(ROOM + "kiri_3a","southeast");

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

