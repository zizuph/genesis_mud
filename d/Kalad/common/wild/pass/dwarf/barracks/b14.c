inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

/* by korat  -  barracks, a hunting ground. */

object ob1;
object ob2;
object ob3;
object ob4;

create_room()
{
   ::create_room();
   set_short("Barracks in Underhome");
   set_long("This engineered cave is not of the usual dwarven "+
      "excellence, but is ment more for functionality than "+
      "anything else. The walls are rough but fairly flat, ending "+
      "in an arching ceiling. In this part of the cave, several "+
      "alcoves has been formed from the rock - making room "+
      "for several dwarves. A fireplace can be seen in the "+
      "eastern end, lighting up the room as well as heating "+
      "up all of this cavern. The only exit is back west.\n");

   add_item(({"wall","walls"}),"They are nothing of the usual "+
      "splendor of engineering that you expect from dwarves.\n");
   add_item(({"bed","beds","alcove","alcoves"}),
      "They are deep insertions into the walls, making room for "+
      "a deep dwarf to sleep.\n");
   add_item(({"fire","fireplace"}),"Some logs are burning in it.\n");

   INSIDE;
   add_prop(ROOM_I_LIGHT,1);

   add_exit(CPASS(dwarf/barracks/b13),"west");

   set_alarm(1.0,0.0,"reset_room");
}

void
reset_room()
{
   if(!objectp(ob1))
      {
      ob1=clone_object(CPASS(dwarf/npc/dwarf_guard));
      ob1->arm_me();
      ob1->move_living("M",TO);
   }
   if(!objectp(ob2))
      {
      ob2=clone_object(CPASS(dwarf/npc/dwarf_guard));
      ob2->arm_me();
      ob2->move_living("M",TO);
   }
   if(!objectp(ob3))
      {
      ob3=clone_object(CPASS(dwarf/npc/dwarf_guard));
      ob3->arm_me();
      ob3->move_living("M",TO);
   }
   if(!objectp(ob4))
      {
      ob4=clone_object(CPASS(dwarf/npc/dwarf_guard));
      ob4->arm_me();
      ob4->move_living("M",TO);
   }

   /* we need to give the leader some dis */
   ob1->set_stat(5,100);

   /* we give these a bit better combat stats - str and con */
   ob1->set_stat(0,ob1->query_stat(0)+20);
   ob2->set_stat(0,ob2->query_stat(0)+20);
   ob3->set_stat(0,ob3->query_stat(0)+20);
   ob4->set_stat(0,ob4->query_stat(0)+20);
   ob1->set_stat(2,ob1->query_stat(2)+20);
   ob2->set_stat(2,ob2->query_stat(2)+20);
   ob3->set_stat(2,ob3->query_stat(2)+20);
   ob4->set_stat(2,ob4->query_stat(2)+20);

   ob1->team_join(ob2);
   ob1->team_join(ob3);
   ob1->team_join(ob4);
   tell_room(TO,"Some dwarves leaves their alcoves to examine you.\n");
}

