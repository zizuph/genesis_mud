/* This is the bunny who produces the lucky rabbit's foot
 * for the lucky items quest in Tenalders. It is hidden in 
 * /d/Earthsea/gont/tenalders/high_fall/briars.c
 * Coded by Amelia, October 1997.
*/

#pragma strict_types

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";

#include <wa_types.h>
#include <ss_types.h>

#define A_FOOT 0
#define A_TEETH 1
#define A_TAIL 2
#define H_HEAD 0
#define H_BODY 1

public void
create_creature()
{
    set_name("rabbit");
    set_living_name("_fuzzy_rabbit_");
    set_race_name("rabbit");
    set_short("fuzzy white bunny rabbit");
    set_adj(({"fuzzy", "white", "bunny"}));
    set_long("A cute fuzzy white bunny rabbit.\n");
    set_m_in("hops in.");
    set_m_out("hops away");
    default_config_creature(3);
    set_skill(SS_DEFENCE, 5);
    set_skill(SS_UNARM_COMBAT, 3);
    add_leftover("/d/Earthsea/gont/tenalders/obj/items/rabbits_foot", "foot", 1, 1, 1, 0);
    set_attack_unarmed(A_TEETH, 10, 20, W_IMPALE, 33, "sharp teeth");
    set_attack_unarmed(A_TAIL, 10, 20, W_BLUDGEON, 33,
        "cute cotton tail");
    set_attack_unarmed(A_FOOT, 10, 20, W_BLUDGEON, 33, 
        "fuzzy white foot");
    set_hitloc_unarmed(H_HEAD, ({ 15, 25, 20, 20 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 10, 15, 30, 20 }), 80, "body");
    set_act_time(80);
    add_act("emote nibbles on a leaf.");
    add_act("emote wiggles his long pink ears.");
    add_act("emote does the bunny hop.");
}
