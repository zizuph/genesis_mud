#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit FLOTSAM_OUT;
object kender;

void
reset_flotsam_room()
{
   if(!objectp(kender))
      {
      kender = clone_object(FNPC + "kender");
      kender->move(TO);
   }
}

create_flotsam_room()
{
   set_short("Crossroad in the town of Flotsam");
   set_long("@@long_descr");
   
   add_item(({"brazier","iron brazier","tall iron brazier"}),"A " +
      "tall iron brazier, its light casting dark shadows on the " +
      "walls of the surrounding buildings. \n");
   add_item("sidewalk","A dirty sidewalk on a crossroad in Flotsam. " +
      "\n");
   add_item("clouds","Overhead loom gloomy clouds that seem to " +
      "hover over Flotsam every minute of the day. \n");
   
   add_exit(FROOM + "street16","north",0);
   add_exit(FROOM + "street18","east",0);
   add_exit(FROOM + "street27","south",0);
   add_exit(FROOM + "street14","west",0);
   
   reset_flotsam_room();
}

string
long_descr()
{
   return tod_descr1() + tod_descr2() + "You stand on a filthy " +
   "cobblestone crossroad in the occupied town of Flotsam. A tall " +
   "iron brazier stands off on a sidewalk, relieving little of the " +
   "gloom brought on by clouds overhead. " + season_descr() +
   "\n";
}
