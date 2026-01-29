/*
 * Made by Korat
 * november 1996
 *
 * A cellar/dungeon beneath the dwarven citadel
*/

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/sys/outlaw.h"
object ogre;
object brigand1;
object brigand2;

create_room()
{
   ::create_room();
   set_short("cellar. @@tracking@@");
   set_long("You are beneath an ancient citadel, long abandoned "+
      "by their masters and makers, the Deep Dwarves. "+
      "Large boulders and stones litter this hallway, making "+
      "it hard to find any paths inbetween them. Among the stones "+
      "large cobwebs shines in the light you carry, making it "+
      "sparkle as being covered with gems. The shadows cast "+
      "by yourself dances in the light, and mingles with the "+
      "everdark areas at the edge of your view.\n\n" +

      /* exits are visible according to the tracking skill of
         the player */

      "@@tracking@@\n");

   add_item(({"cobweb","web","silky network","silky web"}),
      "They are woven, silky networks spun by spiders through "+
      "time. All of them look to be abandoned by their creators, "+
      "much like this place itself; left alone to slowly be "+
      "grinned down by the sand carried along with the wind.\n");

   add_item(({"wall","walls","ceiling","roof"}),
      "Both the walls and the ceiling looks to be cut out of the "+
      "mountain itself. Through time green moss has managed "+
      "to cover it.\n");
   add_item("floor","The floor is covered with fine-grained, white "+
      "sand that must have been carried in here with the wind from the "+
      "great Kaladian waste.\n");
   add_item(({"boulder","boulders","rock","rocks"}),
      "They litter the area, making it very hard to see any path "+
      "that you can follow.\n");
   add_item(({"path","paths"}), "You have a hard time to see "+
      "any paths here. @@tracking@@\n");

   /* gives random darkness descriptions. 'A dark room' is so boring. */
   add_prop(ROOM_S_DARK_LONG,"@@dark_description@@\n");
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);

   add_exit(CPASS(citadel/x1),"up","@@up",3);
   add_exit(CPASS(citadel/cellar/e2),"northwest","@@block",3,1);
   set_alarm(0.0,0.0,"reset_room");
}

reset_room()
{
   if (!objectp(ogre))
   {
      ogre=clone_object("/d/Kalad/common/wild/pass/citadel/npc/ogre_small");
      ogre->arm_me();
      ogre->move_living("M",TO);
      ogre->command("emote laughs viciously.");
   }
   if (!objectp(brigand1))
   {
      brigand1=clone_object("/d/Kalad/common/wild/pass/citadel/npc/brigand_small");
      brigand1->arm_me();
      brigand1->move_living("M",TO);
   }
   if (!objectp(brigand2))
   {
      brigand2=clone_object("/d/Kalad/common/wild/pass/citadel/npc/brigand_small");
      brigand2->arm_me();
      brigand2->move_living("M",TO);
   }
   ogre->team_join(brigand1);
   ogre->team_join(brigand2);
}

/* give a feeling of going downwards */
int
up()
{
   TP->catch_msg("You climb over the rubble to get yourself upwards.\n");
   return 0;
}

/* stops intruders */
int
block()
{
   object stun;
   if (!present(ogre,TO)) return 0;    /* return if no ogre is here */
   if (!IS_OUTLAW(TP) && CAN_SEE(ogre,TP)) /* react if player is not outlaw */
   {
      ogre->command("emote screams at you: Da idiot think me will let 'em go "+
         "befar me kill!\n"); 
      tell_room(TO,QCTNAME(TP)+" tried to walk further into the citadel but "+
         "was brutally stopped by a ogre smashing a fist into "+HIS(TP)+
         "face.\n",TP);
      TP->catch_msg("The huge ogre smashes a fist into your face. You feel "+
         "dazed!\n");
      stun=clone_object("/d/Kalad/common/wild/pass/citadel/obj/stun");
      stun->move(TP);
      return 1;
   }

   /* reaction to outlawed players */
   TP->catch_msg("As you walk you notice that you decend slowly "+
      "downwards.\n");
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
         desc = "You find yourself inside utter darkness.";
         break;
      case 1:
         desc = "A weak and chilling wind is all breaks the darkness.";
         break;
      case 2:
         desc = "You think you hear some sounds in front of you, but "+
                "without vision you cannot know what it comes from.";
         break;
      case 3:
         desc = "A dark room that envelopes you like a cloak of death.";
         break;
      case 4:
         desc = "You touch the wall to make sure you walk in the right "+
                "direction.";
         break;
      default: break;
   }
   
   return desc;
}

/* 
 * function: tracking
 * description: We check if the player has good enough tracking skill
 *              to see the right path in this room. Only if the skill
 *              is high enough, will we allow the player to use the
 *              exit. This function will return the description of the
 *              exits he/she has the skill to see.
 * returns: The exits seen by the player according to tracking skill
 */
string
tracking()
{
   int skill = TP->query_skill(SS_TRACKING);

   switch (skill)
   {
      case 0 .. 10:
      {
          return "You look around but cannot see any exits except "+
             "back up to the citadel.";
          break;
      }
      default:
      {
          return "You notice some footsteps in the dust leading "+
             "towards the northwest.";
          break;
      }
   }
}
