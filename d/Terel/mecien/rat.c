inherit "/std/creature";
inherit "/std/combat/unarmed";

#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>

#define BS(message)   break_string(message, 72)
#define TO            this_object()
#define TP            this_player()

#define A_BITE  0

#define H_HEAD  0
#define H_BODY  1

query_m_out(){
return "scurries away";
}

query_m_in(){
return "scurries in.";
}

create_creature()
{
    set_name("rat");
    set_long(BS(
        "A very foul looking rat. It has dark black fur, dark eyes "
       +"and sharp teeth.\n"
    ));
    set_adj("black");
    set_race_name("rat");

    set_stats( ({15,13,13,4,7,2}) );
    set_hp(9999);
    set_mana(9999);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_SEE_DARK, 1);
    add_prop(LIVE_I_SEE_INVIS, 1);
    add_prop(CONT_I_WEIGHT, 5000);
    add_prop(CONT_I_VOLUME,  4000);
    add_prop(CONT_I_MAX_WEIGHT, 8000);
    add_prop(CONT_I_MAX_VOLUME, 6000);
    add_prop(LIVE_I_QUICKNESS, 40);
    set_skill(SS_DEFENCE,      35);
    set_skill(SS_AWARENESS,    20);
    set_skill(SS_UNARM_COMBAT, 10);
    set_skill(SS_CLIMB,        10);
    set_skill(SS_LOC_SENSE,    40);
    set_skill(SS_HUNTING,      10);

    set_attack_unarmed(A_BITE,  12, 12, W_IMPALE, 100, "teeth");
    
    set_hitloc_unarmed(H_HEAD, 10, 20, "head");
    set_hitloc_unarmed(H_BODY, 12, 80, "body");

    set_act_time(10);
    add_act("emote scurries about.");
    add_act("emote squeeks.");
    
}
