inherit "/d/Roke/common/monster";
inherit "/std/act/attack";
inherit "/std/act/action";
#include "/d/Roke/common/defs.h"
#include "/d/Roke/Cirath/defs.h"
#include <macros.h>
#include "/sys/ss_types.h"

create_monster()
{
  set_race_name("human");
  set_name("warrior");
  set_short("plain warrior");
  set_long("The guard is guarding the towers from people like you.\n");
  set_adj("grand");
  default_config_npc(90);
  set_alignment(-500);
  set_skill(SS_WEP_SWORD,90);
  set_skill(SS_DEFENCE,75);
  set_skill(SS_PARRY,75);
  set_aggressive(1);

  NEVERKNOWN;

  call_out("equip_me",1);
}
query_knight_prestige(){return 800;}

equip_me()
{
  clone_object("/d/Roke/common/gont/re/castle/obj/steelsword")->move(TO);
  clone_object("/d/Roke/common/gont/re/castle/obj/lboots")->move(TO);
  clone_object("/d/Roke/common/gont/re/castle/obj/steelhelmet")->move(TO);
  clone_object("/d/Roke/common/gont/re/castle/obj/steelmail")->move(TO);

  command("wear all");
  command("wield all");
}
