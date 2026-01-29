inherit "/std/object";
#include "/d/Gondor/defs.h"
#include "../erech.h"

#include <macros.h>
#include <stdproperties.h>

/* Prototypes */
string short_desc();
string long_desc();
int    drink(string arg);
int    empty(string arg);

/* Global variables */
int    filled;
string content;

create_object() 
{
    set_short(&short_desc());
    set_long(&long_desc());
    set_name("plate");
    add_name("dish");
    add_name("Erech_farm_plate");
    set_adj("small");
    add_adj("cropped");
    add_prop(OBJ_I_WEIGHT,57);
    add_prop(OBJ_I_VOLUME,25);
    add_prop(OBJ_I_VALUE,35);
    add_prop(ERECH_QUEST_ITEM,1);

    filled = 0;

}

string
short_desc()
{
    if (filled == 0)
        return "small cropped plate";
    else if (filled == 1)
        return "small plate with "+content;
}

string
long_desc()
{
    if (filled == 0)
        return "A small cropped plate. You can probably be able to fill it " +
	    "with something.\n";
    else if (filled == 1)
        return "A small plate filled with "+content+". It might be able to " +
	    "drink from it.\n";
}

void
init()
{
    ::init();
    add_action(drink, "drink");
    add_action(empty, "empty");
}

int
drink(string arg)
{
    object drinker;

    drinker = this_player();

    if (arg == "from plate")
    {
        if (filled == 1)
	{
	    if (drinker->query_name() == "cat")
	    {
  	        if (content != "milk")
		    return 1;
		drinker->set_thirsty(0);
	    }
	    write("You drink some " + content + " from the plate.\n");
	    say(QCTNAME(drinker) + " drinks from " +
		drinker->query_possessive() + " plate.\n");
	    drinker->drink_soft(4);
	    filled = 0;
	    content == "";
	    return 1;
	}
	else
	{
	    write("The plate is empty, you need to fill it with something " +
		  "first.\n");
	    return 1;
	}
    }
    return 0;
}

int
set_filled(string arg)
{
    if (filled == 1)
        return 1;
    //    write("You fill some " + arg + " on the plate.\n");
    filled = 1;
    content = arg;
    return 1;
}

int query_filled() { return filled; }
string query_content() { return content; }

int
empty(string arg)
{
    if (arg != "plate")
    	return 0;
    write("You pour all the " + content + " on the ground.\n");
    say(QCTNAME(this_player()) + " pours some " + content + " from " +
	this_player()->query_possessive() + " plate.\n");
    filled = 0;
    content = "";
    return 1;
}
