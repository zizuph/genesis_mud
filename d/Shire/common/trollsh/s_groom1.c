inherit "/d/Shire/common/lib/room";

#include <stdproperties.h>
#include "/d/Shire/common/defs.h"

object troll;

create_room()
{
   set_short("Side room");
	set_long(
		"You have come into a smelly stinking room south of the big hall. "
		+"The place is filled with dirt and the floor is stained with blood. "
		+"Scattered around this place lay pieces of broken bones and skulls "
		+"which look like they have been here for a long time. There are "
		+"traces from combat here, as there is guts hanging on the wall, not yet "
		+"dried. By the southern wall there is a big chair, carved out in rock.\n");
	
	add_item("chair", "The chair is rather large of size, much bigger then what would be fit "
			+"for humans. Apparently some powerful creature uses this room, as there "
			+"are no guards in here.\n");
	
	add_item("room","This is a smelly room.\n");
	
	add_item("dirt", "Dirt covers the floor, and it is easy to see that those who live here does not "
			+"care for cleaning this place.\n");
			
	add_item("blood", "There are blood all over this place. Obviously there have been lots of fighting "
			+"in here.\n");
	add_item("floor", "It is not easy to see the floor due to all the blood and filth which cover it.\n");
	add_item("bones","Bones lay on the floor as a sign of combat.\n");
	add_item("guts", "On the walls you can see guts hanging. Someone must have been beaten real bad in here.\n");
	
	add_prop(ROOM_I_INSIDE, 1);
	add_prop(ROOM_I_LIGHT, 0);
	
	add_exit(TROLLSH_DIR + "w_hall", "north", 0);

	troll = clone_object(TROLLSH_DIR + "npc/ruletroll");
	troll->move(TO);
}

reset_room()
{
    if(!present("troll"))
  {
      troll = clone_object(TROLLSH_DIR + "npc/ruletroll");
      troll->move(TO);
  }
}
