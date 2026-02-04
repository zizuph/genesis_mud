inherit "std/room";

#include <files.h>
#include <stdproperties.h>

#define PATH "/d/Terel/common/town/street/"

void
create_room()
{
   set_short("Inside the tower");
   set_long("Inside the tower, it is difficult to figure out what " +
       "purpose it originally served: the stone walls are " +
       "bare except where rubble has been piled against them. "+
       "The floor has a pile of freshly-trimmed pine branches "+
       "that are being used as a bed, as well as crushed herbs "+
       "strewn about. "+
	   "A long and mostly broken staircase skirts " +
       "the wall of the tower. Where once it lead to the floor above, "+
       "it looks as though it has fallen into a dangerous state of " +
       "disrepair. A small set of stone stairs toward the north side "+
       "of the tower leads down, into deep darkness.\n");

   room_add_object(PATH + "t_door2");
   add_npc("/d/Terel/common/town/garden/herbalist", 1);

   add_prop(ROOM_M_NO_TELEPORT_TO, 1);
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, -1);
   add_prop(ROOM_S_DARK_LONG, "It is dark here, and dank. Feeling around, "+
      "you think there is a door here, and an opening in the floor that "+
      "leads down.\n");
   add_exit("below_tower", "down", 0, 0, 1);
   
   add_item(({"wall", "walls", "tower", "stone", "soot"}), 
      "The walls of the tower are black with something like soot.\n");
   add_item(({"staircase", "spiral staircase", "up", "broken staircase"}),
      "A staircase once spiraled up along the inner walls of the tower, "+
      "but very little is left of it.\n");
   add_item(({"stairs", "down", "downstairs", "north", "north stairs" }),
      "A small set of stone stairs leads downward into darkness. The "+
      "steps look like they are in better shape than the ones that "+
      "once wound around the interior of the tower.\n");
    add_item(({"rubble", "pile of rubble"}), "It looks like rubble "+
      "from the broken staircase.\n");
    add_item(({"pine branches", "branches", "boughs", "pine boughs",
	  "pile of branches", "bed"}), "Fresh branches have been cut from "+
      "the trees outside, and brought in her to make a fragrant, if "+
      "primative, bed.\n");
    add_item(({"herbs", "herbs on the floor", "crushed herbs"}),
      "It looks like herbs have been crushed underfoot as someone "+
      "moved around.\n");
	  
}
