/*
 *   This file is included in the pipe.c file and uses functions and
 *   defines from that file.
 *
 *   The following spells are defined by this object (these definitions
 *   are also used in the /d/Shire/open/SPELLS/<spellname> files):
 *
 *	peace		Makes all fighting in a room stop for a while.
 *			Needed:
 *			- special mushroom.
 *			- 40 mana.
 *			- (2*INT+WIS)/3 must be above 50
 *			- high enough spellskills, weighted average of
 *			  SPELLCRAFT, _MISC and _DEFENCE is taken. If the
 *			  skills are high, they lower your chance on a random
 *			  failure. The weighted avarage must be above 14.
 *
 *
 *	hide		Become untouchable for the environment.
 *			Needed:
 *			- 10 mana.
 *			- SPELLCRAFT skill must be above 5.
 *
 *
 *	tend		Tend another player's wounds.
 *			Needed:
 *			- 30 mana. (heals 15)
 *			- One magical ingredient
 *
 *
 *	cure		Cure another player's wounds. Twice as good as tend
 *			Needed:
 *			- 60 mana. (heals 30)
 *			- Two magical ingredients
 *
 *
 *	adore		Direct holy prayers to Nob Nar and he will send you
 *			a flower in return.
 *			Needed:
 *			- 5 mana.
 *
 *
 *	candle		Emanate a glowing candle. The candle will last longer
 *			depending on the success of casting the ROUTINE spell
 *			Needed:
 *			- true hin Warrior.
 *			- 5 mana.
 *			- fire gem (/d/Shire/common/obj/firegem)
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
 */
#define SP_PEACE_INGR	({ "_stop_spell_mushroom_" })
#define SP_PEACE_MANA	40
#define SP_PEACE_MIN	50

#define SP_HIDE_INGR	({ })
#define SP_HIDE_MANA	15
#define SP_HIDE_MIN	10

#define SP_TEND_INGR	({ "_tend_spell_ingr_"})
#define SP_TEND_MANA	30
#define SP_TEND_MIN	20

#define SP_CURE_INGR	({ "_cure_spell_ingr1_","_cure_spell_ingr2_"})
#define SP_CURE_MANA	60
#define SP_CURE_MIN	30

#define SP_ADORE_INGR	({ })
#define SP_ADORE_MANA	5
#define SP_ADORE_MIN	10

#define SP_CANDLE_INGR	({ })
#define SP_CANDLE_MANA	7
#define SP_CANDLE_MIN	8


void
update_shire_spells()
{
    int craft, is_wiz;

    /* It doesn't hurt to remove something that doesn't exist */
    remove_spell("peace");
    remove_spell("tend");
    remove_spell("cure");
/*
 *  remove_spell("hide!");
 */
    remove_spell("adore");
    remove_spell("candle");

    /*
     *  Not all spells will be available at all times. The average of
     *  2*INT+WIS is taken, and that must be above a certain level.
     *  Note that this way of adding the spells has nothing to do with
     *  how successfull someone will be when casting the spell in question.
     *  Of course wizards can always cast everything.
     */
    craft = environment()->query_stat(SS_LAYMAN);
    is_wiz = environment()->query_wiz_level();

    add_spell("adore", "do_adore_spell", "adore Nob Nar");
/*
    add_spell("candle", "do_candle_spell", "conjure a glowing candle");
*/
    /* Add all spells */
    if (is_wiz || craft >= SP_PEACE_MIN)
	add_spell("peace", "do_peace_spell", "make peace");
    if (is_wiz || craft >= SP_TEND_MIN)
  	add_spell("tend", "do_tend_spell", "tend someone");
    if (is_wiz || craft >= SP_CURE_MIN)
  	add_spell("cure", "do_cure_spell", "cure someone");
/*
 *  if (is_wiz || craft >= SP_HIDE_MIN)
 *	add_spell("hide!", "do_hide_spell", "hide myself");
 */
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
    int s, i;
    string wrt, *str_arr;

    if (!ingr || !sizeof(ingr))
        return;

    wrt = "You sacrificed ";
    s = sizeof(ingr);

    if (s == 1)
        wrt += LANG_ADDART(ingr[0]) + ".";
    else
    {
	str_arr = map(ingr, "map_short", this_object());
        wrt += LANG_ADDART(implode(str_arr[0..(s-2)], ", "))
             + " and " +  LANG_ADDART(str_arr[s-1]) + ".";
    }
    this_player()->catch_msg(wrt);

    /* And remove the ingredients */
    for (i=0; i < s; i++)
	ingr[i]->remove_object();
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
    object tp;

    tp = this_player();
    tp->catch_msg("You fail to cast the spell correctly.\n");
    tell_room(environment(tp),QCTNAME(tp) + " fails to cast a spell "
	    + "correctly.\n",tp);

    /* There's a chance she loses the ingredients as well */
    if (sizeof(ingr_arr))
    {
	if (random(6))
	    tp->catch_msg("Luckily you manage to keep all ingredients "
			+ "intact.\n");
	else
	    lose_random_ingr(ingr_arr);
    }
}

/**************************************************************************
 *
 *   The actual spells are defined below this line...
 *
 */


/*
 * Function name:   do_peace_spell
 * Decription:	    Cast the peace fighting spell.
 * Returns:	    1 if spell was cast, 0 otherwise.
 */
mixed
do_peace_spell()
{
    object tp, env, obj, *ingr_arr;
    int success, is_wiz;
    string fail;

    tp = this_player();
    is_wiz = tp->query_wiz_level();
    env = environment(tp);

    if (present("statuette of nob nar", environment(tp)))
	return "It is unnecessary to cast that spell here.\n";

    if (fail = check_player(tp, SP_PEACE_INGR, SP_PEACE_MANA, SP_PEACE_MIN))
	return fail;

    /* Get the object array of all ingredients */
    ingr_arr = find_ingr(SP_PEACE_INGR, tp);

    /* Let's see how successful she is */
    if (!is_wiz && (success = tp->resolve_task(TASK_DIFFICULT,
              ({ SKILL_WEIGHT, 50, SS_SPELLCRAFT,
               SKILL_WEIGHT, 90, SKILL_AVG, SS_WIS, SS_INT, SKILL_END,
               SS_FORM_CONJURATION,SS_ELEMENT_AIR}))) <= 0)
    {
	fail_cast(tp,ingr_arr);
        /* Make her pay for it anyway */
        if (!is_wiz)
	    tp->add_mana(-SP_PEACE_MANA);
	return 1;
    }

    tell_room(env, QCTNAME(tp) + " calls upon Nob Nar to make peace "
	    + "in the room.\n", tp);
    tp->catch_msg("You call upon Nob Nar to make peace in the room.\n");

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
    obj = clone_object(STAND_DIR + "stop_statue");
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
	tp->add_mana(-SP_PEACE_MANA);
	remove_ingr(ingr_arr);
    }

    tell_room(env, QCTNAME(tp) + " casts a spell successfully.\n", tp);
    tp->catch_msg("You cast the spell successfully.\n");

    return 1;
}


int
filter_living(object obj)
{
    return living(obj);
}


/*
 * Function name:   do_hide_spell
 * Description:	    Cast the hide spell
 * Returns:	    1 if spell was cast, 0 otherwise.
 */
mixed
do_hide_spell(string str)
{
    object tp, candle, hiding, att, *ingr_arr;
    int is_wiz, success;
    string fail, enemy;

    if (str)
	return "Just type \"hide\".\n";

    if (ghost())
	return "You cannot do that in your state!\n";

    tp = this_player();
    is_wiz = tp->query_wiz_level();

    /* Check the player for ingredients and mana */
    if (fail = check_player(tp, SP_HIDE_INGR, SP_HIDE_MANA, SP_HIDE_MIN))
        return fail;

    /* Get the object array of all ingredients */
    ingr_arr = find_ingr(SP_HIDE_INGR, tp);

    /* Let's see how successful she is */
    if (!is_wiz && tp->resolve_task(TASK_SIMPLE, ({ SS_DEX, SS_HIDE })) <= 0)
    {
	fail_cast(tp,ingr_arr);
        /* Remove the ingredients and make her pay for it. */
        if (!is_wiz)
	    tp->add_mana(-SP_HIDE_MANA);
        return 1;
    }

    tell_room(environment(tp), QCTNAME(tp) + " blends in with "
	    + tp->query_possessive() + " environment and vanishes!\n", tp);
    tp->catch_msg("You blend in with your environment and vanish "
	+ "completely!\n");
#if DEBUG
    tp->catch_msg("<Cloned hidingplace>\n");
#endif
    hiding = clone_object(MYPATH + "hp");
    hiding->set_insider(tp);
    hiding->move(environment(tp));

    /* Make sure that this isn't used as an 'instant-peace-maker' */
    if (att = tp->query_attack())
    {
	enemy = att->query_real_name();
	hiding->set_attacker(enemy);
    }
    tp->move(hiding, 1); /* Move owner inside without checks */

    /* Remove the ingredients and make her pay for it. */
    if (!is_wiz)
    {
	remove_ingr(ingr_arr);
	tp->add_mana(-SP_HIDE_MANA);
    }
    return 1;
}


/*
 * Function name:   do_tend_spell
 * Decription:	    Cast the tend spell.
 * Arguments:	    The person to tend
 * Returns:	    1 if spell was cast, 0 otherwise.
 */
mixed
do_tend_spell(string who)
{
    object tp, target, *ingr_arr;
    int i, success, is_wiz;
    string fail;

    tp = this_player();
    is_wiz = tp->query_wiz_level();

    if (!who)
	return "Tend who?\n";

    if (!(target = present(who, environment(tp))))
	return "There is no " + who + " here.\n";

    if (!living(target))
	return "You cannot tend " + who + ".\n";

    if (fail = check_player(tp, SP_TEND_INGR, SP_TEND_MANA, SP_TEND_MIN))
	return fail;

    /* Get the object array of all ingredients */
    ingr_arr = find_ingr(SP_TEND_INGR, tp);

    /* Let's see how successful she is */
    if (!is_wiz && tp->resolve_task(TASK_ROUTINE,
            ({ SKILL_WEIGHT, 50, SS_SPELLCRAFT,
               SKILL_WEIGHT, 90, SKILL_AVG, SS_WIS, SS_INT, SKILL_END,
               SS_FORM_ENCHANTMENT,SS_ELEMENT_LIFE })) <= 0)
    {
	fail_cast(tp,ingr_arr);
        /* Remove the ingredients and make her pay for it */
        if (!is_wiz)
	    tp->add_mana(-SP_TEND_MANA);
	return 1;
    }

    if (target == tp)
    {
    	tp->catch_msg("You magically tend your wounds.\n"
            + "You feel somewhat better.\n");
    	tell_room(environment(tp), QCTNAME(tp) + " magically tends "
	        + tp->query_possessive() + " wounds.\n"
         + capitalize(tp->query_pronoun()) + " looks somewhat better.\n", tp);
    }
    else
    {
    	tp->catch_msg("You magically tend the wounds of " + QCTNAME(target)
          + ".\n"
          + capitalize(target->query_pronoun()) + " looks somewhat better.\n");
    	tell_room(environment(tp), QCTNAME(tp) + " magically tends the wounds "
	  + "of " + QCTNAME(target) + ".\n"
          + capitalize(target->query_pronoun()) + " looks somewhat better.\n",
	  ({ target, tp }));
    	target->catch_msg(QCTNAME(tp) + " magically tends your wounds.\n"
		    + "You feel somewhat better.\n");
    }

    /* According to the healing spell rules */
    target->heal_hp(SP_TEND_MANA/2);

    /* Remove the ingredients and make her pay for it */
    if (!is_wiz)
    {
	remove_ingr(ingr_arr);
	tp->add_mana(-SP_TEND_MANA);
    }
    return 1;
}


/*
 * Function name:   do_cure_spell
 * Decription:	    Cast the cure spell.
 * Arguments:	    The person to cure
 * Returns:	    1 if spell was cast, 0 otherwise.
 */
mixed
do_cure_spell(string who)
{
    object tp, target, *ingr_arr;
    int i, success, is_wiz;
    string fail;

    tp = this_player();
    is_wiz = tp->query_wiz_level();

    if (!who)
	return "Cure who?\n";

    if (!(target = present(who, environment(tp))))
	return  "There is no " + who + " here.\n";

    if (!living(target))
	return "You cannot cure " + who + ".\n";

    if (fail = check_player(tp, SP_CURE_INGR, SP_CURE_MANA, SP_CURE_MIN))
	return fail;

    /* Get the object array of all ingredients */
    ingr_arr = find_ingr(SP_CURE_INGR, tp);

    /* Let's see how successful she is */
    if (!is_wiz && tp->resolve_task(TASK_DIFFICULT,
            ({ SKILL_WEIGHT, 50, SS_SPELLCRAFT,
               SKILL_WEIGHT, 90, SKILL_AVG, SS_WIS, SS_INT, SKILL_END,
               SS_FORM_ENCHANTMENT,SS_ELEMENT_LIFE })) <= 0)
    {
	fail_cast(tp,ingr_arr);
        /* Remove the ingredients and make her pay for it */
        if (!is_wiz)
	    tp->add_mana(-SP_CURE_MANA);
	return 1;
    }

    if (target == tp)
    {
    	tp->catch_msg("You magically cure your wounds.\n"
            + "You feel much better.\n");
    	tell_room(environment(tp), QCTNAME(tp) + " magically cures "
		+ tp->query_possessive()
	 	+ " wounds.\n"
         	+ capitalize(tp->query_pronoun()) + " looks much better.\n",tp);
    }
    else
    {
    	tp->catch_msg("You magically cure the wounds of " + QCTNAME(target)
	    + ".\n"
            + capitalize(target->query_pronoun()) + " looks much better.\n");
    	tell_room(environment(tp), QCTNAME(tp) + " magically cures the wounds "
	  + "of " + QCTNAME(target) + ".\n"
          + capitalize(target->query_pronoun()) + " looks much better.\n",
	  ({ target, tp }));
    	target->catch_msg(QCTNAME(tp) + " magically cures your wounds.\n"
		    + "You feel much better.\n");
    }

    /* According to the healing spell rules */
    target->heal_hp(SP_CURE_MANA/2);

    /* Remove the ingredients and make her pay for it */
    if (!is_wiz)
    {
	remove_ingr(ingr_arr);
	tp->add_mana(-SP_CURE_MANA);
    }
    return 1;
}


/*
 * Function name:   do_adore_spell
 * Description:	    Cast the adore spell
 * Returns:	    1 if spell was cast, 0 otherwise.
 */
mixed
do_adore_spell(string str)
{
    int is_wiz, success;
    object flower, tp, *ingr_arr;
    string fail;

    if (!str && lower_case(str) != "nob nar")
        return "Adore who?\n";

    if (ghost())
	return "You cannot do that in your state!\n";

    tp = this_player();
    is_wiz = tp->query_wiz_level();

    /* Check the player for ingredients and mana */
    if (fail = check_player(tp, SP_ADORE_INGR, SP_ADORE_MANA, SP_ADORE_MIN))
        return fail;

    /* Get the object array of all ingredients */
    ingr_arr = find_ingr(SP_ADORE_INGR, tp);

    /* Let's see how successful she is */
    if (!is_wiz && (success = tp->resolve_task(TASK_SIMPLE,
              ({ SKILL_WEIGHT, 50, SS_SPELLCRAFT,
               SKILL_WEIGHT, 90, SKILL_AVG, SS_WIS, SS_INT, SKILL_END,
               SS_FORM_CONJURATION,SS_ELEMENT_LIFE}))) <= 0)
    {
	fail_cast(tp,ingr_arr);
        /* Make her pay for it */
        if (!is_wiz)
	    tp->add_mana(-SP_ADORE_MANA);
        return 1;
    }

    tp->catch_msg("You kneel down and sing an ancient song to please Nob Nar.\n"
	+ "When you get up again, you notice that beautiful flower has\n"
	+ "started to grow here, as a sign of Nobs approval of your song.\n");
    tell_room(environment(tp), QCTNAME(tp) + " kneels down and starts to "
     + "sing some ancient song.\n"
     + "While " + this_player()->query_pronoun() + " is singing, a beautiful flower appears from "
     + "nowhere...\nYou gasp in astonishment!\n", tp);
#if DEBUG
    tp->catch_msg("<Cloned flower>\n");
#endif
    flower = clone_object(MYPATH + "flower");
    flower->move(environment(tp));

    /* Remove the ingredients and make her pay for it */
    if (!is_wiz)
    {
	remove_ingr(ingr_arr);
	tp->add_mana(-SP_ADORE_MANA);
    }
    return 1;
}


/*
 * Function name:   do_candle_spell
 * Description:	    Cast the candle spell
 * Returns:	    1 if spell was cast, 0 otherwise.
 */
mixed
do_candle_spell(string str)
{
    object tp, candle, *ingr_arr;
    string fail;
    int is_wiz, success;

    tp = this_player();
    is_wiz = tp->query_wiz_level();

    /* Check the player for ingredients and mana */
    if (fail = check_player(tp, SP_CANDLE_INGR, SP_CANDLE_MANA, SP_CANDLE_MIN))
        return fail;

    /* Get the object array of all ingredients */
    ingr_arr = find_ingr(SP_CANDLE_INGR, tp);

    /* Let's see how successful she is */
    if (!is_wiz && (success = tp->resolve_task(TASK_ROUTINE,
              ({ SKILL_WEIGHT, 50, SS_SPELLCRAFT,
               SKILL_WEIGHT, 90, SKILL_AVG, SS_WIS, SS_INT, SKILL_END,
               SS_FORM_CONJURATION,SS_ELEMENT_FIRE}))) <= 0)
    {
	fail_cast(tp,ingr_arr);
        /* Make her pay for it */
        if (!is_wiz)
	    tp->add_mana(-SP_CANDLE_MANA);
	return 1;
    }

    if (is_wiz)
	success = 250;

    tell_room(environment(tp),QCTNAME(tp) + " concentrates deeply and conjures "
	    + "a magic candle.\n", tp);
    tp->catch_msg("You concentrate deeply and conjure a magic candle.\n");

    candle = clone_object(STAND_OBJ + "magiccandle");
    /* The candle limits to a minimum of 30 and a maximum of 900 seconds */
    candle->set_max(4*success);
#if DEBUG
    tp->catch_msg("<Cloned candle>\n");
#endif
    candle->move(tp, 1); /* Move, ignoring the warnings */
    candle->ignite();

    /* Remove the ingredients */

    /* Make her pay for it */
    if (!is_wiz)
    {
	remove_ingr(ingr_arr);
	tp->add_mana(-SP_CANDLE_MANA);
    }
    return 1;
}


/*
 * Function name:   
 * Description:	    
 * Arguments:	    
 * Returns:	    
 */
