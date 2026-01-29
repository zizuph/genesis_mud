// file name: d_str1
// creator: Ilyian, Sept 24, 1995
// last update:
// purpose: 
// note:
// bug(s):
// to_do:

inherit "/std/room";
#include "/d/Avenir/common/common.h"

create_room()
{
   set_short("side street");
   set_long("This street is made of small cobblestone, "
           +"and leads south, where you can see and " 
           +"hear the crowded bazaar. To the north, "
           +"the street seems deserted and silent. East "
           +"is a small building.\n");
   AI(({"street","road","ground","floor"}),"The "
           +"street is made of small fitted cobble"
           +"stones.\n");
   AI(({"source","ceiling","cavern","cave"}),"The "
           +"great ceiling of Sybarus cavern "
           +"is high above. From it, you can make "
           +"out the dim gloaming of the Source.\n");
   AI(({"bazaar","market"}),"To the north is the "
           +"large and crowded bazaar. You can "
           +"make out all sorts of people milling "
           +"about and buying goods.\n");
   AI(({"building","warehouse"}),"The building to "
           +"the east is small and nondescript. The "
           +"doorway lies open.\n");
   
   AE(BAZAAR + "intr/d_str2", "north", 0, 1);
   AE(BAZAAR + "intr/dead_ware", "east", 0, 1);
   AE(BAZAAR + "extr/str2", "south" ,0,1);

	
	IN;       // Avenir is an undergound domain.


}
