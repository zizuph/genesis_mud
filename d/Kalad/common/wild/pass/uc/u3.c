inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
void reset_room();
void do_search();
int recently_searched;
object ob1;
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_M_NO_TELEPORT,1);
   set_short("A large oval chamber");
   set_long("A large oval chamber lies before you, having been "+
      "meticulously prepared from the surrounding black stone. The surface "+
      "of the walls, floor and ceiling of this room have been so thoroughly "+
      "smoothed down that they appear like nothing more than "+
      "giant black mirrors set against the stone. The chamber itself is "+
      "occupied by a small obsidian altar in the north, a chest to the "+
      "south, and a glowing red orb at its center.\n"+
      "A passage leads to the east.\n");
   add_item(({"large oval chamber","large chamber","oval chamber","chamber"}),
      "A large, artificially-created area here far beneath the surface world.\n");
   add_item(({"black stone","stone"}),
      "Rock so dark it appears as if it were darkness given solid form.\n");
   add_item(({"surface","walls","wall","floor","ceiling"}),
      "Its texture is so fine, so flawless that it is like a work of art, "+
      "not simply a minor part of this chamber.\n");
   add_item(({"small obsidian altar","small altar","obsidian altar","altar"}),
      "A small altar that has been consecrated to Lolth, as evidenced by the "+
      "numerous blood stains on its black surface.\n");
   add_item(({"blood stains","blood stain","stains","stain"}),
      "Brown and thick, it appears as though the last sacrifice was some "+
      "time ago...perhaps you should leave before that changes.\n");
   add_item(({"chest"}),
      "A simple-looking chest of steel. There is no lock on it.\n");
   add_item(({"glowing red orb","glowing orb","red orb","orb"}),
      "The sole source of light in this chamber, the mirror-like surface "+
      "of this room gathers and intensifies the light so that it provides "+
      "an adequate amount throughout the entire area.\n");
   add_item(({"passage"}),
      "A tunnel that leads out of this chamber.\n");
   add_exit(CPASS(uc/u4),"east",0,2,1);
   set_noshow_obvious(1);
   set_alarm(1.0,0.0,"reset_room");
}
void
reset_room()
{
   recently_searched = 0;
   if(!ob1)
      {
      ob1 = clone_object(CPASS(uc/npc/drow_mage));
      ob1 -> arm_me();
      ob1 -> move_living("M",TO);
      tell_room(TO,"A cloud of black smoke rolls in, and when it departs, "+
         "a figure stands before you that was not there previously.\n");
   }
}
void
init()
{
   ::init();
   AA(search_chest,search);
   AA(time,time);
}
time()
{
   write("It is impossible to tell, since you are far beneath the surface "+
      "of Kalad.\n");
   return 1;
}
int
search_chest(string str)
{
   if(!str || str != "chest")
      return 0;
   if(recently_searched)
      {
      write("You find nothing at all.\n");
      return 1;
   }
   write("You start to search the chest.\n");
   say(QCTNAME(TP) + " starts to search the chest.\n");
   set_alarm(4.0,0.0,"do_search");
   return 1;
}
void
do_search()
{
   recently_searched = 1;
   write("You discover a pair of rubies!\n");
   write("You quickly grab them up.\n");
   say(QCTNAME(TP) + " takes something from the chest.\n");
   clone_object(CPASS(uc/obj/ruby))->move(TP);
   clone_object(CPASS(uc/obj/ruby))->move(TP);
   return;
}
