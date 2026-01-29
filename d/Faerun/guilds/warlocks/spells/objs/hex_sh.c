/*
*  Base for the Hex spell
*
*  Nerull 2018
*/

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "objs/shadow_base_sh";

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>
#include <state_desc.h>

string *health_state;


/*
* Function:    initialize_shadow
* Description: Should do all the initialization effects for this
*              particular shadow. Shadows derived from this one should
*              override this.
*/
public void
initialize_shadow(object spell_object, mapping spell_input)
{
    spell_object->set_spell_effect_desc("Hex");
}


int
query_hp()
{
    health_state = SD_HEALTH;

    /* trick ourself into thinking we are almost dead */
    if (file_name(previous_object()) == "/cmd/live/state")
    {
        int illusion_hp = shadow_who->query_max_hp();
        
        illusion_hp = (illusion_hp / ((random(10) + 4)));
        
        return illusion_hp;
    }

    return shadow_who->query_hp();
}


/*
* Function:    hook_spell_effect_started
* Description: Override this to customize the message when this spell effect
*              is added to th target.
*/
public void
hook_spell_effect_started(object spell_object)
{
    object target = spell_object->query_effect_target();

    if (objectp(target))
    {
        target->catch_tell("You feel as if a curse is taking "
        +"effect on you!\nYou feel dizzy and very weak!\n");
    }
}


/*
* Function:    hook_spell_effect_ended
* Description: Override this to customize the message when this spell effect
*              is dispelled.
*/
public void
hook_spell_effect_ended(object spell_object)
{
    object target = spell_object->query_effect_target();

    if (objectp(target))
    {
        target->catch_tell("The curse lifts! You feel better!\n");
    }
}


/*
* Function:    hook_spell_effect_warn_fading
* Description: Override this to customize the message for when
*              the effect has only a minute left.
*/
public void
hook_spell_effect_warn_fading(object spell_object)
{
    object target = spell_object->query_effect_target();

    if (objectp(target))
    {
        target->catch_tell("You sense that the curse bestowed upon you "
        +"is slowly starting to fade away.\n");
    }
}