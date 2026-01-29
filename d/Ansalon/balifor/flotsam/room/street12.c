
/* Crowded street in Flotsam            */

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit FLOTSAM_OUT;
object drac1;
object gob1;

void
reset_flotsam_room()
{
   if (!objectp(drac1))
      {
      drac1 = clone_object(KNPC + "bozak");
      drac1->move(TO);
   }
   if(!objectp(gob1))
      {
      gob1 = clone_object(FNPC + "tiny_gob");
      gob1->move(TO);
   }
}


create_flotsam_room()
{
   set_short("Crowded street in the town of Flotsam");
   set_long("@@long_descr");
   
   add_item(({"cobbled street","street"}),"A filthy, cobbled street " +
      "crowded with the likes of goblins, draconians, and " +
      "mercenaries. \n");
   add_item("patrols","Heavily armed patrols wander the streets, " +
      "stopping newcomers to Flotsam, interrogating them, and " +
      "occasionally arresting them. You wonder what they are looking " +
      "for? \n");
   add_item(({"soldiers","mercenaries"}),"Drunken soldiers of " +
      "the Blue Dragonarmy alongside newly recruited " +
      "mercenaries stumble through the street. It would be " +
      "best to keep out of their way if you dont want " +
      "trouble. \n");
   add_item("warehouse","A large wooden warehouse, probably used for " +
      "storing food for the Dragonarmies. \n");
   
   add_exit(FROOM + "street11","east",0);
   add_exit(FROOM + "ware01", "west", "@@ware_ent", 0);
   add_exit(FROOM + "street13","south",0);
   
   reset_flotsam_room();
}

string
long_descr()
{
   return tod_descr1() + tod_descr2() + "You stand on a crowded " +
   "cobbled street in the town of Flotsam. " +
   "Off duty soldiers, and newly recruited mercenaries, " +
   "roaming from tavern to tavern in search of cheap ale fill " +
   "the streets, alongside heavily armed patrols that seem to be " +
   "searching for something... or someone. " +
   "The streets continue on to the south and east, while to the " +
   "west there is some kind of warehouse. " + season_descr() +
   " \n";
}

int
ware_ent()
{
   write("You enter the warehouse... \n");
   return 0;
}

