#pragma strict_types
inherit "/std/food";

#include <files.h>
#include <macros.h>
#include <language.h>
#include <stdproperties.h>

#include "/d/Avenir/include/defs.h"

public int size = 10, created = time(),
           time_under_wraps, time_start_under_wraps;


public void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    // If the loaf is wrapped up, it does not cool down.
    if (to->id("container"))
	time_start_under_wraps = time();
    else if (from->id("container"))
    {
	time_under_wraps += (time() - time_start_under_wraps);
	time_start_under_wraps = 0;
    }
}

public string
warmth(void)
{
    switch(((time() - created) - time_under_wraps) / 60)
    {
    case 0 .. 60:
	return "piping hot ";
    case 61 .. 120:
	return "hot ";
    case 121 .. 180:
	return "warm ";
    case 181 .. 300:
	return "";
    default:
	return "";
    }
}

public string
loaf_short(void)
{
    return warmth() +"baguette of bread";
}

public string
loaf_pshort(void)
{
    return warmth() +"baguette of bread";
}

public string
loaf_long(void)
{
    string str;

    switch(size)
    {
    case 0..2:
	str = "There is only a small amount left.";
	break;
    case 3..4:
	str = "There is a bit less than half the baguette left.";
	break;
    case 5:
	str = "Only half the baguette remains.";
	break;
    case 6..7:
	str = "Over half the baguette remains.";
	break;
    case 8..9:
	str = "Only a little bread has been broken from the baguette.";
	break;
    default:
	str = "The baguette is complete and unbroken.";
	break;
    }

    return "It is "+ LANG_ADDART(warmth()) +"baguette of bread, very "+
	"fragrant and with a crispy, golden crust. " + str + " It looks "+
    "delcious and you cannot wait to <break bread> to get a piece "+
    "of it.\n";
}

private void
create_food(void)
{
    setuid();
    seteuid(getuid());
	
    set_name("baguette");
    add_name(({"loaf", "bread", "food"}));
    add_pname("loaves");

    set_long(loaf_long);
    set_short(loaf_short);
    set_pshort(loaf_pshort);

    set_amount(500);

    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 1000);
}

public int
break_bread(string str)
{
    string msg;
    object food;
    int num_bread;

    notify_fail(CAP(query_verb()) + " what?\n");
    if (!strlen(str))
	return 0;

    if (!parse_command(str, TP, "[off] [a] [piece] [of] 'bread' [from] "+
	    "[the] [loaf] / [baguette] [of] [bread]"))
	return 0;

    size--;
    if (!size)
    {
	msg = "You break the remainder of the baguette into two "+
    "pieces of bread.\n";
	num_bread = 2;
	// remove the loaf after this command has been executed.
	set_alarm(0.0, 0.0, remove_object);
    }
    else
    {
	msg = "You break a piece from the " + QSHORT(TO) + ".\n";
	num_bread = 1;
    }

    food = clone_object(FOOD_OBJECT);
    food->set_name("bread");
    food->add_name("piece");
    food->set_short("piece of " + warmth() + "bread");
    food->set_pshort("pieces of " + warmth() + "bread");
    food->set_adj(warmth());
    food->set_amount(50);
    food->set_long("It is a fragrant piece of fresh bread, "+
    "broken by hand from a baguette.\n");
    food->add_prop(OBJ_I_WEIGHT, 65);
    food->add_prop(OBJ_I_VOLUME, 65);
    food->add_prop(HEAP_S_UNIQUE_ID, "_piece_of_baguette_" + warmth());
    food->set_heap_size(num_bread);

    TP->catch_msg(msg);
    say(QCTNAME(TP) + " breaks a piece from " + POSSESS(TP) + " " + QSHORT(TO) + ".\n");

    if (food->move(TP))
    {
	write("You drop it on the ground.\n");
	food->move(ENV(TP));
    }

    return 1;
}

public int
eat_bread(string str)
{
    notify_fail(CAP(query_verb()) + " what?\n");
    if (!strlen(str))
	return 0;

    if (!parse_command(str, TP, 
    "[the] 'baguette' / 'loaf' / 'bread' [of] [bread]"))
	return 0;

    notify_fail("You will have to break a piece of bread from "+
	"the baguette before you can eat it.\n");
    return 0;
}

public void
init(void)
{
    ::init();

    add_action(break_bread, "break");
    add_action(break_bread, "tear");
    add_action(eat_bread,   "eat");
}
