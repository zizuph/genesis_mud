/*
 * Made by Korat
 * may 1996
 *
*/

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/sys/outlaw.h"
object scout;

create_room()
{
   ::create_room();
   set_short("dwarven Citadel. A hallway continues to the west and east "+
      "interior of the citadel can be seen to the northwest and northeast");
   set_long("You are inside an ancient citadel, long abandoned "+
      "by their masters and makers, the deep dwarves. "+
      "Even though the citadel has clear marks of decay from "+
      "the centuries of abandonment, the masonry is of such "+
      "quality that you still have problems finding the "+
      "cracks inbetween the stoneblocks, but at this part "+
      "of the hallways you see a larger crack leading out to "+
      "the wilderness. "+
      "The hallway continues towards west and east, hiding "+
       "its content in a veil of darkness. Two rooms in the "+
      "interior of the citadel can be seen to the northwest and northeast.\n");

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
   add_item("crack","The crack seems to lead out to the wilderness.\n");

   /* gives random darkness descriptions. 'A dark room' is so boring. */
   add_prop(ROOM_S_DARK_LONG,"@@dark_description");
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   set_noshow_obvious(1);

   add_exit(CPASS(citadel/x3),"west",0,-1);
   add_exit(CPASS(citadel/x5),"east","@@whistle",-1);
   add_exit(CPASS(citadel/outside1),"out",0,2,1);
   add_exit(CPASS(citadel/outside1),"crack",0,2,1);
   add_exit(CPASS(citadel/level1/a1),"northwest",0,-1);
   add_exit(CPASS(citadel/level1/a2),"northeast",0,-1);
   set_alarm(0.0,0.0,"reset_room");
}

reset_room()
{
   if (!objectp(scout))
   {
      scout=clone_object("/d/Kalad/common/wild/pass/citadel/npc/scout");
      scout->arm_me();
      scout->move_living("M",TO);
      scout -> add_prop(OBJ_I_HIDE, 75);
   }
}

/* makes the scout whistle to warn his fellows of intruders */
int
whistle()
{
   if (!present(scout,TO)) return 0;    /* return if no scout is here */
   if (!IS_OUTLAW(TP) && CAN_SEE(scout,TP))
   {
      switch (TP->query_skill(SS_AWARENESS))
      {
         case 31..50:
            TP->catch_msg("You hear a weak but clear whistling sound "+
               "from somewhere behind you.\n");
            break;
         case 51..100:
            TP->catch_msg("You hear a weak but clear whistling sound "+
               "from somewhere behind you. It sounds like a warning-signal.\n");
            break;
         default: break; /* lousy awareness gives no warning */
      }
      return 0;
   }

   /* reaction to outlawed players */
   TP->catch_msg("You hear someone whisper behind you: Welcome, brigand!\n");
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