#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit FLOTSAM_OUT;
object drac1;
object merc;
object gob1;

void
reset_flotsam_room()
{
   if(!objectp(drac1))
      {
      drac1 = clone_object(KNPC + "sivak");
      drac1->move(TO);
   }
   if(!objectp(gob1))
      {
      gob1 = clone_object(KNPC + "goblin");
      gob1->move(TO);
   }
   if(!objectp(merc))
      {
      merc = clone_object(KNPC + "mercenary");
      merc->move(TO);
   }
}

create_flotsam_room()
{
   set_short("Crowded street outside an ill-kept tavern in Flotsam");
   set_long("@@long_descr");
   
   add_item(({"street","crowded street"}),"You stand " +
      "in a filthy, crowded street in the western parts " +
      "of Flotsam. \n");
   add_item("tavern","This disputable tavern can only be described " +
      "as a dive. At one stage, this bar may have had an air of " +
      "respectability about it, but after many fires and wild brawls " +
      "its appearance has long changed to that of a pile of wood taking " +
      "its own lazy time about falling into the street. Over the door " +
      "the tavern signboard depicts a poorly drawn troll hoisting a " +
      "half-filled flagon in merriment, with an almost illegible " +
      "'The Tanked Troll' scrawled beneath it. \n");
   add_item("clouds","Gloomy clouds seem to hover over Flotsam " +
      "permanantly these days.\n");
   add_item("slums","East of this road marks the slums area of Flotsam. It makes up a fair " +
      "bit of it you notice.\n");
   add_item("upper-middleclass section","To the west and up a small " +
      "rise is the section considered to be Flotsams upper-" +
      "middleclass district.\n");
   
   add_exit(FROOM + "street40","north",0);
   add_exit(FROOM + "tavern02","east","@@ent_tav",0);
   add_exit(FROOM + "street42","south",0);
   add_exit(FROOM + "street43","west",0);
   
   reset_flotsam_room();
}

string
long_descr()
{
   return tod_descr1() + tod_descr2() + "You stand on " +
   "a crowded street in the western parts of Flotsam. " +
   "To your west, the street slopes upwards towards the " +
   "more refined area of Flotsam. To the east, a busy, " +
   "ill-kept tavern marks the borders between the slums " +
   "and upper-middleclass sections of Flotsam. " +
   season_descr() + "\n";
}

int
ent_tav()
{
   write("You step into the tavern of the Tanked Troll... \n");
   return 0;
}
