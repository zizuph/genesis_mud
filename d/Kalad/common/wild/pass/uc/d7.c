inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
void reset_room();
void do_search();
int recently_searched;
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_M_NO_TELEPORT,1);
   set_short("A maroon chamber");
   set_long("A maroon chamber.\n"+
      "This small, crystalline chamber is dominated by a pulsating red orb "+
      "that lies suspended in the air at the exact center of the room. By "+
      "the eerie red light cast by the orb, you can clearly see many glittering "+
      "heaps of platinum coins and quite a few golden ones.\n");
   add_item(({"maroon chamber","small chamber","crystalline chamber","chamber"}),
      "A cavity deep within the ground wherein you are located.\n");
   add_item(({"pulsating red orb","pulsating orb","red orb","orb"}),
      "A small crystalline object that seems to pulse in rhythm with the "+
      "beating of your heart. It is the sole source of light for this chamber.\n");
   add_item(({"heaps","heap"}),
      "Which one?\n");
   add_item(({"glittering heaps","glittering heap","platinum"}),
      "It lies in a great pile nearly ten feet tall.\n");
   add_item(({"golden heaps","golden heap"}),
      "A five foot high mound of gold coins.\n");
   reset_room();
}
void
init()
{
   ::init();
   AA(touch,touch);
   AA(search_heaps,search);
}
int
touch(string str)
{
   if(!str || str != "orb")
      {
      NF("Touch what? The orb?\n");
      return 0;
   }
   write("You touch the orb and feel tremendous pain as black arcs "+
      "of energy race from it and trap you in their deadly embrace.\n");
   say(QCTNAME(TP) + " touches the orb and is instantly engulfed in "+
      "black arcs of energy that race from the orb to "+
      "enwrap " + TP->query_objective() + " in their deadly embrace.\n");
   TP->command("scream");
   write("You feel as though you are vaporized.\n");
   say(QCTNAME(TP) + " is vaporized!\n");
   clone_object(CPASS(uc/obj/ash_pile))->move(TO);
   set_alarm(1.0,0.0,"do_move");
   return 1;
}
void
do_move()
{
   TP->move_living("M","/d/Kalad/common/wild/pass/uc/u42");
   return;
}
void
reset_room()
{
   recently_searched = 0;
}
int
search_heaps(string str)
{
   if(!str || str != "heaps")
      return 0;
   if(recently_searched)
      {
      write("You find nothing that you can easily take.\n");
      return 1;
   }
   write("You start to search the heaps.\n");
   say(QCTNAME(TP) + " starts to search the heaps.\n");
   set_alarm(5.0,0.0,"do_search");
   return 1;
}
void
do_search()
{
   recently_searched = 1;
   write("You discover two rubies!\n");
   write("You quickly pick them up.\n");
   say(QCTNAME(TP) + " takes something from one of the heaps.\n");
   clone_object(CPASS(uc/obj/ruby))->move(TP);
   clone_object(CPASS(uc/obj/ruby))->move(TP);
   return;
}
