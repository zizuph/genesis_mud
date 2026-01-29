inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
create_room() {

  set_short("Road");
  set_long("The road is somewhat clean of rubble in this area, as if "
	  +"used as a path for some unknown inhabitants. The street, "
	  +"though, is still in disrepair. The mist is still present "
	  +"here, seeming to be a wall that blocks sight in all "
     +"directions. To the north, a building can "
	  +"be seen rising tall through the mist, piercing it like a "
	  +"knife. Details of it cannot be seen, but it seems to be "
	  +"the place where all paths lead.\n");	  
  add_item(({"street","streets"}),"The streets were once made of "
                                 +"finely crafted cobles, but now "
                                 +"lay in shambles, covered in "
                                 +"rubble.\n");
  add_item(({"rubble","piles"}),"These small piles of rubble look "
                    +"like the remnants of buildings.\n");
  add_item(({"mist"}),"This is a thick, moist mist that floats just "
                   +"above the ground. It obscures your vision "
                   +"just enough so you can't make out details in "
                   +"the distance.\n");
  add_item(({"building"}),"The building rises high through the mist, "
			 +"acting as a beacon to your sense of sight "
			 +"by pointing the way north.\n");
  add_exit(ANNUM_DIR + "am14", "north", 0);
  add_exit(ANNUM_DIR + "am10", "southeast", 0);
}
