inherit "/d/Shire/room";
#include "/d/Shire/greenfields/camp/tent.h"
#include "/d/Shire/orcmaker/orcmaker.h"
#include "/d/Shire/common/defs.h"
#include "/d/Shire/common/make_money.h"


create_room()
{
   set_short("Inside an orc tent");
   set_long("From the very moment you enter this tent, you know "+
   "it belongs to a dedicated warrior who doesn't mind fighting "+
   "in his own quarters. Bloodstains splatter the walls with no "+
   "obvious pattern, except to signify the power of this occupant. "+
   "This tent belongs to Grushkir, second-in-command of this orc army, "+
   "and he would not be pleased to find you in here.\n");
   
   TENT;
   DIRT;
   WBED;
   add_item(({"blood stain","bloodstains","blood stains"}),
   "They are many different colored and you wonder exactly how "+
"many creatures have fallen at Grushkir's feet.\n");
   add_item(({"camp","outside"}), "The camp is outside, but you cannot "
   + "see it from in here.\n");
   add_item(({"bones","bone","pile"}), 
   "These bones have been gnarled beyond recognition.\n");

   add_item(({"bedroll","bedrolls","bed roll"}),
   "The bedrolls do little more than cover the dirt that these slave\n"
   + " orcs sleep on. They smell as if they have been washed in vomit\n"
   + " quite recently.\n");
   
   add_prop(ROOM_I_INSIDE,1);
   
   add_exit(GREEN_DIR + "camp/camp12","out",0,1);

   enable_reset();
   add_stuff();
   reset_room();
}

reset_room() { add_stuff(); }
void
add_stuff()
{
   object chest, orcleader, orc1, orc2;
   FIXEUID;

   if(!present("chest"))
   {
      chest=clone_object(GREEN_DIR+"obj/mchest");
      chest->move(TO);
   }
   if (!present("leader"))
   {
     orcleader = clone_object(GREEN_DIR + "npc/mzzz");
     orcleader->add_name("leader");
     orcleader->add_prop("_live_m_no_drain", 1);
     orcleader->move(TO);
   }

   if (!present("guard1"))
   {
     orc1 = clone_object(ORCMAKER_DIR + "orcmaker");
     orc1->set_long("This orc guard guards his boss to the death.\n");
     orc1->add_name("guard1");
     orc1->set_power(110 + random(10));
     orc1->set_type(WARRIOR);
     orc1->move(TO);
     orcleader->team_join(orc1);
   }

   if (!present("guard2"))
   {
     orc2 = clone_object(ORCMAKER_DIR + "orcmaker");
     orc2->add_name("guard2");
     orc2->set_power(120 + random(20));
     orc2->set_type(GUARD);
     orc2->move(TO);
     orcleader->team_join(orc2);
   }
}
