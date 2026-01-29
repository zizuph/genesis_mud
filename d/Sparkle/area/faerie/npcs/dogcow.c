/* The old dogcow from old Faerie.
 * This friendly creature is such a part
 * of Genesis that it would be a shame to 
 * not include her in Faerie. Nonetheless, she
 * has been improved so that she does more 
 * than just say 'Moof'.
 * 
 * Updated by Finwe, August 2004
 */

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <const.h>
#include "../defs.h"

#pragma save_binary

inherit "/std/creature";
inherit "/std/combat/unarmed";   /* This gets us standard unarmed routines */
inherit "/std/act/domove";
inherit "/std/act/action";


/*
 * Define some attack and hitloc id's (only for our own benefit)
 */

#define A_BITE  0
#define A_GORE  1
#define A_KICK  2

#define H_HEAD 0
#define H_BODY 1
#define H_LF_LEG 2
#define H_RF_LEG 3
#define H_LR_LEG 4
#define H_RR_LEG 5

create_creature()
{
    set_race_name("dogcow");
    set_adj(({"black and white"}));
    set_long("It is a strange creature. It looks somewhat like " +
        "a very small cow, or perhaps a very large terrier. " +
        "It is long-haired, white with large patches of " +
        "carbon black, and has a pair of bone-yellow horns " +
        "and deep, soulful eyes.\n");

    set_gender(G_FEMALE);
    add_prop(NPC_I_NO_LOOKS,   1);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_base_stat(SS_STR, 15);
    set_base_stat(SS_DEX, 25);
    set_base_stat(SS_CON, 15);
    set_base_stat(SS_INT, 3);
    set_base_stat(SS_WIS, 3);
    set_base_stat(SS_DIS, 35);

    set_skill(SS_DEFENCE, 10);

    set_attack_unarmed(A_BITE, 20, 30, W_IMPALE,   20, "jaw");
    set_attack_unarmed(A_GORE, 20, 30, W_IMPALE,   50, "horns");
    set_attack_unarmed(A_KICK, 40, 20, W_BLUDGEON, 10, "hooves");
   
    set_hitloc_unarmed(H_HEAD,    ({ 15, 25, 20, 20 }), 10, "head");
    set_hitloc_unarmed(H_BODY,    ({ 10, 15, 30, 20 }), 50, "body");
    set_hitloc_unarmed(H_LF_LEG,  ({ 10, 15, 30, 20 }), 10, "left front leg");
    set_hitloc_unarmed(H_RF_LEG,  ({ 10, 15, 30, 20 }), 10, "right front leg");
    set_hitloc_unarmed(H_LR_LEG,  ({ 10, 15, 30, 20 }), 10, "left rear leg");
    set_hitloc_unarmed(H_RR_LEG,  ({ 10, 15, 30, 20 }), 10, "right rear leg");

    set_act_time(5); 
    add_act("emote moos: Moof."); 
    add_act("emote scratches her head with her front paw.");
    add_act("emote looks up at you with her soulful eyes.");
    add_act("emote shakes her head.");
    add_act("emote eats some grass from under the trees.");
    add_act("emote sits down under an apple tree.");
    add_act("emote stands up from under a tree.");
    add_act("emote runs around and kicks her paws up in the air.");
    add_act("emote looks up from eating grass and watches you.");

    set_m_in("prances in");
    set_m_out("prances");
}

