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

private static int current, portion, size = 10;

private static mapping candy = ([
"butterscotch button" : ({
	"dark yellow", "warm and buttery sugar", ({ "butterscotch" })
	}),
"lemon drop" : ({
	"bright yellow", "sugar sweetened lemon", ({ "lemon candy" })
	}),
"cinnamon button" : ({
	"bright red", "fiery cinnamon", ({ "cinnamon" })
	}),
"peppermint drop" : ({
	"white", "cool peppermint", ({ "peppermint" })
	}),
"honey drop" : ({
	"pale gold", "golden honey", ({ "honey" })
	}),
]);

private static string kind = one_of_list(m_indices(candy));


private void
config_candy(string what)
{
    string *arr = explode(kind, " ");

    if (strlen(what))
    {
	remove_adj(arr[0]);
	remove_name(arr[0]);
	remove_name(arr[1]);

	remove_adj(explode(candy[kind][0], " "));

	kind = what;
	arr = explode(kind, " ");
    }

    set_adj(arr[0]);
    add_adj(explode(candy[kind][0], " "));

    set_name(arr[1]);
    add_name(arr[0]);
    set_short(kind);
    set_long("It is a small, round, hard candy which has been colored "+
	candy[kind][0] +".\n");

    add_prop(HEAP_S_UNIQUE_ID,
	"zigg:candy:drops:" + kind);
}

public void
create_food(void)
{
    setuid();
    seteuid(getuid());

    set_adj("hard");
    set_name(({ "candy", "disc" }));

    config_candy("");

    set_amount(20);

    current = food_amount;
    portion = food_amount / size;
}

public int
get_candy_lips(object tp)
{
    object ob = present("Zig::Cbreath", tp);

    if (objectp(ob))
    {
	ob->set_flavors(candy[kind][2]);
	ob->reset_timer();
    }
    else
    {
	ob = clone_object(ZIG_FOOD +"candy_lips");
	ob->set_flavors(candy[kind][2]);
	ob->move(tp, 1);
    }

    return 1;
}
public void
hook_smelled(string str)
{
    write("The scent is faint, but just what you'd expect. It smells like "+
	one_of_list(candy[kind][2]) +".\n");
}

public void
special_effect(int amnt)
{
    write("The candy slowly melts away in your mouth, dissolving into "+
	"a deluge of "+ candy[kind][1] +" flavor.\n");

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

	write("You nibble ineffectually at the hard "+  singular_short()+".\n");
	say(QCTNAME(TP)+ " nibbles on the hard "+ singular_short() +
	    " ineffectually.\n");
	break;

    case "lick":
    case "taste":

	if (!try_to_eat(1))
	    return 1;

	if (how[1] == NO_DEFAULT_ADVERB_WITH_SPACE)
	    how[1] = ADD_SPACE_TO_ADVERB("delicately");

	write("You"+ how[1] +" lick the "+ singular_short() +
	    ", catching a brief taste of "+ candy[kind][1] +".\n");
	say(QCTNAME(TP) + how[1] +" licks "+ HIS(TP) +" "+
	    singular_short() +".\n");

	break;

    case "bite":

	if (!try_to_eat(2))
	    return 1;

	if (how[1] == NO_DEFAULT_ADVERB_WITH_SPACE)
	    how[1] = NO_ADVERB;

	write("You bite"+ how[1] +" into the hard, candy "+ singular_short() +
	    ", making your teeth ache and only managing to break off a "+
	    "tiny chip which quickly dissolves on your tongue, lending "+
	    "a tantalizing taste of "+ candy[kind][1] +".\n");
	say(QCTNAME(TP) +" bites "+ HIS(TP) +" "+ singular_short() +
	    ", producing a loud chipping noise which makes you wonder if "+
	    "it came from the hard candy or "+ HIS(TP) +" teeth.\n");

	get_candy_lips(TP);
	break;

    case "savor":
    case "savour":

	if (!try_to_eat(0))
	    return 1;

	write("You "+ query_verb() +" your "+ singular_short() +
	    ", letting it melt in your mouth, dissolving into a pool of "+
	    candy[kind][1] +" flavor.\n");
	say(QCTNAME(TP) +" savours "+ HIS(TP) +" "+ singular_short() +
	    ", letting it melt in "+ HIS(TP) +" mouth.\n");

	get_candy_lips(TP);
	set_alarm(0.0, 0.0, remove_food);
	break;

    case "suckle":
    case "suck":

	if (!try_to_eat(0))
	    return 1;

	write("You "+ query_verb() +" on your "+ singular_short() +
	    ", letting it melt in your mouth, dissolving into a pool of "+
	    candy[kind][1] +" flavor.\n");
	say(QCTNAME(TP) +" savours "+ HIS(TP) +" "+ singular_short() +
	    ", letting it melt in "+ HIS(TP) +" mouth.\n");

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

    add_action( do_savour, "suck" );
    add_action( do_savour, "suckle"  );
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
    config_candy(what);
}

public string
query_kind(void)	{ return kind; }

public void
set_kind(string str)
{
    if (candy[str])
	config_candy(str);
    else
	write("Choose from: "+ COMPOSITE_WORDS(m_indices(candy)) +".\n");
}

public void
config_split(int num, object orig)
{
    ::config_split(num, orig);
    config_candy(orig->query_kind());
}

public string
stat_object(void)
{
    return ::stat_object() +
	"Unique ID: "+ query_prop(HEAP_S_UNIQUE_ID) + "\n";
}
