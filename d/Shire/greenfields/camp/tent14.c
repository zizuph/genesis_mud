inherit "/d/Shire/room";
#include "/d/Shire/greenfields/camp/tent.h"
#include "/d/Shire/orcmaker/orcmaker.h"
#include "/d/Shire/common/defs.h"


create_room()
{
   set_short("Inside an orc tent");
   set_long("This tent is even dirtier than the camp outside, "+
   "full of smelly things. The orcs obviously don't take much "+
   "pride in keeping their homes clean. Bedrolls and beds are scattered in all "+
   "directions, and some bones are piled up in a corner.\n");
   
   TENT;
   DIRT;
   WBED;
   add_item(({"camp","outside"}), "The camp is outside, but you cannot "
   + "see it from in here.\n");
   add_item(({"bones","bone","pile"}), 
   "These bones have been gnarled beyond recognition.\n");

   add_item(({"bedroll","bedrolls","bed roll"}),
   "The bedrolls do little more than cover the dirt that these slave\n"
   + "orcs sleep on. They smell as if they have been washed in vomit\n"
   + "quite recently.\n");
   
   add_prop(ROOM_I_INSIDE,1);
   
   add_exit(GREEN_DIR + "camp/camp14","out",0,1);

   enable_reset();
   add_stuff();
   reset_room();
}

reset_room() { add_stuff(); }
void
add_stuff()
{
   object orcleader, orc1, orc2, orc3;
   FIXEUID;

   if (!present("leader"))
   {
     orcleader = clone_object(ORCMAKER_DIR + "orcmaker");
     orcleader->set_long("This is an monstrously large orc guard.\n");
     orcleader->add_name("leader");
     orcleader->set_power(80 + random(60));
     orcleader->set_type(WARRIOR);
     orcleader->move(TO);
   }

   if (!present("guard1"))
   {
     orc1 = clone_object(ORCMAKER_DIR + "orcmaker");
     orc1->set_long("This orc guard is eyeing you warily.\n");
     orc1->add_name("guard1");
     orc1->set_power(90 + random(35));
     orc1->set_type(WARRIOR);
     orc1->move(TO);
     orcleader->team_join(orc1);
   }

   if (!present("guard2"))
   {
     orc2 = clone_object(ORCMAKER_DIR + "orcmaker");
     orc2->add_name("guard2");
     orc2->set_power(100 + random(20));
     orc2->set_type(WARRIOR);
     orc2->move(TO);
     orcleader->team_join(orc2);
   }
if (random(3))
   {
   if (!present("guard3"))
     {
     orc3 = clone_object(ORCMAKER_DIR + "orcmaker");
     orc3->add_name("guard3");
     orc3->set_power(50 + random(80));
     orc3->set_type(WARRIOR);
     orc3->move(TO);
     orcleader->team_join(orc3);
    }
   }
}
