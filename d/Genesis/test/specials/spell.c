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
#pragma strict_types

#include "defs.h"

inherit ABILITY_LIB;
inherit ABILITY_DIR+"spell_hooks";
inherit ABILITY_DIR+"resist";
inherit ABILITY_DIR+"components";
inherit ABILITY_DIR+"spell_targetting";

#include <comb_mag.h>
#include <tasks.h>
#include <ss_types.h>

#define LIVE_O_CASTING_ENV       "_live_o_casting_env"


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

public int query_spell()
{
    return 1;
}

public mapping query_saved_args()
{
    return saved_args;
}

public void
resolve_spell(object caster, mixed * targets, int *resist, int result);


public void set_spell_fail(mixed fail)
{
  set_ability_fail(fail);
}

public void set_spell_name(string name)
{
    set_ability_name(name);
}

public string query_spell_name()
{
    return query_ability_name();
}

public void set_spell_time(int time)
{
    set_ability_time(time);
}

public varargs int query_spell_time(string verb, mixed arg)
{
    float time=itof(query_ability_time())/2.0;
      
    time+=rnd()*time+rnd()*time;

    time+=0.5;
    
    if (time<1.0)
    {
        time=1.0;
    }
    return ftoi(time);
}

public void set_spell_offensive(int i)
{
    set_ability_offensive(i);
}

public void set_spell_task(int task)
{
    Spell_task=task;
}

public int get_spell_task()
{
    return Spell_task;
}


public int set_spell_no_reveal(int i)
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


public void set_spell_element(int element,int skill)
{
    Element_skill=element;
    Element_needed=skill;
}

public void set_spell_form(int form,int skill)
{
    Form_skill=form;
    Form_needed=skill;
}

public void set_spell_peaceful(int i)
{
    set_ability_peaceful(i);
}

public void set_spell_stationary(int i)
{
    set_ability_stationary(i);
}

public void set_spell_vocal(int i)
{
    set_ability_vocal(i);
}

public void set_spell_visual(int i)
{
    set_ability_visual(i);
}

public void set_spell_mana(int mana)
{
    Mana_needed=mana;
}

public int get_spell_mana()
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


public void set_spell_target(mixed target)
{
    set_ability_target(target);
}

public void set_spell_resist(mixed resist)
{
    Spell_resist=resist;
}

public void set_spell_resist_task(int task)
{
    Spell_resist_task=task;
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


static int check_valid_action(object caster,mixed * targets,string arg,
            int execute=0)
{
    mixed why;

    object room=environment(caster);

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


    int needed = Mana_needed;
    
    int reduce = ftoi(itof(Mana_needed) * Mana_fail);

    if (execute)
    {
        reduce = Mana_needed-reduce;
        needed = reduce;
    }
    
    /* Do we have enough mana to cast the spell? */
    if (!reduce_mana(caster, needed, 1))
    {
        hook_no_mana_fail(this_object());
        return 0;
    }

    reduce_mana(caster, reduce);

    return 1;
}


static nomask
void schedule_ability(object actor,mixed * targets,string arg)
{
    //Nothing to do here - spells are scheduled by the spell library
}

static mixed * check_required_items(object actor,mixed * targets,
                    string arg,int pretest)
{
    mixed * found=find_components(actor,Ingredients);
    
    if (sizeof(found)!=sizeof(Ingredients))
    {
        hook_no_ingredients_fail(Ingredients);
        return 0;
    }

    found += find_components(actor, Ingredients_opt) || ({});

    return found;
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
    int task = get_spell_task();
    int elem = caster->query_skill(Element_skill),
        form = caster->query_skill(Form_skill);

    task += (Element_needed > elem ? (Element_needed - elem) * 50 :0);
    task += (Form_needed > form ? (Form_needed - form) * 50 : 0);

    int result=max(0, caster->resolve_task(task, ({
        SKILL_WEIGHT, 70, Element_skill,
        SKILL_WEIGHT, 70, Form_skill,
        SKILL_WEIGHT, 20, TS_INT,
        SKILL_WEIGHT, 20, TS_WIS,
        SKILL_WEIGHT, 20, TS_DIS, })));
    return result;
}

static int
query_success(object actor,object target)
{
    int result=query_casting_success(actor);
    return result;
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

static 
void resolve_ability(object actor, mixed * items, 
            mixed * targets, int *resist, mixed *results)
{
    if (results[0]>0)
    {
        resolve_spell(actor,targets,resist,results[0]);
    }
    else
    {
        write(query_ability_fail());
    }

    if (sizeof(items))
    {
        items = filter(items, not @ &->use_component());
        hook_use_ingredients(items);
        items->remove_object();
    }

}


public void
ability_msg(object caster, mixed * targets, string arg)
{
    concentrate_msg(caster,targets,arg);
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
    return target_ability(actor,arg);
}

public nomask int query_spell_pretarget()
{
    return query_ability_pretarget();
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
config_spell(object caster, object * targets, string arg)
{
    return 0;
}
            

public nomask varargs int
config_ability(object caster,object * targets,string arg)
{
    return config_spell(caster,targets,arg);
}


public mixed use_spell_resist(object actor,mixed target,string name)
{
    if (Spell_resist)
    {
        if (pointerp(target) && sizeof(target))
        {
            return Spell_resist(actor,target[0], Element_needed,
                Spell_resist_task);
        }
        return Spell_resist(actor, target, Element_needed, 
            Spell_resist_task);
    }
    return 0;
}

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

}

public int check_ability_pending(object actor,object room)
{
    if (actor->query_prop(LIVE_O_CONCENTRATE) && !objectp(room))
    {
        hook_already_active(this_object());
        return 1;
    }
    if (objectp(room) && Ability_stationary && 
        actor->query_prop(LIVE_O_CASTING_ENV)!=room)
    {
        return 1;
    }
    return 0;
}

public int set_ability_pending(object actor,object room,int set)
{
    if (set)
    {
        actor->add_prop(LIVE_O_CONCENTRATE, this_object());
        actor->add_prop(LIVE_O_CASTING_ENV, room);
    }
    else
    {
        actor->remove_prop(LIVE_O_CONCENTRATE);
    }
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

        spell->set_spell_effect_name(query_ability_name());
        spell->set_spell_effect_element(Element_skill);
        spell->set_spell_effect_form(Form_skill);
        spell->set_spell_effect_power((caster->query_skill(Element_skill) +
            caster->query_skill(Form_skill) + Element_needed +
            Form_needed) / 4);
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


public int
concentrate_spell(object caster, object *targets, string arg)
{
    return start_ability(caster,targets,arg);

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


nomask public mixed
cast_spell(object caster, object *targets, string arg)
{
    object tp=this_player();
    set_this_player(caster);
    return execute_ability(caster,targets,arg);
    set_this_player(tp);
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
public int
start_spell_fail(string verb, string arg)
{
    object caster = this_player();
    mixed  * targets = ({});

    if (query_spell_pretarget())
    {
        targets = target_spell(caster, arg);
    
        if (!sizeof(targets))
        {
            return 1;
        }
    }
    
    mixed args = ({ targets, arg });

    saved_args[caster] = args;

    if (this_object()->do_spell_setup(caster, args[0], args[1]))
    {
        return 1;
    }

    return concentrate_spell(caster, args[0], args[1]);

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

static void restore_required_items(mixed * items)
{
    restore_components(items);
}

nomask public mixed
do_command(string verb, mixed arg)
{
    mixed args=saved_args[this_player()];
    
    if (!sizeof(args))
    {
        args=({ ({ }), arg });
    }
    m_delkey(saved_args,this_player());
    
    return cast_spell(this_player(), args[0], args[1]);
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

public int
exist_command(string verb)
{
    return (query_spell_name()==verb);
}

public int do_ability(string arg)
{
    
    this_player()->start_spell(query_ability_name(),arg,this_object());
    return 1;
}