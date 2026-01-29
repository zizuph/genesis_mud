/*
 * blind_obj_base
 *
 * This is the base object to inherit for all blinds.
 *
 */
#pragma strict_types

#include "defs.h"
#include <tasks.h>
#include <stdproperties.h>

inherit EFFECT_BASE_OBJ;

// Prototypes
// Global Variables
static status       gHastedBlind;
static int          gBlindCycle,
                    gBlindChance,
                    gBlindToHit;
static function     gBlindBegin,
                    gBlindEnded,
                    gBlindFailed;


public function
query_hook_blind_begin()
{
    return gBlindBegin;
}

public void
set_hook_blind_begin(function func)
{
    gBlindBegin = func;
}

/*
 * Function Name:   hook_blind_begin
 * Description:     The text displayed when the blind begins.
 * Arguments:       (object) actor - The actor of the ability
 *                  (object) target - The target of the blind
 *                  (status) 1 - target is already blinded
 *                           0 - target is not previously blinded
 * Returns:         Nothing
 */
public void
hook_blind_begin(object actor, object target, status blinded)
{
} /* hook_blind_begin */

public function
query_hook_blind_ended()
{
    return gBlindEnded;
}

public void
set_hook_blind_ended(function func)
{
    gBlindEnded = func;
}

/*
 * Function Name:   hook_blind_ended
 * Description:     The text displayed when the blind ends.
 * Arguments:       (object) actor - The actor of the ability
 *                  (object) target - The target of the blind
 *                  (status) 1 - target is still blinded
 *                           0 - target is no longer blinded
 * Returns:         Nothing
 */
public void
hook_blind_ended(object actor, object target, status blinded)
{
} /* hook_blind_ended */

public function
query_hook_blind_failed()
{
    return gBlindFailed;
}

public void
set_hook_blind_failed(function func)
{
    gBlindFailed = func;
}


/*
 * Function Name:   hook_blind_failed
 * Description:     The text displayed when the blind fails to apply.
 * Arguments:       (object) actor - The actor of the ability
 *                  (object) target - The target of the blind
 * Returns:         Nothing 
 */
public void
hook_blind_failed(object actor, object target)
{
} /* hook_blind_failed */

/*
 * Function Name:   query_blind_cycle
 * Description:     
 * Arguments:       None
 * Returns:         (int) - 
 */
public int
query_blind_cycle()
{
    return gBlindCycle;
} /* query_blind_cycle */

/*
 * Function Name:   set_blind_cycle
 * Description:     
 * Arguments:       (int) cycle - 
 * Returns:         Nothing
 */
public void
set_blind_cycle(int cycle)
{
    gBlindCycle = cycle;
} /* set_blind_cycle */

/*
 * Function Name:   query_blind_chance
 * Description:     
 * Arguments:       None
 * Returns:         (int) - 
 */
public int
query_blind_chance()
{
    return gBlindChance;
} /* query_blind_chance */

/*
 * Function Name:   set_blind_chance
 * Description:     
 * Arguments:       (int) chance - 
 * Returns:         Nothing
 */
public void
set_blind_chance(int chance)
{
    gBlindChance = max(100, min(chance, 0));
} /* set_blind_chance */

/*
 * Function Name:   query_blind_tohit
 * Description:     
 * Arguments:       None
 * Returns:         (int) - 
 */
public int
query_blind_tohit()
{
    return gBlindToHit;
} /* query_blind_tohit */

/*
 * Function Name:   set_blind_tohit
 * Description:     
 * Arguments:       (int) tohit - 
 * Returns:         Nothing
 */
public void
set_blind_tohit(int tohit)
{
    gBlindToHit = tohit;
} /* set_blind_tohit */

/*
 * Function Name:   query_blind_skills
 * Description:     Returns the skills that are used in calculating the strength
 *                  of the blind.
 * Arguments:       None
 * Returns:         (mixed) - Returns the blind skills
 */
public mixed
query_blind_skills()
{
    return query_effect_skills();
} /* query_blind_skills */

/*
 * Function Name:   set_blind_skills
 * Description:     Sets the skills that will be used in calculating the 
 *                  strength of the blind.
 * Arguments:       (mixed) skills - 
 * Returns:         Nothing
 */
public nomask void
set_blind_skills(mixed skills)
{
    set_effect_skills(skills);
} /* set_blind_skills */

/*
 * Function Name:   query_blind_stats
 * Description:     Returns the stats that are used in calculating the strength
 *                  of the blind.
 * Arguments:       None
 * Returns:         (mixed) - Returns the blind stats
 */
public mixed
query_blind_stats()
{
    return query_effect_stats();
} /* query_blind_stats */

/*
 * Function Name:   set_blind_stats
 * Description:     Sets the stats that will be used in calculating the strength
 *                  of the blind.
 * Arguments:       (mixed) stats - the stats used to determine the success
 * Returns:         Nothing
 */
public nomask void
set_blind_stats(mixed stats)
{
    set_effect_stats(stats);
} /* set_blind_stats */

/*
 * Function Name:   query_blind_combat_aid
 * Description:     Returns the combat aid for the blind.
 * Arguments:       None
 * Returns:         (int) - amount of combat aid
 */
public nomask int
query_blind_combat_aid(object player)
{
    return query_effect_combat_aid(player);
} /* query_blind_combat_aid */

/*
 * Function Name:   set_blind_combat_aid
 * Description:     Sets the combat aid for the blind
 * Arguments:       (mixed) caid - amount of combat aid
 * Returns:         Nothing
 */
public nomask void
set_blind_combat_aid(int caid)
{
    set_effect_combat_aid(caid);
} /* set_blind_combat_aid */

/*
 * Function Name:   query_blind_hasted
 * Description:     Returns the state of the haste status.
 * Arguments:       None
 * Returns:         (status) 1 - The ability is hasted
 *                           0 - The ability is not hasted 
 */
public status
query_blind_hasted()
{
    return gHastedBlind;
} /* query_blind_hasted */

/*
 * Function Name:   set_blind_hasted
 * Description:     Set whether the blind is affected by haste or not.
 * Arguments:       (status) state - the state of the haste status
 * Returns:         Nothing
 */
public status
set_blind_hasted(status state)
{
    gHastedBlind = state;
} /* set_blind_hasted */

/*
 * Function Name:   query_blind_valid
 * Description:     Validation function to see whether this blind object
 *                  is valid in the current situation
 * Arguments:       (object) player - player who is blinded
 * Returns:         (status) 0 - invalid
 *                  (status) 1 - valid
 */
public status
query_blind_valid(object player)
{
    return 1;
} /* query_blind_valid */

/*
 * Function Name:   create_blind
 * Description:     The create function called for objects that inherit this
 * Arguments:       None
 * Returns:         Nothing
 */
public void
create_blind()
{
} /* create_blind */

/*
 * Function Name:   create_effect
 * Description:     The base constructor for effects
 * Arguments:       None
 * Returns:         Nothing
 */
public nomask void
create_effect()
{
    setuid();
    seteuid(getuid());
    
    set_blind_cycle(30);
    set_blind_chance(100);
    set_blind_tohit(100);
    set_blind_hasted(0);
    set_blind_combat_aid(135);
    set_blind_skills(({ SKILL_VALUE, 100 }));
    set_blind_stats(({ SKILL_VALUE, 100 }));
    set_hook_blind_begin(hook_blind_begin);
    set_hook_blind_ended(hook_blind_ended);
    set_hook_blind_failed(hook_blind_failed);
    
    create_blind();
    
    set_name("_blind_base_object_");
    set_short("blind object");    
    set_long("This is the standard blind object.\n");

    add_prop(OBJ_S_WIZINFO, "This is an object created by a blind ability.\n");
    
} /* create_effect */

/*
 * Function name:   add_blind_effect
 * Description:     Adds the effect to the target and prints hooks based on the
 *                  success.
 * Arguments:       (object) target
 * Returns:         (status) 1 - effect successfully added
 *                           0 - effect failed to be added
 */
public nomask status
add_blind_effect(object target)
{
    status      blinded = 1;
    function    func;
    
    if (objectp(target) && living(target))
    {
        if (!objectp(query_effect_caster()))
            return 0;
        
        if (environment() != query_effect_target())
            move(query_effect_target(), 1);
        
        if (!sizeof(target->query_blind_effects()))
        {
            blinded = 0;
            object shadow = clone_object(BLIND_SH);
            shadow->shadow_me(target);
            add_shadow_to_list(shadow);
        }
        
        if (target->add_blind_effect(this_object()))
        {
            if (functionp(func = gBlindBegin))
                applyv(func, ({ query_effect_caster(), target, blinded }));
            
            return 1;
        }
    }
    
    if (functionp(func = gBlindFailed))
        applyv(func, ({ query_effect_caster(), target }));
    
    return !!remove_object();
} /* add_blind_effect */

/*
 * Function name:   remove_blind_effect
 * Description:     Removes the blind effect from the affected target and prints
 *                  corresponding hook.
 * Arguments:       (object) target - the one affected by blind
 * Returns:         (status) 1 - effect successfully removed
 *                           0 - effect failed to be removed
 */
public status
remove_blind_effect(object target)
{
    object *effects = ({});
    status  blinded = 0;
    
    if (!objectp(target))
        return 0;
    
    if (target->remove_blind_effect(this_object()))
    {
        effects = target->query_blind_effects();
        effects -= ({ this_object() });
        if (sizeof(effects))
            blinded = 1;
        
        function func;
        if (functionp(func = gBlindEnded))
            applyv(func, ({ query_effect_caster(), target, blinded }));
        
        return !!remove_object();
    }
    
    return 0;
} /* remove_blind_effect */

/*
 * Function name:   dispel_effect
 * Description:     Cause this effect to be dispelled. If the effect is removed,
 *                  1 should be returned, else 0.  Returning 0 should be a rare
 *                  ocurance, since there generally should not be effects that
 *                  cannot be dispelled.
 * Arguments:       (object) dispeler - the person responsible for dispelling
 *                  the effect.
 * Returns:         (int) 1/0 - effect dispelled/not dispelled
 */
varargs public int
dispel_effect(object dispeler)
{
    return !!remove_blind_effect(query_effect_target());
} /* dispel_effect */

/*
 * Function Name:   start
 * Description:     Start up the effect. We override this method so that we can
 *                  add the blind effect.
 * Arguments:       None
 * Returns:         (int) 1 - effect started
 *                  (int) 0 - effect did not start
 */
public int
start()
{
    int result = ::start();
    if (!result)
        return result;
    
    return add_blind_effect(query_effect_target());
} /* start */

/*
 * Function name:   remove_object
 * Description:     Called upon object destruction. This will need to be done so
 *                  that the shadow can be properly removed when there are no
 *                  more effects.
 * Arguments:       None
 * Returns:         Nothing
 */
public void
remove_object()
{
    foreach(object shadowobj: query_shadow_list())
    {
        remove_blind_effect(shadowobj->query_shadow_who());
    }
    
    ::remove_object();
} /* remove_object */


/*
 * Function name:   set_dispel_time
 * Description;     Creates a timer that will dispel the effect
 * Arguments:       (int) i - number of seconds before the effect vanishes                
 * Returns:         Nothing
 */
public void
set_dispel_time(int i)
{
    set_blind_cycle(i);
} /* set_dispel_time */