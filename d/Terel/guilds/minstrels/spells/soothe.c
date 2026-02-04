/*
 * Minstrel's soothe heal song - Arman 2019
 */

#pragma strict_types

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "heal";

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
 * Function:    config_heal_spell
 * Description: Config function for heal spells. Redefine this in your
 *              own heal spells to override the defaults.
 */
public void
config_heal_spell(void)
{
    set_spell_name("soothe");
    set_spell_desc("a sweet and soothing tune of healing");

    // 1.8 times the standard cast time for a heal spell 
    set_spell_time_factor(1.8);  

    set_spell_combat_aid(50.0);

    set_spell_class(SPELL_CLASS_3);
    set_spell_task(TASK_HARD);
    set_spell_fail(minstrel_perform_fail);

    set_spell_resist(spell_resist_illusion);

    // songs influenced by a combination of TS_DEX and TS_DIS 
    // rather than TS_INT
    set_ability_stats( ({ SKILL_AVG, TS_DEX, TS_DIS, SKILL_END }) );

    // Minstrels use non-traditional spell skills
    set_spell_element(SG_INSTRUMENTAL, 20);
    set_spell_form(SG_VOCAL, 20);
}

/*
 * Function:    query_heal_ingredients
 * Description: This function defines what components are required for
 *              this harm spell.
 */
public string *
query_heal_ingredients(object caster)
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

    if (!IN_ARRAY("soothe", song_list))
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
 * Function:    query_spell_combat_aid_modifier
 * Description: Value between 1.0 and 100.0 that will modify
 *              the maximum combat aid granted by this spell.
 */
public float
query_spell_combat_aid_modifier()
{
    // Combat aid impacted by damage to the instrument to
    // a maximum reduction of 45% before the instrument breaks.

    // modify base caid by active maintained spells.
    float total_combat_aid = 50.0;
    float available_combat_aid = 50.0;

    if (query_spell_apply_whitehit_aid())
    {
        total_combat_aid += itof(query_white_hit_combat_aid());
        available_combat_aid += itof(query_white_hit_combat_aid());
    }


    object instrument = present("minstrel_instrument", this_player()); 
    int instrument_damage = instrument->query_damage();

    // If any Lost Muse songs are being maintained, caid is reduced
    // from 50 to 10.
    if(query_active_lost_muse_effect(this_player(), "any"))
    {
        // DEBUG("Soothe Lost Muse check called");
        available_combat_aid -= 40.0;
    }
    available_combat_aid= max(0.0, available_combat_aid - itof(instrument_damage * 5));

    return 100.0 * available_combat_aid / total_combat_aid;
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

    return 1;
}

/*
 * Function:    resolve_heal_spell
 * Description: Called at the beginning of resolve_spell in order to perform 
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_heal_spell(object caster, object *targets, int *resist, int result)
{
    int c_aid = ftoi(query_spell_combat_aid());
    // DEBUG("Minstrel heal combat aid: " + c_aid);
}

/*
 * Function name: hook_describe_heal_cast
 * Description:   Describe casting of the spell. This takes place before the
 *                actual healing happens.
 *                This can be redefined for custom messages.
 * Arguments:     object caster   - the caster
 *                object * target - the target(s)
 */
public void
hook_describe_heal_cast(object caster, object *targets)
{
  // deliberately kept blank. Healing message covered under concentrate_msg
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

    if(target->query_prop(LIVE_I_UNDEAD))
    {
        caster_message = "You begin performing a melody celebrating " +
            "the glory of life!\n";
        watcher_message = QCTNAME(caster) + " begins performing a " +
            "melody celebrating the glory of life!\n";
    }
    else
    {
        caster_message = "You begin performing a soothing melody" +tar_msg+".\n";
        watcher_message = QCTNAME(caster) + " begins performing a " +
            "soothing melody.\n";
    }
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());  
}


/*
 * Function name: hook_describe_heal_result
 * Description:   Describe the results of the spell upon its targets. This
 *                happens after the healing has happened.
 *                This can be redefined for custom messages.
 * Arguments:     object caster   - the caster
 *                object * target - the target(s)
 *                int * heal_amts - the amounts healed
 */
public void
hook_describe_heal_result(object caster, object *targets, int * heal_amounts)
{
    object tar = targets[0];
    int heal = heal_amounts[0];
    string heal_desc;

    switch(heal)
    {
       case 0:
         heal_desc = " superficially";
         break;
       case 1..50:
         heal_desc = " slightly";
         break;
       case 51..150:
         heal_desc = " somewhat";
         break;
       case 151..250:
         heal_desc = "";
         break;
       case 251..450:
         heal_desc = " greatly";
         break;
       case 451..750:
         heal_desc = " astoundingly";
         break;
       default:
         heal_desc = "";
         break;
    }

    if (tar == caster)
    {
	caster->catch_tell("The melodious tune rushes over your body," +
            heal_desc+ " healing your wounds.\n");
	tell_room(environment(caster), QCTNAME(caster) + " is" +
            heal_desc+ " healed by the melodious tune.\n", targets);
    }
    else
    {
	caster->catch_tell("The melodious tune rushes over " +
	    tar->query_the_possessive_name(caster) + " body," +
	    heal_desc+ " healing " + HIS(tar) + " wounds.\n");
	tar->catch_tell("A melodious tune rushes over your body," +
	    heal_desc+ " healing your wounds.\n");
	tell_room(environment(caster), "A melodious tune rushes over " +
	    tar->query_the_possessive_name(caster) + " body," +
	    heal_desc+ " healing " + HIS(tar) + " wounds.\n",
	    ({ caster, tar }), caster);
    }

    // DEBUG("Minstrel heal amount: " +heal+ ", WC: " +query_spell_weapon_class()+".");
}

/*
 * Function name: hook_describe_harm_result
 * Description:   Describe the results of the spell upon its targets. This
 *                happens after the healing has happened.
 *                This can be redefined for custom messages.
 * Arguments:     object caster   - the caster
 *                object * target - the target(s)
 *                int * harm_amounts - the amounts healed
 */
public void
hook_describe_harm_result(object caster, object *targets, int * harm_amounts)
{
    object tar = targets[0];
    int harm = harm_amounts[0];
    string * harm_desc;

    switch(harm)
    {
       case 0..50:
         harm_desc = ({ " winces", " wince" });
         break;
       case 51..150:
         harm_desc = ({ " shudders", " shudder" });
         break;
       case 151..250:
         harm_desc = ({ " groans painfully", " groan painfully" });
         break;
       case 251..450:
         harm_desc = ({ " moans in despair", " moan in despair" });
         break;
       case 451..750:
         harm_desc = ({ " convulses in great pain", " convulse in great pain" });
         break;
       default:
         harm_desc = ({ " groans painfully", " groan painfully" });
         break;
    }

    if (tar == caster)
    {
	caster->catch_tell("You convulse in pain as the melodious tune celebrating "+
	    "Life lances through your body.\n");
	tell_room(environment(caster), QCTNAME(caster) + " convulses as if "+
	    "in some kind of pain.\n", targets);
    }
    else
    {
	caster->catch_tell(tar->query_The_name(caster)+ " " + harm_desc[0] +
            " as the pure tune celebrating the Glory of Life lances through " +
            HIS(tar)+ " undead body.\n");
	tar->catch_tell("You " + harm_desc[1] +" as the sound of a pure " +
            "tune celebrating the Glory of Life lances through your undead body.\n");
	tell_room(environment(caster), tar->query_The_name(caster)+ " " + harm_desc[0] +
            " as a pure tune celebrating the Glory of Life lances through " +
            HIS(tar)+ " undead body.\n", ({ caster, tar }), caster);
    }

    // DEBUG("Minstrel Harm undead amount: " +harm+ ".");
}
