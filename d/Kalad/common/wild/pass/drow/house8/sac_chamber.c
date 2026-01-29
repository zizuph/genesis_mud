inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#define DG "/d/Kalad/common/wild/pass/drow/npc/h8_dg_slave"
object ob1;
object ob2;
object ob3;
object ob4;
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_M_NO_TELEPORT,1);
   add_prop(ROOM_I_LIGHT,0);
   set_short("Sacrificial chamber");
   set_long("Darkness is ever prevalent here, for not only is the room "+
      "devoid of light, the very stone from which it is made seems to absorb "+
      "any traces of it. All that is discernible here is the grey, featureless "+
      "floor, simply because it is the most eye-catching part of this room. "+
      "The air seems somehow...dead. Sound seems to be muted, as if the stones "+
      "themselves absorbed them.\n");
   add_item(({"darkness"}),
      "A profound absence of light.\n");
   add_item(({"stone","stones"}),
      "It seems as if it was composed of solid darkness.\n");
   add_item(({"grey floor","featureless floor","floor"}),
      "Nothing more than a flat grey surface with nothing, not even a single "+
      "crack marring its featureless face.\n");
   add_exit(CPASS(drow/house8/chapel),"west","@@msg",-1,-1);
   set_noshow_obvious(1);
   set_alarm(1.0,0.0,"reset_room");
}
msg()
{
   write("You leave the unnatural darkness behind.\n");
   return 0;
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(DG);
      ob1 -> move_living("M",TO);
   }
   if(!ob2)
      {
      ob2 = clone_object(DG);
      ob2 -> move_living("M",TO);
   }
   if(!ob3)
      {
      ob3 = clone_object(DG);
      ob3 -> move_living("M",TO);
   }
   if(!ob4)
      {
      ob4 = clone_object(DG);
      ob4 -> move_living("M",TO);
      tell_room(TO,"Several muted moans attract your attention to a huddled group of "+
         "deep gnomes.\n");
   }
}
