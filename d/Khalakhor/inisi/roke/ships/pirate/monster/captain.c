#pragma save_binary

inherit "/std/monster";
#include <ss_types.h>
#include "/d/Roke/common/defs.h"
#include "/sys/money.h"

create_monster()
{
  set_name("longbein");
  set_long("It's the captain of the pirate ship. He is very tall.\n");
  set_short("pirate captain");
  add_name("captain");
  set_adj("pirate");
  
  default_config_npc(50);

  set_skill(SS_WEP_SWORD,50);
  set_skill(SS_PARRY,23);
  set_skill(SS_DEFENCE,25);

  set_alignment(-200);

  set_aggressive(1);

  call_out("equip_me",1);
}
equip_me()
{
  seteuid(getuid(TO));

  MONEY_MAKE_GC(20)->move(TO);

  clone_object(SHIPS+"pirate/obj/cutlass")->move(TO);
  clone_object(REDIR+"castle/obj/doublehelmet")->move(TO);
  command("wear all");
  command("wield all");
}