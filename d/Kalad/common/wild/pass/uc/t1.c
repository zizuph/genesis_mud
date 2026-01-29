inherit "/d/Kalad/common/wild/pass/uc/uc_std";
#include "/d/Kalad/defs.h"
#define SLAVE "/d/Kalad/common/wild/pass/uc/npc/thanar_slave"
object ob1;
object ob2;
object ob3;
/* by Antharanos */
create_room()
{
   ::create_room();
   set_short("A small chamber");
   set_long("A small, roughly circular chamber lies before you. The "+
      "obsidian-colored walls of the chamber seem to absorb the energy "+
      "from your being, leaving it weak and submissive. Nothing, not even "+
      "a single rock lies upon the stone floor.\n"+
      "To the south lies a passage.\n");
   add_item(({"small chamber","chamber"}),
      "A dark and foreboding place.\n");
   add_item(({"obsidian-colored walls","walls","wall"}),
      "They have been roughly carved from the surrounding rock.\n");
   add_item(({"stone floor","floor","ground","ceiling"}),
      "It is composed of an unusually dark stone.\n");
   add_item(({"rock","stone"}),
      "It is what this entire chamber is composed of.\n");
   add_item(({"passage"}),
      "A tunnel located far beneath the surface of Kalad.\n");
   add_exit(CPASS(uc/u26),"south",0,2,1);
   set_alarm(1.0,0.0,"reset_room");
}
void
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(SLAVE);
      ob1 -> move_living("M",TO);
   }
   if(!ob2)
      {
      ob2 = clone_object(SLAVE);
      ob2 -> move_living("M",TO);
   }
   if(!ob3)
      {
      ob3 = clone_object(SLAVE);
      ob3 -> move_living("M",TO);
      tell_room(TO,"A moan from a dark corner of the chamber attracts your "+
         "attention to a small group of dwarves.\n");
   }
}
