/*
ROOM: Central Plaza Monument        
BY:   Sebster                       
DATE: Aug 27, 1994
*/

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include "/sys/ss_types.h"
#define HARD_TO_CLIMB 30
#define DAMAGE 50
string long;

void
create_room()
{
   ::create_room();
   hear_bell = 3;
   DIRTY(3);
   
   set_short("The magnificent (but rather dirty) statue of the High Lord");
   set_long(
      "Here, in the middle of the town square, stands the magnificent statue "+
      "of the High Lord of Kabal. This statue symbolizes the iron-fisted "+
      "grip with which the High Lord rules. It is very dirty here; there is "+
      "lots of trash lying around, some smelly animal excrements decorate "+
      "the ground, and some urine is running down the back of the monument. "+
      "You might be able to climb it, though it seems pretty slippery. "
   );
   
   set_time_desc("Some pigeons sits on the head of the monument, and makes "+
      "it even dirtier than before.\n","The monument seems bigger and even "+
      "threatening in this darkness.\n");
   
   add_exit(CENTRAL(plaza/sq_north),"north",0,1);
   add_exit(CENTRAL(plaza/sq_east),"east",0,1);
   add_exit(CENTRAL(plaza/sq_south),"south",0,1);
   add_exit(CENTRAL(plaza/sq_west),"west",0,1);
   
   add_item(({"statue", "monument", "lord"}),
      "The High Lord looks very ugly. How did he get elected?\n"
   );
   add_item(({"extrements","shit","urine"}),"It smells VERY bad.\n");
   
   add_item("trash", "You are getting very dirty walking around here.\n");
}

void 
init()
{
   ::init();
   add_action("do_urinate", "urinate");
   add_action("do_puke", "puke");
   add_action("do_climb","climb");
}

int
do_urinate(string str)
{
   if ((strlen(str) != 0) && (str != "monument") && (str != "statue"))
      {
      notify_fail("Urinate where?\n");
      return 0;
   };
   if (!str)
      {
      write(
         "You urinate on the ground, and try to make it even dirtier than it "+
         "already was, but you fail miserably.\n"
       );
      say(QCTNAME(this_player()) + " urinates on the ground.\n");
      return 1;
   };
   write(
      "You feel tremendously relieved as you urinate on the statue. So "+
      "this is what it feels like to be a hero!\n"
   );
   say(QCTNAME(this_player()) + " urinates on the statue. How disgusting!\n");
   return 1;
}

int
do_puke(string str)
{
   if ((str != "statue") && (str != "monument")) return 0;
   write(
      "You puke on the shoes of the High Lord. He looks much nicer now!\n"
   );
   say(QCTNAME(this_player()) + " pukes on the shoes of the High Lord.\n");
   return 1;
}

do_climb(string str)
{
   notify_fail("Climb what?\n");
   if (!str)
      return 0;
   if(str !="monument" && str != "statue")
      return 0;
   
   if(TP->query_skill(SS_CLIMB)<(20+(random(HARD_TO_CLIMB))))
      {
      write("You start climbing the monument, but halfway to the top "+
         "you loose your grip on the slippery surface!\n");
      write("Ouch, that really hurt!\n");
      TP->heal_hp(-DAMAGE);
      say(QCTNAME(TP) + " comes rambling down from the statue, ending up both "+
         "bleeding and smelling.\n");
      if(TP->query_hp() <=0)
         TP->do_die(TO);
      return 1;
   }
   write("You manage to climb up the monument, even though it was pretty slippery.\n");
   TP->move_living("climbing the monument", CENTRAL(plaza/monument),1);
   return 1;
}
