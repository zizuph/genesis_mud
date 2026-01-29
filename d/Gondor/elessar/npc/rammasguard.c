inherit "/std/monster";
#include "/d/Gondor/elessar/lib/goodkill.h"

#include "/sys/ss_types.h"
#include "/sys/macros.h"

create_monster()
{
  if (!IS_CLONE)
    return;
  set_name("guard of the gate");
  add_name("guard");
  add_name("soldier");
  set_race_name("human");
  set_short("guard on duty");
  set_adj(({"tall","strong"}));
  set_long("This is one of the guards of the Wall, watching the people approaching\n"+
    "the wall and gate, and guarding it with his life if necessary.\n"+
    "He looks quite competent in fighting, as all guards get training with\n"+
    "the garrison once a week.\n");
  set_pshort("guards on duty");
  default_config_npc(random(10)+45);
  set_base_stat(SS_CON,random(10)+55);
  set_hp(4000+random(5)*100);
  set_skill(SS_WEP_SWORD, random(10)+70);
  set_skill(SS_PARRY,85);
  set_skill(SS_DEFENCE,85);
  set_skill(SS_AWARENESS,70);
  set_chat_time(20);
  add_chat("Looks like the War is drawing nigh.");
  add_chat("What are you hanging around here for?");
  add_chat("Minas Tirith is a well-guarded city.");
  add_chat("I fear the armies of the Evil One.");
  add_chat("I don't like the dark clouds gathering in the east.");
  seq_new("do_things");
  seq_addfirst("do_things",({"@@get_armed","say Reporting for guard-duty!"}));
}

get_armed() {
  object wep, arm;
  seteuid(getuid(this_object()));
  wep = clone_object("/d/Gondor/elessar/obj/wep/rndsword");
  wep->move(this_object());
  command("wield sword");
  arm = clone_object("/d/Gondor/elessar/obj/arm/rndarmour");
  arm->move(this_object());
  command("wear armour");
  arm = clone_object("/d/Gondor/elessar/obj/arm/rndhelmet");
  arm->move(this_object());
  command("wear helmet");
}

init_living()
{
  ::init_living();
  check_race(this_player());
}

check_race(object tp)
{
  if (tp->query_race_name()=="goblin" || tp->query_race_name()=="orc") {
    this_object()->command("say "+capitalize(tp->query_race_name())+"s! Attack!");
    this_object()->command("kill "+tp->query_real_name());
    return 1;
    }
  return 0;
}

