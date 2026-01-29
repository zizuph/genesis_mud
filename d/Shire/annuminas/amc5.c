inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

create_room() {

  set_short("Road");
  set_long("The road continues on here, south of here there seems to "
	  +"be a lot of loud noises, as if someone was partying. "
	  +"To the east, the road continues for a short while, but "
	  +"there is an end in sight. Lining the sides of this narrow "
	  +"road are small piles of rubble, that have apparently been "
	  +"moved to make passage easier for whoever lives here. The "
	  +"dense blanket of mist that coats the ground makes the "
	  +"identification of tracks impossible, so whatever lives "
	  +"here can keep its secret, for now.\n");
  add_item(({"street","streets"}),"The streets were once made of "
                                 +"finely crafted cobbles, but now "
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
  add_item(({"sound","sounds","noise","noises"}),"These sound like "
					+"the sounds made by drunk "
					+"and partying creatures.\n");
  add_exit(ANNUM_DIR + "amc6", "east", 0);
  add_exit(ANNUM_DIR + "pub", "south", 0);
  add_exit(ANNUM_DIR + "amc4", "west", 0);
}
