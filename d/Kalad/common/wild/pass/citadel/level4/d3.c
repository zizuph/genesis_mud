/*
 * Made by Korat
 * may 1996
 *
*/

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ogre;
object ogre1;
object ogre2;
object brigand1;
object brigand2;
object brigand3;
object goliath;


create_room()
{
   ::create_room();
   set_short("dwarven Citadel");
   set_long("You are inside an ancient citadel, long abandoned "+
      "by their masters and makers, the deep dwarves. "+
      "And this room is the top center of the complex, probably "+
      "intended for the main leader of the citadels guardians. "+
      "It seems like the brigands has put it into proper use, "+
      "because all around you see different loot that must have "+
      "cost several traders their lives as their caravans was robbed. "+
      "The only exit is back northwest.\n");
   add_item(({"chair","chairs","table","tables"}),"They are all "+
      "made of wood, but looks fairly solid. They must be to survive "+
      "those drunk ogres you have seen roaming this citadel.\n");
   add_item("loot","You see several decorated chairs, different "+
      "equipment as armours, weapons and other instruments of war. "+
      "A large mirror has been placed against the wall and different "+
      "banners branished with all kinds of ornamentals and symbols "+
      "carpets the cold face of the stonewalls.\n");
   add_item("mirror","The mirror is large, implying its worth. The "+
      "golden colored frame does not ruin your impression. It is too "+
      "heavy to carry for a single man though. Unless you are as "+
      "strong as some of the ogres you passed to get up here.\n");
   add_item("banners","The banners are covered with different symbols. "+
      "A huge red one you recognize as originally belonging to a "+
      "trading-company situated in Kabal. Daring men these brigands "+
      "that takes on as powerful men as them!\n");
   add_item(({"red banner","company banner"}),
      "This banner is huge. But that is the only special attribute "+
      "of it, except for the wall behind it that looks somewhat special.\n");
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

   add_exit(CPASS(citadel/level4/d2),"north","@@block",-1);
   set_alarm(0.0,0.0,"reset_room");
}

/* There is a wall that can be pushed here */
void
init()
{
   ::init();
   add_action("push","push");
}

/* command for pushing a part of the wall. */
void
push(string str)
{
   if (str != "wall")
   {
      TP->catch_msg("Push what?\n");
      return;
   }
   /* strong enough? */
   if (TP->query_base_stat(SS_STR) < 70)
   {
      TP->catch_msg("You push and push, but nothing happens.\n");
      tell_room(TO,QCTNAME(TP)+" pushes at the wall, but nothing happens.\n",TP);
      return;
   }
   TP->catch_msg("You push at the wall, and soon you manage to swing it around. "+
      "You suddenly find yourself falling!\n");
   TP->move_living("arrives falling.",CPASS(citadel/level4/falling));
}

reset_room()
{
   if (!objectp(ogre1))
   {
      ogre1=clone_object("/d/Kalad/common/wild/pass/citadel/npc/ogre_big");
      ogre1->arm_me();
      ogre1->move_living("M",TO);
      ogre1->command("emote groans as you arrive.");
   }
   if (!objectp(ogre))
   {
      ogre=clone_object("/d/Kalad/common/wild/pass/citadel/npc/ogre_big");
      ogre->arm_me();
      ogre->move_living("M",TO);
      ogre1->command("emote grunts: Got any booze on yah! Me like booze.");
   }
   if (!objectp(ogre2))
   {
      ogre2=clone_object("/d/Kalad/common/wild/pass/citadel/npc/ogre_big");
      ogre2->arm_me();
      ogre2->move_living("M",TO);
   }
   if (!objectp(brigand1))
   {
      brigand1=clone_object("/d/Kalad/common/wild/pass/citadel/npc/brigand_medium");
      brigand1->arm_me();
      brigand1->move_living("M",TO);
   }
   if (!objectp(brigand2))
   {
      brigand2=clone_object("/d/Kalad/common/wild/pass/citadel/npc/brigand_big");
      brigand2->arm_me();
      brigand2->move_living("M",TO);
   }
   if (!objectp(brigand3))
   {
      brigand3=clone_object("/d/Kalad/common/wild/pass/citadel/npc/brigand_medium");
      brigand3->arm_me();
      brigand3->move_living("M",TO);
   }
   if (!objectp(goliath))
   {
      goliath=clone_object("/d/Kalad/common/wild/pass/citadel/npc/bandit_overlord");
      goliath->arm_me();
      goliath->move_living("M",TO);
      goliath->command("say Lousy visitors! You better be worth my time!");
   }
   ogre->team_join(brigand1);
   ogre->team_join(brigand2);
   ogre->team_join(brigand3);
   ogre->team_join(goliath);
   ogre->team_join(ogre1);
   ogre->team_join(ogre2);
}

/* make the player be scared if they left while fighting */
int
block()
{
   /* add a scared-prop */
   if (member_array(goliath, TP->query_enemy(-1)))
      TP->add_prop("IS_SCARED_OF_GOLIATH",1);
 
   /* let the player leave */
   TP->catch_msg("Luckily none was standing in the opening, blocking it.\n");
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
