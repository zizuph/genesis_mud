/*
 * Lightning bolt spell for School of High Magic - Arman 2016
 */

#pragma strict_types

#include <ss_types.h>
#include <macros.h>
#include <composite.h>
#include <tasks.h>
#include <stdproperties.h>
#include "defs.h"
#include "/d/Krynn/common/defs.h"

inherit "/d/Genesis/specials/std/spells/harm";

string breath_type, breath_weapon, *how;

/*
 * Function:    config_harm_spell
 * Description: Config function for harm spells. Redefine this in your
 *              own harm spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_harm_spell()
{
    set_spell_name("dragonbreath");
    set_spell_desc("A furious blast of elemental damage common to dragonkind");

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);
    set_spell_combat_aid(60.0);
    set_spell_task(TASK_HARD); 

    // 3 times the standard cast time for a harm spell 
    set_spell_time_factor(3.0);  

    set_spell_element(SS_ELEMENT_AIR, 40);
    set_spell_form(SS_FORM_TRANSMUTATION, 40);
}

/*
 * Function:    query_harm_ingredients
 * Description: This function defines what components are required for
 *              this harm spell.
 */
public string *
query_harm_ingredients(object caster)
{
    return ({  });
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

    return 1;
}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }

    if(caster->query_race_name() != "dragon")
    {
        caster->catch_tell("You cannot summon dragon breath if not in dragon form!\n");
	return 0;
    }

    if(caster->query_dragon_colour() == "red" || caster->query_dragon_colour() == "brass")
    {
       set_spell_element(SS_ELEMENT_FIRE, 40); 
       breath_type = "wave of flame";
       breath_weapon = "a river of flame erupts from ";
       how = ({ "not harmed", "slightly burned", "burned", "injured",
         "burned badly", "caused to collapse" });
    }
    if(caster->query_dragon_colour() == "silver" || caster->query_dragon_colour() == "white")
    {
       set_spell_element(SS_ELEMENT_WATER, 40); 
       set_spell_resist(spell_resist_cold);
       breath_type = "cone of frost";
       breath_weapon = "a cone of frost bursts from ";
       how = ({ "not harmed", "slightly chilled", "chilled", "chilled to "+
         "the bone", "frozen", "frozen solid" });
    }
    if(caster->query_dragon_colour() == "bronze" || caster->query_dragon_colour() == "blue")
    {
       set_spell_element(SS_ELEMENT_AIR, 40); 
       set_spell_resist(spell_resist_electricity);
       breath_type = "bolt of lightning";
       breath_weapon = "a bolt of lightning shoots from ";
       how = ({ "not harmed", "slightly shocked", "slightly burned", "shocked",
         "charred", "electrocuted" });
    }
    if(caster->query_dragon_colour() == "copper" || caster->query_dragon_colour() == "black")
    {
       set_spell_element(SS_ELEMENT_AIR, 40); 
       set_spell_resist(spell_resist_acid);
       breath_type = "stream of acid";
       breath_weapon = "a stream of acid spews from ";
       how = ({ "not harmed", "barely stung", "slightly singed", "singed",
         "badly corroded", "eaten alive" });
    }

    return 1;
}

// HOOKS TO BE DEFINED

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
    object target = targets[0];

        caster_message = "You rise to your full height while rearing your " +
            "head back, inhaling deeply as you prepare to blast " +
            COMPOSITE_LIVE(targets)+ " with a " +breath_type+ ".\n";
        watcher_message = QCTNAME(caster)+" rises to "+HIS(caster)+" full "+
          "height, and you hear a sharp intake of breath as "+HE(caster)+
          " rears back "+HIS(caster)+" head...\n";
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);
    
    setuid();
    seteuid(getuid());
}

/*
 * Function name: desc_harm_damage
 * Description:   Write out some text describing the damage done.  This can
 *                be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object target - the target
 *                mixed *result - return value from harm's hit_me.
 */
public void
desc_harm_damage(object caster, object target, mixed *result)
{
    string caster_message, target_message, watcher_message, how_str;
    int phurt = result[0];
    string hitloc_desc = result[1];

    how_str = how[0];

    if (phurt > 0)
        how_str = how[1];
    if (phurt > 10)
        how_str = how[2];
    if (phurt > 20)
        how_str = how[3];
    if (phurt > 40)
        how_str = how[4];
    if (phurt > 60)
        how_str = how[5];
        
    caster->catch_msg(QCTNAME(target)+" is "+how_str+" by your dragon "+
        "breath!\n");
    target->catch_msg("You are "+how_str+" by the dragon breath!\n");
    target->tell_watcher(QCTNAME(target)+" is "+how_str+" by "+
        QTPNAME(caster)+ " " +breath_type+ "!\n", target, ({ caster, target }));
}

/*
 * Function name: desc_harm_cast
 * Description:   Describe casting of the spell, not including damage messages.
 *                This can be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object target - the target
 */
public void
desc_harm_cast(object caster, object * targets)
{
    string caster_message, target_message, watcher_message;
    object target;
    
    target = targets[0];

        caster_message = "You snap your jaws wide open and " +breath_weapon+
              "your mouth.\n";
        target_message = QCTPNAME(caster)+ " jaws snap open and " +
            breath_weapon +HIS(caster)+ " mouth towards you!\n";

        watcher_message = QCTNAME(caster)+ " snaps " +HIS(caster)+ " jaws open " +
            "and " +breath_weapon +HIS(caster)+ " mouth towards " + 
            QTNAME(target)+"!\n";
    
    caster->catch_msg(caster_message);
    target->catch_msg(target_message);
    caster->tell_watcher(watcher_message, targets, ({ caster }) + targets);    
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
    if(caster->query_race_name() != "dragon")
    {
        caster->catch_tell("You cannot summon dragon breath if not in dragon form!\n");
	return;
    }

    // DEBUG("Target: " +targets[0]->short()+ ", Resist: " +resist[0]+ ", Result: " +result);
}
