/*  RAVEN - protector of the Hierophant
**          Appears when Hierophant "summons" them when she is being
**          attacked. (see rooms/hiercham)
**
**  Date     Action
** --------- ---------------------------------------------
**  1/1/95   Created                          Zima
** 14/6/2000 these ravens were worth too 
**           much xp (their dis was 200
**           to enable them to attack, other
**           stats 20), now that we have
**           NPC_I_NO_FEAR, not necessary.   Maniac
*/
inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";
 
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include "defs.h"
 
#define A_LWING   0
#define A_RWING   1
#define A_BEAK    2
 
#define H_HEAD 0
#define H_BODY 1
 
void
create_creature()
{
    set_adj("demonic");
    set_short("raven");
    set_name("demonic raven");
    set_race_name("raven");
    set_long(break_string(
        "It is a large jet-black bird, maddened with anger. Blood drips " +
        "from his beak.\n",70));
 
    set_gender(2); /* neuter */
    set_stats(({ 20, 20, 20, 20, 20, 20}));
    // set_base_stat(SS_DIS, 200);
    set_hp(4000);
    set_skill(SS_DEFENCE, 20);

    add_prop(NPC_I_NO_FEAR, 1);  

    set_attack_unarmed(A_LWING, 10, 10, W_BLUDGEON, 10, "left wing");
    set_attack_unarmed(A_RWING, 10, 10, W_BLUDGEON, 10, "right wing");
    set_attack_unarmed(A_BEAK,  30, 30, W_SLASH,    80, "sharp beak");
 
    set_hitloc_unarmed(H_HEAD, ({10, 10, 10, 10 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({10, 10, 10, 10 }), 80, "body");
    set_aggressive(1);
    set_attack_chance(100);
}
