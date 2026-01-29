inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

create_room() {

  set_short("Road");
  set_long("The path to the east ends here, but turns northward. "
	  +"To the east lies a vast forest, its depths unexplored, "
	  +"but better left alone. Travellers have been known to "
	  +"simply vanish by just setting foot in the forest. The "
	  +"eerie mist that clings to all of Annuminas seems to "
	  +"almost emanate from the forest, finding life and strength "
	  +"from the unmentionable horrors that dwell there. Rubble "
	  +"lies piled along the edge of the forest, almost as a "
	  +"barrier to keep stray creatures in or out. Still rising "
	  +"above the ruins to your northwest stands a large building. "
	  +"To your immediate north lies more rubble covered streets "
	  +"and more danger.\n");
  add_item(({"street","streets","road","roads"}),"The streets were "
                   +"once made of finely crafted cobbles, but now "
                                 +"lay in shambles, covered in "
                                 +"rubble.\n");
  add_item(({"rubble","piles"}),"These small piles of rubble look "
                    +"like the remnants of buildings.\n");
  add_item(({"mist"}),"This is a thick, moist mist that floats just "
                   +"above the ground. It obscures your vision "
                   +"just enough so you can't make out details in "
                   +"the distance.\n");
  add_item(({"building","castle"}),"The building rises high above "
                                  +"the rest of the ruins, and seems "
                                  +"to be in better condition than "
                                  +"most of the rest of the town.\n");
  add_item(({"forest"}),"The forest is large and dense. Stories "
		       +"of hideous creatures and missing persons "
		       +"are almost common knowledge.\n");
  add_exit(ANNUM_DIR + "amc8", "north", 0);
  add_exit(ANNUM_DIR + "amc6", "west", 0);
}
