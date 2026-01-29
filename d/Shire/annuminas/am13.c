inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
create_room() {

  set_short("Road");
  set_long("You wander along the largest clear path in Annuminas. To the "
	  +"north, the city itself sits, while to the west, east and to "
	  +"the south lie small buildings and homes. Straight ahead "
	  +"there is an enormous building towering over the destroyed "
	  +"city, cloaked in the same mist which cloaks "
	  +"the streets with intrigue and danger. Around the ground "
	  +"lie piles of rubble, unmoved for hundreds of years, "
    +"apparently not until now.\n");
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
  add_item(({"building"}),"The building rises high through the mist, "
			 +"acting as a beacon to your sense of sight "
			 +"by pointing the way north.\n");
  add_exit(ANNUM_DIR + "amc1", "north", 0);
  add_exit(ANNUM_DIR + "am11", "south", 0);


//   "/d/Shire/annuminas/orcroom5"->teleledningsanka();
}
