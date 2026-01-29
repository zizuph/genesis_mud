inherit "/d/Kalad/common/wild/pass/uc/uc_std";
#include "/d/Kalad/defs.h"
#define GIBB "/d/Kalad/common/wild/pass/uc/npc/gibberling"
object ob1;
object ob2;
object ob3;
object ob4;
object ob5;
object ob6;
object ob7;
/* by Antharanos */
create_room()
{
   ::create_room();
   set_short("A large cavern");
   set_long("A large cavern.\n"+
      "Stone of a strangely dark quality comprises the length and breadth of this "+
      "large cavern you are within. The dire fact that even the minutest "+
      "of tremors could cause the countless tons of rock to crash down upon "+
      "you does little to lighten your perspectives. In addition, an utterly "+
      "disgusting smell is present in the air. A passage leads from here and "+
      "heads to the southeast.\n");
   add_item(({"large cavern","cavern"}),
      "A great cavity within the rocky realm beneath the surface of Kalad.\n");
   add_item(({"cramped passage","passage"}),
      "A small tunnel far beneath the surface world.\n");
   add_item(({"stone","rock"}),
      "It is dark, unnaturally so.\n");
   add_item(({"floor","ground","walls","wall","ceiling"}),
      "It is composed of the strange and unusually dark rock common in the "+
      "underground areas of Kalad.\n");
   add_exit(CPASS(uc/g4),"southeast",0,2,1);
   reset_room();
}
void
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(CPASS(uc/obj/hum_corpse_f));
      ob1 -> move(TO);
   }
   if(!ob2)
      {
      ob2 = clone_object(GIBB);
      ob2 -> arm_me();
      ob2 -> move_living("M",TO);
   }
   if(!ob3)
      {
      ob3 = clone_object(GIBB);
      ob3 -> arm_me();
      ob3 -> move_living("M",TO);
   }
   if(!ob4)
      {
      ob4 = clone_object(GIBB);
      ob4 -> arm_me();
      ob4 -> move_living("M",TO);
   }
   if(!ob5)
      {
      ob5 = clone_object(GIBB);
      ob5 -> arm_me();
      ob5 -> move_living("M",TO);
   }
   if(!ob6)
      {
      ob6 = clone_object(GIBB);
      ob6 -> arm_me();
      ob6 -> move_living("M",TO);
   }
   if(!ob7)
      {
      ob7 = clone_object(GIBB);
      ob7 -> arm_me();
      ob7 -> move_living("M",TO);
      ob2 -> team_join(ob3);
      ob2 -> team_join(ob4);
      ob2 -> team_join(ob5);
      ob2 -> team_join(ob6);
      ob2 -> team_join(ob7);
   }
}
void
init()
{
   ::init();
   clone_object(CPASS(uc/obj/tell1))->move(TP,1);
}
leave_inv(ob, to)
{
   object msg;
   ::leave_inv(ob);
   msg = present("tell1",ob);
   if (msg) msg -> remove_object();
}
