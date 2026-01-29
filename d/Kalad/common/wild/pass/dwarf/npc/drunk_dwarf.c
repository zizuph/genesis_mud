/* deep dwarf guards */
/* by Korat */

inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/sys/macros.h"
#include "/sys/filter_funs.h"
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/wild/pass/dwarf/npc/talk.h"

string *accepted_races = (({"dwarf","human","hobbit","gnome"}));

create_monster() {
   int ran;
   
   if (!IS_CLONE)
      return;
   
   set_name("drunk");
   add_name(({"deep dwarf","drunk dwarf"}));
   set_pname("deep dwarves");
   set_short("drunk deep dwarf");
   set_race_name("dwarf");
   set_adj("drunk");
   set_alignment(300);
   set_long("A miserable and dirty, drunk deep dwarf that "+
      "must have lived a hard life to sink this deep. "+
      "Several scars decorate his wrinkled face along with "+
      "a pink tone to his dark skin. Months, maybe years, "+
      "of lingering in the dwarven spirits world has made its "+
      "mark on him.\n");
   set_stats(({85,35,55,30,27,100}));
   add_prop(CONT_I_WEIGHT,30000);
   add_prop(CONT_I_HEIGHT,500);
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(LIVE_I_SEE_DARK,10);
   
   
   set_skill(SS_UNARM_COMBAT, 40);
   set_skill(SS_DEFENCE, 50);
   set_skill(SS_AWARENESS, 10);
   set_skill(SS_LANGUAGE, 60);
   
   
   set_act_time(5);
   add_act("@@do_mutter@@");
   add_act(({"peer nervously",
            "emote looks around carefully.","emote strokes his beard.",
            "emote burps loudly.","emote sings a sad song in "+
            "a deep and rusty voice."}));
   set_cact_time(5);
   add_cact("@@do_comb_speak@@");
   add_cact(({"scream","panic","cry","cringe","gasp"}));
}

/* Here I equip the dewars with weapons and armours */
void
arm_me()
{
   object armo;
   seteuid(getuid(this_object()));
   armo = clone_object("/d/Kalad/common/wild/pass/dwarf/arm/jerkin");
   armo -> move(this_object());
   armo = clone_object(CPASS(dwarf/arm/boots));
   armo -> move(this_object());
   command("wear all");
}

void
do_mutter()
{
   switch (random(7))
   {
      case 1: do_say("I hate those Drows!"); break;
      case 2: do_say("Why? Why do they have to make trouble ...");
      break;
      case 3: do_say("Times of trouble these days. Not good, not good at all.");
      break;
      case 4: do_say("I once fought them drows hard. I spread fear in their dark "+
         "hearts! THEN I was a MAN! But now ... "); break;
      case 5: do_say("Maybe if we started to believe that old priests tales of "+
         "Gods and magic ... but I'm not that gullible! Magic ... "+
         "more help in mining for coal!\n");
      break;
      case 6: do_say("Keep away from that graveyard! Creepy undead stuff lives "+
         "there ... Iv'e seen it myself! I saw something shine so "+
         "very very brightly inside a crypt ... no I can't talk "+
         "about it. That night I came here, and I have never left!\n");
      break;
      case 0: do_say("If only they didn't break down our defences so easily.");
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
         do_say("Do you not hear it? "+
             "The trumpets of war have already begun to bellow!"); break;
         case 3:
         command("nod "+obj->query_real_name());
         break;
         case 4:
         do_say("Hi! How ar'yah doing. Keep yah axe sharp!");
         break;
         case 5:
         do_say("Stay with us friend, "+
             "and join us in honorable death!");
         break;
         default: break;
      }
   }
   return;
}

/* The following functions are the default functions
* that will be called when a player arrives.
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
      TO->command("ask "+player->query_real_name()+" Have you seen any drows around?");
      break;
      case 3:
      do_say("Watch the shadows"+
         ", they might attack at any moment...");
      break;
      case 4:
      TO->command("emote sighs relieved.");
      break;
      case 5:
      TO->command("emote lifts his glass of spirit and toasts you.");
      break;
      case 6:
      TO->command("hug "+player->query_real_name());
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
   TO->attack_object(player);
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
         TO->command("emote flexes his muscles.");
         break;
         case 6:
         TO->command("emtoe tries to rest his hand on the hilt of his weapon in warning, "+
            "but suddenly realises he's sold it months ago.");
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
      TO->command("emote swings his fists towards you!");
      break;
      case 5:
      do_say("I will cut you into ribbons. Both you and your friends, "+
         C(player->query_real_name())+"!");
      break;
      case 6:
      TO->command("emote looks for a place to hide, but finds none!");
      break;
      default:break;
   }
}
