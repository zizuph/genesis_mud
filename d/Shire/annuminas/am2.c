inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"
object ob;

create_room() {

  set_short("Broken Road");
  set_long("You have travelled further down the broken stone road. "
	+"The same mist still obscures the view, hiding the "
	+"ruins that lie to the north. The grass that surrounds the ancient road "
	+"is tall and green, and even it hides something, as if "
+"this entire area were cloaked in an ancient mystery.\n");
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
         

  add_exit(ANNUM_DIR + "am3", "northwest", 0);
  add_exit(ANNUM_DIR + "am1", "south", 0);
}

