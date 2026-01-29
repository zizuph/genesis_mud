#pragma strict_types

#include "../morgulmage.h"
#include <tasks.h>
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <files.h>

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "identify";

#include "generic_functions.c"
#include "generic_hooks.c"
#include "rank_limitation.c"


public void
config_identify_spell()
{
    set_spell_name("arhalgul");
    set_spell_desc("Attempt to reveal the secrets of an object");
    
    set_spell_element(SS_ELEMENT_AIR, 24);
    set_spell_form(SS_FORM_DIVINATION, 10);

    set_ability_stats(STAT_WEIGHTING);

    set_spell_class(SPELL_CLASS_2);
    set_spell_task(TASK_EASY);

    set_morgul_rank(2);

    set_spell_time_factor(adjust_time_by_rank);
}

public void
resolve_identify_spell(object caster, mixed * targets, int * resist, int result)
{
    MORGUL_MASTER->increase_activity(caster, ACTIVITY_SMALL_SPELL);
}

public void
hook_identify_describe_cast(object caster, object target)
{    
    string target_description = (environment(target) == caster)
        ? "something" : LANG_THESHORT(target);
        
    can_see_caster(caster)->catch_msg("Employing Dark Sorcery, "
        + QTNAME(caster) + " casts a spell on " + target_description
        + " to reveal " + ((living(target)) ? target->query_possessive() 
        : "its") + " secrets.\n");
        
    caster->catch_tell("Using the power the Dark Lord has bestowed upon "
        + "you, with the words \"Waro torgul! Arhalo furion rum!\", you "
        + "cast Arhalgul on " + LANG_THESHORT(target) + ".\n");
}

public void
hook_identify_success(object caster, object target, string id_message, int result)
{
    if (!objectp(caster) || !objectp(target))
    {
        return;
    }
    
    caster->catch_tell(id_message);
    target->appraise_object(caster->query_skill(query_identify_skill()) + result);
}

public void
hook_identify_failure(object caster, object target)
{
    if(IS_HERB_OBJECT(target)) 
    {
        caster->catch_tell(target->query_id_long());
    } else {
        caster->catch_tell("You fail to divine any magical properties.\n");
    }
}

public string *
query_identify_ingredients(object caster)
{
    return ({ "_arhal_charge" });
}
