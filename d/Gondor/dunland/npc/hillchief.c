/* hillman */
/* Copyright (C) 1992 Henry E. Hardy */

inherit "/std/monster";
#include "/sys/ss_types.h"
#include "/sys/macros.h"

create_monster()
{
  if (!IS_CLONE) return;
  set_name(({"hillman","dunman","dunlending","chief"}));
  set_short("strong dunlending hillman");
  set_long("A muscular blue-painted hillman chief.\n");
  set_adj(({"muscular","blue-painted","hillman"}));
  set_race_name("human");
  set_alignment(random(1100)-800);
  default_config_npc(random(18)+12);
  set_stats(({random(50)+35,random(25)+30,random(50)+30,random(20),random(20),random(30)+30}));
  /* set_aggressive(random(2)); */
  set_chat_time(random(50)+5);
  add_chat("Prepare to die!");
  set_act_time(11);
  add_act(({"grin","wield sword", "laugh"}));
  /* set_hp(random(500)+300); */
  set_skill(SS_WEP_SWORD,random(40)+30);
  set_skill(SS_WEP_AXE,random(25)+25);
  set_skill(SS_WEP_KNIFE,random(40)+25);
  set_skill(SS_2H_COMBAT,random(40)+20);
  set_skill(SS_UNARM_COMBAT,random(40)+30);
  set_skill(SS_DEFENCE,random(30)+10);
  set_skill(SS_PARRY,random(30)+10);
  set_hp(random(2000)+2000);
  set_whimpy(1);
  set_pick_up(50);
  set_random_move(random(10)+10);
  seq_new("do_stuff");
  seq_addfirst("do_stuff",({"@@arm_me","grin"}));
}
arm_me() {
  seteuid(getuid(this_object()));
  clone_object("/d/Gondor/zephram/weapon/claymore") -> move(this_object());
  clone_object("/d/Gondor/zephram/armour/lchaps") -> move(this_object());
  command("wear chaps");
  clone_object("/d/Gondor/zephram/armour/nhelm") -> move(this_object());
  command("wear helm");
  clone_object("/d/Gondor/zephram/armour/stchain") -> move(this_object());
  command("wear armour");
  }

