
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit FLOTSAM_OUT;
object drac1;
object drac2;
object drac3;
object drac4;
object drac5;
object drac6;


void
reset_flotsam_room()
{
   if(!objectp(drac1))
      {
      drac1 = clone_object(FNPC + "aurak_leader");
      drac1->move(TO);
   }
   if(!objectp(drac2))
      {
      drac2 = clone_object(KNPC + "sivak");
      drac2->move(TO);
   }
   if(!objectp(drac3))
      {
      drac3 = clone_object(KNPC + "bozak");
      drac3->move(TO);
   }
   if(!objectp(drac4))
      {
      drac4 = clone_object(KNPC + "bozak");
      drac4->move(TO);
   }
   if(!objectp(drac5))
      {
      drac5 = clone_object(KNPC + "kapak");
      drac5->move(TO);
   }
   if(!objectp(drac6))
      {
      drac6 = clone_object(KNPC + "kapak");
      drac6->move(TO);
   }
}

create_flotsam_room()
{
   set_short("Crowded street in the town of Flotsam");
   set_long("@@long_descr");
   
   add_item(({"cobbled street","street"}),"A well-used, dirty cobbled " +
      "street. \n");
   add_item(({"brazier","iron brazier","tall iron brazier"}),"A " +
      "tall iron brazier, its light casting dark shadows on the walls" +
      " of the surrounding buildings. \n");
   add_item("clouds","Gloomy clouds, that seem to hover over this " +
      "wretched town every minute of the day. \n");
   add_item(({"soldiers","mercenaries"}),"Off duty soldiers and " +
      "mercenaries stumble drunkenly along the cobbled street " +
      "from tavern to tavern.\n");
   add_item("patrols","Heavily armed patrols of draconians " +
      "walk the streets in search of someone. You wonder who " +
      "the unlucky person is? \n");
   add_item("sidewalk","A tall iron brazier stands on the " +
      "sidewalk.\n");
   
   add_exit(FROOM + "street34","east",0);
   add_exit(FROOM + "street36","south",0);
   add_exit(FROOM + "street31","west",0);
   
   reset_flotsam_room();
}

string
long_descr()
{
   return tod_descr1() + tod_descr2() + "You stand on a crowded " +
   "cobbled street in the town of Flotsam. Off-duty soldiers " +
   "and newly recruited mercenaries roaming from tavern to " +
   "tavern in search of cheap ale fill the streets, alongside " +
   "heavily armed patrols that seem to be searching for " +
   "something... or someone. A tall iron brazier stands off on " +
   "a sidewalk, relieving little of the gloom brought on by the " +
   "clouds overhead. " + season_descr() + "\n";
   
}

