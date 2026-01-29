/* The dealer to whom the herb should be delivered in Minas Tirith */
#include "/d/Gondor/elessar/lib/evilkill.h"
inherit "/std/monster";
inherit "/std/act/action";
#include "/sys/ss_types.h"
#include "/sys/macros.h"
object carrier;

create_monster()
{
  if (!IS_CLONE)
    return;
  set_name(({"thief","fellow","man","guard"}));
  set_race_name("human");
  set_short("sneaky fellow");
  set_adj(({"dirty","sneaky"}));
  set_long("This fellow looks a little suspicious. Maybe you should watch your\n"+
    "pockets while he is around..\n");
  default_config_npc(37);
  set_base_stat(SS_CON,40);
  set_skill(SS_WEP_KNIFE,55);
  set_skill(SS_DEFENCE,55);
  set_skill(SS_PARRY,55);
  set_chat_time(10);
  add_chat("Business is bad here in Minas Tirith now because of all the guards.");
  add_chat("Don't hang around too long, ok?");
  add_chat("Power will be with the Shades!");
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
  wep = clone_object("/d/Gondor/elessar/obj/wep/dagger");
  wep->move(this_object());
  command("wield dagger");
}
