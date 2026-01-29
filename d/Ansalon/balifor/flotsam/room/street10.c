#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit FLOTSAM_OUT;
object sailor;

void
reset_flotsam_room()
{
   if(!objectp(sailor))
      {
      sailor = clone_object(FNPC + "sailor");
      sailor->arm_me();
      sailor->move(TO);
   }
}

create_flotsam_room()
{
   set_short("Edge of the docks in the northern parts of Flotsam");
   set_long("@@long_descr");
   
   add_item(({"docks","piers","dock","pier"}),"Sturdy " +
      "barnacle-covered jetties jut out into the Blood Bay, where " +
      "far-travelled ships that sail the Blood Sea dock. \n");
   add_item(({"sails","vessels","ships"}),"You look at the billowing " +
      "sails of ships that travel as far as Sancrist in the Turbidus " +
      "Ocean... for the right price of course. \n");
   add_item(({"street","streets","main streets"}),"The main " +
      "streets to the south are crowded with the likes of draconians, " +
      "goblins and evil mercenaries. Not pleasant company. \n");
   add_item(({"soldiers","mercenaries","freebooters"}),
      "Drunken soldiers of the Blue dragonarmy along side " +
      "newly recruited mercenaries stumble through the street. It would " +
      "be best to keep out of their way if you don't " +
      "want trouble.\n");
   // Exit to Faerun pier blocked as all traffic is going to route via
   // Sparkle - TAPAKAH.
   //add_exit(FROOM + "faerun_pier","north",0);
   add_exit(FROOM + "street11","south",0);
   add_exit(FROOM + "street07","west",0);
   
   reset_flotsam_room();
}

string
long_descr()
{
   return tod_descr1() + tod_descr2() + "You stand at the edge " +
   "of the docks of Flotsam. To the west you see the sails of " +
   "sea-going vessels docked at the towns many piers. To the south you can see the main " +
   "streets crowded with soldiers of the Dragonarmy and freelancers of all races, attracted " +
   "to the Highlords by high wages and the promise of spoils of " +
   "war. " + season_descr() + " \n";
}
