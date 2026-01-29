/* This is /d/Gondor/common/npc/wrabbit.c
 * A white rabbit
 * Dunstable, Septembet 1993
 */
inherit "/std/creature";
inherit "/std/act/action";
inherit "/std/combat/unarmed";
inherit "/std/act/attack";

#include <const.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

/*
 * Define some attack and hitloc id's
 */
#define A_PECK  0
#define A_LLASH 1
#define A_RLASH 2
#define A_CLAW  3

#define H_HEAD  0
#define H_BODY  1
#define H_LWING 2
#define H_RWING 3

void
create_creature()
{
    set_name("hen");
    set_short("small white hen");
    set_long("A small white hen tips around in the barn looking for food. \n");

    set_gender(G_FEMALE);

    add_adj("white");
    add_adj("small");

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(OBJ_I_NO_GET, 0);

    set_act_time(4);
    add_act("emote looks for something to eat.");
    add_act("emote eats some grains from the floor.");
    add_act("emote clucks.");
    add_act("pace");

    set_skill(SS_DEFENCE, 10);
    set_skill(SS_UNARM_COMBAT, 10);

    set_attack_unarmed(A_PECK, 8, 10, W_IMPALE, 80, "beak");
    set_attack_unarmed(A_LLASH, 10, 10, W_BLUDGEON, 9, "left wing");
    set_attack_unarmed(A_RLASH, 10, 10, W_BLUDGEON, 9, "right wing");
    set_attack_unarmed(A_CLAW, 15, 15, W_SLASH, 2, "claw");

    set_hitloc_unarmed(H_HEAD, ({8, 10, 6}), 35, "head");
    set_hitloc_unarmed(H_BODY, ({8, 10, 5}), 61, "body");
    set_hitloc_unarmed(H_LWING, ({2, 5, 2}), 2, "left wing");
    set_hitloc_unarmed(H_RWING, ({2, 5, 2}), 2, "right wing");
}
