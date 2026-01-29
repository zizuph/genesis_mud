inherit "/d/Shire/room";
#include "/d/Shire/greenfields/camp/tent.h"
#include "/d/Shire/orcmaker/orcmaker.h"
#include "/d/Shire/common/defs.h"



create_room()
{
   set_short("Inside an orc tent");
   set_long("This tent is even dirtier than the camp outside, with sacks "+
   "full of smelly things. The orcs must not have time "+
   "to keeping their humble tents clean. Bedrolls and beds are scattered in all "+
   "directions, and some pots are piled up in a corner.\n");
   
   TENT;
   KITCHEN;
   DIRT;
   SBED;
   add_item(({"sacks","sack"}), "These sacks carry something "
   + "that smells horrible!\n");
   add_item(({"camp","outside"}), "The camp is outside, but you cannot "
   + "see it from in here.\n");

   add_item(({"bedroll","bedrolls","bed roll"}),
   "The bedrolls do little more than cover the dirt that these slave\n"
   + "orcs sleep on. They smell as if they have been washed in vomit\n"
   + "quite recently.\n");
   
   add_prop(ROOM_I_INSIDE,1);
   
   add_exit(GREEN_DIR + "camp/camp04","out",0,1);

   enable_reset();
   add_stuff();
}

void
add_stuff()
{
   object orcleader, orc1, orc2;
   FIXEUID;

   if (!present("leader"))
   {
     orcleader = clone_object(ORCMAKER_DIR + "orcmaker");
     orcleader->set_long("This is an unusually burly orc slave.\n");
     orcleader->add_name("leader");
     orcleader->set_power(40 + random(31));
     orcleader->set_type(SLAVE);
     orcleader->move(TO);
   }

   if (!present("slave1"))
   {
     orc1 = clone_object(ORCMAKER_DIR + "orcmaker");
     orc1->set_long("This is a little orc slave. He is fierce, though.\n");
     orc1->add_name("slave1");
     orc1->set_power(40);
     orc1->set_type(SLAVE);
     orc1->move(TO);
     orc1->team_join(orcleader);
   }

   if (!present("slave2"))
   {
     orc2 = clone_object(ORCMAKER_DIR + "orcmaker");
     orc2->set_long("This orc looks ready to bite your ears off!\n");
     orc2->add_name("slave2");
     orc2->set_power(35+random(16));
     orc2->set_type(SLAVE);
     orc2->move(TO);
     orc2->team_join(orcleader);
   }
}
