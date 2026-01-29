/* spell_config.c - Spell configuration routines
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
 * Other functions available
 * =========================
 * (object *)make_spell_effect_object(mixed, object, object *, int *, int)
 *      Create, default configure, and move spell effect objects
 *      to the targets.
 */

static mixed
     gConc_msg,            /* The message given when concentration starts */
     gSpell_fail,          /* The message given if the spell fails */
     gSpell_break,
     gSpell_abort,
     gSpell_object,

     gSpell_resist,        /* Resistance amount for the spell */

     gIngredients,         /* The list of ingredients needed */  
     gIngredients_opt;
  
static int                 
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
     gSpell_conc,          /* Use this function to start concentration */
     gSpell_cast,          /* Use this function to cast the spell */
     gSpell_effect,        /* Use this function to apply spell effects */
     gTarget_verify,       /* Use this function to verify a target */

     gSpell_resolve,       /* Use this function to resolve casting success */
     gIngredients_opt_fun;

static string
     gSpell_name;

/*
 * Function name: set_spell_conc
 * Description:   Use an alternative routine to start concentration on 
 *                a spell.
 * Arguments:     function f - The function to call to initiate concentration
 */
public void
set_spell_conc(function f)
{
    gSpell_conc = f;
}

/*
 * Function name: set_spell_cast
 * Description:   Use an alternative routine to cast a spell
 * Arguments:     function f - The function to call to initiate casting
 */
public void
set_spell_cast(function f)
{ 
    gSpell_cast = f; 
}

/*
 * Function name: set_spell_effect
 * Description:   Designate the function to call when the spell is
 *                successfully cast to produce the spell's effect.
 * Arguments:     function f - the function to call
 */  
public void
set_spell_effect(function f) 
{
    gSpell_effect = f; 
}

/*
 * Function name: set_spell_ingredients
 * Description:   Set the ingredients needed for the spell.
 * Arguments:     mixed list - An array of ingredients needed for the
 *                             spell or a pointer to a function that
 *                             returns such an array.
 */
public varargs void
set_spell_ingredients(mixed list)
{
    gIngredients = list;
}

/*
 * Function name: set_spell_ingredients
 * Description:   Set the optional ingredients for the spell.
 * Arguments:     mixed list - An array of ingredients needed for the
 *                             spell or a pointer to a function that
 *                             returns such an array.
 &                function f - A function to call with the list of
 *                             optional ingredients found.
 */
public varargs void
set_spell_optional_ingredients(mixed list, function f)
{
    gIngredients_opt = list;
    gIngredients_opt_fun = f;
}

/*
 * Function name: set_spell_offensive
 * Description:   Designate the spell as being offensive (one initiating
 *                combat)
 * Arguments:     int offensive - true if the spell is offensive
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
 * Arguments:     int i - true if spell is stationary
 */
public void
set_spell_stationary(int i)
{
    gSpell_stationary = i;
}

/*
 * Function name: set_spell_time
 * Description:   Set the time it takes to prepare the spell.
 * Arguments:     int time - The time it should take in seconds
 */
public void
set_spell_time(int time)
{
    gSpell_time = time;
}

/*
 * Function name: set_spell_element
 * Description:   Set the element type and the minimum of skill needed.
 * Arguments:     int element - The element type, as found in /sys/ss_types.h
 *                int skill   - The value in skill needed for the spell.
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
 * Arguments:     form - The form type, as found in /sys/ss_types.h
 *                skill - The skill-value needed for the spell.
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
 * Arguments:     mana - The amount of mana
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
 * Arguments:     proc - The % value.
 */
public void
set_spell_mana_fail(int proc)
{
    gMana_fail = itof(proc) / 100.0; 
}

public void
set_spell_conc_message(mixed msg)
{
    gConc_msg = msg;
}

/*
 * Function name: set_spell_fail
 * Description:   Set the function to use when the spell fails.
 *                The function should return a string that contains
 *                the message to write.
 * Arguments:     func - The function to be used
 *                       string func()
 */
public void
set_spell_fail(mixed fail)
{
    gSpell_fail = fail;
}

/*
 * Function name: set_spell_resist
 * Description:   Set the function to use when to get the
 *                resistance value in %. The function should
 *                use query_magic_res() to search for the properties.
 * Arguments:     func - The function to be used
 *                       int func(object target)
 */
public void
set_spell_resist(mixed res)
{
    gSpell_resist = res; 
}

/*
 * Function name: set_spell_task
 * Description:   Set the difficulty of the spell as found in /sys/tasks.h
 * Arguments:     int task - The task difficulty
 */
public void
set_spell_task(int task) 
{ 
    gSpell_task = task; 
}

public void
set_spell_resist_task(int task)
{
   gSpell_resist_task = task;
}

public void
set_spell_resolve(function f)
{
    gSpell_resolve = f;
}

public void
set_spell_target_verify(function f)
{
    gTarget_verify = f;
}

public void
set_spell_no_reveal(int i)
{
    gSpell_no_reveal = i;
}

public void
set_spell_vocal(int i)
{
    gSpell_vocal = i;
}

public void
set_spell_visual(int i)
{
    gSpell_vocal = i;
}

public void
set_spell_peaceful(int i)
{
    gSpell_peaceful = i;
}

public void
set_spell_break(mixed br)
{
    gSpell_break = br;
}

public void
set_spell_abort(mixed abort)
{
    gSpell_abort = abort;
}

public int
query_spell_no_reveal()
{
    return gSpell_no_reveal;
}
   
public void
set_spell_name(string name)
{
    gSpell_name = name;
}

public string
query_spell_name()
{
    return gSpell_name;
}

public void
set_spell_object(mixed ob)
{
    gSpell_object = ob;
}

public mixed
query_spell_object()
{
    return gSpell_object;
}

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
        else
        {
            spell = clone_object(obj);
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
        spell->start();
    }

    if (pointerp(targets))
    {
        return obs;
    }

    return obs[0];
}
