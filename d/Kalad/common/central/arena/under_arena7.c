/* 
 * /d/Kalad/common/central/arena/under_arena7.c
 * Purpose    : Kitchen beneath the arena
 * Located    : /d/Kalad/common/central/arena/
 * Created By : Korat 1995
 * Modified By: Valen 20020119
 */ 

/* Under the arena */
/* made by Korat */

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
void reset_room();
void do_search();
int recently_searched;
int found_grinder;
object ob1;
object ob2;

create_room()
{
   ::create_room();
   hear_bell = 2;
   add_prop(ROOM_I_INSIDE,1);
   add_prop(ROOM_I_LIGHT, 0);
   add_prop(ROOM_I_TYPE,ROOM_BEACH);
   set_short ("Under the arena");
   set_long (
      "You find yourself in a greasy kitchen. The walls are "+
      "filled with shelves that cling for their lives to the "+
      "damp walls with the help of some rusty nails. "+
      "In the corner you see a stove @@stove_lit@@ Next "+
      "to a greasy bench you see a barrel full of water.\n");
   
   add_item ("shelves","They barely hang onto the walls with "+
      "the help of some old and rusty nails.\n");
   
   add_item ("shelf","Well, they are of wood. And there are a lot "+
      "of them around here!\n");
   
   add_item("barrel","The barrel is filled to the rim with "+
      "fresh-tasting water.\n");
   
   add_item("bench","Ack! Its extremely greasy! Who would ever "+
      "want to prepare food on this one! @@grinder@@\n");
   
   
   add_item (({"wall","walls"}),"The walls are made "+
      "of rough-cut stone, and are damp to the touch.\n");
   
   add_item ("stone","They are damp to the touch.\n");
   
   add_item("water","Its cold and fresh-tasting.\n");
   
   add_item("nails","Just some rusty old nails.\n");
   
   add_exit (CENTRAL(arena/under_arena6),"east",0,-1,-1);
   
   reset_room();
}

void
reset_room()
{
   recently_searched = 0;
   found_grinder = 0;
   if (ob1) ob1->remove_object();
   ob1 = clone_object("/d/Kalad/common/central/obj/stove");
   ob1 -> move(TO);
   tell_room(TO,"A slave comes in and fills the stove with "+
      "fresh wood. He then leaves as fast as he came.\n");
   if (ob2 && environment(ob2) == TO) ob2->remove_object();
   ob2 = 0;
}

void
init()
{
   ::init();
   add_action("search","search");
}

stove_lit()
{
   if (ob1->query_prop(OBJ_I_LIGHT))
      return("that burns brightly and sends a weak red light into the room.");
   else
      return("that is cold to the touch.");
}

int
search(string str)
{
   if(!str || str != "shelves")
      return 0;
   if(recently_searched)
      {
      write("You start to search the shelves and find...grease, just grease. "+
         "You quickly wipe your hands on your clothes.\n");
      return 1;
   }
   write ("You start to search the shelves.\n");
   say(QCTNAME(TP) + " starts to search the shelves.\n");
   set_alarm(4.0,0.0,"do_search");
   return 1;
}

void
do_search()
{
   recently_searched = 1;
   write ("All you find is a lot of coffee beans. You start to pick them up "+
      "and soon you have two handfulls of them. You also got "+
      "your hands full of grease, so you wipe them off at your clothes.\n");
   say(QCTNAME(TP) + " starts to pick up something from the shelves. "+
      "It takes some time before its all picked up. Boring!\n");
   clone_object("/d/Kalad/common/central/obj/beans")->move(TP);
   clone_object("/d/Kalad/common/central/obj/beans")->move(TP);
   return;
}

grinder()
{
   if (!found_grinder)
      {
      if(!ob2){
         ob2 = clone_object("/d/Kalad/common/central/obj/grinder");
         ob2 -> move(TO);
       }
      found_grinder = 1;
      return("Even the coffee grinder on it is greased down!");
   }
   return("");
}



