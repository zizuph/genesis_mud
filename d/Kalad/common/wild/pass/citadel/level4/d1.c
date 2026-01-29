/*
 * Made by Korat
 * may 1996
 *
*/

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ogre;

create_room()
{
   ::create_room();
   set_short("dwarven Citadel");
   set_long("You are inside an ancient citadel, long abandoned "+
      "by their masters and makers, the deep dwarves. "+
      "Even though the citadel has clear marks of decay from "+
      "the centuries of abandonment, the masonry is of such "+
      "quality that you still have problems finding the "+
      "cracks inbetween the stoneblocks. "+
      "Towards the south you see a large cloth blocking the "+
      "way into what you believe must be the upper room of "+
      "this citadel.\n");

   add_item("stairway","The stairway is of stone and has "+
      "several large dark-red stains decorating it.\n");
   add_item(({"stain","stains"}),"The stains must be of "+
      "old blood. Not a good sign.\n");
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
   add_item("cloth","The cloth is stained and old, but still manages "+
      "to function as a light wall between you and the central room of "+
      "this citadel.\n");

   /* gives random darkness descriptions. 'A dark room' is so boring. */
   add_prop(ROOM_S_DARK_LONG,"@@dark_description@@");
   INSIDE;

   add_exit(CPASS(citadel/x18),"southeast","@@down",-1);
   add_exit(CPASS(citadel/level4/d2),"south","@@ogre_in_door",-1,1);
   set_alarm(0.0,0.0,"reset_room");
}

reset_room()
{
   if (!objectp(ogre))
   {
      ogre=clone_object("/d/Kalad/common/wild/pass/citadel/npc/ogre_door");
      ogre->arm_me();
      ogre->move_living("M",TO);
      ogre->command("emote grunts: Got any booze on yah! Me like booze.");
   }
}

/* give a feeling of going downwards*/
int
down()
{
   TP->catch_msg("You walk down the stairway, taking care not to slip "+
       "on the stains.\n");
   return 0;
}

/* give a feeling of walking behind a cloth */
int
ogre_in_door()
{
   if (objectp(ogre))
   {
      ogre -> command("emote steps in front of you.");
      return 1;
   }
   TP->catch_msg("You push the cloth away with your right hand "+
      "and enter the southern room.\n");
   return 0;
}

/* returns a random darkroom description */
string
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
