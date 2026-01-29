/* 
 * /d/Kalad/common/wild/pass/nhut.c
 * Purpose    : Home of an NPC
 * Located    : North in Hespyre Mountains
 * Created By : Antharanos  
 * Modified By: 
 */ 

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/filter_funs.h"
object ob1;
object ob2;
/* by Antharanos */
void
create_room()
{
   ::create_room();
   add_prop(ROOM_I_INSIDE,1);
   add_prop(OBJ_I_HAS_FIRE,1);
   set_short("Chieftan's Hut");
   set_long("You are within the largest hut of the village, the chieftan's "+
      "dwelling. This enormous room is dominated by a huge iron pot lying "+
      "at the exact center, below that pot is an intense fire. Strange "+
      "vapors rise from the pot and drift out past a small hole in the "+
      "ceiling. A giant bed lies opposite of you while bones lie scattered "+
      "about the floor. A hideous portrait hangs on one wall of the hut.\n");
   add_item(({"huge iron pot","huge pot","iron pot","pot"}),"A gigantic "+
      "cauldron made entirely out of iron, it must be at least ten feet "+
      "wide!\n");
   add_item(({"intense fire","fire"}),"It glows so brightly that it "+
      "glows white instead of red.\n");
   add_item(({"vapors"}),"Swirling about you, they smell a bit unusual.\n");
   add_item(({"hole","ceiling"}),"In the thatched roof of the hut, is "+
      "a small circular hole, just large enough to allow the vapors to leave "+
      "the hut.\n");
   add_item(({"giant bed","bed"}),"An enormous bed, it stretches twenty feet from "+
      "head to toe, and twelve feet across. It doesn't look very comfortable.\n");
   add_item(({"hideous portrait","portrait"}),
      "\n"+
      "                      &&&&&&&&&&&&&&&\n"+
      "                    &&&&&&&&&&&&&&&&&&&\n"+
      "                   &&&&^^^^^^^^^^^^^&&&&\n"+
      "                   ( )  (*) ()  (*)  ( )\n"+
      "                    ()     (  )      ()\n"+
      "                     (               )\n"+
      "                      (   (----)   )\n"+
      "                       ~&&&&&&&&&&~\n"+
      "                         &&&&&&&&\n"+
      "                          ******\n"+
      "\n");
   add_exit("/d/Kalad/common/wild/pass/w31", "out",0);
   set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
   if (!ob1)
      {
      ob1 = clone_object("/d/Kalad/common/wild/pass/npc/hgcwolf");
      ob1 -> move_living("xxx", TO);
   }
   if (!ob2)
      {
      ob2 = clone_object("/d/Kalad/common/wild/pass/npc/hgchief");
      ob2 -> move_living("xxx", TO);
      ob2 -> team_join(ob1);
   }
}
void
init()
{
   ::init();
   add_action("do_smell", "smell");
   add_action("do_smell", "sniff");
}
int
do_smell(string str)
{
   if(!str || str != "vapors")
      {
      notify_fail("You can't smell '" + str + "'.\n");
      return 0;
   }
   write("You inhale the pungent vapors...\n");
   say(QCTNAME(TP) + " inhales deeply of the vapors.\n");
   set_alarm(2.0,0.0,"do_effect");
   return 1;
}
void
do_effect()
{
   TP->command("stare");
   TP->command("growl insanely");
   TP->command("cackle insanely");
   TP->command("say Die you pitiful loser!");
   TP->command("kick all");
   TP->command("spit all");
   TP->command("kill human");
   TP->command("kill human");
   TP->command("kill elf");
   TP->command("kill elf");
   TP->command("kill dwarf");
   TP->command("kill dwarf");
   TP->command("kill gnome");
   TP->command("kill gnome");
   TP->command("kill hobbit");
   TP->command("kill hobbit");
   TP->command("kill goblin");
   TP->command("kill goblin");
   TP->command("say Get out of this village or I'll kill you myself!");
   return;
}
