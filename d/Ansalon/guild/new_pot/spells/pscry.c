/*
 * pScry - updated by Arman October 2016
 *
 * Doesn't use the standard scry spell template due to its unique
 * spell resolution messages.
 *
 * Updated Nov, 2022 - Zizuph
 *    Check living protection before room, to match other scries
 *    Track the caster in the scried on successful scry, to match other scries.
 *
 */

#pragma strict_types

#include "/d/Ansalon/common/defs.h"
#include <macros.h>
#include <tasks.h> 
#include <filter_funs.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <composite.h>
#include <wa_types.h>

#include "../guild.h"
#include "../spells.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "centralized_spell";
inherit GUILDDIRSPELL + "common";

#include "/d/Genesis/specials/std/spells/centralized_spell_restrictions.h"

string target_name;
 
static string *common_art = ({ "a", "an", "the" });
static string *common_prep = ({ "up", "on", "at", "in", "outside",
    "inside", "above", "below", "beside", "under" });

static mapping race_colour = ([
    "human"     : ({ "white", "silver", "black" }),
    "elf"       : ({ "golden", "yellow", "dark yellow" }),
    "dwarf"     : ({ "silver grey", "grey", "dark grey" }),
    "hobbit"    : ({ "light green", "green", "dark green" }),
    "gnome"     : ({ "light brown", "bronze", "deep bronze" }),
    "goblin"    : ({ "brown", "greenish brown", "brownish black" })
    ]);

static string *brute_colour = ({
    "", "streaked with red", "mottled with red",
    "with swirling clouds of red" });

/* Function name: query_spell_level
 * Description:   Internally used by the standing system
 * Returns:       int - the spell level
 */
int
query_spell_level()
{
    return 9;
}


varargs string *
translate_auras(object *obj, object for_obj)
{
    int i;
    string *auras;

    if (!for_obj)
        for_obj = this_player();

    auras = ({ });

    for (i=0; i<sizeof(obj); i++)
    {
        object o;
        string *ca,c;

        o = obj[i];

        if (o->query_prop(LIVE_I_UNDEAD))
            continue;

        ca = race_colour[o->query_race()];
        if (!pointerp(ca))
            c = "indistinct";
        else if (o->query_alignment() > 250)
            c = ca[0];
        else if (o->query_alignment() < -250)
            c = ca[2];
        else
            c = ca[1];

        c += " aura";

        if (for_obj == o)
            c += " of yourself";
        else if (for_obj->query_met(o))
            c += " belonging to " + C(o->query_real_name());
            
        auras += ({ LANG_ADDART(c) });
    }
    return auras;
}

public void
concentrate_msg(object caster, object *targets, string arg)
{
    object old_tp = TP;
    string watcher_message;

    set_this_player(caster);
    caster->catch_tell("You close your eyes and turn your sight inwards.\n");
    watcher_message = QCTNAME(caster) + " closes " + HIS(caster) + " eyes, " +
        "concentrating on something.\n";
    tell_room(environment(caster), watcher_message, ({ caster }), caster);
    set_this_player(old_tp);
}

/*
 * Function name: resolve_spell
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                object *targets - an array of targets
 *                int *resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */
public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
    object tar = targets[0];
    object env;
    mixed no_scry;
    string s,short_desc;
    string *auras;
    int t;

    env = environment(tar);

    if (tar->query_wiz_level())
    {
        // Not allowed to scry wizards
        caster->catch_tell("You sense a wall of force stopping your " +
            "attempt to divine the location of the wizard " + 
            C(tar->query_real_name()) +".\n");
        return;
    }

    if (tar->query_linkdead())
    {
        // Not allowed to scry wizards or linkdead people
        caster->catch_tell("You sense only a blank as you attempt to " +
            "divine the location of " + C(tar->query_real_name()) +
            ".\n");
        return;
    }

    if (tar->query_npc())
    {
        // Not allowed to scry npcs
        caster->catch_tell("You do not sense " +C(target_name)+
            "'s presence in the realms.\n");
        return;
    }

    // If it's not a valid room, fail.
    if (!env)
    {
        caster->catch_tell("You do not sense anything of " +
        tar->query_the_name(caster) + "'s surroundings.\n");
        return;
    }

    // If the target is no scry, fail.
    no_scry = tar->query_prop(LIVE_M_NO_SCRY);
    if (no_scry)
    {
        if (stringp(no_scry))
        {      
            // If the property specified its own no scry message, we
            // use that instead.
            caster->catch_tell(no_scry + "\n");
        }
        else
        {
            caster->catch_tell("You sense a wall of force " +
                "stopping your attempt to divine the whereabouts " +
                "of " + C(tar->query_real_name()) + ".\n");
        }
        return;
    }

    // If the room is no scry, fail.
    no_scry = env->query_prop(ROOM_M_NO_SCRY);
    if (no_scry)
    {
        if (stringp(no_scry))
        {      
            // If the room specified its own message, we use that
            // instead.
            caster->catch_tell(no_scry + "\n");
        }
        else
        {
            caster->catch_tell("You sense a wall of force stopping " +
                "your attempt to divine the whereabouts of " + 
                C(tar->query_real_name()) + ".\n");
        }
        return;
    }

    // DEBUG("Resist: " + resist[0] + ".");
    // Test to see whether the scry passes the resistance of the target
    if (resist[0] > random(100))
    {
            caster->catch_tell("Your attempt to divine the whereabouts " +
                "of " + C(tar->query_real_name()) + " was resisted.\n");
            tar->catch_tell("You sense someone trying to divine your whereabouts, "
                + "but you successfully ward off the intruding presence.\n");
        return;
    }        


    short_desc = env->short();
    s = "You let your mind travel towards " + tar->query_the_name(caster) +
    ". ";
    
    switch(env->query_prop(ROOM_I_TYPE))
    {
        case ROOM_IN_WATER:
            s += "You see the swirling blue clouds of open water " +
            "all around you. ";
            break;
        case ROOM_UNDER_WATER:
            /* cannot scry under water */
            caster->catch_tell("Somehow, you fail to locate " +
            capitalize(tar->query_real_name()) + ".\n");
            return;
        case ROOM_BEACH:
            s += "You see the swirling blue clouds of open water " +
            "nearby. ";
            break;
    }

    if (short_desc && short_desc != "")
    {
        string tmp;

        tmp = lower_case(explode(short_desc + " ", " ")[0]);
        if (member_array(tmp,common_prep) >= 0)
        {
            short_desc = tmp + extract(short_desc,strlen(tmp));
            s += "Drawing near, you get a strong impression of " +
            "being " + short_desc + ". ";
        }
        else if (member_array(tmp,common_art) >= 0)
        {
            short_desc = tmp + extract(short_desc,strlen(tmp));
            s += "Drawing near, you get a strong impression of " +
            short_desc + ". ";
        }
        else
        {
            s += "Drawing near, you get a strong impression of " +
            "the " + short_desc + ". ";
        }
    }

    auras = translate_auras(FILTER_LIVE(all_inventory(env)), caster);

    if (sizeof(auras))
    {
        s += "Nearby, you sense " + COMPOSITE_WORDS(auras) + ". ";
    }
    else
    {
        s += "You do not sense any auras nearby. ";
    }

    caster->catch_tell(s + "\n");

    /* Only send a message to the target if the caster is
       a non-wizard, to allow for testing
     */
    if (caster->query_wiz_level())
        return;

    tar->catch_msg("You briefly feel an intruding presence " +
    "seeking you out, but the feeling passes.\n");

    if (result)
        caster->adjust_standing(random(8) ?
            RND_RANGE(TO->query_spell_level() * 3, 10) : RND_RANGE(-10, 10));
    else
        caster->adjust_standing(RND_RANGE(-5, 5));

    tar->add_prop("_live_i_scried_by", caster);

}

/*
 * Function:    config_scry_spell
 * Description: Config function for scry spells. Redefine this in your
 *              own scry spells to override the defaults.
 * Arguments:   Same as config_spell 
 * Returns:     Same as config spell
 */
public void
config_scry_spell()
{
    // Nothing special here.
}

private nomask void
config_required_parameters()
{
    // By default, all scry spells must be peaceful and stationary
    set_spell_peaceful(1);
    set_spell_stationary(1);
}

/*
 * Function name: config_spell
 * Description:   configure the spell
 * Arguments:     object caster   - the caster
 *                object *targets - array of spell targets found
 *                string argument - arguments to the spell invocation
 * Returns:       0/1 - spell configured/not configured (cannot be cast)
 */

public nomask void
config_spell()
{
    ::config_spell();
    set_spell_name("pscry");
    set_spell_desc("Divine the whereabouts of someone you know");
    set_spell_target(spell_target_one_distant_living);

    set_ability_stats(STAT_WEIGHTING);

    set_spell_class(SPELL_CLASS_2);
    set_spell_task(TASK_EASY);
    set_spell_vocal(1);
    set_spell_time(10);
    set_spell_fail("You fail in your efforts to invoke the spell.\n");
    set_ability_target_verify(0);
    set_spell_ingredients(({"solinaith", "apple"}));

    set_spell_element(SS_ELEMENT_LIFE, 45);
    set_spell_form(SS_FORM_DIVINATION, 30);
         
    // Call the specific configuration that is to be masked.
    config_scry_spell();
    
    // Call this after the config_scry_spell to ensure that
    // scry spells are always peaceful and stationary.
    config_required_parameters();
}

public int
is_valid_medallion(object caster, object obj)
{
    if (!objectp(obj) || !obj->id(MEDALLION_ID))
    {
        return 0;
    }
    
    return 1;
}

/*
 * Function name:   query_ability_hit
 * Description:     Returns the set ability to-hit value.
 * Arguments:       (object) actor
 *                  (mixed) target
 *                  (object *) items
 * Returns:         (int) ability hit value
 */
public int
query_ability_hit(object actor, mixed target, object * items)
{
    if (calling_function() == "query_spell_tohit")
    {
        // harder to cast on when in poor standings
    
        if (actor->query_skill(PS_STANDING) < -900)
            return convert_task_to_hit(TASK_FORMIDABLE);
        
        if (actor->query_skill(PS_STANDING) < -300) 
            return convert_task_to_hit(TASK_HARD);
    }
    
    return ::query_ability_hit(actor, target, items);
} /* query_ability_hit */

/*
 * Function name: check_required_items
 * Description  : Does some validation to make sure the actor has
 *                all the equipment they need to perform the special.
 * Returns      : items that are required, or 0 if a required item is
 *                missing.
 */
static mixed *
check_required_items(object actor, mixed * targets,string arg, int pretest)
{
    return filter(actor->query_clothing(-1), &is_valid_medallion(actor,));
}

/*
 * Function:    query_spell_power
 * Description: A generic power calculation function that takes into
 *              account skills, stats, and guild strength
 */
public int
query_spell_power()
{
    mixed *items = check_required_items(this_player(), ({}), "", 0);
    return max(1, query_ability_power(this_player(), ({}), items));
}

/*
 * Function name:   query_ability_item_modifier
 * Description:     
 * Arguments:       1. (object) actor
 *                  2. (mixed *) items - The items used with the ability
 * Returns:         (int) 
 */
public int
query_ability_item_modifier(object caster, mixed *items)
{
    items = filter(items, &is_valid_medallion(caster,));
    
    /* If we don't wear the medallion, there is only a 10% chance
     * the spell will actually go through
     */
    if(!sizeof(items))
    {
        caster->adjust_standing(RND_RANGE(-200, 50));
        if (random(10))
            return 0;
    }
    
    return 100;
} /* query_ability_item_modifier */