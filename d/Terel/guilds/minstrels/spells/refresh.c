/*
 * Minstrel's refresh fatigue song - Arman 2019
 */

#pragma strict_types

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "refresh";

#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <files.h>
#include <composite.h>
#include "/d/Terel/common/terel_defs.h"
#include "../guild_defs.h"

#include <macros.h>
#include <tasks.h>

#include "minstrel_spell_hooks.h"

#define HIS(x)        ((x)->query_possessive())

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
    set_spell_name("refresh");
    set_spell_desc("a song of refreshment from fatigue");

    // Minstrels use non-traditional spell skills
    set_spell_element(SG_INSTRUMENTAL, 10);
    set_spell_form(SG_VOCAL, 10);
    set_spell_fail(minstrel_perform_fail);

    set_spell_class(SPELL_CLASS_2);
    set_spell_task(TASK_ROUTINE);

    // songs influenced by a combination of TS_DEX and TS_DIS 
    // rather than TS_INT
    set_ability_stats( ({ SKILL_AVG, TS_DEX, TS_DIS, SKILL_END }) );

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(0);
}

public int
query_spell_can_be_learned(object player)
{
    if (!objectp(player))
    {
        return 0;
    }

    // We don't allow the "cast" verb to be used or
    // the songs of power to show in the spells list
    if (calling_function(-1) == "cast" || calling_function(-1) == "spells")
    {
        return 0;
    }
    
    if (player->query_npc())
    {
        // npcs can always learn the spell.
        return 1;
    }

    string * song_list = SONGBOOK_MANAGER->query_power_songs(player);

    if (!IN_ARRAY("refresh", song_list))
    {
        return 0;
    }

    if (MEMBER(player))
    {
        return 1;
    }
    
    return 0;
}

/*
 * Function:    query_refresh_ingredients
 * Description: This function defines what components are required for
 *              this refresh spell.
 */
public string *
query_refresh_ingredients(object caster)
{ 
    return ({  });
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
    return "vocal, instrument";
}


public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }

    object instrument = present("minstrel_instrument", caster);

    if(query_spell_form_skill() == SG_INSTRUMENTAL ||
       query_spell_element() == SG_INSTRUMENTAL)
    {
        // The instrument is broken if it has 10 damage.
        if(instrument->query_damage() > 9)
        {
            caster->catch_tell(instrument->query_damage_desc()+ " You cannot " +
                "perform with it in such a state!\n");
            return 0;
        }
    }

    object target = targets[0];
    int fatigue = target->query_fatigue();
    int max_fatigue = target->query_max_fatigue();

    if(fatigue == max_fatigue)
    {
        if(target == caster)
            caster->catch_tell("You are extremely alert and not " +
                "in need of refreshing.\n"); 
        else   
            caster->catch_tell(target->query_The_name(caster) + " is " +
               "extremely alert and not in need of refreshing.\n");
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

    if(fatigue == max_fatigue)
    {
        // DEBUG("Minstrel fatigue - no fatigue to heal, result " +result+ ".");
    }
    else
    {
        // DEBUG("refresh: " +fatigue+ ", result: " +result+ ".");
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
    string tar_msg = "";

    if(target != caster)
        tar_msg = " for " +target->query_the_name(caster);

        caster_message = "You begin performing an uplifting melody" +tar_msg+".\n";
        watcher_message = QCTNAME(caster) + " begins performing an " +
            "uplifting melody.\n";
        
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
       case 0:
         heal_desc = " superficially";
         break;
       case 1..10:
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
         heal_desc = " astoundingly";
         break;
       default:
         heal_desc = "";
         break;
    }

    if (tar == caster)
    {
	caster->catch_tell("The uplifting melody" +heal_desc+ 
            " refreshes your body and soul.\n");
	tell_room(environment(caster), QCTNAME(caster) + " seems" +
            heal_desc+ " refreshed by the uplifting tune.\n", targets);
    }
    else
    {
	caster->catch_tell("The uplifting melody seems to" +
            heal_desc+ " refresh " +tar->query_the_possessive_name(caster)+ 
            " body and soul.\n");
	tar->catch_tell("The uplifting melody" +heal_desc+ " refreshes " +
            "your body and soul.\n");
	tell_room(environment(caster), "An uplifting melody" +heal_desc+
	    " refreshes " +tar->query_the_possessive_name(caster) + " body " +
	    "and soul.\n", ({ caster, tar }), caster);
    }

    // DEBUG("Refreshed amount: " +heal+ ".");
}
