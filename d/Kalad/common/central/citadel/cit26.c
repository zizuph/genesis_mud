/* 
Citadel, private chambre.
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
   hear_bell = 2;
   set_short("Citadel, High Lords private chamber");
   set_long("This is the High Lords private chamber! You see a cabinet "+
      "standing next to a weapon rack on the northern wall. Along the "+
      "western wall you cannot avoid noticing the large bed, covered with "+
      "feather pillows. The walls are decorated by a few "+
      "paintings that matches the brownish paneling on the walls. "+
      "Either the decorator or the person living here has a taste for "+
      "simplicity, because the room is rather empty.\n");
   
   add_item(({"weapon rack","rack"}),"You see several excellent swords "+
      "and halberds lined up in it, but they are all securely locked down.\n");
   add_item(({"painting","paintings"}),"They portraits a few scenarios "+
      "of people, nature and a battle-scene here and there.\n");
   add_item(({"panel","paneling"}),"The paneling must be of oak, and has "+
      "been lighly torched to give the wood a darker brownish touch in its "+
      "colour. Together with the desk it manages to dampen the lights from "+
      "the candles, giving a relaxed atmosphere in the room.\n");
   add_item("bed","Its is a large bed that looks pretty comfy with its "+
      "feather pillows and a blue, velvet sheet.\n");
   add_item(({"pillow","pillows"}),"Ohhh, they look soft!\n");
   add_item(({"sheet","velvet","velvet sheet"}),"The large velvet sheet "+
      "shines in its dark-blue colour. It is extremely soft to the touch.\n");
   
   add_exit(CENTRAL(citadel/cit25),"east",0,-1,-1);
   clone_object("/d/Kalad/common/central/obj/cabinet")->move(TO);
}
