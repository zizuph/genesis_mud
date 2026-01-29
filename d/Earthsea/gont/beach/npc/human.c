/*
 * Humans on the beach
 * Coded by Finwe
 * June 1997
 * Updated by Amelia (1/98): Roke references taken out,
 * new weapons and equip added, etc.
 */

#pragma strict_types

inherit "/d/Earthsea/std/monster";

#include <ss_types.h>
#include <stdproperties.h>
#include "default.h"

#define WEAPON ( \
  ({ WEP_DIR + "sword", WEP_DIR + "sword", WEP_DIR + "short_spear" })[random(3)] \
)

public void
create_earthsea_monster()
{
    string age = ({"young","middle-aged", "elderly"})[random(3)],
        descrip  = ({"large", "medium", "small"})[random(3)],
        type  = ({"beachcomber", "bully", "scavenger"})[random(3)];

    add_adj(descrip);
    add_adj(age);
    add_adj(type);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_gender(random(2));
    set_name(type);
    set_short(descrip + " " + age + " " + type);
    set_long("A " + descrip + " " + age + " " + type + ". "+
      capitalize(query_pronoun()) + " seems to be searching for stuff that "+
      "has been left behind or washed up from the sea.\n");

    if (random(5) == 4)
    {
        add_equipment(({ WEAPON, OBJ_DIR + "looter_pack"}));
    } else {
        add_equipment(({ WEAPON }));
    }

    default_config_npc(30+random(30));
    set_skill(SS_DEFENCE, 10+random(10));
    set_skill(SS_PARRY, 25);
    set_skill(SS_WEP_POLEARM, 10 + random(10));
    set_skill(SS_WEP_SWORD, 10 + random(10));
    set_skill(SS_WEP_AXE, 10 + random(10));
    set_all_hitloc_unarmed(1);

    set_m_in("wanders in");
    set_m_out("wanders away");
    set_random_move(80);
    set_restrain_path(BEACH);

    add_prop(OBJ_M_HAS_MONEY, ({ random(30), 0, 0, 0 }));
}
