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
      "for several dwarves. You see four exits leading out "+
      "of this sleeping area.\n");

   add_item(({"wall","walls"}),"They are nothing of the usual "+
      "splendor of engineering that you expect from dwarves.\n");
   add_item(({"hole","holes"}),"They look like small peepingholes.\n");
   add_item(({"bed","beds","alcove","alcoves"}),
      "They are deep insertions into the walls, making room for "+
      "a deep dwarf to sleep.\n");

   INSIDE;
   add_prop(ROOM_I_LIGHT,0);

   add_exit(CPASS(dwarf/barracks/b12),"west");
   add_exit(CPASS(dwarf/barracks/b14),"east","@@guard");
   add_exit(CPASS(dwarf/barracks/b15),"north","@@guard");
   add_exit(CPASS(dwarf/barracks/b16),"south","@@guard");

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
   ob1->team_join(ob2);
   ob1->team_join(ob3);
   ob1->team_join(ob4);
   tell_room(TO,"Some dwarves leaves their alcoves to examine you.\n");
}

/* The npc's will block the way east */
int
guard()
{
   /* are we here ? */
   if (!present(ob1) && !present(ob2) && !present(ob3) && !present(ob4))
      return 0;

   /* are we fighting ? */
   if (ob1->query_attack() || ob2->query_attack() || 
       ob3->query_attack() || ob4->query_attack())
   {
      if(present(ob1)) 
         ob1->do_say("You must be joking, "+TP->query_name()+
            "! I am fighting now!!");
      if(present(ob2)) 
         ob2->do_say("Are you stupid, "+TP->query_name()+
            "? Help me kill this bugger first!");
      if(present(ob3)) 
         ob3->do_say("You must be joking, "+TP->query_name()+
            "! I am fighting now!!");
      if(present(ob4)) 
         ob4->do_say("Are you stupid, "+TP->query_name()+
            "? Help me kill this bugger first!");
      return 1;
   }

   /* is the player a dwarf ? */
   if (TP->query_race_name()=="dwarf")
   {
      if(present(ob1))
         ob1->do_say("A new soldier? Welcome!");
      if(present(ob2))
         ob2->do_say("Came to join us against those drows, are you. Good!");
      if(present(ob3))
         ob1->do_say("A new soldier? Welcome!");
      if(present(ob4))
         ob2->do_say("Came to join us against those drows, are you. Good!");
      return 0;
   }
   return 0;
}
