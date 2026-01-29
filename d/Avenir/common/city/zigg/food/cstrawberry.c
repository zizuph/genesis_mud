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
	ob->set_flavors(({"ripe strawberries", "chocolate",}));
	ob->reset_timer();
    }
    else
    {
	ob = clone_object(ZIG_FOOD +"candy_lips.c");
	ob->set_flavors(({"ripe strawberries", "chocolate",}));
	ob->move(tp, 1);
    }

    return 1;
}

public void
special_effect(int amnt)
{
    write("As you eat the "+ (amnt > 1 ? plural_short() : singular_short()) +
	", the thin, rich chocolate shell cracks into tiny pieces, which melt "+
	"in your mouth, rich and bitter-sweet. The flesh of the fruit is "+
	"ripe and sweet, flooding your mouth with the light, sensual flavor "+
	"of strawberries.\n");

    get_candy_lips(TP);
}

public void
hook_smelled(string str)
{
    write("It has a warm, chocolate fragrance with fainter, fruity notes.\n");
}

public void
create_food(void)
{
    setuid();
    seteuid(getuid());

    set_name(({"strawberry", "candy", "chocolate", "fruit"}));
    set_pname(({"strawberries", "candies", "chocolates"}));
    set_short("chocolate-dipped strawberry");
    set_pshort("chocolate-dipped strawberries");
    set_adj(({"rich", "chocolate", "dipped", "smooth", "shiny", "dark",
	"chocolate-dipped", "sweet"}));
    set_long("A ripe, red strawberry has been dipped in smooth, dark "+
	"chocolate and left to dry into a shiny, hard shell. A favored "+
	"treat shared by lovers, these strawberries are a popular "+
	"indulgence within the Ziggurat of Sybarus.\n");

    set_amount(30);

    current = food_amount;
    portion = food_amount / size;

    add_prop(HEAP_S_UNIQUE_ID,
	"zigg:food:strawberries:chocolate");
	
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

	write("You nibble the "+ singular_short() + how[1] +
	  ", your teeth cracking small pieces off the chocolate shell "+
	  "and revealing more of the ripe, red fruit beneath.\n");
	say(QCTNAME(TP)+ " nibbles on "+ HIS(TP) +" "+ singular_short() +
	  how[1] +".\n");
	break;

    case "bite":

	if (!try_to_eat(4))
	    return 1;

	if (how[1] == NO_DEFAULT_ADVERB_WITH_SPACE)
	    how[1] = ADD_SPACE_TO_ADVERB("messily");

	write("You bite"+ how[1] +" into the "+ singular_short() +
	  ", cracking the thin, hard chocolate shell and biting through "+
	  "the ripe red flesh of the fruit beneath. The flavor of the "+
	  "sweet strawberry and decadent dark chocolate is almost sinfully "+
	  "good.\n");
	say(QCTNAME(TP) +" bites "+ HIS(TP) +" "+ singular_short() +how[1] +
	  " in half.\n");
	get_candy_lips(TP);	  
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
	        ", tasting the chocolate shell and the fainter, tanalizing "+
		"taste of strawberry.\n");
	    say(QCTNAME(TP) +" licks "+ HIS(TP) +" "+
	      singular_short() + how[1] +".\n");
	}

	break;

    case "savor":
    case "savour":

	if (!try_to_eat(4))
	    return 1;

	if (how[1] == NO_DEFAULT_ADVERB_WITH_SPACE)
	    how[1] = ADD_SPACE_TO_ADVERB("slowly");

	write("You"+ how[1] +" chew a bite of your "+ singular_short() +
	  " delighting in the taste of rich, dark chocolate as it cracks "+
	  "under your teeth, and the seductive flavor of strawberries as you "+
	  "savor the ripe, red flesh with an intensity that feels almost "+
	  one_of_list(({"naughty", "wicked", "indecent", "shameless",
	  "wanton"})) +".\n");
	say(QCTNAME(TP) +" savours a bite of "+ HIS(TP) +" "+
	  singular_short() +", chewing it"+ how[1] +" as "+ HE(TP) +
	  " closes "+ HIS(TP) +" eyes and goes mmmm....\n");

	get_candy_lips(TP);
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
