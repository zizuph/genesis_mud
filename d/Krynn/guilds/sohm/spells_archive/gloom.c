/*
 * A darkness spell that clones a darkness object in to
 * the room of the caster and modifies the darkness room message
 * of the room.
 * 
 * Based on the sulambar Morgul Mage spell which spawns a cloud in
 * to the room of the mage.
 *
 * Coded by Arman 2016.
 */

#pragma strict_types

#include <filter_funs.h>
#include <tasks.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <tasks.h>
#include "defs.h"
#include "/d/Krynn/common/defs.h"

inherit "/d/Genesis/specials/std/spells/centralized_spell";
#include "/d/Genesis/specials/std/spells/centralized_spell_restrictions.h"

public string *query_darkness_ingredients(object caster);

public nomask void
config_spell()
{
    set_spell_name("whedabra");
    set_spell_desc("Gloom - summons dark shadows that obscures vision");
    set_spell_vocal(1);
    set_spell_visual(0);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_spell_element(SS_ELEMENT_AIR, 50);
    set_spell_form(SS_FORM_ILLUSION, 60);
    set_spell_task(TASK_DIFFICULT);
    set_spell_mana(60);
    set_spell_time(6);
    set_spell_target(spell_target_caster);
    set_spell_fail("Your attempt to cast the spell fails, fizzling harmlessly.\n");
    set_spell_ingredients(query_darkness_ingredients);
    set_spell_object(SOHM_SPELL_OBJS + "gloom_obj");

}

public string *query_darkness_ingredients(object caster)
{
    return ({ "skullcap" });
}

/*
 * Function:    query_spell_can_be_learned
 * Description: Place restrictions on whether this spell can be used
 *              by the guild member.
 */
public int
query_spell_can_be_learned(object player)
{
    if (!objectp(player))
    {
        return 0;
    }
    
    if (player->query_npc())
    {
        // npcs can always learn the spell.
        return 1;
    }
    
    setuid();
    seteuid(getuid());
    return SOHM_MANAGER->query_memorised_spell(player,"whedabra_memorised");
}

/*
 * Function name: concentrate_msg
 * Description:   Give messages indicating that spell concentration has begun
 * Arguments:     1. (object)   The caster
 *                2. (mixed *) The targets
 *                3. (string)   The arguments passed to the "cast" command
 */
public void
concentrate_msg(object caster, mixed * targets, string arg)
{
    string caster_message, watcher_message;

        caster_message = "You begin weaving your hands through the air while chanting " +
            "'whedabra', magically pulling strands of darkness towards you.\n";
        watcher_message = QCTNAME(caster) + " begins weaving " + HIS(caster)+ " hands " +
           "through the air while chanting mystical words of magic.\n";
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());    
}

#ifndef LIVE_I_MAINTAINED_EFFECTS
#define     LIVE_O_MAINTAINED_EFFECTS   "_live_o_maintained_effects"
#endif

public int
query_has_maintained_spell_effect(object target, mixed filenames)
{

    if (!pointerp(filenames)) filenames = ({ filenames });
    object * effects = target->query_prop(LIVE_O_MAINTAINED_EFFECTS);
    if (!pointerp(effects)) effects = ({});
    
    foreach(object effect : effects) 
    {
        if (objectp(effect) 
            && (member_array(MASTER_OB(effect), filenames) != -1)) 
        {
            return 1;
        }
    }
    
    return 0;
}

public void
add_maintained_spell_effect(object target, mixed obs) 
{
    if (!pointerp(obs)) obs = ({ obs });
    object *effects = target->query_prop(LIVE_O_MAINTAINED_EFFECTS);
    
    if (!pointerp(effects)) effects = obs;
    else effects += obs;
    
    effects -= ({ 0 }); // clear deleted effects
    target->add_prop(LIVE_O_MAINTAINED_EFFECTS, effects);
}

public nomask void
resolve_spell(object caster, mixed * targets, int * resist, int result)
{
    setuid();
    seteuid(getuid());

    object cloud = make_spell_effect_object(query_spell_object(), caster,
            ({ environment(caster) }), resist, result);
    cloud->move(environment(caster), 1);

    add_maintained_spell_effect(caster, cloud);
}