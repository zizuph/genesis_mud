// seabird      (/d/Avenir/common/holm/mon/seabird.c)
// Creator:      Lilith May 1997
// Updates:      
// Purpose:      For Avenir's Holm
// todo: 

inherit "/d/Avenir/inherit/creature";

inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#include "/d/Avenir/common/common.h"
#include "/d/Avenir/include/deities.h"

#define A_BITE   TS_HEAD    
#define A_LHAND  TS_LHAND
#define A_RHAND  TS_RHAND
#define A_RFOOT  TS_RFOOT
#define A_LFOOT  TS_LFOOT

#define H_HEAD   TS_HEAD
#define H_BODY   TS_TORSO
#define H_TAIL   (TS_RARM | TS_LARM)
#define H_LFQ    TS_LFOOT
#define H_RHQ    TS_RFOOT

void
create_creature()
{
    set_name("seabird");
    set_pname("seabirds");
    set_race_name("bird");
    set_adj(({"small", "white", "grey"}));
    set_short("small seabird");
    set_long("This is a small, compact seabird with white and "+
        "grey feathers.\n");
    set_alignment(0);

//  Sets the stats for us, its a simple npc 
    default_config_creature(2 + random(4));

    remove_prop(OBJ_M_NO_GET);
    add_prop(CONT_I_VOLUME, 1000);
    add_prop(CONT_I_WEIGHT, 3000);
    add_prop(LIVE_I_NEVERKNOWN, 1); 
    add_prop(HIZARBIN_OFFERING, 1);  
    add_prop(ACLOLTHAYR_OFFERING, 1);

    set_skill(SS_BLIND_COMBAT, 20);
    set_skill(SS_UNARM_COMBAT, 20);
    set_skill(SS_DEFENCE, 20);
    set_skill(SS_AWARENESS, 40); 

    set_act_time(5);
    add_act("emote scratches at the sand.");	
    add_act("emote preens his feathers.");
    add_act("emote twists his head around at an odd angle.");
    add_act("emote watches you with one eye.");
    add_act("emote cries: Awwwwk aaawwwwk!");
    add_act("emote flutters his wings.");
    
    set_cact_time(10);
    add_cact("emote screeches angrily.");
    add_cact("emote pecks at you with his beak.");

//                   'weapon', hit, pen, damage type, %use, desc                      
    set_attack_unarmed(A_BITE,   10, 10,  W_IMPALE,   20, "beak");
    set_attack_unarmed(A_LHAND,   5,  5,  W_SLASH,    10, "left wing");
    set_attack_unarmed(A_RHAND,   5,  5,  W_SLASH,    10, "right wing");
    set_attack_unarmed(A_RFOOT,   5,  5,  W_BLUDGEON, 30, "right foot");
    set_attack_unarmed(A_LFOOT,   5,  5,  W_BLUDGEON, 30, "left foot");
//  Everything in this column should add up to 100 ---^

//                     where,     ac,  %hit, desc
    set_hitloc_unarmed(H_HEAD, ({ 10 }), 10, "head");
    set_hitloc_unarmed(H_BODY, ({ 10 }), 40, "body");
    set_hitloc_unarmed(H_TAIL, ({ 10 }), 10, "tail");
    set_hitloc_unarmed(H_LFQ,  ({ 10 }), 20, "left wing");
    set_hitloc_unarmed(H_RHQ,  ({ 10 }), 20, "right wing");
//  The sum of this column should be 100 -^   

    add_leftover("/d/Avenir/inherit/leftover", "feather",1, "", 0,0);
    add_leftover("/d/Avenir/inherit/leftover", "feather",1, "", 0,0);
    add_leftover("/d/Avenir/inherit/leftover", "feather",1, "", 0,0);
}

