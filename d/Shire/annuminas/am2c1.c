
inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Shire/orcmaker/orcmaker.h"

create_room() {

  set_short("Road");
  set_long("The road branches out here, heading out towards the west "
	  +"and heading off into the mist. The street here is in "
	  +"shambles, rubble strewn everywhere, partially blocking "
	  +"the path in all directions, but not enough to prevent "
	  +"passage. To the north lies the only building which looks "
	  +"to be intact in the whole town, but it is almost "
	  +"impossible to make out any details on it. The street is "
	  +"silent here, almost foreboding, but certainly eerie.\n");
  add_item(({"street","streets","road","roads"}),"The streets were "
                   +"once made of finely crafted cobbles, but now "
                                 +"lay in shambles, covered in "
                                 +"rubble.\n");
  add_item(({"rubble","piles"}),"These small piles of rubble look "
                    +"like the remnants of buildings.\n");
  add_item(({"mist"}),"This is a thick, moist mist that floats just "
                   +"above the ground. It obscures your vision "
                   +"just enough so you can't make out details in "
                   +"the distance.\n");
  add_item(({"building","castle"}),"The building rises high above "
				  +"the rest of the ruins, and seems "
				  +"to be in better condition than "
				  +"most of the rest of the town.\n");
  add_exit(ANNUM_DIR + "am2c2", "west", 0, 0, 1);
  add_exit(ANNUM_DIR + "am16", "north", 0);
  add_exit(ANNUM_DIR + "am14", "south", 0);
}
