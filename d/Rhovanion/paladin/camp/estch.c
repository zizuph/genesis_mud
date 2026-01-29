 
 
inherit "/std/monster";
 
#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <stdproperties.h>
#include <wa_types.h>
 
#include "campdef.h"
#include </d/Rhovanion/defs.h>
#include "/d/Rhovanion/lib/kill_log.h"
#include <filter_funs.h>
 
void
create_monster()
{
  object ob;
 
  set_race_name("human");
  set_adj("mean");
  set_adj("chief");
  set_short("mean chief barbarian");
  set_name("chief");
 
  set_alignment(-2000);
  set_gender(G_MALE);
  set_long("It is a mean chief barbarian.\nHe looks VERY powerful ! "+
     "He must be an exceptional fighter !\n"+
     "Maybe it would be better if you ran away before he "+
     "attacks you!?!\n");
 
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
  set_skill(SS_AWARENESS, 100);
 
  set_act_time(3);
  add_act("grin");
  add_act("kick all sad");
  add_act("ponder");
  add_act("say Get lost !");
  add_act("curse");
 
  set_cact_time(1);
  add_cact("grin");
  add_cact("wield obsidian axe");
  add_cact("kick all sad");
  add_cact("ponder");
  add_cact("say Get lost !");
  add_cact("curse");
 
  trig_new("%w 'spits' %s","react_spit");
  trig_new("'You' 'aim' %s","react_axe");
 
  set_alarm(1.0,60.0,"do_shield");
 
}
 
void do_shield()
{
  TO->add_mana(100);
  command("cast protection");
}
 
arming ()
{
   object leggings,wep,shield,helmet,mail;
 
   wep = clone_object(PALWEAPON+"obsaxe");
   wep->move(this_object());
   command("wield axe");
   shield = clone_object(PALARMOUR+"obsshield");
   shield->move(this_object());
   command("wear shield");
   helmet = clone_object(PALARMOUR+"obshelmet");
   helmet->move(this_object());
   command("wear helmet");
   mail = clone_object(PALARMOUR+"obsmail");
   mail->move(this_object());
   command("wear platemail");
   leggings = clone_object(PALARMOUR+"obsleggings");
   leggings->move(this_object());
   command("wear leggings");
 
 
 
 
}
 
void
attacked_by(object enemy)
{
  command("say Stupid "+lower_case(enemy->query_nonmet_name())+"!"+
    " I will kill you for this, slowly and painfully!");
 
}
 
void
do_die(object killer)
{
  command("gasp");
  command("puke "+lower_case(killer->query_real_name()));
  command("say You killed me!");
  command("point "+lower_case(killer->query_real_name()));
  command("say But my master will gain vengeance upon you!");
  ::do_die(killer);
 
}
 
int special_attack(object enemy)
{
  mixed *hitloc;
  int dam,ac,dex_st;
  object wielded;
 
  if (random(5)!=3)
      return 0;
  wielded=TO->query_weapon(W_RIGHT);
  if (wielded&&(wielded->query_wt()==W_AXE))
  {
    dex_st=enemy->query_stat(SS_DEX);
    tell_watcher(QCTNAME(this_object()) +
    " makes a wonderful blow and smashes the head of "+
    QTNAME(enemy)+" with his axe !\n",TO,enemy);
    enemy->catch_msg(QCTNAME(this_object())+" makes a wonderful blow "+
          "on you and smashes your head with his axe !\n");
    dam=random(600)-random(5)*dex_st;
    if (dam<0) dam=0;
    enemy->set_hp(enemy->query_hp()-dam);
    return 1;
  }
}
 
void react_axe(string acc,string caa)
{
  command("get obsidian axe");
  command("wield obsidian axe");
}
 
void react_spit(string who,string stt)
{
  command("spit "+who);
}
