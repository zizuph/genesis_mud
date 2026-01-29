inherit "/d/Kalad/common/wild/pass/uc/uc_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   set_short("A cramped passage");
   set_long("A cramped passage.\n"+
      "Stone of an unusually dark hue comprises the entirety of this "+
      "passage you are within. The disturbing fact that just the "+
      "slightest tremor could cause thousands of tons of rock to come crashing "+
      "down upon you does not bode well for you. Also, a rather strong and "+
      "unusual smell lingers within the air of this passage, a passage that "+
      "sharply curves and heads to the northwest and northeast.\n");
   add_item(({"cramped passage","passage"}),
      "A small tunnel far beneath the surface world.\n");
   add_item(({"stone","rock"}),
      "It is dark, unnaturally so.\n");
   add_item(({"floor","ground","walls","wall","ceiling"}),
      "It is composed of the strange and unusually dark rock common in the "+
      "underground areas of Kalad.\n");
   add_exit(CPASS(uc/g3),"northwest",0,2,1);
   add_exit(CPASS(uc/g4),"northeast",0,2,1);
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
