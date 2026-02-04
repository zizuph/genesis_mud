/*
 * Minstrel concerto shadow.
 *
 */
 
#pragma strict_types
#pragma save_binary

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "objs/shadow_base_sh";

#include "/d/Terel/common/terel_defs.h"
#include "../../guild_defs.h"

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>
#include <wa_types.h>

int skill_bonus, spell_power;

public int
query_has_concerto_shadow()
{
     return 1;
}

/*
 * Function:    initialize_shadow
 * Description: Should do all the initialization effects for this 
 *              particular shadow. Shadows derived from this one should
 *              override this.
 */
public void
initialize_shadow(object spell_object, mapping spell_input)
{
    spell_object->set_name("_concerto_spell_obj_");
    spell_object->set_spell_effect_desc("song of inspiration");
    spell_object->set_spell_effect_notes("This Song of Power focuses " +
        "the mind of the Minstrel on their technique, enhancing their " +
        "instrumental and singing skills according to their Minstrel " +
        "rank.\n\nAs with all Songs of Power inspired by a " +
        "Lost Muse, only one can be effectively performed at a time.\n");   
    spell_power = spell_object->query_spell_effect_power();
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

    int caster_rank = target->query_guild_level_lay(); 
    skill_bonus = (min(40, caster_rank));

    if (objectp(target))
    {
        target->catch_tell("You feel your entire being focus on the music. " +
            "Nothing but the music. You feel your fingers relax and your posture " +
            "straighten as you prepare for the perfect performance. It is time to play.\n");
        tell_room(environment(target), QCTPNAME(target)+ " posture relaxes as " +
            target->query_pronoun()+ " prepares " +target->query_objective()+ 
            "self to perform.\n", ({ target }));
    }    

    target->set_skill_extra(SG_INSTRUMENTAL, 
         target->query_skill_extra(SG_INSTRUMENTAL) + skill_bonus);
    target->set_skill_extra(SG_VOCAL, 
         target->query_skill_extra(SG_VOCAL) + skill_bonus);

    spell_power = spell_object->query_spell_effect_power();
    // Power determines how long the spell lasts
    // int duration = ftoi(itof(spell_power) * 10.0);
    // spell_object->set_dispel_time(duration);

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

    target->set_skill_extra(SG_INSTRUMENTAL, 
         target->query_skill_extra(SG_INSTRUMENTAL) - skill_bonus);
    target->set_skill_extra(SG_VOCAL, 
         target->query_skill_extra(SG_VOCAL) - skill_bonus);

    if(target->query_ghost())
        return;

    if (objectp(target))
    {
        target->catch_tell("The effects of Concerto end.\n");
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
        target->catch_tell("You sense Concerto is soon to end.\n");
    }
}

/* 
 * Function:    hook_spell_effect_not_maintained
 * Description: Override this to describe the effect when the caster
 *              cannot maintain the effect.
 */
public void
hook_spell_effect_not_maintained(object spell_object)
{
    object caster = spell_object->query_effect_caster();
    
    if (objectp(caster))
    {
        caster->catch_tell("You are mentally unable to maintain "
            + "Concerto.\n");
    }    
}
