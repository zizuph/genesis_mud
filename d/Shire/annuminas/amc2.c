inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

create_room() {

  set_short("Town");
  set_long("The sounds of life are strong here, they seem to "
	  +"come form the ruins to your immediate north. Piles of "
	  +"rubble lie all around, but a small path is cleared "
	  +"leading towards the sounds. The mist has dissipated "
	  +"in this area, and the view of the large building to "
	  +"the north is somewhat clearer. The small street you "
	  +"are on continues to the east and west, apparently "
	  +"going for a moderate distance.\n"); 
  add_item(({"sounds","sound"}),"It sounds like life, creatures of "
			       +"some sort talking and laughing.\n");
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
  add_item(({"ruins"}),"They appear to be the ruins of a small house "
 		      +"with no roof, and ragged walls.\n");
  add_item(({"path"}),"It leads north and seems to be fairly clear "
		     +"of rubble.\n");
  add_exit(ANNUM_DIR + "amc3", "north", 0);
  add_exit(ANNUM_DIR + "amc1", "west", 0);
  add_exit(ANNUM_DIR + "amc4", "east", 0);
}  
