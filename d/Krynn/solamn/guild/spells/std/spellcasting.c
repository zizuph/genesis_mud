/*
 * Spellcaster.c
 *
 * This file should be inherited by the object from which the spell is cast 
 * from, ie a book or a staff.
 */

#pragma strict_types

#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <std.h>
#include <macros.h>
#include <formulas.h>
#include <comb_mag.h>

//#define LIVE_I_CONCENTRATE "_live_i_concentrate"
inherit "/cmd/std/command_driver";

string *gVerbs = ({}),		/* The verb list */
       *gFuncs = ({}),		/* Function list */
       *gNames = ({}),		/* Name list */
       *gIngredients,		/* The list of ingredients needed */
        gSpell_object,		/* The filename to the spell object */
        gArg;                   /* The argument given to cast the spell */

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
     gSpelltask,	       	/* The difficulty of the spell */
     gSilent,                   /* Don't write a message for every object */
    *gResults;			/* The results of the spell */

object *gTargets,	       	/* A list of target(s) to cast the spell on */
       *gFound_ingrs,           /* A list of found ingredients */
        gCaster;	       	/* The one who casts the spell */

function gFind_target,		/* The function used to find the target(s) */
         gSpell_message,	/* The function used to give the messages */
         gSpell_success,	/* The function used to calculate the success */
         gSpell_fail,		/* Use this function when the spell fails */
	 gSpell_resist,		/* Use this function to calc the resistance */
         gSpell_damage;         /* Use this function to calc the damage */

public object *find_this_object(string arg);
public varargs void spell_message(object caster, object target, mixed result);
public mixed spell_success(object caster, object *targets);
public void spell_fail();
public int spell_damage(object caster, object target);
public int spell_resist(object target);

/*
 * Function:	default_config_spell
 * Description:	Set the default values for the variables
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
    gMana_needed = 1000;

    /* By default the damage type is MAGIC_DT */
    gDamage_type = MAGIC_DT;

    /* By default no spell object is needed */
    gSpell_object = 0;

    /* By default call the internal spell_message */
    gSpell_message = spell_message;

    /* By default call the internal spell_success */
    gSpell_success = spell_success;

    /* By default call the internal spell_fail */
    gSpell_fail = spell_fail;

    /* By default call the internal spell_damage */
    gSpell_damage = spell_damage;

    /* By default call the internal spell_resist */
    gSpell_resist = spell_resist;
}

/*
 * Function:	add_spell
 * Description: Add the spell to the list of active spells.
 * Arguments:   verb - The activating verb string
 *              function - The function to call
 *              name - The name of the spell (to be displayed in
 *                     the player spell list).
 */
nomask void
add_spell(string verb, string func, string name)
{
    /* The spell was already added once */
    if (member_array(verb, gVerbs) >= 0)
        return;

    SECURITY->add_spell(verb, func, this_object(), name);

    gVerbs += ({ verb });
    gFuncs += ({ func });
    gNames += ({ name });

    /* Make sure the command driver reads the list again */
    update_commands();
}

/*
 * Function:	remove_spell
 * Description: Remove the spell with the given verb string.
 * Arguments:   verb - The verb of the spell to remove.
 * Returns:	       True if the remove was successful, otherwise false.
 */
nomask public int
remove_spell(string verb)
{
    int index;

    index = member_array(verb, gVerbs);

    if (index < 0)
        return 0;

    gVerbs = exclude_array(gVerbs, index, index);
    gFuncs = exclude_array(gFuncs, index, index);
    gNames = exclude_array(gNames, index, index);

    /* Make sure the command driver reads the list again */
    update_commands();

    return 1;
}

/*
 * Function:	list_spells
 * Description:	This function is called to list the spells from
 *		the player soul when the command "spells" is typed.
 */
public void
list_spells()
{
    int i;
    string space;

    space = "                                                 ";

    i = sizeof(gVerbs);
    while (i--)
        write(gVerbs[i] + extract(space, 0, 17 - strlen(gVerbs[i])) +
              gNames[i] + extract(space, 0, 31 - strlen(gNames[i])) +
              "\n");
}

/*
 * Function:	query_cmdlist
 * Description: Used by the command_driver, called each time the
 *              command set is reloaded.
 */
nomask public mapping
query_cmdlist()
{
    return (sizeof(gVerbs) ? mkmapping(gVerbs, gFuncs) : ([ ]));
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
    return 1;
}

public int
spell_resist(object target)
{
    return 0;
}

/*
 * Function:	spell_fail
 * Description:	The spell failed.
 * Returns:	A string that should be written or an integer.
 */
public mixed
spell_fail() { return 0; }

/*
 * Function:	set_caster
 * Description:	Set the caster of the spell
 * Arguments:	who - The caster
 */
public void
set_caster(object who) { gCaster = who; }

/*
 * Function:	query_caster
 * Description:	Return the caster of the spell
 */
public object
query_caster() { return gCaster; }

/*
 * Function:	set_ingredients
 * Description:	Set the ingredients needed for the spell.
 * Arguments:	list - A ingredient or a list of ingredients needed for
 *		       the spell.
 */
public void
set_ingredients(string *list)
{
    gIngredients = (stringp(list) ? ({ list }) : list);
}

/*
 * Function:	query_ingredients
 * Description:	Return the ingredients for the spell
 */
public string *
query_ingredients() { return gIngredients; }

/*
 * Function:	set_spell_attack
 * Description:	Make the spell an attack spell.
 */
public void
set_spell_attack() { gSpell_attack = 1; }

/*
 * Function:	set_damage_type
 * Description:	Set the damage type this spell is of. Most spells would have
 *		type MAGIC_DT, but a spell like magic missiles could be of
 *		W_IMPALE type.
 * Arguments:	type - The damage type, as found in /sys/wa_types.h
 */
public void
set_damage_type(int type) { gDamage_type = type; }

/*
 * Function:	query_damage_type
 * Description:	Return the damage type of the spell.
 */
public int
query_damage_type() { return gDamage_type; }

/*
 * Function:	set_spell_time
 * Description:	Set the time it takes to prepare the spell. The real time
 *		will be (time + 2 + LIVE_I_ATTACK_DELAY).
 * Arguments:	time - The time it should take
 */
public void
set_spell_time(int time) { gSpell_time = time; }

/*
 * Function:	query_spell_time
 * Description: It is called from cmdhooks.c, and should return the time
 *		in seconds it takes to prepare the spell. The actual time
 *		will be (time + 2 + LIVE_I_ATTACK_DELAY).
 * Arguments:	verb - The verb that initiated this spell.
 *		arg  - The arguments to the verb.
 * Returns:	The time in seconds.
 */
public int
query_spell_time(string verb, string arg)
{
    return gSpell_time;
}

/*
 * Function:	set_element
 * Description:	Set the element type and the minimum of skill needed.
 * Arguments:	type - The element type, as found in /sys/ss_types.h
 *		       skill - The value in skill needed for the spell.
 */
public void
set_element(int type, int skill)
{
    gElement_skill = type;
    gElement_needed = skill;
}

/*
 * Function:    query_element
 * Description: Return the element skill.
 */
public int
query_element() { return gElement_skill; }

/*
 * Function:	set_form
 * Description:	Set the form type and the minimum of skill needed.
 * Arguments:	type - The form type, as found in /sys/ss_types.h
 *		       skill - The value in skill needed for the spell.
 */
public void
set_form(int type, int skill)
{
    gForm_skill = type;
    gForm_needed = skill;
}

/*
 * Function:    query_form
 * Description: Return the form skill.
 */
public int
query_form() { return gForm_skill; }

/*
 * Function:	set_mana_spell
 * Description:	Set the amount of mana needed to cast the spell.
 * Arguments:	mana - The amount of mana
 */
public void
set_mana_spell(int mana) { gMana_needed = mana; }

/*
 * Function:	query_mana_spell
 * Description:	Return the amount of mana needed to cast this spell.
 */
public int
query_mana_spell() { return gMana_needed; }

/*
 * Function:	query_spell_targets
 * Description:	Returns all the found targets
 */
public object *
query_spell_targets() { return gTargets; }

/*
 * Function:	set_duration
 * Description:	Set the time the spell will last in seconds
 * Arguments:	time - The time the spell should last
 */
public void
set_duration(int time) { gDuration = time; }

/*
 * Function:	query_duration
 * Description:	Return the time the spell should last
 */
public int
query_duration() { return gDuration; }

/*
 * Function:	set_find_target
 * Description:	Set the function to use when we are trying to locate
 *		the target(s)
 * Arguments:	func - The function to be used:
 *		       object *func(string str)
 */
public void
set_find_target(function func) { gFind_target = func; }

/*
 * Function:	set_spell_message
 * Description:	Set the function to use when we want to give the messages.
 * Arguments:	func - The function to be used.
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
 * Function:	set_spell_success
 * Description:	Set the function to use when we want to calculate
 *		the result for the spell. Either one result/target or
 *		only one result for all targets. Calculating results
 *		should be done with resolve_task. If resolve_task fails
 *		then the result should be 0.
 * Arguments:	func - The function to be used.
 *		       mixed func(object caster, object *targets)
 *		       func should return an integer or an array
 *		       of integers.
 */
public void
set_spell_success(function func) { gSpell_success = func; }

/*
 * Function:	set_spell_fail
 * Description:	Set the function to use when the spell fails.
 *	        The function should return a string that contains
 *              the message to write.
 * Arguments:	func - The function to be used
 *		       string *func()
 */
public void
set_spell_fail(function func) { gSpell_fail = func; }

/*
 * Function:	set_spell_resist
 * Description:	Set the function to use when the to get the
 *		resistance value in %. The function should
 *		use query_magic_res() to search for the properties.
 * Arguments:	func - The function to be used
 *		       int *func(object target)
 */
public void
set_spell_resist(function func) { gSpell_resist = func; }

/*
 * Function:	set_spell_damage
 * Description:	Set the function to use when to calculate the damage.
 *              The function should return an integer that could
 *		be used as 'wcpen'. To calculate the value you
 *		should use F_PENMOD, as found in /sys/formulas.h, and
 *		the result value from the success function.
 * Arguments:	func - The function to be used
 *		       int *func(object caster, object target, int result)
 */
public void
set_spell_damage(function func) { gSpell_damage = func; }

/*
 * Function:	set_spell_object
 * Description:	Set the spell object that should be loaded and moved to
 *		the target(s)
 * Arguments:	name - The filename with complete path
 */
public void
set_spell_object(string name) { gSpell_object = name; }

/*
 * Function:	set_spell_task
 * Description:	Set the difficulty of the spell as found in /sys/tasks.h
 * Arguments:	task = The task
 */
public void
set_spell_task(int task) { gSpelltask = task; }

/*
 * Function:	find_this_object
 * description:	By default this_object() will be the target.
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
 * Function:	check_skills
 * Description:	Check the skills on the caster and see if they
 *		are high enough.
 * Returns:	True if it is ok, false otherwise.
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

/*
 * Function:	check_ingredients
 * Description:	Search for an ingredient or a number of ingredients in
 * 		the caster.
 * Returns:	True if everything was found, false otherwise.
 */
public int
check_ingredients()
{
    int i;
    object ob; 

    gFound_ingrs = ({ });

    /* Use filter here. */
    if ((i = sizeof(gIngredients)))
        while (i--)
        {
            if (!(ob = present(gIngredients[i], gCaster)))
	      if(!(ob = present(gIngredients[i], environment(gCaster))))
                return 0;

		gFound_ingrs += ({ ob });
        }

    return 1;
}

/*
 * Function:	start_spell_fail
 * Description:	It is called from cmdhooks.c and it sets up the right
 *		spell and checks so that it is ok to cast.
 * Arguments:   verb - The verb that initiated this spell.
 *		arg  - The arguments to the verb.
 * Returns:	True if the spell failed, false otherwise
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
	write(hook_no_ingredients_fail());
        return 1;
    }

    /* Do we have enough mana to cast the spell? */
    if (gCaster->query_mana() < gMana_needed)
    {
	/*if (!hook_no_mana_fail()) hu???*/
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
 * Function:	query_spell_mess
 * Description:	It is called from cmdhooks.c, and it us used to change the
 *		standard message given when spell is being prepared. You should
 *		handle all the printouts by yourself.
 * Arguments:	verb - The verb that initiated this spell.
 *		arg  - The arguments to the verb.
 * Returns:	True if you are handeling the printouts yourself, 
 *              false otherwise.
 */
public int
query_spell_mess(string verb, string arg)
{
    /* We want the standard messages */
    return 0;
}

/*
 * Function:	filter_kill_access
 * Description:	This function is called from the filter command in
 *		cast_spell, to find all objects that the caster is
 *		able to cast a spell on.
 * Arguments:	ob - The victim
 * Returns:	True if ok, otherwise false
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
 * Function:	cast_spell
 * Description:	This function handles the actual casting of the spell.
 * Arguments:	
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
        gTargets = filter(gTargets, "filter_kill_access", this_object());

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
    if (!(result = gSpell_success(gCaster, gTargets)))
        return gSpell_fail();

    gResults = (intp(result) ? ({ result }) : result);

    gSpell_message(gCaster, gTargets);

    /* Put this in a seperat function */
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

    gFound_ingrs->remove_object();
    gCaster->add_mana(-gMana_left);

    return 1;
}

/*
 * Function:	spell_attack
 * Description:	This function is called from within the combat system
 * Arguments:	attacker - The one who cast the spell
 *		target   - The one who got hit by the spell
 */	
public void
spell_attack(object attacker, object target)
{
    int *result, hurt, i;
    mixed *hitresult;

    gCaster->remove_prop(LIVE_I_CONCENTRATE);

    i = sizeof(gTargets);
 
    /* Check if the spell is successfully cast */
    if (!(result = gSpell_success(gCaster, gTargets)))
	return gSpell_fail();
 
    if (i)
    {
        gCaster->add_mana(-gMana_left);
        gFound_ingrs->remove_object();
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
Rogon tells you: For documentation of the setting of funvars, do state the
arguments and return types for those functions.
Rogon tells you: For instance: Arguments: func - The function to be used: int
func(int a, string b)

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





