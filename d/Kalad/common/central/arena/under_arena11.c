/* 
 * /d/Kalad/common/central/arena/under_arena11.c
 * Purpose    : Sleeping area beneath the arena
 * Located    : /d/Kalad/common/central/arena/
 * Created By : Korat 1995
 * Modified By: 
 */ 

/* Under the arena */
/* made by Korat */

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
object ob2;
object ob3;
int bandage_found;

void
create_room()
{
   ::create_room();
   hear_bell = 1;
   add_prop(ROOM_I_INSIDE,1);
   set_short ("Under the arena");
   set_long (
      "Along all the walls you see wooden beds lined up. This must "+
      "be the sleeping area that the gladiators use when they "+
      "rest themselves after the hard and demanding fights. "+
      "There is little else in this room, except a table in the "+
      "center.\n");

   add_item("table","Its a plain wooden table that show signs "+
      "of recent use. Except from some cards, a candle and some "+
      "bloodied bandages the table is empty.\n");
   
   add_item(({"bed","beds"}),"Most of the beds are empty, but "+
      "two of them have some snooring inhabitants. From measuring "+
      "the sounds they make, you are very surprised that they don't "+
      "wake each other up...\n");
   
   add_item(({"gladiator","gladiators","inhabitant","inhabitants"}),
      "They have covered themselves in some dirty blankets and turned "+
      "their back to you and the rest of the room. Except from "+
      "snooring and turning in their sleep, these are not doing much. "+
      "You will have a hard time i trying to wake them up...\n");
   
   add_item("candle","The candle gives off a weak yellow light.\n");
   
   add_item(({"bandage","bandages"}),"The blood on the bandages "+
      "has dried up, making the soaked bandages become stiff "+
      "and useless. The gladiator who needed these can't have "+
      "much blood left in his body! @@bandage@@\n");
   
   add_item(({"card","cards"}),"Most of them lie spread out on the table "+
      "but some have fallen down onto the floor.\n");
   
   add_item (({"wall","walls"}),"The walls are made "+
      "of rough-cut stone, and are damp to the touch.\n");
   
   add_item ("stone","They are damp to the touch.\n");
   
   add_exit (CENTRAL(arena/under_arena9),"east",0,-1,-1);
   
   set_alarm(1.0,0.0,"reset_room");
   set_alarm (10.0,60.0,"snooring_glads");
   set_alarm (20.0,70.0, "moving_glads");
}

void
init()
{
   ::init();
   add_action("wake_glad","wake");
   add_action("get_bandage","search");
}

int
wake_glad(string str)
{
   if ((!str) && (str != "gladiator") && (str != "inhabitant"))
      {
      write("Wake who?\n");
      return 0;
   }
   
   write("You start to shake them, scream into their ears, rattling "+
      "your weapons; but all to no vain. Nothing will make these men "+
      "wake up.\n");
   
   say(QCTNAME(TP)+" walks up to one of the beds and starts to shake "+
      "the sleeping man. "+QCTNAME(TP)+" then screams loudly and "+
      "rattles with weapons; but the sleeping man just keeps on "+
      "snooring.\n");
}

string
show_current_fight()
{
    return "There are no fights set at this time.\n";
}

void
snooring_glads()
{
   tell_room (TO,"From one of the beds a loud snoore erupts for "+
      "a while, and then dies slowly out.\n");
}

moving_glads()
{
   tell_room (TO,"Someone turns in his sleep, making the bed "+
      "creack loudly.\n");
}

reset_room()
{
   bandage_found = 0;
   if (!objectp(ob1))
      {
      ob1 = clone_object("/d/Kalad/common/central/npc/gladiator1");
      ob1 -> arm_me();
      ob1 -> move_living("M",TO);
      tell_room(TO,"A man wakes up from his long sleep.\n");
   }
   if (!objectp(ob2))
      {
      ob2 = clone_object("/d/Kalad/common/central/npc/gladiator1");
      ob2 -> arm_me();
      ob2 -> move_living("M",TO);
      tell_room(TO,"A gladiator sits himself down at the table.\n");
   }
   if (!objectp(ob3))
      {
      ob3 = clone_object("/d/Kalad/common/central/npc/gladiator1");
      ob3 -> arm_me();
      ob3 -> move_living("xxx",TO);
   }
}

bandage()
{
   if (bandage_found)
      return "";
   else
      return "You see one though, that might still work.";
}

int
get_bandage(string str)
{
   notify_fail("Search what?\n");
   if (!str || str != "bandages")
      return 0;
   if (bandage_found)
      {
      write("You leaf through some of the dried pieces of cloth, "+
         "but find none that are usable.\n");
      return 1;
   }
   write("You start to search the bandages.\n");
   say(QCTNAME(TP) + " starts to search the bandages.\n");
   set_alarm(4.0,0.0,"do_search");
   return 1;
}

void
do_search()
{
   bandage_found =1;
   write("After leafing through some of the dried, useless "+
      "bandages, you find one that still can be worn.\n");
   write("You pick it up.\n");
   say(QCTNAME(TP) + " picks up something from the table.\n");
   clone_object("/d/Kalad/common/central/obj/bandage")->move(TP);
   return;
}
