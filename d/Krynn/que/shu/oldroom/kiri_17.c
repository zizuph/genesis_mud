
#include "../local.h"
inherit ATTACKROOM;
#include "/d/Krynn/common/random_meet.h"

object monster;

void
create_attack_room()
{
    set_short("On a grass path in Que Kiri");
    set_long(BS("You stand before the High Chieftain's home."
     + " The color and size of the building marks it of one being"
     + " inhabatited by a person of importance. Two armed warriors"
     + " stand by the building's entrance, ready to stop anyone"
     + " attempting to see the chieftain unannounced.", 70));
  set_change_long(1,BS(BURN_MACB+BURN_MACL+BURN_SCREAMA
    + "There is a large pile of melted rock here. It would seem " 
    + "pointless to examine it further. Nothing could have "
    + "survived the heat it would have taken to melt that rock."
    + " "+BURN_SHAPESE,70));

    OUTSIDE;

    add_exit(ROOM + "kiri_18","east");
    add_exit(ROOM + "kiri_16","west");

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

