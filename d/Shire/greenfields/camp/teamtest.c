inherit "/d/Shire/room";
#include "/d/Shire/greenfields/camp/tent.h"
#include "/d/Shire/orcmaker/orcmaker.h"
#include "/d/Shire/common/defs.h"


create_room()
{
   set_short("In the leader's tent");
  set_long("While not exactly opulent, this tent is definitely "+
    "well appointed.  Tapestries and rugs hang from each pole, "+
    "and others are scattered about the floor.  A raised dais "+
    "surmounted by a large, black chair dominates the center of "+
    "the tent. Still, it is obvious from the filth and stench that "+
    "the owner of this tent cares little for the actual materials "+
    "of the possessions, and likely just considers them "+
    "to be signs of power and strength.\n");
   
   TENT;
   HBED;
  add_item(({"dias","raised dias"}),
    "A simple dias, it is difficult to guess what it is made of "+
    "since the whole thing is draped with black rugs.\n");
  add_item(({"rugs","tapestries","rug","tapestry"}),
    "The rugs and tapestries here were likely once exquisate "+
    "pieces, but over time and through much abuse they have "+
    "deteriorated to bare threads.  A careful look shows that "+
    "the tapestries once depicted gruesome scenes of death and "+
    "dismemberment, however.\n");
  add_item(({"chair","large chair","black chair","large black chair"}),
    "This large black chair is very ornate, but very worn and much "+
    "abused by its owner.  Elaborate legs from some clawed, twisted "+
    "creature support the entire chair.  The wood and blackened "+
    "metal sections of the back form an eerie resemblance to a great "+
    "staring eye.\n");
   add_item(({"camp","outside"}), "The camp is outside, but you cannot "
   + "see it from in here.\n");
   add_prop(ROOM_I_INSIDE,1);
   add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);
   add_exit(GREEN_DIR + "camp/camp13","out",0,1);

   enable_reset();
   add_stuff();
}


reset_room() { add_stuff(); }


void
add_stuff()
{
   object chest, orcleader, orc1, orc2;
   FIXEUID;

  if(!present("chest"))
  {
    chest=clone_object(GREEN_DIR+"obj/hchest");
    chest->move(TO);
  }
   if (!present("leader"))
   {
     orcleader = clone_object(GREEN_DIR + "npc/hzzz");
     orcleader->add_name("leader");
     orcleader->move(TO);
   }

   if (!present("guard1"))
   {
     orc1 = clone_object(ORCMAKER_DIR + "orcmaker");
     orc1->set_long("This orc guard guards his boss to the death.\n");
     orc1->add_name("guard1");
     orc1->set_power(125 + random(10));
     orc1->set_type(WARRIOR);
     orc1->move(TO);
     orcleader->team_join(orc1);
   }

   if (!present("guard2"))
   {
     orc2 = clone_object(ORCMAKER_DIR + "orcmaker");
     orc2->add_name("guard2");
     orc2->set_power(70 + random(20));
     orc2->set_type(GUARD);
     orc2->move(TO);
     orcleader->team_join(orc2);
   }
}
