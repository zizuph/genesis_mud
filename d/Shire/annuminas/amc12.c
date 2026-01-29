inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Shire/orcmaker/orcmaker.h"

create_room() {

  set_short("Road");
  set_long("The path ends here, and another small clearing is "
	  +"south of here. A tall building is rising out of the "
	  +"fog to your immediate west, but from here, it is "
	  +"inaccessible. Some noises come from the south, playful "
	  +"noises. The rubble is fairly thin over here, and has "
	  +"mostly been used to make rough piles resembling walls. "
	  +"The mist has cleared over here, but remains heavy "
	  +"back to the east, north, and south.\n");
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
  add_exit(ANNUM_DIR + "amc10", "east", 0);
  add_exit(ANNUM_DIR + "amc13", "south", 0);
}
