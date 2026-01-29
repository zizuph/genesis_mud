#pragma save_binary

inherit "/std/monster";
#include <ss_types.h>
#include "/d/Roke/common/defs.h"

create_monster()
{
 
  set_long("This is on of the filthy pirates that follow Captain Longbein.\n");
  set_short("filthy pirate");
  set_name("pirate");
  set_adj("filthy");
  
  default_config_npc(35);

  set_skill(SS_WEP_SWORD,50);
  set_skill(SS_PARRY,23);
  set_skill(SS_DEFENCE,25);

  set_alignment(-75);

  set_aggressive(1);

  call_out("equip_me",1);
}
equip_me()
{
  seteuid(getuid(TO));

  clone_object(SHIPS+"pirate/obj/cutlass")->move(TO);
  clone_object(REDIR+"castle/obj/doublehelmet")->move(TO);
  command("wear all");
  command("wield all");
}