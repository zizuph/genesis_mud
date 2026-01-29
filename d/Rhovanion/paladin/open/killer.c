 
 
inherit "/std/monster";
 
#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <stdproperties.h>
#include <wa_types.h>
 
void
create_monster()
{
  object ob;
 
  set_race_name("killer");
  set_adj("black");
  set_adj("deadly");
  set_short("black killer");
 
  set_alignment(-800);
  set_gender(0);
  set_long("This deadly black killer seems to be able to kill"
     +" everyone, who will attack him!\n");
 
  add_prop(CONT_I_WEIGHT, 72*1000);
  add_prop(CONT_I_VOLUME, 74*1000);
  add_prop(CONT_I_HEIGHT, 174);
  set_stats(({205, 205, 205, 205, 205, 205}));
  set_hp(query_max_hp());
 
 
  set_skill(SS_UNARM_COMBAT, 100);
  set_skill(SS_DEFENCE, 100);
  set_skill(SS_PARRY, 100);
  set_skill(SS_WEP_AXE, 100);
 
  set_act_time(5);
  add_act("grin");
  add_act("smile sadis");
  add_act("laugh");
  add_act("say I will kill you slow and painful!");
  add_act("say Shadows will rule all over the world!");
  add_act("spit");
  add_act("spit all");
 
  seq_new("starting");
  seq_addfirst("starting",({"@@arming","say Don't touch me!"}));
}
 
arming ()
{
   object wep,shield,helmet,mail;
 
   wep = clone_object("/d/Rhovanion/paladin/obsaxe");
   wep->move(this_object());
   command("wield axe");
   shield = clone_object("/d/Rhovanion/paladin/obsshield");
   shield->move(this_object());
   command("wear shield");
   helmet = clone_object("/d/Rhovanion/paladin/obshelmet");
   helmet->move(this_object());
   command("wear helmet");
   mail = clone_object("/d/Rhovanion/paladin/obsmail");
   mail->move(this_object());
   command("wear mail");
 
 
 
 
}
 
void
attacked_by(object enemy)
{
  command("say Stupid "+enemy->query_real_name()+"!! You have no "+
    "chanses to kill me !!!");
 
}
 
void
do_die(object killer)
{
  command("sigh");
  command("say You killed me!");
  command("point "+lower_case(killer->query_real_name()));
  ::do_die(killer);
 
}
 
int special_attack(object enemy)
{
  static int attack_time;
  mixed *hitloc;
  int ac,dex_st;
 
  if (attack_time>0)
    {
      attack_time--;
      return 0;
    }
/*   hitloc=enemy->query_combat_object->guery_hitloc(A_BODY); */
/*   ac=hitloc */
/*   dex_st=enemy->query_stat(SS_DEX); */
  attack_time=10;
 
  return 1 ;
}
 
