/*
 *   This file is included in the pipe.c file and uses functions and
 *   defines from that file.
 *
 *   The following spells are defined by this object (these definitions
 *   are also used in the /d/Shire/open/SPELLS/<spellname> files):
 *
 *	peace - Makes all fighting in a room stop for a while.
 *		Needed:
 *		- special mushroom (/d/Shire/common/obj/treemushroom)
 *		- 40 mana.
 *		- (2*INT+WIS)/3 must be above 50
 *		- high enough spellskills, weighted average of
 *		  SPELLCRAFT, _MISC and _DEFENCE is taken. If the
 *		  skills are high, they lower your chance on a random
 *		  failure. The weighted avarage must be above 14.
 *
 *
 *	tend - Tend another player's wounds. The herbs are not needed,
 *	       but then the effect is worse.
 *		Needed:
 *		- 30 mana. (heals 15, w/o herbs 2/3rd of that)
 *		- Huckleberry (/d/Shire/common/obj/huckleberry)
 *
 *
 *	cure - Cure another player's wounds. Twice as good as tend
 *		Needed:
 *		- 60 mana. (heals 30, w/o herbs 2/3rd of that)
 *		- Huckleberry (/d/Shire/common/obj/huckleberry) and
 *		  Pawnrose (/d/Shire/common/obj/pawnrose)
 *
 *
 *	adore - Direct holy prayers to Nob Nar and he will send you
 *		a flower in return.
 *		Needed:
 *		- 5 mana.
 *
 *
 *	candle - Emanate a glowing candle. The candle will last longer
 *	         depending on the success of casting the ROUTINE spell
 *	         Needed:
 *               - true hin Warrior.
 *	         - 7 mana.
 *	         - fire gem (/d/Shire/common/obj/firegem)
 *
 *
 *	clairvoyance - See what another player sees.
 *		     - 15 mana
 *		     - parsley (/d/Shire/common/obj/parsley)
 *
 *
 *	protect - Protect oneself against being hit
 *		- 50 mana
 *		- small rock ("/d/Shire/common/obj/rock") and
 *		  any tooth conquered from an enemy
 *
 *      hex - Add offending description to another player.
 *            Needed:
 *            - 5 mana
 *
 *      infra - Allows player to see living creatures in any dark room
 *              Needed:
 *              - 40? mana
 *              - river weed?
 */

/*
 *  Ideas for new spells:
 *
 *  - Antidote spells ("antidote tricky")
 *  - tempstat spells (eg. "boost con with str"), max 20% or so.
 *  - shield spells
 *  - armour blessing
 *  - presence-check (check neighbouring rooms for livings (use weights).
 *    Warning: this could be hard when on the map...
 *  - Shapechange spell. This is a toughy.
 *  - Summon elemental. If you summon with no, or the wrong element,
 *    the elemental will attack you.
 *
 */

/*************************************************************************
 *
 *   Prototypes
 */

void update_shire_spells();
varargs mixed check_player(object who, mixed ingr, int mana, int wis);
object * find_ingr(mixed ingr, object who);
void lose_random_ingr(object *ingr);
void update_shire_spells();
int filter_living(object obj);

/*
 *   SP_xxxx_INGR	An array with ingredient names
 *   SP_xxxx_MANA	Required mana
 *   SP_xxxx_MIN	Weighted avarage ((2*INT+WIS)/3) should be at least
 *			this value.
 *   SP_xxxx_TASK	The difficulty of the task of casting the spell
 *   SP_xxxx_LIST	The resolve_task() list of considered skills.
 */

#define SP_PEACE_INGR	({ "_stop_spell_mushroom_" })
#define SP_PEACE_MANA	40
#define SP_PEACE_MIN	50
#define SP_PEACE_TASK	TASK_DIFFICULT
#define SP_PEACE_LIST	({ SKILL_WEIGHT, 50, SS_SPELLCRAFT, \
		SKILL_WEIGHT, 90, SKILL_AVG, SS_WIS, SS_INT, SKILL_END, \
		SS_FORM_CONJURATION, SS_ELEMENT_AIR })

#define SP_TEND_INGR	({ "_tend_spell_ingr_"})
#define SP_TEND_MANA	30
#define SP_TEND_MIN	20
#define SP_TEND_TASK	TASK_ROUTINE
#define SP_TEND_LIST	({ SKILL_WEIGHT, 50, SS_SPELLCRAFT, \
		SKILL_WEIGHT, 90, SKILL_AVG, SS_WIS, SS_INT, SKILL_END, \
		SS_FORM_ENCHANTMENT, SS_ELEMENT_LIFE })

#define SP_CURE_INGR	({ "_cure_spell_ingr1_","_cure_spell_ingr2_"})
#define SP_CURE_MANA	60
#define SP_CURE_MIN	30
#define SP_CURE_TASK	TASK_DIFFICULT
#define SP_CURE_LIST	({ SKILL_WEIGHT, 50, SS_SPELLCRAFT, \
		SKILL_WEIGHT, 90, SKILL_AVG, SS_WIS, SS_INT, SKILL_END, \
		SS_FORM_ENCHANTMENT, SS_ELEMENT_LIFE })

#define SP_ADORE_INGR	({ })
#define SP_ADORE_MANA	5
#define SP_ADORE_MIN	0
#define SP_ADORE_TASK	TASK_SIMPLE
#define SP_ADORE_LIST	({ SKILL_WEIGHT, 50, SS_SPELLCRAFT, \
		SKILL_WEIGHT, 90, SKILL_AVG, SS_WIS, SS_INT, SKILL_END, \
		SS_FORM_CONJURATION, SS_ELEMENT_LIFE })

#define SP_CANDLE_INGR	({ })
#define SP_CANDLE_MANA	7
#define SP_CANDLE_MIN	0
#define SP_CANDLE_TASK	TASK_ROUTINE
#define SP_CANDLE_LIST	({ SKILL_WEIGHT, 50, SS_SPELLCRAFT, \
		SKILL_WEIGHT, 90, SKILL_AVG, SS_WIS, SS_INT, SKILL_END, \
		SS_FORM_CONJURATION, SS_ELEMENT_FIRE })

#define SP_CLV_INGR	({ "_clv_spell_ingr_" })
#define SP_CLV_MANA	15
#define SP_CLV_MIN	16
#define SP_CLV_TASK	TASK_ROUTINE
#define SP_CLV_LIST	({ SKILL_WEIGHT, 50, SS_SPELLCRAFT, \
		SKILL_WEIGHT, 90, SKILL_AVG, SS_WIS, SS_INT, SKILL_END, \
		SS_FORM_ENCHANTMENT, SS_ELEMENT_LIFE })

#define SP_PROT_INGR    ({ "_prot_spell_ingr1_", "tooth" })
#define SP_PROT_MANA    50
#define SP_PROT_MIN     30
#define SP_PROT_TASK    TASK_DIFFICULT
#define SP_PROT_LIST    ({ SKILL_WEIGHT, 50, SS_SPELLCRAFT, \
                SKILL_WEIGHT, 90, SKILL_AVG, SS_WIS, SS_INT, SKILL_END, \
                SS_FORM_ABJURATION, SS_ELEMENT_EARTH })

#define SP_HEX_INGR ({ })
#define SP_HEX_MANA 5
#define SP_HEX_MIN 0
#define SP_HEX_TASK TASK_ROUTINE
#define SP_HEX_LIST ({ SKILL_WEIGHT, 50, SS_SPELLCRAFT, \
                SKILL_WEIGHT, 90, SKILL_AVG, SS_WIS, SS_INT, SKILL_END, \
                SS_FORM_ENCHANTMENT, SS_ELEMENT_DEATH })
    /* It is supposed to be a curse, after all. ^^^^^ */

void
update_shire_spells()
{
    int craft, is_wiz;

    /* It doesn't hurt to remove something that doesn't exist */
    remove_spell("peace");
    remove_spell("tend");
    remove_spell("cure");
    remove_spell("adore");
    remove_spell("candle");
    remove_spell("clairvoyance");
    remove_spell("protect");
    remove_spell("hex");

    /*
     *  Not all spells will be available at all times. The average of
     *  2*INT+WIS is taken, and that must be above a certain level.
     *  Note that this way of adding the spells has nothing to do with
     *  how successfull someone will be when casting the spell in question.
     *  Note also that this has nothing to do with how high your rank in
     *  the Hin Warrior Guild is. That only determines how high one can
     *  train her skills.
     *  Of course wizards can always cast everything.
     */
    is_wiz = environment()->query_wiz_level();
    craft = (2*(environment()->query_stat(SS_INT))
	  + environment()->query_stat(SS_WIS)) / 3;

    /* Add all spells */
    if (is_wiz || craft >= SP_ADORE_MIN)
	add_spell("adore", "do_adore_spell", "adore Nob Nar");
    if (is_wiz || craft >= SP_CANDLE_MIN)
	add_spell("candle", "do_candle_spell", "conjure a glowing candle");
    if (is_wiz || craft >= SP_PEACE_MIN)
	add_spell("peace", "do_peace_spell", "make peace");
    if (is_wiz || craft >= SP_TEND_MIN)
  	add_spell("tend", "do_tend_spell", "tend someone");
    if (is_wiz || craft >= SP_CURE_MIN)
  	add_spell("cure", "do_cure_spell", "cure someone");
    if (is_wiz || craft >= SP_CLV_MIN)
  	add_spell("clairvoyance", "do_clv_spell", "clairvoyance someone");
    if (is_wiz || craft >= SP_PROT_MIN)
  	add_spell("protect", "do_protect_spell", "protect yourself");
    if (is_wiz || craft >= SP_HEX_MIN)
  	add_spell("hex", "do_hex_spell", "hex someone else");
}


/*************************************************************************
 *
 *	Standard checks before a player is allowed to cast a spell:
 *
 *	   + is the player a ghost?
 *	   + is the player a true Hin Warrior?
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

    /*
     * Test for ghosts
     */
    if (who->query_ghost())
        return "You cannot do that in your state.\n";

    /* Make sure that wizards can always cast it */
    if (who->query_wiz_level())
	return 0;

    /* Is magic allowed in this room? */
    if (environment(who)->query_prop(ROOM_I_NO_MAGIC))
        return "A strong magical force keeps you from casting the spell.\n";

    /*
     * Test for true Hin Warriors
     */
    if (!is_a_shire(who))
	return "Only true Hin Warriors can cast this spell.\n";

    craft = (2*(who->query_stat(SS_INT)) + who->query_stat(SS_WIS)) / 3;

    /*
     * Test the player's craft
     */
    if (craft < wis)
	return "You are not wise or intelligent enough to cast the spell.\n";

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

    /*
     * Test if enough mana
     */
    if (who->query_mana() < mana)
	return "You do not feel strong enough to cast the spell.\n";

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
        wrt = wrt + (LANG_ADDART(ingr[0]->short()) + ".");
    else
    {
	str_arr = map(ingr, "map_short", this_object());
        wrt = wrt + (LANG_ADDART(implode(str_arr[0..(num_ingr-2)], ", "))
             + " and " +  LANG_ADDART(str_arr[num_ingr-1]) + ".");
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
    this_player()->catch_msg("You fail to cast the spell correctly.\n");
    tell_room(environment(this_player()),QCTNAME(this_player())
            + " fails to cast a spell correctly.\n",this_player());

    /* There's a chance she loses the ingredients as well */
    if (sizeof(ingr_arr))
    {
	if (random(6))
	    this_player()->catch_msg("Luckily you manage to keep all ingredients "
			+ "intact.\n");
	else
	    lose_random_ingr(ingr_arr);
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

    if (result > 40)
	return "very much better";
    if (result > 30)
	return "much better";
    if (result > 20)
	return "better";
    if (result > 10)
	return "somewhat better";
    if (result > 0)
	return "slightly better";
    if (result == 0)
	return "exactly the same as before";
    if (result > -10)
	return "slightly worse";
    if (result > -20)
	return "somewhat worse";
    if (result > -30)
	return "worse";
    if (result > -40)
	return "much worse";
    return "very much worse";
}

/**************************************************************************
 *
 *   The actual spells are defined below this line...
 *
 */


/*
 * Function name:   do_peace_spell
 * Decription:	    Cast the peace fighting spell.
 * Returns:	    1 if spell was cast, 0 or the errorstring otherwise.
 */
mixed
do_peace_spell()
{
    object env, obj, *ingr_arr;
    int success, is_wiz;
    string fail;

    is_wiz = this_player()->query_wiz_level();
    env = environment(this_player());

    if (present("statuette of nob nar", environment(this_player())))
	return "It is unnecessary to cast that spell here.\n";

    if (fail = check_player(this_player(), SP_PEACE_INGR, SP_PEACE_MANA, SP_PEACE_MIN))
	return fail;

    /* Get the object array of all ingredients */
    ingr_arr = find_ingr(SP_PEACE_INGR, this_player());

    /* Let's see how successful she is */
    if (!is_wiz &&
        (success = this_player()->resolve_task(SP_PEACE_TASK,SP_PEACE_LIST)) <= 0)
    {
	fail_cast(this_player(),ingr_arr);
	return 1;
    }

    tell_room(env, QCTNAME(this_player()) + " calls upon Nob Nar to make peace "
	    + "in the room.\n", this_player());
    this_player()->catch_msg("You call upon Nob Nar to make peace in the room.\n");

    if (env->query_prop(ROOM_I_INSIDE))
    {
       tell_room(env, break_string(
          "Outside you hear a deep rumble. "
        + "Suddenly a bolt of lightning cuts through the ceiling and impacts "
        + "on the floor! "
        + "When the light is gone, you see a statuette has appeared on that "
        + "same spot.\n",70));
    }
    else
    {
       tell_room(env, break_string(
          "Clouds gather above you and form a dense, gray blanket. "
        + "Suddenly a bolt of lightning springs from the clouds and impacts "
        + "on the floor! "
        + "When the light is gone, you see a statuette has appeared on that "
        + "same spot.\n",70));
    }

    /* Finally start casting the spell */
    seteuid(getuid());
    obj = clone_object(HIN_DIR + "stop_statue");
    obj->move(env);

    /*
     * The statue stays for a minimum of 30 seconds, and a maximum of
     * 300 seconds.
     */
    if (success < 15)
	success = 15;
    else if (success > 150)
	success = 150;

    if (is_wiz)
        success = 150;
    
    obj->make_peace(2*success);
    
    /* Make her pay for it and remove the ingredients */
    if (!is_wiz)
    {
	this_player()->add_mana(-SP_PEACE_MANA);
	remove_ingr(ingr_arr);
    }

    tell_room(env, QCTNAME(this_player()) + " casts a spell successfully.\n", this_player());
    this_player()->catch_msg("You cast the spell successfully.\n");

    return 1;
}


int
filter_living(object obj)
{
    return living(obj);
}


/*
 * Function name:   do_tend_spell
 * Decription:	    Cast the tend spell.
 * Arguments:	    who: The person to tend
 * Returns:	    1 if spell was cast, 0 or the errorstring otherwise.
 */
mixed
do_tend_spell(string who)
{
    object target, *ingr_arr;
    int i, success, is_wiz, before, after;
    string fail;

    is_wiz = this_player()->query_wiz_level();

    if (!who)
	return "Tend who?\n";

    if (!(target = present(who, environment(this_player()))))
	return "There is no " + who + " here.\n";

    if (!living(target))
	return "You cannot tend " + who + ".\n";

    fail = check_player(this_player(), SP_TEND_INGR, SP_TEND_MANA, SP_TEND_MIN);

    if (fail && fail != "One of the ingredients is missing!\n")
	return fail;

    /* Get the object array of all ingredients */
    ingr_arr = find_ingr(SP_TEND_INGR, this_player());

    /* Let's see how successful she is */
    if (!is_wiz && this_player()->resolve_task(SP_TEND_TASK, SP_TEND_LIST) <= 0)
    {
	fail_cast(this_player(),ingr_arr);
	return 1;
    }

    before = target->query_hp();

    /* According to the healing spell rules */
    /* Also less effect without the proper ingredients */
    if (sizeof(ingr_arr) < sizeof(SP_TEND_INGR))
    {
	this_player()->catch_msg("The effect would have been better with the proper ingredients.\n");
	target->heal_hp(2 * SP_TEND_MANA / 6);
    }
    else
	target->heal_hp(SP_TEND_MANA / 2);

    after = target->query_hp();

    if (target == this_player())
    {
    	this_player()->catch_msg("You magically tend your wounds.\n"
            + "You feel " + effectstr(before, after) + ".\n");
    	tell_room(environment(this_player()), QCTNAME(this_player()) + " magically tends "
	        + this_player()->query_possessive() + " wounds.\n"
         + capitalize(this_player()->query_pronoun()) + " looks "
	 + effectstr(before, after) + ".\n", this_player());
    }
    else
    {
    	this_player()->catch_msg("You magically tend the wounds of " + QCTNAME(target)
          + ".\n"
          + capitalize(target->query_pronoun()) + " looks "
	  + effectstr(before, after) + ".\n");
    	tell_room(environment(this_player()), QCTNAME(this_player()) + " magically tends the wounds "
	  + "of " + QCTNAME(target) + ".\n"
          + capitalize(target->query_pronoun()) + " looks "
	  + effectstr(before, after) + ".\n",
	  ({ target, this_player() }));
    	target->catch_msg(QCTNAME(this_player()) + " magically tends your wounds.\n"
		    + "You feel " + effectstr(before, after) + ".\n");
    }

    /* Remove the ingredients and make her pay for it */
    if (!is_wiz)
    {
	remove_ingr(ingr_arr);
	this_player()->add_mana(-SP_TEND_MANA);
    }
    return 1;
}


/*
 * Function name:   do_cure_spell
 * Decription:	    Cast the cure spell.
 * Arguments:	    who: The person to cure
 * Returns:	    1 if spell was cast, 0 or the errorstring otherwise.
 */
mixed
do_cure_spell(string who)
{
    object target, *ingr_arr;
    int i, success, is_wiz, before, after;
    string fail;

    is_wiz = this_player()->query_wiz_level();

    if (!who)
	return "Cure who?\n";

    if (!(target = present(who, environment(this_player()))))
	return  "There is no " + who + " here.\n";

    if (!living(target))
	return "You cannot cure " + who + ".\n";

    fail = check_player(this_player(), SP_CURE_INGR, SP_CURE_MANA, SP_CURE_MIN);

    if (fail && fail != "One of the ingredients is missing!\n")
	return fail;

    /* Get the object array of all ingredients */
    ingr_arr = find_ingr(SP_CURE_INGR, this_player());

    /* Let's see how successful she is */
    if (!is_wiz && this_player()->resolve_task(SP_CURE_TASK, SP_CURE_LIST) <= 0)
    {
	fail_cast(this_player(),ingr_arr);
	return 1;
    }

    before = target->query_hp();

    /* According to the healing spell rules */
    /* Also less effect without the proper ingredients */
    if (sizeof(ingr_arr) < sizeof(SP_TEND_INGR))
    {
	this_player()->catch_msg("The effect would have been better with the proper ingredients.\n");
	target->heal_hp(2 * SP_CURE_MANA / 6);
    }
    else
	target->heal_hp(SP_CURE_MANA / 2);

    after = target->query_hp();

    if (target == this_player())
    {
    	this_player()->catch_msg("You magically cure your wounds.\n"
            + "You feel " + effectstr(before, after) + ".\n");
    	tell_room(environment(this_player()), QCTNAME(this_player()) + " magically cures "
		+ this_player()->query_possessive()
	 	+ " wounds.\n"
         	+ capitalize(this_player()->query_pronoun()) + " looks "
		+ effectstr(before, after) + ".\n",this_player());
    }
    else
    {
    	this_player()->catch_msg("You magically cure the wounds of " + QCTNAME(target)
	    + ".\n"
            + capitalize(target->query_pronoun()) + " looks "
	    + effectstr(before, after) + ".\n");
    	tell_room(environment(this_player()), QCTNAME(this_player()) + " magically cures the wounds "
	  + "of " + QCTNAME(target) + ".\n"
          + capitalize(target->query_pronoun()) + " looks "
	  + effectstr(before, after) + ".\n",
	  ({ target, this_player() }));
    	target->catch_msg(QCTNAME(this_player()) + " magically cures your wounds.\n"
		    + "You feel " + effectstr(before, after) + ".\n");
    }

    /* Remove the ingredients and make her pay for it */
    if (!is_wiz)
    {
	remove_ingr(ingr_arr);
	this_player()->add_mana(-SP_CURE_MANA);
    }
    return 1;
}


/*
 * Function name:   do_adore_spell
 * Description:	    Cast the adore spell
 * Arguments:       str: better == "nob nar", else error message.
 * Returns:	    1 if spell was cast, 0 or the errorstring otherwise.
 */
mixed
do_adore_spell(string str)
{
    int is_wiz, success;
    object flower, *ingr_arr;
    string fail;

    if (!str && lower_case(str) != "nob nar")
        return "Adore who?\n";

    if (ghost())
	return "You cannot do that in your state!\n";

    is_wiz = this_player()->query_wiz_level();

    /* Check the player for ingredients and mana */
    if (fail = check_player(this_player(), SP_ADORE_INGR, SP_ADORE_MANA, SP_ADORE_MIN))
        return fail;

    /* Get the object array of all ingredients */
    ingr_arr = find_ingr(SP_ADORE_INGR, this_player());

    /* Let's see how successful she is */
    if (!is_wiz &&
        (success = this_player()->resolve_task(SP_ADORE_TASK, SP_ADORE_LIST)) <= 0)
    {
	fail_cast(this_player(),ingr_arr);
        return 1;
    }

    this_player()->catch_msg("You kneel down and sing an ancient song to please Nob Nar.\n"
	+ "When you get up again, you notice that beautiful flower has\n"
	+ "started to grow here, as a sign of Nobs approval of your song.\n");
    tell_room(environment(this_player()), QCTNAME(this_player()) + " kneels down and starts to sing some "
     + "ancient song.\n"
     + "While " + this_player()->query_pronoun() + " is singing, a beautiful flower appears from "
     + "nowhere...\nYou gasp in astonishment!\n", this_player());
#if DEBUG
    this_player()->catch_msg("<Cloned flower>\n");
#endif
    flower = clone_object(MYPATH + "flower");
    flower->move(environment(environment()));

    /* Remove the ingredients and make her pay for it */
    if (!is_wiz)
    {
	remove_ingr(ingr_arr);
	this_player()->add_mana(-SP_ADORE_MANA);
    }
    return 1;
}


/*
 * Function name:   do_candle_spell
 * Description:	    Cast the candle spell
 * Arguments:       str: *shrug*  not used in the code!
 * Returns:	    1 if spell was cast, 0 or the errorstring otherwise.
 */
mixed
do_candle_spell(string str)
{
    object candle, *ingr_arr;
    string fail;
    int is_wiz, success;

    is_wiz = this_player()->query_wiz_level();

    /* Check the player for ingredients and mana */
    if (fail = check_player(this_player(), SP_CANDLE_INGR, SP_CANDLE_MANA, SP_CANDLE_MIN))
        return fail;

    /* Get the object array of all ingredients */
    ingr_arr = find_ingr(SP_CANDLE_INGR, this_player());

    /* Let's see how successful she is */
    if (!is_wiz && (success = this_player()->resolve_task(SP_CANDLE_TASK, SP_CANDLE_LIST)) <= 0)
    {
	fail_cast(this_player(),ingr_arr);
        return 1;
    }

    if (is_wiz)
	success = 250;

    tell_room(environment(this_player()),QCTNAME(this_player()) + " concentrates deeply and conjures "
	    + "a magic candle.\n", this_player());
    this_player()->catch_msg("You concentrate deeply and conjure a magic candle.\n");

    candle = clone_object(STAND_OBJ + "magiccandle");
    /* The candle limits to a minimum of 30 and a maximum of 900 seconds */
    candle->set_max(4*success);
#if DEBUG
    this_player()->catch_msg("<Cloned candle>\n");
#endif
    candle->move(this_player(), 1); /* Move, ignoring the warnings */
    candle->ignite();

    /* Remove the ingredients */

    /* Make her pay for it */
    if (!is_wiz)
    {
	remove_ingr(ingr_arr);
	this_player()->add_mana(-SP_CANDLE_MANA);
    }
    return 1;
}


/*
 * Function name:   do_clairvoyance_spell
 * Decription:	    Cast the clairvoyance spell, which allows a player
 *		    to see what another player sees.
 * Arguments:	    The person to "clairvoyance".
 * Returns:	    1 if spell was cast, 0 or the errorstring otherwise.
 */
mixed
do_clv_spell(string who)
{
    object target, *ingr_arr;
    int i, success, is_wiz;
    string fail;

    is_wiz = this_player()->query_wiz_level();

    if (!who)
	return "Cast clairvoyance on who?\n";

    who = lower_case(who);

    /*
     *  Only known players can be seen.
     *  (Note: find_known_player() is defined in pipe.c)
     */
    if (!(target = find_known_player(who)))
	return "Noone named " + capitalize(who) + " is currently playing.\n";

    if (target->query_wiz_level())
	return "That person is too powerful to cast the spell on.\n";

    if (fail = check_player(this_player(), SP_CLV_INGR, SP_CLV_MANA, SP_CLV_MIN))
	return fail;

    /* Get the object array of all ingredients */
    ingr_arr = find_ingr(SP_CLV_INGR, this_player());

    /* Let's see how successful she is */
    if (!is_wiz && this_player()->resolve_task(SP_CLV_TASK,SP_CLV_LIST) <= 0)
    {
	fail_cast(this_player(),ingr_arr);
	return 1;
    }

    if (target == this_player())
    {
    	this_player()->catch_msg("You open your eyes wide and peer quizzically "
		    + "around.\n");
    	tell_room(environment(this_player()), QCTNAME(this_player()) + " opens "
		+ this_player()->query_possessive() + " eyes wide.\n"
         	+ capitalize(this_player()->query_pronoun()) + " peers around "
		+ "quizzically.\n",this_player());
    }
    else
    {
    	this_player()->catch_msg("You shift your mind into " + capitalize(who)
		    + " and look with " + target->query_possessive()
		    + " eyes.\n"
	            + environment(target)->long()
		    + "You move your attention from " + capitalize(who)
		    + " again.\n");
        
    	tell_room(environment(this_player()), QCTNAME(this_player()) + " gazes into weird  "
		+ "dimensions.\n", ({ this_player() }));
    	target->catch_msg("You feel a weird magical presence inside...\n"
			+ "You sense the aura of "
			+ QNAME(this_player()) + ".\n"
			+ "The sensation goes away again.\n");
    }

    /* Remove the ingredients and make her pay for it */
    if (!is_wiz)
    {
	remove_ingr(ingr_arr);
	this_player()->add_mana(-SP_CLV_MANA);
    }
    return 1;
}


/*
 * Function name:   do_protect_spell
 * Decription:      Cast the protect spell.
 * Arguments:       str: just in case they try to protect someone else.
 * Returns:         1 if spell was cast, 0 or the error string otherwise.
 */
mixed
do_protect_spell(string str)
{
    object tp, *ingr_arr;
    int i, success, is_wiz;
    string fail;

    tp = this_player();
    is_wiz = tp->query_wiz_level();

    if (str != "myself" && str != "me")
        return "You can only protect yourself.\n";

    if (tp->query_protect_spell_time() > 0)
        return "You are still under influence of the last spell.\n";

    if (fail = check_player(tp, SP_PROT_INGR, SP_PROT_MANA, SP_PROT_MIN))
        return fail;

    /* Get the object array of all ingredients */
    ingr_arr = find_ingr(SP_PROT_INGR, tp);

    /* Let's see how successful she is */
    if (!is_wiz && tp->resolve_task(SP_PROT_TASK, SP_PROT_LIST) <= 0)
    {
        fail_cast(tp, ingr_arr);
        return 1;
    }

    /* Cast the spell */
    if (tp->set_protect_spell_time(30 + tp->query_stat(SS_LAYMAN) * 2))
    {
        tp->catch_msg("You cast a spell of protection.\n");
        tell_room(environment(tp), QCTNAME(tp) + " casts a spell and looks "
          + "more protected.\n", ({ tp }));

        /* Remove the ingredients and make her pay for it */
        if (!is_wiz)
        {
            remove_ingr(ingr_arr);
            tp->add_mana(-SP_PROT_MANA);
        }
    }
    else
    {
        return "Something went wrong when casting the spell.\n";
    }
    return 1;
}


/*
 * Function name: do_hex_spell
 * Description:	  Changes a living's short (via a shadow) to a very
 *                unflattering description.
 * Arguments:	  who: the name of the unlucky target
 * Returns:	  
 */
do_hex_spell(string who)
{
    object target, caster, curse, *ingr_arr;
    int i, success, is_wiz;
    string fail;

    caster = TP;

    is_wiz = caster->query_wiz_level();

    if (!who)
	return "Who did you want to hex?\n";

    if (!(target = present(who, environment(caster))))
	return "There is no " + who + " here.\n";

    if (!living(target))
	return "You cannot hex " + who + ".\n";

    if (fail = check_player(caster, SP_HEX_INGR, SP_HEX_MANA, SP_HEX_MIN))
	return fail;

    /* Get the object array of all ingredients */
    ingr_arr = find_ingr(SP_HEX_INGR, caster);

    /* Let's see how successful she is */
    if (is_wiz)
        success = random(20) + 20; /* X 30 secs. == 10 to 20 min. */
    else if ((success = caster->resolve_task(SP_HEX_TASK, SP_HEX_LIST)) <= 0)
    {
        fail_cast(caster, ingr_arr);
        return 1;
    }

    /* Do the spell effect. */
    curse = clone_object("/d/Shire/common/shadow/hex_shadow");
    curse->shadow_me(target);
    curse->destruct_hex_shadow(success * 30);

    /* Tell them about the spell */
    tell_room(environment(caster),
              QCTNAME(caster) + " begins to make strange noises, and wiggles "
              + HIS_HER(caster) + " fingers dangerously.\n",
              caster);
    caster->catch_msg("You place a hex upon " + QTNAME(target) + ".\n");
    target->catch_msg("You feel a malignant aura surround you.\n");
    tell_room(environment(caster),
              QCTNAME(caster) + " places a hex upon " + QTNAME(target) + "!\n",
              ({ caster, target }));

    /* Remove the ingredients and make them pay for it */
    if (!is_wiz)
    {
	remove_ingr(ingr_arr);
	caster->add_mana(-SP_HEX_MANA);
    }
    return 1;
}
