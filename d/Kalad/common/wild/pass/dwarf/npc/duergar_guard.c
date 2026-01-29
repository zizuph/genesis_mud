/* deep dwarf guards */
/* by Korat */

inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/sys/macros.h"
#include "/sys/filter_funs.h"
#include "/d/Kalad/defs.h"

/* These are random guards descriptions */
#define RNDADJ ({"tough","bitter","grumpy","broad","silent"})

/* These is random equipment for guards */
#define RNDARM ({"dwarf_plate","dwarf_shield","dwarf_robe","dwarf_chain","dwarf_splint"})
#define RNDWEP ({"sword","waraxe","warhammer","knife","spear"})
/* These are random combat and defence skills for guards */
#define SKILLCOM ({55,64,50,71,49})
#define SKILLDEF ({74,65,53,75,66})

string *accepted_races = ({"dwarf","duergar"});
int kicking = 0;

create_monster() {
   int ran;
   
   if (!IS_CLONE)
      return;
   
   ran = random(5);
   set_name("warrior");
   add_name(({"duergar","duergar dwarf","dwarf guard","guard","duergar guard"}));
   set_pname("duergars");
   set_short(RNDADJ[ran] + " duergar");
   set_race_name("duergar");
   set_adj(RNDADJ[ran]);
   set_alignment(100+(ran*100));
   switch (ran)
   {
      case 0:
      set_long("This deep dwarf looks very well trained, but "+
         "still he has a grim expression. Wartime gets on the nerves.\n");
      set_stats(({85,35,65,30,27,100}));
      break;
      case 1:
      set_long("A tough dwarf, well equipped and ready for combat.\n");
      set_stats(({62,45,59,30,30,100}));
      break;
      case 2:
      set_long("This deep dwarf peers nervously around. He looks "+
         "very young to be a warrior, but it seems like any man able "+
         "to wield an axe is good enough in these times of trouble.\n");
      set_stats(({40,20,29,20,15,100}));
      break;
      case 3:
      set_long("When you look at this deep dwarf you understand he "+
         "can be a bitter enemy to those that dares to attack.\n");
      set_stats(({63,42,81,33,33,100}));
      break;
      case 4:
      set_long("Off all the deep dwarves you have seen wielding a "+
         "weapon, this one looks like the hardest and most dangerous "+
         "opponent. He must be a veteran of this war, and maybe has "+
         "seen other times of trouble too; And survived them!\n");
      set_stats(({130,80,120,50,50,100}));
      break;
      default: break;
   }
   add_prop(CONT_I_WEIGHT,30000);
   add_prop(CONT_I_HEIGHT,500);
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(LIVE_I_SEE_DARK,10);
   
   
   set_skill(SS_UNARM_COMBAT, 10 + ran);
   set_skill(SS_WEP_KNIFE, SKILLCOM[ran]);
   set_skill(SS_WEP_AXE, SKILLCOM[ran]);
   set_skill(SS_WEP_POLEARM, SKILLCOM[ran]);
   set_skill(SS_WEP_CLUB, SKILLCOM[ran]);
   set_skill(SS_WEP_SWORD, SKILLCOM[ran]);
   set_skill(SS_DEFENCE, SKILLDEF[ran]);
   set_skill(SS_PARRY, SKILLDEF[ran]);
   set_skill(SS_AWARENESS, 50);
   set_skill(SS_LANGUAGE, 60);
   
   
   set_act_time((ran*5)+5);
   add_act("@@do_mutter@@");
   add_act(({"peer evil",
            "emote looks around carefully.","emote strokes his beard.",
         "emote drinks.","emote polishes his weapon."}));
   set_cact_time(5);
   add_cact("@@do_comb_speak@@");
   add_cact(({"cheer","grin evil","chuckle demon","laugh demon"}));
}

/* Here I equip the dewars with weapons and armours */
void
arm_me()
{
   int ran;
   object weap;
   object armo;
   seteuid(getuid(this_object()));
   ran = random(5);
   weap = clone_object("/d/Kalad/common/wild/pass/dwarf/wep/" + RNDWEP[ran]);
   weap -> move(this_object());
   command("wield all");
   ran = random(5);
   armo = clone_object("/d/Kalad/common/wild/pass/dwarf/arm/" + RNDARM[ran]);
   armo -> move(this_object());
   armo = clone_object(CPASS(dwarf/arm/dew_boots));
   armo -> move(this_object());
   command("wear all");
}

public int
do_say(string arg)
{
   if (!strlen(arg))
      {
      NF("Say what in the Dewar jargon?\n");
      return 0;
   }
   
   
   
   filter(all_inventory(environment(this_object())) - ({ this_object() }),
      "do_it", this_object(), arg);
   return 1;
}

public int
do_it(object who, string arg)
{
   int i;
   string text;
   string dummy;
   if (!living(who))
      return 0;
   if ((who->query_race_name() == "dwarf" && who->query_skill(SS_LANGUAGE) > 40) ||
      who->query_skill(SS_LANGUAGE) > 50)
   {
      tell_object(who, TO->query_The_name() + " growls "+
         "in the local dwarven jargon: " + arg + "\n");
      return 1;
   }
   if(who->query_skill(SS_LANGUAGE) < 20)
      {   
      tell_object(who, TO->query_The_name() + " growls "+
         "some harsh sounds. You find it utterly unconprehensable.\n");
      return 1;
   }
   
   /* remove vocals from arg according to ss_language skill */
   
   text="";
   for (i=0;i<strlen(arg);i++)
   {
      dummy=extract(arg,i,i);
      if(dummy != "a" && dummy !="e" && dummy != "i" &&
            dummy != "o" && dummy != "u" && dummy !="s" && dummy != "y")
      text=text+dummy;
      else
         {
         if (random(who->query_skill(SS_LANGUAGE)-20)>10)
            text=text+dummy;
         else
            switch(random(4))
         {
            case 0: text=text+"x"; break;
            case 1: text=text+"r"; break;
            case 2: text=text+"gh"; break;
            case 3: text=text+"z"; break;
            default: text=text+"r"; break;
         }
        }
   }
   tell_object(who, TO->query_The_name() + " growls "+
      "something in the local dwarven jargon. You manage to catch this: "+
      text+".\n");
}

do_mutter()
{
   switch (random(6))
   {
      case 1: do_say("I hate those Drows!"); break;
      case 2: do_say("I like trouble! It's fun, fun and more fun.");
      break;
      case 3: do_say("Times of trouble these days. Good times!");
      break;
      case 4: do_say("Strangers! Can we trust them?"); break;
      case 5: do_say("Kill them all I say, but nobody listens to me.");
      break;
      case 0: do_say("Those stupid deep dwarves! Good fer nothing except mining for coal!");
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

do_comb_speak()
{
   switch (random(7))
   {
      case 0: do_say("Hey, this idiot wants to fight!");
      break;
      case 1: do_say("I'll smash your face in."); break;
      case 2: do_say("We are under attack!! The drows are coming!");
      break;
      case 3: do_say("Spies! Kill'em all."); break;
      case 4: do_say("Enemies in the town! Warn the King!!");
      break;
      case 5: do_say("Bring it on scumbag, I'll turn your head into ush!");
      break;
      case 6: do_say("What are we going to do!? We need help!"); break;
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
      set_alarm(0.0,0.0,"do_kick", ob);
   }
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
         do_say("Greetings.");
         break;
         case 1:
         command("shake "+obj->query_real_name());
         break;
         case 2:
         do_say("Beware, we can "+
            "be attacked at any time! Especially you ..."); break;
         case 3:
         command("nod "+obj->query_real_name());
         break;
         case 4:
         set_alarm(0.0,0.0,"do_say","Hi! How ar'yah doing. Keep yah axe sharp!");
         break;
         case 5:
         set_alarm(0.0,0.0,"do_say","Have you come to help us"+
         "? Cause we don't need it!");
         break;
         default: break;
      }
   }
   return;
}

/* This file is to be inherited by npc's that shall react
* to the race of the arriving livings.
* Made by Korat with great help from Mercade.
*/
void
init_living()
{
   object leader;
   object dummy;
   float time;
   
   ::init_living();
   
   if (objectp(leader = this_player()->query_leader()))
      {
      if (present(leader, environment()) &&
            (CAN_SEE(this_object(),leader)) &&
         (leader != (dummy = this_player())))
      {
         return;
       }
   }
   
   if (CAN_SEE(this_object(), this_player()))
      {
      time = itof(random(4)+1);
      set_alarm(time, 0.0, "do_react", this_player());
      return;
   }
}


void
do_react(object player)
{
   object *team;
   object *team_present;
   string player_race;
   int i;
   
   if (environment(player) != environment())
      {
      return;
   }
   
   team = player->query_team_others();
   player_race = player->query_race_name();
   if (player->query_real_name() == "warrior")
      return;
   if(!sizeof(team))
      {
      if (member_array(player_race, accepted_races) > -1)
         set_alarm(0.0, 0.0, "do_react_friend_alone", player);
      else
         set_alarm(0.0, 0.0, "do_react_enemy_alone", player);
      return;
   }
   
   /* lets check the team that is here and can be seen */
   
   team_present = FILTER_CAN_SEE(team, this_object());
   
   /* return if none can be seen. */
      if(!sizeof(team_present)) return;
   
   
   if(member_array(player_race, accepted_races) > -1)
      {
      set_alarm(0.0, 0.0, "do_react_friend_alone", player);
      set_alarm(1.0, 0.0, "do_react_friend_team", player, team_present);
   }
   else
      {
      set_alarm(0.0, 0.0, "do_react_enemy_team", player, team_present);
   }
   return;
}

/* The following functions are the default functions
* that will be called when a player arrives.
* Recode them in your npc's file if you want different
   * reactions.
*/

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
      set_alarm(0.0,0.0,"do_say","Have you seen any drows around?");
      break;
      case 3:
      do_say("Stay alert, they might attack at any moment...");
      break;
      case 4:
      TO->command("emote grins at you.");
      break;
      case 5:
      do_say("I think I saw one! In that shadow ...over there.");
      TO->command("emote points towards a ruin.");
      break;
      case 6:
      TO->command("emote pokes you in your stomack.");
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
      set_alarm(0.0,0.0,"do_say","Die, enemy of my kin!");
      break;
      case 1:
      set_alarm(0.0,0.0,"do_say","The drooows are heeere!!");
      break;
      case 2:
      set_alarm(0.0,0.0,"do_say","It is a drow! It must be!! It is so ugly!!!");
      break;
      case 3:
      TO->command("spit "+player->query_real_name());
      break;
      case 4:
      TO->command("emote gets ready to kill you!");
      break;
      case 5:
      TO->command("cheer");
      break;
      case 6:
      TO->command("emote looks at you with amusement.");
      break;
      default:break;
   }
   set_alarm(0.0,0.0,"do_kick", player);
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
         do_say("You better make sure your friends behave.");
   }
   else
      {
      do_say("Make sure your friends behave.");
   }
   for (i=0;i<sizeof(enemies);i++)
   {
      if(member_array(enemies[i]->query_race_name(),accepted_races) > -1)
         {
         break;
        }
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
      do_say("I will cut you into ribbons. Both you and your friends!");
      break;
      case 6:
      TO->command("say Go away, and take your lousy lot with you!");
      break;
      default:break;
   }
   set_alarm(0.0,0.0,"do_kick",player);
}


/* kick-emote. Shall work on corpses too, and will do
* damage (small) if on living. If a hit, then combat is
   * initiated.
*/

public int
do_kick(object who)
{
   object *oblist, *oblive, *obdead;
   int result;
   object ob, *obj;
   mixed *hitresult;
   string str;
   string how;
   string what;
   string *name;
   int i;
   
   
   
   NF("But you are already preparing a kick!\n");
   if(kicking) return 0;
   NF("Dkick at whom/what?\n");
   
   /* The player kicks someone, so we will make an attempt to
   * do damage and then initiate combat.
   */
   
   set_alarm(0.0,0.0,"do_this",who);
   
   return 0;
}


void
do_this(object who)
{
   if (!F_DARE_ATTACK(TP, who))
      {
      write("You don't dare to do it!\n");
      return;
   }
   if(!member_array(who,TP->query_enemy(-1)))
      {
      do_say("I don't dare to attack! We need heeelp!!");
      return;
   }
   if (who && environment(TP) != environment(who))
      {
      do_say("Hahh! Ran away like a chicken ...");
      return;
   }
   kicking=1;
   TO->attack_object(who);
   TO->add_attack_delay(2);
   TO->add_prop(LIVE_O_SPELL_ATTACK, this_object());
   return;
}


void
tell_watcher(string str, object me, object enemy)
{
   object *ob;
   int i;
   ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
   ob -= ({ enemy });
   for (i=0;i<sizeof(ob);i++)
   if (ob[i]->query_see_blood())
      ob[i]->catch_msg(str);
}


void
spell_attack(object attacker, object target)
{
   string how;
   mixed *hitresult;
   object is_here;
   
   is_here=present(target,E(attacker));
   if(!is_here)
      {
      kicking = 0;
      attacker->catch_msg("Dissapointedly, you realise that "+QTNAME(target)+
         "has dissapeared.\n");
      return;
   }
   hitresult = target->hit_me(200, W_BLUDGEON, attacker, -1);
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
      kicking = 0;
      return;
   }
   attacker->catch_msg("You miss with the kick against "+
      QTNAME(target)+"'s chest and fall flatfaced down on the ground.\n");
   target->catch_msg(QCTNAME(attacker) +
      " tries to kick you in your chest, but misses utterly and "+
      " falls flatfaced down on the ground.\n");
   tell_watcher(QCTNAME(attacker) + " tries to kick " + QTNAME(target) +
      " in the chest, but misses utterly and falls flatfaced down "+
      " on the ground.\n", attacker, target);
   TP->add_attack_delay(2);
   kicking = 0;
   return;
}



