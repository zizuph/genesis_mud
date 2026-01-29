#pragma save_binary

/*      This is the second set of emotes for the Calian warrior's guild.
        It is included into the calian cmdsoul.

/*

    coder(s):   Amelia
    history:
                      11/9/98   some emotes modified        Maniac 
                      30/3/96   underwater block added      Maniac
                       24/8/95  typo taken out              Maniac
                       10/4/95  typo taken out              Maniac
			8/4/95	corrected by Amelia ;)
*/

int
calian_relieved()
{

	write("A great feeling of relief washes over you.\n");
	allbb(" looks very relieved!");
	SOULDESC("looking extremely relieved");
	return 1;
}


int
calian_happy()
{
	write("You revel in the sheer joy of what has happened.\n");
	allbb(" revels in the sheer joy of what has happened.");
	SOULDESC("revelling in the sheer joy of what has happened");
	return 1;
}


int
calian_misery()
{
	write("You crumple into a miserable heap.\n");
	allbb(" crumples into a miserable heap.");
	SOULDESC("crumpled into a miserable heap");
	return 1;
}


int
calian_laugh(string friend_name)
{
	object *friend;

        IN_WATER_BLOCK;
        UNDER_WATER_BLOCK; 

	if (!friend_name)
		{
		write("You roll on the floor, laughing "+
			"your head off!\n");
		allbb(" rolls on the floor, "+
		"laughing "+TP->query_possessive()+" head off!");
		SOULDESC("laughing hysterically");
		return 1;
		}
	friend = parse_this(friend_name, "[at] %l");
	if(!sizeof(friend))
		{
		notify_fail("Laugh at whom?\n");
		return 0;
		}
	actor("You point a finger at", friend, " and fall down "+
		"laughing onto the floor.");
	targetbb(" points a finger at you "+
		"and falls down laughing onto the floor.", friend);
	all2actbb(" points a finger at", friend," and falls down "+
		"laughing onto the floor.");
	SOULDESC("laughing hysterically");
	return 1;
}

int
calian_mutter()
{
        UNDER_WATER_BLOCK;
	write("You frown and mutter darkly to yourself.\n");
	allbb(" frowns and mutters darkly to "+
		TP->query_objective()+"self.");
	SOULDESC("frowning and muttering darkly");
	return 1;
}


int
calian_fond(string friend_name)
{
	object *friend;

	if (!friend_name)
		{
		notify_fail("Whom are you fond of?\n");
		return 0;
		}
	friend = parse_this(friend_name, "%l");
	if (!sizeof(friend))
		{
		notify_fail("Whom are you fond of?\n");
		return 0;
		}
	actor("You give", friend, " a fond look.");
	targetbb(" gives you a fond look.", friend);
		
	all2actbb(" gives", friend, " a fond look.");
	SOULDESC("looking very affectionate");
	return 1;
}

int
calian_protect(string friend_name)
{
	object *friend;

        IN_WATER_BLOCK;
        UNDER_WATER_BLOCK;
	if (!friend_name)
		{
		notify_fail("Invoke Caliana to protect whom?\n");
		return 0;
		}
	friend = parse_this(friend_name, "%l");
	if (!sizeof(friend))
		{
		notify_fail("Invoke Caliana to protect whom?\n");
		return 0;
		}
	actor("You bow deeply to", friend, " and intone, "+
		"May Caliana protect you on your chosen path!");
	targetbb(" bows deeply to you and intones, "+
		"May Caliana protect you on your chosen path!", friend);
	all2actbb(" bows deeply to", friend, " and intones, "+
		"May Caliana protect you on your chosen path!");
	return 1;
}

int
calian_slap(string friend_name)
{
	object *friend;

	if (!friend_name)
		{
		notify_fail("Slap whom?\n");
		return 0;
		}
	friend = parse_this(friend_name, "%l");
	if (!sizeof(friend))
		{
		notify_fail("Slap whom?\n");
		return 0;
		}
	actor("You give", friend, " a hearty slap on the back!");
	targetbb(" gives you a hearty slap on the back!", friend);
	all2actbb(" gives", friend, " a hearty slap on the back!");
	return 1;
}


int
calian_drunk()
{

	int max_drunk, index, level;

        IN_WATER_BLOCK;
        UNDER_WATER_BLOCK; 

	max_drunk = TP->intoxicated_max();
	level = TP->query_intoxicated() + random(35);
	index = level / (max_drunk/5);


	switch (index)
	{
	case 0:
		{
		write("You are just a little too sober.\n");
		allbb(" appears very sober.");
		SOULDESC("looking sober");
		return 1;
		}
	case 1:
		{
		write("You hiccup and sway tipsily.\n");
		allbb(" hiccups and sways tipsily.");
		SOULDESC("hiccupping and swaying tipsily");
		return 1;
		}
	case 2:
		{
		write("You grin drunkenly and begin to sing "+
			"a little song about a house in Re Albi.\n");
		allbb(" grins drunkenly and begins to sing "+
			"a little song about a house in Re Albi.");
		SOULDESC("grinning and singing drunkenly");
		return 1;
		}
	case 3:
		{
		write("You stagger around drunkenly and "+
		"barely manage to stay on your feet.\n");
		allbb(" staggers around drunkenly and "+
		"barely manages to stay on "+
		TP->query_possessive()+" feet.");
		SOULDESC("staggering drunkenly");
		return 1;
		}
	case 4:
		{
		write("You suddenly turn green and puke on "+
		"your shoes!\n");
		allbb(" turns green and pukes on "+
		TP->query_possessive()+" shoes.");
		SOULDESC("looking very green, with messy shoes");
		return 1;
		}
	case 5:
		{
		write("You fall down and pass out for a moment.\n");
		allbb(" falls down and passes out for a moment.");
		SOULDESC("looking slightly unconscious");
		return 1;
	}
	}
}
