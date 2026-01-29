inherit "/std/monster";
inherit "/d/Emerald/telberin/npc/aid_npc";

#include <const.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <default.h>

#define TO  this_object()
#define TP  this_player()

void return_bow(string who);
void return_smile(string who);
void return_shake(string who);
void arm_me();

void
create_monster()
{
   set_name("paladin");
   set_race_name("elf");
   set_short("paladin");
   set_long("This powerful warrior is dedicated to the elven Gods to " +
      "protect the inhabitants of Telberin. He is well-built and " +
      "looks very confident with his sword.\n");

   set_base_stat(SS_STR, 101);
   set_base_stat(SS_DEX, 155);
   set_base_stat(SS_CON, 146);
   set_base_stat(SS_INT, 114);
   set_base_stat(SS_WIS, 112);
   set_base_stat(SS_DIS, 106);
   
   set_skill(SS_WEP_SWORD, 75);
   set_skill(SS_2H_COMBAT, 80);
   set_skill(SS_WEP_KNIFE, 77);
   set_skill(SS_DEFENCE, 54);
   set_skill(SS_PARRY, 55);
   set_alignment(650);
   
   set_hp(3000);
   
   set_all_hitloc_unarmed(5); /* Inherent AC of 5 */

   set_give_aid(1);
   
   add_prop(CONT_I_WEIGHT, 71000);
   add_prop(CONT_I_MAX_WEIGHT, 180000);
   add_prop(OBJ_I_VOLUME, 71000);
   add_prop(LIVE_O_ENEMY_CLING, 1);
   add_prop(CONT_I_MAX_VOLUME, 100000);
   
   set_chat_time(15);                             /* Set speaking interval */
   add_chat("Hmmm. Things art quiet around here.");
   add_chat("Greetings stranger! How art thou?");
   
   
   set_cchat_time(8);                      /* Set combat speaking interval */
   add_cchat("Thou art making a mistake my friend.");
   add_cchat("I think that thee ought to reconsider thy actions.");
   
   
   set_act_time(15);                    /* Set action interval           */
   add_act("bat");
   add_act("wink");
   add_act("ponder");
   add_act("smile");
   add_act("hmm");
   
   trig_new("%w 'smiles' %s", "react_smile");
   trig_new("%w 'introduces' %s", "react_introduce");
   trig_new("%w 'shakes' %w 'head' %s", "react_shake");
   trig_new("%w 'bows' %s", "react_bow");
   
   set_alarm(1.0, 0.0, arm_me);
}

int
react_bow(string who, string dummy) {
   if(who) {
      who = lower_case(who);
      set_alarm(2.0, 0.0, &return_bow(who));
      return 1;
   }
}

void
return_bow(string who) {
   object obj;
   int ran;
   
   if(obj = present(who, environment())) {
      ran = random(3);
      if(ran == 0)
         command("say Greetings.");
      if(ran == 1)
         command("bow to " + who);
      if(ran == 2)
         command("say Nice to meet you, "+
         obj->query_nonmet_name() +".");
   }
}

int
react_smile(string who, string dummy) {
   if (who) {
      who = lower_case(who);
      set_alarm(2.0, 0.0, &react_smile(who));
      return 1;
   }
}

void
return_smile(string who) {
   object obj;
   int ran;
   
   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         command("say Nice to see that you are happy, " +
         obj->query_nonmet_name() + "?");
      if (ran == 1)
         command("shake " + who);
      if (ran == 2)
         command("say It's a lovely day today, " + obj->query_nonmet_name()
         + "?");
   }
}

int
react_introduce(string who, string dummy) {
   if (who) {
      who = lower_case(who);
      return 1;
   }
}

void
return_introduce(string who) {
   object obj;
   int ran;
   
   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         {
         command("say Nice to meet you, " + obj->query_name() + ".");
         command("bow to " + who);
       }
      if (ran == 1)
         {
         command("bow to " + who);
       }
      if (ran == 2)
         {
         command("say How are you, " + obj->query_race() + "?");
         command("bow to " + who);
       }
   }
}

int
react_shake(string who, string dummy1, string dummy2) {
   if (who) {
      who = lower_case(who);
      set_alarm(2.0, 0.0, &return_shake(who));
      return 1;
   }
}

string
fix_name(object player)
{
   switch(player->query_race())
   {
      case "elf":
      return "elves";
      break;
      case "dwarf":
      return "dwarves";
      break;
      case "human":
      return "humans";
      break;
      case "gnome":
      return "gnomes";
      break;
      case "hobbit":
      return "hobbits";
      break;
      case "goblin":
      return "goblins";
      break;
      default:
      return "some";
      break;
   }
}

void
return_shake(string who) {
   object obj;
   string str;
   int ran;
   
   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         command("say Really, " + obj->query_race() + "?");
      if (ran == 1)
         command("say I agree with you, "
         + ((obj->query_gender() == G_MALE) ? "master" : "lady") + ".");
      if (ran == 2)
         str = fix_name(obj);
      command("say Why " + str + " always disagree?");
   }
}

int
special_attack(object ob)
{ 
   if (!random(20) && (query_hp() < query_max_hp() / 2))
   { 
      tell_room(environment(), "The Paladin raises his sweet voice "+
         "in holy chants, and seems refreshed and vital again.\n", this_object());
      heal_hp(200 + random(100));
      return 1;     
   }
   
   return 0;
}

void
arm_me()
{
   object *eq = map(({ WEP_DIR + "e_longs", WEP_DIR + "dirk",
            ARM_DIR + "sil_gre", ARM_DIR + "sil_bra",
            ARM_DIR + "w_plate", ARM_DIR + "w_hel" }), clone_object);
   eq->move(this_object(), 1);
   
   command("wield all");
   command("wear all");
}

void attacked_by(object enemy)
{
   ::attacked_by(enemy);
   get_assistance(enemy);
}

void assist()
{
   command("shout How dare you bring harm to this city!?");
   tell_room(environment(), "The Paladin gives holy assistance "+
      "unto his comrade.\n", this_object());
}
