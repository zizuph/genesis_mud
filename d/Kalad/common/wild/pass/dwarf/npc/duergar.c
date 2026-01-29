/* duergar warriors */
/* based on Anth's work */

inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/wild/pass/dwarf/npc/talk.h"

string *accepted_races = ({"dwarf","duergar"});

/* These are random guards descriptions */
#define RNDADJ ({"dirty","short","grim","treacherous","rough"})

/* These is random equipment for guards */
#define RNDARM ({"plate","shield","robe","chain","jerkin"})
#define RNDWEP ({"waraxe","sword","knife","warhammer","spear"})

create_monster() {
   int ran;
   
   if (!IS_CLONE)
      return;
   
   ran = random(5);
   set_name("warrior");
   add_name(({"duergar","duergar guard"}));
   set_pname("duergar");
   set_short(RNDADJ[ran] + " duergar");
   set_race_name("duergar");
   set_adj(RNDADJ[ran]);
   set_alignment(-300-(ran*100));
   set_knight_prestige(-3-(ran));

   switch (ran)
   {
      case 0:
      set_long("Dressed in dirty and smelling armours, this dwarf seems quite "+
         "eager to swap with your equipment. With the long unkept beard " +
         "and the vicious glint in the eyes making him look quite " +
         "dangerous.\n");
      set_stats(({85,35,65,30,27,65}));
      break;
      case 1:
      set_long("This duergar is a smaller warrior but not less dangerous if "+
         "caught in a corner. Better avoid messing with him.\n");
      set_stats(({62,45,59,30,30,55}));
      break;
      case 2:
      set_long("He looks like a tough opponent even tougher than others " +
         "you have seen around here. Especially if angered.\n");
      set_stats(({86,50,67,25,25,70}));
      break;
      case 3:
      set_long("A duergar with goldlust shining in the eyes. Better watch "+
         "yourself!\n");
      set_stats(({93,72,91,33,33,85}));
      break;
      case 4:
      set_long("A duergar with the weapon ready to strike at any opportunity. "+
         "He seems to want to go and kill some drow or rats to feed on.\n");
      set_stats(({137,90,119,50,50,110}));
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

   set_act_time((ran*5)+10);
   add_act("@@do_mutter@@");
   add_cact(({"scream","spit","kick all","grin sadis"}));
   set_cact_time(10+(ran*2));
   add_cact("@@do_comb_speak@@");
   add_act(({"grin","grumble","smile evi","yawn","cackle"}));

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

void
do_mutter()
{
   switch (random(10))
   {
      case 1: do_say("I hate those Drows!"); break;
      case 2: do_say("Give me your gold!");
      break;
      case 3: do_say("Lets drink.");
      break;
      case 4: do_say("I hate that lousy king and his plans!"); break;
      case 5: do_say("Kill them all I say, but nobody listens to me.");
      break;
      case 0: do_say("Lets loot some ruins in the north.");
      break;
      case 6: do_say("Drows are lousy food!");
      break;
      case 7: do_say("You smell ... clean!");
      break;
      case 8: do_say("Be careful, you might trip on my weapon.");
      break;
      case 9: do_say("Get out of here scum!");
      break;
      default: break;
   }
}

void
do_comb_speak()
{
   switch (random(7))
   {
      case 0: do_say("Hey, this idiot wants to fight!");
      break;
      case 1: do_say("I'll smash your face in."); break;
      case 2: do_say("Idiot! I hope you carry some good loot.");
      break;
      case 3: do_say("Spies! Kill'em all."); break;
      case 4: do_say("Enemies in the town! Finally!!");
      break;
      case 5: do_say("Bring it on scumbag, I'll turn your head into ush!");
      break;
      case 6: do_say("I'll make a smile on your face ... "+
         "from ear to ear."); break;
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
         TO->command("emote grins viciously and get a wild look in the eyes.");
         break;
         case 1:
         TO->command("emote plants his feet on the ground."); break;
         case 2:
         TO->command("emote works himself into a wild battlerage!"); break;
         case 3:
         TO->command("emote croaches down, and runs at you!"); break;
         default:break;
       }
      set_alarm(1.0,0.0,"do_kick", ob);
   }
}   

public int
do_speak(object dummy)
{
    do_mutter();
    return 1;
}

public void
introduce_me(string person)
{
   object obj;
   person = lower_case(person);
   if(obj = present(person, environment()))
      {
      if (obj->query_race_name() != "dwarf")
         {
         return;
      }
      switch (random(6))
      {
         case 0:
         do_say("And?");
         break;
         case 1:
         command("grin "+obj->query_real_name());
         break;
         case 2:
         do_say("Beware, we can "+
            "end up in a fight if you don't keep your distance!"); break;
         case 3:
         command("nod "+obj->query_real_name());
         break;
         case 4:
         do_say("Nice tah meet you, nice tah forget you.");
         break;
         case 5:
         do_say("Have you come to help? "+
            "? Those gully deep dwarves surely need it. Lousy pay though.");
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
     do_say("This creature is too tough!! Lets run!");
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

/* we redefine the reactions these npc's do - see talk.h */
void
do_react_friend_alone(object player)
{
   switch (random(10))
   {
      case 0:
      TO->command("nod "+player->query_real_name());
      break;
      case 1:
      TO->command("greet "+player->query_real_name());
      break;
      case 2:
      TO->command("ask "+player->query_real_name()+" Have you seen any drows around?");
      break;
      case 3:
       do_say("Best to keep a sharp ear. "+
         "The enemy is known for their stealth...");
      break;
      case 4:
      TO->command("emote chuckles amusedly when studying you.");
      break;
      case 5:
      do_say("Come now"+
         ", lets drink! Lets slay some drows!! Lets have fun!!!");
      break;
      case 6:
      TO->command("nudge "+player->query_real_name());
      break;
      default: break;
   }
}

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
      TO->command("emote cheers!");
      break;
      case 5:
      TO->command("emote smiles a broad toothless grin.");
      break;
      case 6:
      TO->command("jump");
      break;
      default:break;
   }
   set_alarm(1.0,0.0,"do_kick", player);
}

void
do_react_friend_team(object friend, object *team)
{
   object *enemies;
   object *dummy;
   int i;
   enemies = team;
   enemies -= ({ friend });
   if (sizeof(dummy = TO->query_team_others()))
      {
      if(random(4) == 0)
         do_say("Make sure your friends behave, "+
         C(friend->query_real_name())+".");
   }
   else
      {
      do_say("Make sure your friends behave, "+
         C(friend->query_real_name())+".");
   }
   for (i=0;i<sizeof(enemies);i++)
   {
      if(member_array(enemies[i]->query_race_name(),accepted_races) > -1)
         break;
      
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
         C(player->query_real_name())+"!");
      break;
      case 6:
      TO->command("emote points to a place where you can hide while "+
         "laughing evilly.");
      break;
      default:break;
   }
   set_alarm(1.0,0.0,"do_kick",player);
}
