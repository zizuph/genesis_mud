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
	ob->set_flavors(({"sweet orange", "candy oranges"}));
	ob->reset_timer();
    }
    else
    {
	ob = clone_object(ZIG_FOOD +"candy_lips.c");
	ob->set_flavors(({"sweet orange", "candy oranges"}));
	ob->move(tp, 1);
    }

    return 1;
}

public void
special_effect(int amnt)
{
    write("Sticky, sugary coating dissolves away, leaving a sweet, rather "+
	"chewy and intensely orange flavored treat that you quickly finish "+
	"off.\n");

    get_candy_lips(TP);
}

public void
hook_smelled(string str)
{
    write("It has a wonderfully sweet, citrus smell.\n");
}

public void
create_food(void)
{
    setuid();
    seteuid(getuid());

    set_name(({"orange", "fruit", "blood orange", "slice", "candy", "fruit"}));
    set_pname(({"oranges", "fruits", "blood oranges", "slices", "candies"}));
    set_short("candied blood orange");
    set_pshort("candied blood oranges");
    set_adj(({"blood","sweet","red","orange","candied", "honied",}));
    set_long("A sweet blood orange has been sliced so thin light seems to "+
	"glow through the segmented crimson flesh. The slices have been "+
	"cooked in a sugary syrup until the white pith surrounding the "+
	"segments turned clear and then cooled, leaving a sticky, sweet "+
	"coating.\n");

    set_amount(50);

    current = food_amount;
    portion = food_amount / size;

    add_prop(HEAP_S_UNIQUE_ID,
	"zigg:food:oranges:blood");

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

    switch(query_verb())
    {
    case "nibble":

	if (!try_to_eat(2))
	    return 1;

	if (how[1] == NO_DEFAULT_ADVERB_WITH_SPACE)
	    how[1] = ADD_SPACE_TO_ADVERB("lightly");

	write("You nibble the edge of your "+ singular_short() + how[1] +
	  ", tasting the slightly bitter pith beneath the sugary coating.\n");
	say(QCTNAME(TP)+ " nibbles on the edge of "+ HIS(TP) +" "+
	  singular_short() + how[1] +".\n");
	break;

    case "lick":
    case "taste":

	if (how[1] == NO_DEFAULT_ADVERB_WITH_SPACE)
	    how[1] = ADD_SPACE_TO_ADVERB("tentatively");

	write("You take a tiny taste of the "+ singular_short() +
	  ","+ how[1] +" touching your tongue to the sugary coating. "+
	  "It is very sweet and faintly orange tasting.\n");
	say(QCTNAME(TP) + how[1] +" tastes the "+ singular_short() +
	  ", just barely touching it with the tip of "+ HIS(TP) +" tongue.\n");
	break;

    case "bite":

	if (!try_to_eat(5))
	    return 1;

	if (how[1] == NO_DEFAULT_ADVERB_WITH_SPACE)
	    how[1] = NO_ADVERB;

	write("You bite"+ how[1] +" into the crimson flesh of the "+
	  singular_short() +" and smack your sticky lips as you enjoy the "+
	  "intensely sweet, orange taste.\n");
	say(QCTNAME(TP) +" bites"+ how[1] +" into "+ HIS(TP) +" "+
	  singular_short() +", then smacks "+ HIS(TP) +" sticky, sugar-"+
	  "coated lips.\n");
	get_candy_lips(TP);
	break;

    case "savor":
    case "savour":

	if (!try_to_eat(3))
	    return 1;

	if (how[1] == NO_DEFAULT_ADVERB_WITH_SPACE)
	    how[1] = ADD_SPACE_TO_ADVERB("slowly");

	write("You"+ how[1] +" chew a bite of your "+ singular_short() +
	  " savouring the sticky, orange sweetness of the vibrant, red fruit.\n");
	say(QCTNAME(TP) +" savours a bite of "+ HIS(TP) +" "+
	  singular_short() +", chewing it"+ how[1] +".\n");
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
