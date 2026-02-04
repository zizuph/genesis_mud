
basket_here()
{
    seteuid(getuid());
    if (THIS_LEVEL == BASKET->query_level())
	return 1;
    return 0;
}

/* rope_here: returns 1 if rope is visible */
int
rope_here()
{
    seteuid(getuid());
    if (THIS_LEVEL <= BASKET->query_level())
	return 1;
    return 0;
}

string
desc_basket()
{
    if (basket_here())
	return BASKET->query_desc();
    return("Hmmm... you don't see any basket here...\n");
}

string
desc_rope()
{
    if (basket_here())
	return(break_string("You can't see where the rope comes from - " +
	    "you imagine it's fixed somewhere above you, maybe at the top " +
	    "of the well? There's hanging a basket on the rope just next " +
	    "to you.\n",70));
    if (rope_here())
	return(break_string("You can't see where the rope comes from - " +
	    "you imagine it's fixed somewhere above you, maybe at the top " +
	    "of the well? The rope continues downwards, but you can't make " +
	    "out its end - probably there's something hanging on it " +
	    "below.\n",70));
    return("Hmmm... you don't see any rope here...\n");
}

init()
{
    ::init();
    add_action("enter_basket","enter");
    add_action("pull_rope","pull");
#ifdef INITADD
INITADD
#endif
}

int
pull_rope(string str)
{
    notify_fail("Pull what?\n");
    if (str != "rope") return 0;
    notify_fail("But there's no rope here to pull...\n");
    if (!rope_here()) return 0;
    WELL->pull_notify();
    BASKET->pull_notify(THIS_LEVEL);
    write("You pull the rope...\n");
    say(QCTNAME(this_player()) + " pulls the rope.\n");
    return 1;
}

int
enter_basket(string str)
{
    notify_fail("Enter what?\n");
    if (str != "basket") return 0;
    notify_fail("But there's no basket here..\n");
    if (!basket_here()) return 0;
    notify_fail("But the basket is already occupied..\n");
    if (BASKET->TAS()) return 0;
    this_player()->move_living("into basket",BASKET);
    return 1;
}

notify(string arrdep, string dir)
{
    tell_room(this_object(),
	"Suddenly, a basket on a rope " + arrdep + dir + ".\n");
}

pull_notify()
{
    tell_room(this_object(),
	"The rope just moved - probably somebody pulled it above or below.\n");
}

notify_tooheavy()
{
    if (basket_here())
	tell_room(this_object(),break_string(
	    "The basket trembles for a second, as if somebody above tried to " +
	    "lift the basket but didn't succeed because he's " +
	    "too weak.\n",70));
    else
	tell_room(this_object(),break_string(
	    "The rope trembles for a second, as if somebody above tried " +
	    "to lift whatever is hanging on the rope but didn't succeed " +
	    "because he's too weak.\n",70));
}

string
long_desc()
{
    return(break_string("You find yourself on a very narrow ledge " +
	"made of rock. You can hardly keep your balance... to the " + DIR +
	" you recognize the shaft of a well" +
	(basket_here() ? " with a basket hanging on a rope inside. " : 
	    (rope_here() ? " with a rope hanging inside. " : ". " )) +
	"Far above you can make out some light, while it's dark " +
	"below. The walls are of dried out loam mixed with stones. It smells " +
	"of decay here...\n",70));
}


