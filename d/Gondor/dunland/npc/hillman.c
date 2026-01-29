/* hillman */
/* Copyright (C) 1992 Henry E. Hardy */

inherit "/std/monster";
#include "/sys/ss_types.h"
#include "/sys/macros.h"

create_monster()
{
  if (!IS_CLONE) return;
  set_name(({"hillman","dunman","dunlending","warrior"}));
  set_short("average dunlending hillman");
  set_long("A stocky blue-painted hillman warrior.\n");
  set_adj(({"stocky","blue-painted","hillman"}));
  set_race_name("human");
  set_alignment(random(1100)-800);
  default_config_npc(random(8)+2);
  set_stats(({random(30)+10,random(25)+10,random(35)+10,random(20),random(20),random(30)+5}));
  /* set_aggressive(random(2)); */
  set_chat_time(random(50)+5);
  add_chat("Prepare to die!");
  set_act_time(11);
  add_act(({"grin","wield sword", "laugh"}));
  set_skill(SS_WEP_SWORD,random(35)+20);
  set_skill(SS_WEP_KNIFE,random(40)+10);
  set_skill(SS_2H_COMBAT,random(40)+10);
  set_skill(SS_UNARM_COMBAT,random(40)+20);
  set_skill(SS_DEFENCE,random(10)+5);
  set_skill(SS_PARRY,random(10)+5);
  set_hp(random(1200)+800);
  set_whimpy(1);
  set_pick_up(50);
  set_random_move(random(10)+10);
  seq_new("do_stuff");
  seq_addfirst("do_stuff",({"@@arm_me","grin"}));
}
arm_me() {
  seteuid(getuid(this_object()));
  clone_object("/d/Gondor/zephram/weapon/dirk") -> move(this_object());
  command("wield knife");
  clone_object("/d/Gondor/zephram/armour/cubplate") -> move(this_object());
  command("wear armour");
  }

