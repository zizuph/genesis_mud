#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit FLOTSAM_OUT;
object drac1;
object drac2;

void
reset_flotsam_room()
{
   if(!objectp(drac1))
      {
      drac1 = clone_object(KNPC + "bozak");
      drac1->move(TO);
   }
   if(!objectp(drac2))
      {
      drac2 = clone_object(KNPC + "kapak");
      drac2->move(TO);
   }
}

create_flotsam_room()
{
   set_short("Crowded street in the town of Flotsam");
   set_long("@@long_descr");
   
   add_item(({"brazier","iron brazier","tall iron brazier"}),"A " +
      "tall iron brazier, its light casting dark shadows on the " +
      "walls of the surrounding buildings. \n");
   add_item(({"street","cobbled street"}),"A filthy, well-used, " +
      "cobblestone street. \n");
   add_item("clouds","Overhead loom gloomy clouds that seem to " +
      "hover over Flotsam every minute of the day. \n");
   add_item(({"gate","gates","town gates"}),"To the east " +
      "you can make out the town gates, the main " +
      "exit to the other lands on the Goodland Peninsula.\n");
   add_item(({"soldiers","mercenaries"}),"Drunken soldiers of the Blue dragonarmy " +
      "along side newly recruited mercenaries stumble through " +
      "the street. It would be best to keep out of " +
      "their way if you don't want trouble.\n");
   add_item("patrols","Heavily armed patrols wander the streets, " +
      "stopping newcomers to Flotsam, interrogating them, and " +
      "occasionally arresting them. You wonder what " +
      "they are looking for?\n");
   
   add_exit(FROOM + "street20","east",0);
   add_exit(FROOM + "street25","south",0);
   add_exit(FROOM + "street18","west",0);
   
   reset_flotsam_room();
}

string
long_descr()
{
   return tod_descr1() + tod_descr2() + "You stand on a crowded " +
   "cobbled street in the town of Flotsam. Mercenaries " +
   "roam alongside heavily armed patrols of Dragonarmy " +
   "soldiers, the later often stopping people in the " +
   "street, sometimes dragging them off for 'questioning'. " +
   "To the east you can see the towns gates at the " +
   "end of the street. A tall iron brazier stands off on a " +
   "sidewalk, relieving little of the gloom brought on by the " +
   "clouds overhead. " + season_descr() + "\n";
}
