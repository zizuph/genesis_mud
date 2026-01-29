/*
 * - /d/Avenir/union/lib/ability.h
 *
 * Contains the code for:
 *
 * Mark - mark knives and daggers as your own
 * Dget - pick up your marked daggers from somewhere
 * Stop - preventative to stop people from being able to sway in combat
 * Sway - The special ability 'sway'
 * Compare - Compare different Union virtues with another member
 * Uadverbs - List and query the list of Union adverbs.
 * Flick - The flick command.
 * Revisions:
 * 	Zizuph, June 2021: Various fixes for flick.
 *  Lilith,  May 2022: removed combat check for unis and uapp,
 *                     updated virtue text.
 *
 */
#define SD_COMPARE_PURITY   ({ \
    "about as pure as",		"a bit more pure than",		\
    "more pure than",		"much more pure than"		\
})
#define SD_COMPARE_GRACE    ({ \
    "about as graceful as",	"a bit more graceful than",	\
    "more graceful than",	"much more graceful than"	\
})
#define SD_COMPARE_DIGNITY  ({ \
    "about as dignified as",	"a bit more dignified than",	\
    "in possession of greater dignity than",			\
    "in possession of much greater dignity than"		\
})
#define SD_COMPARE_PRIDE    ({ \
    "about as proud as",	"a bit more proud then",	\
    "more proud than",		"much more proud than"		\
})

private static mixed compare_strings = ({
    SD_COMPARE_DIGNITY, SD_COMPARE_PRIDE,
    SD_COMPARE_GRACE,   SD_COMPARE_PURITY
});
private static string *virtue_names = ({
    "dignity", "pride", "grace", "purity"
});
private static int *virtue_skill = ({
    US_DIGNITY, US_PRIDE, US_GRACE, US_PURITY
});

#define UNION_S_MARKED	"_union_s_knife_marked"

public int
marking_filter(object ob)
{
    if (ob->query_wt() != W_KNIFE)
	return 0;

    return (ob->query_prop(UNION_S_MARKED) == TP->query_real_name());
}

public int
dget(string str)
{
    int found;

//    if (!CAN_SEE_IN_ROOM(TP))
//	return NF("You cannot see here.\n");

    if (TP->query_ghost())
    return NF("You cannot pick things up.\n");

    foreach(object place : ({ ENV(TP) }) + all_inventory(ENV(TP)))
    {
	object *stuff;

	if ((place != ENV(TP)) && !IS_CORPSE_OBJECT(place))
	    continue;

	stuff = filter(all_inventory(place), marking_filter);

	if (!sizeof(stuff))
	    continue;

	/* Attempt to move items. */
	stuff = filter(stuff, not @ &->move(TP));

	/* See if we moved anything. */
	if (!sizeof(stuff))
	    continue;

	found++;

	write("You recover " + COMPOSITE_DEAD(stuff) +
	  " from " + (place == ENV(TP) ? "the ground" :
	    LANG_THESHORT(place)) + ".\n");
    }

    if (!found)
    {
	write("You have no marked knives in the immediate area "+
	  "nor in any nearby corpses.\n");
    }
    else
    {
	say(QCTNAME(TP) + " recovers some items from the "+
	  "nearby area.\n");
    }

    return 1;
}

public int
mark(string str)
{
    object *stuff;

    if (!strlen(str))
	return NF("Mark which knife as your own?\n");

    if (str == "all")
	stuff = filter(all_inventory(TP), is_knife);
    else
	stuff = filter(FIND_STR_IN_OBJECT(str, TP), is_knife);

    if (!sizeof(stuff))
	return NF("You marked nothing.\n");

#if 0
    Dosen't quite work...
    for(i=0;i<sizeof(stuff);i++)
	if (!stuff[i]->query_prop(UNION_S_MARKED))
	    stuff[i]->set_long(stuff[i]->query_long() +
	      "@@marked_desc:" + file_name(TO) + "|" + file_name(stuff[i]) + "@@");
#endif

    stuff->add_prop(UNION_S_MARKED, TP->query_real_name());
    write("You mark "+ COMPOSITE_DEAD(stuff) +" as being your own.\n");

    return 1;
}

#if 0
public string
marked_desc(string what)
{
    string nm = find_object(what)->query_prop(UNION_S_MARKED);
    // That find_object stuff is a hassle, but it seems
    // previous_object() and calling_object() won't work

    if (!nm || !strlen(nm))
	return "";

    return "Lightly etched within the surface of the blade is the "
    + "name " + CAP(nm) + ".\n";
}
#endif

public varargs string
virtue_desc(object who, int which, object for_obj)
{
    string *good = ({}), *bad = ({}), *ret = ({}), me;

    if (!objectp(who))
	who = TP;

    if (objectp(for_obj) && (for_obj != who))
	me = who->query_The_name(for_obj) + " is ";
    else
	me = "You are ";

    if (!which || which == US_DIGNITY)
    {
	switch(who->query_union_virtue(US_DIGNITY))
	{
	case US_VIRTUE_MIN .. -1000:
	    bad += ({ "disappointingly undignified" });
	    break;
	case -999 .. -700:
	    bad += ({ "very undignified" });
	    break;
	case -699 .. -500:
	    bad += ({ "very undignified" });
	    break;
	case -499 .. -300:
	    bad += ({ "very undignified" });
	    break;
	case -299 .. -100:
	    bad += ({ "rather undignified" });
	    break;
	case -99 .. -40:
	    bad += ({ "somewhat undignified" });
	    break;
	case -39 .. -10:
	    bad += ({ "slightly undignified" });
	    break;
	case -9 .. 10:
	    bad += ({ "without dignity" });
	    break;
	case 11 .. 40:
	    good += ({ "slightly dignified" });
	    break;
	case 41 .. 100:
	    good += ({ "somewhat dignified" });
	    break;
	case 101 .. 300:
	    good += ({ "dignified" });
	    break;
	case 301 .. 500:
	    good += ({ "quite dignified" });
	    break;
	case 501 .. 700:
	    good += ({ "very dignified" });
	    break;
	case 701 .. 1000:
	    good += ({ "extremely dignified" });
	    break;
	case 1001 .. US_VIRTUE_MAX:
	    good += ({ "the paradigm of dignity" });
	    break;
	default:
	    good += ({ "in possession of a strange dignity" });
	    break;
	}
    }

    if (!which || which == US_PURITY)
    {
	switch(who->query_union_virtue(US_PURITY))
	{
	case US_VIRTUE_MIN .. -1000:
	    bad += ({ "disgusting to behold" });
	    break;
	case -999 .. -700:
	    bad += ({ "disgusting to behold" });
	    break;
	case -699 .. -500:
	    bad += ({ "filthy" });
	    break;
	case -499 .. -300:
	    bad += ({ "dirty" });
	    break;
	case -299 .. -100:
	    bad += ({ "impure" });
	    break;
	case -99 .. -40:
	    bad += ({ "very unclean" });
	    break;
	case -39 .. -10:
	    bad += ({ "unclean" });
	    break;
	case -9 .. 10:
	    bad += ({ "without purity" });
	    break;
	case 11 .. 40:
	    good += ({ "clean" });
	    break;
	case 41 .. 100:
	    good += ({ "very clean" });
	    break;
	case 101 .. 300:
	    good += ({ "approaching purity" });
	    break;
	case 301 .. 500:
	    good += ({ "mostly pure" });
	    break;
	case 501 .. 700:
	    good += ({ "pure" });
	    break;
	case 701 .. 1000:
	    good += ({ "extremely pure" });
	    break;
	case 1001 .. US_VIRTUE_MAX:
	    good += ({ "the epitome of purity" });
	    break;
	default:
	    good += ({ "a strange sort of purity" });
	    break;
	}
    }

    if (!which || which == US_PRIDE)
    {
	switch(who->query_union_virtue(US_PRIDE))
	{
	case US_VIRTUE_MIN .. -1000:
	    bad += ({ "cowardly" });
	    break;
	case -999 .. -700:
	    bad += ({ "cowardly" });
	    break;
	case -699 .. -500:
	    bad += ({ "cowardly" });
	    break;
	case -499 .. -300:
	    bad += ({ "debased" });
	    break;
	case -299 .. -100:
	    bad += ({ "humble" });
	    break;
	case -99 .. -40:
	    bad += ({ "humble" });
	    break;
	case -39 .. -10:
	    bad += ({ "humble" });
	    break;
	case -9 .. 10:
	    bad += ({ "prideless" });
	    break;
	case 11 .. 40:
	    good += ({ "somewhat proud" });
	    break;
	case 41 .. 100:
	    good += ({ "somewhat proud" });
	    break;
	case 101 .. 300:
	    good += ({ "proud" });
	    break;
	case 301 .. 500:
	    good += ({ "very proud" });
	    break;
	case 501 .. 700:
	    good += ({ "noble" });
	    break;
	case 701 .. 1000:
	    good += ({ "very noble" });
	    break;
	case 1001 .. US_VIRTUE_MAX:
	    good += ({ "inspiringly noble" });
	    break;
	default:
	    good += ({ "strangly proud" });
	    break;
	}
    }

    if (!which || which == US_GRACE)
    {
	switch(who->query_union_virtue(US_GRACE))
	{
	case US_VIRTUE_MIN .. -1000:
	    bad += ({ "very clumsy" });
	    break;
	case -999 .. -700:
	    bad += ({ "very clumsy" });
	    break;
	case -699 .. -500:
	    bad += ({ "very clumsy" });
	    break;
	case -499 .. -300:
	    bad += ({ "quite clumsy" });
	    break;
	case -299 .. -100:
	    bad += ({ "slightly clumsy" });
	    break;
	case -99 .. -40:
	    bad += ({ "clumsy" });
	    break;
	case -39 .. -10:
	    bad += ({ "graceless" });
	    break;
	case -9 .. 10:
	    bad += ({ "without grace" });
	    break;
	case 11 .. 40:
	    good += ({ "slightly graceful" });
	    break;
	case 41 .. 100:
	    good += ({ "graceful" });
	    break;
	case 101 .. 300:
	    good += ({ "graceful" });
	    break;
	case 301 .. 500:
	    good += ({ "quite graceful" });
	    break;
	case 501 .. 700:
	    good += ({ "very graceful" });
	    break;
	case 701 .. 1000:
	    good += ({ "very graceful" });
	    break;
	case 1001 .. US_VIRTUE_MAX:
	    good += ({ "incredibly graceful" });
	    break;
	default:
	    good += ({ "the bearer of a strange grace" });
	    break;
	}
    }

    if (!which)
    {
	if (sizeof(good))
	    ret += ({ COMPOSITE_WORDS(good) });
	if (sizeof(bad))
	    ret += ({ COMPOSITE_WORDS(bad) });

	if (sizeof(ret) == 1)
	    return me + ret[0] + ".\n";
	else
	    return me + ret[0] + ", but " + ret[1] + ".\n";
    }
    else if (sizeof(good + bad))
	return me + (good + bad)[0] + ".\n";
    else
	return "Strange virtue level!\n";
}

public int
vitals(string str)
{
    if (strlen(str))
	return 0;

    write(virtue_desc());
    return 0; // return the rest of the vitals command
}

/*
 * This to prevent people from doing 'stop fight' so they can
 * enter the sway again right away.
 */
public int
stop(string str)
{
    TP->add_prop(UNION_I_MOVE, time());
    return 0;
}

public int
uapp(string str)
{
    object *weps;
    string desc = "";

//    if (TP->query_attack())
//	return NF("You are too busy fighting right now.\n");

    if (!CAN_SEE_IN_ROOM(TP))
	return NF("You cannot see to do that.\n");

    weps = filter(deep_inventory(TP), &->check_weapon());

    if (!sizeof(weps))
	return NF("You have no weapons to examine the condition of.\n");

    foreach(object wep : weps)
    {
	int cond;

	if (!CAN_SEE(TP, wep))
	    continue;

	if ((ENV(wep) != TP) && !ENV(wep)->query_prop(CONT_I_TRANSP))
	    continue;

	desc += CAP(wep->short());

	if (ENV(wep) != TP)
	    desc += " (" + ENV(wep)->short() + ")";

	desc += ":  ";
	cond  = wep->query_dull() - wep->query_repair_dull();

	switch(cond)
	{
	case 0:
	    desc += "prime condition";
	    break;
	case 1:
	    desc += "fine condition";
	    break;
	case 2:
	    desc += "little touched by battle";
	    break;
	case 3:
	    desc += "scarred by battle";
	    break;
	case 4: case 5:
	    desc += "very scarred by battle";
	    break;
	case 6: case 7: case 8:
	    desc += "big need of a smith";
	    break;
	default:
	    desc += "going to break";
	    break;
	}

	desc += ".\n";
    }

    write("You examine the status of all your weapons:\n" + desc);
    say(QCTNAME(TP) +" quickly examines the status of all " +
	HIS(TP) +" weapons.\n");

    return 1;
}

public int
uins(string str)
{
    object *arms;
    string desc = "";

//    if (TP->query_attack())
//	return NF("You are too busy fighting right now.\n");

    if (!CAN_SEE_IN_ROOM(TP))
	return NF("You cannot see to do that.\n");

    /* Could use query_clothing(-1), but clothing doesn't take damage. */
    if (!sizeof(arms = TP->query_armour(-1)))
	return NF("You are wearing no armours to check the condition of.\n");

    foreach(object arm : arms)
    {
	int cond, cloth;

	if (!CAN_SEE(TP, arm))
	    continue;

	desc += CAP(arm->short()) + ":  ";
	cloth = arm->is_cloth_armour();
	cond  = arm->query_condition() - arm->query_repair();

	switch(cond)
	{
	case 0:
	    desc += (cloth ? "without rips" : "prime condition");
	    break;
	case 1: case 2:
	    desc += (cloth ? "has few tears" : "little worn down");
	    break;
	case 3: case 4:
	    desc += (cloth ? "some rips & tears" : "very bad shape");
	    break;
	case 5: case 6: case 7:
	    desc += (cloth ? "many rips & tears" : "urgent need of repair");
	    break;
	default:
	    desc += (cloth ? "falling apart" : "likely to break");
	    break;
	}

	desc += ".\n";
    }

    write("You inspect your worn armours for wear and tear:\n" + desc);
    say(QCTNAME(TP) +" inspects " + HIS(TP) +" armours and "+
	"clothing for wear and tear.\n");

    return 1;
}

/*
 ************************************************************
 ****************** Compare Union Virtues *******************
 ************************************************************
 */
/*
 * Function name: compare_living_virtue
 * Description:   Support function to compare
 * Note: Pretty much just copied from compare_living() in
 *       /cmd/living/state.c
 */
public mixed
compare_living_virtue(int stat, object player1, object player2)
{
    int a, b, c, skill, seed1, seed2, swap, ind;

    a  = player1->query_skill(stat);
    b  = player2->query_skill(stat);

    if (player1 != player2)
    {
	// Success is based on the wisdom of the player
	skill = TP->query_stat(SS_WIS);
	sscanf(OB_NUM(player1), "%d", seed1);
	sscanf(OB_NUM(player2), "%d", seed2);
	skill = 1000 / (skill + 1);
	/* 27 is an arbitrarily selected constant */
	a += random(skill, seed1 + seed2 + 27 + stat);
	b += random(skill, seed1 + seed2 + stat);
    }

    if (a > b)
	c = 100 - (80 * b) / a;
    else
    {
	c = 100 - (80 * a) / b;
	swap = 1;
    }

    switch(stat)
    {
    case US_DIGNITY:	ind = 0; break;
    case US_PRIDE:	ind = 1; break;
    case US_GRACE:	ind = 2; break;
    case US_PURITY:	ind = 3; break;
    }

    c = max(3, (c * sizeof(compare_strings[ind]) / 100));
    return ({ swap, compare_strings[ind][c] });
}

/*
 * Function name: compare
 * Description:   compare virtues of 2 living objects
 */
public int
compare_virtue(string str)
{
    int ix, me;
    string stat, name1, name2;
    mixed p1, p2;
    object pl1, pl2, *ob_list;
    mixed *cstr;

    notify_fail("Correct syntax is: 'compare <virtue> with <person>' or\n" +
	"'compare <virtue> of <person1> and <person2>'\n");

    if (!strlen(str))
	return 0;

    if (!CAN_SEE_IN_ROOM(TP))
    {
	notify_fail("It is too dark to see.\n");
	return 0;
    }

    str += " ";
    ob_list = FILTER_OTHER_LIVE(all_inventory(ENV(TP)));

    if (!parse_command(str, ({}), "%w 'of' %s 'and' %s", stat, name1, name2))
    {
	if (!parse_command(str, ({}), "%w 'with' %s", stat, name2))
	    return 0;

	p2 = FIND_STR_IN_ARR(name2, ob_list);
	if (sizeof(p2) < 1)
	{
	    notify_fail("Compare " + stat + " with who?\n");
	    return 0;
	}

	me = 1;
	pl2 = p2[0];
    }
    else
    {
	p1 = FIND_STR_IN_ARR(name1, ob_list);
	p2 = FIND_STR_IN_ARR(name2, ob_list);

	if (sizeof(p1) < 1 || sizeof(p2) < 1)
	    return 0;

	pl1 = p1[0];
	pl2 = p2[0];
    }


    notify_fail("Unknown virtue. Possible choices are:\n" +
	implode(virtue_names, ", ") + "\n");

    ix = member_array(lower_case(stat), virtue_names);
    if (ix == -1) return 0;

    if (!CAN_SEE(TP, pl2))
    {
	notify_fail("You cannot see that person.\n");
	return 0;
    }

    if (me)
    {
	cstr = compare_living_virtue(virtue_skill[ix], TP, pl2);
	write((cstr[0] ? pl2->query_The_name(TP) + " is " :
		"You are ") + cstr[1] + " " + (cstr[0] ? "you" :
		pl2->query_the_name(TP)) + ".\n");

	if (CAN_SEE(pl2, TP))
	{
	    pl2->catch_msg(QCTNAME(TP) + " seems to be appraising your "+
		"worth carefully.\n");
	}
    }
    else
    {
	if (!CAN_SEE(TP, pl1))
	{
	    notify_fail("You cannot see that person.");
	    return 0;
	}

	cstr = compare_living_virtue(virtue_skill[ix], pl1, pl2);
	write((cstr[0] ? pl2 : pl1)->query_The_name(TP) +" is "+
	    cstr[1] +" "+ (cstr[0] ? pl1 : pl2)->query_the_name(TP) +
	    ".\n");

	if (CAN_SEE(pl2, TP))
	{
	    pl2->catch_msg(QCTNAME(TP) + " seems to be appraising your "+
		"worth carefully.\n");
	}
	if (CAN_SEE(pl1, TP))
	{
	    pl1->catch_msg(QCTNAME(TP) + " seems to be appraising your "+
		"worth carefully.\n");
	}
    }
    return 1;
}

public int
uadverbs(string str)
{
    if (!strlen(str))
	str = "all";

    write(UADVERBS_FILE->show_adverbs(str));
    return 1;
}

public void
flicked_it(object me, object target, object knife)
{
    if (!objectp(me) || !objectp(target) || !objectp(knife))
	return;

    object env = environment(me);

    if (env != environment(target))
	  return;

    if (me != environment(knife))
  	  return;

    if (knife->move(target))
    {
	me->catch_tell(target->query_The_name(me) +" fails to pluck "+
	    LANG_THESHORT(knife) +" from the air.\n");
	say(QCTNAME(me) +" flicks "+ LANG_ASHORT(knife) +" at "+
	    QTNAME(target) +", who failed to pluck it from the air.\n",
	    ({ me, target }));
	target->catch_tell(me->query_The_name(target) +" flicks "+
	    LANG_ASHORT(knife) +" at you.\nYou fumble and fail to pluck "+
	    "it from the air.\n");

	me->emote_adjust_union_virtue(US_PRIDE, -5);
	target->emote_adjust_union_virtue(US_PRIDE, -10);

	if (knife->move(env))
	    knife->move(env, 1);

	knife->set_dull(knife->query_dull() + 1 + random(3));
	return;
    }

    me->catch_tell(target->query_The_name(me) +" deftly plucks "+
	LANG_THESHORT(knife) +" from the air.\n");
    say(QCTNAME(me) +" flicks "+ LANG_ASHORT(knife) +" at "+
	QTNAME(target) +", who deftly plucks it from the air.\n",
	({ me, target }));
    target->catch_tell(me->query_The_name(target) +" flicks "+
	LANG_ASHORT(knife) +" at you.\nYou instinctively pluck "+
	"it from the air, its hilt slapping firmly against your palm.\n");

    me->emote_adjust_union_virtue(US_PRIDE, 3);
    target->emote_adjust_union_virtue(US_PRIDE, 3);
}

public int
flick(string str)
{
    int size;
    string str1, str2;
    object knife, who, *what;

    if (strlen(str))
    {
	if (sscanf(str, "%s to %s", str1, str2) != 2)
	    str1 = str2 = str;
    }

    notify_fail("Flick what to whom?\n");

    what = FIND_STR_IN_OBJECT(str1, TP);

    if (!sizeof(what))
	knife = get_knife(TP);
    else
	knife = what[0];

    if (!objectp(knife))
	return 0;

    if (!valid_knife(knife, TP))
    {
	write("The "+ knife->short() +" cannot be flicked.\n");
	return 1;
    }

    what = parse_this(str2, "[the] %l");
    size = sizeof(what);

    if (!size)
	return 0;

    if (size > 1)
    {
	write("You may only flick to one person at a time.\n");
	return 1;
    }

    who = what[0];

    if (!IS_MEMBER(who) || !CAN_SEE(TP, who))
    {
	write("Flick "+ LANG_THESHORT(knife) +" at whom?\n");
	return 1;
    }

    write("With a graceful flick of your wrist, "+
	"you send "+ LANG_THESHORT(knife) +" flying at "+
	who->query_the_name(TP) +".\n");

    set_alarm(1.0, 0.0, &flicked_it(TP, who, knife));
    return 1;
}
