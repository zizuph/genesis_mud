/* 
Citadel, private chambre.
Made by Korat 
Feb 14. 1995
20180108 Zignur Made sure Urian always spanws with the rest 
*/

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
object ob2;
object ob3;
object ob4;
int lord_cloned_once;
#define LORD_CLONE_CHANCE 3

void
create_room()
{
   ::create_room();
   add_prop(ROOM_I_INSIDE,1);
   add_prop(ROOM_M_NO_TELEPORT, 1);

   hear_bell = 2;
   set_short("Citadel, High Lords office");
   set_long("This is the High Lord's office. The walls are decorated "
   +"with a few paintings that matches the brownish panelling on the "
   +"walls and the large ornate, redwood desk that is situated in the "
   +"centre of the room. In each corner a large chandelier stands tall, "
   +"spreading out their yellow, flickering light. @@is_lord_here@@\n");
   
   add_item("desk","The redwood of the large desk is neatly decorated with "+
    "intricate ornamentals, making it a work of art! The desk is fairly "+
    "tidy, with just some letters and official reports covering it.\n");
   add_item("chair","The High Lord's chair has several intricate decorations "+
    "engraved into the wood, giving it a timeless feel of elegance.\n");
   add_item(({"painting","paintings"}),"They portraits a few scenarios "+
    "of people, nature and a battle-scene here and there.\n");
   add_item(({"panel","paneling"}),"The paneling must be of oak, and has "+
    "been lighly torched to give the wood a darker brownish touch in its "+
    "colour. Together with the desk it manages to dampen the lights from "+
    "the candles, giving a relaxed atmosphere in the room.\n");
   add_item(({"candeliers","candles"}),"The candeliers have each six arm "+
    "a long, white candle that burns brightly. They shine in a golden "+
    "colour, so you wouldn't be surprised if they were of pure gold.\n");
   
   add_prop("_lords_office",1);
   add_exit(CENTRAL(citadel/cit26),"west","@@ok",-1,-1);
   clone_object("/d/Kalad/common/central/doors/high_lord_door2")->move(TO);
   set_alarm(0.0,0.0,"reset_room");
}

void
reset_room()
{
   if (!objectp(ob1)) 
   {
       ob1 = clone_object("/d/Kalad/common/central/npc/high_lord");
       ob1 -> arm_me();
       ob1 -> move_living("M",TO);
       tell_room(TO,"The High Lord arrives from his chambers.\n");      
   }
   if (!objectp(ob2))
      {
      ob2 = clone_object("/d/Kalad/common/central/npc/lord_councellor");
      ob2 -> arm_me();
      ob2 -> move_living("M",TO);
      tell_room(TO,"A small cloaked human enters silently the office.\n");
   }
   if (!objectp(ob3))
      {
      ob3 = clone_object("/d/Kalad/common/central/npc/cit_elite_lordguard");
      ob3 -> arm_me();
      ob3 -> move_living("M",TO);
      tell_room(TO,"An elite guard arrives, taking his post at the door.\n");
   }
   if (!objectp(ob4))
      {
      ob4 =  clone_object("/d/Kalad/common/central/npc/cit_elite_lordguard");
      ob4 -> arm_me();
      ob4 -> move_living("M",TO);
      tell_room(TO,"An elite guard arrives, taking his post at the door.\n");
   }
   if (objectp(ob1))
      {
      ob1 -> team_join(ob2);
      ob1 -> team_join(ob3);
      ob1 -> team_join(ob4);
      return;
   }
   ob2 -> team_join(ob3);
   ob2 -> team_join(ob4);
   return;
}

is_lord_here()
{
   if (objectp(ob1))
      {
      return "But all this just vanishes from your mind as soon as "+
      "your attention focuses on the High Lord Himself, sitting as "+
      "he does in his large, decorated chair.";
   }
   else
      { 
      return "You feel something is amiss though...where is the High Lord?";
   }
}

ok()
{
   if (ob1 || ob2 || ob3)
      {
      write("You are stopped from entering the room.\n");
      if (ob3) ob3 -> command("say Get out of there!");
      if (ob4) ob4 -> command("emote stops you from going west.");
      return 1;
   }
   return 0;
}
