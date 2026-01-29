/* Barracks */
/* Made by Korat 100195 */
inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include "/sys/filter_funs.h"

int guards_present;
object ob1;
object ob2;
object ob3;

void
create_room()
{
   ::create_room();
   add_prop(ROOM_I_INSIDE,1);
   hear_bell = 2;
   set_short("Barracks");
   set_long("This is the barracks for the militia officers, hired by the "+
      "city council to protect the city of Kabal. "+
      "@@officers_here@@");
   
   add_exit(CENTRAL(barracks/entrance),"south",0,-1,-1);
   add_exit(CENTRAL(barracks/barracks3),"up","@@stop_player",-1,-1);
   
   add_item (({"table"}),"A simple wooden table, ruined by several "+
      "carvings and food-stains. On it you notice several maps and "+
      "unsigned orders.\n");
   add_item(({"maps","orders"}),"The maps on the table shows the "+
      "plaza and its surrounding streets, while the rest of the papers "+
      "looks like orders for the guards.\n");
   add_item (({"officer","officers"}),"@@exa_guards");
   
   set_alarm(0.0,0.0,"reset_room");
}

void
reset_room()
{
   guards_present = 0;
   return;
}

officers_here()
{
   if (guards_present)
      return "In the middle of the room, you see a table filled with papers. "+
   "This must be where the officers make their plans and decides "+
   "on what orders to give to the guards under their command.\n";
   else
      return "In the middle of the room you see some of the officers "+
   "standing beside a table, "+
   "in deep discussion about some topic. It would be "+
   "wise to leave them undisturbed...\n";
}

int
stop_player()
{
   object *ob;
   int pres,i;
   ob = all_inventory(this_room());
   pres = 0;
   for (i=0;i<sizeof(ob); i++)
   {
      if (ob[i]->query_npc() && ob[i]->query_name() == "Officer")
         pres = 1;
   }
   if (pres == 1)
      {
      if (ob1) ob1->command("shout You ain't going up there!");
      if (ob2) ob2->command("emote steps in front of the "+
            "stairway with his sword ready for action.");
      if (ob3) ob3->command("say You wretch! Going to assasinate "+
            "our captain? We will see about that!");
   }
   if (pres == 0 && guards_present == 0)
      {
      pres = 1;
      write("The guards at the table frowns at you, and stops "+
         "you from going up.\n");
      say(QCTNAME(TP)+" tried to walk up the stairway, but "+
         "was stopped by the officers.\n");
   }
   return pres;
}

exa_guards()
{
   if(TP->query_base_stat(SS_DIS) < 50)
      {
      write ("You don't dare to disturb the officers!\n");
      say(QCTNAME(TP) + " tries to force himself to disturb " +
         "the officers, but lacks the courage.\n");
      return 1;
   }
   say (QCTNAME(TP) + " walks closer to the officers and starts to examine them. "+
      "The officers turn around and frowns.\n");
   if(guards_present)
      return "The officers decide to ignore you and keeps on with "+
   "their discussion.\n";
   guards_present = 1;
   set_alarm(1.0,0.0,"wake_guards");
   return "The officers roars angrily and stop their discussion.\n";
}

wake_guards()
{
   if (!objectp(ob1))
      {
      ob1 = clone_object("/d/Kalad/common/central/npc/militia_officer");
      ob1 -> arm_me();
      ob1 -> set_aggressive(1);
      ob1 -> move_living("M", TO);
      tell_room(TO,"The officer turns towards you and attacks!\n");
      ob1 -> command("kill "+ QTNAME(TP));
   }
   if (!objectp(ob2))
      {
      ob2 = clone_object("/d/Kalad/common/central/npc/militia_officer");
      ob2 -> arm_me();
      ob2 -> set_aggressive(1);
      ob2 -> move_living("M", TO);
      tell_room(TO,"The officer turns towards you and attacks!\n");
   }
   if (!objectp(ob3))
      {
      ob3 = clone_object("/d/Kalad/common/central/npc/militia_officer");
      ob3 -> arm_me();
      ob3 -> set_aggressive(1);
      ob3 -> move_living("M", TO);
      tell_room(TO,"The officer turns towards you and attacks!\n");
   }
   ob1 -> team_join(ob2);
   ob1 -> team_join(ob3);
}

