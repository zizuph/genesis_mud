// -*-C++-*-
// file name:
// creator(s):
// last update:
// purpose:
// note:
// bug(s):
// to-do:

inherit "/std/food";
inherit "/lib/commands";

#include <composite.h>
#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include <adverbs.h>
#include "zigg.h"

private static int current, portion, size = 10;

public void
special_effect(int amnt)
{
    write("Sweet nectar floods your mouth as you eat the "+ (amnt > 1 ?
	plural_short() : singular_short()) +".\n");
}

public void
hook_smelled(string str)
{
    write("It smells ripe and warm and sweet.\n");
}

public void
create_food(void)
{
    set_name(({"peach", "fruit",}));
    set_pname(({"peaches", "fruits",}));
    set_short("heavy ripe peach");
    set_pshort("heavy ripe peaches");
    set_adj(({"heavy","sweet","juicy","peach","pink", "rosy", "rose-kissed",
	"silver-fuzzed", "golden", "ripe", "rose-blushed", "velvety",
	"succulent"}));
    set_long("The round fruit's ripe, succulent flesh makes it heavy for its "+
	"size. It looks juicy and sweet with "+ one_of_list(({
	"velvety, rose-blushed, golden", "pink, silver-fuzzed",
	"velvety, rose-kissed, peach"}))+ " skin.\n");

    set_amount(50);

    current = food_amount;
    portion = food_amount / size;

    add_prop(HEAP_S_UNIQUE_ID,
	"zigg:food:peaches");
}

public nomask int
is_zig_food(void)         { return 1; }

public void
remove_food(void)
{
    current = food_amount;
    ::remove_food();
}

/*
 * int amnt = # of portions to try to eat.
 *            0 == try to eat all remaining.
 */
private int
try_to_eat(int amnt)
{
    int val = (amnt ? (amnt * portion) : current);

    if (!TP->eat_food(val))
    {
	write("The " + singular_short() + " is too much for you.\n");
	return 0;
    }

    if (val > current)
    {
	int num = num_heap();

	special_effect(1);
	current = food_amount;
	set_heap_size(num - 1);
	return 0;
    }

    current -= val;

    return 1;
}

public int
do_savour(string str)
{
    object obj, *obs;
    string *how;

    how = parse_adverb_with_space(str, NO_DEFAULT_ADVERB, 1);

    if (!strlen(how[0]))
	return NF(CAP(query_verb()) +" what?\n");

    obs = filter(all_inventory(TP), is_zig_food);

    if (!parse_command(how[0], obs, "[on] [the] [my] %o", obj) ||
	(obj != TO))
    {
	notify_fail(CAP(query_verb()) +" what?\n");
	return 0;
    }

    if (current <= portion)
    {
	int num = num_heap();

	if (!try_to_eat(0))
	    return 1;

	special_effect(1);
	current = food_amount;
	set_heap_size(num - 1);
	return 1;
    }

    switch(query_verb())
    {
    case "nibble":

	if (!try_to_eat(1))
	    return 1;

	if (how[1] == NO_DEFAULT_ADVERB_WITH_SPACE)
	    how[1] = ADD_SPACE_TO_ADVERB("playfully");

	write("You nibble the "+ singular_short() + how[1] +
	  ", your teeth nipping at the fuzzy skin.\n");
	say(QCTNAME(TP)+ " nibbles on "+ HIS(TP) +" "+ singular_short() +
	  how[1] +".\n");
	break;

    case "taste":

	if (!try_to_eat(1))
	    return 1;

	if (how[1] == NO_DEFAULT_ADVERB_WITH_SPACE)
	    how[1] = ADD_SPACE_TO_ADVERB("gingerly");

	write("You try to take a tiny taste of the "+ singular_short() +
	  ", biting it"+ how[1] +", but sweet peach juice runs down "+
	  "your hand and chin. \n");
	say(QCTNAME(TP) +" tries to take a tiny bite of "+ HIS(TP) +" "+
	  singular_short() + ", but peach juice fountains down "+ HIS(TP) +
	  " hand and chin.\n");
	break;

    case "bite":

	if (!try_to_eat(3))
	    return 1;

	if (how[1] == NO_DEFAULT_ADVERB_WITH_SPACE)
	    how[1] = ADD_SPACE_TO_ADVERB("deeply");

	write("You bite"+ how[1] +" into the "+ singular_short() +
	  ", using your lips and tongue to capture the sweet juice as it "+
	  "runs from the fruit.\n");
	say(QCTNAME(TP) +" bites"+ how[1] +" into "+ HIS(TP) +" "+
	  singular_short() +".\n");
	break;

    case "lick":

	if (current != food_amount)
	    str = "";

	if (how[1] == NO_DEFAULT_ADVERB_WITH_SPACE)
	    how[1] = ADD_SPACE_TO_ADVERB("gently");

	if (strlen(str))
	{
	    write("You"+ how[1] +" lick the "+ singular_short() +
		", the fuzzy skin prickling your tongue.\n");
	    say(QCTNAME(TP) +" licks "+ HIS(TP) +" "+
		singular_short() + how[1] +".\n");
	}
	else
	{
	    write("You"+ how[1] +" lick the drops of sweet juice clinging "+
		"to your "+ singular_short() +".\n");
	    say(QCTNAME(TP) + how[1] +" licks the droplets of juice "+
 		"clinging to "+ HIS(TP) +" "+ singular_short() +".\n");
	}
	break;

    case "savor":
    case "savour":

	if (!try_to_eat(2))
	    return 1;

	if (how[1] == NO_DEFAULT_ADVERB_WITH_SPACE)
	    how[1] = ADD_SPACE_TO_ADVERB("slowly");

	write("You"+ how[1] +" chew a bite of your "+ singular_short() +
	  " savouring the sweet flavor.\n");
	say(QCTNAME(TP) +" savours a bite of "+ HIS(TP) +" "+
	  singular_short() +", chewing it"+ how[1] +".\n");
	break;
    }

    return 1;
}

public void
init(void)
{
    ::init();

    if (ENV() != TP)
	return;

    add_action( do_savour, "savour" );
    add_action( do_savour, "savor"  );
    add_action( do_savour, "nibble" );
    add_action( do_savour, "bite"   );
    add_action( do_savour, "taste"  );
    add_action( do_savour, "lick"  );
}

public string
stat_object(void)
{
    return ::stat_object() +
	"Unique ID: "+ query_prop(HEAP_S_UNIQUE_ID) + "\n";
}
