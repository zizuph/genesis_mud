// fort donut /d/Avenir/common/outpost/obj/food/donut.c
// creator(s):  Lilith   May 2022
// purpose:     Good food for the brave defenders of the fort
// note:
// revisions:
// to-do:

inherit "/std/food";
inherit "/lib/commands";

#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include <composite.h>
#include <adverbs.h>
#include "/d/Avenir/common/outpost/outpost.h"

private static int current, portion, size = 5;

private static mapping donut = ([
"sprinkle covered donut" : ({
	"pale brown, glazed with white sugar, with little candies "+
    "the size of a grain of rice sprinkled on top", 
	"sweet cake", ({ "brown", "glazed", "sprinkle-covered", "sugar"}),
    ({"glazed donut", "sprinkles"})
	}),
"cinnamon cider donut" : ({
	"made with apple cider and covered in a dark brown sugary powder", 
    "cinnamon and apples", 
    ({ "cinnamon", "apple", "cider", "brown", "powdered sugar" }),
	({"cinnamon donut", "cider donut"})
	}),
"maple bacon donut" : ({
	"brown with a tan maple flavoured glaze and crispy bacon", 
    "maple and bacon",	({ "maple", "bacon" }),
	({"bacon donut", "maple donut"})
	}),
"chocolate frosted donut" : ({
	"light brown and frosted with a topping of chocolate", 
    "chocolate and cake", 
	({ "brown", "frosting", "chocolate", "frosted" }),
	({"frosted donut", "chocolate donut"})
	}),
"sticky honeybun" : ({
	"light brown and sticky with honey", 
    "delicious honey", ({ "honey", "sticky" }),
	({"bun", "honeybun"})
	}),
"sweet airy cruller" : ({
   "a crispy delicate donut with a thin sugar glaze",
   "sugar and choux", ({ "sweet", "glaze", "airy",
   "glazed", "eggy"}), ({"cruller", "sweet cruller", "airy cruller"})
    }),   
]);

private static string kind = one_of_list(m_indices(donut));

public nomask int
is_donut(void)         { return 1; }

	
private void
config_donut(string what)
{
    string *arr = explode(kind, " ");

    if (strlen(what))
    {
	remove_adj(arr[0]);
	remove_name(arr[0]);
	remove_name(arr[1]);

	remove_adj(explode(donut[kind][0], " "));

	kind = what;
	arr = explode(kind, " ");
    }

    set_adj((donut[kind][2]));
	set_name((donut[kind][3]));
 
    set_short(kind);
    set_long("It is a small, fried ring of sweetened dough. "+
	"This one is "+ donut[kind][0] +".\n");

    add_prop(HEAP_S_UNIQUE_ID,"fort:donut:" + kind);
	
}

public void
create_food(void)
{
    setuid();
    seteuid(getuid());

    set_adj(({"fried","soft"}));
    set_name(({ "donut", "ring", "doughnut" }));

    config_donut("");
    set_amount(20);

    current = food_amount;
    portion = food_amount / size;
}

public void
hook_smelled(string str)
{
	string smell = (donut[kind][1]);
    write("The scent is tantalizing. It smells like "+
	smell +".\n");
}

public void
special_effect(int amnt)
{
    write("The "+ singular_short() +" floods your mouth with "+
    donut[kind][1] +" flavor.\n");
}

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

    obs = filter(all_inventory(TP), is_donut);

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

	write("You nibble at the "+  singular_short()+
        ", making a bit of a mess.\n");
	say(QCTNAME(TP)+ " nibbles on the "+ singular_short() +
	    ", making a bit of a mess.\n");
	break;

    case "taste":
    case "sample":
	if (!try_to_eat(1))
	    return 1;

	if (how[1] == NO_DEFAULT_ADVERB_WITH_SPACE)
	    how[1] = ADD_SPACE_TO_ADVERB("carefully");

	write("You"+ how[1] +" sample the "+ singular_short() +
	    ", getting a small taste of "+ donut[kind][1] +".\n");
	say(QCTNAME(TP) + how[1] +" samples "+ POSSESS(TP) +" "+
	    singular_short() +".\n");

	break;

    case "bite":

	if (!try_to_eat(2))
	    return 1;

	if (how[1] == NO_DEFAULT_ADVERB_WITH_SPACE)
	    how[1] = NO_ADVERB;

	write("You bite"+ how[1] +" into the "+ singular_short() +
	    ", breaking off a chunk that floods your mouth with "+
	    "its "+ donut[kind][1] +" flavor.\n");
	say(QCTNAME(TP) +" bites into "+ POSSESS(TP) +" "+ singular_short() +
	    ".\n");
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
    add_action( do_savour, "sample"  );
    add_action( do_savour, "nibble" );
    add_action( do_savour, "bite"   );
    add_action( do_savour, "taste"  );
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
    config_donut(what);
}

public string
query_kind(void)	{ return kind; }

public void
set_kind(string str)
{
    if (donut[str])
	config_donut(str);
    else
	write("Choose from: "+ COMPOSITE_WORDS(m_indices(donut)) +".\n");
}

public void
config_split(int num, object orig)
{
    ::config_split(num, orig);
    config_donut(orig->query_kind());
}

public string
stat_object(void)
{
    return ::stat_object() +
	"Unique ID: "+ query_prop(HEAP_S_UNIQUE_ID) + "\n";
}
