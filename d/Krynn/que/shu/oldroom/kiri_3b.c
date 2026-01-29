
#include "../local.h"
inherit ATTACKROOM;
#include "/d/Krynn/common/random_meet.h"

object monster;

void
create_attack_room()
{
    set_short("Village Hall");
    set_long(BS("You manage to squeeze yourself past the"
     + " throng of people outside and make your way into the hall."
     + " The room is packed with people, mostly women and older men."
     + " At the head of the room are three Que Kiri elders dressed"
     + " in formal leather outfits. They seem to be talking to people"
     + " in front of the room, but your to far back to hear what"
     + " is being said. Perhaps you could ask someone what is going"
     + " on?", 70));

    OUTSIDE;

    add_exit(ROOM + "kiri_4b","out");

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

