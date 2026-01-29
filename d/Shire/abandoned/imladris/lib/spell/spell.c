/*
 * /std/spell.c  -  The standard spell object.
 *
 * This is the standard spell object for all legal spells in Genesis.
 *
 * General Overview
 *
 *     A spell can not be cast unless triggered by another object, which
 *     can be any object in the game. To start a spell, this origin object
 *     must *clone* an object which inherits this file, and then call:
 *
 *	  spell_object->cast_spell(arg);
 *
 *     Where arg is the string after the verb.
 *     
 *
 */

inherit "/std/object";

#include <ss_types.h>
#include <comb_mag.h>
#include <macros.h>

#include "defs.h"
#include "spell.h"
#include "effect.h"

/*
 * Global variables.
 */

int extra_difficulty;  /* Difficulty added when requirements not met */
int spell_power;       /* The spells power. */
object caster;	       /* The caster of this spell. */
object origin;	       /* The origin of the spell, a spell book or a cmdsoul? */
object *targets;       /* The targets of this spell. */
object sf;	       /* The spell function hook. Functions checked are:

			    sf->start_spell_msg(arg);
			    sf->unsuccesful_cast(res);
			    sf->no_target();

			*/

/*
 * Prototypes
 */

void do_instant_spell();
void unsuccessful_cast(int failed);

/*
 * Function:	set_caster
 * Description: Sets the caster of this spell.
 */
void
set_caster(object who)
{
    caster = who;
}

/*
 * Function:	query_caster
 * Description: Returns the caster of this spell.
 *		Can be used by counter-spells.
 */
object
query_caster()
{
    return caster;
}

/*
 * Function name:  query_targets
 * Description:    Returns a list of the objects to be affected. This can
 *		   be used by a reverse or a counter-spell.
 */
object *
query_targets()
{
    return targets;
}

/*
 * Function name:   set_targets
 * Description:     Sets the targets of this spell. Used by counter-spells.
 */
void
set_targets(mixed who)
{
    if(objectp(who))
	targets = ({ who });
    else if(pointerp(who))
	targets = who;
}

/*
 * Function name:   query_origin()
 * Description:     Returns the origin of this spell. It returns the object
 *		    responsible for the casting of this spell.
 */
object
query_origin()
{
    return origin;
}

/*
 * Function name:   set_origin
 * Arguments:	    (object) orig - The origin point of this spell.
 * Description:     Sets the origin of this spell to be set to a specific
 *		    object. This object is usually the object responsible
 *		    for casting a spell.
 */
void
set_origin(object orig)
{
    origin = orig;
}

/*
 * Function name:   set_sf
 * Arguments:	    (object) spell_fun
 * Description:     Sets this spell to hook the following functions:
 *
 *		    sf->start_spell_msg(arg);
 *		    sf->unsuccesful_cast(res);
 *		    sf->no_target();
 */
void
set_sf(object spell_fun)
{
    sf = spell_fun;
}

/*
 * Function name:   query_sf
 * Returns:	    The current spell_fun.
 */
object
query_sf()
{
    return sf;
}

/*
 * Function name:   set_spell_power
 * Arguments:	    (int) power [range 1..100].
 * Description:     Sets the power of this spell. Should *not* be called
 *		    from the spell object itself, since it is calculated
 *		    in this file.
 */
void
set_spell_power(int power)
{
    spell_power = power;
}

/*
 * Function name:   query_spell_power
 * Returns:	    The current spell power of this spell (range 1..100,
 *		    normally, though up to 1000 for godly spells.)
 */
int
query_spell_power()
{
    return spell_power;
}

/*
 * Function name:   add_difficulty
 * Arguments:	    (int) diff	: extra difficuly.
 * Description:     Under certain circumstances (standing on your head,
 *		    swimming underwater with an anchor tied around your neck..)
 *		    You may wish to make a spell more difficult to cast than
 *		    normal. An added difficulty of 300 is one full level
 *		    (see 'man tasks' for more details).  This function allows
 *		    you to adjust the difficulty by 'diff'.
 */
void
add_difficulty(int diff)
{
    extra_difficulty += diff;
}

/*
 * Function name:   create_spell
 * Description:     This is the function to redefine for all spells.
 *		    You should set the appropriate properties of the
 *		    spell here.
 */
public void
create_spell()
{
}

/*
 * Function name:   create_object
 * Description:     Sets some defaults for the spell, call the user function
 *		    'create_spell'.
 */
nomask void
create_object()
{
    targets = ({});

    change_prop(SPELL_I_IS, 1);

    change_prop(SPELL_O_EFFECT, 0);
	/* By default all effects are instant. */

    change_prop(SPELL_I_GENERAL, SS_SPELLCRAFT);
	/* By default all spells require spellcraft, not SS_ALCHEMY
	   or SS_HERBALISM. We want this because some 'spells' just
	   require standard skills, for instance an assassin guild,
	   using SS_SNEAK to do the famous 'vanishing' trick, which
	   actually should use the magic system. */

    change_prop(SPELL_I_DURATION, DURATION_INSTANT);
	/* By default, the spell should not continue to exist in
	   cyberspace, but be destructed after the spell is cast. */

    change_prop(EFFECT_I_IS, EFFECT_SPELL);
    change_prop(EFFECT_I_POWER, 10);
	/* By default, each spell is an effect, and it's power is 10. */

    create_spell();
}

/*
 * Function name:   valid_skills
 * Description:     This function checks to see that the skills the caster
 *		    has are sufficient to cast the spell. If they are not,
 *		    the spell difficulty is increased one full level for each
 *		    deficient skill.
 */
int
valid_skills()
{
    int elem_skill, form_skill;

    form_skill = this_player()->query_skill(query_prop(SPELL_I_FORM_SKILL));
    elem_skill = this_player()->query_skill(query_prop(SPELL_I_ELEMENT_SKILL));

    if (form_skill < query_prop(SPELL_I_FORM_NEEDED))
	extra_difficulty += 300;

    if (elem_skill < query_prop(SPELL_I_ELEMENT_NEEDED))
	extra_difficulty += 300;

    /* notify_fail("You haven't got the skills to cast this spell.\n"); */
    return 1;
}

/*
 * Function name:   test_material
 * Arguments:	    (string) name	 : Name of the material requirement.
 *		    (int) environment_ok :
 *			0 - Component must be in the inventory. [Default]
 *			1 - Component can be in the envoronment of the player.
 * Description:     Checks to see if the passed material component
 *		    requirements are met.
 * Returns:	    A object pointer to the material found, or 0 if not found.
 */
varargs object
test_material(string name, int environment_ok = 0)
{
    if (environment_ok)
	return (present(name, ({ environment(this_player()) })
            + deep_inventory(this_player()) ) );
    else
        return (present(name, deep_inventory(this_player())) );
}

/*
 * Function name:   valid_materials
 * Description:     Checks to see if the player has a valid set of components
 *		    to cast the spell or not. For reference, each element in
 *		    the material array is an array of the following format:
 *
 *		    ({ name, class, environment_ok, pct_consumed,
 *		       write_msg, say_msg, extra_difficulty })
 *
 * Returns:	    1 if valid materials, 0 if not.
 */
public int 
valid_materials()
{
    mixed *materials;
    int i, j;
    object found;
    string *class_used;
    string *class_not_used;

    materials = query_prop(SPELL_AM_MATERIALS);

    for (i = 0; i < sizeof(materials); i++)
    {
        if (member_array(materials[i][1], class_used) >= 0)
            break;

        found = test_material(materials[i][0], materials[i][2]);
	if (!found)
	{
	    class_not_used += materials[i][1];
	    extra_difficulty += materials[i][7];
	}
        else
        {
            class_used += materials[i][1];
            class_not_used -= materials[i][1];
            if (random(100) < materials[i][3])
            {
		write(materials[i][4]);
		say(materials[i][5]);

                if (!found->query_prop(HEAP_I_IS))
                    found->remove_object();
                else
		    found->set_heap_size(found->num_heap() - 1);
            }
        }
    }

    return !sizeof(class_not_used);
}

/*
 * Function name:   area_of_effect
 * Arguments:	    (string) arg    : The arguments of this spell.
 * Description:     This is the routine to determine what area of effect
 *		    the spell has depending on the arguments after a spell.
 * Returns:	    (object *)	    : The area of effect.
 */
object *
area_of_effect(string arg)
{
    return ({});
}

/*
 * Function name:   pre_parse
 * Arguments:	    The arguments (string).
 * Description:     Preparses the input.
 * Returns:	    The argument string.
 */
string
pre_parse(string arg)
{
    return arg;
}

/*
 * Function name:   start_spell_msg
 * Arguments:	    arg - The arguments passed with the spell.
 * Description:     Handles the output given when the caster begins
 *		    to chant a spell.
 * Returns:         If it did handle output.
 */
int
start_spell_msg(string arg)
{
    /* This function only shows how to use this function. */
    return 0;
}

/*
 * Function name:   start_spell_fail
 * Arguments:	    arg: The arguments.
 * Description:     Checks weather the caster can cast a spell.
 * Returns:	    1 - If the spell is not to be cast.
 *		    0 - If not.
 */
int
start_spell_fail(string arg)
{
    string *fumble = this_player()->query_prop(LIVE_AS_ATTACK_FUMBLE);

    if (sizeof(fumble))
    {
	write("You fail to cast your spell!\n");
	write(fumble[0]);
	return 1;
    }
    else
	return 0;
}

/*
 * Function name:    find_targets
 *
 * Arguments:	     arg: The arguments.
 *
 * Description:      Returns a list of the objects to be affected, based upon
 *		     the string passed in. It calls the area_of_effect()
 *		     function to find targets, and removes illegal targets
 *		     if the spell is an attack spell.
 *
 * Returns:	     The targets (object *).
 *
 * Note:	     A ({}) returned means that the spell fails.
 */
object *
find_targets(string arg)
{
    object *targets;
    int i;

    if (objectp(sf) && sizeof(targets = sf->area_of_effect(arg)))
	return targets;

    targets = area_of_effect(arg);
    if (!sizeof(targets))
	return 0;

    if (query_prop(SPELL_I_ATTACK))
	for (i = sizeof(targets) - 1; i >= 0; i--)
        {
	    if (targets[i]->query_prop(OBJ_M_NO_MAGIC_ATTACK))
		targets = exclude_array(targets, i, i);
	}
    return targets;
}


/*
 * Function name:   cast_spell
 *
 * Description:     Actually cast the spell.  This is the entry point to
 *		    the object and actually handles the complete casting
 *		    of the spell.
 *
 * Arguments:	    arg  : The string after the spell verb.
 *		    orig : The object which has triggered the spell.
 *			   [default - previous_object()].
 *			   Typically a cmdsoul or a spellbook.
 *
 * Returns:	    1 - If the spell accepted the syntax of the spell.
 *		    0 - If not, usually having a notify_fail command.
 */
varargs public int
cast_spell(string arg, object orig)
{
    object room;
    int casting_time;
    string mess;

    if (!orig)
	orig = previous_object();

    if (!IS_CLONE)
	return CLONE_COPY->cast_spell(arg, orig); /* We need to use copies. */

    caster = this_player();

    set_origin(orig);

    room = environment(caster);
    if (RNMAGIC(room))
	return notify_fail("You can not cast spells here.\n");

    if (!valid_skills()) 
	return 0;

    if (!valid_materials()) 
        return 0;

    arg = pre_parse(arg);

    if (start_spell_fail(arg))
	return 0;

    targets = find_targets(arg);
    if (!targets || sizeof(targets)==0)
        return 0;

    if (caster->query_mana() < query_prop(SPELL_I_MANA))
	return notify_fail("You do not have mana to properly cast the spell.\n");

    if (!sf || !sf->start_spell_msg(arg))
    {
	write("You raise your hands and start to chant a spell.\n");
	mess = " raises "+this_player()->query_possessive()+
	       " hands and starts to chant a spell.";
	say( ({ METNAME + mess + "\n",
		TART_NONMETNAME + mess + "\n",
		"Someone starts chanting a spell.\n" }) );
    }
    
    caster->add_mana(-query_prop(SPELL_I_MANA)/2);

    casting_time = query_prop(SPELL_I_CASTING_TIME)+
		   caster->query_prop(LIVE_I_ATTACK_DELAY);

    /* Make sure that npc's knows they are cast upon.
       Also, a shadow might detect it, a reverse-spell for instance.. :-) */

    targets->notify_spell_cast(this_object());

    if (casting_time == -1)
    {
	this_object()->do_instant_spell();
	return 1;
    }

    move(this_player());   /* Move the spell to the player */

    /* Freeze caster until spell is complete. */
    caster->add_prop(LIVE_O_CONSENTRATES_SPELL, this_object());

    /* Ensure no fighting until spell is complete. */
    if (query_prop(SPELL_I_ATTACK))
    {
	caster->add_prop(LIVE_O_SPELL_ATTACK, this_object());
	caster->add_prop(LIVE_I_ATTACK_DELAY, casting_time);
    }
    else
    {
	call_out("do_spell", casting_time);
	caster->add_prop(LIVE_AS_ATTACK_FUMBLE,
	    ({"You avoid attacking while chanting upon your spell.\n"}));
    }

    return 1;
}

/*
 * Function name:   calc_result
 *
 * Description:     Calculates the outcome of a spell. Redefine this if
 *		    you feel that the the resolve_task routine is inapropiate.
 *		    But remember the rules!
 *
 * Returns:	    The result of the spell. Negative or zero indicates
 *		    spell failure. The number if positive indicates how
 *                  succesful it was, from 1 to 1000 (Percentiles).
 */
int
calc_result()
{
    return caster->resolve_task(
	query_prop(SPELL_I_DIFFICULTY) + extra_difficulty,
	({
	    query_prop(SPELL_I_GENERAL),
	    query_prop(SPELL_I_FORM_SKILL),
	    query_prop(SPELL_I_ELEMENT_SKILL)
	}));
}

/*
 * Function name:   calc_power
 *
 * Description:     Calculates the power of this spell.
 *		    The power ranges from [1..1000].
 *		    A spell with 1000 power is a God-like spell.
 *		    Normal spells should lie in range 1 to 100.
 *
 * Returns:	    The spell power.
 *
 * Proposed calc:   Wisdom is used to for calculating the power.
 *		    How much mana used is added quite a lot.
 *		    A good result will add to this in a certain amount.
 *		    The higher difficulty the more powerful.
 *		    The higher skills needed the more powerful.
 */
int
calc_power(int result)
{
    spell_power =
	caster->query_stat(SS_WIS) / 10 +
	query_prop(SPELL_I_MANA) / 5 +
	query_prop(SPELL_I_FORM_NEEDED) / 4 +
	query_prop(SPELL_I_ELEMENT_NEEDED) / 4 +
	query_prop(SPELL_I_DIFFICULTY) / 10 +
	ABS(result)/10;

    if (spell_power < 0)
	spell_power = 0;

    if (spell_power > 1000)
	spell_power = 1000;

    return spell_power;
}

/*
 * Function name:   do_spell
 *
 * Description:     After cast_spell has verified all requirements, this
 *		    function is called out to in order to handle spell casting
 *		    time. It may also be called from the combat object.
 */
public void
do_spell()
{
    int res, power;

    caster->remove_prop(LIVE_O_CONSENTRATES_SPELL);
    caster->remove_prop(LIVE_AS_ATTACK_FUMBLE);

    res = calc_result();

    power = calc_power(res);
		     /* Done before checks for unsuccesful cast,
			after all, there is power in the spell
			even if you fumble with it. */

    if (res <= 0 || power == 0)
    {
	unsuccessful_cast(-res);
	return;
    }

    caster->add_mana(-query_prop(SPELL_I_MANA)/2);

    if(!query_prop(SPELL_O_EFFECT))
	this_object()->do_instant_effect(targets, power);
    else
	this_object()->do_effect(targets, power);

    switch(query_prop(SPELL_I_DURATION))
    {
	case DURATION_UNTIL_REBOOT:
	    return;
	default:
	    call_out("dispel_effect", query_prop(SPELL_I_DURATION));
	    return;
    }
}

/* Function name:   do_instant_spell
 * Description:     Handles the casting of immediate spells. These should be
 *		    rare, but some spells must be able to be cast at once.
 */
public void
do_instant_spell()
{
    do_spell(); /* Call the delayed do_spell imidately. */
}

/*
 * Function name:   spell_attack
 * Description:     This is the entry point for a spell attack called from
 *		    the combat object. It simply calls do_spell()
 */
public void
spell_attack(object me, object enemy)
{
    do_spell();
}

/*
 * Function name:   unsuccessful_cast
 *
 * Argument:	    failed (int) :  How much failed.
 *				    (Positive number, typical range 0..1000+)
 *
 * Description:     Handles what is supposed to happen if you fail to cast a
 *		    spell. This can be used to inflict damage to the caster on
 *		    a poorly cast dangerous spell.
 */
public void
unsuccessful_cast(int failed)
{
    string mess = " fails to cast a spell.";

    if (sf && sf->unsuccessful_cast(failed))
	return;

    write("Your spell fails.\n");
    say( ({ METNAME + mess + "\n",
	    TART_NONMETNAME + mess + "\n",
	    "" }) );
}

/*
 * Function name:   do_instant_effect
 *
 * Arguments:	    targets (object *) : The targets of this spell.
 *		    power (int)        : The power in this spell.
 *
 * Description:     Handle the immediate effects of the spell. Many spells will
 *		    only have instant effects and this will be sufficient.
 *		    For spells with a duration, set SPELL_O_EFFECT to an object
 *		    which inherits spell_effect.c
 *
 *		    This is routine is also called for spells with duration,
 *		    but this is to let the spell produce output messages, the
 *		    shadowing/moving of spell effects are done in do_effect.
 */
public void 
do_instant_effect(object *targets, int power)
{

}

/*
 * Function name:   init_effect
 *
 * Arguments:	    effect_file (string) : The effect file name.
 *		    target (object)	 : The target of *one* effect.
 *		    power (int)		 : The power of the spell.
 *
 * Description:     Takes care of initialising an effect of an object.
 */
void
init_effect(string effect_file, object target, int power)
{
    object ob;
    string err_msg;

    setuid();
    seteuid(getuid()); /* Set the right priveleges to clone objects. */

    ob = clone_object(effect_file);
    if (!ob)
	log_file("spells",
		file_name(this_object()) + ": could not load.");

    if (function_exists("init_shadow", ob) == EFFECT_SHADOW_FILE)
    {
	err_msg = ob->init_shadow(target, power);
	if (stringp(err_msg))
	{
	    log_file("SPELL_ERRORS",
		effect_file+" : Failed to shadow " + file_name(target)+"\n");
	    write("You notice a failure in the fabric of space:\n"+
		  err_msg);
	}
    }
    else
    {
	err_msg = ob->init_object(target, power);
	if (stringp(err_msg))
	{
	    log_file("SPELL_ERRORS",
		effect_file+" : Failed to move into " + file_name(target)+"\n");
	    write("You notice a failure in the fabric of space:\n"+
		  err_msg);
	}
    }
}

/*
 * Function name:   in_spell_range
 *
 * Arguments:	    target (object) : Target of a spell.
 *
 * Description:     Checks to see weather or not a target is within
 *		    the spell range.
 *
 * Returns:	    1 - If target is withing spell range.
 *		    0 - If not.
 */
int
in_spell_range(object target)
{
    if (living(target))
	return environment(target) == environment(caster);
    else
	return environment(target) == environment(caster) ||
	       environment(target) == caster ||
	       environment(caster) == target;
}

/*
 * Function name:   no_targets
 *
 * Description:     Displays an error message when no target is
 *		    within spell range when the spell is actually
 *		    cast.
 *
 * Returns:	    0 - if the spell should not continue with no targets
 *		    1 - otherwise
 *
 * Note:	    If you use set_sf(ob), then the return values should be:
 *		    0 - if normal message routine should be used.
 *		    1 - if you define your own messages, and spell should stop.
 *		    2 - if you define own messages, but spell effects should
 *			procede normally even if no targets are within range.
 */
int
no_targets()
{
    int ret;
    string mess;

    if (objectp(sf) && (ret = sf->no_targets()))
	return ret == 1;

    mess = " spell failed.";
    write("Your spell fails since target(s) are out of spell range.\n");
    say( ({ LANG_POSS(METNAME) + mess + "\n",
	    LANG_POSS(TART_NONMETNAME) + mess + "\n",
	    "" }) );
    return 0;
}

/*
 * Function name:   do_effect
 *
 * Arguments:	    targets (object *)	: The targets of this spell.
 *		    power (int) 	: The power of this spell.
 *
 * Description:     This function handles all effects of spells, including
 *		    checking for other spells in the appropriate environment
 *		    and attempting cancellation of those spells.
 *
 *		    It also starts the duration effects.
 */
public nomask void
do_effect(object *targets, int power)
{
    int i;
    string effect_file;
    string err_msg;
    object ob;

    targets = filter(targets, "in_spell_range", this_object());

    if (!sizeof(targets) && !no_targets())
	return;

    effect_file = query_prop(SPELL_O_EFFECT);

    if (!effect_file)
	return;

    this_object()->do_instant_effect(targets, power);

    for (i = 0; i < sizeof(targets); i++)
	init_effect(effect_file, targets[i], power/sizeof(targets));
}

/*
 * Function name:   dispel_effect
 * Description:     What if someone tries to dispel this spell object,
 *		    For instance, during preparation of a spell, or
 *		    a spell object in a wand.
 */
int
dispel_effect()
{
    remove_call_out("do_spell");
    call_out("remove_object",0);
}








