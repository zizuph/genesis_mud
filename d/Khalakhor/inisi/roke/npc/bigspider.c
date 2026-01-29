/*
 * bigspider.c
 *
 * Used in wild/monk_occtrain2.c
 *
 * Created during the Roke cleanup by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/creature";
inherit "/std/combat/unarmed";

#include "defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <money.h>
#include <wa_types.h>
#include <const.h>

int alarmid;

void
create_creature()
{
    int i;
    string type;

    set_name("spider");
    set_race_name("spider");
    set_short("big spider");
    set_long("A big nasty spider.\n");
    set_adj("big");
    set_gender(G_NEUTER);

    NEVERKNOWN;

    set_attack_unarmed(0, 15+random(10), 20+random(10), W_IMPALE, 52, "jaws");
    set_attack_unarmed(1, 20+random(10), 10+random(10), W_BLUDGEON, 9,
                       "front left leg");
    set_attack_unarmed(2, 20+random(10), 10+random(10), W_BLUDGEON, 9,
                       "front right leg");
    set_attack_unarmed(3, 10+random(10), 10+random(10), W_BLUDGEON, 5,
                       "second left leg");
    set_attack_unarmed(4, 10+random(10), 10+random(10), W_BLUDGEON, 5,
                       "second right leg");
    set_attack_unarmed(5, 10+random(10), 10+random(10), W_BLUDGEON, 5,
                       "third left leg");
    set_attack_unarmed(6, 10+random(10), 10+random(10), W_BLUDGEON, 5,
                       "third right leg");
    set_attack_unarmed(7, 10+random(10), 10+random(10), W_BLUDGEON, 5,
                       "back left leg");
    set_attack_unarmed(8, 10+random(10), 10+random(10), W_BLUDGEON, 5,
                       "back right leg");

    set_hitloc_unarmed(0, ({20}), 20, "head");
    set_hitloc_unarmed(1, ({20}), 80, "body");

    set_base_stat(SS_STR, 38);
    set_base_stat(SS_DEX, 29);
    set_base_stat(SS_CON, 27);
    set_base_stat(SS_INT, 9);
    set_base_stat(SS_WIS, 21);
    set_base_stat(SS_DIS, 32);
}
