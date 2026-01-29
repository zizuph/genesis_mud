// file name:    blackberry.c
// creator(s):   Zielia     Jan. 2007
// last update:
// purpose:      Food for the Ziggurat
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
    write("The tiny black clusters burst in your mouth as you chew, "+
	"filling your mouth with rich, tart flavor as you eat the "+
	(amnt > 1 ? plural_short() : singular_short()) +".\n");
}

public void
hook_smelled(string str)
{
    write("It smells ripe and delicious.\n");
}

public void
create_food(void)
{
    set_name(({"blackberry", "berry", "fruit",}));
    set_pname(({"blackberries", "berries", "fruits",}));
    set_short("shiny ripe blackberry");
    set_pshort("shiny ripe blackberries");
    set_adj(({"black", "shiny", "small", "ripe", "glossy", "sweet"}));
    set_long("The berry is made of many tiny fruits called drupelets, "+
	"clustered together and connected with a greenish-white core. "+
	"The drupelets are round and black with smooth, fragile skin "+
	"and filled with sweet, purple juice.\n");

    set_amount(10);

    current = food_amount;
    portion = food_amount / size;

    add_prop(HEAP_S_UNIQUE_ID,
	"zigg:food:blackberries");
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
	    how[1] = ADD_SPACE_TO_ADVERB("lightly");

	write("You nibble the "+ singular_short() +","+ how[1] +
	  " separating one of the tiny drupelets and biting it off.\n");
	say(QCTNAME(TP)+ " nibbles on "+ HIS(TP) +" "+ singular_short() +
	  how[1] +".\n");
	break;

    case "bite":

	if (!try_to_eat(5))
	    return 1;

	if (how[1] == NO_DEFAULT_ADVERB_WITH_SPACE)
	    how[1] = ADD_SPACE_TO_ADVERB("carefully");

	write("You bite"+ how[1] +" into the "+ singular_short() +
	  ", splitting it in half and bursting several of the tiny round "+
	  "drupelets.\n");
	say(QCTNAME(TP) +" bites "+ HIS(TP) +" "+ singular_short() +how[1] +
	  " in half.\n");
	break;

    case "lick":
    case "taste":

	if (!try_to_eat(1))
	    return 1;

	if (how[1] == NO_DEFAULT_ADVERB_WITH_SPACE)
	    how[1] = NO_ADVERB;

	write("You lick the "+ singular_short() + how[1] +
	    ", your tongue rupturing the fragile skin of the tiny clusters, "+
	    "giving you a taste of the sweet juice inside.\n");
	say(QCTNAME(TP) +" licks "+ HIS(TP) +" "+ singular_short() +".\n");
	break;

    case "savor":
    case "savour":

	if (!try_to_eat(0))
	    return 1;

	if (how[1] == NO_DEFAULT_ADVERB_WITH_SPACE)
	    how[1] = ADD_SPACE_TO_ADVERB("slowly");

	write("You"+ how[1] +" chew your "+ singular_short() +
	  " letting the juicy clusters burst and turn into a sweet "+
	  "pulp.\n");
	say(QCTNAME(TP) +" savours "+ HIS(TP) +" "+
	  singular_short() +", chewing it"+ how[1] +".\n");

	set_alarm(0.0, 0.0, remove_food);
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
