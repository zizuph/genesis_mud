/*
 * Bottle of soap for blowing bubbles
 * By Finwe, September 2001
 *
 * Made adjustments so it would work as a bowl of petals.
 * The file was half bubbles and half petals and wouldn't load, so I moved it 
 * over to all petals.
 * Raymundo, March 2020
 */


#include "/d/Shire/sys/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

inherit "/std/object";
inherit "/lib/keep";

int bubble_count;


create_object()
{
    set_short("rose petal bowl");
	add_name("bowl");
	add_adj( ({"glass", "cut", "petal", "petals", "rose"}));
    set_name(({"bowl of petals"}));
    set_pname("bowls of petals");
    set_long("This a bowl used to hold rose petals. The bowl is made of cut crystal and very ornate looking. You could probably throw the petals. The bowl is @@petal_status@@.\n");

    bubble_count=100;
	

}


init()
{
    ::init();
    add_action("throw_petals", "throw");
}

int
query_bubbles_bottle()
{
    return 1;
}

string petal_status()
{

    if (bubble_count >= 90)
        return "full";
    else if(bubble_count >= 75)
        return "more than half full";
    else if(bubble_count >= 50)
        return "about half full";
    else if(bubble_count >= 25)
        return "less than half full";
    else if(bubble_count >= 15)
        return "almost empty";
    else if(bubble_count <= 0)
        return "empty";
}

int
throw_petals(string str)
{  
	if(str == "flower petals" | str == "rose petals" | str == "petals")
	{
		if (bubble_count <= 0)  /* got bubbles? */
		{
			notify_fail("You are all out of petals.\n");
			return 0;
		}
		write("You grab a handful of rose petals and throw them into the air!\n");
		say(QCTNAME(this_player()) + " grabs a handful of rose petals and throws "
			+ "them into the air!\n");
              bubble_count = (bubble_count - (1 + random(5))); /* decrease bubble count */
		return 1;

	 }
	 else
		 notify_fail("Did you mean to throw petals?\n");
	 return 0;
}
