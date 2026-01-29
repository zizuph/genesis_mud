/*
** /lib/effect.c
**
** This file is intended as the part of the handling
** of magical effects. Read 'man spell-system' for
** further details.
**
**
**
**
**
**
**
*/

#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>

/*
 *  Global variables.
 */

mixed	 effect_reducible;	/* Is effect of reducible type?        */
mixed	 effect_remove; 	/* Remove the covered objects?	       */
int	 effect_power;		/* The effect's power.                 */
mixed	 effect_element;	/* Which element.		       */
mixed	 effect_sec_elem;	/* Secondary element.		       */
int	 effect_duration;	/* The duration of this effect.        */
int	 effect_protect;        /* This effect offers some kind of protection */
object	 effect_ef;		/* Other object is the actual effect.  */

/*
 * Function:	set_ef
 * Arguments:	ef - effect object
 * Description: Sets another object as responsible as the object responsible
 *		for reducing/attacks/etc.
 * Example:	A wall of fire needs two objects, one for each room. One
 *		of these is the actual effect object.
 */
void
set_ef(object ob) { effect_ef = ob; }

/*
 * Function:	query_ef
 * Description: Who is the actual effect object?
 */
object
query_ef() { return effect_ef; }

void
set_protect(int i) { effect_protect = i; }

int
query_spell_protect() { return effect_protect; }

/*
 * Function:	set_reducible
 * Arguments:	int - if it is reducible or not. [vbfc support].
 * Description: This sets weather the effect is reducible or not.
 *		If it is not reducible, then any strong enough attack
 *		will call dispel_effect(). If it is, an attack will
 *		reduce its power by an amount and call dispel_effect()
 *		if it has a power less than or equal to nil.
 */
void
set_reducible(int i)
{
    if (objectp(query_ef()))
	query_ef()->set_reducible(i);
    else
	effect_reducible = i;
}

/*
 * Function:	query_reducible
 * Returns:	If this is a reducible effect or not.
 * Description: See set_reducible.
 */
int
query_reducible()
{
    if (objectp(query_ef()))
	return query_ef()->query_reducible();
    else
	return effect_reducible;
}

/*
 * Function:	set_remove_on_dispel
 * Arguments:	int = 1 : removes the object it is covering on dispel
 *		    = 0 : removes only the effect object.
 */
void
set_remove_on_dispel(int i)
{
    if (objectp(query_ef()))
	query_ef()->set_remove_on_dispel(i);
    else
	effect_remove = i;
}

/*
 * Function:	query_remove_on_dispel
 * Returns:	If the effect should remove the covered object on a
 *		dispel (1) or only the effect object (0).
 */
int
query_remove_on_dispel()
{
    if (objectp(query_ef()))
	return query_ef()->query_remove_on_dispel();
    else
	return effect_remove;
}

/*
 * Function:	set_power
 * Argmunents:	power (int)
 * Description:
 *	Sets the magical power in this magical effect.
 *	The range should be in the range 1,...,100.
 *      But could be more.
 */
void
set_power(int i)
{
    if (objectp(query_ef()))
	query_ef()->set_power(i);
    else
	effect_power = i;
}

/*
 * Function:	query_power
 * Arguments:	-
 * Description:
 *	Returns the magical power in this magical effect.
 */
int
query_power()
{
    if (objectp(query_ef()))
	return query_ef()->query_power();
    else
	return effect_power;
}

/*
 * Function:	reduce_power
 * Arguments:	amount - (int)
 * Description: Reduces the power in this effect.
 *		If power <= 0 then the effect is dispelled
 *		by calling dispel_effect().
 *		If amount is less that zero, then the power
 *		is increased.
 */
void
reduce_power(int amount)
{
    write("le:hej\n");

    if (objectp(query_ef()))
    {
	query_ef()->reduce_power(amount);
	return;
    }

    if (amount <= 0)
    {
	set_power(query_power() - amount);
	return;
    }

    if (!query_reducible() && (amount >= query_power()))
    {
	this_object()->dispel_magic_effect(previous_object());
	return;
    }

    effect_power -= amount;

    if (effect_power <= 0)
	this_object()->dispel_magic_effect(previous_object());
    else
	this_object()->notify_reduced_power(previous_object(), amount);
}

/*
 * Function:	notify_reduced_power
 * Arguments:	attacker (object)   : Object attacking us.
 *		amount	 (int)	    : Amount reduced.
 * Description: Notifies this object that it got hit by anti-magic.
 *		Can be used to display messages when this happens.
 */
public void
notify_reduced_power(object attacker, int amount)
{
    if (objectp(query_ef()))
	query_ef()->notify_reduced_power(attacker, amount);
}

/*
 * Function:	set_element
 * Arguments:	element  - See /sys/spell.h for values.  [vbfc support ]
 *		sec_elem - Secondary element. [optional] [---- '' -----]
 * Description: Sets the primary element for this effect.
 *		The second optional argument is used for resistance
 *		calculations only.
 */
varargs void
set_element(int elem, int sec_elem)
{
    if (objectp(query_ef()))
    {
	query_ef()->set_element(elem, sec_elem);
    }

    effect_element = elem;

    if (sec_elem)
	effect_sec_elem = sec_elem;
}

/*
 * Function:	query_element
 * Returns:	This effect's primary element.
 * Description: Which element this effect consists of.
 *		Value by function support.
 */
int
query_element()
{
    if (objectp(query_ef()))
	return query_ef()->query_element();
    else
	return effect_element;
}

/*
 * Function:	set_secondary_element
 * Arguments:	element - Secondary element.
 * Description: Sets the secondary element of this effect. It is used
 *		for defensive calculations only.
 */
void
set_secondary_element(int i)
{
    if (objectp(query_ef()))
	query_ef()->set_secondary_element(i);
    else
	effect_sec_elem = i;
}

/*
 * Function:	query_secondary_element()
 * Returns:	secondary element.
 * Description: Which secondary element this effect has some resistance
 *		against. Used for defensive calculations only.
 */
int
query_secondary_element()
{
    if (objectp(query_ef()))
	return query_ef()->query_secondary_element();
    else
	return effect_sec_elem;
}

/*
 * Function:	opposing_element
 * Arguments:	elem - Which element to test, default: this effect's element.
 * Returns:	The opposing element of an element.
 * Description: Returns the opposing element of this effect according to
 *		these rules:
 *
 *		Life vs. Death.
 *		Earth vs. Air.
 *		Fire vs. Water.
 */
nomask varargs int
opposing_element(int element)
{
    if (!element)
	element = query_element();

    switch(element)
    {
	case SS_ELEMENT_LIFE : return SS_ELEMENT_DEATH;
	case SS_ELEMENT_DEATH: return SS_ELEMENT_LIFE;
	case SS_ELEMENT_EARTH: return SS_ELEMENT_AIR;
	case SS_ELEMENT_AIR  : return SS_ELEMENT_EARTH;
	case SS_ELEMENT_FIRE : return SS_ELEMENT_WATER;
	case SS_ELEMENT_WATER: return SS_ELEMENT_FIRE;
	default:
	    return SS_ELEMENT_DEATH;
    }
}

/*
 * Function:	set_duration
 * Arguments:	time (int)  : The duration. [vbfc support]
 * Description: How many seconds this effect should last.
 *		If set to -1 the effect lasts until reboot.
 *		If set to -2 the effect lasts forever.
 */
void
set_duration(int i)
{
    if (objectp(query_ef()))
	query_ef()->set_duration(i);
    else
	effect_duration = i;
}

/*
 * Function:	query_duration
 * Returns:	How many seconds this effect should last.
 */
int
query_duration()
{
    if (objectp(query_ef()))
	return query_ef()->query_duration();
    else
	return effect_duration;
}

/*
 * Function:	query_time_left
 * Returns:	How many seconds this effect will last.
 *		-2 if forever.
 *		-1 if until reboot.
 */
int
query_time_left()
{
    mixed alarm;

    if (objectp(query_ef()))
	return query_ef()->query_time_left();

    if (!(alarm = get_alarm(this_object()->query_magic_alarm())))
	return query_duration();
    else
	return ftoi(alarm[2]);
}

/*
 * Function:	magic_attack
 * Arguments:	power	 - (int) The power of the attack
 *		attacker - (object) What object attacks us?
 *		element  - (int) The element of the attack
 * Description:
 *		What to happen when someone attacks us.
 */
mixed
magic_attack(int power, object attacker, int element)
{
    object caster;
    int attack_power;

    if (objectp(query_ef()))
	return query_ef()->magic_attack(power, attacker, element);

    caster = attacker->query_caster(); /* Who's to gain exp? */

    if (element == opposing_element())
	attack_power = 2 * power;
    else if (element == query_element())
	attack_power = - power;
    else if (element == query_secondary_element())
	attack_power = - power / 2;
    else if (element == opposing_element(query_secondary_element()))
	attack_power = power;
    else
	attack_power = 0;

    write(sprintf("LE: power: %O\n ap: %O\n", power, attack_power));

    attacker->reduce_power(random(power));

    if (attack_power == 0) return 0;

    reduce_power(attack_power); /* Negative power will increase the power. */
}
