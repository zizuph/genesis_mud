/*
 * Loremaster Haste Object
 *
 * This is the spell object for the dryad weapon when wielded by the elven
 * archers. This haste object adds haste when added into the inventory
 * and constantly checks to make sure that the weapon is wielded.
 *
 */

#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <files.h>

inherit "/d/Genesis/specials/std/spells/obj/haste_obj";

#include "/d/Genesis/specials/debugger/debugger_tell.h"

public object       gBow;

/*
 * Function name:   create_spell_object
 * Description:     Override this to customize properties for the spell object
 * Arguments:       None
 * Returns:         Nothing
 */
public void 
create_spell_object()
{
    // Don't call ::create_spell_object and don't call set_dispel_time. We don't
    // want this to dispel
    set_name("_loremaster_haste_object_");
    set_short("loremaster haste spell object");    
    set_long("This is the loremaster haste object. It causes one to move "
    + "faster.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object created for the dryad bow "
    + "that archers get from the guru quest.\n");
    
    set_spell_effect_desc("loremaster haste");
    
    set_spell_effect_input(7); // 7% combat aid translates to around 23 haste
    set_maintain_mana(0); // there is no cost to keep and maintain this effect
} /* create_spell_object */

/*
 * Function name:   hook_spell_effect_started
 * Description:     Override this to customize the message when this spell
 *                  effect is added to th target.
 * Arguments:       None
 * Returns:         Nothing
 */
public void
hook_spell_effect_started()
{
    query_effect_target()->catch_msg("You are enveloped in a gentle breeze, "
    + "and you can feel yourself moving at a slightly elevated pace.\n");
    // Don't do anything to indicate that there is haste present
} /* hook_spell_effect_started */

/*
 * Function name:   hook_spell_effect_ended
 * Description:     Override this to customize the message when this spell
 *                  effect is dispelled.
 * Arguments:       None
 * Returns:         Nothing
 */
public void
hook_spell_effect_ended()
{
    query_effect_target()->catch_msg("The power of the " + gBow->short() + " "
    + "fades and you can feel yourself moving slower.\n");
    // Don't do anything to indicate that there is haste ending
} /* hook_spell_effect_ended */

/*
 * Function name:   hook_spell_effect_warn_fading
 * Description:     Override this to customize the message for when the effect
 *                  has only a minute left.
 * Arguments:       None
 * Returns:         Nothing
 */
public void
hook_spell_effect_warn_fading()
{
    // Don't do anything to indicate that haste is about to end
} /* hook_spell_effect_warn_fading */

/* 
 * Function name:   hook_spell_effect_not_maintained
 * Description:     Override this to describe the effect when the caster cannot
 *                  maintain the effect.
 * Arguments:       None
 * Returns:         Nothing
 */
public void
hook_spell_effect_not_maintained()
{
    // Don't do anything to indicate that it's not being maintained
} /* hook_spell_effect_not_maintained */

/* 
 * Function name:   is_valid_haste_target
 * Description:     Basically just checks whether this is a living object that
 *                  we can add haste to.
 * Arguments:       None
 * Returns:         Nothing
 */
public int
is_valid_haste_target(object player)
{
    if (!objectp(player))
        return 0;
    
    if (IS_LIVING_OBJECT(player))
        return 1;
    
    return 0;
} /* is_valid_haste_target */

/*
 * Function name:   set_hoopak_object
 * Description:     sets the bow object that cloned this haste object.
 * Arguments:       None
 * Returns:         Nothing
 */
public void
set_hasted_object(object bow)
{
    gBow = bow;
} /* set_hasted_object */

/*
 * Function name:   query_hoopak_object
 * Description:     Returns the bow object that cloned this haste object
 * Arguments:       None
 * Returns:         (object) the wielded bow
 */
public object
query_hasted_object()
{
    return gBow;
} /* query_hasted_object*/

/*
 * Function name:   check_for_valid_wielded
 * Description:     Checks to make sure that the bow wielder is the same as the
 *                  container of this person.
 * Arguments:       None
 * Returns:         Nothing
 */
public void
check_for_valid_wielded()
{
    if (!objectp(gBow)  || gBow->query_wielded() != environment(this_object()))
        set_alarm(0.0, 0.0, remove_object);
} /* check_for_valid_wield */

/*
 * Function name:   enter_env
 * Description:     This function is called whenever this object enters a new
 *                  environment. If it's a living being that is wielding the bow
 *                  then we set the appropriate variables and start the spell
 *                  effect.
 * Arguments:       1. (object) inv  - the environment this object is entering.
 *                  2. (object) from - the possible place this object came from.
 * Returns:         Nothing
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
} /* enter_env */
