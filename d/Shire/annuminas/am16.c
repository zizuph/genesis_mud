inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

create_room() {

  set_short("Road");
  set_long("The road leads on to the north, heading towards a huge "
	  +"building mostly unruined. Mist clings to everything, "
	  +"dampening the road and obscuring the surroundings. Rubble "
	  +"covers the street, piles of it everywhere. The ruins of "
	  +"buildings line the street, unenterable for anything but "
	  +"rats. The curtain of mist makes long distance viewing "
	  +"impossible, and the surrounding area is visible only "
	  +"as a vague haze.\n");
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
  add_exit(ANNUM_DIR + "am2c1", "south", 0);
  add_exit(ANNUM_DIR + "am18", "north", 0);
}
