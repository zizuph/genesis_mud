

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit FLOTSAM_OUT;
object drac1;
object merc;

void
reset_flotsam_room()
{
   if(!objectp(drac1))
      {
      drac1 = clone_object(KNPC + "bozak");
      drac1->move(TO);
   }
   if(!objectp(merc))
      {
      merc = clone_object(KNPC + "mercenary");
      merc->move(TO);
   }
}

create_flotsam_room()
{
   set_short("Crossroad in the streets of Flotsam");
   set_long("@@long_descr");
   
   add_item(({"brazier","iron brazier","tall iron brazier"}),"A tall " +
      "iron brazier, its light casting dark shadows on the walls of the surrounding buildings. \n");
   
   add_item("sidewalk","A dirty sidewalk on a cobblestone crossroad in Flotsam \n");
   add_item("clouds","Gloomy clouds, that seem to hang around Flotsam " +
      "all the year long. \n");
   add_item(({"crossroad","cobblestone","cobblestone crossroad"}),"A " +
      "dirty, cobblestone crossroad in the centre of Flotsam. \n");
   
   add_exit(FROOM + "street10","north",0);
   add_exit(FROOM + "street16","east",0);
   add_exit(FROOM + "street14","south",0);
   add_exit(FROOM + "street12","west",0);
   
   reset_flotsam_room();
}

string
long_descr()
{
   return tod_descr1() + tod_descr2() + "You stand at a filthy, " +
   "cobblestone crossroad in the occupied town of Flotsam. A tall " +
   "iron brazier stands off on a sidewalk, relieving little of the " +
   "gloom brought on by the clouds overhead. " + season_descr() +
   " \n";
}
