// file name: d_str2
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
   set_short("winding street");
   set_long("The street turns sharply here from "
           +"the east to the south. In the distance " 
           +"you can hear the noise from the bazaar, "
           +"but here everything is still and quiet.\n");
   AI(({"street","road","ground","floor"}),"The "
           +"street is made of small fitted cobble"
           +"stones.\n");
   AI(({"source","ceiling","cavern","cave"}),"The "
           +"great ceiling of Sybarus cavern "
           +"is high above. From it, you can make "
           +"out the dim gloaming of the Source.\n");
   
   AE(BAZAAR + "intr/d_str1", "south",0,1);
   AE(BAZAAR + "intr/d_str3", "west", 0, 1);
   
   	
	IN;       // Avenir is an undergound domain.

}
