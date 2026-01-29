inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

create_room() {

  set_short("Stairs");
  set_long("The street ends here at the bottom of a huge set of "
  	  +"stairs. Ahead to the north lies the ruins of a once "
	  +"grand castle. It is the biggest building in the city, "
	  +"but it too lies in ruins. The mist even this close, "
	  +"hinders the view of the castle, it seems to form a "
	  +"thick blanket at the entrance to the castle, making "
	  +"the doors impossible to see. The only paths open for "
	  +"travel lead up to the castle, or back away from it.\n");
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
  add_exit(ANNUM_DIR + "am16", "south", 0);
  add_exit(ANNUM_DIR + "am19", "northeast", 0);

//   "/d/Shire/annuminas/orcroom3"->teleledningsanka();
}
