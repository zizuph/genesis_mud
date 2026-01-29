inherit "/std/food";

#include <stdproperties.h>
#include <macros.h>
#define INTACT_EGG "/d/Dville/deinonychus/tmp/intact_egg.c"
#define BROKEN_EGG "/d/Dville/deinonychus/tmp/broken_egg.c"

create_food()
{
    set_amount(0);
    set_name("egg");
    set_short("intact egg");
    set_adj("intact");
    set_long("This is an intact Easter-egg.\n" + 
        break_string("Do you know that there's an old custom in " +
	"the land of mountains and cheese for these egg? " +
	"It needs two people, each holding an intact egg. The one " +
	"aims to crack the other person's egg with his own. The " +
	"person whose egg cracks has to give his egg to the other. " +
	"Just type: crack egg with <player>.\n",70));
}

void
init()
{
    ::init();
    add_action("crack", "crack");
}

int
crack(string what)
{
    object oponent, oponent_egg, my_egg, broken_egg;
    string crack_what, with_whom, name;
    int i;

    setuid();
    seteuid(getuid());
    if(parse_command(what, environment(this_player()),
        "'egg' 'with' %o", oponent) &&
       parse_command("intact egg", this_player(), "%o", my_egg))
    {
	if(oponent == this_player())
	{
	    notify_fail("You can't crack eggs with yourself.\n");
	    return 0;
	}
    	if(parse_command("intact egg", oponent, "%o", oponent_egg))
	{
	    say(QCTNAME(this_player()) + " cracks eggs with " +
		QCTNAME(oponent) + ".\n", ({this_player(), oponent}));
	    if(random(2))
	    {
		if(this_player()->query_met(oponent))
		    name = oponent->query_name();
		else
		    name = "the " + oponent->query_short();
		write("You crack eggs with " + name + " and win.\n" +
		    "HURRAY!\nYour oponent gives you the broken egg.\n");
		if(oponent->query_met(this_player()))
		    name = this_player()->query_name();
		else
		    name = "The " + this_player()->query_short();
		tell_object(oponent, name + " cracks eggs with you. " +
		    "You lose.\nWAAHHH!\nYou give your egg to your oponent.\n");
		i = oponent_egg->num_heap() - 1;
		oponent_egg->set_heap_size(i);
		broken_egg = clone_object(BROKEN_EGG);
		broken_egg->move(this_player());
		return 1;
	    }
	    else
	    {
		if(this_player()->query_met(oponent))
		    name = oponent->query_name();
		else
		    name = "the " + oponent->query_short();
		write("You crack eggs with " + name + " and lose.\n" +
		    "WAAHHH!\nYou give your egg to your oponent.\n");
		if(oponent->query_met(this_player()))
		    name = this_player()->query_name();
		else
		    name = "The " + this_player()->query_short();
		tell_object(oponent, name + " cracks eggs with you. " +
		    "You win.\nHURRAY!\nYour oponent gives you the broken egg.\n");
		i = my_egg->num_heap() - 1;
		my_egg->set_heap_size(i);
		broken_egg = clone_object(BROKEN_EGG);
		broken_egg->move(oponent);
		return 1;
	    }
	}
    	if(!(oponent_egg = present("egg", oponent)))
    	{
	    if(this_player()->query_met(oponent))
	        name = oponent->query_name();
	    else
	        name = "The " + oponent->query_short();
    	    notify_fail(name + " doesn't seem to have an " +
    	        "Easter-egg.\n");
    	    return 0;
    	}
    	if(parse_command("broken egg", oponent, "%o", oponent_egg))
    	{
	    if(this_player()->query_met(oponent))
	        name = oponent->query_name();
	    else
	        name = "the " + oponent->query_short();
    	    notify_fail("The egg " + name + " is holding is " +
		"broken. You can't crack eggs with this person.\n");
	    return 0;
    	}
    }
    else
    {
        notify_fail("Crack what with whom?\n");
    }
    return 0;
}
