inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Shire/orcmaker/orcmaker.h"

create_room() {

  set_short("Stairs");
  set_long("The street ends here, at the base of a huge set of stairs. "
          +"The castle looms to the northwest of the stairs, and "
	  +"another set of identical stairs leads up to the castle "
	  +"to the west. The castle is shrouded in a heavy mist "
	  +"which is concentrated around the doors and front of the "
	  +"building, obstructing the view. The stairs look well "
	  +"worn, evidence of the ages of use, even up until the "
	  +"present.\n");
  add_item(({"doors","door"}),"The doors are hard to see, but appear "
			     +"to be gone.\n");
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
  add_item(({"stairs"}),"The stairs are made of beautiful marble, "
		       +"but have obviously felt the ages pass. The "
		       +"once polished shapely steps have given way "
		       +"to rugged, windblow steps. They lead up to "
		       +"the castle before you.\n");
  add_item(({"building","castle"}),"The building rises high above "
	 			  +"you to the north, standing tall "
				  +"above the rest of the rubble "
				  +"and destruction of the town. "
				  +"It seems to be a castle, but the "
				  +"mist is still too heavy to be "
				  +"sure.\n");
  add_exit(ANNUM_DIR + "am19", "northwest", 0);
  add_exit(ANNUM_DIR + "am15", "south", 0);
}  
