/*
 *  As part of the re-balancing of magic guilds following white 
 *  hit changes, added +40 defensive skill benefit 
 *  (then removed it based on feedback... they will have an 
 *   increase in caid from 80 to 130 instead)
 *
 *  Arman, November 2021
 *
 */

#pragma strict_types
#pragma save_binary

#include <macros.h>
#include <ss_types.h>

#include "/d/Genesis/specials/local.h"
inherit SPELL_OBJ_DIR + "stoneskin_obj";

#define _NO_PREP_TIME_ADJUSTMENT
#include "../generic_functions.c"

// #define SS_DEFENCE_BONUS 40

public void 
create_spell_object()
{
    set_name("_ringurth_object_");
    set_short("stoneskin spell object");    
    set_long("This is the standard stoneskin spell's object. It turns "
        + "one's skin to stone.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the morgul mage ringurthstoneskin spell.\n");
    set_spell_effect_desc("Chill of Death");    
}

public void
hook_spell_effect_started()
{
    object target = query_effect_target();

    if (objectp(target))
    {
        target->catch_tell("A cloud appears and envelopes you in response.\n");
        can_see_caster(target)->catch_msg("You shiver as the chill of "
            + "death surrounds " + QTNAME(target) + " and pushes warmth "
            + "out of your bones.\n", target);
    }    

//    target->set_skill_extra(SS_DEFENCE, 
//         target->query_skill_extra(SS_DEFENCE) + SS_DEFENCE_BONUS);
}

public void
hook_spell_effect_ended()
{
    object target = query_effect_target();

    if (objectp(target))
    {
        target->catch_tell("The chill of death departs silently, "
            + "leaving you feeling less protected.\n");
        can_see_caster(target)->catch_msg("Warmth creeps back into your "
            + "bones as the chill of death surrounding "
            + QTNAME(target) + " departs.\n", target);
    }

//    target->set_skill_extra(SS_DEFENCE, 
//         target->query_skill_extra(SS_DEFENCE) - SS_DEFENCE_BONUS);
}

public void
hook_spell_effect_warn_fading()
{
    object target = query_effect_target();
    
    if (objectp(target))
    {
        target->catch_tell("You feel the effects of ringurth lessen.\n");
    }
}

public void
hook_spell_effect_not_maintained()
{
    object caster = query_effect_caster();
    
    if (objectp(caster))
    {
        caster->catch_tell("Mentally drained, you lose control of "
            + "the Chill of Death.\n");
    }    
}

public string
query_stoneskin_subloc_description(object on, object for_obj)
{
    if (for_obj == on)
        return "A cold, comforting shadow surrounds your body.\n";
    else
        return "A cold, ever-shifting shadow surrounds "
            + on->query_possessive() + " body.\n";
}
