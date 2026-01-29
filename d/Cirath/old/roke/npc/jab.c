/*
 * jab.c
 *
 * Used in nyreese/red_jabroom.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";
inherit "/std/act/domove";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>

void
default_config_npc(int i)
{
    int j;
    for (j = 0; j < 6; j++)
        set_base_stat(j, i);
}

void
create_creature()
{
    default_config_npc(100);

    set_name("jabberwock");
    set_race_name("jabberwock");
    set_short("fierce jabberwock");
    set_adj("fierce");

    set_long("He has very sharp claws, and nasty-looking jaws.\n");

    set_alignment(-100);

    set_skill(SS_DEFENCE, 75);
    set_skill(SS_UNARM_COMBAT, 75);

    set_attack_unarmed(0, 100, 100, W_IMPALE, 50, "jaws");
    set_attack_unarmed(1, 100, 100, W_IMPALE, 50, "claws");
    set_hitloc_unarmed(0, ({90}), 20, "head");
    set_hitloc_unarmed(1, ({90}), 80, "body");

    add_prop(CONT_I_WEIGHT, 10000000);
    add_prop(CONT_I_MAX_WEIGHT, 20000000);
}
