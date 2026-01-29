inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

create_room() {

  set_short("Broken Road");
  set_long("Ahead the road enters the ruined town. The mist seems to "
	  +"be thicker here than it was further south. The grass has "
	  +"grown more sparse as you near the ruins. Some rubble can "
	  +"still be seen among the grass, but it too, has become "
	  +"less common. Briefly you thought you saw movement in "
	  +"the ancient ruins.\n"); 
  add_item(({"road"}),"This is an old stone leading northwards. The "
                   +"broken marble slabs are laying astray of a "
                   +"normal path, and grass has sprouted between the slabs.\n");
  add_item(({"ruins"}),"You can't make out much, but it seems to be "
                    +"the ruins of a rather large town. A small "
                    +"stream of smoke is trailing into the air, "
                    +"the only sign of life in the area.\n");
  add_item(({"grass","plains"}),"A large grassy plain, with tall "
                             +"thick, green grass sprouting "
                             +"everywhere, covering the ground "
                             +"like a blanket.\n");
  add_item(({"rubble","piles"}),"These small piles of rubble look "
                    +"like the remnants of a small wall that was "
                    +"overrun and destroyed.\n");
  add_item(({"mist"}),"This is a thick, moist mist that floats just "
                   +"above the grass. It obscures your vision "
                   +"just enough so you can't make out the ruins "
                   +"in the distance.\n");
  
  add_exit(ANNUM_DIR + "am8", "north", 0);
  add_exit(ANNUM_DIR + "am6", "southwest", 0);
}
