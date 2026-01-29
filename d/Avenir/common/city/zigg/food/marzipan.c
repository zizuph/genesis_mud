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

private static mapping treat = ([
"mouse" : ({
	"light brown",
	([
	    "nose" : 1,
	    "ear"  : 2,
	    "paw"  : 2,
	    "foot" : 2,
	    "tail" : 1,
	    "head" : 1,
	]),
	"It is a sweet light brown mouse with big round ears and large goofy "+
	"eyes. Complete with a thin marzipan tail, it is almost too cute "+
	"to eat, but too delicious not to.\n", 14
	}),
"frog" : ({
	"green",
	([
	    "leg"  : 2,
	    "arm"  : 2,
	    "head" : 1,
	]),
	"It is an adorably grotesque frog sculpted out of marzipan. Big "+
	"staring eyes sit atop a wide-mouthed head. Its green legs appear "+
	"ready to hop. Its little body is small enough to nestle into "+
	"the palm of your hand.\n", 10
	}),
"spider" : ({
	"black",
	([
	    "leg" : 8,
	]),
	"A round black body is formed out of marzipan and surrounded by "+
	"eight sculpted legs. Two silly eyes and a little smiling mouth "+
	"personifies the arachnid, taking away from any sort of realism "+
	"but making it much more palatable to squeamish appetites.\n", 18
	}),
"snake" : ({
	"green",
	([
	    "head"   : 1,
	    "tongue" : 1
	]),
	"A long coiled rope of marzipan has been colored a vibrant green and  "+
	"scored with a scale-like pattern. A pink, forked tongue sticks "+
	"out of the candy snake's mouth and tiny, painted eyes decorate "+
	"each side of its head.\n", 12
	}),
"aglyna" : ({
	"purple yellow",
	([
	    "nose" : 1,
	    "wing" : 2,
	    "foot" : 2,
	    "tail" : 1,
	    "head" : 1,
	]),
	"The dimpled marzipan scales are colored purple and its soft belly "+
	"is yellow as are its talons, making this usually fearsome creature "+
	"appear cute and cheerful. The bat-like wings are tucked close to "+
	"the body and formed out of thin, folded sheets of marzipan. Large "+
	"eyes are placed on either side of its wedge-shaped head.\n", 16
	}),
"heart" : ({
	"red",
	([]),
	"A thin sheet of marzipan has been cut into a pretty red "+
	"heart. It is a simple, sweet treat.\n", 8
	}),
"leaf" : ({
	"orange",
	([]),
	"A thin sheet of marzipan has been cut into a pretty orange "+
	"heart-shaped leaf with red veins. It is a lovely, sweet treat "+
	"that looks just like a kesoit tree leaf.\n", 8
	}),
"mushroom" : ({
	"purple white",
	([]),
	"Sweet, clay-like marzipan is molded to form a delicious, surreal "+
	"mushroom with a bumpy, purple cap. and short, white stalk.\n", 8
	}),
"orange" : ({
	"orange",
	([]),
	"A small orange ball of marzipan with a slightly dimpled surface "+
	"and a tiny green leaf. It looks just like a tiny little orange.\n",
	8
	}),
"grape bunch" : ({
	"purple",
	([
	    "grape" : 10
	]),
	"Tiny purple globes of marzipan are clustered together to form "+
	"a tasty bunch of miniature grapes.\n", 10
	}),
"strawberry" : ({
	"red",
	([]),
	"A heart-shaped blob of marzipan has been colored a deep red color "+
	"and dotted with tiny black speckles. A leafy stem of green "+
	"marzipan has been added to the top.\n", 8
	}),
]);

private static string kind = one_of_list(m_indices(treat));
private static int current, portion, size = treat[kind][3];

private void
config_treat(string what)
{
    if (strlen(what))
    {
	remove_name(kind);
	remove_adj(explode(treat[kind][0], " "));

	kind = what;
    }

    set_name(kind);
    set_short("marzipan "+ kind);
    set_long(treat[kind][2]);
    set_adj(explode(treat[kind][0], " "));

    add_prop(HEAP_S_UNIQUE_ID,
	"zigg:candy:marzipan:" + kind);
}

public void
create_food(void)
{
    setuid();
    seteuid(getuid());

    set_name(({ "marzipan", "treat", "candy" }));
    add_adj("marzipan");

    config_treat(kind);

    set_amount(40);

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
	ob->set_flavors(({"sugar", "almond"}));
	ob->reset_timer();
    }
    else
    {
	ob = clone_object(ZIG_FOOD +"candy_lips");
	ob->set_flavors(({"sugar", "almond"}));
	ob->move(tp, 1);
    }

    return 1;
}

public void
hook_smelled(string str)
{
    write("An extremely sweet, nutty aroma greets your senses.\n");
}

public void
special_effect(int amnt)
{
    write("The marzipan is extremely sweet with a light, nutty taste "+
	"and soft, doughy texture which you slowly consume.\n");

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
    string *how, flavor, loc;

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

    if (m_sizeof(treat[kind][1]) > 0)
	loc = one_of_list(m_indices(treat[kind][1]));
    else
	loc = "piece";

    switch(query_verb())
    {
    case "taste":
    case "nibble":

	if (!try_to_eat(1))
	    return 1;

	if (how[1] == NO_DEFAULT_ADVERB_WITH_SPACE)
	    how[1] = ADD_SPACE_TO_ADVERB("lightly");

	write("You nibble on your "+ singular_short() + how[1] +
	    ", nipping off a perfect sized taste of the doughy "+
	    "confection to enjoy the almond flavor without being"+
	    " overwhelmed by the sweetness.\n");
	say(QCTNAME(TP)+ " nibbles on "+ HIS(TP) +" "+ singular_short() +
	    how[1] +".\n");
	break;

    case "lick":

	if (how[1] == NO_DEFAULT_ADVERB_WITH_SPACE)
	    how[1] = ADD_SPACE_TO_ADVERB("delicately");

	write("You"+ how[1] +" lick the "+ singular_short() +". The "+
	    "smooth, clay-like confection has a nutty, sweet taste.\n");
	say(QCTNAME(TP) +" licks "+ HIS(TP) +" "+
	     singular_short() + how[1] +".\n");

	break;

    case "savor":
    case "savour":
    case "bite":

	if (!try_to_eat(2))
	    return 1;

	if (how[1] == NO_DEFAULT_ADVERB_WITH_SPACE)
	    how[1] = NO_ADVERB;

	if (treat[kind][1][loc] == 1)
	{
	    m_delkey(treat[kind][1], loc);
	    loc = "the " + loc;
	}
	else
	{
	    treat[kind][1][loc] -= 1;
	    loc = LANG_ADDART(loc);
	}

	write("You"+ how[1] +" bite "+ loc +" off the "+
	    singular_short() +" and slowly chew the doughy, sweet "+
	    "morsel, savouring the rich taste of almonds.\n");
	say(QCTNAME(TP) + how[1] +" bites "+ loc +" off "+ HIS(TP) +
	    " "+ singular_short() +" and chews it savouringly.\n");

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

    config_treat(what);
}

public string
query_kind(void)	{ return kind; }

public void
set_kind(string str)
{
    if (treat[str])
	config_treat(str);
    else
	write("Choose from: "+ COMPOSITE_WORDS(m_indices(treat)) +".\n");
}

public void
config_split(int num, object orig)
{
    ::config_split(num, orig);
    config_treat(orig->query_kind());
}

public string
stat_object(void)
{
    return ::stat_object() +
	"Unique ID: "+ query_prop(HEAP_S_UNIQUE_ID) + "\n";
}
