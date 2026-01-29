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
#include "/d/Avenir/include/deities.h"

private static int current, portion, size = 10;

public int
get_candy_lips(object tp)
{
    object ob = present("Zig::Cbreath", tp);

    if (objectp(ob))
    {
	ob->set_flavors(({"ripe cherries", "chocolate", "sugary fodant"}));
	ob->reset_timer();
    }
    else
    {
	ob = clone_object(ZIG_FOOD +"candy_lips.c");
	ob->set_flavors(({"ripe cherries", "chocolate", "sugary fodant"}));
	ob->move(tp, 1);
    }

    return 1;
}

public void
special_effect(int amnt)
{
    write("The thin, rich chocolate shell cracks and melts in the warmth of "+
	"your mouth, loosing a flood of sweet fondant syrup before you taste "+
	"the tender, sweet cherry at the core of the "+
	(amnt > 1 ? plural_short() : singular_short()) +".\n");

    get_candy_lips(TP);
}

public void
hook_smelled(string str)
{
    write("It has a warm, chocolate fragrance.\n");
}

public void
create_food(void)
{
    setuid();
    seteuid(getuid());

    set_name(({"cherry", "candy", "chocolate", "cordial", "fruit"}));
    set_pname(({"cherries", "candies", "chocolates", "cordials"}));
    set_short("cherry cordial");
    set_pshort("cherry cordials");
    set_adj(({"rich", "chocolate", "covered", "smooth", "shiny", "small",
	"chocolate-covered", "sweet", "cherry"}));
    set_long("A ripe, red cherry has been rolled in fondant and dipped in "+
	"rich milk chocolate. The natural acids in the cherry have turned "+
	"the fondant into a sweet, liquid syrup, perfectly sealed in its "+
	"chocolate shell, just waiting to be released by anyone seeking "+
	"the delicious fruit prize at the core.\n");

    set_amount(20);

    current = food_amount;
    portion = food_amount / size;

    add_prop(HEAP_S_UNIQUE_ID,
	"zigg:food:cherries:chocolate");
	
    add_prop(SISERA_OFFERING, 1);	
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

    if (!parse_command(how[0], obs, "[on] [the] [my] %o", obj)
    || (obj != TO))
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

	write("You nibble the "+ singular_short() + how[1] +
	  ", your teeth nipping away a tiny bit of chocolate and allowing "+
	  "a small pearl of syrup to slowy bleed through the shell.\n");
	say(QCTNAME(TP)+ " nibbles on "+ HIS(TP) +" "+ singular_short() +
	  how[1] +", taking a tiny taste.\n");
	break;

    case "bite":

	if (!try_to_eat(5))
	    return 1;

	if (how[1] == NO_DEFAULT_ADVERB_WITH_SPACE)
	    how[1] = ADD_SPACE_TO_ADVERB("messily");

	write("You bite"+ how[1] +" into the "+ singular_short() +
	  ", splitting it in half with your teeth and loosing the sticky, "+
	  "sweet syrup within, experiencing the ambrosial blend of buttery "+
	  "milk chocolate, sugary fondant and tender, ripe cherries, even as "+
	  "the liquid threatens to run over your fingers and lips.\n");
	say(QCTNAME(TP) +" bites "+ HIS(TP) +" "+ singular_short() +how[1] +
	  " in half.\n");
	break;

    case "lick":
    case "taste":

	if (current != food_amount)
	    str = "";

	if (how[1] == NO_DEFAULT_ADVERB_WITH_SPACE)
	    how[1] = ADD_SPACE_TO_ADVERB("playfully");

	if (strlen(str))
	{
	    write("You lick the chocolate shell of the "+ singular_short() +
		how[1] +" enjoying a taste of the high quality chocolate.\n");
	    say(QCTNAME(TP) + how[1] +" licks the chocolate shell of "+
		HIS(TP) +" "+ singular_short() +".\n");
	}
	else
	{
	    write("You"+ how[1] +" lick the "+ singular_short() +
	      ", tasting the sweet, slightly cherry flavored syrup and the "+
		"milk chocolate shell.\n");
	    say(QCTNAME(TP) +" licks "+ HIS(TP) +" "+
	      singular_short() + how[1] +".\n");
	}

	get_candy_lips(TP);
	break;

    case "savor":
    case "savour":

	if (!try_to_eat(0))
	    return 1;

	if (how[1] == NO_DEFAULT_ADVERB_WITH_SPACE)
	    how[1] = ADD_SPACE_TO_ADVERB("slowly");

	write("You"+ how[1] +" chew your "+ singular_short() +
	  " savoring the taste of chocolate as it cracks under your teeth, "+
	  "the fleshy texture of the cherry core and the sweet flood of "+
	  "syrup filling your mouth.\n");
	say(QCTNAME(TP) +" savours a bite of "+ HIS(TP) +" "+
	  singular_short() +", chewing it"+ how[1] +".\n");

	get_candy_lips(TP);
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
