
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit FLOTSAM_OUT;
object drac1;
object drac2;
object drac3;
object drac4;
object gob1;
object gob2;
object sailor;
object merc;

void
reset_flotsam_room()
{
   if(!objectp(drac1))
      {
      drac1 = clone_object(FNPC + "sivak_leader");
      drac1->move(TO);
   }
   if(!objectp(drac2))
      {
      drac2 = clone_object(KNPC + "ogre");
      drac2->move(TO);
   }
   if(!objectp(drac3))
      {
      drac3 = clone_object(KNPC + "baaz");
      drac3->move(TO);
   }
   if(!objectp(drac4))
      {
      drac4 = clone_object(KNPC + "baaz");
      drac4->move(TO);
   }
   if(!objectp(gob1))
      {gob1 = clone_object(KNPC + "goblin");
      gob1->move(TO);
   }
   if(!objectp(gob2))
      {
      gob2 = clone_object(KNPC + "goblin");
      gob2->move(TO);
   }
   if(!objectp(sailor))
      {
      sailor = clone_object(FNPC + "sailor");
      sailor->arm_me();
      sailor->move(TO);
   }
   if(!objectp(merc))
      {
      merc = clone_object(KNPC + "mercenary");
      merc->move(TO);
   }
}

create_flotsam_room()
{
   set_short("Crowded street in the centre of Flotsam");
   set_long("@@long_descr");
   
   add_item(({"cobbled street","street"}),"A well-used, dirty cobbled " +
      "street. \n");
   add_item(({"drunken sailors","sailors"}),"Drunken sailors stagger from " +
      "local Inns back towards the general area of their " +
      "ship. You would put even bets on them making it " +
      "back before they leave.\n");
   add_item(({"mercenaries","soldiers"}),"Drunken soldiers " +
      "of the Blue Dragonarmy along side newly recruited " +
      "mercenaries stumble through the street. It would be " +
      "best to keep out of their way if you don't want trouble.\n");
   add_item("patrols","Heavily armed patrols " +
      "wander the streets, stopping newcomers to Flotsam, " +
      "interrogating them, and occasionally arresting them. You " +
      "wonder what they are looking for?\n");
   add_item(({"office","harhourmasters office","remains",
            "burned remains"}),"The " +
      "charred and burned remains of the harbourmasters " +
      "office. From the looks of the scorched cobblestones " +
      "around it, the office looks like it had been " +
      "struck by lightning... multiple times. \n");
   
   add_exit(FROOM + "street11","north",0);
   add_exit(FROOM + "street15","east",0);
   add_exit(FROOM + "street13","west",0);
   
   reset_flotsam_room();
}

string
long_descr()
{
   return tod_descr1() + tod_descr2() + "You stand on a crowded " +
   "cobbled street in the town of Flotsam. Newly recruited " +
   "mercenaries and off-duty soldiers wander the streets, " +
   "and drunken sailors stagger north back towards their " +
   "docked ships. To the south stands the burned remains " +
   "of the harbourmasters office. " + season_descr() + 
   "\n";
   
}

