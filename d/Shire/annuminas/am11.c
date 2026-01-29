inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

create_room() {

  set_short("Road");
  set_long("The street continues onward. As it delves deeper into "
	  +"the ruined city, you begin to truly appreciate the amount "
	  +"destruction caused by the Witchking upon this once glorious "
	  +"city. Even now, descendents from his army are present here "
	  +"as goblins. Even without seeing them, their smell "
	 +"pervades the ruins. This place is no longer the "
	  +"haven for good that it once was.\n");
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
  add_exit(ANNUM_DIR + "am13", "north", 0);
  add_exit(ANNUM_DIR + "am10", "southwest", 0);
}
