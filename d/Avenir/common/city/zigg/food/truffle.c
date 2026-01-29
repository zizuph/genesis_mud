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

#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include <composite.h>
#include <adverbs.h>
#include "zigg.h"
#include "/d/Avenir/include/deities.h"

private static int current, portion, size = 10;

private static mapping truffle = ([
"chocolate" : ({
	"dense chocolate ganache", ({"dark chocolate", "bitter-sweet"}),
	"A velvety smooth, dense ganache center, rich with fresh, whipped "+
	"cream and butter, are thinly coated in dark chocolate, then "+
	"drizzled with lighter, sweeter, milk chocolate.\n",
	({ "chocolate" }), ({ "dark", "chocolate" })
	}),
"raspberry cream" : ({
	"black raspberry cream", ({"dark chocolate", "bitter-sweet"}),
	"A velvety smooth, fresh, black raspberry ganache center, is thinly "+
	"coated in dark chocolate, then drizzled with red chocolate.\n",
	({ "chocolate", "raspberry" }),
	({ "dark", "chocolate", "raspberry", "cream", "raspberry-cream" })
 	 }),
"mint cream" : ({
	"silky mint cream", ({"dark chocolate", "bitter-sweet"}),
	"The perfect treat after a meal, it is filled with silky, white "+
	"mint cream and enrobed in shiny dark chocolate.\n",
	({ "chocolate", "mint" }),
	({ "dark", "chocolate", "mint", "cream", "mint-cream" })
	}),
"lemon cream" : ({
	"light lemon cream", ({"dark chocolate", "bitter-sweet"}),
	"Freshly squeezed lemon juice is infused into a light, creamy "+
	"white chocolate center, enrobed in dark chocolate and topped with "+
	"a sprinkle of lemon sugar.\n", ({ "chocolate", "lemon cream" }),
	({ "dark", "chocolate", "lemon-cream", "lemon", "cream" })
	}),
"strawberry cream" : ({
	"sweet strawberry cream", ({"milk chocolate", "creamy"}),
	"The center is a succulent mix of milk and white chocolate and "+
	"fresh strawberries dipped in rich milk chocolate with a tiny pink "+
	"chocolate bow pipped on the top.\n",
	({ "chocolate", "strawberry cream", "strawberry" }),
	({ "milk", "chocolate", "strawberry-cream", "strawberry", "cream" })
	}),
"caramel" : ({
	"creamy caramel", ({"milk chocolate", "creamy"}),
	"Soft buttery caramel fills creamy, sweet, milk chocolate squares "+
	"and drizzled with melted dark chocolate.\n",
	({ "chocolate", "buttery caramel" }),
	({ "milk", "chocolate", "caramel" })
	}),
"peanut butter" : ({
	"dense peanut butter", ({ "milk chocolate", "creamy" }),
	"Dense, soft peanut butter is smothered in creamy milk chocolate "+
	"and molded into a delectable little cup.\n",
	({ "chocolate", "peanut butter" }),
	({ "milk", "chocolate", "peanut", "butter" })
	}),
"kahve" : ({
	"kahve and chocolate", ({ "milk chocolate", "creamy" }),
	"A delightful combination of kahve mixed with dark and milk "+
	"chocolates create the center of this indulgence. It is then "+
	"dipped in milk chocolate and garnished with kahve bean shavings. "+
	"This truffle flavor is sure to please the avid kahve enthusiast.\n",
	({ "chocolate", "kahve" }), ({ "milk", "chocolate", "kahve" })
	}),
"kesoit fruit" : ({
	"spicy kesoit ganache", ({ "milk chocolate", "creamy" }),
	"Bitter-sweet chocolate ganache is infused with sweet yet picant "+
	"kesoit fruit extract to form a silky smooth center. The spicy "+
	"heat blends remarkably well with the creamy, sweet chocolate "+
	"shell, creating an exciting, exotic taste. The truffle has been "+
	"decorated with drizzles of orange colored chocolate giving it "+
	"a vibrant presentation.\n",
	({ "chocolate", "kesoit fruit", "spicy, sweet fruit" }),
	({ "milk", "chocolate", "kesoit", "fruit",})
	}),
]);

private static string kind = one_of_list(m_indices(truffle));

private void
config_truffle(string what)
{
    if (strlen(what))
    {
	remove_adj(truffle[kind][4]);
	kind = what;
    }

    set_adj(truffle[kind][4]);
    set_short(kind +" truffle");
    set_long(truffle[kind][2]);

    add_prop(HEAP_S_UNIQUE_ID,
	"zigg:candy:truffle:" + kind);
}

public void
create_food(void)
{
    setuid();
    seteuid(getuid());

    set_name(({ "truffle", "candy" }));

    config_truffle("");

    set_amount(20);

    current = food_amount;
    portion = food_amount / size;
    
    add_prop(SISERA_OFFERING, 1);

}

public int
get_candy_lips(object tp)
{
    object ob = present("Zig::Cbreath", tp);

    if (objectp(ob))
    {
	ob->set_flavors(truffle[kind][3]);
	ob->reset_timer();
    }
    else
    {
	ob = clone_object(ZIG_FOOD +"candy_lips");
	ob->set_flavors(truffle[kind][3]);
	ob->move(tp, 1);
    }

    return 1;
}
public void
hook_smelled(string str)
{
    write("The delicious aroma of "+ one_of_list(truffle[kind][3]) +
	" makes your mouth water.\n");
}

public void
special_effect(int amnt)
{
    write("The thin "+ truffle[kind][1][0] +" shell gives way to a "+
	truffle[kind][0] +" center, the flavors blending deliciously in a "+
	"rich, sweet indulgence decadent enough to make you melt with "+
	"pleasure.\n");

    get_candy_lips(TP);
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

	write("You nibble the outside of your "+ singular_short() +
	    how[1] + ", breaking off tiny pieces of the "+
	    truffle[kind][1][1] +" "+ truffle[kind][1][0] +" shell.\n");
	say(QCTNAME(TP)+ " nibbles on the "+ truffle[kind][1][0] +
	  " shell of "+ HIS(TP) +" "+ singular_short() + how[1] +".\n");
	break;

    case "lick":
    case "taste":

	if (current != food_amount)
	    str = "";

	if (how[1] == NO_DEFAULT_ADVERB_WITH_SPACE)
	    how[1] = ADD_SPACE_TO_ADVERB("delicately");

	if (strlen(str))
	{
	    write("You"+ how[1] +" lick the "+ singular_short() +
	      ", enjoying the silky smooth, "+ truffle[kind][1][1] +
	      " "+ truffle[kind][1][0] +".\n");
	    say(QCTNAME(TP) +" licks "+ HIS(TP) +" "+
	      singular_short() + how[1] +".\n");
	}
	else
	{
	    write("You"+ how[1] +" lick the "+ singular_short() +
	      ", partaking of a taste of the decadent, "+
	      truffle[kind][0] + " center.\n");
	    say(QCTNAME(TP) +" licks "+ HIS(TP) +" "+
	      singular_short() + how[1] +".\n");
	}
	break;

    case "bite":

	if (!try_to_eat(5))
	    return 1;

	if (how[1] == NO_DEFAULT_ADVERB_WITH_SPACE)
	    how[1] = NO_ADVERB;

	write("You bite"+ how[1] +" into the "+ singular_short() +
	    " letting your tongue caress the "+ truffle[kind][1][1] +
	    " "+ truffle[kind][1][0] +" outer shell for just a moment "+
	    "before the delicious taste of the "+ truffle[kind][0] +
	    " surprises your tongue.\n");
	say(QCTNAME(TP) +" bites"+ how[1] +" into "+ HIS(TP) +
	    " "+ singular_short() +".\n");

	get_candy_lips(TP);
	break;

    case "savor":
    case "savour":

	if (!try_to_eat(5))
	    return 1;

	write("You savour a bite of your "+ singular_short() +
	    ", letting "+ "the silky "+ truffle[kind][1][1] +
	    " slowly melt on your tongue, blending with the sweet "+
	    truffle[kind][0] +" into a decadent, almost sensual "+
	    "experience.\n");
	say(QCTNAME(TP) +" savours a bite of "+ HIS(TP) +
	    " "+ singular_short() +".\n");

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
    add_action( do_savour, "lick"   );
}

public string
query_recover(void)
{
    return ::query_recover() + "kind:*" + kind + "*";
}

public void
init_recover(string str)
{
    string what;

    ::init_recover(str);
    sscanf(str, "%skind:*%s*%s", str, what, str);
    config_truffle(what);
}

public string
query_kind(void)	{ return kind; }

public void
set_kind(string str)
{
    if (truffle[str])
	config_truffle(str);
    else
	write("Choose from: "+ COMPOSITE_WORDS(m_indices(truffle)) +".\n");
}

public void
config_split(int num, object orig)
{
    ::config_split(num, orig);
    config_truffle(orig->query_kind());
}

public string
stat_object(void)
{
    return ::stat_object() +
	"Unique ID: "+ query_prop(HEAP_S_UNIQUE_ID) + "\n";
}
