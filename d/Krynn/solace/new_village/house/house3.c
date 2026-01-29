/*
* A normal house in Solace
*
* By Rastlin
*Descrip changed by Teth
*/

#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit  SOLINROOM;

object gDoor;

public void
create_solace_room()
{
   seteuid(getuid());
   
   set_short("A carpenter's house");
   set_long("@@my_desc@@");
   
   add_item("woodwork", "Ah, the work of a master carpenter. No " +
      "holes can be seen where plank meets plank, creating an " +
      "effective barrier against harsh winter storms.\n");
   
   add_item(({"tool", "tools"}), "Hammers, saws, awls, yardsticks, " +
      "rope: all can be found in every corner and crevice.\n");
   
   add_item(({"hammer", "hammers"}), "A variety of hammers exist, " +
      "some rusted with disuse while others are shiny new. Most are " +
      "somewhere in between, however.\n");
   
   add_item(({"saw", "saws"}), "The saws look to be heavily used as " +
      "almost every saw is missing one tooth or more.\n");
   
   add_item(({"awl", "awls"}), "Not a common tool of a carpenter, " +
      "you suspect the carpenter must do some leatherwork on the side " +
      "with this tapered piercing instrument.\n");
   
   add_item(({"yardstick", "yardsticks"}), "These yardsticks look " +
      "to be almost perfectly one yard in length. Not surprising.\n");
   
   add_item("rope", "The rope looks frayed and unable to support " +
      "even the weight of a baby kender.\n");
   
   add_item("bed", "The bed is littered with tools. No blankets " +
      "or pillows can be seen.\n");
   
   add_item(({"dresser", "drawer", "drawers"}), "The dresser and all " +
      "of its drawers are full with even more tools. The only item of " +
      "apparel is a toolbelt. You have to wonder where the carpenter's " +
      "clothes could possibly be.\n");
   
   add_item("stove", "This stove has spent many hours burning scraps " +
      "of wood. Right now, however, it is empty.\n");
   
   add_item(({"kitchen", "cutlery", "nails"}), "You have to wonder " +
      "if the carpenter's diet ever gets low in iron, considering all " +
      "of the nails in the kitchen, which outnumber the cutlery by " +
      "an extremely large factor.\n");
   
   add_item("rug", "If you were to clear off some of the tools and " +
      "step down, you suspect that yours would be the first foot to " +
      "touch the carpet in quite a long time.\n");
   
   gDoor = clone_object(OBJ + "d_house3");
   gDoor->move(TO);
}

public string
my_desc()
{
   string str;
   
   str = "This is, most likely, a carpenter's house. It is a " +
   "well-constructed house, with solid woodwork evident wherever " +
   "you look. The greenish-coloured wooden door set in the northwest " +
   "wall is ";
   
   if (gDoor->query_open())
      str += "open";
   else
      str += "closed";
   
   str += ". Tools are scattered everywhere. Not even the bed " +
   "escapes their presence. The dresser has carpenters' apparatus " +
   "poking out its drawers, while the stove stands guard over a small " +
   "pile. Looking at the kitchen, it seems there are more nails than " +
   "cutlery. You can barely notice a rug underneath all the tools on " +
   "the floor.\n";
   
   return str;
}



