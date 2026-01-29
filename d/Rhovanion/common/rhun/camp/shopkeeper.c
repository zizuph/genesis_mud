 
 
inherit "/std/monster";
 
#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <stdproperties.h>
#include <wa_types.h>
 
#include "campdef.h"
#include "/d/Rhovanion/lib/kill_log.h"
#include </d/Rhovanion/defs.h>
 
#include <filter_funs.h>
void
create_monster()
{
  object ob;
 
  set_race_name("human");
  set_adj("mean");
  set_adj("strong");
  set_short("mean strong shopkeeper");
  set_name("barbarian");
 
  set_alignment(-700);
  set_gender(G_MALE);
  set_long("It is mean strong shopkeeper.\nHe seems to be glad"
     +" to trade with anyone !\n");
 
  add_prop(CONT_I_WEIGHT, 72*1000);
  add_prop(CONT_I_VOLUME, 74*1000);
  add_prop(CONT_I_HEIGHT, 174);
  add_prop(LIVE_I_SEE_DARK, 10);
  set_stats(({205, 205, 205, 205, 205, 205}));
  set_hp(query_max_hp());
 
 
  set_skill(SS_DEFENCE, 100);
  set_skill(SS_BLIND_COMBAT, 100);
  set_skill(SS_PARRY, 100);
  set_skill(SS_WEP_AXE, 100);
 
  set_act_time(3);
  add_act("grin");
  add_act("poke all");
  add_act("ponder");
  add_act("say Want to buy something ?");
  add_act("smile");
 
  set_cact_time(1);
  add_cact("grin");
  add_cact("kick all sad");
  add_cact("ponder");
  add_cact("say Get lost !");
  add_cact("curse");
 
 
  seq_new("starting");
 seq_addfirst("starting",({"@@arming","say When will we "+
              "kill rohirrims ?"}));
}
 
arming ()
{
   object leggings,wep,shield,helmet,mail;
 
   wep = clone_object(PALWEAPON+"staxe");
   wep->move(this_object());
   command("wield axe");
   shield = clone_object(PALARMOUR+"stshield");
   shield->move(this_object());
   command("wear shield");
   helmet = clone_object(PALARMOUR+"sthelmet");
   helmet->move(this_object());
   command("wear helmet");
   mail = clone_object(PALARMOUR+"stmail");
   mail->move(this_object());
   command("wear mail");
   leggings = clone_object(PALARMOUR+"stleggings");
   leggings->move(this_object());
   command("wear leggings");
 
 
 
 
}
 
void
attacked_by(object enemy)
{
  command("say Stupid "+lower_case(enemy->query_nonmet_name())+"!"+
    " I will kill you for it slow and painful!");
 
}
 
void
do_die(object killer)
{
  command("gasp");
  command("curse");
  command("say You killed me!");
  command("point "+lower_case(killer->query_real_name()));
  ::do_die(killer);
 
}
 
int attack_time;
int special_attack(object enemy)
{
  mixed *hitloc;
  int dam,ac,dex_st;
  object wielded;
 
  if (attack_time>0)
    {
      attack_time--;
      return 0;
    }
  wielded=TO->query_weapon(W_RIGHT);
  if (wielded&&(wielded->query_wt()==W_AXE))
  {
    dex_st=enemy->query_stat(SS_DEX);
    attack_time=5;
    tell_watcher(QCTNAME(this_object()) +
    " makes the wonderful blow and smashes the head of "+
    QTNAME(enemy)+" with his axe !\n",TO,enemy);
    enemy->catch_msg(QCTNAME(this_object())+" makes the wonderful blow "+
          "on you and smashes your head with his axe !\n");
    dam=random(600)-random(5)*dex_st;
    if (dam<0) dam=0;
    enemy->set_hp(enemy->query_hp()-dam);
    return 1;
  }
}
 
 
