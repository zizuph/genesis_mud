
 /*  
    A turtle for the water area

    coder(s):    Jaacar

    Modified, Maniac, 18/9/96
    Fixed set_restrain_path,  Jaacar, 18/8/97
 */

inherit "/d/Calia/std/sea_creature";
inherit "/std/combat/unarmed";

inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include <formulas.h>
#include <const.h>

#include "defs.h"

#define A_BITE  0
#define A_L_FLIPPER 1
#define A_R_FLIPPER 2

#define H_HEAD 0
#define H_BODY 1
#define H_L_FLIPPER 2
#define H_R_FLIPPER 3

void
create_creature()
{
    set_name("turtle");
    set_adj("big");
    add_adj("green");
    set_race_name("turtle");
    set_long("This creature is very large, and probably very old. "+
        "It has a large dark green shell covering its vulnerable "+
        "flesh from predators. This turtle does not seem to be "+
        "as slow as you think as it is swimming around quite "+
        "quickly looking for food.\n");

    add_leftover(SEA_LEFTOVERS+"turtle_meat",
                             "meat", 1, 0, 0, 1);
    add_leftover(SEA_LEFTOVERS+"turtle_eye", 
                              "eyeball", 2, 0, 0, 1);
    add_leftover(SEA_LEFTOVERS+"turtle_shell","shell", 1, 0, 1, 1);
    add_leftover(SEA_LEFTOVERS+"turtle_neck","neck", 1, 0, 0, 1);

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_LOOKS, 1);

    set_alignment(15);
    set_gender(G_NEUTER);

    set_random_move(15); 

    /* Want to keep these on the surface */ 
    set_restrain_path(({(SECTOR_PATH(0, 0, 0)),(SECTOR_PATH(10, 0, 0)),
        (SECTOR_PATH(0, 10, 0)),(SECTOR_PATH(10, 10, 0))}));

    add_prop(CONT_I_VOLUME, 20000);
    add_prop(CONT_I_WEIGHT, 20000);

    set_stats(({30,30,25,15,15,30}));

    set_skill(SS_SWIM, 100);
    set_skill(SS_UNARM_COMBAT, 30);
    set_skill(SS_BLIND_COMBAT, 50);
    set_skill(SS_DEFENCE, 30);

    set_attack_unarmed(A_BITE,15,17,W_SLASH,70,"bite");
    set_attack_unarmed(A_L_FLIPPER, 10, 10, W_BLUDGEON, 15, "left flipper"); 
    set_attack_unarmed(A_R_FLIPPER, 10, 10, W_BLUDGEON, 15, "right flipper"); 

    set_hitloc_unarmed(H_HEAD, ({5,5,5,5}), 10, "head");
    set_hitloc_unarmed(H_L_FLIPPER, ({5,5,5,10}), 15, "left flipper");
    set_hitloc_unarmed(H_R_FLIPPER, ({5,5,5,10}), 15, "right flipper");
    set_hitloc_unarmed(H_BODY, ({10,15,15,20}), 60, "shell");

    set_act_time(7); 
    add_act("emote flaps its flippers."); 
    add_act("emote paddles around gently."); 
    add_act("emote ducks into its shell sensing danger is near.");
    add_act("emote nibbles at some seaweed."); 
}

