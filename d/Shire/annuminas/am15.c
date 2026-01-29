inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

create_room() {

  set_short("Town");
  set_long("Looming closer now, the building to the north becomes "
	  +"almost visible. The mist coalesces into a thick cloud "
	  +"here, but the size and proportions of the building can "
	  +"not be hidden. The street here is almost clear of rubble "
	  +"and the sounds of voices can be heard emanating from "
	  +"shadows. The road ends to the north at a large set "
	  +"of stairs.\n");
  add_item(({"sounds","sound","voices"}),"It sounds like life, "
                     +"creatures of some sort talking and laughing.\n");
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
  add_item(({"building"}),"The building is very large, even while "
			 +"ruined, and was obviously a castle of "
			 +"some sort, even now it maintains "
			 +"habitation, the cleanliness of the area "
			 +"surrounding it makes that clear.\n");
  add_item(({"stairs"}),"The stairs are broad and made of marble. "
		       +"The marble has worn down over the years "
		       +"as it lay in ruin, but they serve their "
		       +"purpose well. They lead up to the front of "
		       +"the castle.\n");
  add_exit(ANNUM_DIR + "am17", "north", 0);
  add_exit(ANNUM_DIR + "amc1", "south", 0);
}  
