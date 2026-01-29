inherit "/d/Kalad/common/wild/pass/uc/uc_std";
#include "/d/Kalad/defs.h"
object ob1;
/* by Antharanos */
create_room()
{
   ::create_room();
   set_short("A cramped passage");
   set_long("A cramped passage.\n"+
      "Stone of a strangely dark quality comprises the length and breadth of this "+
      "passage you are travelling in. The grim fact that even the slightest "+
      "of tremors could cause the countless tons of rock to crash down upon "+
      "you does little to lighten your perspectives. In addition, an utterly "+
      "horrible smell is in the air. The passage itself curves sharply here, "+
      "veering off to the northwest and southwest.\n");
   add_item(({"cramped passage","passage"}),
      "A small tunnel far beneath the surface world.\n");
   add_item(({"stone","rock"}),
      "It is dark, unnaturally so.\n");
   add_item(({"floor","ground","walls","wall","ceiling"}),
      "It is composed of the strange and unusually dark rock common in the "+
      "underground areas of Kalad.\n");
   add_exit(CPASS(uc/g1),"northwest",0,2,1);
   add_exit(CPASS(uc/g5),"southwest",0,2,1);
   reset_room();
}
void
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(CPASS(uc/obj/hum_corpse_e));
      ob1 -> move(TO);
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
