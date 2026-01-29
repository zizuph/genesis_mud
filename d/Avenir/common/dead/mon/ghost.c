
// file name: ghost
// creator(s): Ilyian (16 September, 1995)
// last update:
// purpose: Invisible ghost for the catacombs
// note:
// bug(s):
// to-do:

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/attack";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/ranpick";

#include "../dead.h"
#include "money.h";
#include <formulas.h>
#include <cmdparse.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/sys/ss_types.h"
#include "/sys/macros.h"

void
arm_me()
{
   seteuid(getuid());
   MONEY_MAKE_GC(2)->move(this_object());
}


void
create_creature()
{
  set_name(({"ghost","apparition","_Dead_Isle_Ghost","undead", "being"}));
  set_race_name("ghost");
  set_gender(G_NEUTER);

  set_long("This being is shadowy and translucent.\n"
          +"You cannot really make out anything about it.\n");

  set_alignment(0);

  set_stats(({95,120,110,70,70,130}));
  set_hp(query_max_hp());
  set_restrain_path(CRYPT);

  set_skill(SS_AWARENESS, 90);

  set_pick_up(1);
  set_random_move(1,1);
  set_attack_chance(75); 

  set_attack_unarmed(0,35,35,W_SLASH,50,"claw");
  set_attack_unarmed(1,35,35,W_SLASH,50,"claw");

  set_hitloc_unarmed(0, ({50,35,20}),25,"head");
  set_hitloc_unarmed(1,({50,35,20}),50,"body");
  set_hitloc_unarmed(2,({50,35,20}),25,"legs");

  add_prop(LIVE_I_NO_CORPSE,1);
  add_prop(LIVE_I_SEE_DARK,20);
  add_prop(LIVE_I_UNDEAD,1);
  add_prop(LIVE_I_NEVERKNOWN,1);
  add_prop(OBJ_I_INVIS,1);

  set_act_time(20);
   add_act("emote moves slightly.");
   add_act("emote brushes past you.");

}


