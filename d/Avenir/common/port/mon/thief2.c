// Coded by Ibun 070612
// bug(s):
// to-do:

#pragma strict_types
#include <stdproperties.h>     /* Where the properties are defined. */
#include <ss_types.h>
#include <macros.h>
#include <money.h>
#include <wa_types.h>
#include <state_desc.h>
#include "/d/Avenir/common/common.h"

inherit "/std/monster";
inherit "/lib/unique";

void equip_me();

void
create_monster()
{
  set_name("Barney");
  set_adj("tanned");
  set_race_name("human");
  set_long("This is a tanned man in his best age.\n");
  set_stats(({130, 130, 200, 60, 60, 90}));
  set_alignment(-1000);
  set_skill(SS_DEFENSE, 100 );
  set_skill(SS_PARRY, 80);
  set_skill(SS_WEP_KNIFE, 100 );
  set_skill(SS_AWARENESS, 70 );
  set_cchat_time(5);
  add_cchat("Burn!");
  add_cchat("DIE!");
  equip_me();
}

void
equip_me()
{
    MONEY_MAKE_SC(random(50))->move(this_object(), 1);

    clone_object(PORT + "obj/jacket")->move(this_object(), 1);
    clone_unique((PORT + "obj/shadow_cloak"), 5, (PORT + "obj/oilskin_cloak"),
        1, 30)->move(this_object(), 1);
    command("wear all");
    clone_object(PORT + "obj/uw_dagger")->move(this_object(), 1);
    command("wield dagger");
}


