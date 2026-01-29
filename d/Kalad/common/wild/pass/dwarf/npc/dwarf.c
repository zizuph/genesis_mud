/* deep dwarf guards */
/* by Korat */

inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/wild/pass/dwarf/npc/talk.h"

/* These are random guards descriptions */
#define RNDADJ ({"wrinkled","small","curious","scared","nervous"})

/* These is random equipment for guards */
#define RNDARM ({"robe","shield","belt"})
#define RNDWEP ({"knife","miner_axe","spear"})

create_monster() 
{
   int ran;
   
   if (!IS_CLONE)
      return;
   
   ran = random(5);
   set_name("commondwarf");
   add_name(({"deep dwarf"}));
   set_pname("deep dwarves");
   set_short(RNDADJ[ran] + " deep dwarf");
   set_race_name("dwarf");
   set_adj(RNDADJ[ran]);
   set_alignment(500+(ran*100));  /* from 500 to 900 */
   set_knight_prestige(-3-(ran)); /* from -5 to -9 */

   /* random descriptions and stats */
   switch (ran)
   {
      case 0:
      set_long("This dwarf looks like one of the old maps "+
         "you once saw in a library. All wrinkles and beard.\n");
      break;
      case 1:
      set_long("You have seldom seen such a small dwarf ever. "+
         "Not much flesh on those bones; they must be starving here.\n");
      break;
      case 2:
      set_long("Peering at you from behind the small beard, this "+
         "dwarf seems curious about how you ended up here. It seems "+
         "like they are not used to your kind down here.\n");
      break;
      case 3:
      set_long("You notice at once that this deep dwarf is scared "+
         "by your presence. The war must have made the deep dwarves "+
         "quite nervous.\n");
      break;
      case 4:
      set_long("This deep dwarf keeps trying to avoid your scrutinizing "+
         "look. Some nervous twitching can be seen in the dwarfs face.\n");
      break;
      default: break;
   }
   set_stats(({40,20,29,20,15,30}));
   add_prop(CONT_I_WEIGHT,20000);
   add_prop(CONT_I_HEIGHT,400);
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(LIVE_I_SEE_DARK,10);
   
   set_skill(SS_UNARM_COMBAT, 10 + (ran*10));
   set_skill(SS_WEP_KNIFE, 10 + (ran*10));
   set_skill(SS_WEP_AXE, 20 + (ran*10));
   set_skill(SS_WEP_POLEARM, 20 + (ran*10));
   set_skill(SS_DEFENCE, 10 + (ran*5));
   set_skill(SS_PARRY, 10 + (ran*5));
   set_skill(SS_AWARENESS, 10 + (ran*5));
   set_skill(SS_LANGUAGE, 60);
   
   /* the smaller talks more than the bigger */
   set_act_time((ran*5)+5); 
   /* do_speak will make the npc talk their own language */
   add_act("@@do_mutter@@");
   add_act(({"peer nervously",
            "emote looks around carefully.","emote strokes the beard.",
            "emote tries to avoid you.","emote strokes the unkept beard."}));
   /* the smaller talks more than the bigger */
   set_cact_time(5+(ran));
   add_cact("@@do_comb_speak@@");
   add_cact(({"scream","panic","cry","cringe","gasp"}));

}

/* Here I equip the dewars with weapons and armours */
void
arm_me()
{
   int ran;
   object wep;
   object arm;
   seteuid(getuid(this_object()));
   ran = random(3);
   wep = clone_object("/d/Kalad/common/wild/pass/dwarf/wep/" + RNDWEP[ran]);
   wep -> move(this_object());
   command("wield all");
   arm = clone_object("/d/Kalad/common/wild/pass/dwarf/arm/" + RNDARM[ran]);
   arm -> move(this_object());
   arm = clone_object(CPASS(dwarf/arm/dew_boots));
   arm -> move(this_object());
   command("wear all");
}

/* random sentences generated. Actual talk done through do_say() */
void
do_mutter()
{
   switch (random(10))
   {
      case 0: do_say("If only they didn't break down our "+
                     "defences so easily. Then we would at least "+
                     "have a hope for survival.");
      break;
      case 1: do_say("Those tales of the Drows scares me."); 
      break;
      case 2: do_say("Why? Why do they have to make trouble?");
      break;
      case 3: do_say("Times of trouble these days. "+
                      "Not good, not good at all.");
      break;
      case 4: do_say("Strangers. I don't trust them."); 
      break;
      case 5: do_say("I am hungry.");
      break;
      case 6: do_say("Those duergars are a lousy lot. "+
                        "Stealing and pillaging is all they do.");
      break;
      case 7: do_say("Maybe we should listen to the old priest? "+
                     "His tales of old are at least amusing.");
      break;
      case 8: do_say("All these strangers. Lets hope they come "+
                     "here to help us mine out coal. Then we "+
                     "don't have to do it!");
      break;
      case 9: do_say("Our King will remedy all the ills we are "+
                     "suffering now. In time our halls will shine "+
                     "like they did before.");
      break;
      default: break;
   }
}

public int
do_speak(object dummy)
{
    do_mutter();
    return 1;
}

void
do_comb_speak()
{
   switch (random(7))
   {
      case 0: do_say("Heeeeeeeeelp!");
      break;
      case 1: do_say("Pleeease?? I am but a farmer of no "+
                     "importance!"); 
      break;
      case 2: do_say("We are under attack!! The drows are coming!");
      break;
      case 3: TO->command("scream"); 
      break;
      case 4: TO->command("panic");
      break;
      case 5: TO->command("cry");
      break;
      case 6: TO->command("emote groans painfully."); 
      break;
      default: break;
   }
}

/* respons on introductions */
void
introduce_me(string person)
{
   object obj;
   person = lower_case(person);
   if(obj = present(person, environment()))
      {
      /* only return intro to dwarves */
      if (obj->query_race_name() != "dwarf")
         {
         return;
      }
      switch (random(6))
      {
         case 0:
         do_say("Greetings.");
         break;
         case 1:
         command("shake "+obj->query_real_name());
         break;
         case 2:
         do_say("Axe high!  Battle is soon upon us."); break;
         case 3:
         command("smile "+obj->query_real_name());
         break;
         case 4:
         do_say("Hi! Got any food to spare?");
         break;
         case 5:
         do_say("Have you come to help us"+
            "? We need it ...");
         break;
         default: break;
      }
   }
   return;
}

/* player is alone and is a friend */
void
do_react_friend_alone(object player)
{
   switch (random(10))
   {
      case 0:
      TO->command("nod . "+player->query_real_name());
      break;
      case 1:
      TO->command("greet "+player->query_real_name());
      break;
      case 2:
      do_say("Have you seen any drows around?");
      break;
      case 3:
      do_say("Stay alert "+capitalize(player->query_real_name())+
         ", they might attack at any moment...");
      break;
      case 4:
      TO->command("emote sighs relieved.");
      break;
      case 5:
      do_say("I think I saw one! In that shadow ...over there.");
      TO->command("emote points towards a ruin.");
      break;
      case 6:
      TO->command("hug "+player->query_real_name());
      break;
      default: break;
   }
}

/* player is alone and is an enemy eg. wrong race */
void
do_react_enemy_alone(object player)
{
   switch (random(9))
   {
      case 0:
      do_say("Die, enemy of my kin!");
      break;
      case 1:
      do_say("The drooows are heeere!!");
      break;
      case 2:
      do_say("It is a drow! It must be!! It is so ugly!!!");
      break;
      case 3:
      TO->command("spit "+player->query_real_name());
      break;
      case 4:
      TO->command("emote cringes in terror!");
      break;
      case 5:
      TO->command("panic");
      break;
      case 6:
      TO->command("emote looks at you in utter fear.");
      break;
      default:break;
   }
   set_alarm(0.0,0.0,"do_kick", player);
}

/* player is in a team (reacts on team-leader) and is friendly */
void
do_react_friend_team(object friend, object *team)
{
   object *enemies;
   object *dummy;
   int i;
   
   /* team-members might be enemies, but since team-leader is
   a friend we accept them */
   enemies = team;
   enemies -= ({ friend });

   /* if we are alot of npc's we let the leader talk only */
   if (objectp(dummy = this_object->query_leader()))
      do_say("Make sure your friends behave, "+
         capitalize(friend->query_real_name())+".");

   /* if we are alone we talk */
   if (!sizeof(this_object->query_team_others()))
      do_say("Make sure your friends behave, "+
         capitalize(friend->query_real_name())+".");

   for (i=0;i<sizeof(enemies);i++)
   {
      if(member_array(enemies[i]->query_race_name(),accepted_races) < 0)
         {
         switch (random(8))
            {
            case 0:
            TO->command("emote peers suspiciously at you.");
            break;
            case 1:
            TO->command("poke "+enemies[i]->query_real_name());
            break;
            case 2:
            TO->command("nudge "+enemies[i]->query_real_name());
            break;
            case 3:
            TO->command("emote looks uneasy in your presence.");
            break;
            case 4:
            do_say("Beware! Surface dwellers are here!");
            break;
            case 5:
            TO->command("emote polishes his weapon.");
            break;
            case 6:
            TO->command("emote rests his hand on the hilt in warning.");
            break;
            default:break;
         }
      }
   }
}

/* player is enemy and is a leader of a team */
void
do_react_enemy_team(object player, object *team)
{
   switch (random(8))
   {
      case 0:
      TO->command("spit "+player->query_real_name());
      break;
      case 1:
      do_say("Cowards! You don't dare to meet me alone huh?");
      break;
      case 2:
      do_say("We are under attack!!!"); break;
      case 3:
      TO->command("emote grumbles: Lousy, cowards!");
      break;
      case 4:
      TO->command("emote swings his weapon towards you!");
      break;
      case 5:
      do_say("I will cut you into ribbons. Both you and your friends, "+
         capitalize(player->query_real_name())+"!");
      break;
      case 6:
      TO->command("emote looks for a place to hide, but finds none!");
      break;
      default:break;
   }
   /* do_kick() will  initiate an attack */
   set_alarm(0.0,0.0,"do_kick",player);
}
