/* A standard member of the Shades */
inherit "/std/monster";
inherit "/std/act/action";
#include "/d/Gondor/elessar/lib/evilkill.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"

create_monster()
{
  if (!IS_CLONE)
    return;
  set_name("man");
  add_name("thief");
  add_name("assassin");
  set_race_name("human");
  set_short("dark-robed man");
  set_pshort("dark-robed men");
  set_long("The slender man is clad in grey clothes, and he is wearing\n"+
    "a black cloak over his shoulders. Grey, narrow eyes follow you\n"+
    "closely and suspiciously when you move around.\n");
  default_config_npc(37);
  set_base_stat(SS_CON,40);
  set_skill(SS_WEP_KNIFE,55);
  set_skill(SS_DEFENCE,55);
  set_skill(SS_PARRY,55);
  set_act_time(10);
  add_act("grin");
  add_act("snicker");
  add_act("chuckle");
  set_cchat_time(7);
  add_cchat("You won't beat the Shades!");
  add_cchat("Hey, stop it! What have I ever done to hurt you??");
  add_cchat("Help! I'm innocent!");
  add_cchat("I didn't do it! Nobody saw me! Can't prove anything!");
  add_cchat("Leave me alone! I'm a peaceful man!");
  seq_new("do_things");
  seq_addfirst("do_things",({"@@get_armed","grin"}));
}

get_armed() {
  object wep, arm;
  seteuid(getuid(this_object()));
  wep = clone_object("/d/Gondor/elessar/obj/wep/poisoned_dagger");
  wep->move(this_object());
  command("wield dagger");
  arm = clone_object("/d/Gondor/elessar/obj/arm/blackcloak");
  arm->move(this_object());
  command("wear cloak");
}
