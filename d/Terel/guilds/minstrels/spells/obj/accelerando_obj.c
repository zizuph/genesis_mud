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
inherit SPELL_DIR + "objs/haste_obj";

// sometimes query_spell_effect_still_valid is called
// multiple times before the object is removed, resulting
// in multiple removals of quickness. This is to ensure
// that check only happens once.
int song_maintained = 1;

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_accelerando_object_");
    set_short("Minstrel accelerando song object");    
    set_long("This is the Minstrel accelerando song object, based on the " +
        "standard haste spell's object.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object created by " +
        "the accelerando song.\n");
    set_spell_effect_desc("song of celerity"); 
    set_spell_effect_notes("This Song of Power inspires a Minstrel's " +
        "team to rapidly quicken their attacks. However that inspiration " +
        "fades shortly after team members move away from the presence " +
        "of the Minstrel.\n\nAs with all Songs of Power inspired by a " +
        "Lost Muse, only one can be effectively performed at a time.\n");  

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

    if((present(caster, environment(target))))
    {
        return 1;
    }
    else
    {
        if(!song_maintained)
        {
            return 1;
        }
        song_maintained = 0;
        return 0;
    }

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
        target->catch_tell("You feel your body quicken to the pace of " +
            "the rapid Song of Celerity.\n");
        tell_room(environment(target), "You perceive " +QTNAME(target) + " moving "
            + "and reacting more rapidly than before.\n", ({ target }));
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
            caster->catch_tell("You feel the quickness from your Song " +
               "of Celerity leave " +target->query_the_name(caster)+ ".\n");
            target->catch_tell("You feel your pace slow as the Song " +
               "of Celerity ends.\n");
        }
        else
            caster->catch_tell("You feel your pace slow as the Song " +
               "of Celerity ends.\n");
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
        target->catch_tell("You feel the Song of Celerity is getting close to ending.\n");
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
            "the Song of Celerity.\n");
    }    
}
