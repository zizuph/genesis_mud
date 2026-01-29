/* deep dwarf guards */
/* by Korat */

inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/wild/pass/dwarf/npc/talk.h"

/* These are random guards descriptions */
#define RNDADJ ({"nervous","bitter","grumpy","barrel-chested","huge"})

/* These is random equipment for guards */
#define RNDARM ({"robe","shield","chain","splint","plate"})
#define RNDWEP ({"knife","sword","spear","waraxe","warhammer"})

create_monster() 
{
   int ran;
   
   if (!IS_CLONE)
      return;
   
   ran = random(5);
   set_name("warrior");
   add_name(({"deep dwarf","guard","dwarf guard"}));
   set_pname("deep dwarves");
   set_short(RNDADJ[ran] + " deep dwarf");
   set_race_name("dwarf");
   set_adj(RNDADJ[ran]);
   set_alignment(300+(ran*100));  /* from 300 to 700 */
   set_knight_prestige(-3-(ran)); /* from -3 to -7 */

   /* random descriptions and stats */
   switch (ran)
   {
      case 0:
      set_long("This deep dwarf peers nervously around. He looks "+
         "very young to be a warrior, but it seems like any man able "+
         "to wield an axe is good enough in these times of trouble.\n");
      set_stats(({40,20,29,20,15,35}));
      break;
      case 1:
      set_long("A tough dwarf, well equipped and ready for combat.\n");
      set_stats(({62,45,59,30,30,50}));
      break;
      case 2:
      set_long("This deep dwarf looks very well trained, but "+
         "still he has a grim expression. Wartime gets on the nerves.\n");
      set_stats(({85,65,75,40,47,70}));
      break;
      case 3:
      set_long("When you look at this deep dwarf you understand he "+
         "can be a bitter enemy to those that dares to attack.\n");
      set_stats(({103,82,101,53,43,100}));
      break;
      case 4:
      set_long("Off all the deep dwarves you have seen wielding a "+
         "weapon, this one looks like the hardest and most dangerous "+
         "opponent. He must be a veteran of this war, and maybe has "+
         "seen other times of trouble too; And survived them!\n");
      set_stats(({130,90,120,50,50,120}));
      break;
      default: break;
   }
   add_prop(CONT_I_WEIGHT,30000);
   add_prop(CONT_I_HEIGHT,500);
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(LIVE_I_SEE_DARK,10);
   
   
   set_skill(SS_UNARM_COMBAT, 20 + (ran*10));
   set_skill(SS_WEP_KNIFE, 30 + (ran*10));
   set_skill(SS_WEP_AXE, 50 + (ran*10));
   set_skill(SS_WEP_POLEARM, 40 + (ran*10));
   set_skill(SS_WEP_CLUB, 50 + (ran*10));
   set_skill(SS_WEP_SWORD, 30 + (ran*10));
   set_skill(SS_DEFENCE, 40 + (ran*10));
   set_skill(SS_PARRY, 30 + (ran*10));
   set_skill(SS_AWARENESS, 10 + (ran*10));
   set_skill(SS_LANGUAGE, 60);

   set_act_time((ran*5)+5);
   /* do_speak will make the npc talk their own language */
   add_act("@@do_mutter@@");
   add_act(({"peer nervously",
            "emote looks around carefully.","emote strokes his beard.",
            "emote stumbles.","emote polishes his weapon."}));
   set_cact_time(5+(ran*2));
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
   ran = random(5);
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
      case 0: do_say("If only they didn't break down our defences so easily.");
      break;
      case 1: do_say("I hate those Drows!"); 
      break;
      case 2: do_say("Why? Why do they have to make trouble ...");
      break;
      case 3: do_say("Times of trouble these days. Not good, not good at all.");
      break;
      case 4: do_say("Strangers! Can we trust them?"); 
      break;
      case 5: do_say("Kill them all I say, but nobody listens to me.");
      break;
      case 0: do_say("If only they didn't break down our defences so easily.");
      break;
      case 6: do_say("Those duergars are a lousy lot. "+
                        "Stealing and pillaging is all they do.");
      break;
      case 7: do_say("If only that stupid old priest would stop "+
                     "stuffing our ears with his tales of God's and old times.");
      break;
      case 8: do_say("All these strangers. Lets hope they come "+
                     "here to help us crack some elven necks!");
      break;
      case 9: do_say("If only our King didn't ask the duergars to come "+
                     "to our aid! All they will do is to watch the drows "+
                     "slay us all, and then go off to loot our corpses!");
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
      case 0: do_say("Hey, this idiot wants to fight!");
      break;
      case 1: do_say("I'll smash your face in."); 
      break;
      case 2: do_say("We are under attack!! The drows are coming!");
      break;
      case 3: do_say("Spies! Kill'em all."); 
      break;
      case 4: do_say("Enemies in the town! Warn the King!!");
      break;
      case 5: do_say("Bring it on scumbag, I'll turn your head into ush!");
      break;
      case 6: do_say("What are we going to do!? We need help!"); 
      break;
      default: break;
   }
}

void
help_friend(object ob)
{
   if (ob && !query_attack() && present(ob, environment()))
      {
      switch (random(4))
      {
         case 0:
         do_say("This will be a fight till death, fools!");
         break;
         case 1:
         TO->command("emote plants his feet on the ground."); break;
         case 2:
         TO->command("emote works himself into a wild battlerage!"); break;
         case 3:
         TO->command("emote croaches down, and runs at you!"); break;
         default:break;
      }
      set_alarm(1.0,0.0,"do_kick",ob); /* a special attack that initiates combat */
   }
}   

/* triggered on introductions */

/* respons on introductions */
public void
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
         do_say("Beware.  We can "+
            "be attacked at any time!"); break;
         case 3:
         command("nod "+obj->query_real_name());
         break;
         case 4:
         do_say("Hi! How ar'yah doing. Keep yah axe sharp!");
         break;
         case 5:
         do_say("Have you come to help us "+
            "? We need it ...");
         break;
         default: break;
      }
   }
   return;
}

/* special attack that the npc's use to initiate combat */

public int
do_kick(object target)
{
   string how;
   mixed *hitresult;
   object attacker;

   /* The player kicks someone, so we will make an attempt to
   * do damage and then initiate combat.
   */

   if (!F_DARE_ATTACK(TO, target))
      {
      do_say("I don't dare to attack! We need heeelp!!");
      return 1;
   }
   if (target && environment(TO) != environment(target))
      {
      do_say("Hahh! Ran away like a chicken ...");
      return 1;
   }

   TO->attack_object(target);
   attacker = TO;

   hitresult = target->hit_me((TO->query_stat(0)*2), W_BLUDGEON, attacker, -1);
   how = "unharmed";
   if (hitresult[0] > 0)
      how = "a rib";
   if (hitresult[0] > 5)
      how = "two ribs";
   if (hitresult[0] > 10)
      how = "some ribs";
   if (hitresult[0] > 20)
      how = "several ribs";
   if (hitresult[0] > 50)
      how = "the chest itself";
   
   if(hitresult[0] > 0)
      {
      attacker->catch_msg("The kick lands hard into "+
         QTNAME(target)+"'s chest. You hear "+
         "the dry sound of "+how+" cracking from the impact!\n");
      target->catch_msg(QCTNAME(attacker) +
         " kicks you in the chest with all "+attacker->query_possessive()+
         " might. You feel "+how+" crack from the impact!\n");
      tell_watcher(QCTNAME(attacker) + " kicks " + QTNAME(target) +
         " hard in the chest. You can hear the dry sound of "+
         how+" cracking from he impact!\n", attacker, target);
      if (target->query_hp() <= 0)
         target->do_die(attacker);
      return 1;
   }
   attacker->catch_msg("You miss with the kick against "+
      QTNAME(target)+"'s chest and fall flatfaced down on the ground.\n");
   target->catch_msg(QCTNAME(attacker) +
      " tries to kick you in your chest, but misses utterly and "+
      " falls flatfaced down on the ground.\n");
   tell_watcher(QCTNAME(attacker) + " tries to kick " + QTNAME(target) +
      " in the chest, but misses utterly and falls flatfaced down "+
      " on the ground.\n", attacker, target);
   return 1;
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
