// file name: n_bridge.c
// creator(s): Ilyian, April 1995
// last update: 
// purpose: Bridge between park and bazaar islands.
// note: 
// bug(s):
// to-do:

inherit "/std/room";
inherit "/d/Avenir/inherit/room_tell";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "../bazaar.h"

create_room()
{
set_short("North end of arched bridge");
set_long("You stand upon a steeply arching bridge of blackened stone "
   +"that rises up steeply to the south, and slopes downwards to the "
   +"north, ending at the shore of the bazaar island. "
   +"The bridge is of very solid construction. Below you, the "
   +"dark waters of the sea swirl menacingly, and to the south you see "
   +"a pair of large stone statues rise up on either side of the bridge.\n");

AE(BAZAAR+"green/m_bridge","south",0,3);
AE(BAZAAR+"green/s_shore","north",0);

    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
add_prop(OBJ_I_CONTAIN_WATER);     //water is available here
   add_prop(ROOM_I_TYPE, ROOM_BEACH);
add_prop(ROOM_I_LIGHT,1);
IN

AI(({"bridge","stone"}), "This bridge is made from a rough "
   +"grey stone that has blackened to a sooty colour over the years. It "
   +"arches high over the sea, ending at islands at either side. Large "
   +"stone statues rise up at the center of the bridge, seemingly "
   +"guarding the way.\n");
AI(({"water","sea","ocean"}),"The water beneath the bridge is "
   +"completely lightless, so you have no indication of either how "
   +"deep it is, or what hides beneath the surface. It gives you an "
   +"uncomfortable feeling, and strange eddies swirl in eerie patterns.\n");
AI(({"statue","statues"}),"They are large, but that is all you can make out "
   +"from this far away.\n");
AI(({"south island","park"}),"The bridge arches so steeply to the south "
   +"that you cannot make out the island that lies in that direction "
   +"from here.\n");
AI(({"north island","island","bazaar"}),"From your vantage point, you "
   +"have a good view of the bazaar island. It is a crowded mass of "
   +"buildings, vendors, and citizens milling about. The noise of "
   +"haggling reaches your ears even from this distance. In the center "
   +"rises a large hill, upon which a dark shape looms. In the southern "
   +"part of the island is a pleasant garden.\n");

   set_tell_time (110);
     add_tell ("A warm breeze blows across the bridge, bringing upon "
          +"it a strange scent.\n");
     add_tell ("The sea below you swirls and churns in strange eddies.\n");
     add_tell ("From the north island, you hear the distant call of "
          +"hawkers selling their wares.\n");
     add_tell ("A bit of driftwood floats by beneath the bridge\n");

}

void
enter_inv(object ob, object from)
{
   start_room_tells();
   ::enter_inv(ob, from);
}
