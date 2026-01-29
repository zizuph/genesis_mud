inherit "/d/Shire/room";
#include "/d/Shire/greenfields/camp/tent.h"
#include "/d/Shire/orcmaker/orcmaker.h"
#include "/d/Shire/common/defs.h"


create_room()
{
   set_short("Inside an orc tent");
   set_long("This tent is a bit neater than the camp outside, with sacks "+
   "full of smelly things. The orcs must not have time "+
   "to to do anything but cook for the others. There is a stove "+
   "in the center of the tent and a hole in the top lets the "+
   "most foul of the odors out. "+
   "directions, and some pots are piled up in a corner.\n");
   
   TENT;
   KITCHEN;
   DIRT;
   SBED;

   add_item(({"sacks","sack"}), "These sacks carry something "
   + "that smells horrible!\n");

   add_item(({"stove","center","hole"}),
   "The stove has several pots heating on it, from those pots you smell the stench "+
   "of humanoid meat bubbling in some kind of blood sauce. You definitely don't "+
   "want any of that stuff!!!\n");
   add_item(({"camp","outside"}), "The camp is outside, but you cannot "
   + "see it from in here.\n");

   add_item(({"bedroll","bedrolls","bed roll"}),
   "The bedrolls do little more than cover the dirt that these slave\n"
   + "orcs sleep on. They smell as if they have been washed in vomit\n"
   + "quite recently.\n");
   
   add_prop(ROOM_I_INSIDE,1);
   
   add_exit(GREEN_DIR + "camp/camp06","out",0,1);

   enable_reset();
   add_stuff();
}

void
add_stuff()
{
   object orcleader, orc1, orc2, orc3;
   FIXEUID;

   if (!present("leader"))
   {
     orcleader = clone_object(ORCMAKER_DIR + "orcmaker");
     orcleader->set_long("This seems to be the cook. I wouldn't disturb him.\n");
     orcleader->add_name("leader");
     orcleader->set_power(45 + random(21));
     orcleader->set_type(SLAVE);
     orcleader->move(TO);
   }

   if(!present("slave1"))
   {
     orc1 = clone_object(ORCMAKER_DIR + "orcmaker");
     orc1->set_long("This is a little orc slave. He is busy stirring the pots.\n");
     orc1->add_name("slave1");
     orc1->set_power(49);
     orc1->set_type(SLAVE);
     orc1->move(TO);
     orc1->team_join(orcleader);
   }

   if (!present("slave2"))
   {
     orc2 = clone_object(ORCMAKER_DIR + "orcmaker");
     orc2->set_long("This orc looks ready to eat you whole!\n");
     orc2->add_name("slave2");
     orc2->set_power(55);
     orc2->set_type(SLAVE);
     orc2->move(TO);
     orc2->team_join(orcleader);
     }


   if(random(6))
   {
     if(!present("slave3"));
     {
      orc3 = clone_object(ORCMAKER_DIR + "orcmaker");
      orc3->set_long("This orc seems to be watching the others.\n");
       orc3->add_name("slave3");
     orc3->set_type(WARRIOR);
     orc3->set_power(125);
     orc3->move(TO);
      orc3->team_join(orcleader);
     }
   }
}
