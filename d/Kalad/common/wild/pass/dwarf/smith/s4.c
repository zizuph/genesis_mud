inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by korat */

object ob1;
object ob2;
object ob3;
object ob4;

create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   set_short("within a smith in Underhome");
   set_long("This room looks like the storage room for "+
      "the metal ore that the blacksmith slowly hammers into "+
      "weapons and armours. There is nothing more in here except "+
      "some large crates in the eastern end of the room.\n");
   add_item("ore","The ore looks like iron, being red in colour.\n");
   add_item(({"crates","crate"}),"@@crate@@");
   
   add_exit(CPASS(dwarf/smith/s1),"southwest",0,-1,-1);
   set_alarm(2.0,0.0,"reset_room");
   
}

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
   ob1->team_join(ob2);
   ob1->team_join(ob3);
   ob1->team_join(ob4);
   tell_room(TO,"Some dwarves arrive while others leave.\n");
}

init()
{
   ::init();
   add_action("search","search");
}
search(string str)
{
   NF("Search what?\n");
   if(!str || (str!="crates" && str!="crate"))
      return 0;
   if(present("guard",E(TO)))
      {
      notify_fail("The deep dwarves stops you in your attempt to search them.\n");
      return 0;
   }
   write("You start to search the crates.\n");
   say(QCTNAME(TP)+" starts to search the crates.\n");
   set_alarm(5.0,0.0,"search_result",TP);
   return 1;
}
search_result(object who)
{
   object person;
   if(person=present(who,E(TO)))
      {
      person->catch_msg("You see a tunnel behind them, well hidden.\n");
      return;
   }
}

enter()
{
   if(present("deep dwarf",E(TO)))
      {
      if(TP->query_race()!="dwarf")
         {
         TP->catch_msg("The dwarves stops you when you walk towards the crates.\n");
         return 1;
      }
      TP->catch_msg("The deep dwarf whispers to you: "+
         "Take care in there ... beware of the drows!\n");
      return 0;
   }
   TP->catch_msg("You start to climb through the opening.\n");
   return 0;
}

crate()
{
   return "They are almost covering the eastern wall.\n";
}
