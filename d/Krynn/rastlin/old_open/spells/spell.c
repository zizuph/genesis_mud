/**********************************************************/
/*
 * The spell handleing routines.
 */

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <composite.h>
#include <formulas.h>
#include <tasks.h>
#include <cmdparse.h>

static object *targets,
	      *found_ingredients,
	       spell_effect,
	       spell_origin,
	       caster;

static string *spell_ingredients,
	      spell_area_of_effect,
              spell_message,
              spell_fail_cast,
              spell_damage;

static int spell_attack,
	   spell_time,
	   spell_general,
	   spell_duration,
	   spell_element,
	   spell_element_needed,
	   spell_form,
	   spell_form_needed,
	   spell_difficulty,
           spell_multiple_targets,
           spell_no_targets,
           spell_one_target,
           spell_mana_fail,
	   spell_mana_needed,
           spell_dt,
           spell_protect,
           spell_remove,
           spell_reduce;

static int extra_difficulty;

/*
 * Some set_XXX functions
 */
void set_spell_mana_needed(int i) { spell_mana_needed = i; }
void set_spell_mana_fail(int i) { spell_mana_fail = i; }
void set_spell_difficulty(int i) { spell_difficulty = i; }
void set_spell_element(int i, int j) { spell_element = i; spell_element_needed = j; }
void set_spell_form(int i, int j) { spell_form = i; spell_form_needed = j; }
void set_spell_duration(int i) { spell_duration = i; }
void set_spell_general(int i) { spell_general = i; }
void set_spell_time(int i) { spell_time = i; }
void set_spell_attack() { spell_attack = 1; }
void set_spell_ingredients(string *ingr) { spell_ingredients = ingr; }
void set_spell_allow_multiple_targets() { spell_multiple_targets = 1; }
void set_spell_allow_no_targets() { spell_no_targets = 1; }
void set_spell_dont_allow_one_target() { spell_one_target = 0; }
void set_spell_message(string str) { spell_message = str; }
void set_spell_damage(string str) { spell_damage = str; }
void set_spell_protect() { spell_protect = 1; }
void set_spell_dt(int i) { spell_dt = i; }
void set_spell_fail(string str) { spell_fail_cast = str; }
void set_spell_area_function(string str) { spell_area_of_effect = str; }
void set_spell_reducible(int i) { spell_reduce = i; }
void set_spell_remove(int i) { spell_remove = i; }

int query_spell_mana_needed() { return spell_mana_needed; }
int query_spell_mana_fail() { return spell_mana_fail; }
int query_spell_attack() { return spell_attack; }
int query_spell_duration() { return spell_duration; }
int query_spell_element() { return spell_element; }
int query_spell_element_needed() { return spell_element_needed; }
int query_spell_protect() { return spell_protect; }
int query_spell_dt() { return spell_dt; }
int query_spell_form() { return spell_form; }
object query_caster() { return caster; }
object *query_targets() { return targets; }

mixed
query_all_variables()
{
    return ({caster, spell_element, spell_duration, spell_protect,
             spell_remove, spell_reduce
           });
}

/*
 * Function name:   default_config_spell
 * Description:     Sets some defaults for the spell, call the user function
 *		    'create_spell'.
 */
nomask void
default_config_spell()
{
    targets = ({});

    spell_general = SS_SPELLCRAFT;
	/* By default all spells require spellcraft, not SS_ALCHEMY
	   or SS_HERBALISM. We want this because some 'spells' just
	   require standard skills, for instance an assassin guild,
	   using SS_SNEAK to do the famous 'vanishing' trick, which
	   actually should use the magic system.
           (How come? /Rastlin)
        */

    spell_duration = 0;
	/* By default, the spell should not continue to exist in
	   cyberspace, but be destructed after the spell is cast. */

    spell_ingredients = 0;
	/* By default, no ingredients are needed for the spell.
	   Normally the it will be an array of strings. */

    spell_attack = 0;
        /* By default, this spell wont start a fight. */

    spell_multiple_targets = 0;
    spell_no_targets = 0;
    spell_one_target = 1;
        /* By default, this spell can only be cast on one object/living. */

    spell_area_of_effect = "area_of_effect";
        /* By default, this will call an internal routine that does
           nothing. */

    caster = this_player();
    spell_origin = this_object();
    spell_message = "spell_message";
    spell_damage = "spell_damage";
    spell_fail_cast = "spell_fail_cast";
    spell_protect = 0;
    spell_difficulty = TASK_SIMPLE;
    spell_reduce = 0;
    spell_remove = 0;
}

/*
 * Function name:   valid_skills
 * Description:     This function checks to see that the skills the caster
 *		    has are sufficient to cast the spell. If they are not,
 *		    the spell difficulty is increased one full level for each
 *		    deficient skill.
 */
nomask int
valid_skills()
{
    int element, form;

    form = caster->query_skill(spell_form);
    element = caster->query_skill(spell_element);

    if (form < spell_form_needed)
	extra_difficulty += 300 * (1 - (form/spell_form_needed));

    if (element < spell_element_needed)
	extra_difficulty += 300 * (1 - (element/spell_element_needed));

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
nomask int
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
	if (sizeof(spell_ingredients) != sizeof(found_ingredients)) return 0;
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
nomask object *
area_of_effect(string str)
{
    object *list;

    list = PARSE_THIS(str, "[at] [the] %l");

    if (!list || !sizeof(list)) return 0;
    return list;
}

/*
 * Is the object possible to kill?
 */
int 
kill_access(object ob)
{
    if (!living(ob) || ob->query_ghost() || ob == this_player())
	return 0;
    else
	return 1;
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
 * Note:	     A ({}) returned means that the spell fails.
 */
object *
find_targets(string str)
{
    string str2;
    object *list;
    int i;

    if (str && (str == "me" || str == "myself"))
      return ({ this_player() });

    list = call_other(this_object(), spell_area_of_effect, str);

    if (!list || (sizeof(list) == 0))
    {
	if (!spell_no_targets)
	  write("No " + str + " here.\n");
	return 0;
    }

    if (spell_attack)
    {
	for (i = sizeof(list) - 1; i >= 0; i--)
        {
	    if (list[i]->query_prop(OBJ_M_NO_MAGIC_ATTACK) ||
		!kill_access(list[i]))
		list = exclude_array(list, i, i);
            /*
             * Check if we dare attacking the monster(s)!
             */
	    else
	        if (!F_DARE_ATTACK(caster, list[i]))
	        {
	            write("Umm... no, You do not dare to attack.!\n");
		    list = exclude_array(list, i, i);
	        }
	}
	if ((sizeof(list) > 1) && !spell_multiple_targets)
	{
	    str2 = COMPOSITE_LIVE(list);
	    write(break_string("Be specific, you can't cast this " +
                  "spell at " + str2 + " at the same time.\n", 70));
            return 0;
	}
	else
            if (!sizeof(list)) 
            {
	        write("You find no such living creature.\n");
                return 0;
            }
    }
    return list;
}

/*
 * Function name:   spell_calc_result
 *
 * Description:     Calculates the outcome of a spell. Redefine this if
 *		    you feel that the the resolve_task routine is inapropiate.
 *		    But remember the rules!
 *
 * Returns:	    The result of the spell. Negative or zero indicates
 *		    spell failure.
 */
nomask varargs int
spell_calc_result(object attacker, object enemy)
{
    if (enemy)
        return attacker->resolve_task(
	    spell_difficulty + extra_difficulty,
	    ({ SKILL_AVG, spell_element, spell_form, SKILL_END,
	       spell_general }),
	    enemy, ({ SKILL_AVG, spell_element, spell_form, SKILL_END }));

    return attacker->resolve_task(
           spell_difficulty + extra_difficulty,
           ({ SKILL_AVG, spell_element, spell_form, SKILL_END,
              spell_general }));
}

/*
 * Function name:   spell_calc_power
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
nomask int
spell_calc_power(object attacker, int result)
{
    int spell_power;

    spell_power =
	attacker->query_stat(SS_WIS) / 10 +
	spell_mana_needed / 5 +
	spell_form_needed / 4 +
	spell_element_needed / 4 +
	spell_difficulty / 10 +
    	2 * result / 100;

    if (spell_power > 1000)
	spell_power = 1000;

    return spell_power;
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
 * Description:     Calculate the damage done when hit by
 *                  the spell in combat.
 * Returns:         (int) The damage done.
 */
public int
spell_damage(object attacker)
{
}

/*
 * Function name:   spell_fail_cast
 * Description:     Tell the caster that he/she failed to cast the
 *                  spell.
 */
public void
spell_fail_cast()
{
    write("Sorry, but you are not strong enough for that spell.\n");
}

/*
 * Function name:   stop (Skill TO Property)
 * Description:     Convert a skill to a property
 */
nomask string
stop(int skill)
{
    switch(skill)
    {
	case SS_ELEMENT_FIRE  : return MAGIC_I_RES_FIRE;
        case SS_ELEMENT_AIR   : return MAGIC_I_RES_AIR;
        case SS_ELEMENT_EARTH : return MAGIC_I_RES_EARTH;
        case SS_ELEMENT_WATER : return MAGIC_I_RES_WATER;
        case SS_ELEMENT_LIFE  : return MAGIC_I_RES_LIFE;
        case SS_ELEMENT_DEATH : return MAGIC_I_RES_DEATH;
        default:
            return 0;
    }
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
    int damage, result, power, res;
    object *list;

    result = spell_calc_result(me, enemy);

    if (result < 0)
    {
        call_other(this_object(), spell_fail_cast);
        return 0;
    }

    power = spell_calc_power(me, result);

    damage = call_other(this_object(), spell_damage, me);

    list = filter(enemy->query_magic_effects(), "filter_magic_protect", this_object());

    list->magic_attack(power, this_object(), spell_element);

    res = 100 - enemy->query_magic_res(stop(spell_element));

    result = enemy->hit_me(damage*res/100, spell_dt, me, -1);

    call_other(this_object(), spell_message, me, enemy, result);

    if (enemy->query_hp() <= 0)
        enemy->do_die(me);

    me->remove_prop(LIVE_AS_ATTACK_FUMBLE);
}

int
filter_magic_protect(object obj)
{
    return obj->query_spell_protect();
}
