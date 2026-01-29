/*
 * pHeal
 */

#pragma strict_types

inherit "/d/Genesis/specials/std/spells/refresh";

#include "../defs.h"
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <files.h>
#include <composite.h>
#include "/d/Krynn/common/defs.h"

#include <macros.h>
#include <tasks.h>

#include "../oots_god_descs.h"

/*
 * Function:    config_refresh_spell
 * Description: Config function for refresh spells. Redefine this in your
 *              own refresh spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_refresh_spell()
{
    set_ability_group(GUILD_NAME);
    set_spell_name("orefresh");
    set_spell_desc("Refresh - refresh fatigue");

    set_spell_element(SS_ELEMENT_LIFE, 10);
    set_spell_form(SS_FORM_TRANSMUTATION, 15);
    set_spell_fail("Your prayer is unheard.\n");

    set_spell_task(TASK_ROUTINE);

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
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

    // Level 7 (Learned Disciple) spell
    if(OOTS_LEVEL(player) < 7)
    {
        return 0;
    }

    return 1;
}

/*
 * Function:    query_refresh_ingredients
 * Description: This function defines what components are required for
 *              this refresh spell.
 */
public string *
query_refresh_ingredients(object caster)
{
    return ({ "bunchberry" });
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
    return "bunchberry";
}

void
hook_use_ingredients(object *ingrs)
{
    write("The veined oval leaf turns a deep autumn yellow and " +
          "then crumbles to dust.\n");

}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
        return 0;

    if (caster->query_alignment() < 600)
    {
        caster->catch_tell("Your recent behaviours and actions do not " +
           "align with the teachings of " +oots_god_name(caster)+ 
           ". Your prayer goes unanswered.\n");
        return 0;
    }

    object target = targets[0];
    int fatigue = target->query_fatigue();
    int max_fatigue = target->query_max_fatigue();

    if(fatigue == max_fatigue)
    {
        caster->catch_tell(target->query_The_name(caster) + " is " +
           "extremely alert and not in need of refreshing. " +
           oots_god_name(caster)+ " does not respond to your " +
           "prayer.\n");
        return 0;
    }

    return 1;
}

/*
 * Function:    resolve_refresh_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_refresh_spell(object caster, mixed * targets, int * resist, int result)
{
    object target = targets[0];
    int fatigue = target->query_fatigue();
    int max_fatigue = target->query_max_fatigue();
    int fatigue_xp = min(50, (result / 4));

    if(fatigue == max_fatigue)
    {
    //  DEBUG("ofatigue no fatigue to heal, result " +result+ ".");
    }
    else
    {
    //  DEBUG("ofatigue: " +fatigue+ ", result: " +result+ ", xp: " +fatigue_xp+ ".");
        OOTS_ADD_EXP(caster, fatigue_xp); 
    }

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
    object target = targets[0];

        caster_message = "You whisper a prayer, supplicating " + 
              oots_god_name(caster)+ " for the blessing of divine " +
              "assistance.\n";
        watcher_message = QCTNAME(caster) + " whispers a prayer to the "
              +oots_god_desc(caster)+ " " +oots_god_name(caster)+".\n";
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());  
}


/*
 * Function name: desc_refresh_cast
 * Description:   Describe casting of the spell to cure fatigue.
 *                This can be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object * targets - the targets 
 *                int amount - the amount refreshed
 */
public void
desc_refresh_cast(object caster, object * targets, int amount)
{
    object tar = targets[0];
    int heal = amount;
    string heal_desc;

    switch(heal)
    {
       case 0..10:
         heal_desc = " slightly";
         break;
       case 11..20:
         heal_desc = " somewhat";
         break;
       case 21..30:
         heal_desc = "";
         break;
       case 31..40:
         heal_desc = " greatly";
         break;
       case 41..100:
         heal_desc = " miraculously";
         break;
       default:
         heal_desc = "";
         break;
    }

    if (tar == caster)
    {
	caster->catch_tell("You feel the blessings of " +
            oots_god_name(caster)+ " wash over you and energy infuse " +
            "your body," +heal_desc+ " refreshing you.\n");
	tell_room(environment(caster), QCTNAME(caster) +
	    " straightens up, looking" +heal_desc+ " more refreshed.\n", 
            targets);
    }
    else
    {
	caster->catch_tell("You place your hands on " +
	    tar->query_the_name(caster) + ", and " + HE(tar) +
	    " looks" +heal_desc+ " refreshed.\n");
	tar->catch_tell(caster->query_The_name(tar) + " places " +
	    HIS(caster) + " hands on you, and you feel" +
	    heal_desc+ " refreshed.\n");
	tell_room(environment(caster), QCTNAME(caster) + " places " +
	    HIS(caster) + " hands on " + QTNAME(tar) + ", and " +
	    HE(tar) + " looks" +heal_desc+ " refreshed.\n",
	    ({ caster, tar }), caster);
    }

    // DEBUG("Refreshed amount: " +heal+ ".");
}

public int
is_valid_medallion(object caster, object obj)
{
    if (!objectp(obj) || !obj->id("oots_guild_object"))
    {
        return 0;
    }
    
    return 1;
}

/*
 * Function name: query_casting_success
 * Description:   Determine if a spell is successfully cast
 * Returns:       The result as an integer indicating success or
 *                failure (0 indicating failure, positive integer
 *                indicating % success)
 */
static int
query_casting_success(object caster)
{
    object * med = filter(all_inventory(TP), &is_valid_medallion(caster,));

    int ret = ::query_casting_success(caster);

    /* If we don't wear the medallion, there is only a 10% chance
     * the spell will actually go through
     */
    if(!med[0]->query_worn())
    {
        if (random(10))
            return 0;
    }
        
    return ret;
}