/* deep dwarf guards */
/* by Korat */

inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/wild/pass/dwarf/npc/talk.h"

string *accepted_races = (({"dwarf","human","hobbit","gnome"}));

create_monster() {
   
   if (!IS_CLONE)
      return;
   
   set_name("inn-keeper");
   add_name(({"deep dwarf","keeper"}));
   set_pname("deep dwarves");
   set_short("dwarven inn-keeper");
   set_race_name("dwarf");
   set_adj("inn-keeper");
   set_alignment(300);
   set_long("Standing behind the counter, this deep dwarf will "+
      "serve you anything you wish from the menu.\n");
   set_stats(({85,35,65,30,27,100}));
   add_prop(CONT_I_WEIGHT,30000);
   add_prop(CONT_I_HEIGHT,500);
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(LIVE_I_SEE_DARK,10);
   
   
   set_skill(SS_UNARM_COMBAT, 40);
   set_skill(SS_DEFENCE, 50);
   set_skill(SS_AWARENESS, 60);
   set_skill(SS_LANGUAGE, 60);
   
   
   set_act_time(5);
   add_act("@@do_speak@@");
   add_act(({"emote fills some glasses with the strong dwarf-spirit.",
            "emote carries a tray to a table and serves some guests.",
            "emote dries a still dirty glass with his greasy apron.",
            "emote smiles broadly with his toothless grin.",
            "emote fries some fresh mushrooms. The smell fills the inn."}));
   set_cact_time(5);
   add_cact("@@do_comb_speak@@");
   add_cact(({"scream","panic","cry","cringe","gasp"}));

   set_alarm(0.0,0.0,"arm_me");
}
/* Here I equip the dewars with weapons and armours */
void
arm_me()
{
   object armo;
   seteuid(getuid(this_object()));
   armo = clone_object("/d/Kalad/common/wild/pass/dwarf/arm/jerkin");
   armo -> move(this_object());
   armo = clone_object(CPASS(dwarf/arm/dew_boots));
   armo -> move(this_object());
   command("wear all");
}

void
do_speak()
{
   switch (random(7))
   {
      case 1: do_say("I hate those Drows!"); break;
      case 2: do_say("Why? Why do they have to make trouble ...");
      break;
      case 3: do_say("Times of trouble these days. Not good, not good at all.");
      break;
      case 4: do_say("The mushrooms are reknown for their taste. Try some."); break;
      case 5: do_say("Buisness has never been as good as now in these times of trouble!");
      break;
      case 6: do_say("Careful with the spirit, stranger. It can be a mind-blower "+
         "for your weak body.");
      break;
      case 0: do_say("If only they didn't break down our defences so easily.");
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
      do_say("Welcome to my inn! Can I serve you anything?");
      break;
      case 3:
      do_say("Stay alert "+player->query_real_name()+
         ", they might attack at any moment ... so drink while you can!");
      break;
      case 4:
      TO->command("emote sighs relieved.");
      break;
      case 5:
      do_say("Life will seem brighter as soon as you get one of "+
         "my spirits into your stomack.");
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
   TO->command("emote goes hmmm.");
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
         C(friend->query_real_name())+". I don't want any "+
         "brawling in my bar!");
   }
   else
      {
      do_say("Make sure your friends behave, "+
         C(friend->query_real_name())+". I don't want any brawling in my bar!");
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
         do_say("Never seen such a lot in this place in decades!");
         break;
         case 5:
         TO->command("emote polishes his counter.");
         break;
         case 6:
         TO->command("emote grips his hand around a bottle in warning.");
         break;
         default:break;
      }
   }
}

void
do_react_enemy_team(object player, object *team)
{
   TO->command("emote goes hmmm and watches you scrutinizingly.");
}
