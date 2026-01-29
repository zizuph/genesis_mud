/* -*- Mode: C -*-
 * npc/g11-golem
 *
 * By Skippern 20(c)02
 *
 * This is a stone golem. It is summoned when any of the magicians
 * servants are attacked.
 */
inherit "/std/creature";
inherit "/std/combat/unarmed";

inherit "/std/act/action";
inherit "/std/act/add_things";
inherit "/std/act/attack";
inherit "/std/act/asking";
inherit "/std/act/domove";
inherit "/std/act/ranpick";

#include <ss_types.h>
#include <wa_types.h>
#include "../defs.h"

#define A_L_FIST    0
#define A_R_FIST    1
#define A_HORN      2
#define A_LFOOT     3
#define A_RFOOT     4

#define W_HEAD      0
#define W_BODY      1
#define W_L_FOOT    2
#define W_R_FOOT    3
#define W_L_ARM     4
#define W_R_ARM     5

#define GEM_LIST    ({ "opal_fire", "ruby", "diamond_black", "bloodstone", \
                         "moonstone", "jade", "emerald", "beryl_red" })


string gem = one_of_list(GEM_LIST);

void
create_creature()
{
    set_name("golem");
    set_short("stone golem");
    set_long("A stone golem is a battle machine.\n");

    set_stats( ({ 100, 85, 85, 50, 50, 100 }) );

    set_skill(SS_DEFENCE,         80);
    set_skill(SS_PARRY,           80);
    set_skill(SS_UNARM_COMBAT,   100);
    set_skill(SS_BLIND_COMBAT,    50);

    set_attack_unarmed(A_L_FIST, 29, 25, W_BLUDGEON, 25, "left fist");
    set_attack_unarmed(A_R_FIST, 29, 25, W_BLUDGEON, 25, "right fist");
    set_attack_unarmed(  A_HORN, 29, 25,   W_IMPALE, 10, "horn");
    set_attack_unarmed( A_LFOOT, 29, 25, W_BLUDGEON, 15, "left foot");
    set_attack_unarmed( A_RFOOT, 29, 25, W_BLUDGEON, 15, "right foot");

    set_hitloc_unarmed(  W_HEAD, ({ 10, 10, 10, 50 }), 15, "head");
    set_hitloc_unarmed(  W_BODY, ({  8, 10, 12, 50 }), 45, "body");
    set_hitloc_unarmed(W_L_FOOT, ({  2,  2,  8, 50 }), 10, "left foot");
    set_hitloc_unarmed(W_R_FOOT, ({  2,  2,  8, 50 }), 10, "right foot");
    set_hitloc_unarmed( W_L_ARM, ({  2,  2,  8, 50 }), 10, "left arm");
    set_hitloc_unarmed( W_R_ARM, ({  2,  2,  8, 50 }), 10, "right arm");

    add_leftover(DOL_LEFTOVER + "g_claw", "claw", random(8), 0, 1, 0);
    add_leftover(GEM_DIR + gem, "eye", random(3), 0, 1, 0);
}

/*
 * Function name: attacked_by
 * Description:   This function is called when somebody attacks this object
 * Arguments:     ob - The attacker
 */
void
attacked_by(object ob)
{
    object *arr, o;
    int i;

    ::attacked_by(ob);

    arr = (object *)query_team_others();
    for (i = 0; i < sizeof(arr); i++)
        arr[i]->notify_ob_attacked_me(this_object(), ob);
}

