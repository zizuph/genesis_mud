/* spell.c - Spell configuration routines
 *
 * Creating a spell is simple.  All you need to do is define a function
 * config_spell(), which configures the spells attributes, and a function
 * resolve_spell(), which implements the spell's effects.
 *
 * Spell configuration functions available
 * =======================================
 * set_spell_name(string)
 *     Set the name of the spell.
 *
 * set_spell_desc(string)
 *     Set a description of the spell's effect to be shown to the
 *     caster.
 * 
 * set_spell_time(int)
 *     Set the amount of casting time required (in seconds)
 *     Default: 6
 *
 * set_spell_ingredients(mixed ingrs)
 *     Set the components required for casting
 *     Default: no components
 *
 * set_spell_optional_ingredients(mixed ingrs)
 *     Set the optional components allowed for casting.
 *
 * set_spell_offensive(int)
 *     Designate the spell as an offensive spell
 *     Default: false
 *
 * set_spell_element(int, int)
 *     Set the element used for the spell and the skill level required.
 *     Default: SS_ELEMENT_FIRE, 40
 *
 * set_spell_form(int, int)
 *     Set the form used for the spell and the skill level required.
 *     Default: SS_FORM_TRANSMUTATION, 40
 *
 * set_spell_mana(int)
 *     Set the amount of mana required to cast the spell
 *     Default: 1000
 *
 * set_spell_mana_fail(int)
 *     Set the percentage of mana taken if the spell fails
 *     Default: 33
 *
 * set_spell_fail(mixed)
 *     Take special actions if the spell fails
 *     Default: 0
 *
 * set_spell_resist(function f)
 *     Designate a resistance routine for this spell
 *     Default: internal function, spell_resist()
 *
 * set_spell_task(int)
 *     Set the casting difficulty
 *     Default: TASK_ROUTINE
 *
 * set_spell_resist_task(int)
 *     Set the difficulty level for resisting the spell
 *     Default: TASK_FORMIDABLE
 *
 * set_spell_stationary(int)
 *     Designate that the spell will fail if the caster moves
 *     Default: true
 *
 * set_spell_vocal(int)
 *     Designate that the spell requires the caster to be able to
 *     speak
 *     Default: true
 *
 * set_spell_visual(int)
 *     Designate that the spell requires the caster to be able to
 *     see (for most spells, this can be handled by the targeting
 *     routine)
 *     Default: true
 * 
 * set_spell_peaceful(int)
 *     Designate that the spell cannot be cast in combat
 *     Default: false
 *
 * set_spell_no_reveal(int)
 *     Designate that casting should not reveal a hidden caster
 *     Default: false
 * 
 * set_spell_target(function)
 *     Give a function to be called to find the targets of the spell
 *     Default: internal function, spell_target_caster()  
 *
 * set_spell_target_verify(function)
 *     Verify that targets are still valid at the point of casting
 *     Default: 0
 *
 * set_spell_exp_factor(int)
 *     Set a percentage of normal general exp this spell is to
 *     give the caster.
 *     Default: 100 
 *
 * Other functions available
 * =========================
 * (mixed*)make_spell_effect_object(mixed, object, object *, int *, int)
 *      Create, default configure, and move spell effect objects
 *      to the targets.
 *
 * To give custom messages when casting is started, redefine concentrate_msg()
 * To take special action when casting is aborted, redefine abort_spell()
 * To take special action when casting is broken, redefine break_spell()
 *
 * Changelog:
 *   - Inserted calls to set the concentrate property when starting a spell,
 *     and unsetting it if concentrate_spell doesn't succeed.
 *        Petros, January 2009
 *   - Added support for query_spell_ingredients and query_spell_optional_ingredients
 *     so that spells can customize the usage depending on the situation.
 *        Petros, October 2009
 *   - Added support so that wizards and npcs can ignore ingredients. Wizards
 *     need to add a special prop.
 *        Petros, December 2009
 *   - Added failure_chance when casting while holding shields. Mostly to
 *     make it more difficult for casters to wear 2 shields and turn themselves
 *     into tanks.
 *        Arman/Lucius, September 2017
 *   - Fixed an issue in check_required_items where optional components bugged
 *     out.
 *        Carnak, May 2018
 *   - Removed nomask from query_success.
 *        Arman, May 2020
 */
#pragma strict_types

#include <files.h>
#include <wa_types.h>

#include "defs.h"

inherit TIMED_ABILITY_LIB;
inherit ABILITY_DIR+"spell_hooks";
inherit ABILITY_DIR+"resist";
inherit ABILITY_DIR+"components";
inherit ABILITY_DIR+"spell_targetting";

#include <comb_mag.h>
#include <tasks.h>
#include <ss_types.h>
#include <macros.h>

static string
     Spell_desc;          /* Description of the spell */

static mixed
     Ingredients,         /* The list of ingredients needed */  
     Ingredients_opt,
     Spell_object,        /* Object to clone when spell is cast */
     Spell_fail;          /* The message given if the spell fails */

static function
     Spell_resist;       /* For calculating resistance */

static int
     Spell_task,          /* The difficulty */
     Spell_resist_task,   /* The difficulty to resist*/
     Form_skill,          /* The form skill */
     Element_skill,       /* The element skill */
     Form_needed,         /* The form skill needed */
     Element_needed,      /* The element skill needed */
     Mana_needed;         /* Amount of mana needed to cast the spell */

static float               
     Mana_fail;           /* The % of mana to reduce when spell fails */
     

static mapping saved_args=([]);

// Defines
#define WIZ_IGNORE_INGREDIENTS_PROP "_wizard_ignore_spell_ingredients"

// Prototypes
public int      query_spell_can_be_learned(object player);
public int      has_sufficient_skill(object caster);
public int *    query_insufficient_skills(object caster);


public int 
query_spell()
{
    return 1;
}

/* These functions are simple renames for the same functions in
 * the underlying ability classes.
 */


public void 
set_spell_fail(mixed fail)
{
    set_ability_fail(fail);
}

/*
 * Function:    query_spell_fail
 * Description: When the spell fails, this message is the one that gets
 *              returned.
 */
public mixed
query_spell_fail()
{
    return query_ability_fail();
}

public void 
set_spell_name(string name)
{
    set_ability_name(name);
}

public string 
query_spell_name()
{
    return query_ability_name();
}

public void 
set_spell_time(int time)
{
    set_ability_time(time);
}

public int
query_spell_time()
{
    return query_ability_time();
}

public void 
set_spell_offensive(int i)
{
    set_ability_offensive(i);
}

public void 
set_spell_task(int task)
{
    Spell_task = task;
}

public int 
get_spell_task()
{
    return Spell_task;
}

public int 
set_spell_no_reveal(int i)
{
    set_ability_no_reveal(i);
}

/*
 * Function name: set_spell_ingredients
 * Description:   Set the ingredients needed for the spell.
 * Arguments:     1. (mixed *)  An array of ingredients needed for the spell
 *                   (function) Function that produces an ingredient list
 */
public varargs void
set_spell_ingredients(mixed list)
{
    Ingredients = list;
}

/*
 * Function:    ignore_spell_ingredients
 * Description: Function that allows a person to ignore spell ingredients
 *              By default, npcs and wizards who have a special property
 *              set will be able to ignore spell ingredients.
 */
public int
ignore_spell_ingredients(object caster)
{
    if (!objectp(caster))
    {
        return 0;
    }
    
    if (caster->query_npc())
    {
        // NPCs always ignore ingredients
        return 1;
    }
    else if ((caster->query_wiz_level()
              || wildmatch("*jr", caster->query_real_name()))
             && caster->query_prop(WIZ_IGNORE_INGREDIENTS_PROP))
    {
        return 1;
    }
    
    return 0;
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
    return 0;
}

/*
 * Function:    query_spell_ingredients
 * Description: Returns an string array of ingredients or 0 if there are
 *              none defined. It will properly handle if Ingredients variable
 *              is a function as well.
 * Arguments    bShowAlways - If set to non-zero, will not call the ignore
 *                            function. Allows one to always return the total
 *                            ingredients.
 */
public string *
query_spell_ingredients(int bShowAlways = 0)
{
    string * ingredients;
    object player = this_player();
    
    if (!bShowAlways && ignore_spell_ingredients(player))
    {
        return ingredients;
    }
    
    if (functionp(Ingredients))
    {
        function ingredients_func = Ingredients;
        ingredients = ingredients_func(this_player());
    }
    else if (objectp(Ingredients))
    {
        ingredients = ({ Ingredients });
    }
    else if (pointerp(Ingredients))
    {
        ingredients = Ingredients;
    }
    
    return ingredients;
}

/*
 * Function name: set_spell_ingredients
 * Description:   Set the optional ingredients for the spell.
 * Arguments:     1. (mixed *)  An array of ingredients needed for the spell
 *                   (function) Function that produces an ingredient list
 */
public varargs void
set_spell_optional_ingredients(mixed list)
{
    Ingredients_opt = list;
}

/*
 * Function:    query_spell_optional_ingredients
 * Description: Returns an string array of ingredients or 0 if there are
 *              none defined. It will properly handle if Ingredients_opt
 *              variable is a function as well.
 * Arguments    bShowAlways - If set to non-zero, will not call the ignore
 *                            function. Allows one to always return the total
 *                            ingredients.
 */
public string *
query_spell_optional_ingredients(int bShowAlways = 0)
{
    string * ingredients;
    object player = this_player();

    if (!bShowAlways && ignore_spell_ingredients(player))
    {
        return ingredients;
    }
    
    if (functionp(Ingredients_opt))
    {
        function ingredients_func = Ingredients_opt;
        ingredients = ingredients_func(this_player());
    }
    else if (objectp(Ingredients_opt))
    {
        ingredients = ({ Ingredients_opt });
    }
    else if (pointerp(Ingredients_opt))
    {
        ingredients = Ingredients_opt;
    }
    
    return ingredients;
}

public void 
set_spell_element(int element, int skill)
{
    Element_skill = element;
    Element_needed = skill;
}

/*
 * Function:    query_spell_element_skill
 * Description: Returns the actual element skill number that is required
 *              for the spell.
 */
public int
query_spell_element()
{
    return Element_skill;
}

/*
 * Function:    query_spell_element_skill
 * Description: Returns the actual element skill number that is required
 *              for the spell.
 */
public int
query_spell_element_skill()
{
    return Element_skill;
}

/*
 * Function:    query_spell_element_needed
 * Description: Returns the number of skill levels needed in order to
 *              cast the spell successfully for the set element.
 */
public int
query_spell_element_needed()
{
    return Element_needed;
}

public void 
set_spell_form(int form, int skill)
{
    Form_skill = form;
    Form_needed = skill;
}

/*
 * Function:    query_spell_form_skill
 * Description: Returns the actual form skill number that is required
 *              for the spell.
 */
public int
query_spell_form_skill()
{
    return Form_skill;
}

/*
 * Function:    query_spell_form_needed
 * Description: Returns the number of skill levels needed in order to
 *              cast the spell successfully for the set form.
 */
public int
query_spell_form_needed()
{
    return Form_needed;
}

public void 
set_spell_peaceful(int i)
{
    set_ability_peaceful(i);
}

public void 
set_spell_stationary(int i)
{
    set_ability_stationary(i);
}

public void 
set_spell_vocal(int i)
{
    set_ability_vocal(i);
}

public void 
set_spell_visual(int i)
{
    set_ability_visual(i);
}

public void 
set_spell_mana(int mana)
{
    Mana_needed = mana;
}

public int 
get_spell_mana()
{
    return Mana_needed;
}


/*
 * Function name: set_spell_mana_fail
 * Description:   Set the % value of how much mana that should be
 *                reduced when the spell fails.
 * Arguments:     1. (int) The % value.
 */
public void
set_spell_mana_fail(int proc)
{
    Mana_fail = itof(proc) / 100.0; 
}


public void 
set_spell_target(mixed target)
{
    set_ability_target(target);
}

public void 
set_spell_resist(mixed resist)
{
    Spell_resist = resist;
}

public void 
set_spell_resist_task(int task)
{
    Spell_resist_task = task;
}


/*
 * Function name: set_spell_desc
 * Description:   Give a description for this spell.  This should be relatively
 *                brief, not a full explanation of the spell's workings.
 * Arguments:     1. (string) The description text.
 */
public void
set_spell_desc(string desc)
{
    Spell_desc = desc;
}

/* 
 * Function name: query_spell_desc
 * Description:   Get the description of the spell
 * Returns:       (string) The description.
 */
public string
query_spell_desc()
{
    return Spell_desc;
}

/*
 * Function name: set_spell_object
 * Description:   Designate a spell effect object which will be cloned and
 *                configured automatically by the spell.
 * Arguments:     1. (string)   The path to the spell effect object
 *                   (object)   A spell effect object instance
 *                   (function) A function returning a spell effect instance
 */
public void
set_spell_object(mixed ob)
{
    Spell_object = ob;
}

/*
 * Function name: query_spell_object
 * Description:   Query the spell effect object setting
 */
public mixed
query_spell_object()
{
    return Spell_object;
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
    caster->catch_tell("You begin to concentrate on the spell.\n");
    tell_room(environment(caster), QCTNAME(caster) + " closes "
        + caster->query_possessive() + " eyes and concentrates.\n",
        ({ caster }), caster);
}

/*
 * Function name: reduce_mana
 * Description:   Test to see if the caster has sufficient mana, and reduce
 *                it by a given amount, if so.
 * Arguments:     1. (object) The caster
 *                2. (int)    The amount of mana to take (a positive value)
 *                3. (int)    If true, only test if the caster has sufficient
 *                            mana.  Do not reduce the mana.
 * Returns:       1 - caster had sufficient mana
 *                0 - caster did not have sufficient mana
 */
public varargs int
reduce_mana(object caster, int amnt, int test)
{
    if (caster->query_mana() < amnt)
    {
        return 0;
    }

    if (!test)
    {
        send_debug_message("spell_base", "Reducing caster mana by "
            + amnt);
        caster->add_mana(-amnt);
    }

    return 1;
}

/*
 * Function:    process_mana
 * Description: Mana is taken in increments, once at the beginning of the
 *              cast, and once at the completion of the cast. This is
 *              to reduce the amount of penalty for a failed cast.
 */
public int
process_mana(object caster, int execute)
{
    // Some mana is reduced during the start of the ability, and the
    // rest is reduced when the ability actually executes.
    // check_valid_action is called twice. We take different amounts
    // depending on whether "execute" is set or not.   
    int reduce_now, needed, total;
    
    total = get_spell_mana();
    if (execute)
    {
        reduce_now = ftoi(itof(total) * (1.0 - Mana_fail));
        needed = reduce_now;
    }
    else
    {
        reduce_now = ftoi(itof(total) * Mana_fail);
        needed = total;
    }
    
    /* Do we have enough mana to cast the spell? */
    if (!reduce_mana(caster, needed, 1))
    {
        hook_no_mana_fail(this_object());
        return 0;
    }

    reduce_mana(caster, reduce_now);
    return 1;
}

static int 
check_valid_action(object caster, mixed * targets,
                   string arg, int execute = 0)
{
    // Spells cannot be cast if they cannot be learned. It's necessary
    // to add it here because spells can be added as command abilities
    // in the command soul.
    if (!query_spell_can_be_learned(caster))
    {
        // We don't have any error messages simply because the
        // command just shouldn't be available until it is learnable.
        caster->catch_tell("What?\n");
        return 0;
    }

    mixed why;

    object room = environment(caster);

    why = RNMAGIC(room);
    if (why)
    {
        hook_room_no_magic_fail(why, room);
        return 0;
    }

    if (Ability_offensive &&
        (why = RNMATTACK(room)))
    {
        hook_room_no_magic_attack_fail(why, room);
        return 0;
    }
    
    if (!has_sufficient_skill(caster))
    {
        hook_insufficient_skill(caster, query_insufficient_skills(caster));
        return 0;
    }
    
    return 1;
}

static mixed * 
check_required_items(object actor, mixed * targets, string arg, int pretest)
{    
    string * ingredients = query_spell_ingredients(),
           * optional = query_spell_optional_ingredients();
    mixed * found = find_components(actor, ingredients);
    
    if (sizeof(found) != sizeof(ingredients))
    {
        hook_no_ingredients_fail(ingredients);
        if (pointerp(found))
        {
            // Need to remove the property
            restore_components(found);
        }
        return 0;
    }

    // We have to loop through the components and see if there are herbs
    // that we cannot identify
    if (sizeof(found))
    {
        foreach (object ingredient : found)
        {
            if (objectp(ingredient) && IS_HERB_OBJECT(ingredient)
                && ingredient->do_id_check(actor) == 0)
            {
                hook_no_identify_herb_ingredient(ingredient);
                restore_components(found);
                return 0;
            }
        }
    }
        
    // We have the ingredients. That means we can properly reduce mana.
    if (!process_mana(actor, (pretest + 1) % 2)) // (x + 1) % 2 inverts the boolean
    {
        // Insufficient mana. The error message is thrown in process_mana
        // so all we need to do is restore the components
        if (pointerp(found))
        {
            restore_components(found);
        }
        return 0;
    }

    if (pretest)
    {
        // When checking for required items in start_ability, we
        // don't actually want to do anything with the components.
        // We will just restore them and return an empty array to
        // indicate that it passed.
        if (pointerp(found))
        {
            restore_components(found);
        }
        return ({ });
    }
    
    found += find_components(actor, optional) || ({ });

    return found;
}

/*
 * Function:    query_adjusted_spell_task
 * Description: Adjusts the task based on the needed skill and forms and how
 *              much more skill the caster has beyond the minimum threshold.
 */
public int
query_adjusted_spell_task(object caster)
{
    int task = get_spell_task();
    int elem = caster->query_skill(query_spell_element_skill()),
        form = caster->query_skill(query_spell_form_skill());

    task -= (query_spell_element_needed() < elem ? (elem - query_spell_element_needed()) :0);
    task -= (query_spell_form_needed() < form ? (form - query_spell_form_needed()) : 0);
    
    return task;
}

public mixed *
query_casting_success_task()
{
    return ({ 
            SKILL_WEIGHT, 70, query_spell_element_skill(),
            SKILL_WEIGHT, 70, query_spell_form_skill(),
            SKILL_WEIGHT, 20, TS_INT,
            SKILL_WEIGHT, 20, TS_WIS,
            SKILL_WEIGHT, 20, TS_DIS, 
            });
}

/*
 * Function name: query_casting_success
 * Description:   Determine if a spell is successfully cast
 * Returns:       The result as an integer indicating success or
 *                failure (0 indicating failure, positive integer
                  indicating % success, possibly > 100)
 */
static int
query_casting_success(object caster)
{
    int task = query_adjusted_spell_task(caster);

    // If changes are made to the weighting, please update test_casting_success output
    // methods.
    return max(0, caster->resolve_task(task, query_casting_success_task()));
}

/*
 * Function:    test_casting_success
 * Description: Tests the casting success of this spell for this specific caster
 *              over 10000 (default) iterations.
 */
public float
test_casting_success(object caster, int iterations = 1000)
{
    int successes = 0;
    for (int iteration = 0; iteration < iterations; ++iteration)
    {
        if (query_casting_success(caster) > 0)
        {
            ++successes;
        }
    }
    write("Relevant Factors for Casting Success:\n");
    write("Task: " + get_spell_task() + " [adjusted " + query_adjusted_spell_task(caster) + "]\n");
    write("Element Skill (weighted 70): " 
        + caster->query_skill(query_spell_element_skill()) 
        + " [min " + query_spell_element_needed() + "]\n");
    write("Form Skill (weighted 70): " + caster->query_skill(query_spell_form_skill()) 
        + " [min " + query_spell_form_needed() + "]\n");
    write("INT (weighted 20): " + caster->query_stat(SS_INT) + "\n");
    write("WIS (weighted 20): " + caster->query_stat(SS_WIS) + "\n");
    write("DIS (weighted 20): " + caster->query_stat(SS_DIS) + "\n");
    return (itof(successes) / itof(iterations)) * 100.0;
}


/*
 * Function name: resolve_spell
 * Description:   This function is responsible for performing the routines
 *                necessary to produce the spell effect(s).  All spells that
 *                manifest any effect whatsoever need to redefine this and
 *                implement those.
 * Arguments:     1. (object)   The caster
 *                2. (object *) The targets
 *                3. (int *)    Resistance values corresponding to each target
 *                4. (int)      The casting result as returned by
 *                              query_casting_success()
 */
public void
resolve_spell(object caster, mixed *targets, int *resist, int result)
{
}

/*
 * Function:    query_insufficient_skills
 * Description: Returns the skills that are not high enough to cast this
 *              spell.
 */
public int *
query_insufficient_skills(object caster)
{
    int * needed_skills = ({ });
    if (caster->query_skill(query_spell_element_skill()) < query_spell_element_needed())
    {
        needed_skills += ({ query_spell_element_skill() });
    }
    if (caster->query_skill(query_spell_form_skill()) < query_spell_form_needed())
    {
        needed_skills += ({ query_spell_form_skill() });
    }
    
    return needed_skills;
}

public int
has_sufficient_skill(object caster)
{
    // If the caster doesn't have the minimum skill requirements to cast
    // the spell, we should let them know
    return (sizeof(query_insufficient_skills(caster)) == 0);
}

/*
 * Function name: target_spell
 * Description:   Find the target(s) for spell invocation.
 * Arguments:     1. (object) The caster
 *                2. (string) Arguments passed to the "cast" command
 * Returns:       (object *) The targets found.
 */
public nomask object *
target_spell(object actor, string arg)
{
    return target_ability(actor, arg);
}

/* 
 * Function:    config_spell
 * Description: This is the function that every spell should override in
 *              order to customize the parameters defined inside of
 *              default_config_ability in this file.
 */
public void
config_spell()
{
}
            
public mixed 
use_spell_resist(object actor, mixed target, string name)
{
    object spell_target;
    if (Spell_resist)
    {
        if (pointerp(target) && sizeof(target))
        {
            spell_target = target[0];
        }
        else
        {
            spell_target = target;
        }
        return Spell_resist(actor, spell_target, query_spell_element_skill(), 
                            Spell_resist_task);
    }
    return 0;
}

public nomask void
set_ability_pending(object actor, object room, int set)
{
    object abort;
    object * aborts;
    
    ::set_ability_pending(actor, room, set);
    
    if (!objectp(actor))
    {
        // actor could have been destructed and is no longer valid.
        return;
    }
    
    // Set up the concentrate property to stop normal melee
    // combat when casting a spell.
    if (set)
    {
        // This gets set in start_ability
        actor->add_prop(LIVE_O_CONCENTRATE, this_object());
        // Add the spell abort object
        setuid();
        seteuid(getuid());
        abort = clone_object(ABILITY_DIR + "std/spells/abort_spell_obj");
        abort->set_spell_file(MASTER_OB(this_object()));
        abort->move(actor, 1);
    }
    else
    {
        // This gets unset in execute_ability
        actor->remove_prop(LIVE_O_CONCENTRATE);
        // Remove the spell abort object
        aborts = filter(all_inventory(actor), &->id("_abort_spell_object"));
        if (sizeof(aborts))
        {
            aborts->remove_object();
        }
    }
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
}

/*
 * Function name: abort_spell
 * Description:   Take special actions when casting is aborted
 * Arguments:     1. (object) The caster.
 */
public void
abort_spell(object caster)
{
}

/*
 * Function name: list_spells
 * Description:   This function is called to list the spells from
 *                the player soul when the command "spells" is used.
 */
public void
list_spells()
{
    string desc = query_spell_desc() || "";
    write(sprintf("%-15s %s\n", query_spell_name(), desc));
}

/*
 * Function name: make_spell_effect_object
 * Description:   Create, default configure, and move spell effect objects
 *                to the targets.
 * Arguments:     1. (object)   The spell effect object
 *                   (string)   The filename of the spell effect (to be cloned)
 *                   (function) A function that returns a spell effect
 *                2. (object)   The caster
 *                3. (object)   The target
 *                   (object *) An array of targets
 *                4. (int)      Resistance value for single target
 *                   (int *)    Resistance values corresponding to each target
 *                5. (int)      The casting success, as given by
 *                              query_casting_success()
 * Returns:       (object *) An array of spell effect objects, one element for
 *                           each target
 *                (object)   A single spell effect object if target was
 *                           specified as a single object.
 */
public mixed
make_spell_effect_object(mixed obj, object caster, mixed targets, 
                         mixed resist, int result)
{
    int i;
    object spell, *obs;
    function f;
    object *target_arr;
    int *resist_arr;

    target_arr = (pointerp(targets) ? targets : ({ targets }));
    resist_arr = (pointerp(resist)  ? resist  : ({ resist }));
    i = sizeof(target_arr);
    obs = allocate(i);

    setuid();
    seteuid(getuid());
    while (i--)
    {
        if (functionp(obj))
        {
            f = obj;
            spell = f(caster, targets);
        }
        else if (stringp(obj))
        {
            spell = clone_object(obj);
        }
        else
        {
            spell = obj;
        }

        obs[i] = spell;

        spell->set_spell_effect_name(query_ability_name());
        spell->set_spell_effect_element(query_spell_element_skill());
        spell->set_spell_effect_form(query_spell_form_skill());
        spell->set_spell_effect_power((caster->query_skill(query_spell_element_skill()) +
            caster->query_skill(query_spell_form_skill()) + query_spell_element_needed() +
            query_spell_form_needed()) / 4);
        spell->set_spell_effect_caster(caster);
        spell->set_spell_effect_target(target_arr[i]);

        if (!spell->setup_spell_effect())
        {
            // Should we destroy the spell effect object?
            obs[i] = 0;
        }
    }

    if (pointerp(targets))
    {
        return obs;
    }

    return obs[0];
}

/*
 * Function:    do_ability_setup
 * Description: This function calls do_spell_setup. Here we do some
 *              basic initialization functions.
 */
public nomask int
do_ability_setup(object player, mixed * targets, string arg)
{
    return this_object()->do_spell_setup(player, targets, arg);
}

/*
 * Function:	modify_casting_success
 * Description: Further modify query_casting_success() based on
 * 		additional factors not allowed to be masked.
 * Arguments:	int result   - The task result from query_casting_success.
 * 		object actor - The spellcaster
 */
static nomask int
modify_casting_success(int result, object actor)
{
    // We already failed, no modification necessary.
    if (!result)
	return result;

    object *shields = filter(actor->query_armour(-1),
	&operator(==)(A_SHIELD) @ &->query_at());

    // Not wearing any shields, return un-modified.
    if (!sizeof(shields))
	return result;

    int count, fail_chance;
    foreach(object item: shields)
    {
	/* This was made a static table both for ease
	 * of reading and also future adaptability.
	 */
	int slots = sizeof(item->query_shield_slots());
	switch(++count)
	{
	case 1:  /* One shield worn. */
	    switch(slots) {
	    case 0..1: /* First slot free. */	break;
	    case 2:	fail_chance += 2;	break;
	    case 3:	fail_chance += 4;	break;
	    default:	fail_chance += 10;	break;
	    }
	    break;
	case 2:  /* Two shields worn. */
	    switch(slots) {
	    case 0..1:	fail_chance += 40;	break;
	    case 2:	fail_chance += 50;	break;
	    case 3:	fail_chance += 60;	break;
	    default:	fail_chance += 70;	break;
	    }
	    break;
	default: /* Three+ shields, are we a cephalopad? */
	    fail_chance = 1000;
	    break;
	}
    }

    /* 'result' gives unpredictable numbers
     * so we emulate a simple d100 roll.
     */
    if (random(100) > fail_chance)
	return result;

    hook_casting_shield_failure(actor, shields);
    return 0;
}

/*
 * Function:    query_success
 * Description: Determines whether this spell has been cast successfully.
 */
// static nomask int
public int
query_success(object actor, object target, mixed *items)
{
    int result = query_casting_success(actor);
    return modify_casting_success(result, actor);
}

static nomask void 
resolve_ability(object actor, mixed * items, 
                mixed * targets, int *resist, mixed *results)
{
    if (results[0] > 0)
    {
        resolve_spell(actor, targets, resist, results[0]);
    }
    else
    {
        mixed fail_message = query_spell_fail();
        if (functionp(fail_message))
        {
            function f = fail_message;
            write(f());
        }
        else if (stringp(fail_message))
        {
            write(fail_message);
        }
        // Spells which fail shouldn't consume ingredients
        if (sizeof(items))
        {
            // Restore the components since they aren't being used
            restore_components(items);
        }
        return;
    }

    // Consume the spell components here.
    if (sizeof(items))
    {
        items = filter(items, not @ &->use_component());
        hook_use_ingredients(items);
        items->remove_object();
    }
}

public nomask void
ability_msg(object caster, mixed * targets, string arg)
{
    concentrate_msg(caster, targets, arg);
}

public void 
hook_special_complete()
{
    // Spells don't indicate that they're finished.
}

public void
hook_stopped_ability(object ability, object player)
{
    player->catch_tell("You stop concentrating on the spell.\n");
}

public varargs string
query_restricted_ability_message(string ability, object player)
{
    string short_desc;
    
    short_desc = ability->short();
    if (!strlen(short_desc))
    {
        return "You are busy casting a spell.\n";
    }
    
    return "You are too busy casting a spell to "
        + short_desc + ".\n";    
}

/*
 * Function name: start_spell_fail
 * Description:   masked to allow the spell ability system to 
 *                take over, instead of allowing the old spell
 *                system.
 * Arguments:     verb - The verb that initiated this spell.
 *                arg  - The arguments to the verb.
 * Returns:       True if the spell failed, false otherwise
 */
public int
start_spell_fail(string verb, string arg)
{
    do_ability(arg);
    
    // Always return 1. This is to fake the /std/living/spells.c
    // start_spell out and convince it to not do anything.
    return 1;
}

public int
exist_command(string verb)
{
    return (query_spell_name() == verb);
}

/*
 * Function:    query_spell_can_be_learned
 * Description: This function is called by /d/Genesis/specials/abilities.c
 *              in order to determine whether the player can actually
 *              add this spell. This will allow guilds to customize the
 *              learning path for the caster guild, limiting access to
 *              spells until certain conditions are met.
 */
public int
query_spell_can_be_learned(object player)
{
    // By default, this spell can be learned by anyone. Guilds should
    // mask this and return 1 or 0 based on specific guild requirements.
    return 1;
}

/*
 * Function:    default_config_ability
 * Description: This function gets called during the "create" loading function
 *              of the object. We specify all the defaults for spells here.
 *              They should be overridden as necessary inside of config_spell.
 */
public nomask void
default_config_ability()
{
    ::default_config_ability();
    set_ability_time(5);
    set_ability_offensive(0);
    set_ability_fail(0);
    set_ability_no_reveal(0);
    set_ability_vocal(1);
    set_ability_visual(1);
    set_ability_peaceful(0);
    set_ability_target(spell_target_caster);
    set_ability_target_verify(spell_verify_present);
    set_spell_ingredients(0);
    set_spell_optional_ingredients(0);
    set_spell_element(SS_ELEMENT_FIRE, 40);
    set_spell_form(SS_FORM_TRANSMUTATION, 40);
    set_spell_mana(1000);
    set_spell_stationary(1);
    set_spell_task(TASK_ROUTINE);
    set_spell_resist(spell_resist);
    set_ability_resist(use_spell_resist);
    set_spell_resist_task(TASK_FORMIDABLE);
    set_spell_mana_fail(33);
    set_ability_exclusive(1);
}

/*
 * Function:    create_spell
 * Description: This is called by create_ability, which is called by create.
 *              It should only be called once for the loading of the object.
 *              We do all initialization routines here, including the initial
 *              configuration of the ability.
 */
public void
create_spell()
{
    config_spell();
}

/*
 * Function:    create_ability
 * Description: This is called by the object's "create" function. We call
 *              the create_spell function, which can be overridden by
 *              spells and make this one nomask.
 */
public nomask void
create_ability()
{
    create_spell();
}
