// file name: d_str3
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
   set_short("quiet street");
   set_long("This is a quiet street that bends "
           +"from the east to the north, where it "
           +"leads up to a boat landing at the "
           +"island's northern edge.\n");
   AI(({"street","road","ground","floor"}),"The "
           +"street is made of small fitted cobble"
           +"stones.\n");
   AI(({"source","ceiling","cavern","cave"}),"The "
           +"great ceiling of Sybarus cavern "
           +"is high above. From it, you can make "
           +"out the dim gloaming of the Source.\n");
   AI(({"landing","dock","pier"}),"The dock lies "
           +"to the north. It seems to be sturdy "
           +"and made of strong wood.\n");
   
   AE(BAZAAR + "intr/d_str2", "east", 0, 1);
   AE(BAZAAR + "intr/d_landing", "north",0,1);
   
   	
	IN;       // Avenir is an undergound domain.


}
