/* The sculptor for the museum
 *  Cirion 040296
 */
#include "museum.h"
inherit "/std/monster";

void create_monster()
{
  set_name("hamblinaski");
  set_adj("energetic");
  set_race_name("gnome");
  add_name("sculptor");
  set_title("the Master Sculptor of Sybarus");

  set_stats(({85,55,18,43,26,19}));
  add_prop(NPC_I_NO_RUN_AWAY, 1);
  set_gender(G_MALE);
  set_appearance(35);

  set_skill(SS_LANGUAGE,      30);
  set_skill(SS_WEP_KNIFE,     19);
  set_skill(SS_ACROBAT,       20);
  set_skill(SS_AWARENESS,     45);
  set_skill(SS_DEFENCE,       10);
  set_skill(SS_UNARM_COMBAT,  24);
  set_skill(SS_SWIM,          10);
  set_skill(SS_CLIMB,         21);
  set_skill(SS_LOC_SENSE,     10);
  set_skill(SS_HERBALISM,     21);

  set_alignment(-16);

  set_act_time(15);
    add_act("emote pokes idly at a block of stone "
           +"with his chisel.");
    add_act("hmm");
    add_act("say Ever think of a modelling career?");
    add_act("say I can make statues for a price...");

 set_cact_time(3);
    add_cact("scream");
    add_cact("panic");
    add_cact("cringe");
    add_cact("cry");

 add_ask(({"statue","statues","about statues","about statue"}),
          VBFC_ME("about_statues"));

 set_all_hitloc_unarmed(30);
}

void arm_me()
{
  object chisel;
  
  SGT;
  chisel = clone_object("/std/weapon");
   chisel->set_name("chisel");
   chisel->set_short("long chisel");
   chisel->set_adj("long");
   chisel->set_default_weapon(4, 9, W_KNIFE, W_IMPALE, W_LEFT);
   chisel->update_prop_settings();
   chisel->move(TO);

  command("wield all");
}

string about_statues()
{
  set_alarm(0.5, 0.0, &command("say I can make statues of "
        +"you, for a price of "
        +LANG_WNUM(STAT_COST / 1728)+" platinum coins."));
  set_alarm(1.5, 0.0, &command("say If you want one made, "
        +"you can simply pay me, and I will begin work "
        +"on the statue."));
  set_alarm(2.5, 0.0, &command("say Be sure you dress "
        +"up the way you want to look in the statue, "
        +"because once I have completed one, I can't "
        +"change it!"));
  return "";
}

void init_living()
{
  ::init_living();

  if(!interactive(TP) || TP->query_met(query_name()))
   return;

  if(!sizeof(get_all_alarms()))
   set_alarm(2.0, 0.0, &command("introduce myself"));
}

string race_sound()
{
  return "babbles";
}
