inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Shire/orcmaker/orcmaker.h"

create_room() {

  set_short("Road");
  set_long("The small path is mostly rubble free, and allows easy "
	  +"travel westward. Noise comes from both the north and "
	  +"west, this noise is a different one than the one from "
	  +"the forest, though. A clearing amoung the rubble lies "
	  +"to the north, but mist shrouds its contents. Far to "
	  +"the west is the large building that stands high in "
	  +"the air, protruding from the mist.\n"); 
  add_item(({"noises","noise"}),"They sound like creatures talking "  
  		       +"and having fun.\n");
  add_item(({"path"}),"It is fairly small and seems to be fairly clear "
                     +"of rubble.\n");
  add_item(({"forest"}),"The forest is large and dense. Stories "
                       +"of hideous creatures and missing persons "
                       +"are almost common knowledge.\n");
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
  add_exit(ANNUM_DIR + "amc11", "north", 0);
  add_exit(ANNUM_DIR + "amc12", "west", 0);
  add_exit(ANNUM_DIR + "amc9", "east", 0);
}
