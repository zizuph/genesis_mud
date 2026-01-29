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
 *
 *   - Set all spells to be in a default spell-specific group so they do
 *        not interfere with other guild specials.
 *        Zizuph, Aug 2022.
 *
 *   For resolve_spell based components, use F_PENMOD(40, 100) as the baseline
 *   instead of F_PENMOD(60, 100), since spell enhancers aren't that high.
 *
 */
#pragma strict_types

#include <files.h>
#include <wa_types.h>

#include "defs.h"

inherit COMBAT_ABILITY_LIB;

inherit SPELL_HOOKS_LIB;
inherit RESIST_LIB;
inherit SPELL_TARGETTING_LIB;

#include <comb_mag.h>
#include <tasks.h>
#include <ss_types.h>
#include <macros.h>
#include <formulas.h>

static string
     Spell_desc;          /* Description of the spell */

static mixed
     Spell_object,        /* Object to clone when spell is cast */
     Spell_fail;          /* The message given if the spell fails */

static function
     Spell_resist;       /* For calculating resistance */

static int
     Spell_class,         /* The class from 0-4 */
     Spell_task,          /* The difficulty */
     Spell_resist_task,   /* The difficulty to resist*/
     Form_skill,          /* The form skill */
     Element_skill,       /* The element skill */
     Form_needed,         /* The form skill needed */
     Element_needed,      /* The element skill needed */
     Tohit_based;         /* Use tohit for the result, rather than pen */
     

static string SPELL_DEFAULT_GROUP = "spell_default_group";

static mapping saved_args=([]);

// Prototypes
public int      query_spell_can_be_learned(object player);
public int      has_sufficient_skill(object caster);
public int *    query_insufficient_skills(object caster);
static nomask int query_spell_tohit(object actor, mixed target, mixed *items);

public int 
query_spell()
{
    return 1;
}

/* These functions are simple renames for the same functions in
 * the underlying ability classes.
 */

public varargs void set_spell_ingredients(mixed list) { set_ability_ingredients(list); }
public varargs void set_spell_optional_ingredients(mixed list) { set_ability_optional_ingredients(list); }
public string * query_spell_ingredients(int bShowAlways = 0) { return query_ability_ingredients(bShowAlways); }
public string * query_spell_optional_ingredients(int bShowAlways = 0) { return query_ability_optional_ingredients(bShowAlways); }
public string query_spell_ingredients_description() { return query_ability_ingredients_description(); }
public void set_spell_fail(mixed fail) { set_ability_fail(fail); }
public mixed query_spell_fail() { return query_ability_fail(); }
public void set_spell_name(string name) { set_ability_name(name); }
public string query_spell_name() { return query_ability_name(); }
public void set_spell_time(int time) { set_ability_time(time); }
public int query_spell_time() { return query_ability_time(); }
public void set_spell_offensive(int i) { set_ability_offensive(i); }
public void set_spell_target(mixed target) { set_ability_target(target); }
public int set_spell_no_reveal(int i) { set_ability_no_reveal(i); }
public void set_spell_peaceful(int i) { set_ability_peaceful(i); }
public void set_spell_stationary(int i) { set_ability_stationary(i); }
public void set_spell_vocal(int i) { set_ability_vocal(i); }
public void set_spell_visual(int i) { set_ability_visual(i); }
public nomask object * target_spell(object actor, string arg) { return target_ability(actor, arg); }
public void set_spell_mana(int mana) { set_ability_resource_needed(mana); }
public int get_spell_mana() { return query_ability_resource_needed(); }
public void set_spell_mana_fail(int proc) { set_ability_resource_fail(itof(proc) / 100.0); }
public nomask void set_spell_mana_factor(mixed factor) { set_ability_resource_factor(factor); }

/*
 * Function:    query_spell_mana_factor
 * Description: Returns what the spell factor set by this spell is
 */
public nomask float
query_spell_mana_factor()
{
    if (functionp(query_ability_resource_factor))
    {
        function f = query_ability_resource_factor;
        return f();
    }
    
    return query_ability_resource_factor();
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

public void
set_spell_class(int class)
{
    Spell_class = class;
}

public int get_spell_class()
{
    return Spell_class;
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
/*
 * Function:    query_spell_tohit_based
 * Description: Returns whether to use tohit as the pen, and avoid a
 *              separate tohit check.
 */
public int
query_spell_tohit_based()
{
    return Tohit_based;
}

/*
 * Function:    set_spell_tohit_based
 * Description: If set, the spell will call resolve_spell with the tohit
 *              value instead of the pen, and not do a separate tohit check.
 */
public void
set_spell_tohit_based(int val)
{
    Tohit_based = val;
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

static void 
resolve_compound_combat_special(object actor, object *targets, int *hitlocs,
    int *random_hitlocs, int *pen, int *damage_types, mixed * items,
    int *resist, int *results)
{
    object *spelltarget = ({});
    int    *spellresist = ({}),
            spellpen = 0;
    
    for(int i = 0; i < sizeof(targets); i++)
    {
        if (results[i] > 0)
        {
            spelltarget += ({ targets[i] });
            spellresist += ({ resist[i] });
            spellpen += pen[i];
        }
    }
    
    if (spellpen > 0)
    {
        // Calculate the success of the spell.
        spellpen = 100 * spellpen / F_PENMOD(40, 100);
        spellpen /= sizeof(spelltarget);
        spellpen = random(spellpen / 4) + random(spellpen / 4)
                 + random(spellpen / 4) + random(spellpen / 4);
        resolve_spell(actor, spelltarget, spellresist, spellpen);
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
    set_ability_concentrate(1);
    set_ability_hit_function(query_spell_tohit);
    set_ability_resource(mana);
    set_ability_stats(({ TS_INT }));
    set_ability_abort(1);
    set_ability_group(SPELL_DEFAULT_GROUP);
    set_ability_apply_resistance_function(spell_resist_modify_value);
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

public nomask int
convert_task_to_hit(int task)
{
    switch(task)
    {
        case TASK_SIMPLE:
            return 120;
        case TASK_EASY:
            return 110;
        case TASK_ROUTINE:
            return 100;
        case TASK_HARD:
            return 90;
        case TASK_DIFFICULT:
            return 70;
        case TASK_EXACTING:
            return 50;
        case TASK_FORMIDABLE:
            return 30;
        case TASK_IMPOSSIBLE:
            return 10;
        default:
            return 65;
    }
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
    int result = convert_task_to_hit(get_spell_task());
    
    if (query_spell_tohit_based())
    {
        result = result * query_ability_base_skill(actor, items) / 100;
    }
    
    return result;
} /* query_ability_hit */

/*
 * Normalize offensive / defensive values
 *
 */
static int
fixnorm(int offence, int defence)
{
   if (offence + defence == 0)
       return 0;

   return ((100 * offence) / (offence + defence)) - 50;
} /* fixnorm */

static nomask int
query_spell_tohit(object actor, mixed target, mixed *items)
{
    int     tmp, whit, wchit, tar_dis;
    
    wchit = query_ability_hit(actor, target, items);
    tmp = 40; // Adventurers guild value as base.
    
    if (living(target) && query_ability_offensive(({ target })))
    {
        // Doctor Who, what?
        tar_dis = target->query_stat(SS_DIS);
        
        tmp = max(20, target->query_skill(SS_SPELLCRAFT));
        tmp += max(20, target->query_skill(SS_FORM_ABJURATION));
        
        // Give NPCs a boost as they usually dont have spellcraft or
        // abjuration.
        if (target->query_npc())
        {
            if (!target->query_skill(SS_SPELLCRAFT))
                tmp += target->query_average_stat() / 4;
            if (!target->query_skill(SS_FORM_ABJURATION))
                tmp += target->query_average_stat() / 4;
            tmp = min(tmp, 200);
        }

        if (!CAN_SEE_IN_ROOM(actor) ||
            (target->query_prop(OBJ_I_INVIS) > actor->query_prop(LIVE_I_SEE_INVIS)))
        {
            wchit = actor->query_skill(SS_BLIND_COMBAT) * wchit / 100;
        }

        if (!CAN_SEE_IN_ROOM(target) ||
            (actor->query_prop(OBJ_I_INVIS) > target->query_prop(LIVE_I_SEE_INVIS)))
        {
            tmp = target->query_skill(SS_BLIND_COMBAT) * tmp / 100;
        }
    }
    
    // Lets calculate based on dis compared to average for self-casts and 
    // objects.
    if (!living(target) || actor == target)
        tar_dis = actor->query_average_stat();
    
    whit = 4 * fixnorm(random(wchit) + random(wchit) + random(wchit)
           + random(wchit), random(tmp));
    whit += 2 * fixnorm(actor->query_stat(SS_DIS), tar_dis);

    send_debug_message("debug_spell_tohit", 
       sprintf("wchit %d, defence %d, whit %d",
       wchit, tmp, whit));

    
    if (whit > 0)
        return 1;
    else
        return whit - 1;
} /* query_spell_tohit */

/*
 * Function name:   restart_npc_special
 * Description:     A function which repeats special abilities for NPCs.
 * Arguments:       1. (object) actor
 *                  2. (string) arg
 * Returns:         Nothing
 */
public void
restart_npc_special(object actor, string arg)
{
    // Spells shouldnt default to repeating
} /* restart_npc_special */