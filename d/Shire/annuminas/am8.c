inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

create_room() {

  set_short("Threshold to the Town");
  set_long("North the road enters the ruins of Annuminas. The mist seems to "
	  +"part as the town appears. The grass is all but gone now, "
	  +"the town now dominates your view. The ground is thick with "
	  +"rubble here, close to the ruins. To the north a huge "
	  +"ruined arch beckons into the ruins, to explore its "
	  +"hidden treasures. A flickering light can be seen through "
	  +"and further into the ruins, but its origin remains a "
          +"secret.\n"); 
  add_item(({"road"}),"This is an old stone leading northwards. The "
                   +"broken marble slabs are laying astray of a "
                   +"normal path, and grass has sprouted between the slabs.\n");
  add_item(({"ruins"}),"You can't make out much, but it seems to be "
                    +"the ruins of a rather large town. A small "
                    +"stream of smoke is trailing into the air, "
                    +"the only sign of life in the area.\n");
  add_item(({"grass","plains"}),"A large grassy plain, with tall "
                        +"thick, green grass. The grass is "
			+"thinning out here as it nears the ruins.\n");
  add_item(({"rubble","piles"}),"These small piles of rubble look "
                    +"like the remnants of buildings, and the huge "
		    +"arch that lies to your north.\n");
  add_item(({"mist"}),"This is a thick, moist mist that floats just "
                   +"above the grass. It obscures your vision "
                   +"just enough so you can't make out the ruins "
                   +"in the distance.\n");
  add_item(({"arch"}),"This is a huge ruined arch that once marked "
		     +"the entrance to the ruined city before you. "
		     +"Even though ruined, it still towers above your "
		     +"head, a huge monolith in the otherwise plain "
		     +"ruins.\n");
  add_item(({"light"}),"It is a flickering light that seems to resemble "
		      +"a fire, but the brief glimpse you got of it "
		      +"was not enough for a positive identification "
		      +"of its source.\n");
  add_exit(ANNUM_DIR + "am9", "north", 0);
  add_exit(ANNUM_DIR + "am7", "south", 0);
}
