/*
* The consider ability, taken from the former consider spell.
*/

mixed
consider(string str)
{
    int level, sublevel, stat, align;
    object *oblist, ob;
    string st, pr, nr, tr, typ, order;

    level = TP->query_knight_level();
    switch(level)
    {
    case(5):
	order = "Order of the Rose";
	break;
    case(4):
	order = "Order of the Sword";
	break;
    case(3):
	order = "Order of the Crown";
	break;
    case(2):
	order = "Knighthood";
	break;
    default:
	order = "not used";
	break;
    }

    sublevel = TP->query_knight_sublevel();
    stat = TP->query_skill(SS_PRESTIGE_ST);

    if (TP->query_prop(KNIGHT_I_DEVOTION) < TP->query_age() + 200)
	TP->add_prop(KNIGHT_I_DEVOTION, TP->query_age() + 200);

    if (!str)
    {
	if (level > 2)
	{
	    if (sublevel != 1)
		write("Your rank in the "+order+" is "+TP->query_knight_title()+
		  ".\n");
	    else
		write("Your rank in the "+order+" is "+TP->query_knight_title()+
		  ", but you are dangerously close to becoming a Knight of "+
		  "the Black Rose.\n");

	    if (sublevel < TP->query_level_up(stat + 1))
		st = "deserving of a promotion";
	    else if (sublevel < TP->query_level_up(stat + 3))
		st = "as one who will soon be worthy of promotion";
	    else if (sublevel > TP->query_level_up(stat - 1))
		st = "very recently promoted, and not deserving of another promotion "+
		"in the near future";
	    else if (sublevel > TP->query_level_up(stat - 3))
		st = "recently promoted, and not yet ready for another promotion";
	    else
		st = "as an established member of your current rank";

	    write("You feel your deeds and actions of late have left "+
	      "you " + st + ".\n");
	}

	if (level == 2)
	{
	    nr = SQUIRE_TITLES[sublevel + 1];
	    pr = SQUIRE_TITLES[sublevel - 1];
	    tr = SQUIRE_TITLES[sublevel];

	    if (sublevel < TP->query_level_up(stat + 1))
		st = "and you feel your promotion to " + nr + " is likely to "+
		"come very soon.";
	    else if (sublevel < TP->query_level_up(stat + 3))
		st = "and you feel that soon you will be promoted to " + nr +".";
	    else if (sublevel > TP->query_level_up(stat - 1))
		st = "but you have only recently attained this rank, and "+
		"are not even close to another promotion.";
	    else if (sublevel > TP->query_level_up(stat - 3))
		st = "but you have recently attained this rank, and are not "+
		"close to another promotion.";
	    else
		st = "and while you've proven yourself as worthy of this rank, "+
		"you doubt that you will be promoted any time soon.";
	    write("Your actions as a Squire have attained you the "+
	      "rank of " + tr + ", "+st+"\n");
	    return 1;
	}


	if (level == 1)
	{
	    if (sublevel < 1)
		write("At the moment, you are about as likely to be reinstated as "+
		  "a draconian.\n");
	    if (sublevel == 1)
		write("Your actions have been a disgrace to the Knighthood, and "+
		  "presently they do not think highly of you at all.\n");
	    if (sublevel == 2)
		write("While you are a Knight of the Black Rose, you feel that your "+
		  "journey to becoming a true Knight again is nearly over.\n");
	    return 1;
	}

	return 1;
    }

    oblist = parse_this(str, "[the] %l");

    NF("Consider whom?\n");
    if (!oblist || !sizeof(oblist))
	return 0;

    NF("You can only consider one being at a time.\n");
    if (sizeof(oblist) > 1)
	return 0;

    ob = oblist[0];

    if (ob == TP)
	return "There is no prestige to be won by suicide.\n";

    stat = TP->query_ob_prestige(ob);
    align = ob->query_alignment();
    typ = "creature";

    /*
       if (interactive(ob) && ob->query_race_name() != "goblin")
	  {
	  stat = -1;
	  typ = "person";
       }
    */

    if (!stat || interactive(ob))
    {
	if (align < -750)
	    align = -751;
	if (align > 400)
	    align = 401;

	switch(align)
	{
	case -200..200:
	    stat = 0;
	    break;
	case -400..-201:
	    stat = 100;
	    break;
	case -750..-401:
	    stat = 500;
	    break;
	case -751:
	    stat = 1000;
	    break;
	case 201..400:
	    stat = -2;
	    break;
	case 401:
	    stat = -4;
	    break;
	default:
	    stat = 0;
	    break;
	}
    }

    if (stat == 0)
	TP->catch_msg("You feel that " + QTNAME(ob) + " is of no concern to "+
	  "the Knighthood.\n");
    else if (stat > 1000)
	TP->catch_msg("You feel the Knighthood would be very impressed by your "+
	  "defeat of " + QTNAME(ob) + ".\n");
    else if (stat > 500)
	TP->catch_msg("You feel the Knighthood would be thankful to you for "+
	  "ridding the world of " + QTNAME(ob) + ".\n");
    else if (stat > 100)
	TP->catch_msg("You feel the Knighthood would approve of your actions, "+
	  "were you to kill " + QTNAME(ob) + ".\n");
    else if (stat > 0)
	TP->catch_msg("You do not think the Knighthood would object to your "+
	  "killing " + QTNAME(ob) + ".\n");
    else  if (stat < -4)
	TP->catch_msg("The Knighthood will not stand for your unknightly " +
	  "behavior if you kill "+QTNAME(ob) + "!\n");
    else  if (stat < -2)
	TP->catch_msg("The Knighthood would be gravely disappointed in you if "+
	  "you killed " + QTNAME(ob) + ".\n");
    else  if (stat < -0)
	TP->catch_msg("You believe the Knighthood would frown upon you for killing " +
	  QTNAME(ob) + ".\n");
    return 1;
}

