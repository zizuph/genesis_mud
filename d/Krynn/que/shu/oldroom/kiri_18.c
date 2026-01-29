
#include "../local.h"
inherit ATTACKROOM;
#include "/d/Krynn/common/random_meet.h"

object monster;

void
create_attack_room()
{
    set_short("On a grass path in Que Kiri");
    set_long(BS("You are standing in the middle of a grass path"
      + " within the Que Kiri village. To your west lies a great stone"
      + " building. From here you can see that it has been painted in"
      + " bright colors ranging from blue, red, green, and yellow."
      + " It's color and grandure put the surrounding buildings to"
      + " shame. Who ever lives there must hold a high ranking"
      + " within the village.", 70));
  set_change_long(1,BS(BURN_MACF+BURN_MACE+BURN_SCREAMB
    + "To your west is a huge pile of melted rock. "
    +BURN_SHAPESA,70));

    OUTSIDE;

    add_exit(ROOM + "kiri_17","west");
    add_exit(ROOM + "kiri_29","southeast");

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

