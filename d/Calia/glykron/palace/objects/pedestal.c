inherit "/std/container";
#include <stdproperties.h>
#include "defs.h"

string *colours =
({
    "black",
    "violet",
    "blue",
    "green",
    "yellow",
    "orange",
    "red"
});

mapping colour_indices =
([
    "black" : 0,
    "violet" : 1,
    "blue" : 2,
    "green" : 3,
    "yellow" : 4,
    "orange" : 5,
    "red" : 6
]);

int turn(string str)
{
    object ob;
    string direction, *words;
    int colour_index;
    words = explode(str, " ");
    if (!sizeof(words))
    {
	NF("Turn what ?\n");
	return 0;
    }
    if (present(str, this_object()))
    {
	NF("Turn " + str + " which way?\n");
	return 0;
    }
    direction = words[sizeof(words) - 1];
    words -= ({ direction });
    if (!sizeof(words), !(ob = present(str = implode(words, " "), THIS)))
    {
	if (direction == "left" || direction == "right")
	    NF("Turn what " + direction + "?\n");
	else
	    NF("Turn what ?\n");
	return 0;
    }
    if (direction != "left" && direction != "right")
    {
	NF("Turn " + str + " how?");
	return 0;
    }
    if (ob->query_name() != "rod")
    {
	write("The " + str + " will not turn.\n");
	return 1;
    }

    if (!ob->query_prop(OBJ_I_CHANGEABLE_COLOUR))
    {
	write("Ok.\n");
	return 1;
    }

    colour_index = colour_indices[ob->query_colour()];
    say("The colour of the rod changed from " + ob->query_colour() + " to ");

    ob->set_colour
    (
	colours
	[
	    direction == "left"
	        ? colour_index > 0 ? colour_index - 1 : 6
	        : colour_index < 6 ? colour_index + 1 : 0
        ]
    );

    say(ob->query_colour() + ".\n");
    return 1;
}

void init()
{
    ::init();
    add_action("turn", "turn");
}

string description()
{
    string descrip;
    object rod;
    descrip = "The white pedestal is in the shape of a frustrum of a cone.\n" +
	"It has a hole in the top.\n";
    if (rod = present("rod", THIS))
	descrip += "The pedestal has a " + rod->short() +
	    " sticking out of its top.\n";
    return descrip;
}

void create_container()
{
    set_name("pedestal");
    set_adj("white");
    set_long("@@description");
    add_item("hole", "It is dark in there!\n");
    add_subloc("hole");
    add_prop(OBJ_I_NO_GET, 1);
    add_prop(CONT_I_TRANSP, 1);
    add_prop(CONT_I_WEIGHT, 10000);
    add_prop(CONT_I_VOLUME, 10000);
    add_prop(CONT_I_MAX_WEIGHT, 20000);
    add_prop(CONT_I_MAX_VOLUME, 10101);
}
