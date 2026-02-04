/*
 * Obfuscate Spell Object
 *
 * Used by the Vampyr Obfuscate Spell to load and remove the
 * shadow when in effect.
 *
 */
 
#include <stdproperties.h>
#include <macros.h>
#include "../../guild.h"

inherit "/std/object";
inherit SPELLOBJ_DIR+"spell_obj";

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Defines
#define TOTAL_MANA_COST               90
#define TOTAL_BLOOD_COST              24
#define OBFUSCATE_INTERVAL_TIME       60.0

// Global Variables
public int      total_duration;
public int      obfuscate_start_time;
public int      paid_mana;
public int      paid_blood;

// Prototypes
public void     pay_obfuscate_cost(object player);
public int      query_mana_cost();
public int      query_blood_cost();


public void create_object()
{
    set_name("_obfuscate_obj");
    
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_S_WIZINFO, "Object providing silent movement.\n" +
    "The player has a random chance of being seen.  If the target is in "+
    "combat or teamed with the player, the player is always seen.\n");

    set_spell_effect_desc("hide your presence");
    set_no_show();

}

varargs public int
dispel_spell_effect(object dispeller)
{
    object target;
    
    target = query_effect_target();    
    if (target->query_obfuscate_shadow())
    {
    	target->remove_obfuscate_shadow();
        target->catch_tell("You relax your mind, letting the deep inner "
            + "focus fade.  Your mental mask of concealment is now "
            + "removed.\n");
    }
    // Before removing the spell object, we check to see if we need
    // to pay any final costs upon expiration of alarm
    int mana_cost = query_mana_cost();
    int blood_cost = query_blood_cost();
    if (mana_cost < target->query_mana()
        && blood_cost < target->query_blood())
    {
        target->add_mana(-mana_cost);
        target->add_blood(-blood_cost);
    }
    
    remove_spell_effect_object();
    return 1;
}

public void warn_fading()
{
    query_effect_caster()->catch_tell("The burden of concealing your "+
    "presence starts to weigh more heavily on your mind.\n");
}


public int
start()
{
    if (!::start())
    {
        remove_spell_effect_object();
        return 0;
    }   

    object target;
    target = query_effect_target();

    target->catch_tell("Drawing inward, you attune your " 
        + "mind to the thoughts of those around you. With deep focus, you " 
        + "obscure your presence in the minds of your potential prey. You are " 
        + "hidden to those whose will you can manipulate.\n");

    move(target, 1);
    
    // Set up the obfuscate shadow
    if (!target->query_obfuscate_shadow())
    {
        setuid();
        seteuid(getuid());
        clone_object(SHADOW_DIR + "obfuscate_sh")->shadow_me(target);
    }
    
    target->start_obfuscate();

    total_duration = max(240, target->query_vamp_stat() * 5);
    total_duration = min(1200, total_duration); // capped at 20 minutes, reached at 240 stat

    set_dispel_time(total_duration);
    
    // Set up for incremental costs
    obfuscate_start_time = time();
    paid_mana = TOTAL_MANA_COST / 3;
    paid_blood = TOTAL_BLOOD_COST / 3;
    
    set_alarm(0.0, OBFUSCATE_INTERVAL_TIME, 
        &pay_obfuscate_cost(query_effect_target()));

    return 1;
}

public void init()
{
    ::init();
    add_action(stop,"stop");
}

public int
query_mana_cost()
{
    int elapsed_time, time_left, total_incremental, new_paid, cost;
    int original_paid;
    
    original_paid = TOTAL_MANA_COST / 3;
    total_incremental = TOTAL_MANA_COST - original_paid;
    elapsed_time = time() - obfuscate_start_time;
    time_left = total_duration - elapsed_time;

    // We calculate how much we should have paid by now.
    new_paid = total_incremental * elapsed_time / total_duration;
    new_paid += original_paid;
    cost = new_paid - paid_mana;
    paid_mana = new_paid;
    send_debug_message("obfuscate_obj", "Paying mana cost of "
        + cost + " for a total of " + paid_mana + " paid.");
    
    return cost;
}

public int
query_blood_cost()
{
    int elapsed_time, time_left, total_incremental, new_paid, cost;
    int original_paid;
    
    original_paid = TOTAL_BLOOD_COST / 3;
    total_incremental = TOTAL_BLOOD_COST - original_paid;
    elapsed_time = time() - obfuscate_start_time;
    time_left = total_duration - elapsed_time;

    // We calculate how much we should have paid by now.
    new_paid = total_incremental * elapsed_time / total_duration;
    new_paid += original_paid;
    cost = new_paid - paid_blood;
    paid_blood = new_paid;
    send_debug_message("obfuscate_obj", "Paying blood cost of "
        + cost + " for a total of " + paid_blood + " paid.");
    
    return cost;
}

public void
pay_obfuscate_cost(object player)
{
    int mana_cost = query_mana_cost();  
    int blood_cost = query_blood_cost();  
    if (player->query_mana() < mana_cost
        || player->query_blood() < blood_cost)
    {
        send_debug_message("obfuscate_obj", "Dispelling the "
            + "effect without enough mana.");
        // don't have enough mana, remove the object
        set_alarm(0.0, 0.0, &dispel_spell_effect(player));
        player->catch_tell("You are too weak to maintain your "
            + "ability to mentally hide yourself from others.\n");
        return;
    }
    
    player->add_mana(-mana_cost);
    player->add_blood(-blood_cost);
}
