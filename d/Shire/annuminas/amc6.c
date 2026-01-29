/*

ChangeLog:
  20 May 2006 - Palmer
  Removed north exit which had an integer as the filename.

*/


inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Shire/orcmaker/orcmaker.h"

create_room() {

  set_short("Road");
  set_long("The road ends up ahead, but here there runs a small path "
	  +"north, as well as the roads directions of east and west. "
	  +"The mist blocks enough of your sight so that the way "
	  +"north, as well as east are too difficult to discern. "
	  +"The street is covered in rubble, making the small road "
	  +"treacherous, as well as mysterious. To the north, you "
	  +"can still barely make out the building which stands tall "
	  +"amidst the rubble.\n");
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
  add_exit(ANNUM_DIR + "amc7", "east", 0);
  add_exit(ANNUM_DIR + "amc5", "west", 0);
}

