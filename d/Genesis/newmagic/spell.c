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
 */

inherit "/d/Genesis/newmagic/resist";
inherit "/d/Genesis/newmagic/hooks";
inherit "/d/Genesis/newmagic/components";
inherit "/d/Genesis/newmagic/targeting";

#include <comb_mag.h>
#include <files.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>

#define LIVE_O_CASTING_ENV       "_live_o_casting_env"

#ifndef MAGIC_I_RES_ILLUSION
#define MAGIC_I_RES_ILLUSION "_magic_i_res_illusion"
#endif

#ifndef F_SPELL_EXP
#define F_SPELL_EXP(mana, task, power, factor)  max(0, ftoi(itof(mana) * \
        (itof(power * factor) / 1000.0)) + ((task - TASK_ROUTINE) / 2))
#endif

static mixed
     gSpell_fail,          /* The message given if the spell fails */
     gSpell_break,
     gSpell_object,
     gIngredients,         /* The list of ingredients needed */  
     gIngredients_opt;
  
static int 
     gSpell_exp_factor,    /* The general exp factor for this spell */
     gSpell_time,          /* The time it takes to prepare the spell */
     gMana_needed,         /* Amount of mana needed to cast the spell */
     gSpell_offensive,     /* True if it is a combat initiating spell*/
     gSpell_stationary,    /* If the spell requires standing still */
     gForm_skill,          /* The form skill */
     gElement_skill,       /* The element skill */
     gForm_needed,         /* The form skill needed */
     gElement_needed,      /* The element skill needed */
     gSpell_resist_task,   /* The difficult of resisting the spell */
     gSpell_task,          /* The difficulty of the spell */
     gSpell_no_reveal,     /* True if the spell should not reveal the caster
                              if hidden */
     gSpell_vocal,
     gSpell_visual,
     gSpell_peaceful;

static float               
     gMana_fail;           /* The % of mana to reduce when the spell fails */
                           
static function            
     gSpell_resist,        /* Resistance calculation routine for the spell */
     gSpell_target,
     gSpell_target_verify;

static string
     gSpell_name,
     gSpell_desc;


static private int
     gMana_consumed,
     gMana_left;

static object
    *gReq_ingrs_found,
    *gOpt_ingrs_found,
    *gOpt_ingrs_used;

public void default_config_spell();
public varargs int config_spell(object caster, object *targets, string arg);

/*
 * Function name: create_spell
 * Description:   Configure this spell.
 *
 * Note:          If you need to reset various spell settings on a per-casting
 *                basis (vary casting time based on the level of the caster,
 *                for instance), use config_spell().
 */
public void
create_spell()
{
    // This is for backward compatibility.
    config_spell(0);
}

private nomask void
create()
{
    default_config_spell();
    create_spell();
}

/*
 * Function name: set_spell_exp_factor
 * Description:   Set the general experience factor for this spell from
 *                a range of 0 - 150 % of normal.
 * Arguments:     1. (int) the experience factor
 */  
public void
set_spell_exp_factor(int i)
{
    gSpell_exp_factor = min(150, max(0, i));
}

/*
 * Function name: query_spell_exp_factor
 * Description:   Returns the general exp factor for this spell
 */
public int
query_spell_exp_factor()
{
    return gSpell_exp_factor;
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
    gIngredients = list;
}

/*
 * Function name: query_spell_ingredients
 * Description:   Returns the gIngredients variable. Can be overridden to 
 *                customize the ingredients returned based on the caster
 * Arguments:     1. (object) The person to get the ingredients for
 */
public mixed
query_spell_ingredients(object caster = 0)
{
    // Wizards with a special property set (via a clasp) can ignore all components.
    // In order for this to work correctly, the spell's components must be set
    // via the "set_pot_spell_ingredients" function.
    if (objectp(caster) && caster->query_prop("_wizard_ignore_spell_ingredients"))
    {
        return ({ });
    }

    return gIngredients;
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
    gIngredients_opt = list;
}

/*
 * Function name: set_spell_offensive
 * Description:   Designate the spell as being offensive (one initiating
 *                combat)
 * Arguments:     1. (int) True if the spell is offensive
 */
public void
set_spell_offensive(int offensive)
{
    gSpell_offensive = offensive;
}

/*
 * Function name: set_spell_stationary
 * Description:   Designate the spell as being stationary (caster may not
 *                move while concentrating).
 * Arguments:     1. (int) True if spell is stationary
 */
public void
set_spell_stationary(int i)
{
    gSpell_stationary = i;
}

/*
 * Function name: set_spell_time
 * Description:   Set the time it takes to prepare the spell.
 * Arguments:     1. (int) The time it should take in seconds
 */
public void
set_spell_time(int time)
{
    gSpell_time = time;
}

public int
query_spell_time()
{
    return gSpell_time;
}

/*
 * Function name: set_spell_element
 * Description:   Set the element type and the minimum of skill needed.
 * Arguments:     1. (int) The element type, as found in /sys/ss_types.h
 *                2. (int) The value in skill needed for the spell.
 */
public void
set_spell_element(int element, int skill)
{
    gElement_skill = element;
    gElement_needed = skill;
}

/*
 * Function name: query_spell_element
 * Description:   Return the element skill.
 */
public int
query_spell_element()
{
    return gElement_skill;
}

/*
 * Function name: set_spell_form
 * Description:   Set the form type and the minimum of skill needed.
 * Arguments:     1. (int) The form type, as found in /sys/ss_types.h
 *                2. (int) The skill-value needed for the spell.
 */
public void
set_spell_form(int form, int skill)
{
    gForm_skill = form;
    gForm_needed = skill;
}

/*
 * Function name: query_spell_form
 * Description:   Return the form skill.
 */
public int
query_spell_form()
{
    return gForm_skill;
}

/*
 * Function name: set_spell_mana
 * Description:   Set the amount of mana needed to cast the spell.
 * Arguments:     1. (int) The amount of mana
 */
public void
set_spell_mana(int mana)
{
    gMana_needed = mana;
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
    gMana_fail = itof(proc) / 100.0; 
}

/*
 * Function name: set_spell_fail
 * Description:   Designate a special message to be used when the spell fails.
 * Arguments:     1. (function) A function which can be called to obtain the
                                failure message.
 *                   (string)   A static failure message.
 */
public void
set_spell_fail(mixed fail)
{
    gSpell_fail = fail;
}

/*
 * Function name: set_spell_resist
 * Description:   Set the function to use to get a target's resistance in %.
 *                The function should use query_magic_res() to search for the
 *                properties.
 * Arguments:     1. (function) - The function to be used
 */
public void
set_spell_resist(function res)
{
    gSpell_resist = res; 
}

/*
 * Function name: set_spell_task
 * Description:   Set the difficulty of the spell as found in /sys/tasks.h
 * Arguments:     1. (int) The task difficulty
 */
public void
set_spell_task(int task) 
{ 
    gSpell_task = task; 
}

/* 
 * Function name: set_spell_resist_task
 * Description:   Set the difficulty level for resisting the spell.  Use the
 *                task difficulties as found in /sys/tasks.h
 * Arguments:     1. (int) The task difficulty
 */
public void
set_spell_resist_task(int task)
{
    gSpell_resist_task = task;
}

/*
 * Function name: set_spell_target
 * Description:   Indicate which function to use to determine the spell's
 *                target. This function should be of the form
 *
 *                     object *func(object, string)
 *
 *                where the first argument is the caster, and the second is
 *                the string argument passed to the "cast" command.  The
 *                function returns an array of targets, empty if none were
 *                found.
 *
 * Arguments:     1. (function) The targeting function
 */
public void
set_spell_target(function f)
{
    gSpell_target = f;
}

/*
 * Function name: set_spell_target_verify
 * Description:   Indicate which function to use to determine if targets are
 *                still valid when the spell is resolved.  This function should
 *                be of the form
 *
 *                     object *func(object, object *, string)
 *
 *                where the first argument is the caster; the second is an
 *                array containing the targets, as determined when
 *                concentration began; the third is the string argument passed
 *                to the "cast" command.  The function returns an array of
 *                valid targets, empty if none were valid.
 *
 * Arguments:     1. (function) The verification function.
 */
public void
set_spell_target_verify(function f)
{
    gSpell_target_verify = f;
}

/* 
 * Function name: set_spell_no_reveal
 * Description:   Indicate that casting this spell will not reveal a hidden
 *                caster.
 * Arguments:     1. (int) If true, don't reveal the caster.
 */
public void
set_spell_no_reveal(int i)
{
    gSpell_no_reveal = i;
}

/*
 * Function name: query_spell_no_reveal
 * Description:   Returns a true value if the spell reveals the caster upon
 *                casting.
 * Returns:       true/false, indicating whether the caster is not revealed
 */
public int
query_spell_no_reveal()
{
    return gSpell_no_reveal;
}

/* 
 * Function name: set_spell_vocal
 * Description:   Indicate that the spell requires the caster to use his
 *                voice.  Such spells are not possible when the
 *                LIVE_M_MOUTH_BLOCKED property is true.
 * Arguments:     1. (int) If true, spell requires voice.
 * 
 * TODO:          Classify vocal spells as ACTION_AURAL.
 */
public void
set_spell_vocal(int i)
{
    gSpell_vocal = i;
}

/*
 * Function name: set_spell_visual
 * Description:   Indicate that the spell requires the caster to be able to
 *                see in his environment and to see the target, if there is
 *                one.
 * Arguments:     1. (int) If true, spell requires caster to see.
 */
public void
set_spell_visual(int i)
{
    gSpell_visual = i;
}

/*
 * Function name: set_spell_peaceful
 * Description:   Indicate that the spell cannot be cast in combat.
 * Arguments:     1. (int) If true, spell cannot be cast in combat.
 */
public void
set_spell_peaceful(int i)
{
    gSpell_peaceful = i;
}

/* 
 * Function name: set_spell_name
 * Description:   Designate a name for the spell.  This will be used as an
 *                argument to the "cast" command to cast this spell.
 * Arguments:     1. (string) The name of the spell.  Do not include spaces.
 */
public void
set_spell_name(string name)
{
    gSpell_name = name;
}

/*
 * Function name: query_spell_name
 * Description:   Get the name of this spell
 * Returns:       string
 */
public string
query_spell_name()
{
    return gSpell_name;
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
    gSpell_desc = desc;
}

/* 
 * Function name: query_spell_desc
 * Description:   Get the description of the spell
 * Returns:       (string) The description.
 */
public string
query_spell_desc()
{
    return gSpell_desc;
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
    gSpell_object = ob;
}

/*
 * Function name: query_spell_object
 * Description:   Query the spell effect object setting
 */
public mixed
query_spell_object()
{
    return gSpell_object;
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
make_spell_effect_object(mixed obj, object caster,
    mixed targets, mixed resist, int result)
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

        spell->set_spell_effect_name(gSpell_name);
        spell->set_spell_effect_element(gElement_skill);
        spell->set_spell_effect_form(gForm_skill);
        spell->set_spell_effect_power((caster->query_skill(gElement_skill) +
            caster->query_skill(gForm_skill) + gElement_needed +
            gForm_needed) / 4);
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
 * Function name: default_config_spell
 * Description:   Set the default values for the variables
 */
public void
default_config_spell()
{
    set_spell_time(6);
    set_spell_ingredients(0);
    set_spell_optional_ingredients(0);
    set_spell_offensive(0);
    set_spell_element(SS_ELEMENT_FIRE, 40);
    set_spell_form(SS_FORM_TRANSMUTATION, 40);
    set_spell_mana(1000);
    set_spell_stationary(1);
    set_spell_task(TASK_ROUTINE);
    set_spell_resist(spell_resist);
    set_spell_resist_task(TASK_FORMIDABLE);
    set_spell_mana_fail(33);
    set_spell_fail(0);
    set_spell_no_reveal(0);
    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_peaceful(0);
    set_spell_target(spell_target_caster);
}

/*
 * Function name: query_spell_pretarget
 * Description:   Indicates whether this spell should acquire targets before
 *                casting (when concentration begins) or at the moment of
 *                casting.  There is no configuration function to set this, so
 *                you must redefine this function if you don't want the
 *                default.
 * Returns:       true (1) - All spells are pretargeted by default.
 */
public int
query_spell_pretarget()
{
    return 1;
}

/*
 * Function name: target_spell
 * Description:   Find the target(s) for spell invocation.
 * Arguments:     1. (object) The caster
 *                2. (string) Arguments passed to the "cast" command
 * Returns:       (object *) The targets found.
 */
public object *
target_spell(object caster, string arg)
{
    if (gSpell_target)
    {
        return gSpell_target(caster, arg);
    }

    return ({});
}

/*
 * Function name: filter_kill_access
 * Description:   This function is called to determine which targets the
 *                caster is able to attack (in the case of an offensive spell)
 * Arguments:     1. (object) The caster
 *                2. (object) The target
 *                3. (int) If true, don't write failure messages
 * Returns:       True if ok, otherwise false
 */
varargs public int
filter_kill_access(object caster, object ob, int silent)
{
    if (!living(ob) || ob->query_ghost() || ob == caster)
    {
        return 0;
    }

    if (!present(ob, environment(caster)))
    {
        return 0;
    }

    if (NPMATTACK(ob))
    {
        if (!silent)
        {
            hook_living_no_magic_attack_fail(ob);
        }

        return 0;
    }

    if (!F_DARE_ATTACK(caster, ob) && (caster->query_attack() != ob))
    {
        if (!silent)
        {
            hook_dont_dare_attack_fail(ob);
        }

        return 0;
    }

    return 1;
}

/*
 * Function name: test_movement_fail
 * Description:   Determine if the spell fails because the caster moved
 *                during casting.
 * Arguments:     1. (object) The caster
 * Returns:       1 - movement caused spell failure
 *                0 - movement did not cause spell failure
 */
public int
test_movement_fail(object caster)
{
    int diff;

    if (caster->query_prop(LIVE_O_CASTING_ENV) != environment(caster))
    {
        if (gSpell_stationary)
        {
            return 1;
        }

        // We don't want to have to keep track of how many moves the caster
        // makes while casting, so we'll just use this cheap little check
        // to try to figure out if the caster has moved once or more than
        // once.  If he's moved just once, his last room (LIVE_O_LAST_ROOM)
        // should be set to the room where he started casting the spell
        // (LIVE_O_CASTING_ENV); otherwise, he must have moved more than
        // once.
        // This check isn't fool-proof, but I think it's satisfactory.  Even
        // if a player figured out the loophole, it would be difficult to take
        // advantage of it regularly.
        if (caster->query_prop(LIVE_O_CASTING_ENV) !=
            caster->query_prop(LIVE_O_LAST_ROOM))
        {
            // The caster has moved more than one room, so we'll make it
            // slightly harder to continue casting.
            diff = gSpell_task / 3;
        }
        else
        {
            diff = gSpell_task / 4;
        }

        if (diff >
            (random(caster->query_skill(SS_SPELLCRAFT)) +
            random(caster->query_stat(SS_DIS))))
        {
            return 1;
        }
    }

    return 0;
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
        caster->add_mana(-amnt);
    }

    return 1;
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
    int task = gSpell_task;
    int elem = caster->query_skill(gElement_skill),
        form = caster->query_skill(gForm_skill);

    task += (gElement_needed > elem ? (gElement_needed - elem) * 50 :0);
    task += (gForm_needed > form ? (gForm_needed - form) * 50 : 0);

    return max(0, caster->resolve_task(task, ({
        SKILL_WEIGHT, 70, gElement_skill,
        SKILL_WEIGHT, 70, gForm_skill,
        SKILL_WEIGHT, 20, TS_INT,
        SKILL_WEIGHT, 20, TS_WIS,
        SKILL_WEIGHT, 20, TS_DIS, })));
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
resolve_spell(object caster, object *targets, int *resist, int result)
{
}


/*
 * Function name: cast_spell
 * Description:   This function handles the actual casting of the spell.
 * Arguments:     1. (object)   the caster
 *                2. (object *) the targets
 *                3. (string)   arguments to spell invocation
 * Returns:       1 - casting success
 *                0 - casting failure, default fail message
 *                string - casting failure, use string for fail message
 */
nomask public mixed
cast_spell(object caster, object *targets, string arg)
{
    mixed result, why;
    int delay, *resist;
    object target, *all_ingrs, *combatants, *vtargets;
    function f;

    caster->remove_prop(LIVE_O_CONCENTRATE);

    if (!query_spell_pretarget())
    {
        targets = target_spell(caster, arg);
        if (!targets)
        {
            return 0;
        }
    }

    if (gSpell_target_verify)
    {
        vtargets = gSpell_target_verify(caster, targets, arg);
    }
    else
    {
        vtargets = targets - ({ 0 });
    }

    if ((sizeof(targets) > 0) && (sizeof(vtargets) == 0))
    {
        hook_targets_gone();
        return 0;
    }

    targets = vtargets;

    if (gSpell_peaceful)
    {
        if (sizeof(combatants = (filter(all_inventory(environment(caster)),
            &operator(==)(caster) @ &->query_attack()) |
            ({ caster->query_attack() })) - ({ 0 })))
        {
            hook_combat_fail(combatants);
            return 0;
        }
    }

    if (gSpell_vocal)
    {
        if (why = caster->query_prop(LIVE_M_MOUTH_BLOCKED))
        {
            hook_cannot_speak_fail(stringp(why) ? why : 0);
            return 0;
        }

        /* Check for under water? */
    }

    if (gSpell_visual)
    {
        if (!CAN_SEE_IN_ROOM(caster))
        {
            hook_cannot_see_fail();
            return 0;
        }
    }
    
    if (gSpell_offensive)
    {
        /* Get all targets that we can hit with our spell */
        targets = filter(targets, &filter_kill_access(caster));

        if (!sizeof(targets))
        {
            hook_targets_gone();
            return 0;
        }

        /* Do we need to attack the enemy? */
        if (!(target = caster->query_attack()) ||
            (member_array(target, targets) < 0))
        {
            caster->attack_object(targets[0]);
        }

        /* Let targets start attacking if they aren't already */
        filter(targets, &operator(==)(-1) @
                        &member_array(caster) @
                        &->query_enemy(-1))->attacked_by(caster);
    }
 
    /* Make sure we are in the same room as we were when we started */
    if (test_movement_fail(caster))
    {
        hook_changed_env();
        return 0;
    }

    /* Do we have the proper ingredients? */
    if (!(gReq_ingrs_found = find_components(caster, query_spell_ingredients(caster))))
    {
        hook_no_ingredients_fail(query_spell_ingredients(caster));
        return 0;
    }

    gOpt_ingrs_found = find_components(caster, gIngredients_opt) || ({});

    /* Check if the spell is successfully cast */
    result = query_casting_success(caster);
    if (!result)
    {
        if (gSpell_fail)
        {
            if (functionp(gSpell_fail))
            {
                f = gSpell_fail;
                result = f(caster, targets, arg);
            }
            else
            {
                result = gSpell_fail;
            }
        }

        restore_components(gReq_ingrs_found);
        restore_components(gOpt_ingrs_found);

        return result;
    }

    if (!reduce_mana(caster, gMana_left))
    {
        hook_no_mana_fail();
        restore_components(gReq_ingrs_found);
        restore_components(gOpt_ingrs_found);
        return 0;
    }
    
    gMana_consumed += gMana_left;

    if (!gSpell_resist)
    {
        resist = allocate(sizeof(targets));
    }
    else
    {
        resist = map(targets, 
            &gSpell_resist(caster, , gElement_skill, gSpell_resist_task));
    }

    gOpt_ingrs_used = ({});

    resolve_spell(caster, targets, resist, result);

    if (sizeof(all_ingrs = gReq_ingrs_found + gOpt_ingrs_used))
    {
        all_ingrs = filter(all_ingrs, not @ &->use_component());
        /* For heaps, split one off the heap. We assume only one of each
         * heaped item is needed. */
        all_ingrs->split_heap(1);
        hook_use_ingredients(all_ingrs);
        all_ingrs->remove_split_heap();
        all_ingrs -= FILTER_HEAP_OBJECTS(all_ingrs);
        all_ingrs->remove_object();
    }
 
    restore_components(gReq_ingrs_found);
    restore_components(gOpt_ingrs_found);

    // Okay now that we've cast the spell we reward the caster.

#ifdef SPELLCASTING_XP
    if (gSpell_exp_factor)
    {
        caster->add_exp_general(F_SPELL_EXP(gMana_needed, gSpell_task, 
            (gElement_needed, gElement_skill, gForm_needed, gForm_skill) / 4, 
            gSpell_exp_factor));
    }
#endif

    return 1;
}

/*
 * Function name: query_optional_ingredients_found
 * Returns:       An array of optional ingredients which were found available
 *                to be used by the caster.
 */
public object *
query_optional_ingredients_found()
{
    return gOpt_ingrs_found + ({});
}

/*
 * Function name: use_optional_ingredient
 * Description:   Optional ingredients found are not necessarily used. Those
 *                which *are* used should be designated by calling this
 *                function.
 * Arguments:     1. (mixed) An individual (object) ingredient or an array
 *                           of ingredients.
 */
public void
use_optional_ingredient(mixed ingr)
{
    if (!pointerp(ingr))
    {
        ingr = ({ ingr });
    }

    if (!gOpt_ingrs_used)
    {
        gOpt_ingrs_used = ingr;
    }
    else
    {
        gOpt_ingrs_used += ingr;
    }
}

public void
reclaim_components()
{
    restore_components(gReq_ingrs_found);
    gReq_ingrs_found = ({});
    restore_components(gOpt_ingrs_found);
    gOpt_ingrs_found = ({});
    gOpt_ingrs_used = ({});
}

public void
reclaim_partial_mana(object caster)
{
    if (gMana_left && (gMana_consumed == gMana_needed))
    {
        caster->add_mana(gMana_left);
    }
}

public void
reclaim_full_mana(object caster)
{
    if (gMana_consumed)
    {
        caster->add_mana(gMana_consumed);
    }
}

/*
 * Function name: concentrate_msg
 * Description:   Give messages indicating that spell concentration has begun
 * Arguments:     1. (object)   The caster
 *                2. (object *) The targets
 *                3. (string)   The arguments passed to the "cast" command
 */
public void
concentrate_msg(object caster, object *targets, string arg)
{
    caster->catch_tell("You begin to concentrate on the spell.\n");
}

/*
 * Function name: concentrate_spell
 * Description:   Start concentration on the spell
 * Arguments:     1. (object)   The caster
 *                2. (object *) The targets
 *                3. (string)   The arguments passed to the "cast" command
 * Returns:       0 - Concentration begun
 *                1 - Concentration not begun; spell aborted.
 */
public int
concentrate_spell(object caster, object *targets, string arg)
{
    object room, *combatants;
    mixed why;
    int reduce;
 
    if (caster->query_prop(LIVE_I_STUNNED))
    {
        hook_stun_fail();
        return 1;
    }

    if (!gSpell_no_reveal)
    {
        caster->reveal_me();
    }

    room = environment(caster);

    if (gSpell_peaceful)
    {
        if (sizeof(combatants = (filter(all_inventory(environment(caster)),
            &operator(==)(caster) @ &->query_attack()) |
            ({ caster->query_attack() })) - ({ 0 })))
        {
            hook_combat_fail(combatants);
            return 1;
        }
    }

    if (gSpell_vocal)
    {
        if (why = caster->query_prop(LIVE_M_MOUTH_BLOCKED))
        {
            hook_cannot_speak_fail(stringp(why) ? why : 0);
            return 1;
        }

        /* Check for under water? */
    }

    if (gSpell_visual)
    {
        if (!CAN_SEE_IN_ROOM(caster))
        {
            hook_cannot_see_fail();
            return 1;
        }
    }

    why = RNMAGIC(room);
    if (why)
    {
        hook_room_no_magic_fail(why, room);
        return 1;
    }

    if (gSpell_offensive &&
        (why = RNMATTACK(room)))
    {
        hook_room_no_magic_attack_fail(why, room);
        return 1;
    }

    /* Do we have enough mana to cast the spell? */
    if (!reduce_mana(caster, gMana_needed, 1))
    {
        hook_no_mana_fail();
        return 1;
    }

    reduce = ftoi(itof(gMana_needed) * gMana_fail);

    /* We need to reduce this later, when the spell is cast */
    gMana_left = gMana_needed - reduce;

    reduce_mana(caster, reduce);
    gMana_consumed = reduce;

    /* The spell is ready to be cast. */
    caster->add_prop(LIVE_O_CONCENTRATE, this_object());
    caster->add_prop(LIVE_O_CASTING_ENV, room);

    concentrate_msg(caster, targets, arg);

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
 * Function name: query_spell_mess
 * Description:   Inidicate whether we want the standard concentration
 *                messages or not.
 * Arguments:     1. (object)   The caster
 *                2. (object *) The targets
 *                3. (string)   The arguments passed to the "cast" command
 * Returns:       1 - Do not use default messages
 *                0 - Use default messages.
 */
public int
query_spell_mess(object caster, object *targets, string arg)
{
    // We never use the default messages.  You'll need to override this
    // function and return 0 if you want them.
    return 1;
}

/* 
 * Function name: config_spell
 * Description:   (Re)Configure this spell for this specific casting attempt.
 *                This can be used to redefine certain parameters such as
 *                mana cost, casting time, etc. on a per-casting basis.  It
 *                can also be used to trigger an instant spell failure (no
 *                components/mana consumed).
 * Arguments:     1. (object)   The caster
 *                2. (object *) The targets
 *                3. (string)   The arguments passed to the "cast" command
 * Returns:       0 - Configuration successful.
 *                1 - Configuration not successful.  Casting aborted.
 *
 */
public varargs int
config_spell(object caster, object *targets, string arg)
{
    return 0;
}

/* 
 * Function name: do_spell_setup
 * Description:   This initiates the spell's configuration routines
 * Arguments:     1. (object)   The caster
 *                2. (object *) The targets
 *                3. (string)   The arguments passed to the "cast" command
 * Returns:       0 - Configuration successful.
 *                1 - Configuration not successful.  Casting aborted.
 *
 * NOTE:          do_spell_setup(0) is called to configure the spell when
 *                certain general information is required.  This indicates
 *                that the spell is not being configured for a casting
 *                attempt, and therefore should not return 1.
 */
public varargs int
do_spell_setup(object caster, object *targets, string arg)
{
    gMana_left = 0;
    gMana_consumed = 0;
    //default_config_spell();
    return config_spell(caster, targets, arg);
}

public void
restore_components(object *ingrs)
{
    ::restore_components(ingrs);
}

public void
remove_object()
{
    destruct();
}
