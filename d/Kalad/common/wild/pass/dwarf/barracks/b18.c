inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

/* by korat  -  barracks, a hunting ground. */

object ob1;
object ob2;

create_room()
{
   ::create_room();
   set_short("A hallway");
   set_long("This engineered cave is not of the usual dwarven "+
      "excellence, but is ment more for functionality than "+
      "anything else. The walls are rough but fairly flat, ending "+
      "in an arching ceiling. Not much can be seen here except "+
      "some small holes in the northern wall. The only exit is to "+
      "the east.\n");

   add_item(({"wall","walls"}),"They are nothing of the usual "+
      "splendor of engineering that you expect from dwarves.\n");
   add_item(({"hole","holes"}),"They look like small peepingholes.\n");

   INSIDE;
   add_prop(ROOM_I_LIGHT,0);

   add_exit(CPASS(dwarf/barracks/b16),"east");
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

   /* we need to give the leader some dis */
   ob1->set_stat(5,100);
   ob1->team_join(ob2);
   tell_room(TO,"Some dwarves stands up as you arrive.\n");
}

