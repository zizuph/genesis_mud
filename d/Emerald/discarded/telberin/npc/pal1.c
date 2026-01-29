inherit "/std/monster";
inherit "/d/Emerald/telberin/npc/aid_npc";

#include <stdproperties.h>
#include <ss_types.h>
#include "default.h"

#define TO  this_object()
#define TP  this_player()

void arm_me();

void
create_monster()
{
   set_name("paladin");
   add_adj("tall");
   add_adj("haughty");
   add_adj("effeminate");
   set_race_name("elf");
   set_short("paladin");
   set_long("This powerful warrior is dedicated to the elven Gods to " +
      "protect the inhabitants of Telberin. He is well-built and " +
      "looks very confident with his sword.\n");
   
   set_stats(({ 101, 155, 146, 114, 112, 150 })); 
   
   set_skill(SS_WEP_SWORD, 90);
   set_skill(SS_2H_COMBAT, 80);
   set_skill(SS_WEP_KNIFE, 77);
   set_skill(SS_DEFENCE, 54);
   set_skill(SS_PARRY, 80);
   set_skill(SS_AWARENESS, 60);
   set_alignment(900);
   
   refresh_mobile();
   
   set_all_hitloc_unarmed(5); /* Inherent AC of 5 */
   
   set_give_aid(1);
   
   add_prop(NPC_I_NO_RUN_AWAY, 1);
   
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
   
   set_alarm(1.0, 0.0, arm_me);
}

/*
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
*/

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
   map(({ WEP_DIR + "e_longs", WEP_DIR + "dirk",
            ARM_DIR + "sil_gre", ARM_DIR + "sil_bra",
            ARM_DIR + "w_plate", ARM_DIR + "w_hel" }), 
      clone_object)->move(this_object(), 1);
   
   command("wield sword");
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
