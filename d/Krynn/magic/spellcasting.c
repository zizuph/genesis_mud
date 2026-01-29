/*
 * Spellcaster.c
 *
 * This file should be inherited by the object from which the spell is cast, 
 * ie a book or a staff.
 */

/*
 * The following has changed:
 *   add_spell now uses function types.
 *
 * The following functions has changed name:
 *   set_ingredients   -> set_spell_ingredients
 *   set_element       -> set_spell_element
 *   query_element     -> query_spell_element
 *   set_form          -> set_spell_form
 *   query_form        -> query_spell_form
 *   set_mana_spell    -> set_spell_mana
 *   set_duration      -> set_spell_duration
 *
 * The following is new:
 *   set_spell_success is removed
 *   resolve_spell is added (internal)
 *   set_spell_task(task, type)
 *   several hook_ functions are added.
 */
#pragma strict_types

#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <std.h>
#include <macros.h>
#include <formulas.h>
#include <comb_mag.h>
#include <cmdparse.h>
#include <composite.h>
#include <tasks.h>

#define TEMP_I_HEAP_COUNT  "_temp_i_heap_count"
#define SPELL_FUNCTION     0
#define SPELL_NAME         1

static
string *gIngredients,		/* The list of ingredients needed */
        gSpell_object,		/* The filename to the spell object */
        gArg;                   /* The argument given to cast the spell */

static
int  gSpell_time,	       	/* The time it takes to prepare the spell */
     gMana_needed,		/* Amount of mana needed to cast the spell */
     gMana_left,	       	/* Mana to reduce when the spell is cast */
     gSpell_attack,		/* True if it is an attack spell */
     gForm_skill,	       	/* The form skill */
     gElement_skill,		/* The element skill */
     gForm_needed,		/* The form skill needed */
     gElement_needed,		/* The element skill needed */
     gDamage_type,		/* The type of damage to inflict */
     gDuration,			/* How long the spell lasts in seconds */
     gSpell_task,	       	/* The difficulty of the spell */
     gResolve_type, 
     gSilent,                   /* Don't write a message for every object */
     gTmp,                      /* A variable used to count */
    *gResults;			/* The results of the spell */

static
object *gTargets,	       	/* A list of target(s) to cast the spell on */
       *gFound_ingrs,           /* A list of found ingredients */
        gCaster;	       	/* The one who casts the spell */

static
function gFind_target,		/* The function used to find the target(s) */
         gSpell_message,	/* The function used to give the messages */
         gSpell_fail,		/* Use this function when the spell fails */
         gSpell_resist,		/* Use this function to calc the resistance */
         gSpell_damage;         /* Use this function to calc the damage */

static
mapping gSpells = ([]);

public object *find_this_object(string arg);
public varargs void spell_message(object caster, object target, mixed result);
public mixed spell_success(object caster, object *targets);
public void spell_fail();
public int spell_damage(object caster, object target);
public int spell_resist(object target);

/*
 * Function name: default_config_spell
 * Description:	  Set the default values for the variables
 */
public void
default_config_spell()
{
    /* By default we will call find_this_object() */
    gFind_target = find_this_object;

    /* By default it will take 6 seconds to prepare the spell */
    gSpell_time = 6;

    /* By default we don't need any ingredients */
    gIngredients = 0;

    /* By default it is a non-attack spell */
    gSpell_attack = 0;

    /* By default we will need the FIRE element with 40 in skill */
    gElement_skill = SS_ELEMENT_FIRE;
    gElement_needed = 40;

    /* By default it will be a TRANSMUTATION form with 40 in skill */
    gForm_skill = SS_FORM_TRANSMUTATION;
    gForm_needed = 40;

    /* By default it will take 1000 mana points to cast the spell */
    gMana_needed = 0;

    /* By default the damage type is MAGIC_DT */
    gDamage_type = MAGIC_DT;

    /* By default no spell object is needed */
    gSpell_object = 0;

    /* By default call the internal spell_message */
    gSpell_message = spell_message;

    gSpell_task = TASK_ROUTINE;
    gResolve_type = 1;

    /* By default call the internal spell_fail */
    gSpell_fail = spell_fail;

    /* By default call the internal spell_damage */
    gSpell_damage = spell_damage;

    /* By default call the internal spell_resist */
    gSpell_resist = spell_resist;
}

/************************************************
 * Command driver replacement
 ************************************************/
/* 
 * Function name: do_command
 * Description:   Perform the given command, if present.
 * Returns:       1/0 depending on success.
 */
nomask public int
do_command(string verb, string arg)
{
    function f;

    f = gSpells[verb][SPELL_FUNCTION];

    return f(arg);
}

/* 
 * Function name: exist_command
 * Description  : Check if a command exists.
 * Returns      : 1/0 depending on success.
 */
nomask public int
exist_command(string verb)
{
    /* Actually we return an integer value, but that isn't a problem.
     * The calling function checks for true/false and it would only
     * take time to parse the outcome.
     */
    return ((member_array(verb, m_indexes(gSpells)) < 0) ? 0 : 1);
}

/*
 * Function name: add_spell
 * Description:   Add the spell to the list of active spells.
 * Arguments:     spell - The activating verb string
 *                function - The function to call
 *                name - The name of the spell (to be displayed in
 *                       the player spell list).
 */
nomask varargs void
add_spell(string spell, function func, string name)
{
    /* The spell was already added once */
    if (member_array(spell, m_indexes(gSpells)) >= 0)
        return;

    SECURITY->add_spell(spell, sprintf("%O", func), this_object(), name);


    gSpells += ([ spell : ({ func, name }) ]);
}

/*
 * Function name: remove_spell
 * Description:   Remove the spell with the given verb string.
 * Arguments:     verb - The verb of the spell to remove.
 * Returns:	         True if the remove was successful, otherwise false.
 */
nomask public int
remove_spell(string verb)
{
    int index;

    if (member_array(verb, m_indexes(gSpells)) < 0)
        return 0;

    gSpells = m_delete(gSpells, verb);

    return 1;
}

/*
 * Function name: list_spells
 * Description:	  This function is called to list the spells from
 *		  the player soul when the command "spells" is used.
 */
public void
list_spells()
{
    int i;
    string *verbs = m_indexes(gSpells);

    i = sizeof(verbs);
    while (i--)
        write(sprintf("%s %31s\n", verbs[i], gSpells[verbs[i]][SPELL_NAME]));
}

/*
 * Function name: query_spell_map
 * Description:   Return all the spells in the form:
 *                   ([ (string)verb : 
 *                        ({ (function)function, (string)name }), .. ])
 * Returns:       A mapping.
 */
public mapping
query_spell_map()
{
    return gSpells + ([]);
}

/*
 * Default, non-documented functions
 */
public varargs void 
spell_message(object caster, object target, mixed result)
{
}

public mixed
spell_success(object caster, object *targets)
{
}
public int
spell_damage(object attacker, object target)
{
    return 0;
}

public int
spell_resist(object target)
{
    return 0;
}

/*
 * Function name: spell_fail
 * Description:	  The spell failed.
 * Returns:	  A string that should be written or an integer.
 */
public mixed
spell_fail() { return 0; }

/*
 * Function name: set_caster
 * Description:	  Set the caster of the spell
 * Arguments:	  who - The caster
 */
public void
set_caster(object who) { gCaster = who; }

/*
 * Function name: query_caster
 * Description:	  Return the caster of the spell
 */
public object
query_caster() { return gCaster; }

/*
 * Function name: set_spell_ingredients
 * Description:	  Set the ingredients needed for the spell.
 * Arguments:	  list - A ingredient or a list of ingredients needed for
 *		         the spell.
 */
public void
set_spell_ingredients(string *list)
{
    gIngredients = (stringp(list) ? ({ list }) : list);
}

/*
 * Function name: set_spell_attack
 * Description:	  Make the spell an attack spell.
 */
public void
set_spell_attack() { gSpell_attack = 1; }

/*
 * Function name: set_damage_type
 * Description:	  Set the damage type this spell is of. Most spells would have
 *		  type MAGIC_DT, but a spell like magic missiles could be of
 *		  W_IMPALE type.
 * Arguments:	  type - The damage type, as found in /sys/wa_types.h
 */
public void
set_damage_type(int type) { gDamage_type = type; }

/*
 * Function name: set_spell_time
 * Description:	  Set the time it takes to prepare the spell. The real time
 *		  will be (time + 2 + LIVE_I_ATTACK_DELAY).
 * Arguments:	  time - The time it should take
 */
public void
set_spell_time(int time) { gSpell_time = time; }

/*
 * Function name: query_spell_time
 * Description:   It is called from cmdhooks.c, and should return the time
 *		  in seconds it takes to prepare the spell. The actual time
 *		  will be (time + 2 + LIVE_I_ATTACK_DELAY).
 * Arguments:	  verb - The verb that initiated this spell.
 *		  arg  - The arguments to the verb.
 * Returns:	  The time in seconds.
 */
public int
query_spell_time(string verb, string arg)
{
    return gSpell_time;
}

/*
 * Function name: set_spell_element
 * Description:	  Set the element type and the minimum of skill needed.
 * Arguments:	  type - The element type, as found in /sys/ss_types.h
 *		         skill - The value in skill needed for the spell.
 */
public void
set_spell_element(int type, int skill)
{
    gElement_skill = type;
    gElement_needed = skill;
}

/*
 * Function name: query_spell_element
 * Description:   Return the element skill.
 */
public int
query_spell_element() { return gElement_skill; }

/*
 * Function name: set_spell_form
 * Description:	  Set the form type and the minimum of skill needed.
 * Arguments:	  type - The form type, as found in /sys/ss_types.h
 *		  skill - The skill-value needed for the spell.
 */
public void
set_spell_form(int type, int skill)
{
    gForm_skill = type;
    gForm_needed = skill;
}

/*
 * Function name: query_spell_form
 * Description:   Return the form skill.
 */
public int
query_spell_form() { return gForm_skill; }

/*
 * Function name: set_spell_mana
 * Description:	  Set the amount of mana needed to cast the spell.
 * Arguments:	  mana - The amount of mana
 */
public void
set_spell_mana(int mana) { gMana_needed = mana; }

/*
 * Function name: query_spell_targets
 * Description:	  Returns all the found targets
 */
public object *
query_spell_targets() { return gTargets; }

/*
 * Function name: set_spell_duration
 * Description:	  Set the time the spell will last in seconds
 * Arguments:	  time - The time the spell should last
 */
public void
set_spell_duration(int time) { gDuration = time; }

/*
 * Function name: set_find_target
 * Description:	  Set the function to use when we are trying to locate
 *		  the target(s)
 * Arguments:	  func - The function to be used:
 *		         object *func(string str)
 */
public void
set_find_target(function func) { gFind_target = func; }

/*
 * Function name: set_spell_message
 * Description:	  Set the function to use when we want to give the messages.
 * Arguments:	  func - The function to be used.
 *
 *		       NON-attack spell:
 *		       void func(object caster, object *targets)
 *
 *		       If it is an attack spell:
 *		       void func(object caster, object target, mixed hitresult)
 */
public void
set_spell_message(function func) { gSpell_message = func; }

/*
 * Function name: set_spell_fail
 * Description:	  Set the function to use when the spell fails.
 *	          The function should return a string that contains
 *                the message to write.
 * Arguments:	  func - The function to be used
 *		         string *func()
 */
public void
set_spell_fail(function func) { gSpell_fail = func; }

/*
 * Function name: set_spell_resist
 * Description:	  Set the function to use when the to get the
 *		  resistance value in %. The function should
 *		  use query_magic_res() to search for the properties.
 * Arguments:	  func - The function to be used
 *		         int *func(object target)
 */
public void
set_spell_resist(function func) { gSpell_resist = func; }

/*
 * Function name: set_spell_damage
 * Description:	  Set the function to use when to calculate the damage.
 *                The function should return an integer that could
 *		  be used as 'wcpen'. To calculate the value you
 *		  should use F_PENMOD, as found in /sys/formulas.h, and
 *		  the result value from the success function.
 * Arguments:	  func - The function to be used
 *		         int *func(object caster, object target, int result)
 */
public void
set_spell_damage(function func) { gSpell_damage = func; }

/*
 * Function name: set_spell_object
 * Description:	  Set the spell object that should be loaded and moved to
 *		  the target(s)
 * Arguments:	  name - The filename with complete path
 */
public void
set_spell_object(string name) { gSpell_object = name; }

/*
 * Function name: set_spell_task
 * Description:	  Set the difficulty of the spell as found in /sys/tasks.h
 * Arguments:	  task - The task
 *                type - The type used when resolving the success,
 *                       1 means make one check/target, 0 means
 *                       make one check only.
 */
public varargs void
set_spell_task(int task, int type = 1) 
{ 
    gSpell_task = task; 
    gResolve_type = type;
}

/*
 * Function name: find_this_object
 * Description:	  By default this_object() will be the target.
 */
public object *
find_this_object(string arg)
{
    return ({ this_object() });
}

/*
 * Function name: hook_no_magic_fail
 * Description:   Return the message that should be printed when noone
 *                is supplied with ROOM_M_NO_MAGIC.
 * Arguments:     obj - The room object.
 * Returns:       The message to print.
 */
public string
hook_no_magic_fail(object obj)
{
    return "You can't draw upon the magic, as if resisted by the " +
	   "very air around you.\n";
}

/*
 * Function name: hook_no_magic_attack_fail
 * Description:   Return the message that should be printed when noone
 *                is supplied with ROOM_M_NO_MAGIC_ATTACK.
 * Arguments:     obj - The room object.
 * Returns:       The message to print.
 */
public string
hook_no_magic_attack_fail(object obj)
{
    return "You can't draw upon the magic, as if resisted by the " +
	   "very air around you.\n";
}

/*
 * Function name: hook_no_skills_fail
 * Description:   Return the message that should be printed when the caster
 *                doesn't have good enough skills
 * Returns:       The message to print.
 */
public string
hook_no_skills_fail()
{
    return "Sorry, but you are not skilled enough for this spell!\n";
}

/*
 * Function name: hook_no_mana_fail
 * Description:   Return the message that should be printed when the caster
 *                doesn't have enough mana.
 * Returns:       The message to print.
 */
public string
hook_no_mana_fail()
{
    return"You don't have mana enough to properly cast the spell.\n";
}

/*
 * Function name: hook_no_ingredients_fail
 * Description:   Return the message that should be printed when the caster
 *                doesn't have the right ingredients
 * Returns:       The message to print.
 */
public string
hook_no_ingredients_fail()
{
    return "Sorry, but you don't have the right ingredients for the spell!\n";
}

/*
 * Function name: query_opposite_elem
 * Description:   Return the opposite element to a given element.
 * Arguments:     i - The element.
 * Returns:       The opposite element, false if not found.
 */
public int
query_opposite_elem(int i)
{
    switch(i)
    {
        case SS_ELEMENT_EARTH:
            return SS_ELEMENT_AIR;
	case SS_ELEMENT_AIR:
	    return SS_ELEMENT_EARTH;
	case SS_ELEMENT_FIRE:
	    return SS_ELEMENT_WATER;
        case SS_ELEMENT_WATER:
	    return SS_ELEMENT_FIRE;
        case SS_ELEMENT_LIFE:
	    return SS_ELEMENT_DEATH;
        case SS_ELEMENT_DEATH:
	    return SS_ELEMENT_LIFE;
	default:
	    return 0;
    }
}

/*
 * Function name: resolve_spell
 * Description:   This is a replacement for resolve_task, shorter and
 *                quicker, almost everything is hard coded.
 * Returns:       The result as an interger or an array of integers (one
 *                for each target).
 */
static mixed
resolve_spell()
{
    int i, caster, rand, target, *result = ({});

    rand = random(500) - random(500) + 500;

    caster = MIN(gCaster->query_skill(SS_SPELLCRAFT),
		 gCaster->query_skill(gElement_skill)) +
	     MIN(gCaster->query_skill(SS_SPELLCRAFT),
		 gCaster->query_skill(gForm_skill));

    if (!gResolve_type) 
        return (100 * (rand + 2 * caster - gSpell_task) / gSpell_task);
    else
        for (i = 0; i < sizeof(gTargets); i++)
	{
	    target = (gTargets[i]->query_skill(SS_FORM_ABJURATION) +
	              gTargets[i]->query_skill(query_opposite_elem(
				   gElement_skill))) / 2;

	    result += ({ (100 * (rand + 2 * caster - target - gSpell_task) /
			  gSpell_task) });
	}
    return result;
}

/*
 * Function name: check_skills
 * Description:	  Check the skills on the caster and see if they
 *		  are high enough.
 * Returns:	  True if it is ok, false otherwise.
 */
public int
check_skills()
{
    int skill;

    if (gForm_needed > gCaster->query_skill(gForm_skill))
	return 0;
    if (gElement_needed > gCaster->query_skill(gElement_skill))
	return 0;
    return 1;
}


static nomask int 
virtual_first(object ob)
{
    if (gTmp < 1)
        return 0;
    else 
        if (ob->query_prop(HEAP_I_IS))
        {
	    int tmp = (gTmp > ob->num_heap() ? ob->num_heap() : gTmp);
	    ob->add_prop(TEMP_I_HEAP_COUNT, tmp);
	    gTmp -= tmp;
	}
    else
        gTmp -= 1;

    return 1;
}


static mixed *
visible_access(mixed *arr)
{
    int num;
    object *a;
    
    if (!pointerp(arr))
        return 0;                   /* It must be an array */
    num = arr[0];                   /* Numeric designation */

    a = COMPOSITE_SORT(arr, "short");

    a = filter(a, objectp);

    a = filter(a, &CMDPARSE_STD->can_see(,gCaster));

    if (!sizeof(a))
        return ({ });               /* Not accessible */
    if (num == 0)
        return a;                   /* Select all items */
    else if (num < 0)               
        /* Select a certain item, eg. first or third */
        return CMDPARSE_STD->order_num(a, -num);
    else
    {
        /* Select a number of items, eg. one or three */
        gTmp = num;
        a = filter(a, virtual_first);
        /* Get the first so many we want */
        return a;                   /* If fewer, return so many we have */
    }
}

/*
 * Function name: check_ingredients
 * Description:	  Search for an ingredient or a number of ingredients in
 * 		  the caster.
 * Returns:	  True if everything was found, false otherwise.
 */
public int
check_ingredients()
{
    int i;
    object *items; 

    gFound_ingrs = ({ });

    /* Use filter here. */
    if ((i = sizeof(gIngredients)))
        while (i--)
        {
	    if (parse_command(gIngredients[i], all_inventory(gCaster), 
			      "%i", items))
	    {
		items = visible_access(items);

	        gFound_ingrs += items;

		if (gTmp > 0)
		    return 0;
	    }
	    else
	        return 0;
	}
    return 1;
}

/*
 * Function name: prepare_ingrs_heap
 * Description:   Prepare and move a heap object. 
 * Argumnets:     ob - The heap object.
 * Returns:       True.
 */
static int
prepare_ingrs_heap(object ob)
{
    object env;

    if (ob->query_prop(HEAP_I_IS))
    {
	ob->split_heap(ob->query_prop(TEMP_I_HEAP_COUNT));
	ob->remove_prop(TEMP_I_HEAP_COUNT);
	
	env = environment(ob);
	ob->move(this_object(), 1);
        ob->leave_env(env, this_object());
    }
    return 1;
}

/*
 * Function name: start_spell_fail
 * Description:	  It is called from cmdhooks.c and it sets up the right
 *		  spell and checks so that it is ok to cast.
 * Arguments:     verb - The verb that initiated this spell.
 *		  arg  - The arguments to the verb.
 * Returns:	  True if the spell failed, false otherwise
 */
nomask public int
start_spell_fail(string verb, string arg)
{
    object room;
    string no_magic_fail;
    int reduce;

    default_config_spell();

    set_caster(previous_object());

    if (call_other(this_object(), "create_spell_" + verb, arg))
      return 1;

    room = environment(gCaster);

    no_magic_fail = RNMAGIC(room);
    if (no_magic_fail)
    {
	if (!stringp(no_magic_fail))
	    write(hook_no_magic_fail(room));
	else
	    write(no_magic_fail);
        return 1;
    }

    no_magic_fail = RNMATTACK(room);
    if (gSpell_attack && no_magic_fail)
    {
	if (!stringp(no_magic_fail))
	    write(hook_no_magic_attack_fail(room));
	else
	    write(no_magic_fail);
        return 1;
    }

    /* Are we skilled enough to cast this spell? */
    if (!check_skills())
    {
        write(hook_no_skills_fail());
	return 1;
    }

    /* Do we have the proper ingredients? */
    if(!check_ingredients())
    {
        gFound_ingrs->remove_prop(TEMP_I_HEAP_COUNT);
	write(hook_no_ingredients_fail());
        return 1;
    }

    /* Do we have enough mana to cast the spell? */
    if (gCaster->query_mana() < gMana_needed)
    {
	write(hook_no_mana_fail());
        return 1;
    }

    /* Look for the targets */
    gTargets = gFind_target(arg);

    if (!gTargets || !sizeof(gTargets))
        return 1;

    gSilent = ((sizeof(gTargets) > 1) ? 1 : 0);

    reduce = gMana_needed/3;

    /* We need to reduce this later, when the spell is cast */
    gMana_left = gMana_needed - reduce;

    gCaster->add_mana(-reduce);

    /* The spell is ready to be cast. */

    gArg = arg;

    gCaster->add_prop(LIVE_I_CONCENTRATE, 1);

    return 0;
}

/*
 * Function name: query_spell_mess
 * Description:	  It is called from cmdhooks.c, and it us used to change the
 *		  standard message given when a spell is being prepared. You
 *		  should handle all the printouts by yourself.
 * Arguments:	  verb - The verb that initiated this spell.
 *		  arg  - The arguments to the verb.
 * Returns:	  True if you are handeling the printouts yourself, 
 *                false otherwise.
 */
public int
query_spell_mess(string verb, string arg)
{
    /* We want the standard messages */
    return 0;
}

/*
 * Function name: filter_kill_access
 * Description:	  This function is called from the filter command in
 *		  cast_spell, to find all objects that the caster is
 *		  able to cast a spell on.
 * Arguments:	  ob - The victim
 * Returns:	  True if ok, otherwise false
 */
public int
filter_kill_access(object ob)
{
    if (!living(ob) || ob->query_ghost() || ob == gCaster)
        return 0;

    if (!present(ob, environment(gCaster)))
        return 0;

    if (NPMATTACK(ob))
    {
        if (!gSilent)
	    gCaster->catch_msg("You can't cast the spell on " + QTNAME(ob) + 
			       ".\n");
        return 0;
    }

    if (!F_DARE_ATTACK(gCaster, ob) && (gCaster->query_attack() != ob))
    {
        if (!gSilent)
	    gCaster->catch_msg("You do not dare to cast the spell on " + 
			       QTNAME(ob) + ".\n");
        return 0;
    }

    return 1;
}

/*
 * Function name: cast_spell
 * Description:	  This function handles the actual casting of the spell.
 */
nomask public int
cast_spell()
{
    mixed result;
    int i, t, delay;
    object spell;

    if (gSpell_attack)
    {
        /* Get all targets that we can hit with our spell */
        gTargets = filter(gTargets, &filter_kill_access());

        if (!sizeof(gTargets))
        {
            gCaster->catch_msg("Nobody here to cast the spell on!\n");
            gCaster->remove_prop(LIVE_I_CONCENTRATE);
            return 0;
        }

        /* This must be called */
        gCaster->add_prop(LIVE_O_SPELL_ATTACK, this_object());

        /* Do we need to attack the enemy? */
	if (gCaster->query_attack() != gTargets[0])
	    gCaster->attack_object(gTargets[0]);
        return 1;
    }
 
    gCaster->remove_prop(LIVE_I_CONCENTRATE);

    /* Look for the targets, again (This is needed) */
    gTargets = gFind_target(gArg);
    if (!sizeof(gTargets))
	return 0;

    /* Check if the spell is successfully cast */
    if (!(result = resolve_spell()))
        return gSpell_fail();

    gResults = (intp(result) ? ({ result }) : result);

    gSpell_message(gCaster, gTargets);

    /* Put this in a seperat function? */
    if (gSpell_object)
    {
        i = sizeof(gTargets);
        t = sizeof(gResults);

	seteuid(getuid());

        while(i--)
        {
            spell = clone_object(gSpell_object);
	    spell->set_duration(gDuration);
            spell->set_caster(gCaster);
            spell->set_element(gElement_skill);
            spell->set_form(gForm_skill);

	    ((t > 1) ? spell->set_power(gResults[i]) : 
	     spell->set_power(gResults[0]));

            spell->move_spell(gCaster, gTargets[i], this_object());
        }
    }

    if (sizeof(gFound_ingrs))
    {
        gFound_ingrs = filter(gFound_ingrs, prepare_ingrs_heap);
        write("You sacrificed " + COMPOSITE_DEAD(gFound_ingrs) + ".\n");
	filter(gFound_ingrs, &->remove_object());
    }

    gCaster->add_mana(-gMana_left);

    return 1;
}

/*
 * Function name: spell_attack
 * Description:	  This function is called from within the combat system
 * Arguments:	  attacker - The one who cast the spell
 *		  target   - The one who got hit by the spell
 */	
public void
spell_attack(object attacker, object target)
{
    int *result, hurt, i;
    mixed *hitresult;

    gCaster->remove_prop(LIVE_I_CONCENTRATE);

    i = sizeof(gTargets);
 
    /* Check if the spell is successfully cast */
    if (!(result = resolve_spell()))
	return gSpell_fail();
 
    if (i)
    {
        gCaster->add_mana(-gMana_left);

        if (sizeof(gFound_ingrs))
        {
            gFound_ingrs = filter(gFound_ingrs, prepare_ingrs_heap);
            write("You sacrificed " + COMPOSITE_DEAD(gFound_ingrs) + ".\n");
            filter(gFound_ingrs, &->remove_object());
        }
    }

    gResults = (intp(result) ? ({ result }) : result);
 
    while (i--)
        if (present(gTargets[i], environment(attacker)))
        {
            hurt = gSpell_damage(attacker, gTargets[i], gResults[i]);
            hurt -= hurt * gSpell_resist(gTargets[i]) / 100;

            hitresult = gTargets[i]->hit_me(hurt, gDamage_type, attacker,  -1);

            gSpell_message(attacker, gTargets[i], hitresult);
            if (gTargets[i]->query_hp() == 0)
                gTargets[i]->do_die(attacker);

            gTargets[i]->notify_got_hit_by_spell(attacker);
        }
}

/*
 * Function name: enter_env
 * Description:   Add the object to the list of spell objects.
 */
public varargs void
enter_env(object dest, object old)
{
    if (!dest || !living(dest))
        return;

    dest->add_spellobj(this_object());
}

/*
 * Function name: leave_env
 * Description:   Remove the object from the list of spell objects
 */
public varargs void
leave_env(object old, object dest)
{
    if (!old || !living(old))
        return;

    old->remove_spellobj(this_object());
}

/*
-> When casting an attack spell to initiate a combat or when changing
   enemy will give the spell longer preparation time, the time will
   be added with: 5 - LIVE_I_QUICKNESS seconds.

-> The following has been changed:
     stdproperties.h  - added LIVE_I_CONCENTRATE
                      - added LIVE_S_BREAK_CONCENTRATE
     /secure/master.c - In modify_commands added check for
                        LIVE_I_CONCENTRATE
     cbase.c          - In heart_beat added check for
                        LIVE_I_CONCENTRATE
     cmdhooks.c       - In cmdhooks_break_spell, added remove_prop on
                        LIVE_I_CONCENTRATE
		      - In my_command, at the end, removed
		        add_attack_delay

*/





