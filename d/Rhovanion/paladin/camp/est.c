 
 
inherit "/std/monster";
 
#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <filter_funs.h>
 
#include "campdef.h"
#include </d/Rhovanion/defs.h>
#include "/d/Rhovanion/lib/kill_log.h"
 
 
#define FDES ({"dark","black","dangerous","strong"})
#define SDES ({"evil","stupid","fat","expirienced"})
 
void
create_monster()
{
  object ob;
  int ss,sd,sc,si,sw,sds;
  string fdes,sdes;
 
  set_race_name("human");
  fdes=ONE_OF_LIST(FDES);
  sdes=ONE_OF_LIST(SDES);
  set_adj(sdes);
  set_adj(fdes);
  set_short(fdes+" "+sdes+" barbarian");
  set_name("barbarian");
 
  ss=80+random(70);
  sd=80+random(70);
  sc=80+random(70);
  si=80+random(70);
  sw=80+random(70);
  sds=80+random(70);
 
  set_alignment(-(ss+sd+sc+si+sw+sds));
  set_gender(G_MALE);
  set_long("This barbarian seems to be an easterling.\n"+
           "Easterlings came from far east to join Sauron's army.\n"+
           "They have made a LONG way and now they are "+
           "enjoying some rest before they go to Minas Morgul.\n");
 
  add_prop(CONT_I_WEIGHT, 72*1000);
  add_prop(CONT_I_VOLUME, 74*1000);
  add_prop(CONT_I_HEIGHT, 174);
  add_prop(LIVE_I_SEE_DARK, 6);
  set_stats(({ss, sd, sc, si, sw, sds}));
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
  add_act("say Get lost!");
  add_act("curse");
 
  set_cact_time(1);
  add_cact("grin");
  add_cact("kick all sad");
  add_cact("ponder");
  add_cact("say Get lost!");
  add_cact("curse");
 
  set_alarm(1.0,10.0,"tryattack");
}
 
object wep;
 
arming ()
{
   object shield,helmet,mail,leggings;
 
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
   command("wear platemail");
   leggings = clone_object(PALARMOUR+"stleggings");
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
  command("fart "+lower_case(killer->query_nonmet_name()));
  command("say You killed me!");
  command("point "+lower_case(killer->query_nonmet_name()));
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
    dam=random(400)-(random(900)*dex_st)/100;
    if (dam<0) dam=0;
    enemy->set_hp(enemy->query_hp()-dam);
    return 1;
  }
}
 
void tryattack()
{
  object *list;
  int i,r;
 
  if (TO->query_enemy()) return;
  list=FILTER_LIVE(all_inventory(environment(TO)))-({TO});
  for(i=0;i<sizeof(list);i++)
    if ((list[i]->query_name()!="Barbarian")&&
         (list[i]->query_name()!="Chief")&&
         (list[i]->query_invis()==0))
      {
        command("kill "+lower_case(list[i]->query_name()));
        return;
      }
}
 
