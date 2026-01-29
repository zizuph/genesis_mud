/*
 * ant.c
 *
 * Used in wild/ran/forroom.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/creature";
inherit "/std/act/domove";
inherit "/std/combat/unarmed";

#include "defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <money.h>
#include <wa_types.h>

void
create_creature()
{
    int i;
    string type;

    set_name("ant");
    set_race_name("ant");
    set_short("small ant");
    set_long("A small hard working ant.\n");
    set_adj("small");
    set_restrain_path(ROKEDIR + "wild/ran/");
    set_random_move(10);

    NEVERKNOWN;
    add_prop(LIVE_I_NO_CORPSE, 1);

    set_attack_unarmed(0, 3, 3, W_IMPALE, 52, "tiny jaws");
    set_attack_unarmed(1, 2, 2, W_BLUDGEON, 8, "front left leg");
    set_attack_unarmed(2, 2, 2, W_BLUDGEON, 8, "front right leg");
    set_attack_unarmed(3, 2, 2, W_BLUDGEON, 8, "middle left leg");
    set_attack_unarmed(4, 2, 2, W_BLUDGEON, 8, "middle right leg");
    set_attack_unarmed(5, 2, 2, W_BLUDGEON, 8, "back left leg");
    set_attack_unarmed(6, 2, 2, W_BLUDGEON, 8, "back right leg");

    set_hitloc_unarmed(0, ({1}), 20, "head");
    set_hitloc_unarmed(1, ({1}), 80, "body");

    set_base_stat(SS_STR, 5);
    set_base_stat(SS_DEX, 4);
    set_base_stat(SS_CON, 2);
    set_base_stat(SS_INT, 4);
    set_base_stat(SS_WIS, 4);
    set_base_stat(SS_DIS, 5);

    i = random(200);
    if (i == 0)
        type = "gold";
    else if (i < 25)
        type = "silver";
    else
        type = "copper";

    MONEY_MAKE(1, type)->move(this_object());
}
