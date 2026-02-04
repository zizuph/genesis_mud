/* 
 * Minstrel accelerando team quickness object
 */

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include "/d/Terel/common/terel_defs.h"
#include "../../guild_defs.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "unfinished/regen_mana_obj";

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_animato_object_");
    set_short("Minstrel animato song object");    
    set_long("This is the Minstrel animato song object, based on the " +
        "standard mana regen spell object.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object created by " +
        "the animato song.\n");
    set_spell_effect_desc("song of invigoration"); 
    set_spell_effect_notes("This Song of Power refreshes a Minstrel's " +
        "team, improving their mental regeneration. However that invigoration " +
        "fades shortly after team members move away from the presence " +
        "of the Minstrel.\n\nAs with all Songs of Power inspired by a " +
        "Lost Muse, only one can be effectively performed at a time.\n");  

    set_element_skill_effect(SG_INSTRUMENTAL); 
}

/*
 * Function:    query_spell_effect_still_valid()
 * Description: For a maintained spell effect, this allows the spell
 *              effect to determine whether it is still valid or not.
 *              In the maintain_spell_effects function, it will dispel
 *              the effect object if it determines that it is no longer
 *              valid.
 */
public int
query_spell_effect_still_valid()
{
    object target = query_effect_target();
    object caster = query_effect_caster();

    if (!target)
        return 0;
    if(present(caster, environment(target)))
        return 1;
    else
        return 0;
}

/*
 * Function:    hook_spell_effect_started
 * Description: Override this to customize the message when this spell effect
 *              is added to th target.
 */
public void
hook_spell_effect_started()
{
    object target = query_effect_target();
    object caster = query_effect_caster();

    if (objectp(target))
    {
        target->catch_tell("You feel mentally refreshed by " +
            "the Song of Invigoration.\n");
        tell_room(environment(target), QCTNAME(target) + " looks "
            + "mentally invigorated!\n", ({ target }));
    }  
}

/*
 * Function:    hook_spell_effect_ended
 * Description: Override this to customize the message when this spell effect
 *              is dispelled.
 */
public void
hook_spell_effect_ended()
{
    object target = query_effect_target();
    object caster = query_effect_caster();

    if(target->query_ghost())
        return;

    if (objectp(target))
    {
        if(caster != target)
        {
            caster->catch_tell("You feel the invigoration from your Song " +
               "of Power leave " +target->query_the_name(caster)+ ".\n");
            target->catch_tell("You feel less mentally invigorated as the Song " +
               "of Power ends.\n");
        }
        else
            caster->catch_tell("You feel less mentally invigorated as the Song " +
               "of Power ends.\n");
    }

}

/*
 * Function:    hook_spell_effect_warn_fading
 * Description: Override this to customize the message for when
 *              the effect has only a minute left.
 */
public void
hook_spell_effect_warn_fading()
{
    object target = query_effect_target();
    
    if (objectp(target))
    {
        target->catch_tell("You feel the Song of Invigoration is getting close to ending.\n");
    }
}

/* 
 * Function:    hook_spell_effect_not_maintained
 * Description: Override this to describe the effect when the caster
 *              cannot maintain the effect.
 */
public void
hook_spell_effect_not_maintained()
{
    object caster = query_effect_caster();
    
    if (objectp(caster))
    {
        caster->catch_tell("Mentally drained, you are unable to continue performing " +
            "the Song of Invigoration.\n");
    }    
}

/*
 * Function:    hook_describe_regeneration
 * Description: Mask this to give messages for when the target gets healed
 *              by the regeneration effect.
 */
public void
hook_describe_regeneration(object target, int amount)
{     
    object caster = query_effect_caster();

    // DEBUG("Mana regen amount: " +amount+ ".");

    if(random(3))
        return;

    if(target == caster)
        target->catch_tell("You feel mentally refreshed by your invigorating song.\n");
    else 
        target->catch_tell("You feel mentally refreshed by " +
            caster->query_the_possessive_name(target)+ " invigorating song.\n");
}

/*
 * Function:    query_mana_regen_subloc_description
 * Description: When someone examines a person with this spell effect,
 *              they will see whatever is returned by this function.
 */
public string
query_mana_regen_subloc_description(object on, object for_obj)
{
    if (for_obj == on)
	return  "You are mentally invigorated by a song of Power.\n";
    else
	return capitalize(on->query_pronoun()) + " looks " +
	"mentally invigorated.\n";
}
