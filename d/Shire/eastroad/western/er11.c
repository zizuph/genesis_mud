#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;

object ob;

void
create_er_room()
{
   
   area = "close to"; /* Distance from areaname */
   areaname = "Waymeet";
   land = "the Shire";
   areatype = 8;
   areadesc = "undulating plain";
   grass = "lush and green";
   
   extraline =  "You are not far from a cross-road to the east, "
   +"where roads from the north and the south meet in the "
   +"hamlet of Waymeet. The northern road leads to Nobottle "
   +"and Needlehole, while the southern road leads to Whitwell. "
   +"To the west lies Michel Delving, and beyond that, Mithlond, "
   +"while beyond Waymeet are the villages of Hobbiton and Bree.";
   
   add_item("michel delving",
      "Far to the west,  Michel Delving is barely visible from here.\n");
   
   add_item("hobbiton",
      "The former capital of the Shire lies off the Great "
      +"East Road, next to The Water.\n");
   
   add_item("bree",
      "If you keep going past Hobbiton, you will eventually get to "
      +"Bree.\n");
   
   add_item("whitwell",
      "South of Waymeet, Whitwell is a typical hobbit hamlet.\n");
   
   add_item("nobottle",
      "Off the Great East Road to the north, Nobottle is a small "
      +"hamlet like many others in the Shire.\n");
   
   add_item("needlehole",
      "Near Nobottle, the hamlet of Needlehole is famous within "
      +"the Shire for its tailor.\n");
   
   add_item(({"mithlond","grey havens"}),
      "Mithlond, or Grey Havens, lies beyond the White Downs "
      +"to the west of you.  It is a large city beside the sea, "
      +"and has ships to many foreign lands.\n");
   
   add_item("waymeet",
      "The hamlet of Waymeet lies a few miles to the east, "
      +"just over a rise.\n");

   add_exit(EAST_R_DIR + "er10","west");
   add_exit(EAST_R_DIR + "er12","east");
   add_exit(EAST_R_DIR + "er11n","north",0,2,1);
   add_exit(EAST_R_DIR + "er11s","south",0,2,1);
      
   reset_shire_room();
}

void
reset_shire_room() 
{   
// if(!ob) 
    if (!objectp(ob))
   {
      ob = clone_object(HOBBIT_DIR + "npc/quest_hobbit");
/*
      ob->set_restrain_path(({"/d/Shire/eastroad/western", 
                             "/d/Shire/eastroad/village/whit",
                             "/d/Shire/common/hobbiton",
                             "/d/Shire/michel" }));
      ob->set_random_move(3);
*/
      ob->set_monster_home("/d/Shire/eastroad/western/er11");
      ob->move(this_object());
   }
}
