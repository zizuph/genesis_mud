#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit FLOTSAM_OUT;
object drac1;
object merc;
object kid1;
object kid2;

void
reset_flotsam_room()
{
   if(!objectp(drac1))
      {
      drac1 = clone_object(KNPC + "kapak");
      drac1->move(TO);
   }
   if(!objectp(merc))
      {
      merc = clone_object(KNPC + "mercenary");
      merc->move(TO);
   }
   if(!objectp(kid1))
      {
      kid1 = clone_object(FNPC + "kid");
      kid1->arm_me();
      kid1->move(TO);
   }
   if(!objectp(kid2))
      {
      kid2 = clone_object(FNPC + "kid");
      kid2->arm_me();
      kid2->move(TO);
   }
}

create_flotsam_room()
{
   set_short("Crowded street in the town of Flotsam");
   set_long("@@long_descr");
   
   add_item(({"street","cobbled street"}),"A filthy, well-used " +
      "cobbled street. \n");
   add_item(({"warehouse","warehouses"}),"The warehouses " +
      "that line the street seem to have been cleared " +
      "out recently, probably awaiting the arrival of " +
      "provisions for the Dragonarmies. \n");
   add_item(({"youths","homeless youths","homeless"}),"Gangs " +
      "of homeless youths call the warehouses of this " +
      "area their home. Fights often break out amongst " +
      "them it seems, probably due to hunger or boredom \n");
   add_item("poster","A ragged poster on one of the " +
      "ware houses shows a rough picture of a weathered " +
      "human male with youthful eyes. Underneath the picture " +
      "a sizeable reward is offered by the highlord for his " +
      "capture. \n");
   
   add_exit(FROOM + "street19","east",0);
   add_exit(FROOM + "street15","west",0);
   
   reset_flotsam_room();
}

string
long_descr()
{
   return tod_descr1() + tod_descr2() + "You stand on a crowded " +
   "street in the town of Flotsam. Disused warehouses " +
   "line the street, housing gangs of homeless youths. " +
   "A poster has been nailed to the wall of one " +
   "of these warehouses. " +
   season_descr() + "\n";
}
