/*
 * Made by Korat
 * may 1996
 *
*/

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

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
      "This room has just two exits and looks fairly empty. "+
      "You can walk to the south or pass through an exit to the "+
      "north. The old cloth hiding the northern way will easily "+
      "be pushed away.\n");
   add_item("cloth","It is old and very dirty but manages to hide "+
      "the northern exit.\n");
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
   add_prop(ROOM_S_DARK_LONG,"@@dark_description@@");
   INSIDE;

   add_exit(CPASS(citadel/level4/d3),"south","@@in",-1);
   add_exit(CPASS(citadel/level4/d1),"north","@@out",-1,1);
}

/* give a feeling of walking into the leaders room */
int
in()
{
   if (TP->query_prop("IS_SCARED_OF_GOLIATH"))
   {
      TP->catch_msg("You would be killed if you reenter that room! "+
         "You don't dare to do it.\n");
      tell_room(TO,QCTNAME(TP)+" tries to walk southeast, but "+
         "freezes up in fright!\n",TP);
      return 1;
   }
   TP->catch_msg("You suddenly realize that you now have entered "+
       "the room of the leader of the brigands! You better behave.\n");
   return 0;
}

/* give a feeling of walking behind a cloth */
int
out()
{
   TP->catch_msg("You push the cloth away with your right hand "+
      "and enter the northern room.\n");
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
