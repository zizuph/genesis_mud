/* spellcasting.c - Spellcasting routines
 *
 * Usage:
 * 1) inherit this module in your spellcasting object
 * 2) add calls to add_spell_object() and remove_spell_object()
 *    to your object (generally in enter_env() and leave_env(), 
 *    respectively).
 * 3) in the constructor of your object, add each spell using
 *    add_spell()
 * 4) configure your spells
 *
 * Example:
 * inherit "/std/object";
 * inherit "/d/Genesis/magic/spellcasting";
 *
 * void
 * create_object()
 * {
 *     set_name("talisman");
 *     ... configure object ...
 *    
 *     add_spell("hokuspokus", "Mysterious spell", create_hokuspokus,
 *         target_one_living);
 * }
 *
 * void
 * enter_env(object env, object from)
 * {
 *     ::enter_env(env, from);
 *     add_spell_object(env);
 * }
 *
 * void
 * leave_env(object env, object to)
 * {
 *     ::leave_env(env, to);
 *     remove_spell_object(env);
 * }
 *
 * int
 * create_hokuspokus(object caster, object *targets, string args)
 * {
 *     set_spell_time(10);
 *     set_spell_mana(80);
 *     set_spell_ingredients(({ "garlic" }));
 *     set_spell_task(TASK_ROUTINE);
 *     set_spell_element(SS_ELEMENT_LIFE, 40);
 *     set_spell_form(SS_FORM_TRANSMUTATION, 40);
 *     set_spell_resist(spell_resist);
 *     set_spell_target_verify(spell_verify_present);
 *     set_spell_effect(hokuspokus);
 *     return 0; // 0 indicates successful configuration
 * }
 *
 * void
 * hokuspokus(object caster, object *targets, int *resist, int result)
 * {
 *     if (random(100) < resist[0])
 *     {
 *         caster->catch_tell("Nothing happened!\n");
 *         return;
 *     }
 * 
 *     if (target[0]->id("vampire") || 
 *         target[0]->query_guild_member("Vampires of Emerald"))
 *     {
 *         caster->catch_tell("Poof!\n");
 *         target[0]->catch_tell(caster->query_The_name(target[0]) +
 *             " utters the magic word, \"Hokuspokus\", and you " +
 *             "turn into a bat!\n");
 *
 *         ... turn target into bat ...
 *    }
 * }
 *     
 *
 * Spell configuration functions available
 * =======================================
 * set_spell_time(int)
 *     Set the amount of casting time required (in seconds)
 *     Default: 6
 *
 * set_spell_ingredients(mixed ingrs)
 *     Set the components required for casting
 *     Default: no components
 *
 * set_spell_optional_ingredients(mixed ingrs, function f)
 *     Set the optional components allowed for casting and
 *     a function to call with the list of optional ingredients
 *     that are found
 *
 * set_spell_offensive(int)
 *     Designate the spell as an offensive spel
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
 * set_spell_conc_message(mixed)
 *     Give a special message when concentration begins
 *     Default: 0
 *
 * set_spell_mana_fail(int)
 *     Set the percentage of mana taken if the spell fails
 *     Default: 33
 *
 * set_spell_fail(mixed)
 *     Take special actions if the spell fails
 *     Default: 0
 *
 * set_spell_resist(mixed)
 *     Set the resistance value for this spell
 *     Default: internal function, spell_resist()
 *
 * set_spell_conc(function)
 *     Take special actions when concentration begins
 *     Default: internal function, spell_concentrate()
 *
 * set_spell_cast(function)
 *     Use a nonstandard casting routine
 *     Default: interal function, spell_cast()
 *
 * set_spell_effect(function)
 *     Generate the effects of a successful spell
 *     Default: function with the same name as the spell (if it exists)
 *
 * set_spell_task(int)
 *     Set the casting difficulty
 *     Default: TASK_ROUTINE
 *
 * set_spell_resist_task(int)
 *     Set the difficulty level for resisting the spell
 *     Default: TASK_FORMIDABLE
 *
 * set_spell_resolve(function)
 *     Use a different routine to determine casting success
 *     Default: internal function, spell_resolve()
 *
 * set_spell_target_verify(function)
 *     Verify that targets are still valid at the point of casting
 *     Default: 0
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
 *     Default: true
 * 
 * set_spell_break(mixed)
 *     Give a special message when concentration is broken
 *     Default: 0
 *
 * set_spell_abort(mixed)
 *     Give a special message when concentration is aborted
 *     Default: 0
 *
 * Spell resistance functions available
 * ====================================
 * spell_resist
 *     Standard spell resistance, factoring in stats, skills, and 
 *     magic resistance.
 *
 * spell_resist_basic
 *     Basic resistance, factoring in magic resistance only.
 *
 * spell_resist_illusion
 *    Resistance to magical illusions, factoring in stats, skills,
 *    and magic resistance
 *
 * spell_resist_identify
 *    Resistance to identification spells (for both living and nonliving
 *    targets)
 *
 * spell_resist_healing
 *    Resistance to healing spells
 *
 * spell_resist_beneficial
 *    Resistance to beneficial spells
 *
 * Spell targeting functions available
 * ===================================
 * spell_target_caster
 *     Spell targeted on the caster
 *
 * spell_target_one_present_enemy
 *     Spell targeted on the caster's current "enemy"
 *
 * spell_target_present_enemies
 *     Spell targeted on all present enemeies
 *
 * spell_target_present_team
 *     Spell targeted on caster's team (including caster)
 *
 * spell_target_present_team_others
 *     Spell targeted on caster's team (excluding caster)
 *
 * spell_target_one_present_living
 *     Spell targeted on a single specified living
 *
 * spell_target_one_other_present_living
 *     Spell targeted on a single specified living other than
 *     the caster
 *
 * spell_target_present_livings
 *     Spell targeted on one or more specified livings
 *
 * spell_target_one_present_non_living
 *     Spell targeted on one specified non-living
 *
 * spell_target_present_non_livings
 *      Spell targeted on one or more specified non-livings
 *
 * spell_target_one_present_object
 *      Spell targeted on one present object
 *
 * spell_target_present_objects
 *      Spell targeted on one or more present objects
 *
 * spell_target_one_distant_living
 *      Spell targeted on one non-present living
 * 
 * spell_target_one_distant_known_living
 *      Spell targeted at one known (met) living
 *
 * Spell target verification functions available
 * =============================================
 * spell_verify_present
 *      Verify that targets are still present in the environment
 *      of the caster
 *
 * Other functions available
 * =========================
 * (object *)make_spell_effect_object(mixed, object, object *, int *, int)
 *      Create, default configure, and move spell effect objects
 *      to the targets.
 *
 * Spell components
 * ================
 * Spell components are found and used automatically by the spell
 * casting routine.
 * Necessary components are specified with the set_spell_ingredients()
 * function, which accepts an array of mixed values, one for each
 * component expected.  An object pointer element designates that
 * particular object as a component.  A function pointer element will
 * be called with two arguments, an array of possible component objects
 * and an array of components already found; the function should return
 * an object pointer to the component found.  A string element will
 * first be checked against the true names of any herbs that the caster
 * is able to identify; if no matching herbs are found, parse_command()
 * is used to try to match an object.  Note that only one object will be
 * matched:  strings of the form "two swords" or "second stick" will not
 * work.  "two swords" can, however, be simulated with two elements,
 * "sword" and "sword".
 * Components may define the function use_component(), which can be used
 * to implement special behaviour in an object when it is used as a
 * component (reusable components, for example).  If use_component()
 * returns 1, it will not be destroyed.
 */

/* TODO
 *      Check for a LIVE_O_SPELL_ATTACK before allowing another
 *      spell to be started.
 *
 *      Verify that in all cases of failure, that it removes the
 *      concentrating prop.
 */

#pragma strict_types

inherit "/d/Genesis/magic/resist";
inherit "/d/Genesis/magic/targeting";
inherit "/d/Genesis/magic/components";
inherit "/d/Genesis/magic/spell_config";
inherit "/d/Genesis/magic/hooks";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include <comb_mag.h>
#include <tasks.h>

#define SPELL_ARR_DESC         0
#define SPELL_ARR_CREATE_FUNC  1
#define SPELL_ARR_TARGET_FUNC  2
#define SPELL_ARR_TARGET_STAGE 3
#define SPELL_ARR_SIZE         4

#define LIVE_O_CASTING_ENV       "_live_o_casting_env"

#ifndef MAGIC_I_RES_ILLUSION
#define MAGIC_I_RES_ILLUSION "_magic_i_res_illusion"
#endif

static string              
     gArg,                 /* The argument given to cast the spell */
     gSpell;
                           
static int                 
     gMana_left;           /* Mana to reduce when the spell is cast */
                           
static object              
    *gTargets,             /* A list of target(s) to cast the spell on */
    *gFound_ingrs,         /* A list of found ingredients */
    *gFound_opt_ingrs,
     gCaster;              /* The one who casts the spell */
                           
static mapping
     gSpells = ([]);

nomask public int spell_cast(object caster, object *targets, string arg);
static int spell_resolve(object caster);
public object query_caster();

public int spell_concentrate(object caster, object *targets, string arg);

/*
 * Function name: default_config_spell
 * Description:   Set the default values for the variables
 */
public void
default_config_spell(string spell)
{
    set_spell_time(6);
    set_spell_ingredients(0);
    set_spell_optional_ingredients(0, 0);
    set_spell_offensive(0);
    set_spell_target_verify(0);
    set_spell_element(SS_ELEMENT_FIRE, 40);
    set_spell_form(SS_FORM_TRANSMUTATION, 40);
    set_spell_mana(1000);
    set_spell_stationary(1);
    set_spell_conc_message(0);
    set_spell_task(TASK_ROUTINE);
    set_spell_resist_task(TASK_FORMIDABLE);
    set_spell_resolve(spell_resolve);
    set_spell_mana_fail(33);
    set_spell_fail(0);
    set_spell_resist(spell_resist);
    set_spell_conc(spell_concentrate);
    set_spell_cast(spell_cast);
    set_spell_effect(mkfunction(spell, this_object()));
    set_spell_no_reveal(0);
    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_peaceful(0);
    set_spell_break(0);
    set_spell_abort(0);
    set_spell_name(spell);
}

/*
 * Function name: add_spell
 * Description:   Add the spell to the list of active spells.
 * Arguments:     string name           - The activating verb string
 *                string desc           - Description of the spell
 *                function create_func  - The function to call to configure
 *                                        the spell
 *                function target_func  - The function to call to find
 *                                        targets
 *                int target_stage      - The stage in which to find targets.
 *                                        If false, targets are found at
 *                                        concentration; otherwise, they are
 *                                        found at casting time.
 */
nomask varargs void
add_spell(string name, string desc, function create_func, 
    function target_func, int target_stage)
{
    mixed *arr = allocate(SPELL_ARR_SIZE);

    arr[SPELL_ARR_DESC]         = desc;
    arr[SPELL_ARR_CREATE_FUNC]  = create_func;
    arr[SPELL_ARR_TARGET_FUNC]  = target_func;
    arr[SPELL_ARR_TARGET_STAGE] = target_stage;

    gSpells[name] = arr;
}

/*
 * Function name: remove_spell
 * Description:   Remove the spell with the given verb string.
 * Arguments:     string name - The name of the spell to remove.
 */
nomask public void
remove_spell(string name)
{
    gSpells = m_delete(gSpells, name);
}

/*
 * Function name: list_spells
 * Description:   This function is called to list the spells from
 *                the player soul when the command "spells" is used.
 */
public void
list_spells()
{
    int i;
    string *verbs = m_indices(gSpells);

    i = sizeof(verbs);
    while (i--)
    {
        write(sprintf("%-15s %s\n", verbs[i],
            gSpells[verbs[i]][SPELL_ARR_DESC]));
    }
}

/*
 * Function name: query_spell_targets
 * Description:   Returns all the found targets
 * Returns:       An array of target objects
 */
public object *
query_spell_targets()
{
    return gTargets;
}

/*
 * Function name: query_found_ingredients
 * Description:   Returns all the ingredients found
 * Returns:       An array of ingredient objects
 */
public object *
query_found_ingredients()
{
    return gFound_ingrs;
}

/*
 * Function name: query_found_optional_ingredients
 * Description:   Returns all the optional ingredients found
 * Returns:       An array of ingredient objects
 */
public object *
query_found_optional_ingredients()
{
    return gFound_opt_ingrs;
}

/*
 * Function name: query_spell_map
 * Description:   Get the spell mapping (gSpells)
 * Returns:       A mapping.
 */
public mapping
query_spell_map()
{
    return secure_var(gSpells);
}

/*
 * Function name: query_caster
 * Description:   Return the caster of the spell
 */
public object
query_caster()
{
    return gCaster;
}

/*
 * Function name: query_spell_arg
 * Description:   Returns the argument
 */
public mixed
query_spell_arg() 
{ 
    return gArg; 
}

/*
 * Function name: spell_resolve
 * Description:   Determine if a spell is successfully cast
 * Returns:       The result as an integer indicating success or
 *                failure (0 indicating failure, positive integer
 *                indicating % success)
 */
static int
spell_resolve(object caster)
{
    int task = gSpell_task;
    int elem = caster->query_skill(gElement_skill),
        form = caster->query_skill(gForm_skill);

    task += (gElement_needed > elem ? (gElement_needed - elem) * 50 :0);
    task += (gForm_needed > form ? (gForm_needed - form) * 50 : 0);

    return max(0, caster->resolve_task(task, ({
        SKILL_WEIGHT, 70, elem,
        SKILL_WEIGHT, 70, form,
        SKILL_WEIGHT, 20, TS_INT,
        SKILL_WEIGHT, 20, TS_WIS,
        SKILL_WEIGHT, 20, TS_DIS, })));
}

/*
 * Function name: check_skills
 * Description:   Check the skills on the caster and see if they
 *                are high enough.
 * Returns:       True if it is ok, false otherwise.
 */
public int
check_skills(object caster, int spell_form, int min_form, int spell_elem,
    int min_elem)
{
    return ((min_form <= caster->query_skill(spell_form)) &&
            (min_elem <= caster->query_skill(spell_elem)));
}

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

public int
spell_concentrate(object caster, object *targets, mixed arg)
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

    /* Are we skilled enough to cast this spell? */
    if (!check_skills(caster, gForm_skill, gForm_needed, 
        gElement_skill, gElement_needed))
    {
        hook_no_skills_fail();
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

    /* The spell is ready to be cast. */
    caster->add_prop(LIVE_O_CONCENTRATE, this_object());
    caster->add_prop(LIVE_O_CASTING_ENV, room);

    return 0;
}

/*
 * Function name: filter_kill_access
 * Description:   This function is called from the filter command in
 *                spell_cast, to find all objects that the caster is
 *                able to cast a spell on.
 * Arguments:     ob - The victim
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

public int
test_movement_fail(object caster)
{
    if (gCaster->query_prop(LIVE_O_CASTING_ENV) != environment(gCaster))
    {
        if (gSpell_stationary)
        {
            return 1;
        }

        if (gCaster->query_prop(LIVE_O_CASTING_ENV) !=
            gCaster->query_prop(LIVE_O_LAST_ROOM))
        {
            if (random(gSpell_task / 3) >
                (random(gCaster->query_skill(SS_SPELLCRAFT)) +
                random(gCaster->query_stat(SS_DIS))))
            {
                return 1;
            }
        }
        else if (random(gSpell_task / 4) >
            (random(gCaster->query_skill(SS_SPELLCRAFT)) +
            random(gCaster->query_stat(SS_DIS))))
        {
            return 1;
        }
    }

    return 0;
}

/*
 * Function name: spell_cast
 * Description:   This function handles the actual casting of the spell.
 * Arguments:     object caster   - the caster
 *                object *targets - an array of spell targets
 *                mixed arg       - arguments to spell invocation
 * Returns:       1 - casting success
 *                0 - casting failure, default fail message
 *                string - casting failure, use string for fail message
 */
nomask public mixed
spell_cast(object caster, object *targets, mixed arg)
{
    mixed result, why;
    int delay, *resist;
    object target, *ingrs, *combatants;
    function f;

    caster->remove_prop(LIVE_O_CONCENTRATE);

    if (gSpells[gSpell][SPELL_ARR_TARGET_STAGE] &&
        (f = gSpells[gSpell][SPELL_ARR_TARGET_FUNC]))
    {
        gTargets = targets = f(caster, arg);
    }

    targets = filter(targets, objectp);
    if (!sizeof(targets))
    {
        return 0;
    }

    if (gTarget_verify)
    {
        gTargets = targets = gTarget_verify(caster, targets, arg);
    }
    else
    {
        gTargets = targets;
    }
    
    if (gSpells[gSpell][SPELL_ARR_TARGET_FUNC] && !sizeof(targets))
    {
        hook_targets_gone();
        return 0;
    }

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
        gTargets = targets = filter(targets, &filter_kill_access(caster));

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

        targets->attacked_by(caster);
    }
 
    /* Make sure we are in the same room as we were when we started */
    if (test_movement_fail(caster))
    {
        hook_changed_env();
        return 0;
    }

    /* Do we have the proper ingredients? */
    if (!(gFound_ingrs = find_components(caster, gIngredients)))
    {
        hook_no_ingredients_fail(gIngredients);
        return 0;
    }

    gFound_opt_ingrs = find_components(caster, gIngredients_opt) || ({});

    if (gIngredients_opt_fun)
    {
        gIngredients_opt_fun(caster, gFound_opt_ingrs);
    }

    /* Check if the spell is successfully cast */
    result = gSpell_resolve(caster);
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

        restore_components(gFound_ingrs);
        restore_components(gFound_opt_ingrs);

        return result;
    }

    if (!reduce_mana(caster, gMana_left))
    {
        hook_no_mana_fail();
        restore_components(gFound_ingrs);
        restore_components(gFound_opt_ingrs);
        return 0;
    }
    
    if (!gSpell_resist)
    {
        resist = allocate(sizeof(targets));
    }
    else
    {
        resist = map(targets, 
            &gSpell_resist(caster, , gElement_skill, gSpell_resist_task));
    }

    if (gSpell_effect)
    {
        gSpell_effect(caster, targets, resist, result);
    }

    if (sizeof(ingrs = gFound_ingrs + gFound_opt_ingrs))
    {
        ingrs = filter(ingrs, not @ &->use_component());
        hook_use_ingredients(ingrs);
        ingrs->remove_object();
    }
 
    restore_components(gFound_ingrs);
    restore_components(gFound_opt_ingrs);

    return 1;
}

/*
 * Spell object registration functions
 */

/*
 * Function name: add_spell_object
 * Decription:    Call this to add the spells defined by this object to
 *                a living
 * Arguments:     object ob - the living receiving the spells
 */
public void
add_spell_object(object ob)
{
    ob->add_spellobj(this_object());
}

/*
 * Function name: remove_spell_object
 * Description:   Call this to remove the spells definied by this object from
 *                a living
 * Arguments:     object ob - the living from whom the spells are to be removed
 */
public void
remove_spell_object(object ob)
{
    ob->remove_spellobj(this_object());
}
    
/*
 * The following functions called by the basic spell routines
 * found in the player object.
 */

/*
 * Function name: break_spell
 * Description:   Called when concentration is broken
 * Arguments:     string spell   - the spell that was broken
 *                object breaker - what broke the spell
 */
public void
break_spell(string spell, object breaker)
{
    function f;

    if (!gSpell_break)
    {
        return;
    }

    if (functionp(gSpell_break))
    {
        f = gSpell_break;
        f(breaker);
        return;
    }

    gCaster->catch_tell(gSpell_break);
}

/*
 * Function name: abort_spell
 * Description:   Called when concentration is aborted
 * Arguments:     string spell - the spell that was aborted
 */
public void
abort_spell(string spell)
{
    function f;

    if (!gSpell_abort)
    {
        return;
    }

    if (functionp(gSpell_abort))
    {
        f = gSpell_abort;
        f();
        return;
    }

    gCaster->catch_tell(gSpell_abort);
}

/*
 * Function name: query_spell_time
 * Description:   It is called from cmdhooks.c, and should return the time
 *                in seconds it takes to prepare the spell. The actual time
 *                will be (time + 2 + LIVE_I_ATTACK_DELAY).
 * Arguments:     verb - The verb that initiated this spell.
 *                arg  - The arguments to the verb.
 * Returns:       The time in seconds.
 */
public int
query_spell_time(string verb, mixed arg)
{
    return gSpell_time + 
        (gSpell_offensive ? gCaster->query_prop(LIVE_I_ATTACK_DELAY) : 0);
}

/*
 * Function name: query_spell_mess
 * Description:   It is called from cmdhooks.c, and it us used to change the
 *                standard message given when a spell is being prepared. You
 *                should handle all the printouts by yourself.
 * Arguments:     verb - The verb that initiated this spell.
 *                arg  - The arguments to the verb.
 * Returns:       True if you are handeling the printouts yourself, 
 *                false otherwise.
 */
public int
query_spell_mess(string verb, mixed arg)
{
    function f;
    if (functionp(gConc_msg))
    {
        f = gConc_msg;
        f(gCaster, gTargets, gArg);
        return 1;
    }

    if (stringp(gConc_msg))
    {
        write(gConc_msg);
        return 1;
    }

    /* We want the standard messages */
    return 0;
}

/*
 * Function name: start_spell_fail
 * Description:   Called to initiate spell concentration.  This is where
 *                we initialize the spell, do some preliminary checks. and
 *                apply initial spell costs
 * Arguments:     verb - The verb that initiated this spell.
 *                arg  - The arguments to the verb.
 * Returns:       True if the spell failed, false otherwise
 */
nomask public int
start_spell_fail(string verb, mixed arg)
{
    function f;

    default_config_spell(verb);

    gCaster = this_player();

    gArg = arg;
    gSpell = verb;
    gTargets = ({});
    gFound_ingrs = ({});
    gFound_opt_ingrs = ({});

    if (!gSpells[verb][SPELL_ARR_TARGET_STAGE] &&
        (f = gSpells[verb][SPELL_ARR_TARGET_FUNC]))
    {
        if (!sizeof(gTargets = f(gCaster, arg)))
        {
            return 1;
        }
    }

    f = gSpells[verb][SPELL_ARR_CREATE_FUNC];
    if (f(gCaster, gTargets, arg))
    {
        return 1;
    }

    return gSpell_conc(gCaster, gTargets, arg);
}

/* 
 * Function name: do_command
 * Description:   Called to initiate the actual spell casting
 * Returns:       1 - success
 *                0/string - failure
 */
nomask public mixed
do_command(string verb, string arg)
{
    return gSpell_cast(gCaster, gTargets, gArg);
}

/* 
 * Function name: exist_command
 * Description  : Check if a spell exists.
 * Returns      : 1/0 depending on success.
 */
nomask public int
exist_command(string verb)
{
    return !!gSpells[verb];
}


/*
 *-> When casting an attack spell to initiate a combat or when changing
 *   enemy will give the spell longer preparation time, the time will
 *   be added with: 5 - LIVE_I_QUICKNESS seconds.
 *
 *-> The following has been changed:
 *     stdproperties.h  - added LIVE_I_CONCENTRATE
 *                      - added LIVE_S_BREAK_CONCENTRATE
 *     /secure/master.c - In modify_commands added check for
 *                        LIVE_I_CONCENTRATE
 *     cbase.c          - In heart_beat added check for
 *                        LIVE_I_CONCENTRATE
 *     cmdhooks.c       - In cmdhooks_break_spell, added remove_prop on
 *                        LIVE_I_CONCENTRATE
 *                    - In my_command, at the end, removed
 *                      add_attack_delay
 *
 */
