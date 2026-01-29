/*
 * shepdoggy.c
 *
 * Used in npc/shepherd.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/creature";
inherit "/std/combat/unarmed";

#include <ss_types.h>
#include <wa_types.h>

void
create_creature()
{
    set_name("doggy");
    add_name("dog");
    set_short("yellow dog");
    set_adj("yellow");
    set_long("This is an ordinary, yellow dog.\n");
    set_race_name("dog");
    default_config_creature(20);
    set_base_stat(SS_DIS, 80);
    set_base_stat(SS_STR, 40);

    set_attack_unarmed(0, 40, 25, W_IMPALE, 90, "grim teeth");
    set_attack_unarmed(1, 40, 20, W_SLASH, 50, "left paw");
    set_attack_unarmed(2, 40, 20, W_SLASH, 50, "right paw");

    set_hitloc_unarmed(A_HEAD, 15, 20, "head");
    set_hitloc_unarmed(A_BODY, 35, 60, "body");
    set_hitloc_unarmed(A_R_ARM, 15, 10, "right leg");
    set_hitloc_unarmed(A_L_ARM, 15, 10, "left leg");
}
