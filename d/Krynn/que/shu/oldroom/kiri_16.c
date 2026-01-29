
#include "../local.h"
inherit ATTACKROOM;
#include "/d/Krynn/common/random_meet.h"

object monster;

void
create_attack_room()
{
    set_short("On a grass path in Que Kiri");
    set_long(BS("You are standing in the middle of a grass path"
		+ " within the Que Kiri village. To your east lies a great stone"
		+ " building. From here you can see that it has been painted in"
		+ " bright colors ranging from blue, red, green, and yellow."
		+ " It's color and grandure put the surrounding buildings to"
		+ " shame. Who ever lives there must hold a high ranking"
		+ " within the village.", 70));
    set_change_long(1,BS(BURN_MACA+BURN_MACE+BURN_SCREAMD
			 + "There is a huge pile of melted rocks to your east. "
			 +BURN_SHAPESC,70));
    set_change_long(2,BS(DESTED_MACA+DESTED_MACE+"There is a huge "
			 + "pile of melted rocks to your east. ",70));
    set_change_long(3,BS(RUMMAGE_MACA+RUMMAGE_MACE+"There is a huge "
			 + "pile of rocks to your east. ",70));
    set_change_long(4,BS(BUILD_MACA+BUILD_MACE+"There are a few "
			 + "men cleaning up a huge pile of rocks to your east. ",70));
    
    add_item(({"rocks","rock","pile"}),"@@rock_desc");
    
    OUTSIDE;
    
    add_exit(ROOM + "kiri_17","east");
    add_exit(ROOM + "kiri_25","southwest");
    
}

string
rock_desc()
{
    switch(state_of_room)
      {
	case 0: return "The rock might have been at one time a stone "
	    + "building that would have withstood the tests of time. But "
	    + "some destructive force has destroyed the building.\n";
	case 1: return "The rocks seem partly melted. What fire could " 
	    + "could be hot enough to melt rocks?\n";
       default: return "There are a few pebbles scattered about on the "
            + "ground.\n";

      }
}

int
hook_change_room(int which)
{
    if (which == 0)
      {
	  if (monster)
	    return 0;
	  monster = RANDOM_MEET(TABLE);
	  monster->set_color("red");
	  monster->move_living("xx",TO);
	  return 1;
      }
    if (which == 1)
      if (monster)
	return 0;
    return 1;
}

	  
	  
	  
	  
