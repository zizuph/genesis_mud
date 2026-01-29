#pragma strict_types

#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include "../morgulmage.h"
#include "/d/Gondor/guilds/morgulmage/morgul_corpse.h"

inherit "/d/Genesis/specials/std/spells/at_will_harm";

#define _NO_DEFAULT_FAILURE_MESSAGE

#include "generic_functions.c"
#include "generic_hooks.c"
#include "rank_limitation.c"

#define NARK_LOG ("/d/Gondor/guilds/morgulmage/spells/narkirisse_log")

/*
 * Function:    config_at_will_spell
 * Description: Config function for at will damage spells. Redefine this in your
 *              own at will spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_at_will_spell()
{
    set_spell_name("narkirisse");
    set_spell_desc("Cause your flaming weapon to hurt your opponent");
    
    set_spell_element(SS_ELEMENT_FIRE, 10);
    set_spell_form(SS_FORM_CONJURATION, 10);
    
    set_spell_vocal(0);
    set_spell_visual(0);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);
    set_spell_combat_aid(60.0);

    set_spell_task(TASK_HARD);

    set_morgul_rank(4);

    set_spell_time_factor(adjust_time_by_rank);
}

private object
find_narusse_weapon(object caster)
{
    object *weapons = filter(caster->query_weapon(-1), &->is_narusse_enhanced());
    if (!sizeof(weapons)) return 0;
    return weapons[0];
}

string
query_spell_fail() 
{
    string weapon = this_player()->check_call(
        find_narusse_weapon(this_player())->query_short());

    return "The " + weapon + " slips in your grip causing you to miss "
        + "your opening.\n";
}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute)
{
    int result = ::check_valid_action(caster, targets, arg, execute);
    if (!result)
    {
        return result;
    }
    
    if (!objectp(find_narusse_weapon(caster))) 
    {
        caster->catch_tell("You need a weapon that is enhanced by the "
            + "narusse spell to use this gift.\n");
        return 0;
    }
    
    return result;    
}

public void 
hook_special_complete()
{
    object ob = find_narusse_weapon(this_player());
    if (!objectp(ob)) {
        write("You are ready to cast 'narkirisse' again.\n");
        return;
    }

    string weapon = this_player()->check_call(
        ob->query_short());

    write("The flames on your " + weapon + " burn again with power"
        + " and terrible purpose.\n");
}

public void
hook_special_in_cooldown()
{
    string weapon = this_player()->check_call(
        find_narusse_weapon(this_player())->query_short());

    write("The flames on your " + weapon + " seem to have burned low, and"
      + " must strengthen before you may strike again.\n");
}

public void
desc_harm_cast(object caster, object *targets)
{
}

private string
describe_damage(int percentual_damage) 
{
    switch(percentual_damage) 
    {
        case   0..8: return "licks";
        case  9..12: return "singes";
        case 13..16: return "scorches";
        case 17..20: return "burns";
        default    : return "withers";
    }
}

public void
desc_harm_damage(object caster, object target, mixed *result)
{
    int proc_damage = result[3] * 100 / target->query_max_hp();
    string damage_desc = describe_damage(proc_damage);
    object weapon = find_narusse_weapon(caster);
    string hitloc_desc = result[1];
    object corpse_sh;
    
    caster->catch_tell("You point your " + weapon->short() + " at "
        + target->query_the_name(caster) + ", releasing a column "
        + "of fire that " + damage_desc + " " + target->query_possessive()
        + " " +hitloc_desc+ ".\n");
    target->catch_tell(caster->query_The_name(target) + " points "
        + caster->query_possessive() + " " + weapon->short() 
        + " at you, releasing a column of fire that " + damage_desc 
        + " your " +hitloc_desc+ ".\n");
    caster->tell_watcher(QCTNAME(caster) + " points "
        + caster->query_possessive() + " " + weapon->short() 
        + " at " + QTNAME(target) + ", releasing a column of fire that "
        + damage_desc+ " " + target->query_objective()
        + " " +hitloc_desc+ ".\n", target, ({ caster, target }));

    if (objectp( target ) && target->query_hp() <= 0)
    {
        corpse_sh = clone_object( MORGUL_DEATH_SHADOW );
        corpse_sh->shadow_me( target );
        corpse_sh->set_death_cause( NARUSSE_CS );
        corpse_sh->set_death_variant( random( NARUSSE_VR ) );
        target->do_die(caster); 
        corpse_sh->remove_shadow();
    }

    // result is in array of:
    //  ({ proc_hurt, hitloc desc, phit, dam, hitloc id })
    int dam = result[3];
    string player_name = caster->query_real_name();

    send_debug_message("narkirisse", capitalize(player_name)
        + " (lvl " +caster->query_morgul_level()+ 
        ") narkirisse damage: " +dam+ ".", NARK_LOG);
}

/*
 * Function:    resolve_harm_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_harm_spell(object caster, object *targets, int *resist, int result)
{
    ::resolve_harm_spell(caster, targets, resist, result);
    MORGUL_MASTER->increase_activity(caster, ACTIVITY_SMALL_SPELL);
}
