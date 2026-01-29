inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

create_room() {

  set_short("Town");
  set_long("The sounds of life are abundant here, echoing through "
	  +"the mist like a crackling fire. The street continues "
	  +"on east and west, snaking its way through the rubble "
	  +"like a living creature. To the northwest you can see "
	  +"the large building rising out of the mist. Lining "
	  +"this street are rows of ruins, mostly unenterable. "
	  +"Further to the east, there appears to be something.\n");
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
  add_exit(ANNUM_DIR + "amc2", "west", 0);
  add_exit(ANNUM_DIR + "amc5", "east", 0);


//   "/d/Shire/annuminas/orcroom2"->teleledningsanka();
}  
