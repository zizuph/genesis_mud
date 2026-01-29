//based on loaf.c by Cirion
#pragma strict_types
inherit "/std/object";

#include <files.h>
#include <macros.h>
#include <stdproperties.h>

#include "../defs.h"

public int size = 10;

public string
cheese_long()
{
    string str;

    switch(size)
    {
    case 0..2:
	str = "There is only a small amount left.";
	break;
    case 3..4:
	str = "There is a bit less than half the round left.";
	break;
    case 5:
	str = "Only half the round remains.";
	break;
    case 6..7:
	str = "Over half the round remains.";
	break;
    case 8..9:
	str = "Only a little cheese has been broken from the round.";
	break;
    default:
	str = "The round is complete and unbroken.";
	break;
    }

    return "It is a round of mild cheese made from cream "+
	"skimmed from the milk of sybarun goats. It is "+
	"soft and pale yellow in colour. " + str + "\n";
}

public void
create_object()
{
    reset_euid();

    set_name("round");
    add_name(({"cheese"}));
    set_pname("rounds");
    set_adj("sybarun");
    add_adj(({"goat", "soft", "yellow", "mild"}));
    set_long(cheese_long);
    set_short("round of sybarun cheese");
    set_pshort("rounds of sybarun cheese");
    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VOLUME, 5000);
}

public int
cut_cheese(string str)
{
    string msg;
    object food;
    int num_cheese;

    notify_fail(CAP(query_verb()) + " what?\n");

    if (!strlen(str))
	return 0;
    /*
     * Possible wordings:
     * cut / slice cheese
     * cut / slice off a piece of cheese
     * cut / slice cheese from round
     * cut / slice a piece of cheese from the round
     */
    if (!parse_command(str, TP, "[off] [a] [piece] [of] 'cheese' [from] "+
	    "[the] [round] [of] [cheese]"))
	return 0;

    if (!(--size))
    {
	msg = "You cut the remainder of the round into two pieces of cheese.\n";
	num_cheese = 2;
	// remove the round after this command has been executed.
	set_alarm(0.0, 0.0, remove_object);
    }
    else
    {
	msg = "You slice a piece of cheese from the " + QSHORT(TO) + ".\n";
	num_cheese = 1;
    }

    food = clone_object(FOOD_OBJECT);
    food->set_name("cheese");
    food->add_name(({"slice", "piece"}));
    food->set_short("piece of sybarun goat cheese");
    food->set_pshort("pieces of sybarun goat cheese");
    food->set_adj(({"sybarun", "goat"}));
    food->set_amount(50);
    food->set_long("It is a piece of cheese cut from a larger "+
	"round of cheese.\n");
    food->add_prop(OBJ_I_WEIGHT, 65);
    food->add_prop(OBJ_I_VOLUME, 65);
    food->add_prop(HEAP_S_UNIQUE_ID, "_slice_of_union_cheese");
    food->set_heap_size(num_cheese);

    TP->catch_msg(msg);
    say(QCTNAME(TP) + " slices a piece from " + HIS(TP) +
	" " + QSHORT(TO) + ".\n");

    if (food->move(TP))
    {
	write("You drop it on the ground.\n");
	food->move(ENV(TP));
    }

    return 1;
}

public int
eat_cheese(string str)
{
    notify_fail(CAP(query_verb()) + " what?\n");

    if (!strlen(str))
	return 0;

    if (!parse_command(str, TP, "[the] [round] [of] [sybarun] 'cheese'"))
	return 0;

    return NF("It is too large. You would need to cut a piece of cheese "+
	"from the round, first.\n");
}

public void
init(void)
{
    ::init();

    add_action(cut_cheese, "cut");
    add_action(cut_cheese, "slice");
    add_action(eat_cheese, "eat");
}
