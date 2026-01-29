inherit "/std/monster";
#include "/d/Gondor/elessar/lib/evilkill.h"

#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"

void no_notice(object player);

void
create_monster()
{
  if (!IS_CLONE)
    return;
  set_name("cook");
  set_pname(({"men","humans","haradrim","cooks"}));
  add_name("man");
  add_name("haradrim");
  add_name("southron");
  set_adj("giant");
  set_adj("dark-skinned");
  set_long(BS("This is probably the cook. He seems to feed himself rather liberally, " +
    "for he is a true giant. But he moves with a speed that is almost impossible " +
    "for a man of his size. Unlike the other Haradrim, he doesn't wear a single earring. \n"));
  set_race_name("human");
  set_alignment(-250-6*random(26));
  set_aggressive(1);
  set_attack_chance(100);
  default_config_npc(random(12)+72);
  set_base_stat(SS_STR,random(12)+98);
  set_base_stat(SS_DEX,random(12)+98);
  set_base_stat(SS_CON,random(15)+88);
  set_hp(10000);
  set_skill(SS_WEP_AXE, random(10)+70);
  set_skill(SS_WEP_KNIFE, random(10)+70);
  set_skill(SS_AWARENESS, 30 + random(5));
  set_skill(SS_2H_COMBAT, 60 + random(15));
  set_skill(SS_PARRY,85);
  set_skill(SS_DEFENCE,85);
  set_chat_time(12);
  add_chat("Stealing scum, always trying to filch an extra ration!");
  add_chat("Next one to come into this tent will die!");
  add_chat("I'm tired of waiting in this filthy camp!");
  add_chat("Why do we have to camp with the dirty orcs?");
  add_chat("We will plunder the houses of Minas Tirith soon!");
  set_cchat_time(5);
  add_cchat("Bleed to death, dirty hyena!");
  add_cact("shout Help! Intruders!");
  add_cact("shout Alarm! Enemies are in the camp!");
  add_cchat("I'll make dog chow out of you!");
  add_cchat("I'll chop yer to little pieces to feed to the orcs!");
  add_cchat("Die screaming, dog!");
}

arm_me() {
  object wep, arm;
  seteuid(getuid(TO));
  wep = clone_object("/d/Gondor/ithilien/obj/cleaver");
  wep->move(TO);
  command("wield cleaver");
  arm = clone_object(WEP_DIR + "poison_dagger");
  arm->set_doses(3);
  arm->move(TO);
  command("wield dagger");
  arm = clone_object("/d/Gondor/ithilien/obj/apron");
  arm->move(TO);
  command("wear apron");
}

/* Solemnian prestige */
query_knight_prestige() { return 120; }

init_attack()
{
  if(TP->query_npc()) return;
  if(TP->query_skill(SS_SNEAK) > TO->query_skill(SS_AWARENESS))
  {
    set_alarm(2.0, 0.0, &no_notice(TP));
    return;
  }
  if(!TO->query_attack())
  {
    command("shout I don't want any more stealing bastards in this tent!");
    set_alarm(2.0, 0.0, &aggressive_attack(TP));
  }
}

void
no_notice(object player)
{
  player->catch_msg(QCTNAME(TO) + " does not seem to notice you.\n");
  return;
}
