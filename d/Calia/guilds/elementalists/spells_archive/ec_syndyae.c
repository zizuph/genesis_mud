/*
 * Syndyasmos Air + Fire combination spell the
 * Elemental Cleric Guild of Calia
 *
 * Created by Jaacar, June 2017
 */

#pragma strict_types

#include <macros.h>
#include <files.h>
#include <tasks.h>
#include <ss_types.h>
#include <composite.h>
#include "defs.h"

inherit "/d/Genesis/specials/std/spells/unfinished/disarm";
inherit (ELEMENTALIST_SPELLS + "spell_functions");

/*
 * Function:    is_full_master_cleric_spell
 * Description: Used for filtering spells into the right categories
 */
public int
is_full_master_cleric_spell()
{
    return 1;
}

/*
 * Function:    config_disarm_spell
 * Description: Config function for disarm spells. Redefine this in your
 *              own disarm spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */

public void
config_disarm_spell()
{
    set_spell_name("eaeragis");
    set_spell_desc("Syndyasmos Air + Earth Combination");

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);
    set_spell_fail("Your prayer fails.\n");
    set_spell_task(TASK_HARD);
    set_spell_element(SS_ELEMENT_AIR, 50);
    set_spell_form(SS_FORM_CONJURATION, 50);
    set_spell_fail("You fail in your efforts to invoke the prayer.\n");

    // 2.0 times the standard cast time for a harm spell
    set_spell_time_factor(2.0);

    set_spell_target(spell_target_present_enemies);
    set_spell_combat_aid(130.0);

    set_spell_ingredients(query_disarm_ingredients);
    set_spell_object(ELEMENTALIST_SPELL_OBJS + "ec_disarm_obj");

}

/*
 * Function:    query_spell_combat_aid_modifier
 * Description: Value between 1.0 and 100.0 that will modify
 *              the maximum combat aid granted by this spell.
 */
public float
query_spell_combat_aid_modifier()
{
    float caid_result;

    if (TP->is_elemental_racial_cleric)
    {
        if (TP->query_prop(CONDUIT_PENALTY) == 3)
    		caid_result = 50.0;
    	else
    		caid_result = 100.0;
    }
    else
    {
        if (TP->query_prop(CONDUIT_PENALTY) == 3)
    		caid_result = 46.1;
    	else
    		caid_result = 92.3;
    }
    return caid_result;
}

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

    if (player->query_wiz_level())
    {
        // Wizards get all spells
        return 1;
    }

    // We don't allow the "cast" verb to be used
    if (calling_function(-1) == "cast" || calling_function(-1) == "spells")
    {
        return 0;
    }

    if (player->query_stat(SS_LAYMAN) < SPELL_MINIMUM_GSTAT_CLERIC_SYNDYASMOS)
    {
        return 0;
    }

    // Only full master clerics and higher get this spell
    if (!GUILD_MANAGER->query_is_full_master(player))
    {
        return 0;
    }

    // Only players who have finished the Guru quest get this spell
    if (!player->test_bit("Calia",EC_GURU_GROUP,EC_GURU_BIT))
    {
        return 0;
    }

    // Only air clerics get this spell
    if (GUILD_MANAGER->query_primary_element(player) != "air")
    {
        return 0;
    }

    return 1;
}

public void
hook_already_has_spell_object(object caster, object target)
{
    if (objectp(target))
    {
        caster->catch_msg(QCTNAME(target) + " has already been "+
            "disarmed!\n");
    }
}

public void
hook_no_weapons_wielded(object caster, object target)
{
    if (objectp(target))
    {
        caster->catch_msg(QCTNAME(target) + " has no weapons wielded!\n");
    }
}

/*
 * Function name : resolve_spell_resisted
 * Description   : The spell was resisted, this hook allows for writing specific methods.
 * Arguments     : object caster - The caster of the spell.
 *               : object target - The target of the spell.
 *               : int resist    - The resist value.
 *               : int result    - How well the spell was cast.
 */
public void
resolve_spell_resisted(object caster, object target, int resist, int result)
{
    caster->catch_msg(QCTNAME(target)+" resisted your prayer.\n");

}

public int
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }

    if (!can_cast_elementalist_spell(caster))
    {
        return 0;
    }

    if (caster->query_wiz_level())
    {
        // Wizards get all spells
        return 1;
    }

    // Only air clerics get this spell
    if (GUILD_MANAGER->query_primary_element(caster) != "air")
    {
        return 0;
    }

    object mandala = present("_elemental_guild_mandala", caster);
    if (!mandala)
    {
        write("You cannot use this prayer without your sacred mandala!\n");
        return 0;
    }

    if (present("_elemental_child_mandala", caster))
    {
    	write("You cannot use this prayer without carving the Word of Power "+
    	    "into your sacred mandala!\n");
    	return 0;
    }

    if (!GUILD_MANAGER->query_current_syndyasmos_partner(caster))
    {
    	return 0;
    }

    // The disarm spell cannot be cast if it is already in effect. At some
    // point, if this spell is going to be mass cast, we should allow the
    // spell to be cast even if some of the targets have the disarm spell on.
    // We just need to be careful not to stack the effects.
    foreach (object target : targets)
    {
        if (has_spell_object(target))
        {
            hook_already_has_spell_object(caster, target);
            return 0;
        }

        if (!sizeof(target->query_weapon(-1)))
        {
        	hook_no_weapons_wielded(caster, target);
        }
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
    string caster_message, caster_name, watcher_message, partner_name;
    string partner_message;
    object partner_ob;

    caster_name = capitalize(caster->query_real_name());
    partner_name = GUILD_MANAGER->query_current_syndyasmos_partner(caster);
    partner_ob = find_player(partner_name);
    partner_name = capitalize(partner_name);

    caster_message = "You hold out your hand and focus on gathering the "+
        "power of Lady Aeria.\n"+partner_name+" holds out "+
        partner_ob->query_possessive()+ " and concentrates intensely.\n";
    partner_message = caster_name+" holds out "+caster->query_possessive()+
        " hand and concentrates intensely.\nYou hold out your hand and focus "+
        "on gathering the power of Lady Gu.\n";
    watcher_message = QCTNAME(caster) + " and "+QTNAME(partner_ob)+
        " both hold out their hands and begin to concentrate intensely.\n";

    caster->catch_tell(caster_message);
    partner_ob->catch_tell(partner_message);
    tell_room(environment(caster), watcher_message,
    	({ caster, partner_ob }), caster);

    setuid();
    seteuid(getuid());
    int conduit_penalty = caster->query_prop(CONDUIT_PENALTY);

    switch(conduit_penalty)
    {
    	case 1:  // halved conduit gain
    		GUILD_MANAGER->add_practice_level(caster, 5);
		    GUILD_MANAGER->add_player_conduit_earned(caster, 5);
		    GUILD_MANAGER->add_guild_conduit(5);
		    caster->catch_tell("\n\nYou have acted outside of your Vow of "+
		    	"Service. "+
		        "This strains your connection with the Circle and the "+
		        "Conduit.\n\n\n");
    		break;
    	case 2:  // halved conduit gain, double conduit cost
    		GUILD_MANAGER->add_practice_level(caster, 5);
		    GUILD_MANAGER->add_player_conduit_earned(caster, 5);
		    GUILD_MANAGER->add_guild_conduit(5);
		    caster->catch_tell("\n\nYou have deliberately violated your "+
		    	"Vow of Service. "+
		        "The Conduit between the Circle and the Five suffers from "+
		        "your lack of Faith.\n\n\n");
    		break;
    	case 3:  // halved conduit gain, double conduit cost, halved CAID
    		GUILD_MANAGER->add_practice_level(caster, 5);
		    GUILD_MANAGER->add_player_conduit_earned(caster, 5);
		    GUILD_MANAGER->add_guild_conduit(5);
		    caster->catch_tell("\n\nYou have repeatedly violated your Vow "+
		    	"of Service. "+
		        "With such malpractice, your prayers sound weak and "+
		        "hollow.\n\n\n");
    		break;
    	default:
    		GUILD_MANAGER->add_practice_level(caster, 10);
		    GUILD_MANAGER->add_player_conduit_earned(caster, 10);
		    GUILD_MANAGER->add_guild_conduit(10);
    		break;
    }
}

public void
hook_describe_disarm(object caster, mixed * targets, int result)
{
    string caster_message, target_message, watcher_message;
    string partner_message, partner_name, caster_name;
    object partner_ob;

    string go_plural;

    partner_name = GUILD_MANAGER->query_current_syndyasmos_partner(caster);
    partner_ob = find_player(partner_name);
    partner_name = capitalize(partner_name);
    caster_name = capitalize(caster->query_real_name());
    int num_targs = sizeof(targets);

    if(sizeof(targets) > 1)
      go_plural = "them";
    else
      go_plural = targets[0]->query_objective();

    caster_message= "Your prayers being heard, you extend " +
		      "your hands towards "+ partner_name+" and as you "+
		      "do so, a wave of airy energy rushes towards "+
		      partner_ob->query_objective()+".\n"+
		      partner_name+" extends "+partner_ob->query_possessive()+
		      " hands towards you and as "+partner_ob->query_pronoun()+
		      " does so, a wave of earthly energy rushes towards you.\n"+
		      "The two energy waves collide between you and begin to "+
		      "mesh and mingle by twisting into one another. Suddenly "+
		      "the now combined energy wave turns and rushes towards "+
		      COMPOSITE_LIVE(targets) +"\n";
	partner_message= "Your prayers being heard, you extend " +
		      "your hands towards "+ caster_name+" and as you "+
		      "do so, a wave of earthly energy rushes towards "+
		      caster->query_objective()+".\n"+
		      caster->query_The_name(partner_ob) +
              " extends "+caster->query_possessive()+
		      " hands towards you and as "+caster->query_pronoun()+
		      " does so, a wave of airy energy rushes towards you.\n"+
		      "The two energy waves collide between you and begin to "+
		      "mesh and mingle by twisting into one another. Suddenly "+
		      "the now combined energy wave turns and rushes towards "+
		      COMPOSITE_LIVE(targets) +"\n";
    target_message = QCTNAME(caster) + " extends " +
    	caster->query_possessive() +
		" hands towards "+partner_ob->query_the_name(targets)+" and as "+
		caster->query_pronoun()+" does so, a wave of airy energy rushes "+
		"towards "+partner_ob->query_objective()+".\n"+
		partner_ob->query_The_name(targets)+" extends "+
		partner_ob->query_possessive()+
		" hands towards "+caster->query_the_name(targets)+" and as "+
		partner_ob->query_pronoun()+" does so, a wave of earthly energy "+
		"shoots "+
		"towards "+caster->query_objective()+".\nThe two energy waves "+
		"collide between them and begin to mesh and mingle by twisting "+
		"into one another. Suddenly the now combined energy wave turns "+
		"and rushes towards you!\n";
    watcher_message = QCTNAME(caster) + " extends " +
    	caster->query_possessive() +
		" hands towards "+QTNAME(partner_ob)+" and as "+
		caster->query_pronoun()+" does so, a wave of airy energy rushes "+
		"towards "+partner_ob->query_objective()+".\n"+
		QCTNAME(partner_ob)+" extends "+partner_ob->query_possessive()+
		" hands towards "+QTNAME(caster)+" and as "+
		partner_ob->query_pronoun()+" does so, a wave of earthly energy "+
		"shoots "+
		"towards "+caster->query_objective()+".\nThe two energy waves "+
		"collide between them and begin to mesh and mingle by twisting "+
		"into one another. Suddenly the now combined energy wave turns "+
		"and rushes towards " + COMPOSITE_LIVE(targets) +".\n";

	caster->catch_msg(caster_message);
    partner_ob->catch_msg(partner_message);
    targets->catch_msg(target_message);
    caster->tell_watcher(watcher_message, targets,
    	({ caster, partner_ob }) + targets);
    caster->add_prop(LIVE_I_SYNDYASMOS_TARGETS, num_targs);
}

/*
 * Function:    hook_no_disarm_message
 * Description: When it is not possible to disarm, for whatever reason,
 *              this message is given.
 * Arguments:   caster - person casting the spell
 *              target - the person being disarmed
 */
public void
hook_no_disarm_message(object caster, object target)
{
    caster->catch_tell("Your cannot seem to locate your target.\n");
}

/*
 * Function:    query_disarm_ingredients
 * Description: This function defines what components are required for
 *              this disarm spell.
 */
public string *
query_disarm_ingredients(object caster)
{
    return ({ "_syndyasmos_component_" });
}

/*
 * Function:    query_spell_ingredients_description
 * Description: Returns a string description of the ingredients. Can be used
 *              in messages to casters about what is actually required
 *              for this spell.
 */
public string
query_spell_ingredients_description()
{
    return "blade, alexandrite shard";
}

/*
 * Function name: list_spells
 * Description:   This function is called to list the spells from
 *                the player soul when the command "prayers" is used.
 */
public void
list_spells()
{
    string ingredients_description = query_spell_ingredients_description();
    if (!strlen(ingredients_description))
    {
        ingredients_description = "none";
    }
    write(sprintf("%-15s %s (%s)\n", query_spell_name(), ::query_spell_desc(),
        ingredients_description));
}

/* Had to mask the below function from spell_targetting.c */

public object *
spell_target_present_enemies(object actor, string str)
{
    object *enemies = (object *)actor->query_enemy(-1) &
        all_inventory(environment(actor));

    if (!sizeof(enemies))
    {
        actor->catch_msg("You must first be in combat before you can "+
        	"call on this prayer!\n");
        return ({});
    }

    return enemies;
}
