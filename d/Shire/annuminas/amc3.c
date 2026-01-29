inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

create_room() {

  set_short("Town");
  set_long("The path only leads a short way, and stops here, in "
	  +"the ruins of an old house. There is no ceiling to offer "
	  +"shelter from the rain, and the walls barely manage to "
	  +"stand. There is a campfire here, burning bright. There "
	  +"has been some sort of creature here recently, the fire "
	  +"proves that, as does the moved rubble.\n");
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
  add_item(({"fire"}),"This is a freshly made fire. It is burning "
		     +"quite hot and stands tall.\n");
  add_exit(ANNUM_DIR + "amc2", "south", 0);
}  
