/*

ChangeLog:
  20 May 2006 - Palmer
  Removed north exit which had an integer as the filename.

*/


inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Shire/orcmaker/orcmaker.h"

create_room() {

  set_short("Road");
  set_long("The road continues on northward here, but there is "
	  +"also a small path leading west. To your east lies a "
	  +"gloomy forest, as well as a pile of rubble which "
	  +"seems to serve as a boundary to keep either things "
	  +"in the town, or keep things from coming into the town. "
	  +"Mist hovers in midair, penetrating clothing and "
	  +"making everything damp. To the west, a huge building "
	  +"juts out of the mist and rubble like a church spire. "
	  +"Noises can be heard originating from the cave to "
	  +"the east. Tales of death and worse are told of the "
	  +"forest, unpleasant things that would make Sauron "
	  +"smile. Beware.\n");
  add_item(({"noises","noise"}),"They sound like the death squeals "
	   		       +"of animals.\n");
  add_item(({"forest"}),"The forest is large and dense. Stories "
                       +"of hideous creatures and missing persons "
                       +"are almost common knowledge.\n");
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
  add_exit(ANNUM_DIR + "amc10", "west", 0);
//   add_exit(ANNUM_DIR + "amc14", "north", 0);
  add_exit(ANNUM_DIR + "amc8", "south", 0);
}

