/*
 * Hoopak Haste Object
 *
 * This is the spell object for the hoopak weapon when wielded by
 * kenders. This haste object adds haste when added into the inventory
 * and constantly checks to make sure that the weapon is wielded.
 *
 * Created by Petros, February 2012
 */

#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <files.h>

inherit "/d/Genesis/specials/std/spells/obj/haste_obj";

#include "/d/Genesis/specials/debugger/debugger_tell.h"

public object       gHoopakObject = 0;

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    // Don't call ::create_spell_object and don't call set_dispel_time. We don't
    // want this to dispel
    set_name("_hoopak_haste_object_");
    set_short("hoopak haste spell object");    
    set_long("This is the hookpak haste object. It causes "
        + "one to move faster.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created to give haste to kenders who are " +
                            "wielding the hoopak.\n");
    set_spell_effect_desc("hoopak haste");
    
    set_spell_effect_input(30); // 30% combat aid translates to around 60 quickness
    set_maintain_mana(0); // there is no coste to keep and maintain this effect
}

/*
 * Function:    hook_spell_effect_started
 * Description: Override this to customize the message when this spell effect
 *              is added to th target.
 */
public void
hook_spell_effect_started()
{
    // Don't do anything to indicate that there is haste present
}

/*
 * Function:    hook_spell_effect_ended
 * Description: Override this to customize the message when this spell effect
 *              is dispelled.
 */
public void
hook_spell_effect_ended()
{
    // Don't do anything to indicate that there is haste ending
}

/*
 * Function:    hook_spell_effect_warn_fading
 * Description: Override this to customize the message for when
 *              the effect has only a minute left.
 */
public void
hook_spell_effect_warn_fading()
{
    // Don't do anything to indicate that haste is about to end
}

/* 
 * Function:    hook_spell_effect_not_maintained
 * Description: Override this to describe the effect when the caster
 *              cannot maintain the effect.
 */
public void
hook_spell_effect_not_maintained()
{
    // Don't do anything to indicate that it's not being maintained
}

/* 
 * Function:    is_valid_haste_target
 * Description: Basically just checks whether this is a living object
 *              that we can add haste to.
 */
public int
is_valid_haste_target(object player)
{
    if (!objectp(player))
    {
        return 0;
    }
    
    if (IS_LIVING_OBJECT(player))
    {
        return 1;
    }
    
    return 0;
}

/*
 * Function:    set_hoopak_object
 * Description: sets the hoopak object that cloned this haste
 *              object.
 */
public void
set_hoopak_object(object wep)
{
    gHoopakObject = wep;
}

/*
 * Function:    query_hoopak_object
 * Description: returns the hoopak object that cloned this haste object
 */
public object
query_hoopak_object()
{
    return gHoopakObject;
}

/*
 * Function:    check_for_valid_wielded
 * Description: Checks to make sure that the hoopak wielder is the same
 *              as the container of this person.
 */
public void
check_for_valid_wielded()
{
    if (!objectp(gHoopakObject) 
        || gHoopakObject->query_wielded() != environment(this_object()))
    {
        send_debug_message("hoopak_haste", "Destroying the haste object because it is invalid.\n"); 
        set_alarm(0.0, 0.0, remove_object);
    }
}

/*
 * Function name: enter_env
 * Description  : This function is called whenever this object enters a new
 *                environment. If it's a living being that is wielding the hoopak
 *                then we set the appropriate variables and start the spell
 *                effect.
 * Arguments    : object inv  - the environment this object is entering.
 *                object from - the possible place this object came from.
 */
void
enter_env(object inv, object from)
{
    ::enter_env(inv, from);

    if (is_valid_haste_target(inv))
    {
        set_spell_effect_caster(inv);
        set_spell_effect_target(inv);
        setup_spell_effect();
        set_alarm(5.0, 5.0, &check_for_valid_wielded());
    }
}
