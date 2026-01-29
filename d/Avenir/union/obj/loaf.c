#pragma strict_types
inherit "/std/object";

#include <files.h>
#include <macros.h>
#include <language.h>
#include <stdproperties.h>

#include "../defs.h"

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
	return "piping hot";
    case 61 .. 120:
	return "hot";
    case 121 .. 180:
	return "warm";
    case 181 .. 300:
	return "cold";
    default:
	return "stone cold";
    }
}

public string
loaf_short(void)
{
    return warmth() +" loaf of bread";
}

public string
loaf_pshort(void)
{
    return warmth() +" loaves of bread";
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
	str = "There is a bit less than half the loaf left.";
	break;
    case 5:
	str = "Only half the loaf remains.";
	break;
    case 6..7:
	str = "Over half the loaf remains.";
	break;
    case 8..9:
	str = "Only a little bread has been broken from the loaf.";
	break;
    default:
	str = "The loaf is complete and unbroken.";
	break;
    }

    return "It is "+ LANG_ADDART(warmth()) +" loaf of bread, fragrant "+
	"and wholesome. " + str + "\n";
}

public void
create_object()
{
    reset_euid();

    set_name("loaf");
    set_pname("loaves");

    set_long(loaf_long);
    set_short(loaf_short);
    set_pshort(loaf_pshort);

    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VOLUME, 5000);
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
	    "[the] [loaf] [of] [bread]"))
	return 0;

    size--;
    if (!size)
    {
	msg = "You break the remainder of the loaf into two pieces of bread.\n";
	num_bread = 2;
	// remove the loaf after this command has been executed.
	set_alarm(0.0, 0.0, remove_object);
    }
    else
    {
	msg = "You break a piece of bread from the " + QSHORT(TO) + ".\n";
	num_bread = 1;
    }

    food = clone_object(FOOD_OBJECT);
    food->set_name("bread");
    food->add_name("piece");
    food->set_short("piece of " + warmth() + " bread");
    food->set_pshort("pieces of " + warmth() + " bread");
    food->set_adj(warmth());
    food->set_amount(50);
    food->set_long("It is a piece of bread, broken by hand from a loaf.\n");
    food->add_prop(OBJ_I_WEIGHT, 65);
    food->add_prop(OBJ_I_VOLUME, 65);
    food->add_prop(HEAP_S_UNIQUE_ID, "_slice_of_union_" + warmth() + "_bread");
    food->set_heap_size(num_bread);

    TP->catch_msg(msg);
    say(QCTNAME(TP) + " breaks a piece from " + HIS(TP) + " " + QSHORT(TO) + ".\n");

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

    if (!parse_command(str, TP, "[the] 'loaf' / 'bread' [of] [bread]"))
	return 0;

    notify_fail("You would need to first break a piece of bread from "+
	"the loaf before you can eat it.\n");
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
