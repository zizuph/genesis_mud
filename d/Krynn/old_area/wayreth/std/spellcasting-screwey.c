/*
 * Spellcaster.c
 *
 * This file should be inherited by the object from which the spell is cast, 
 * ie a book or a staff.
 *
 * CHANGELOG -
 *
 * : Karath 970826
 *		Modified check_ingredients to do a search through the
 *		inventory of the player for open containers with the
 *		property CONT_I_HOLDS_COMPONENTS set. Also, it does
 *		a search for herbs and does a query_herb_name.
 *              LIMITATIONS: You may not have a component such as
 *		"two suranies" as herb names aren't available in
 *		containers and thus cannot be checked via parse_command.
 *		I have not verified this, but i strongly suspect that
 *		set_ingredient( ({ "copper coin", "copper coin" }) );
 *		would cause a single copper coin to be matched twice
 *		and the function would not check to see if a single
 *		component has been tagged more than once in the checking
 *		the component list. Therefore, at the moment, you cannot
 *		have spells that use more than one of the same herb.
 *		Spells that use multiples of non-herb items must do it
 *		in a descriptive manner that is passed to parse_command.
 *		This latest version of spellcasting.c is done so with a
 *		bit of unease on my part as it's the first changes I've
 *		made to a module in it that I cannot say I completely
 *		understand, therefore increasing the liklihood of bugs.
 *		But I can't hold everything back on this point, so:
 *		"Ready, Fire, Aim".
 *
 * : Karath 970623
 *		Put in checks for environment of the caster being the
 *		same at beginning and end of the spell. Made a chance
 *		of failure for the spell based on random(task/4) >
 *		random(spellcraft) + random(dis). (task/3 if they
 *		have moved more than one room away).
 *		Also added set_spell_stationary() if a spell should
 *		not have any chance of success if they move.
 *
 * : Karath 970603
 *		Moved removal of the concentrate prop to be just before
 *		removing the ingredients (or in the two if-statements
 *		before that)
 *
 * : Karath 970521
 *		Added a check for environment change from start of
 *		preparation to finish and a hook for that specific
 *		failure.
 *
 * : Karath 970511
 *		Added a define for TASK_EASY, defined as 
 *			TASK_SIMPLE + 150
 *		which is currently halfway between TASK_SIMPLE
 *		and TASK_ROUTINE. This should be a better choice
 *		for combat oriented spells that are widely available
 *		do different branches of the guildmembers who might
 *		have different skill concentrations.
 *
 * : Karath 970430
 *             Added set_spell_offensive() for spells that should
 *             try to initiate combat, and check for dare attack
 *             but aren't direct damage spells. This is mutually
 *             exclusive with set_spell_attack()
 *
 * TODO
 *	Check for a LIVE_O_SPELL_ATTACK before allowing another
 *	spell to be started.
 *
 *      Verify that in all cases of failure, that it removes the
 *	concentrating prop.
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
#define TASK_EASY TASK_SIMPLE + 150
#define LIVE_O_CASTING_ENV "_live_o_casting_env"

static
mixed   gArg;                   /* The argument given to cast the spell */

static
string *gIngredients,		/* The list of ingredients needed */
        gSpell_object;		/* The filename to the spell object */


static
int  gSpell_time,	       	/* The time it takes to prepare the spell */
     gMana_needed,		/* Amount of mana needed to cast the spell */
     gMana_left,	       	/* Mana to reduce when the spell is cast */
     gSpell_attack,		/* True if it is an attack spell */
     gSpell_offensive,		/* True if it is a combat initiating spell*/
                                /* ... mutually exclusive with gSpell_attack*/
     gSpell_stationary,		/* If the spell requires standing still */
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
float gMana_fail;               /* The % of mana to reduce when the spell
                                   fails */

static
object *gTargets,	       	/* A list of target(s) to cast the spell on */
       *gFound_ingrs,           /* A list of found ingredients */
        gCaster;	       	/* The one who casts the spell */

static
function gFind_target,		/* The function used to find the target(s) */
         gSpell_message,	/* The function used to give the messages */
         gSpell_fail,		/* Use this function when the spell fails */
         gSpell_resist,		/* Use this function to calc the resistance */
         gSpell_death,          /* Tell the spell that the target should die */
         gSpell_damage;         /* Use this function to calc the damage */

static
mapping gSpells = ([]);

/*
 * Prototypes
 */
public object *find_this_object(string arg);
public varargs void spell_message(object caster, object target, mixed result);
public void spell_fail();
public int spell_damage(object caster, object target);
public int spell_resist(object target);
public void spell_death(object target);

/*
 * Function name: default_config_spell
 * Description:	  Set the default values for the variables
 */
public void
default_config_spell()
{
    /* By default we will call find_this_object() */
    gFind_target = find_this_object;

    /* By default it will take 6 seconds (really 8) to prepare the spell */
    gSpell_time = 6;

    /* By default we don't need any ingredients */
    gIngredients = 0;

    /* By default it is a non-attack spell */
    gSpell_attack = 0;

    /* By default it is a non-offensive spell */
    gSpell_offensive = 0;

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

    gMana_fail = 1.0 / 3.0;
    
    /* By default call the internal spell_fail */
    gSpell_fail = spell_fail;

    /* By default call the internal spell_damage */
    gSpell_damage = spell_damage;

    /* By default call the internal spell_resist */
    gSpell_resist = spell_resist;

    /* By default the target dies in the normal way */
    gSpell_death = spell_death;
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
    return ((member_array(verb, m_indexes(gSpells)) < 0) ? 0 : 1);
}

/*
 * Function name: add_spell
 * Description:   Add the spell to the list of active spells.
 * Arguments:     verb - The activating verb string
 *                function - The function to call
 *                name - The name of the spell (to be displayed in
 *                       the player spell list).
 */
nomask varargs void
add_spell(string verb, function func, string name)
{
    /* The spell was already added once */
    if (member_array(verb, m_indexes(gSpells)) >= 0)
        return;

    SECURITY->add_spell(verb, sprintf("%O", func), this_object(), name);

    gSpells += ([ verb : ({ func, name }) ]);
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
    return secure_var(gSpells);
}

/*
 * Default, non-documented functions
 */
public varargs void 
spell_message(object caster, object target, mixed result)
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

public void
spell_death(object target)
{
    target->do_die(gCaster);
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
 * Function name: set_spell_arg
 * Description:   Set the argument given after the verb
 */
public void
set_spell_verb(mixed arg) { gArg = arg; }

/*
 * Function name: query_spell_arg
 * Description:   Returns the argument
 */
public mixed
query_spell_arg() { return gArg; }

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
 * Function name: set_spell_death
 * Description:   Use this function to tell the spell that the target
 *                should die. The spell has to call do_die in the target
 *                to really kill.
 * Arguments:     func - The function to call
 *                       void func(object target)
 */
public void
set_spell_death(function func) { gSpell_death = func; }

/*
 * Function name: set_spell_attack
 * Description:	  Make the spell an attack spell.
 */
public void
set_spell_attack() { gSpell_attack = 1; }

/*
 * Function name: set_spell_offensive
 * Description: Make the spell a non-direct-damage combat initiating spell.
 */
public void
set_spell_offensive() { gSpell_offensive = 1; }

/*
 * Function name: set_spell_stationary
 * Description:   Make the spell require standing still while concentrating
 */
public void
set_spell_stationary() { gSpell_stationary = 1; }

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
 * Arguments:	  element - The element type, as found in /sys/ss_types.h
 *		  skill - The value in skill needed for the spell.
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
query_spell_element() { return gElement_skill; }

/*
 * Function name: set_spell_form
 * Description:	  Set the form type and the minimum of skill needed.
 * Arguments:	  form - The form type, as found in /sys/ss_types.h
 *		  skill - The skill-value needed for the spell.
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
query_spell_form() { return gForm_skill; }

/*
 * Function name: set_spell_mana
 * Description:	  Set the amount of mana needed to cast the spell.
 * Arguments:	  mana - The amount of mana
 */
public void
set_spell_mana(int mana) { gMana_needed = mana; }

/*
 * Function name: set_spell_mana_fail
 * Description:   Set the % value of how much mana that should be
 *                reduced when the spell fails.
 * Arguments:     proc - The % value.
 */
public void
set_spell_mana_fail(int proc) { gMana_fail = itof(proc / 100); }

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
 *		         string func()
 */
public void
set_spell_fail(function func) { gSpell_fail = func; }

/*
 * Function name: set_spell_resist
 * Description:	  Set the function to use when to get the
 *		  resistance value in %. The function should
 *		  use query_magic_res() to search for the properties.
 * Arguments:	  func - The function to be used
 *		         int func(object target)
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
 *		         int func(object caster, object target, int result)
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
 * Function name: query_spell_result
 * Description:   Return the results of the spell.
 * Returns:       An integer array.
 */
public int *
query_spell_result()
{
    return secure_var(gResults);
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
 * Function name: notify_concentrate_break
 * Description:   This function gets called as soon as someone
 *                does anything while concentrating.
 *                NOTE: If this function is redefined, make sure
 *                      that you do: who->cmdhooks_break_spell(<msg>);
 *                      to break the concentration or else it wont be
 *                      broken.
 * Arguments:     who - The one that was concentrating
 */
public void
notify_concentrate_break(object who)
{
    who->cmdhooks_break_spell(who->query_prop(LIVE_S_BREAK_CONCENTRATE));
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
 * Function name: hook_dont_dare_attack_fail
 * Description:   Return the messages that should be printed to the caster
 *                when he/she don't dare to cast the spell.
 * Arguments:     target - The victim that is too strong.
 * Returns:       The message to print.
 */
public string
hook_dont_dare_attack_fail(object target)
{
    return "You don't dare to cast the spell on " + QTNAME(target) + ".\n"; 
}

/*
 * Function name: hook_targets_gone
 * Description:   Return the string that will be printed to the caster when
 *                the targets has disappeared during the prepartion of the
 *                spell.
 * Returns:       The message to print
 */
public string
hook_targets_gone()
{
    return "Nobody here to cast the spell on!\n";
}

/*
 * Function name: hook_changed_env
 * Description:   Return the string that will be printed to the caster when
 *                he or she has moved rooms while preparing the spell.
 * Returns:       The message to print.
 */
public string
hook_changed_env()
{
	return "You have lost concentration while moving!\n";
}

/*
 * Function name: hook_use_ingredients
 * Description:   This function should return the message that will be printed
 *                to the caster when he/she has used some ingredients.
 * Arguments:     ingrs - The ingredients that will be used.
 * Returns:       The message to print.
 */
public string
hook_use_ingredients(object *ingrs)
{
    int i;
    for (i = 0; i < sizeof(ingrs); i++)
      {
    	find_player("karath")->catch_msg("using " +file_name(ingrs[i])+"\n");
      }
    return "You sacrificed " + COMPOSITE_DEAD(ingrs) + ".\n";
}

/*
 * Function name: hook_living_no_magic_attack_fail
 * Description:   This function should return the string that will be printed
 *                to the caster, when trying to attack a living that has the
 *                property OBJ_M_NO_MAGIC_ATTACK set.
 * Arguments:     target - The intended targer
 * Returns:       The message to print
 */
public string
hook_living_no_magic_attack_fail(object target)
{
   return "You can't cast a spell on " + QTNAME(target) + ".\n";
}

/*
 * Function name: resolve_spell
 * Description:   This is a replacement for resolve_task, shorter and
 *                quicker, almost everything is hard coded.
 * Returns:       The result as an interger or an array of integers (one
 *                for each target), if the result is 0, then the spell
 *                failed on that target.
 */
static mixed
resolve_spell()
{
    int i, caster, rand, *result = ({}), t;
    int elem = gCaster->query_skill(gElement_skill),
        form = gCaster->query_skill(gForm_skill);

    rand = random(500) - random(500) + 500;

    gSpell_task += (gElement_needed > elem ? (gElement_needed - elem) * 30 :0);
    gSpell_task += (gForm_needed > form ? (gForm_needed - form) * 30 : 0);

    caster = MIN(gCaster->query_skill(SS_SPELLCRAFT), elem) +
	     MIN(gCaster->query_skill(SS_SPELLCRAFT), form);

    if (!gResolve_type)
        return ( (t = (100 * (rand + 2 * caster - gSpell_task) / gSpell_task))
		 > 0 ? t : 0);
    else
        for (i = 0; i < sizeof(gTargets); i++)
	{
	    result += ({ ((t = (100 * (rand + 2 * caster - gSpell_task) /
			  gSpell_task)) > 0 ? t : 0) });
	}

    return (!sizeof(result - ({ 0 })) ? 0 : result);
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
    int i, j, k, l;
    object *items, *casterInv, *invToCheck, *tempFound_ingrs; 

    gFound_ingrs = ({ });
    tempFound_ingrs = ({ });
    invToCheck = ({ });

    casterInv = all_inventory(gCaster);

    /* Use filter here. */
    if ((i = sizeof(gIngredients)))
        while (i--)
        {
        if(j = sizeof(casterInv))
	    while (j--)
	    {
		if (function_exists("create_container", casterInv[j]))
		    if(casterInv[j]->query_prop(CONT_I_HOLDS_COMPONENTS) &&
			!(casterInv[j]->query_prop(CONT_I_CLOSED)))
		      {
			invToCheck += all_inventory(casterInv[j]);
		      }

	    }

	    invToCheck += casterInv;

	    if (parse_command(gIngredients[i], invToCheck, "%i", items))
	    {
		items = visible_access(items);
	        gFound_ingrs += items;

		if (gTmp > 0)
		    return 0;
	    }

	    if (sizeof(items = filter(invToCheck, &operator(==)(gIngredients[i]) @ &->query_herb_name())))
	      {
		find_player("karath")->catch_msg("I am looking for " +
			gIngredients[i] + "\n");
		/* Ugly ugly hack to put it in %i form of parse_command */
		/* We will only ever look for one herb at a time. */
		l = (sizeof(items) > 1 ? 0 : 1);
		items = ({ l , }) + items;

                if (!sizeof( gFound_ingrs & items ))
		  {
		    items = visible_access(items);
		    gFound_ingrs += items;
		  }

		if (gTmp > 0)
		    return 0;
	      }
	    if (!sizeof(gFound_ingrs)) return 0;
	}
    for ( k = 0; k < sizeof(gFound_ingrs); k++)
      {
        find_player("karath")->catch_msg("found "+file_name(gFound_ingrs[k])+"\n");
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

    gArg = arg;

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
    if ((gSpell_attack || gSpell_offensive) && no_magic_fail)
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

    /* Look for the targets */
    gTargets = gFind_target(arg);

    if (!gTargets || !sizeof(gTargets))
        return 1;

    /* Do we have enough mana to cast the spell? */
    if (gCaster->query_mana() < gMana_needed)
    {
	write(hook_no_mana_fail());
        return 1;
    }

    gSilent = ((sizeof(gTargets) > 1) ? 1 : 0);

    reduce = ftoi(itof(gMana_needed) * gMana_fail);

    /* We need to reduce this later, when the spell is cast */
    gMana_left = gMana_needed - reduce;

    gCaster->add_mana(-reduce);

    /* The spell is ready to be cast. */
    gCaster->add_prop(LIVE_O_CONCENTRATE, this_object());
    gCaster->add_prop(LIVE_O_CASTING_ENV, room);

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
	    gCaster->catch_msg(hook_living_no_magic_attack_fail(ob));
        return 0;
    }

    if (!F_DARE_ATTACK(gCaster, ob) && (gCaster->query_attack() != ob))
    {
        if (!gSilent)
	    gCaster->catch_msg(hook_dont_dare_attack_fail(ob));
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

    if (gSpell_attack || gSpell_offensive)
    {
        /* Get all targets that we can hit with our spell */
        gTargets = filter(gTargets, &filter_kill_access());

        if (!sizeof(gTargets))
        {
	    gCaster->catch_msg(hook_targets_gone());
            gCaster->remove_prop(LIVE_O_CONCENTRATE);
            return 0;
        }

        /* This must be called */
        if (gSpell_attack)
            gCaster->add_prop(LIVE_O_SPELL_ATTACK, this_object());

        /* Do we need to attack the enemy? */
	if (gCaster->query_attack() != gTargets[0])
	    gCaster->attack_object(gTargets[0]);

        if (gSpell_attack)
            return 1;
    }
 
    /* Make sure we are in the same room as we were when we started */
    if(gCaster->query_prop(LIVE_O_CASTING_ENV) != environment(gCaster))
      {
	if(gSpell_stationary)
	  {
		gCaster->catch_msg(hook_changed_env());
        	gCaster->remove_prop(LIVE_O_CONCENTRATE);
		return 0;
	  }
	if(gCaster->query_prop(LIVE_O_CASTING_ENV) !=
		gCaster->query_prop(LIVE_O_LAST_ROOM))
	  {
		if(random(gSpell_task/3) >
		    (random(gCaster->query_skill(SS_SPELLCRAFT)) +
		     random(gCaster->query_stat(SS_DIS))))
	  	{
		    gCaster->catch_msg(hook_changed_env());
        	    gCaster->remove_prop(LIVE_O_CONCENTRATE);
		    return 0;
	  	}
	  }
	else
	if(random(gSpell_task/4) >
	    (random(gCaster->query_skill(SS_SPELLCRAFT)) +
	     random(gCaster->query_stat(SS_DIS))))
	 	{
	    gCaster->catch_msg(hook_changed_env());
            gCaster->remove_prop(LIVE_O_CONCENTRATE);
	    return 0;
		}
      }

    /* Look for the targets, again (This is needed) */
    gTargets = gFind_target(gArg);
    if (!sizeof(gTargets))
      {
	gCaster->catch_msg(hook_targets_gone());
        gCaster->remove_prop(LIVE_O_CONCENTRATE);
	return 0;
      }

    /* Check if the spell is successfully cast */
    result = resolve_spell();
    if (intp(result) && !result)
    {
        mixed msg = gSpell_fail();
        if (stringp(msg))
            gCaster->catch_msg(gSpell_fail());
        gCaster->remove_prop(LIVE_O_CONCENTRATE);
        return 0;
    }

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
            spell->set_element(gElement_skill);
            spell->set_form(gForm_skill);
//	    spell->set_caster(gCaster);

//	    ((t > 1) ? spell->set_power(gResults[i]) : 
//	     spell->set_power(gResults[0]));

            spell->move_spell(gCaster, gTargets[i]);
        }
    }

    gCaster->remove_prop(LIVE_O_CONCENTRATE);

    if (sizeof(gFound_ingrs))
    {
        gFound_ingrs = filter(gFound_ingrs, prepare_ingrs_heap);
	gCaster->catch_msg(hook_use_ingredients(gFound_ingrs));
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
    int hurt, i, size;
    mixed *hitresult, *result;

    set_this_player(gCaster);

    gCaster->remove_prop(LIVE_O_CONCENTRATE);

    i = size = sizeof(gTargets);
 
    /* Check if the spell is successfully cast */
    result = resolve_spell(); 
    if (intp(result) && !result)
    {
        mixed msg = gSpell_fail();
        if (stringp(msg))
            gCaster->catch_msg(gSpell_fail());
        return;
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
	    else
	        /* This will start an attack too */
	        gTargets[i]->notify_got_hit_by_spell(attacker);
        }

    if (size)
    {
        gCaster->add_mana(-gMana_left);

        if (sizeof(gFound_ingrs))
	{
            gFound_ingrs = filter(gFound_ingrs, prepare_ingrs_heap);
            gCaster->catch_msg(hook_use_ingredients(gFound_ingrs));
            filter(gFound_ingrs, &->remove_object());
	}

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
 *		      - In my_command, at the end, removed
 *		        add_attack_delay
 *
 */
