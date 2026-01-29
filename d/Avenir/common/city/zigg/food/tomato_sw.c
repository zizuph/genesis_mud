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
    write("The savoury taste of fresh, milky goat cheese blends perfectly "+
      "with the sweet flavor of ripe tomato as you eat the "+ (amnt > 1 ?
	plural_short() : "dainty " + singular_short()) +".\n");
}

public void
hook_smelled(string str)
{
    write("It smells like fresh toasted bread with a hint of cheese.\n");
}

public void
create_food(void)
{
    set_name(({"sandwich", "morsel", "delicacy"}));
    set_pname(({"sandwiches", "morsels", "delicacies"}));
    set_short("tomato and cheese sandwich");
    set_pshort("tomato and cheese sandwiches");
    set_adj(({"tomato","cheese","tomato and cheese","bite-sized","tiny",
	"dainty"}));
    set_long("Thick slices of ripe red tomato sprinkled with salt and "+
      "pepper lay atop soft Sybarun goat cheese between two dainty "+
      "triangles of lightly toasted bread.\n");

    set_amount(50);

    current = food_amount;
    portion = food_amount / size;

    add_prop(HEAP_S_UNIQUE_ID,
	"zigg:food:tomato:sandwich");
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
    string *how, flavor;

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

    flavor = one_of_list(({
	"flavor of fresh, toasted bread",
	"flavor of soft, milky goat cheese",
	"savory, sweet flavor",
	"flavor of ripe, juicy tomato",
    }));

    switch(query_verb())
    {
    case "nibble":

	if (!try_to_eat(1))
	    return 1;

	if (how[1] == NO_DEFAULT_ADVERB_WITH_SPACE)
	    how[1] = ADD_SPACE_TO_ADVERB("daintily");

	write("You nibble the edge of your "+ singular_short() + how[1] +
	  ", enjoying the "+ flavor +".\n");
	say(QCTNAME(TP)+ " nibbles on "+ HIS(TP) +" "+ singular_short() +
	  how[1] +".\n");
	break;

    case "taste":

	if (!try_to_eat(1))
	    return 1;

	if (how[1] == NO_DEFAULT_ADVERB_WITH_SPACE)
	    how[1] = ADD_SPACE_TO_ADVERB("tentatively");

	write("You take a tiny bite of your "+ singular_short() + how[1] +
	  ", tasting the sweet, savoury flavor of ripe tomato and "+
	  "milky goat cheese. \n");
	say(QCTNAME(TP) +" takes a tiny bite of "+ HIS(TP) +" "+
	  singular_short() + ","+ how[1] +" tasting it.\n");
	break;

    case "bite":

	if (!try_to_eat(3))
	    return 1;

	if (how[1] == NO_DEFAULT_ADVERB_WITH_SPACE)
	    how[1] = NO_ADVERB;

	write("You"+ how[1] +" take a bite of your "+ singular_short() +
	  " enjoying the "+ flavor +".\n");
	say(QCTNAME(TP)+ how[1] +" bites into "+ HIS(TP) +" "+
	  singular_short() + ".\n");
	break;

    case "savor":
    case "savour":

	if (!try_to_eat(2))
	    return 1;

	if (how[1] == NO_DEFAULT_ADVERB_WITH_SPACE)
	    how[1] = ADD_SPACE_TO_ADVERB("slowly");

	write("You"+ how[1] +" chew a bite of your "+ singular_short() +
	  " savouring the "+ flavor +".\n");
	say(QCTNAME(TP) +" savours a bite of "+ HIS(TP) +" "+
	  singular_short() +", chewing"+ how[1] +".\n");
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
}

public string
stat_object(void)
{
    return ::stat_object() +
	"Unique ID: "+ query_prop(HEAP_S_UNIQUE_ID) + "\n";
}
