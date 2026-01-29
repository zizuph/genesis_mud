/**********************************************************************
 * - aura.c                                                         - *
 * - Eil-Galiath alignment spell                                    - *
 * - Created by Damaris 2/2002                                      - *
 **********************************************************************/ 
#pragma strict_types

inherit "/d/Genesis/newmagic/spell";

#include <ss_types.h>
#include <tasks.h>
#include <stdproperties.h>
#include <composite.h>
#include <filter_funs.h>
#include <macros.h>

public void
create_spell()
{
    set_spell_name("aura");
    set_spell_desc("See someone's aura.");
    set_spell_target(spell_target_one_present_living);

    set_spell_time(5);
    set_spell_mana(30);
    set_spell_task(TASK_ROUTINE - (caster->query_stat(SS_RACE) / 2));    
    set_spell_element(SS_ELEMENT_LIFE, 20);
    set_spell_form(SS_FORM_DIVINATION, 20);
    set_spell_ingredients(0);
    set_spell_resist(spell_resist_aura);
    set_spell_target_verify(spell_verify_present);
    set_spell_peaceful(1);


}

/*
 * Function name: concentrate_msg
 * Description:   Give messages indicating that spell concentration has begun
 * Arguments:     1. (object)   The caster
 *                2. (object *) The targets
 *                3. (string)   The arguments passed to the "cast" command
 */
public void
concentrate_msg(object caster, object *targets, string arg)
{

    caster->catch_tell("You close your eyes and concentrate upon the "+
      "power of the mystic vine.\n");
    FILTER_IS_SEEN(caster, FILTER_PLAYERS(all_inventory(environment(caster)))
      - ({ caster }))->catch_msg(QCTNAME(caster) +" starts concentrating "+
      "deeply.\n");
}
/* 
 * Function name: break_spell
 * Description:   Take special actions when casting is broken.
 * Arguments:     1. (object) The caster
 *                2. (object) The object responsible for breaking the spell
 */
public void
break_spell(object caster, object breaker)
{
    caster->catch_tell("Your concentration is broken and you feel the "+
      "power of the mystic vine slip away.\n");
    FILTER_IS_SEEN(caster, FILTER_PLAYERS(all_inventory(environment(caster)))
          - ({ caster }))->catch_msg(QCTNAME(caster) +" loses "+
          "concentration.\n");
}

/*
 * Function name: abort_spell
 * Description:   Take special actions when casting is aborted
 * Arguments:     1. (object) The caster.
 */
public void
abort_spell(object caster)
{
    caster->catch_tell("You open your eyes and relax.\n");
    FILTER_IS_SEEN(caster, FILTER_PLAYERS(all_inventory(environment(caster)))
          - ({ caster }))->catch_msg(QCTNAME(caster) +" relaxes.\n");
}
