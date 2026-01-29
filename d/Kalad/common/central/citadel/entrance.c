/* 
Citadel, entrance.
Made by Korat 
Feb 14. 1995 
*/

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

object ob1;
object ob2;
object ob3;

void
create_room()
{
   ::create_room();
   add_prop(ROOM_I_INSIDE,1);
   hear_bell = 2;
   set_short("Citadel, entrance");
   set_long("This is the entrance of the Citadel. You are struck by "+
      "the intricate decorations on the arch, leading inwards into the "+
      "citadel, but something else attracts your attention more...the "+
      "tidiness of the place. People must actually be cleaning up here! "+
      "Next to the arch you see two small guardhouses, that keeps the "+
      "sentry guard dry when it rains. You see two exits branch off from the "+
      "northwestern archway, going northeast and southwest, while the "+
      "archway continues through a huge bronze gate.\n");
   
   add_exit(CENTRAL(citadel/s1),"southeast",0,-1,-1);
   add_exit(CENTRAL(citadel/cit5),"northeast","@@officer",-1,-1);
   add_exit(CENTRAL(citadel/cit1),"southwest","@@guard",-1,-1);
   
   add_item ("arch","The arch is engraved with several symbols. It seems "+
      "like a sun is the most frequent one. Very nice indeed.\n");
   
   add_item (({"houses","guardhouses"}),"They are made of wood and "+
      "has nothing inside them of interest. All they do is to keep "+
      "the sentry guards dry when it rains.\n");
   
   clone_object(CENTRAL(doors/citadel_door1))->move(TO);
   set_alarm(0.0,0.0,"reset_room");
}

void
reset_room()
{
   if (!objectp(ob1))
      {
      ob1 = clone_object("/d/Kalad/common/central/npc/cit_guard");
      ob1 -> arm_me();
      ob1 -> move_living("M", TO);
      tell_room(TO,"The guards stand at attention when you arrive.\n");
      
   }
   if (!objectp(ob2))
      {
      ob2 = clone_object("/d/Kalad/common/central/npc/cit_guard");
      ob2 -> arm_me();
      ob2 ->  move_living("M", TO);
      ob2 -> team_join(ob1);
   }
   if (!objectp(ob3))
      {
      ob3 = clone_object("/d/Kalad/common/central/npc/beggar");
      ob3 -> arm_me();
      ob3 -> move_living("M", TO);
      tell_room(TO,"A beggar arrives limping.\n");
   }
   return;
}


officer()
{
   write("You head into the small passage northeast.\n");
   return 0;
}

guard()
{
   write("You bend your head and enter the passage southwestwards.\n");
   return 0;
}
