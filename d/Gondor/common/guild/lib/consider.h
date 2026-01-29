/*
 * /d/Gondor/common/guild/lib/consider.h
 *
 * The Ranger ability to consider the taint on the soul
 * of another being.
 *
 * The ability gives no advantages, but is needed to keep from
 * attracting the penalties for aiding evil-aligned players.
 */

mixed
consider(string str)
{
    int  align;
    object *oblist, ob;
    string st, pr, nr, tr, typ, order;

    oblist = parse_this(str, "[the] %l");

    str = lower_case(str);
    if (str == "myself" || str == "me" || str == TP->query_real_name())
    {
	oblist = ({ this_player() });
    }
    if (!oblist || !sizeof(oblist))
    {
	NF("Consider whom?\n");
	return 0;
    }

    NF("You can only consider one being at a time.\n");
    if (sizeof(oblist) > 1)
	return 0;

    ob = oblist[0];

    if (ob == TP)
    {
	switch(TP->query_skill(SS_RANGER_DISFAVOUR))
	{
	case 0:
	    TP->catch_tell("You feel that the Valar are satisfied "+
	      "with your use of their gifts.\n");
	    break;
	case 1..25:
	    TP->catch_tell("You feel that the Valar are dissatisfied with your "+
	      "use of their gifts.\n");
	    break;
	case 26..50:
	    TP->catch_tell("You feel that the Valar are upset with your "+
	      "use of their gifts.\n");
	    break;
	case 51..70:
	    TP->catch_tell("You feel that the Valar are angry with your "+
	      "use of their gifts.\n");
	    break;
	default:
	    TP->catch_tell("You feel that the Valar are furious with your "+
	      "use of their gifts.\n");
	    break;
	}
	return 1;
    }

    align = ob->query_alignment();
    if (!ob->query_npc() &&
      (RANGER_DIR + "outlaw")->query_outlaw(ob->query_real_name()))
    {
	TP->catch_msg("You have a very strong feeling that "
	  + QTNAME(ob) + " supports the Dark Lord.\n");
        return 1;
    }

    if (align < -850)
	TP->catch_msg("You have a really strong feeling that "
	  + QTNAME(ob) + " bears a powerful hatred for the "
	  + "Free Peoples.\n");
    else if (align < -500)
	TP->catch_msg("You have a very strong feeling that "
	  + QTNAME(ob) + " is unfaithful to the Valar.\n");
    else if (align < -150)
	TP->catch_msg("You have a strong feeling that "
	  + QTNAME(ob) + " supports darker causes.\n");
    else if (align < 0)
	TP->catch_msg("You have a feeling that "
	  + QTNAME(ob) + " cannot be trusted.\n");
    else if (align < 100)
        TP->catch_msg("You have no particularly strong feeling about " +
            QTNAME(ob) + ".\n");
    else if (align < 250)
        TP->catch_msg("You feel that " + QTNAME(ob) + " may be " +
            "trustworthy.\n");
    else if (align < 500)
	TP->catch_msg("You have a strong feeling that "
	  + QTNAME(ob) + " may be good and trustworthy.\n");
    else if (align < 850)
	TP->catch_msg("You have a very strong feeling that "
	  + QTNAME(ob) + " supports noble causes and is faithful "
	  + "to the Valar.\n");
    else
	TP->catch_msg("You have a really strong feeling that "
	  + QTNAME(ob) + " is pure of spirit and very faithful "
	  + "to the Valar.\n");
    return 1;
}

