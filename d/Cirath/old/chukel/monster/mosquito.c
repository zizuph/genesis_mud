inherit "/std/act/attack";
inherit "/std/creature";
inherit "/std/act/domove";
inherit "/std/combat/unarmed";

#include "/d/Roke/Cirath/defs.h"
#include "/d/Roke/common/defs.h"
#include <ss_types.h>
#include <macros.h>
#include <money.h>
#include <wa_types.h>


create_creature()
{
  if (!IS_CLONE)
    return;

  set_name("mosquito");
  set_race_name("mosquito");
  set_short("irritating mosquito");
  set_long("A small blood-thursting mosquito.\n");
  set_adj("irritating");
  set_restrain_path(JUNGLE);
  set_random_move(10);
  set_aggressive(1);

  NEVERKNOWN;
  add_prop(LIVE_I_NO_CORPSE,1);

  set_attack_unarmed(0, 3, 3, W_IMPALE, 80, "bite");

  set_hitloc_unarmed(0, ({ 1 }), 20, "head");
  set_hitloc_unarmed(1, ({ 1 }), 80, "body");

  set_base_stat(SS_STR,1);
  set_base_stat(SS_DEX,40);
  set_base_stat(SS_CON,1);
  set_base_stat(SS_INT,1);
  set_base_stat(SS_WIS,1);
  set_base_stat(SS_DIS,50);
}
