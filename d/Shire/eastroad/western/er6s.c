#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;

void add_stuff();

object bessie, farmer;

void
create_er_room()
{
   
   area = "not far";
   areaname = "Greenholm";
   land = "the Shire";
   areatype = 10;
   areadesc = "meadow";
   grass = "green";
   
   extraline = "This meadow south of the village Greenholm looks like "+
   "a place where cattle often graze, judging by the level at which the "+
   "grass is kept.  Be careful not to step in anything squishy!  The East Road "+
   "and the rest of the village lies north.";
   
   add_item(({"meadow","village"}),
      "The meadow here has very short, green grass and melds into the "+
      "village Greenholm to the north.\n");

   add_exit(EAST_R_DIR + "er6","north");
   add_exit(EAST_R_DIR + "er7s","east",0,1,1);
   add_exit(EAST_R_DIR + "er5s","west",0,1,1);   

   add_stuff();
}

void
reset_shire_room()
{
   add_stuff();
}

void
leave_inv(object ob, object from)
{
   ::leave_inv(ob, from);
   
   if(!interactive(ob)) return;
   
   else ob->catch_msg("You just barely avoid stepping in "+
         "one of the larger cow-patties.\n");
   
}

void
add_stuff()
{
   if (!bessie)
      {
      bessie = clone_object(ER_NPC + "cow");
   }
   
   if (!farmer)
      {
      farmer = clone_object(ER_NPC + "oldfarm");
      farmer->move(TO);
      bessie->move(TO);
      if (present(bessie,TO))
         farmer->team_join(bessie);
   }
}
