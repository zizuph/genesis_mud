inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

create_room() {

  set_short("Through the Arch");
   set_long("All around lay the ruins of the fabled city of "
           +"Annuminas, past home to the kings of Arnor. The streets "
           +"here have lost their splendor, and now lie in "
	   +"ruin, rubble from destroyed buildings covering the "
	   +"once finely cobbled ground. Most of the buildings "
	   +"now lie in piles, crushed as the Armies of Angmar "
	   +"ruthlessly smashed their way through everything in "
	   +"Arnor. Further north, something appears to be the "
	   +"only intact building in the city, but the heavy mist "
   	+"obstructs the view enough so that  "
	   +"no definite shapes are discernable. The only thing "
    +"that is clear is that something feels very, very wrong.\n");
  add_item(({"road"}),"The road ends here, becoming a normal city "
                   +"street. The street is also in disrepair, just "
                   +"as the road outside was. This street is very "
		   +"large, making the streets in both Hobitton and "
		   +"Bree look like sidewalks.\n");
  add_item(({"mist"}),"This is a thick, moist mist that floats just "
                   +"above the ground. It obscures your vision "
                   +"just enough so you can't make out details in " 
		   +"the distance.\n");
  add_item(({"arch"}),"This is a huge ruined arch that once marked "
                     +"the entrance to the ruined city before you. "
                     +"Even though ruined, it still towers above your "
                     +"head, a huge monolith in the otherwise plain "
                     +"ruins.\n");
  add_item(({"rubble","piles"}),"These small piles of rubble look "
                    +"like the remnants of buildings.\n");
add_item(({"building"}),"This appears to be a huge building. The "
		       +"strange thing about it is it seems to be "
		       +"the only thing not in ruins.\n");
  add_exit(ANNUM_DIR + "am8", "south", 0);
  add_exit(ANNUM_DIR + "am10", "north", 0);
}
