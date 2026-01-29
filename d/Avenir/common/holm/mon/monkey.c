// small monkey  (/d/Avenir/common/holm/mon/monkey.c)
// Creator:      Lilith 25 March 1997
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
    set_name("monkey");
    set_pname("monkeys");
    set_race_name("monkey");
    set_adj(({"small", "brown"}));
    set_short("small brown monkey");
    set_pshort("small brown monkeys");
    set_long("This little fellow dwells in the trees of the Holm's "+
        "jungle, feeding off of insects and fruit. His tiny face is "+
        "dominated by large, limpid eyes that are so dark you cannot "+
        "see the pupil.\n");
    set_alignment(0);

//  Sets the stats for us, its a simple npc 
    default_config_creature(9 + random(7));

    remove_prop(OBJ_M_NO_GET);
    remove_prop(OBJ_M_NO_GIVE);
    add_prop(CONT_I_VOLUME, 6000);
    add_prop(CONT_I_WEIGHT, 5000);
    add_prop(LIVE_I_NEVERKNOWN, 1); 
    add_prop(UNIVERSAL_OFFERING, 1);  
  
    set_skill(SS_BLIND_COMBAT, 20);
    set_skill(SS_UNARM_COMBAT, 20);
    set_skill(SS_DEFENCE, 20);
    set_skill(SS_AWARENESS, 40); 

    set_act_time(10);
    add_act("emote crunches on a juicy ant.");	
    add_act("emote gets busy grooming himself.");
    add_act("emote plucks a bug from your hair and munches it happily.");
    add_act("emote watches you with a surprising intelligence behind "+
        "his eyes.");
    add_act("get weapon");
    add_act("get item");
    
    set_cact_time(10);
    add_cact("emote screeches angrily.");
    add_cact("emote hops around and screeches at you, showing his fangs.");

//                   'weapon', hit, pen, damage type, %use, desc                      
    set_attack_unarmed(A_BITE,   10, 10,  W_IMPALE,   20, "fangs");
    set_attack_unarmed(A_LHAND,   5,  5,  W_SLASH,    30, "left front claw");
    set_attack_unarmed(A_RHAND,   5,  5,  W_SLASH,    30, "right front claw");
    set_attack_unarmed(A_RFOOT,   5,  5,  W_BLUDGEON, 10, "right rear foot");
    set_attack_unarmed(A_LFOOT,   5,  5,  W_BLUDGEON, 10, "left rear foot");
//  Everything in this column should add up to 100 ---^

//                     where,     ac,  %hit, desc
    set_hitloc_unarmed(H_HEAD, ({ 10 }), 10, "head");
    set_hitloc_unarmed(H_BODY, ({ 10 }), 40, "body");
    set_hitloc_unarmed(H_TAIL, ({ 10 }), 10, "tail");
    set_hitloc_unarmed(H_LFQ,  ({ 10 }), 20, "left forearm");
    set_hitloc_unarmed(H_RHQ,  ({ 10 }), 20, "right hind-quarter");
//  The sum of this column should be 100 -^   
}

