// tiny deer    (/d/Avenir/common/holm/mon/deer.c)
// Creator:      Lilith
// Updates:            
// Purpose:      For Avenir's Holm
// todo: 

inherit "/d/Avenir/inherit/creature";

inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#include "../holm.h"
#include <ss_types.h>
#include <wa_types.h>
#include "/d/Avenir/include/deities.h"

/* These define what the animal will -attack- with when
 * fighting. Deer don't have hands and feet, so we will
 * define what they do have ;)  */
#define A_BITE   TS_HEAD    
#define A_LHOOF  TS_LHAND
#define A_RHOOF  TS_RHAND
#define A_RRHOOF TS_RFOOT
#define A_RLHOOF TS_LFOOT

/* These define what will be -hit- on the animal when it is
 * fighting. Deer don't have hands and feet, so we will
 * define what they do have ;)  */
#define H_HEAD   TS_HEAD
#define H_BODY   TS_TORSO
#define H_TAIL   (TS_RARM | TS_LARM)
#define H_LFQ    TS_LFOOT
#define H_RHQ    TS_RFOOT

void
create_creature()
{
    set_name("deer");
    set_pname("deer");
    set_race_name("deer");
    set_adj("miniature");
    set_short("miniature deer");
    set_pshort("miniature deer");
    set_long("This small forest creature is barely knee-high. Its "+
        "coat is golden brown and marked by infrequent white spots "+
        "on its hindquarters. Its legs are spindly and its hooves "+        
        "so small that it could easily stand on the palm of your "+
        "hand.\n");

    set_alignment(0);

//  Sets the stats for us, its a simple npc 
    default_config_creature(7 + random(7));

    remove_prop(OBJ_M_NO_GET);
    add_prop(CONT_I_VOLUME, 7000);
    add_prop(CONT_I_WEIGHT, 11000);
    add_prop(SALILUS_OFFERING, 1); 
    add_prop(ACLOLTHAYR_OFFERING, 1);
    add_prop(UNIVERSAL_OFFERING, 1); 
  
    set_skill(SS_BLIND_COMBAT, 20);
    set_skill(SS_UNARM_COMBAT, 20);
    set_skill(SS_DEFENCE, 20);
    set_skill(SS_AWARENESS, 60); 

//  We will restrain the path to the jungle area  
    set_restrain_path("/d/Avenir/common/holm/");

    set_random_move(20, 0);

    set_act_time(10);
    add_act("emote nibbles at a leaf.");	
    add_act("emote raises its head and stares curiously at you.");
    add_act("emote nudges its moist nose into your hand.");
    add_act("emote licks its nose.");
    
    set_cact_time(10);
    add_cact("emote raises its head and stares curiously at you.");

//                   'weapon', hit, pen, damage type, %use, desc                      
    set_attack_unarmed(A_BITE,   10, 10,  W_IMPALE,   20, "teeth");
    set_attack_unarmed(A_LHOOF,   5,  5,  W_SLASH,    30, "left front hoof");
    set_attack_unarmed(A_RHOOF,   5,  5,  W_SLASH,    30, "right front hoof");
    set_attack_unarmed(A_RRHOOF,  5,  5,  W_BLUDGEON, 10, "right rear hoof");
    set_attack_unarmed(A_RLHOOF,  5,  5,  W_BLUDGEON, 10, "left rear hoof");
//  Everything in this column should add up to 100 ---^

//                     where,     ac,  %hit, desc
    set_hitloc_unarmed(H_HEAD, ({ 10 }), 10, "head");
    set_hitloc_unarmed(H_BODY, ({ 10 }), 40, "body");
    set_hitloc_unarmed(H_TAIL, ({ 10 }), 10, "tail");
    set_hitloc_unarmed(H_LFQ,  ({ 10 }), 20, "left foreleg");
    set_hitloc_unarmed(H_RHQ,  ({ 10 }), 20, "right hind-quarter");
//  The sum of this column should be 100 -^   
    add_leftover("/d/Avenir/inherit/leftover", "intestine",1, "", 0,0);
}

/* A little something to relieve the boredom, and let the little
 * dudes actually get some revenge :) */
int
cr_did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit)
{
    if (aid == A_RLHOOF)
    {
        tell_object(enemy, "The deer kicks you painfully hard with "+
            "its rear legs, temporarily disabling you.\n");
        enemy->add_attack_delay(10);	
    }   
    return 0;
}

/*
void
init_living()
{
    ::init_living();

    if (interactive(TP))
	set_alarm(3.0, 0.0, &react_blood(TP));
}

void
react_blood(object tp)
{
    if (!present(tp, environment(TO)))
        return;

    if (tp->query_prop("i_killed_a_deer"))
    {
//not sure what I want to do here--maybe have them run away.
    }
}

void
do_die(object killer)
{   
    if (query_hp() > 0) 
      return;

    if (killer && environment(TO) == environment(killer)) 
    {
        killer->add_prop("_i_killed_a_deer", 1);     
    }   

    ::do_die(killer);
}
*/
