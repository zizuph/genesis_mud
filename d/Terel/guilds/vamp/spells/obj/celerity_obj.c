
#include "../../guild.h"

inherit SPELLOBJ_DIR+"spell_obj";
inherit CORELIB_DIR+"std/evade_obj_base";
inherit "/lib/commands";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>

/*
 * Function     : create_effect
 * Description  : The create function called for objects that inherit this
 * Arguments    : none
 * Returns      : nothing
 */
public void
create_effect()
{    
    //Evade combat aid is overridden with query_evade_combat_aid
    //For the various scenarios
    
    set_evade_skills(({ SS_DEFENSE })); // removing weighting since it can be drained
    set_evade_stats(({ SKILL_AVG, TS_DEX, TS_OCC, SKILL_END }));
    
    set_evade_combat_aid(33);
    set_name("_vamp_celerity_obj");
    add_name( ({"vamp_celerity_obj" }) );
    set_short("hidden vamp celerity object");    
    set_long("A basic evade object. One should not be able to see it "
           + "in their inventory.\n");
    
    
}

varargs public int
dispel_effect(object dispeller)
{

    effect_target->catch_msg("Your hastened state subsides.\n");
	
    effect_target->add_prop(LIVE_I_QUICKNESS,
        effect_target->query_prop(LIVE_I_QUICKNESS) - 100);
        
    effect_target->query_combat_object()->cb_update_speed();

    remove_effect_object();
    return 1;
}

public int
start()
{

    set_spell_effect_desc("move at an accellerated speed");

    if (!::start() || move(effect_target,1))
    {
        remove_effect_object();
        return 0;
    }

    effect_target->add_prop(LIVE_I_QUICKNESS,
        effect_target->query_prop(LIVE_I_QUICKNESS) + 100);

    effect_target->query_combat_object()->cb_update_speed();

    write("You focus your power and instantly you begin " +
         "to move at an amazing rate.\n");
    allbb(" begins to move with blinding speed.\n");

    //Typical effect time - 4 minutes to 10 
    int delay=max(240,effect_target->query_vamp_stat()*8);
    
    delay=min(600,delay);
    
    set_dispel_time(delay);

    return 1;
}

public void init()
{
    ::init();
    add_action(stop,"stop");
}

/*
 * Function: attack_blocked
 * makes messages for watchers that we covered hit with shield
 */
public void
attack_blocked(object player,object attacker,int att_id)
{
    attacker->catch_msg(QCTNAME(player) +
        " is moving with such celerity that you miss your chance to " +
        "strike at " + OBJ(player) + ".\n");

}


public int query_celerity_effect()
{
    return 1;
}

public int
query_evade_valid(object player, object attacker, int attack_id)
{
    return 1;
}

