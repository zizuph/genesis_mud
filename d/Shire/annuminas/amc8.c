inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Shire/orcmaker/orcmaker.h"

create_room() {

  set_short("Road");
  set_long("The road now has turned heading northward, following "
	  +"the edge of the forest to the east. A heavy veil of "
	  +"mist covers both the forest and the city completely, "
	  +"making vision hardly reliable. The mist shrouds the "
	  +"rubble covering the ground, hiding the treacherous "
	  +"ground from casual looks. To the northwest, a "
	  +"building pierces the mist, looking oddly unruined. "
   	  +"Strange noises emanate from the eerie forest, giving "
	  +"the area an almost malevolent feel.\n"); 
  add_item(({"noises","noise"}),"They sound like the death squeals "
	   		       +"of animals.\n");
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
  add_exit(ANNUM_DIR + "amc9", "north", 0);
  add_exit(ANNUM_DIR + "amc7", "south", 0);
}
