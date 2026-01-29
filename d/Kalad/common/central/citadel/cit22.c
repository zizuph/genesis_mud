/* 
Citadel, kitchen.
Made by Korat 
Feb 14. 1995 
*/

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

void
create_room()
{
   ::create_room();
   add_prop(ROOM_I_INSIDE,1);
   add_prop(ROOM_M_NO_TELEPORT, 1);

   hear_bell = 2;
   set_short("Citadel, kitchen");
   set_long("This is the kitchen that prepares the food for the "+
      "High Lord himself! No wonder you see several chefs and waitresess "+
      "working hard on preparing the excellent food that is needed to "+
      "please the High Lord. You notice that one fat man walks around, "+
      "tasting all the dishes in a random order and selection.\n");

   add_item(({"fat human","fat man", "man"}),"He is clad in expensive "+
      "clothing, and from his adorned belt an attached chain runs "+
      "towards the spoon he holds in his right hand. Now and then he "+
      "dippes this spoon in one of the kettles and tastes the "+
      "content. He must be both a lover and critiziser of food "+
      "along with his obvious duty of checking it all for any poison.\n");

   add_item("dishes","They span from some delicious salads "+
      "to a few artful decorated silver plates with "+
      "escargot, filet mignon, boiled lobster and other "+
      "exotics. They all makes your mouth water.\n");
   add_exit(CENTRAL(citadel/cit21),"north",0,-1,-1);
}
