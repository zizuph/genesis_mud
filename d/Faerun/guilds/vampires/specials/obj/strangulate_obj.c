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
    set_name("vampires_strangulate");
    add_name( ({"vampires_strangulate_object" }) );
    set_short("hidden vampires strangulate object");    
    set_long("This is a hidden vampires strangulate object.\n");
    
    setuid();
    seteuid(getuid());

    set_effect_combat_aid(90);
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
    
    object silence_cooldown_obj;
    
    if (objectp(enemy = environment(this_object())) && living(enemy))
    {
        shadow = clone_object(VAMPIRES_GUILD_DIR 
        + "specials/obj/strangulate_sh");
        
        shadow->shadow_me(enemy);
        
        enemy->init_strangulate_shadow();
        
        // 90 caid is 50 seconds duration. 
        set_alarm(STRANGULATE_DURATION, 0.0, &remove_object());
    }
    
    return result;
}


public void
remove_object()
{
    object enemy;
    
    if (objectp(enemy = environment(this_object())) && living(enemy))
    {
        enemy->remove_strangulate_shadow();
    }
    
    ::remove_object();
}