#pragma strict_type

inherit "/d/Genesis/specials/std/effect_obj_base";

#include "../../guild.h"
#include <macros.h>
#include <options.h>
#include <formulas.h>
#include <files.h>
#include <adverbs.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>

mixed   rage_alarm;

/*
 * Function     : create_effect
 * Description  : The create function called for objects that inherit this
 * Arguments    : none
 * Returns      : nothing
 */
public void
create_effect()
{
    set_name("fireknives_blind");
    add_name( ({"fireknives_blind_object" }) );
    set_short("hidden fireknives blind object");    
    set_long("This is a hidden fireknives blind object.\n");
    
    setuid();
    seteuid(getuid());

    set_effect_combat_aid(90);
}


public void
remove_object()
{
    object enemy;
    
    if (objectp(enemy = environment(this_object())) && living(enemy))
    {
        enemy->remove_blind_shadow();
    }
    
    ::remove_object();
}


/*
 * Function name: start
 * Description;   Start up the spell effect.  This should be redefined
 *                to provide specific behaviour for a given spell
 *                effect.
 * Returns:       1/0 - effect started/not started
 */
public int
start()
{
    int     result = ::start();
    object  shadow, enemy;
    
    object blind_cooldown_obj;
    
    if (objectp(enemy = environment(this_object())) && living(enemy))
    {
        shadow = clone_object(FIREKNIVES_GUILD_DIR + "specials/obj/blind_sh");
        shadow->shadow_me(enemy);
        
        enemy->init_blind_shadow();
        
        set_alarm(BLIND_DURATION, 0.0, &remove_object());
    }
    
    return result;
}


