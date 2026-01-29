/*
 * Made by Korat
 * may 1996
 *
*/

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/sys/outlaw.h"
object ogre;
object ogre1;
object brigand1;
object brigand2;

create_room()
{
   ::create_room();
   set_short("dwarven Citadel. A hallway continues to the northeast and south");
   set_long("You are inside an ancient citadel, long abandoned "+
      "by their masters and makers, the deep dwarves. "+
      "Even though the citadel has clear marks of decay from "+
      "the centuries of abandonment, the masonry is of such "+
      "quality that you still have problems finding the "+
      "cracks inbetween the stoneblocks. "+
      "The hallway continues towards northeast and south, hiding "+
      "its content in a veil of darkness.\n");

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
   set_noshow_obvious(1);

   add_exit(CPASS(citadel/x17),"northeast","@@block",-1);
   add_exit(CPASS(citadel/x15),"south","@@down",-1);
   set_alarm(0.0,0.0,"reset_room");
}

reset_room()
{
   if (!objectp(ogre1))
   {
      ogre1=clone_object("/d/Kalad/common/wild/pass/citadel/npc/ogre_medium");
      ogre1->arm_me();
      ogre1->move_living("M",TO);
      ogre1->command("emote laughs viciously.");
   }
   if (!objectp(ogre))
   {
      ogre=clone_object("/d/Kalad/common/wild/pass/citadel/npc/ogre_big");
      ogre->arm_me();
      ogre->move_living("M",TO);
   }
   if (!objectp(brigand1))
   {
      brigand1=clone_object("/d/Kalad/common/wild/pass/citadel/npc/brigand_medium");
      brigand1->arm_me();
      brigand1->move_living("M",TO);
   }
   if (!objectp(brigand2))
   {
      brigand2=clone_object("/d/Kalad/common/wild/pass/citadel/npc/brigand_medium");
      brigand2->arm_me();
      brigand2->move_living("M",TO);
   }
   ogre->team_join(brigand1);
   ogre->team_join(brigand2);
   ogre->team_join(ogre1);
}

/* give a feeling of going downwards*/
int
down()
{
   TP->catch_msg("As you walk you notice that you decend slowly "+
      "downwards.\n");
   return 0;
}

/* stops intruders and give a feeling of going upwards*/
int
block()
{
   object stun;
   if (!present(ogre,TO)) return 0;    /* return if no ogre is here */
   if (!IS_OUTLAW(TP) && CAN_SEE(ogre,TP)) /* react if player is not outlaw */
   {
      ogre->command("emote screams at you: Da idiot think me will let 'em go "+
         "befor me kill and KILL and KILL!!\n"); 
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
   TP->catch_msg("As you walk you notice that you accend slowly "+
      "upwards.\n");
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