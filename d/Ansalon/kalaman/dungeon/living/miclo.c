/*
 * Dungeon Prisoner Miclo
 *
 * Actually based upon the character Miclo
 *
 * 2011 Lunatari
 */
#include "local.h"

inherit AM_FILE

#define MICLO_SHORT "pale red-eyed human"
#define SHIRT DOBJ + "rags_shirt"
#define PANTS DOBJ + "rags_pants"

object trust_ob;

string 
query_hero_desc()
{
  return "He has scars on his left leg, right leg, nose, left arm, right arm, left " +
  "hand, right hand, forehead, left cheek and right cheek.\n" +
  "He has a refined aura.\n" +
  "He has intense ember red eyes.\n" +
  "He has short metallic blue nails.\n" +
  "His hair is shoulder length, dark brown and tied back.\n" +
  "He has pale skin.\n" +
  "He has a pierced tongue and lip with no rings in them.\n";
}

string
query_hero_title()
{
  return "the Traveller of Legend, " +
    "Disgraced Monk of the Dragon Order " +
    "and Notorius Outlaw of Kalaman";
}

void chain_me();

/* VOID CREATE MICLO :) */
void 
create_krynn_monster()
{
  set_name("miclo");
  add_name("human");
  set_living_name("miclo");
  set_title(query_hero_title());
  set_race_name("human");
  set_gender(G_MALE);
  set_adj(({"pale","red-eyed"}));
  set_short(MICLO_SHORT);
  set_long("He is a " + short() + ".\n" + query_hero_desc());
  set_stats(({179, 165, 170, 141, 141, 140}));

  set_hp(query_max_hp());

  set_alignment(-1200);
  set_knight_prestige(10);
  set_introduce(1);

  set_skill(SS_WEP_POLEARM, 75);
  set_skill(SS_UNARM_COMBAT, 100);
  set_skill(SS_BLIND_COMBAT, 75);
  set_skill(SS_DEFENCE, 100);
  set_skill(SS_PARRY, 50);
  set_skill(SS_AWARENESS, 75);
                        
  add_prop(CONT_I_WEIGHT, 50000);
  add_prop(CONT_I_HEIGHT, 180);

  set_act_time(40);
  add_act("moan");
  add_act("sigh deeply");
  add_act("smirk");
  add_act("say Lord Calof should just be slain over and over again.");

  set_default_answer("I do not know, I really do not know!\n");
  add_ask(({ "miclo", "angpaur"}), 
    "say Yes I remember those names, why do you ask?\n");

  seteuid(getuid());

  equip(({ SHIRT, PANTS }));

  set_alarm(2.0, 0.0, &chain_me());
}

void
unchain_me(object player)
{
  if (ENV(TO)->query_chains())
  {
     ENV(TO)->remove_prisoner();
     command("say Thank you " + QNAME(player) + ", now I will " +
       "leave you here, hope you get out alive!");
     command("west");
     command("shout Guards! Guards! Intruders!");
     TO->remove_object();
  }
}

void
chain_me()
{
  if (!ENV(TO)->query_chains())
  {
     ENV(TO)->add_prisoner(TO);
  }
}
