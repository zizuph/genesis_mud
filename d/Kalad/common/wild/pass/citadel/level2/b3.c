/*
 * Made by Korat
 * may 1996
 *
*/

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object prisoner;
object rat1;
object rat2;
object rat3;

create_room()
{
   ::create_room();
   set_short("dwarven Citadel");
   set_long("You are inside an ancient citadel, long abandoned "+
      "by their masters and makers, the deep dwarves. "+
      "Even though the citadel has clear marks of decay from "+
      "the centuries of abandonment, the masonry is of such "+
      "quality that you still have problems finding the "+
      "cracks inbetween the stoneblocks. Along the southern wall "+
      "you see different chains attached to it. "+
      "The only exit is northwest towards another room hidden "+
      "in a veil of darkness.\n");

   add_item(({"chain","chains"}),"They look old and frail, but "+
      "will still be able to make sure any locked in prisoner "+
      "will stay put in here.\n");
   add_item(({"cobweb","web","silky network","silky web"}),
      "They are woven, silky networks spun by spiders through "+
      "time. All of them look to be abandoned by their creators, "+
      "much like the citadel itself; left alone to slowly be "+
      "grinned down by the sand carried along with the wind.\n");
   add_item(({"wall","walls","ceiling","roof"}),
      "Both the walls and the ceiling looks to be made by "+
      "brilliant craftsmen. This citadel was made to last ... "+
      "for thousands of years.\n");
   add_item("floor","The floor is covered with fine-grained, white "+
      "sand that must have been carried in here with the wind from the "+
      "great Kaladian waste.\n");
   add_item("citadel","The citadel you are inside is a masterpiece "+
      "of construction. Time has managed to mark it with signs of age, "+
      "but that only mystifies it more than its centuries of abandonment "+
      "manages to do alone.\n");

   /* gives random darkness descriptions. 'A dark room' is so boring. */
   add_prop(ROOM_S_DARK_LONG,"@@dark_description");
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);

   add_exit(CPASS(citadel/level2/b1),"northwest","@@arch",-1);
   set_alarm(0.0,0.0,"reset_room");
}

reset_room()
{
   if (!objectp(prisoner))
   {
      prisoner=clone_object("/d/Kalad/common/wild/pass/citadel/npc/traderprisoner");
      prisoner->move_living("M",TO);
      prisoner->command("moan");
   }
   if (!objectp(rat1))
   {
      rat1=clone_object("/d/Kalad/common/wild/pass/citadel/npc/rat");
      rat1->move_living("M",TO);
   }
   if (!objectp(rat2))
   {
      rat2=clone_object("/d/Kalad/common/wild/pass/citadel/npc/rat");
      rat2->move_living("M",TO);
   }
   if (!objectp(rat3))
   {
      rat3=clone_object("/d/Kalad/common/wild/pass/citadel/npc/rat");
      rat3->move_living("M",TO);
      rat1->team_join(rat2);
      rat1->team_join(rat3);
   }
}

/* give a feeling of passing through an arc */
void
arch()
{
   TP->catch_msg("You walk through a low passage that arches around you.\n");
   return 0;
}

/* returns a random darkroom description */
dark_description()
{
   string desc;
   switch (random(5))
   {
      case 0:
         desc = "You find yourself inside utter darkness.\n";
         break;
      case 1:
         desc = "A weak and chilling wind is all breaks the darkness.\n";
         break;
      case 2:
         desc = "You think you hear some sounds in front of you, but "+
                "without vision you cannot know what it comes from.\n";
         break;
      case 3:
         desc = "A dark room that envelopes you like a cloak of death.\n";
         break;
      case 4:
         desc = "You touch the wall to make sure you walk in the right "+
                "direction.\n";
         break;
      default: break;
   }
   
   return desc;
}
