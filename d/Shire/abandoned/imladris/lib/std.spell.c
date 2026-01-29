/*
 * The spell handling routines.
 *
 * In this revision, the following have been emphasized:
 * - Maximum use of internal variables, instead of properties. 
 * - Moving most checks out of the spell itself, it should
 *   be in the spell casting object.
 * - Allowing the spell to be as generic to allow non-healers
 *   to cast it. No dependancies on this guild!
 * - Now longer an object, it is to be inherited.
 *
 * Sir Rogon.
 */

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <composite.h>
#include <formulas.h>

static object *targets,
	      *found_ingredients,
	       spell_effect,
	       spell_origin,
	       caster;

static string *spell_ingredients,
	      spell_area_of_effect,
              spell_message,
              spell_damage;

static int spell_attack,
	   spell_time,
	   spell_effect_power,
	   spell_general,
	   spell_duration,
	   spell_element,
	   spell_element_needed,
	   spell_form,
	   spell_form_needed,
	   spell_difficulty,
           spell_multiple_targets,
	   spell_mana_needed;

static int extra_difficulty;

/*
 * Some set_XXX functions
 */
void set_spell_mana_needed(int i) { spell_mana_needed = i; }
void set_spell_difficulty(int i) { spell_difficulty = i; }
void set_spell_element(int i, int j) { spell_element = i; spell_element_needed = j; }
void set_spell_form(int i, int j) { spell_form = i; spell_form_needed = j; }
void set_spell_duration(int i) { spell_duration = i; }
void set_spell_general(int i) { spell_general = i; }
void set_spell_effect(object obj) { spell_effect = obj; }
void set_spell_time(int i) { spell_time = i; }
void set_spell_attack() { spell_attack = 1; }
void set_spell_ingredients(string *ingr) { spell_ingredients = ingr; }
void set_spell_multiple_targets() { spell_multiple_targets = 1; }
void set_spell_message(string str) { spell_message = str; }
void set_spell_damage(string str) { spell_damage = str; }

int query_spell_mana_needed() { return spell_mana_needed; }
int query_spell_attack() { return spell_attack; }

/*
 * Function name:   default_config_spell
 * Description:     Sets some defaults for the spell.
 */
nomask void
default_config_spell()
{
    targets = ({});

    spell_effect = 0;
	/* By default all effects are instant. */
    
    spell_effect_power = 10;
	/* By default, each spell is an effect, and it's power is 10. */

    spell_general = SS_SPELLCRAFT;
	/* By default all spells require spellcraft, not SS_ALCHEMY
	   or SS_HERBALISM. We want this because some 'spells' just
	   require standard skills, for instance an assassin guild,
	   using SS_SNEAK to do the famous 'vanishing' trick, which
	   actually should use the magic system. */

    spell_duration = 0;
	/* By default, the spell should not continue to exist in
	   cyberspace, but be destructed after the spell is cast. */

    spell_ingredients = 0;
	/* By default, no ingredients are needed for the spell.
	   Normally the it will be an array of strings. */

    spell_attack = 0;
        /* By default, this spell wont start a fight. */

    spell_multiple_targets = 0;
        /* By default, this spell can only be cast on one object/living. */

    spell_area_of_effect = "area_of_effect";
        /* By default, this will call an internal routine that does
           nothing. */

    caster = this_player();
    spell_origin = this_object();
    spell_message = "spell_message";
    spell_damage = "calc_power";
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
    int element, form;

    form = caster->query_skill(spell_form);
    element = caster->query_skill(spell_element);

    if (form < spell_form_needed)
	extra_difficulty += 300;

    if (element < spell_element_needed)
	extra_difficulty += 300;

    return 1;
}

/*
 * Function name:   valid_ingredients
 * Description:     Search for an ingredient or a number of ingredients in
 *                  a player. 
 *		    The should be extended for a search in the
 *		    environment of the player, and/or to a special container
 *		    like a pouch or something that could contain the
 *		    ingredients.
 */
int
valid_ingredients()
{
    int i;
    object ob;

    found_ingredients = ({});

    if (spell_ingredients)
    {
    	if (stringp(spell_ingredients))
            spell_ingredients = ({ spell_ingredients });

        for (i=0; i < sizeof(spell_ingredients); i++)
        {
            if (ob = present(spell_ingredients[i], caster))
                found_ingredients += ({ ob });
        }
	if (sizeof(spell_ingredients) != sizeof(found_ingredients)) 
	    return 0;
    }
    return 1;
}

/*
 * Function name:   area_of_effect
 * Arguments:	    arg : The arguments of this spell.
 * Description:     This is the routine to determine what area of effect
 *		    the spell has depending on the arguments after a spell.
 * Returns:	    The area of effect.
 */
object *
area_of_effect(string str)
{
    object obj;

    obj = present(str, environment(caster));
    if (!obj) 
	return 0;
    return ({ obj });
}

/*
 * Is the object possible to kill?
 */
int 
magic_kill_access(object ob)
{
    return living(ob) && !ob->query_ghost() && ob != this_player();
}

int
magic_attack_access(object ob)
{
    return ob->query_prop(OBJ_M_NO_MAGIC_ATTACK);
}

int
magic_dare_attack(object ob)
{
    return F_DARE_ATTACK(caster, ob);
}

/*
 * Function name:    find_targets
 *
 * Arguments:	     str: The name of the target(s)
 *
 * Description:      Returns a list of the objects to be affected, based upon
 *		     the string passed in. It calls the area_of_effect()
 *		     function to find targets, and removes illegal targets
 *		     if the spell is an attack spell.
 *
 * Returns:	     The targets (object *).
 *
 * Note:	     A 0 returned means that the spell fails.
 */
object *
find_targets(string str)
{
    string str2;
    object *targets;
    int i;

    targets = call_other(spell_origin, spell_area_of_effect, str);

    if (!targets || (sizeof(targets) == 0))
	return notify_fail("No " + str + " here.\n");
 
    if (spell_attack)
    {
	targets = filter(targets, "magic_kill_access", this_object());
	if (!sizeof(targets))
	    return notify_fail("You can not kill that.\n");

	targets = filter(targets, "magic_attack_access", this_object());
	if (!sizeof(targets))
	    return notify_fail("Magic prevents you from attacking.\n");
	
	targets = filter(targets, "magic_dare_attack", this_object());
	if (!sizeof(targets))
	    return notify_fail("Umm... no. You do not dare to attack!\n");

	if ((sizeof(targets) > 1) && !spell_multiple_targets)
	    return notify_fail("Be specific, you can't cast this spell at " +
			       COMPOSITE_LIVE(targets) + " at the same time.\n");
	else if (!sizeof(targets))
	    return notify_fail("You find no such living creature.\n");
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
 * Arguments:	    str  : The string after the spell verb.
 *                         It should be the target for the spell.
 *		    orig : The object which has triggered the spell.
 *			   [default - this_object()].
 *			   Typically a cmdsoul or a spellbook.
 *
 * Returns:	    1 - If the spell accepted the syntax of the spell.
 *		    0 - If not, usually having a notify_fail command.
 /*
varargs public int
cast_spell(string str, object orig)
{
    object room;
    int casting_time, i;
    string no_magic_fail;

    if (!orig)
	spell_origin = this_object();

    /*
    if (!IS_CLONE)
	return CLONE_COPY->cast_spell(str, orig);
    /* We need to use copies. Do we? /*

    caster = this_player();

    room = environment(caster);

    /* This can cause some problem /*
    /* Will do something about it, but what? /*
    no_magic_fail = room->query_prop(ROOM_M_NO_MAGIC);
    if (no_magic_fail)
	return notify_fail(no_magic_fail);

    no_magic_fail = room->query_prop(ROOM_M_NO_MAGIC_ATTACK);
    if (spell_attack && no_magic_fail)
	return notify_fail(no_magic_fail);

    if (!valid_skills() || !valid_ingredients())
    {
	notify_fail("You don't have the right ingredients.\n"); 
	return 0;
    }

/*  We need someting better here, maybe just a new function name
    if (start_spell_fail(str))
	return 0;
/*

    targets = find_targets(str);
    if (!targets || sizeof(targets)==0)
        return 0;

    if (caster->query_mana() < spell_mana_needed)
	return notify_fail("You do not have mana to properly cast the spell.\n");

/*    start_spell_msg(str); /*

    caster->add_mana(-spell_mana_needed/2); /* Olorin thinks this is too much. /*
    casting_time = spell_time + caster->query_prop(LIVE_I_ATTACK_DELAY);

    /* Make sure that npc's knows they are cast upon.
       Also, a shadow might detect it, a reverse-spell for instance.. :-) /*

/*  Where does this function exsist? /Rastlin
    targets->notify_spell_cast(this_object()); /*

    if (spell_duration == 0)
    {
	this_object()->do_instant_spell();
	return 1;
    }

    /* move(caster);    Move the spell to the player. Why? /Rastlin /*

    /* Freeze caster until spell is complete. /*
    /* Hmmm, better wait with this one. /Rastlin
    caster->add_prop(LIVE_O_CONSENTRATES_SPELL, this_object()); /*

    /* Ensure no fighting until spell is complete. /*
    if(spell_attack)
    {
        write("Attack!!!\n");
	caster->add_prop(LIVE_O_SPELL_ATTACK, this_object());
	caster->add_prop(LIVE_I_ATTACK_DELAY, casting_time);
    }
    else
    {
	set_alarm(itof(casting_time), 0.0, "do_spell");
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
 *		    spell failure.
 */
int
calc_result(object attacker)
{
    return attacker->resolve_task(
	spell_difficulty + extra_difficulty,
	({
	    spell_general, attacker->query_skill(spell_general),
	    spell_form, attacker->query_skill(spell_form),
	    spell_element, attacker->query_skill(spell_element)
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
calc_power(object attacker)
{
    int spell_power, result;

    result = calc_result(attacker);

    spell_power =
	attacker->query_stat(SS_WIS) / 10 +
	spell_mana_needed / 5 +
	spell_form_needed / 4 +
	spell_element_needed / 4 +
	spell_difficulty / 10 +
    	2 * ABS(result) / 100;

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
 /*
public void
do_spell()
{
    int res, power;

/*    caster->remove_prop(LIVE_O_CONSENTRATES_SPELL); /*
    caster->remove_prop(LIVE_AS_ATTACK_FUMBLE);

    res = calc_result();

    power = calc_power(res);
		     /* Done before checks for unsuccesful cast,
			after all, there is power in the spell
			even if you fumble with it. /*

    if (res <= 0 || power == 0)
    {
/*	unsuccessful_cast(-res);
/*	return;
    }

    caster->add_mana(-spell_mana_needed/2);

    write("Hej hopp\n");
    if(!spell_effect)
	call_other(spell_origin, spell_effect, targets, power);
    else
	this_object()->do_effect(targets, power);

    switch(spell_duration)
    {
	case 0:
	    dispel_effect();
	    return;
	case -1:
	    return;
	default:
	    set_alarm(itof(spell_duration), 0.0, "dispel_effect");
	    return;
    }
}

/* Function name:   do_instant_spell
 * Description:     Handles the casting of immediate spells. These should be
 *		    rare, but some spells must be able to be cast at once.
 /*
public void
do_instant_spell()
{
    write("Instant\n");
    do_spell(); /* Call the delayed do_spell imidately. /*
}

/*
 * Function name:   spell_message
 * Description:     Give the message of what happens when hit
 *                  by the spell in combat.
 */
public void
spell_message(object attacker, object enemy, int result)
{
}

/*
 * Function name:   spell_damage
 * Description:     Calculate the result of the spell.
 */
public void
spell_damage(object attacker)
{
}

/*
 * Function name:   spell_attack
 * Description:     This is the entry point for a spell attack called from
 *		    the combat object.
 *                  Attacking messages and damage should be handled in
 *		    this function.
 * Arguments:	    me    - The attacking object
 *		    enemy - The attacked object
 */
public void
spell_attack(object me, object enemy)
{
    int damage, result;

    damage = call_other(spell_origin, spell_damage, me);

    result = enemy->hit_me(damage, MAGIC_DT, me, -1);

    write("har2\n");
    call_other(spell_origin, spell_message, me, enemy, result);
    write("har3\n");
    if (enemy->query_hp() <= 0)
        say("You should have died now.\n");
      /*        target->do_die(me);*/

    enemy->remove_prop(LIVE_AS_ATTACK_FUMBLE);
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
 /*
public void 
do_instant_effect(object *targets, int power)
{

}

/*
 * Function name:   dispel_effect
 * Description:     What if someone tries to dispel this spell object,
 *		    For instance, during preparation of a spell, or
 *		    a spell object in a wand.
 /*
int
dispel_effect()
{
/*    remove_call_out("do_spell");
    call_out("remove_object",0); /*
}
*/

