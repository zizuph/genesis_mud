
inherit "/std/creature";

inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#include "/d/Avenir/common/common.h"

/* These define what the insect will attack with */
#define A_LFORE  TS_LHAND
#define A_RFORE  TS_RHAND
#define A_RMID   TS_RFOOT
#define A_LMID   TS_LFOOT

/* These define what body parts will be hit in fights */
#define H_HEAD    TS_HEAD
#define H_ABDOM   TS_TORSO
#define H_RMID    TS_RARM  
#define H_LMID    TS_LARM
#define H_RHLEG   TS_RFOOT 
#define H_LHLEG   TS_LFOOT


void
create_creature()
{
    set_name("termite");
    set_pname("termites");
    set_race_name("insect");
    set_adj("pale");
    set_short("pale termite insect");
    set_long("The exoskeleton is surprisingly pale, almost "+
        "white. It resembles a large white ant, and it feeds "+
        "on wood.\n");

    set_alignment(0);
    remove_prop(OBJ_M_NO_GET);


//  Sets the stats for us, its a simple npc 
    default_config_creature(1 + random(3));

//                   'weapon', hit, pen, damage type, %use, desc                      
    set_attack_unarmed(A_LFORE, 1, 1, W_BLUDGEON, 1, "left foreleg");
    set_attack_unarmed(A_RFORE, 1, 1, W_BLUDGEON, 1, "right foreleg");
    set_attack_unarmed(A_RMID,  1, 1, W_BLUDGEON, 1, "right middle leg");
    set_attack_unarmed(A_LMID,  1, 1,  W_BLUDGEON, 1, "left middle leg");

//                     where,     ac,  %hit, desc
    set_hitloc_unarmed(H_HEAD,  ({ 10 }), 10, "head");
    set_hitloc_unarmed(H_ABDOM, ({ 5 }),  10, "abdomen");
    set_hitloc_unarmed(H_RMID,  ({ 30 }), 10, "right middle leg");
    set_hitloc_unarmed(H_LMID,  ({ 30 }), 10, "left middle leg");
    set_hitloc_unarmed(H_RHLEG, ({ 30 }), 10, "right hind leg");
    set_hitloc_unarmed(H_LHLEG, ({ 30 }), 10, "left hind leg");

// Set last to not be overwritten above.
    add_prop(CONT_I_VOLUME, 100);
    add_prop(CONT_I_WEIGHT, 100);
    add_prop(CONT_I_MAX_VOLUME, 1000);
    add_prop(CONT_I_MAX_WEIGHT, 1000);
}
