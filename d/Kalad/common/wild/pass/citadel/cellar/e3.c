/*
 * Made by Korat
 * november 1996
 *
 * A cellar/dungeon beneath the dwarven citadel
*/

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

object spider;
int done_corpse;

void
create_room()
{
   ::create_room();
   set_short("cellar. @@tracking@@");
   set_long("You are beneath an ancient citadel, long abandoned "+
      "by their masters and makers, the Deep Dwarves. "+
      "Large boulders and stones litter this hallway, making "+
      "it hard to find any paths inbetween them. Among the stones "+
      "large cobwebs shines in the light you carry, making it "+
      "sparkle as being covered with gems. A larger silky web "+
      "attracts your attention. The shadows cast "+
      "by yourself dances in the light, and mingles with the "+
      "everdark areas at the edge of your view.\n\n" +

      /* exits are visible according to the tracking skill of
       * the player
       */

      "@@tracking@@\n");

   add_item(({"cobweb","web","silky network","silky web"}),
      "They are woven, silky networks spun by spiders through "+
      "time. All of them look to be abandoned by their creators, "+
      "much like this place itself; left alone to slowly be "+
      "grinned down by the sand carried along with the wind. One of "+
      "them seems to be occupied since it contains large "+
      "balls of stick webstrings.\n");
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
   add_item(({"ball","balls"}),"Especially one of them catches "+
      "your attention. It is as large as a human!\n");

   /* gives random darkness descriptions. 'A dark room' is so boring. */
   add_prop(ROOM_S_DARK_LONG,"@@dark_description@@\n");
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);

   add_exit(CPASS(citadel/cellar/e10),"northeast","@@walk",3,1);
   add_exit(CPASS(citadel/cellar/e4),"northwest","@@walk",3,1);
   add_exit(CPASS(citadel/cellar/e2),"up","@@up",3,1);

   set_alarm(0.0,0.0,"reset_room");
}

reset_room()
{
   if (!objectp(spider))
   {
      spider=clone_object("/d/Kalad/common/wild/pass/dwarf/npc/spider");
      spider->move_living("M",TO);
      spider->command("emote snaps after you with its mandibles.");
   }
   done_corpse = 0;
}

void
init()
{
   ::init();
   add_action("cut","cut");
}

int
cut(string what)
{
   object weap1, weap2, weap3;

   if (what != "ball")
   {
      NF("Cut what?\n");
      return 0;
   }

   if (done_corpse)
   {
      NF("It has already been cut open.\n");
      return 0;
   }

   weap1 = TP->query_weapon(W_LEFT);
   weap2 = TP->query_weapon(W_RIGHT);
   weap3 = TP->query_weapon(W_BOTH);

   if (!weap1 && !weap2 && !weap3)
   {
      NF("Cut with what? You don't have any weapon wielded!\n");
      return 0;
   }
   if (weap1 && (weap1->query_wf(W_SLASH) || weap1->query_wf(W_IMPALE)))
   {
      set_alarm(1.0,0.0,"do_cut",TP,weap1);
      return 1;
   }
   if (weap2 && (weap2->query_wf(W_SLASH) || weap2->query_wf(W_IMPALE)))
   {
      set_alarm(1.0,0.0,"do_cut",TP,weap2);
      return 1;
   }
   if (weap3 && (weap3->query_wf(W_SLASH) || weap3->query_wf(W_IMPALE)))
   {
      set_alarm(1.0,0.0,"do_cut",TP,weap3);
      return 1;
   }
   NF("Cut it open with that? No way!\n");
   return 0;
}

void
do_cut(object player, object weapon)
{
   object corpse;

   set_this_player(player);
   write("You cut open the ball of silky web with your "+
      weapon->query_short()+".\n");
   say(QCTNAME(TP)+" cuts open a ball of silky web with "+
      HIS(TP) + " " + weapon->query_short() + ".\n");

   tell_room(TO,"A corpse falls out of the ball of silky web.\n");

   corpse = clone_object(CPASS(citadel/npc/corpse));
   corpse -> move(TO);
   corpse -> set_hp(1);
}

/* give a feeling of walking on a path */
int
walk()
{
   TP->catch_msg("You follow a twisting path that takes you further "+
       "into this underground area.\n");
   return 0;
}

int
up()
{
   TP->catch_msg("As you walk you notice that you ascend "+
      "upwards.\n");
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
      case 0 .. 25:
      {
          return "You look around but cannot see any paths "+
             "leading out of here.";
          break;
      }
      default:
      {
          return "You notice some footsteps in the dust leading "+
             "towards the northeast, northwest and upwards.";
          break;
      }
   }
}

