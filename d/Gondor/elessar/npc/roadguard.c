inherit "/std/monster";
#include "/d/Gondor/elessar/lib/goodkill.h"

#include "/sys/ss_types.h"
#include "/sys/macros.h"

create_monster()
{
  if (!IS_CLONE)
    return;
  set_name(({"guard","road warden","warden"}));
  set_race_name("human");
  set_short("tall road-warden");
  set_adj(({"tall","rohirrim"}));
  set_long("This is one of the road-wardens of Rohan, patrolling the\n"+
    "road keeping order and looking for crooks and thieves.\n"+
    "He looks quite competent in fighting, as all guards get training with\n"+
    "the garrison once a week.\n");
  set_pshort("tall road-wardens");
  default_config_npc(random(10)+35);
  set_base_stat(SS_CON,random(10)+45);
  set_hp(3500+random(5)*100);
  set_skill(SS_WEP_SWORD, random(10)+65);
  set_skill(SS_DEFENCE,80);
  set_skill(SS_PARRY,80);
  seq_new("do_things");
  seq_addfirst("do_things",({"@@get_armed","say Reporting for patrol-duty!"}));
}

get_armed() {
  object wep, arm;
  seteuid(getuid(this_object()));
  wep = clone_object("/d/Gondor/elessar/obj/wep/rosword");
  wep->move(this_object());
  command("wield sword");
  arm = clone_object("/d/Gondor/elessar/obj/arm/roshield");
  arm->move(this_object());
  command("wear shield");
  arm = clone_object("/d/Gondor/elessar/obj/arm/rohelm");
  arm->move(this_object());
  command("wear helm");
}

init_living()
{
  if (present("cockroach",environment(this_object()))) command("kill cockroach");
  ::init_living();
}

