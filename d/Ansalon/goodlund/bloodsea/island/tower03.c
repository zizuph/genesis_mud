#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/nethosak/city/local.h"
#include "/d/Ansalon/goodlund/bloodsea/local.h"
#include <stdproperties.h>
#include <macros.h>
 
inherit MITHAS_OUT;

object queen, harpy1, harpy2;

void 
reset_mithas_room()
{
   if(!objectp(harpy1))
   {
      harpy1 = clone_object(BNPC + "harpy");
      harpy1->move(TO);
   }

   if(!objectp(harpy2))
   {
      harpy2 = clone_object(BNPC + "harpy");
      harpy2->move(TO);
   }

   if(!objectp(queen))
   {
      queen = clone_object(BNPC + "harpy_queen");
      queen->move(TO);
   }
}

void
create_mithas_room()
{
   set_short("rooftop of a ruined tower, high above the isle of Karthay");
   set_long("@@long_descr"); 


   add_item(({"black rocky cliffs","black cliffs","rocky cliffs","cliffs","cliff"}),
         "Far below, you notice the tower sits on the edge of the high cliffs that " +
         "make up the coastline of Karthay.\n");

   add_item(({"isle","island","isle of karthay","karthay","view"}),
         "From the top of the tower you have an amazing view of the isle of Karthay. " +
         "To your north and east, barren hot plains stretch out far into the distance, where they " +
         "eventually meet with the great Worldscap mountains. To your south and west stretches " +
         "the Bloodsea of Istar.\n");

   add_item(({"plains","barren hot plains","hot plains","barren plains"}),
         "Looking inland, the isle of Karthay consists of barren, hot plains that stretch out " +
         "to the base of the Worldscap mountains. Apart from this lighthouse, you can see no " +
         "signs of civilisation.\n");

   add_item(({"ruins","abandoned ruins","tower","winston's tower","great tower",
         "lighthouse","beacon","holy beacon","ruins"}),
         "Once a holy beacon for travellers, Winston's Tower is now abandoned, " +
         "home only to the darkness.\n");

   add_item("istar","You cannot see the lands of Istar... it sunk beneath the waters of the " +
         "Bloodsea during the cataclysm.\n");

   add_item(({"stones","stone floor","floor"}),
         "The stones at the top of the tower have been scorched black here by mighty fires that " +
         "once raged here an age ago. You notice more recent markings on these stones... it looks " +
         "like dried blood!\n");

   add_item(({"blood","dried blood"}),
         "You nervously notice that a lot of blood has dried here recently!\n");

   add_item(({"worldscap mountains","mountains"}), 
         "In the far distance to your northeast, the Worldscap mountains rise high into the " +
         "sky. It is rumoured a strange avian race make these mountains their home.\n");

   add_item(({"bloodsea","sea","water","bloodsea of istar"}),
         "Far beneath you to your south and west, stretching out as far as the eye can see " +
         "is the Bloodsea of Istar. You can make out the occasional sail on the horizon, " +
         "however whether it is a minotaur, Saifhum, pirate, or Dragonarmy ship is anyones " +
         "guess.\n");

   add_item("sail","You see a sail in the distance, but can't tell what sort of ship it is.\n");


   add_exit(BISLAND + "tower02","down",0);

   reset_mithas_room();     
}

string
long_descr()
{ 
   return "You stand on the ruined rooftop of a great lighthouse, once known as Winston's " +
       "Tower. Before the cataclysm this tower served as a holy beacon for travellers " +
       "across the lands of Istar, now it is a haunt for fell creatures of darkness. The " +
       "stone floor still shows signs of the beacon, the stones being permanently " +
       "scorched black by the intense fires that used to burn up here.\n";
}
