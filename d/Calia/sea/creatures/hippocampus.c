
 /*  
    A hippocampus (sea horse) for the water area

    coder(s):    Jaacar  July 2003

 */

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include <formulas.h>
#include <const.h>
#include "defs.h"
#include GLYKDEF
#include RANDOM_HEADER
inherit SEA_CREATURES+"hippoc";

#define A_BITE  0
#define A_L_HOOF 1
#define A_R_HOOF 2
#define A_TAIL 3

#define H_HEAD 0
#define H_BODY 1
#define H_L_HOOF 2
#define H_R_HOOF 3
#define H_TAIL 4

void
create_hippocampus()
{
    if (!IS_CLONE)
	return;
    ::create_hippocampus();
    set_name("hippocampus");
    set_pshort("enormous proud hippocampi");
    add_name("sea horse");
    set_adj(({"enormous","proud"}));
    set_pname("hippocampi");
    set_race_name("hippocampus");
    set_long("This creature looks alot like a land dwelling horse "+
        "except it only has the head and forequarters of a normal "+
        "horse and its tail looks like that of a large dolphin. It "+
        "looks quite powerful and agile.\n");

    add_leftover(SEA_LEFTOVERS+"hippocampus_meat",
                             "meat", (random(8)), 0, 0, 1);

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_LOOKS, 1);

    set_alignment(15);
    set_gender(G_MALE);

    add_prop(CONT_I_VOLUME, 40000);
    add_prop(CONT_I_WEIGHT, 40000);

    set_stats(({(70+random(30)),(50+random(45)),(50+random(45)),
        (50+random(45)),(50+random(45)),(50+random(40))}));

    set_skill(SS_SWIM, 100);
    set_skill(SS_UNARM_COMBAT, 75);
    set_skill(SS_BLIND_COMBAT, 50);
    set_skill(SS_DEFENCE, 60);

    set_attack_unarmed(A_BITE,15,17,W_SLASH,55,"bite");
    set_attack_unarmed(A_L_HOOF, 10, 10, W_BLUDGEON, 15, "left hoof"); 
    set_attack_unarmed(A_R_HOOF, 10, 10, W_BLUDGEON, 15, "right hoof"); 
    set_attack_unarmed(A_TAIL,15,17,W_SLASH,15,"tail");

    set_hitloc_unarmed(H_HEAD, ({5,5,5,5}), 10, "head");
    set_hitloc_unarmed(H_L_HOOF, ({5,5,5,10}), 15, "left hoof");
    set_hitloc_unarmed(H_R_HOOF, ({5,5,5,10}), 15, "right hoof");
    set_hitloc_unarmed(H_BODY, ({10,15,15,20}), 45, "body");
    set_hitloc_unarmed(H_TAIL, ({10,15,15,20}),15,"tail");

    set_act_time(7); 
    add_act("emote nibbles at some seaweed on the ground."); 
}

