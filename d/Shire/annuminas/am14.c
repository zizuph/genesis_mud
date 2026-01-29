inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

create_room() {

  set_short("Road");
  set_long("You are following the entrance road of Annuminas. Through "
	  +"the mist, one seemingly intact building towers in the north, "
	  +"and back to the south lies the way out of the city. "
	  +"There is more rubble here than there was a moment ago, as "
	  +"if it was gathered up here to make passage easier for "
	  +"some creature. The damp mist clings to your skin, beading "
	  +"up on all flat surfaces, and dampening your clothes. The "
	  +"mist isn't the only thing making you damp, the sweat of "
	  +"anticipated danger clings to your brow, and dampens your "
	  +"palms. This place exudes a feeling not of evil, but of "
	  +"untamed chaos, a force even your iron-will and warrior "
	  +"senses and skills cannot combat.\n");
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
  add_exit(ANNUM_DIR + "am2c1", "north", 0);
  add_exit(ANNUM_DIR + "am12", "south", 0);
}
