inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
/* by Antharanos */
void reset_room();
void create_raiders();
int summoned;
void
create_room()
{
   INSIDE;
   set_short("The quarters of the Matron Mother of House Kilsek");
   set_long("You are within a sumptiously decorated chamber of black stone.\n"+
      "All around the room are a nearly infinite number of faerie fire "+
      "decorations, all exquisitely done. A single lace and silk-covered "+
      "bed lies at the far end of the chamber, while a platinum brazier, "+
      "incense pouring from it, lies opposite it, on the other side of the "+
      "chamber. To the west lies a large platinum chest, while in the east "+
      "there is a small altar to Lolth.\n"+
      "The very center of the room is occupied by a blood red column of "+
      "light.\n");
   add_item(({"quarters","decorated chamber","chamber","room"}),
      "It is where you currently are, have a look around.\n");
   add_item(({"faerie fire decorations","decorations","decoration","faerie fire decoration"}),
      "Numerous depictions of drow debasing themselves before the Spider "+
      "Queen Lolth, and not a single one depicts a male drow.\n");
   add_item(({"lace bed","lace-covered bed","silk bed","silk-covered bed","bed"}),
      "A gigantic bed that looks as if sleeping on it would bring about "+
      "instant pleasure.\n");
   add_item(({"platinum brazier","brazier"}),
      "A platinum bowl set upon a tripod around five feet in height, from it "+
      "pours forth a continual stream of incense.\n");
   add_item(({"incense"}),
      "The smoke is all over the room, pervading it with its scent.\n");
   add_item(({"large platinum chest","large chest","platinum chest","chest"}),
      "A massive chest fashioned from pure platinum, it looks quite sturdy.\n");
   add_item(({"small altar","altar"}),
      "A simple shrine to the drow goddess, Lolth. Several dark stains mar "+
      "its otherwise perfect facade.\n");
   add_item(({"dark stains","dark stain","stains","stain"}),
      "An unidentifiable dried liquid.\n");
   add_item(({"blood red column","red column","light"}),
      "A glowing beam of light that leads down through the floor to the "+
      "main hall of the House Kilsek compound.\n");
   add_item("thesummoningspellforthedrowraiders","@@drow_raiders");
   add_exit(CPASS(drow/house5/main_hall),"down","@@msg",-1,-1);
   set_noshow_obvious(1);
   reset_room();
}
void
init()
{
   ::init();
   AA(enter,enter);
}
int
enter(string str)
{
   if(!str || str != "theportaltothesurfaceworld")
      {
      NF("What?\n");
      return 0;
   }
   write("You enter the portal.\n");
   set_alarm(1.0,0.0,"do_trans");
   return 1;
}
void
do_trans()
{
   TP->move_living("into the portal with a brilliant flash","/d/Kalad/common/caravan/caravan_gate");
   return;
}
void
reset_room()
{
   summoned = 0;
   if(!ob1)
      {
      ob1 = clone_object(CPASS(drow/npc/h5_matron));
      ob1 -> move_living("xxx",TO);
   }
}
string
drow_raiders()
{
   if(summoned)
      return("The raiders have already been summoned.\n");
   set_alarm(6.0,0.0,"create_raiders");
   return("The raiders have not yet been summoned.\n");
}
void
create_raiders()
{
   int i;
   summoned = 1;
   for(i = 0; i < 10; i++)
   {
      clone_object(CPASS(drow/npc/raider))
      ->move(TO);
      tell_room(TO,"A drow raider steps out of the red column of light!\n");
   }
}
msg()
{
   write("You step into the red light, and feel yourself grow lighter as "+
      "you are transported by the column.\n");
   say(QCTNAME(TP) + " steps into the red light, and seems to grow lighter "+
      "as " + TP->query_pronoun() + " is transported by the column.\n");
   return 0;
}
