inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#define GOBLIN "/d/Kalad/common/wild/pass/drow/npc/h5_gob_slave"
#define OGRE "/d/Kalad/common/wild/pass/drow/npc/h5_ogre_slave"
void reset_room();
void do_search();
int recently_searched;
object ob1;
object ob2;
object ob3;
object ob4;
object ob5;
object ob6;
object ob7;
object ob8;
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_M_NO_TELEPORT,1);
   add_prop(ROOM_I_LIGHT,0);
   set_short("The slave pens");
   set_long("The smell is the first thing you notice about this place, "+
      "not only does it reek of stale sweat and too many unwashed bodies, "+
      "but of feces and the more sinister odor given off from a body that "+
      "has been left to decay. The building itself is constructed of the "+
      "same dark stone the rest of the compound is made of, yet that is all "+
      "they have in common. This huge holding area is bare of furnishings, "+
      "and possesses nothing in the way of ventilation, save for the "+
      "dark archway to the north.\n");
   add_item(({"building","structure","holding area","area"}),
      "The interior is nothing but a wide clear space where many slaves "+
      "are kept when they are not out performing menial labor for the drow.\n");
   add_item(({"dark archway","archway"}),
      "A black space in the northern side of this building.\n");
   add_exit(CPASS(drow/house5/entrance),"north",0,-1,1);
   set_noshow_obvious(1);
   reset_room();
}
void
init()
{
   ::init();
   AA(search_area,search);
}
int
search_area(string str)
{
   if(!str || str != "area")
      return 0;
   if(recently_searched)
      {
      write("You discover nothing in your search.\n");
      return 1;
   }
   recently_searched = 1;
   write("You start to search the area.\n");
   say(QCTNAME(TP) + " starts to search the area.\n");
   set_alarm(4.0,0.0,"do_search");
   return 1;
}
void
do_search()
{
   write("You discover a house insignia!\n");
   write("You quickly pick it up.\n");
   say(QCTNAME(TP) + " discovers something and then quickly picks it up.\n");
   clone_object(CPASS(drow/obj/h5_insignia))->move(TP);
   return;
}
void
reset_room()
{
   recently_searched = 0;
   if(!ob1)
      {
      ob1 = clone_object(GOBLIN);
      ob1 -> move_living("M",TO);
   }
   if(!ob2)
      {
      ob2 = clone_object(GOBLIN);
      ob2 -> move_living("M",TO);
   }
   if(!ob3)
      {
      ob3 = clone_object(GOBLIN);
      ob3 -> move_living("M",TO);
   }
   if(!ob4)
      {
      ob4 = clone_object(GOBLIN);
      ob4 -> move_living("M",TO);
   }
   if(!ob5)
      {
      ob5 = clone_object(OGRE);
      ob5 -> move_living("M",TO);
   }
   if(!ob6)
      {
      ob6 = clone_object(OGRE);
      ob6 -> move_living("M",TO);
   }
   if(!ob7)
      {
      ob7 = clone_object(OGRE);
      ob7 -> move_living("M",TO);
   }
   if(!ob8)
      {
      ob8 = clone_object(OGRE);
      ob8 -> move_living("M",TO);
      tell_room(TO,"A chorus of groans directs your attention to the far "+
         "end of the room.\n");
   }
}
