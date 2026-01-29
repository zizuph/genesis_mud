inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

create_room() {

  set_short("Town");
  set_long("There is a small intersection here, turning east into "
	  +"depths of the city. The street is dotted by piles of "
	  +"rubble, and the same mist still lingers in the air. "
	  +"The stillness that was present from afar is no longer "
	  +"here, though, and the sounds of life rings through "
	  +"the air. To the north a huge building stands, most "
	  +"likely a castle of sorts, but from the mist it is "
   +"impossible to tell.\n");
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
  add_exit(ANNUM_DIR + "am15", "north", 0);
  add_exit(ANNUM_DIR + "am13", "south", 0);
  add_exit(ANNUM_DIR + "amc2","east", 0);
}  
