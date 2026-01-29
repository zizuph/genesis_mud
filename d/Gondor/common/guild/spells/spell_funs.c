/*
 * /d/Gondor/common/guild/spells/spell_funs.c
 *
 * Some generic spell functions for ranger spells.
 * These functions are inherited by the ranger spellbook but also
 * by some spell objects used by scrolls which permit casting of
 * spells when a player studies them.
 *
 */
#pragma strict_types

#include "/d/Gondor/defs.h"

#include <composite.h>
#include <language.h>
#include <macros.h>
#include <ss_types.h>

#include "ranger_spell_defs.h"

public void
check_carry()
{
    if (!living(environment()))
        this_object()->remove_object();
}

public int
env_check()
{
    if (!living(environment()))
        return 0;
    if (environment()->query_wiz_level()) 
        return 0;
    return 1;
}

/*************************************************************************
 *
 *	Standard checks before a player is allowed to cast a spell:
 *	   + is the player a ghost?
 *	   + does the player have all magical ingredients?
 *	   + does the player have enough mana?
 *	   - does the player have high enough skills?
 *
 *	And afterwards:
 *	   - remove the magical ingredients
 *	   - subtract the used mana
 *	   - perhaps add a little skill?
 *
 *					(+) handled in check_player().
 */

/*
 * Function name:   check_player
 * Description:     Check if the player matches a few tests. If not, the
 *                  reason is returned.
 * Arguments:       who: The player to check
 *                  ingr: if 0, the no magical ingredients are checked.
 *                        if object or list of objects, check if the player
 *                        posesses all of them.
 *                  mana: Required mana to cast the spell
 * Returns:         0 if the player turns out to be okay, the string
 *		    with the errormessage if something is wrong.
 */
static mixed
check_player(object who, mixed ingr, int mana)
{
    int     i, s,
            is_wiz;

    /*
     * Test for ghosts
     */
    if (who->query_ghost())
        return "You cannot do that in your state.\n";
  
    /* Make sure that wizards can always cast it */
    is_wiz = who->query_wiz_level();
    /* Test if player is a Ranger, and is allowed to use it */
    if (!who->query_company() && !is_wiz) 
    {
        /*
	 * Test for all magic ingredients
	 */
        if (ingr)
	{
	    if (objectp(ingr))
	        ingr = ({ ingr });

	    for (i = 0, s = sizeof(ingr); i < s; i++)
	    {
	        if (!is_wiz && !present(ingr[i], who))
		    return "You feel that you lack something for casting that spell!\n";
	    }
	}
    }
  
    /*
     * Test if enough mana
     */
    if (!is_wiz && (who->query_mana() < mana))
        return "You do not feel strong enough to cast the spell.\n";
  
    /* Passed all tests successfully */
    return 0;
}

/*
 * Function name:   find_ingr
 * Description:	    Finds the ingredients in a person.
 * Arguments:	    ingr: A string or an array of string of ingredients
 *			  It is advisable to give your special ingredients
 *			  a special extra name, like "MY_CARROT", so not
 *			  anyones carrot will be recognised...
 *		    who:  The person to be checked for the objects.
 * Returns:	    An array with the objects found, might be empty.
 */
static object *
find_ingr(mixed ingr, object who)
{
    int     i, s;
    object  ob, 
           *return_arr = ({ });

    if (ingr)
    {
        if (objectp(ingr))
	    ingr = ({ ingr });

	for (i = 0, s = sizeof(ingr); i < s; i++)
	{
	    if (ob = present(ingr[i], who))
	        return_arr += ({ ob });
	}
    }
    return return_arr;
}

/*
 * Function name:   lose_random_ingr
 * Description:	    Destructs one random ingredient with a chance of 1/6th,
 *		    and tells the player that it happened.
 * Arguments:	    ingr: An array of objects of ingredients, as returned
 *			  by find_ingr()
 */
static void
lose_random_ingr(object *ingr)
{
    int ran;
  
    if (sizeof(ingr))
    {
        if (random(6))
	    TP->catch_msg("Luckily you manage to keep all "
				     + "ingredients intact.\n");
	else
	{
            ran = random(sizeof(ingr));
	    TP->catch_msg("Unfortunately you lose the "
	      + ingr[ran]->short() + " in the process.\n");
	    ingr[ran]->remove_object();
	}
    }
}


/*
 * Function name:   remove_ingr
 * Description:	    Destructs all ingredients, and tells the player that
 *		    it happened.
 * Arguments:	    ingr: An array of objects of ingredients, as returned
 *			  by find_ingr()
 */
static void
remove_ingr(object *ingr)
{
    int     s, i;
    string  wrt = "You sacrificed ",
           *str_arr;

    if (!ingr || !(s = sizeof(ingr)))
        return;

    wrt += COMPOSITE_DEAD(ingr) + ".\n";
    this_player()->catch_msg(wrt);

    /* And remove the ingredients */
    for (i = 0; i < s; i++)
        ingr[i]->remove_object();
}

public varargs int
esf(int esf_force, int mana_cost, string spellname, string ingr, string fighting)
{
    tell_room(ENV(TP), QCTNAME(TP)+" fumbles "+TP->query_possessive()+" spell!\n", TP);

    if (strlen(spellname))
        log_file(spellname, ctime(time()) + ": " + TP->query_name() + 
            " fumbles (" + esf_force + ", " + mana_cost + ", " +
            TP->query_skill(SS_ELEMENT_LIFE) + ", " +
            TP->query_skill(SS_FORM_CONJURATION) + ", " +
            TP->query_ranger_rank() + ", " + 
            (strlen(ingr) ? ingr : "") + ", " +
            (strlen(fighting) ? fighting : "") + ").\n");

    if (esf_force < 10) 
    {
        write(BSN("Your skill with this kind of magic fails you, and "
	  + "the spell fizzles off in the wrong direction. And of "
	  + "course, the mana went with it.")); 
	TP->add_mana(-mana_cost);
    }
    else if (esf_force < 20) 
    {
        write(BSN("You lack the necessary skills for this kind of "
	  + "magic. With a shock of weariness you feel the mana waste "
	  + "away into nothingness.")); 
	TP->add_mana(-mana_cost);
	TP->add_fatigue( - (TP->query_max_fatigue() / 2));
    }
    else 
    {
        write(BSN("You botch your spell from lack of skills, or maybe "
	  + "bad luck - you are not quite sure - for all your mana is "
	  + "thrown away into the empty air. You are left with a "
	  + "feeling of worthlessness and weariness.")); 
	TP->add_mana(- (TP->query_mana()));
	TP->add_fatigue(- (TP->query_fatigue()));
    }
    return 1;
}

/*
 * Functions specific to the ranger spellbook.
 * Moved here from ranger_spell_defs.h by Olorin, 18-dec-196
 */
public int
query_rspell_no(string str)
{
    return member_array(LOW(str), RSPELL_CODENAME);
}

public string
query_rspell_name(string str)
{
    int i;

    if (!strlen(str)) 
        return ("No spell");

    i = query_rspell_no(str);
    if (i == -1) 
        return "No spell";
    return RSPELL_NAME[i];
}

public string
query_rspell_codename(string str)
{
    int i;

    i = member_array(LOW(str), RSPELL_NAME);
    if (i == -1) 
        return "No code";
    return RSPELL_CODENAME[i];
}

public int
query_rspell_level(string str)
{
    int i = query_rspell_no(str);
    if ((i < 0) || (i >= sizeof(RSPELL_LEVEL)))
        return 0;
    return RSPELL_LEVEL[i];
}

public int
query_rspell_total_levels()
{
    int     total = 0,
            i = -1,
            s = sizeof(RSPELL_NAME);

    while (++i < s)
        if (this_object()->query_spell_known(RSPELL_CODENAME[i]))
            total += RSPELL_LEVEL[i];

    return total;
}

public int
setup_ranger_spells()
{
    int     i = -1,
            s = sizeof(RSPELL_NAME);
    while (++i < s)
    {
        if (this_object()->query_spell_known(RSPELL_CODENAME[i]))
	    this_object()->add_spell(RSPELL_NAME[i],RSPELL_FUNC(i),RSPELL_DESC[i]);
    }
}
