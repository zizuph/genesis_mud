/*
 *   This file is included in the  file and uses functions and
 *   defines from that file.
 *
 *   The following spells are defined by this object (these definitions
 *   are also used in the /d/Shire/open/SPELLS/<spellname> files):
 *
 *	vanahwesta - Makes all fighting in a room stop for a while.
 *		Needed:
 *		- special mushroom (/d/Shire/common/obj/treemushroom)
 *		- 40 mana.
 *		- (2*INT+WIS)/3 must be above 50
 *		- high enough spellskills, weighted average of
 *		  SPELLCRAFT, _MISC and _DEFENCE is taken. If the
 *		  skills are high, they lower your chance on a random
 *		  failure. The weighted avarage must be above 14.
 *    > Formerly known as 'peace'
 *
 *	lissinen - Tend another player's wounds. The herbs are not needed,
 *	       but then the effect is worse.
 *		Needed:
 *		- 60 mana. (heals 30, w/o herbs 2/3rd of that)
 *		- Huckleberry (/d/Shire/common/obj/huckleberry)
 *  > Formerly known as tend.
 *
 *	engwagalad ----> defined in HERALD_DIR + "cure"
 *		Needed:
 *		- 100 mana.
 *		- Huckleberry (/d/Shire/common/obj/huckleberry) or
 *		  Athelas (/d/Gondor/common/herbs/athelas)
 *    -> Formerly known as 'cure', now used to heal poisons.
 *
 *	mel - Direct holy prayers to Lorien and he will send you
 *		a flower in return.
 *		Needed:
 *		- 5 mana.
 *  -> The adore spell from the Hins.
 *  -> Lorien is the Vala of gardens, so it fits here too :)
 *
 *	silme - Emanate a glowing candle. The candle will last longer
 *	         depending on the success of casting the ROUTINE spell
 *	         Needed:
 *               - Herald of the Valar
 *	         - 7 mana.
 *   .-> Formerly the 'candle' spell.
 *
 *	haetir - See what another player sees.
 *		     - 15 mana
 *		     - parsley (/d/Shire/common/obj/parsley)
 *   -> formerly clairvoyance
 *
 *	ondo - Protect oneself against being hit
 *		- 50 mana
 *		- small rock ("/d/Shire/common/obj/rock")
 *    -> formerly  'protect'
 *
 *
 *      ramar - Allows player to summon a messenger eagle
 *              Needed:
 *              - 20 mana
 *
 *    khil - Know alignment prayer.
 *    Need 30 mana.
 */

/*
 *  Ideas for new spells:
 *
 *  - weapon blessing (only on non-magical bladed weapons)
 *  - armour blessing
 *
 */

/*************************************************************************
 *
 *   Prototypes
 */

#include <tasks.h>
#include "/d/Shire/bits.h"
#include "herald.h"
varargs mixed check_player(object who, mixed ingr, int mana, int wis);
object * find_ingr(mixed ingr, object who);
void lose_random_ingr(object *ingr);

int filter_living(object obj);

/*
 *   SP_xxxx_INGR	An array with ingredient names
 *   SP_xxxx_MANA	Required mana
 *   SP_xxxx_MIN	Weighted avarage ((2*INT+WIS)/3) should be at least
 *			this value.
 *   SP_xxxx_TASK	The difficulty of the task of casting the spell
 *   SP_xxxx_LIST	The resolve_task() list of considered skills.
 */

/*************************************************************************
 *
 *	Standard checks before a player is allowed to cast a spell:
 *
 *	   + is the player a ghost? - We don't care. It's 2.4.6 code! Nevermind it!
 *	   + is the player a follower of the Valar?
 *	   + does the player have all magical ingredients?
 *	   + does the player have enough mana?
 *	   + does the player have high enough stats?
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
 *		    wis:  Compared with (2*INT+WIS)/3. If smaller, then the
 *			  player is not crafted enough to cast the spell.
 * Returns:         0 if the player matches, else the string with the reason
 *		    why the player flunked.
 */
varargs mixed
check_player(object who, mixed ingr, int mana, int wis)
{
    int i, craft;
    object *ob_arr;

    /* Make sure that wizards can always cast it */
    if (who->query_wiz_level())
	return 0;
    //      who->catch_msg("DEBUG: checking magic props.\n");
    /* Is magic allowed in this room? */
    if (environment(who)->query_prop(ROOM_I_NO_MAGIC))
	return "Your prayer cannot be granted here.\n";
    //       who->catch_msg("DEBUG: checking Guild Membership.\n");    
    if(!(IS_MEMBER(who)))
	return "You are not a Herald of the Valar!\n";
    craft = (2*(who->query_stat(SS_INT)) + who->query_stat(SS_WIS)) / 3;
    //      who->catch_msg("DEBUG: checking craft.\n");
    /*
     * Test the player's craft
     */
    if (craft < wis)
	return "You are not wise or intelligent enough to cast the spell.\n";
    //      who->catch_msg("DEBUG: checking ingredients.\n");
    /*
     * Test for all magic ingredients
     */
    if (ingr)
    {
	if (stringp(ingr))
	    ingr = ({ ingr });

	ob_arr = find_ingr(ingr, who);
	if (!ob_arr)
	    ob_arr = ({ });

	if (sizeof(ingr) != sizeof(ob_arr))
	    return "One of the ingredients is missing!\n";
    }
    //      who->catch_msg("DEBUG: checking mana.\n");
    /*
     * Test if enough mana
     */
    if (who->query_mana() < 100)
	return "You do not feel strong enough to make the call.\n";

    /* Passed all tests successfully */
    return 0;
}


/*
 * Function name:   find_ingr
 * Description:	    Find an ingredient or a number of ingredients in
 *		    a player.
 * Arguments:	    ingr: Either a string or an arrays of strings with
 *		    names of the ingredients. It is wise to give a unique
 *		    name to your object, something like "_shire_carrot_",
 *		    in addition to its normal names.
 * Returns:	    An array with found objects.
 */
object *
find_ingr(mixed ingr, object who)
{
    int i;
    object ob, *return_arr;

    return_arr = ({ });

    if (ingr)
    {
	if (objectp(ingr))
	    ingr = ({ ingr });
	//     who->catch_msg("DEBUG: looking for ingredients.\n");
	for (i=0; i < sizeof(ingr); i++)
	{
	    if (ob = present(ingr[i],who))
		return_arr += ({ ob });
	}
    }

    return return_arr;
}



/*
 * Function name:   remove_ingr
 * Description:	    Remove all ingredients, and tell it to the player
 * Arguments:	    ingr: The array with objects of ingredients
 */
void
remove_ingr(object *ingr)
{
    int num_ingr, i, new_size;
    string wrt, *str_arr;

    if (!ingr || !sizeof(ingr))
	return;
    wrt = "You sacrificed ";
    num_ingr = sizeof(ingr);

    if (num_ingr == 1)
	wrt = wrt + (LANG_ADDART(ingr[0]->short()) + ".\n");
    else
    {
	str_arr = map(ingr, "map_short", this_object());
	wrt = wrt + (LANG_ADDART(implode(str_arr[0..(num_ingr-2)], ", "))
	  + " and " +  LANG_ADDART(str_arr[num_ingr-1]) + ".\n");
    }
    this_player()->catch_msg(wrt);

    /* And remove the ingredients */
    for (i=0; i < num_ingr; i++)
    {
	if (!function_exists("restore_heap", ingr[i]))
	    ingr[i]->remove_object();
	else
	{
	    new_size = ingr[i]->num_heap() - 1;
	    ingr[i]->set_heap_size(new_size);
	}
    }
}

string
map_short(object obj)
{
    return obj->short();
}

/*
 * Function name:   lose_random_ingr
 * Description:	    Lose a random ingredient from an array of ingredients
 * Arguments:	    ingr: The array with objects of ingredients
 */
void
lose_random_ingr(object *ingr)
{
    int ran;
    ran = random(sizeof(ingr));
    this_player()->catch_msg("Unfortunately you lose the "
      + ingr[ran]->short()
      + " in the process.\n");
    ingr[ran]->remove_object();
}


/*
 * Function name:   fail_cast
 * Description:     Handles the casting failure. There is a chance of 1/6th
 *		    that some ingredient will be lost at the failure.
 * Arguments:	    who: The player who failed to cast the spell
 *		    ingr_arr: The array with ingredient objects.
 */
void
fail_cast(object who, object *ingr_arr)
{
    //    who->catch_msg("DEBUG: failing cast!.\n");
    this_player()->catch_msg("Your prayer is not heard.\n");
    tell_room(environment(this_player()),QCTNAME(this_player())
      + " makes a prayer which is not heard.\n",this_player());

    /* There's a chance she loses the ingredients as well */
    if (sizeof(ingr_arr))
    {
	if (random(6))
	{
	    this_player()->catch_msg("Luckily you manage to keep all ingredients "
	      + "intact.\n");
	    return;
	}
	lose_random_ingr(ingr_arr);
	//     who->catch_msg("DEBUG: going to lose ingredients!.\n");
	return;
    }
}

/*
 * Function name:   effectstr
 * Description:	    Return a string that expresses the effect of a
 *		    cure or tend spell.
 * Arguments:	    before: hp before the healing
 *		    after: hp after the healing
 * Returns:	    A nice string.
 */
string
effectstr(int before, int after)
{
    int result;

    result = after - before;

    if (result > 250)
	return "very much better";
    if (result > 200)
	return "much better";
    if (result > 150)
	return "better";
    if (result > 100)
	return "somewhat better";
    if (result > 50)
	return "slightly better";
    if (result == 0)
	return "exactly the same as before";
    if (result > -50)
	return "slightly worse";
    if (result > -100)
	return "somewhat worse";
    if (result > -150)
	return "worse";
    if (result > -200)
	return "much worse";
    if (result > -250)
	return "very much worse";
}

int
filter_living(object obj)
{
    return living(obj);
}
