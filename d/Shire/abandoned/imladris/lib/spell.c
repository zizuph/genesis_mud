//
// This line of spells uses the new spell object used by Rastlin,
// which probably is to be the standard spell object. 
//

#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <comb_mag.h>

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
int query_spell_difficulty() { return spell_difficulty; }
int query_spell_element() { return spell_element; }
int query_spell_element_needed() { return spell_element_needed; }
int query_spell_form() { return spell_form; }
int query_spell_form_needed() { return spell_form_needed; }
int query_spell_duration() { return spell_duration; }
int query_spell_general() { return spell_general; }
object query_spell_effect() { return spell_effect; }
int query_spell_time() { return spell_time; }
int query_spell_attack() { return spell_attack; }
string *query_spell_ingredients() { return spell_ingredients + ({}); }
string query_spell_message() { return spell_message; }
string query_spell_damage() { return spell_damage; }

/*
 * Function name:   create_object
 * Description:     Sets some defaults for the spell, call the user function
 *		    'create_spell'.
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
    object *targets;
    int i;

    targets = call_other(spell_origin, spell_area_of_effect, str);

    if (!targets || (sizeof(targets) == 0))
    {
	write("No " + str + " here.\n");
	return 0;
    }

    if (spell_attack)
    {
	for (i = sizeof(targets) - 1; i >= 0; i--)
        {
	    if (targets[i]->query_prop(OBJ_M_NO_MAGIC_ATTACK) ||
		!kill_access(targets[i]))
		targets = exclude_array(targets, i, i);
            /*
             * Check if we dare attacking the monster(s)!
             */
	    else
	    {
		if (!F_DARE_ATTACK(caster, targets[i]))
		{
		    write("Umm... no, You do not dare to attack.!\n");
		    targets = exclude_array(targets, i, i);
		}
	    }
	}
	if ((sizeof(targets) > 1) && !spell_multiple_targets)
	{
	    str2 = COMPOSITE_LIVE(targets);
	    notify_fail(break_string("Be specific, you can't cast this " +
				     "spell at " + str2 + " at the same time.\n", 70));
	    return 0;
	}
	else if (!sizeof(targets))
	{
	    notify_fail("You find no such living creature.\n");
            return 0;
	}
    }
    return targets;
}


