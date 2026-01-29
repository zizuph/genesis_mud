// fort ice cream /d/Avenir/common/outpost/obj/food/ice_cream_cone.c
// creator(s):  Lilith   May-June 2022
// purpose:     Dessert for the brave defenders of the fort
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

private static int current, portion, size = 20;

private static mapping flavor = ([
"vanilla" : ({
	"made with vanilla beans, sugar, and egg yolks blended well and stirred "+
    "until frozen.", "vanilla", 
    ({"vanilla ice cream", "vanilla ice cream cone"}),
	}),
"chocolate" : ({
	"made with melted chocolate stirred into a custard base and frozen.", 
    "chocolate",
	({"chocolate ice cream", "chocolate ice cream cone"})
	}),
"strawberry" : ({
    "made with chopped strawberries stirred into a base of vanilla custard "+
    "and then frozen.",
    "strawberries", 
   ({ "strawberries", "strawberry ice cream",
      "vanilla custard", "strawberry ice cream cone" }),
    }),
"neapolitan" : ({
   "made of three different sections of chocolate, strawberry, and "+
   "vanilla ice cream.",
   "a mix of chocolate, vanilla, and strawberry", 
   ({"neapolitan ice cream", "neapolitan ice cream cone", "chocolate",
   "vanilla", "strawberry"})
    }),      	
"vanilla caramel swirl" : ({
	"made by taking partially-set vanilla ice cream and swirling melted "+
    "caramel into it.", 
	"vanilla and caramel",
    ({"caramel swirl", "caramel", "vanilla caramel swirl ice cream", 
	"vanilla caramel swirl ice cream cone"})
	}),	
"cookies and cream" : ({
	"accomplished by swirling cookie crumbles into a base of white "+ 
    "chocolate ice cream.", "cookies and milk", 
	({ "cookies", "cream", "cookies and cream ice cream",
       "cookies and cream ice cream cone"	}),
	}),
"mint chocolate chip" : ({
	"made with chips of chocolate stirred into minty ice cream.", 
    "chocolate and mint",
	({"mint", "chocolate", "mint chocolate", "chocolate chip",
    "mint chocolate chip ice cream", "mint chocolate chip ice cream cone"})
	}),
"banana" : ({
   "made with a banana puree blended into a vanilla ice cream base.",
   "bananas and vanilla",  
   ({"banana ice cream", "banana ice cream cone"})
    }),   	
"pistachio" : ({
   "made by mixing a puree of pistachios and almonds into a vanilla ice "+
   "cream base and stirring until frozen.",
   "sweet and nutty",  
   ({"pistachio ice cream", "pistachio ice cream cone"})
    }),   
"kahve" : ({
   "made with instensely sweet, creamy sybarun kahve stirred into a "+
   "rich vanilla custard base.",
   "kahve and cream",
   ({"kahve ice cream", "kahve ice cream cone"})
    }),   
"cookie dough" : ({
   "vanilla ice cream with little balls of raw cookie doough stirred in.",
   "cookies",  
   ({"cookie dough ice cream", "cookie dough ice cream cone", 
   "cookie", "dough"})
    }), 
"butter rum" : ({
   "rich vanilla ice cream with butter rum sauce swirled into it.",
   "butter, rum, and vanilla", 
   ({"butter", "rum", "butter rum ice cream", "butter rum ice cream cone"})
    }),    
"white chocolate raspberry swirl" : ({
   "made by swirling raspberry syrup into vanilla ice cream flavoured "+
   "with melted white chocolate.",
   "white chocolate and raspberries",
   ({"white chocolate", "raspberry", "raspberry swirl",
   "white chocolate raspberry swirl ice cream", 
   "white chocolate raspberry swirl ice cream cone"})  
    }),
"chocolate peanut butter swirl" : ({
   "made by swirling peanut butter into chocolate ice cream.",
   "choclate and peanut butter",
   ({"chocolate peanut butter", "peanut butter", "peanut butter swirl",
   "chocolate peanut butter swirl ice cream", 
   "chocolate peanut butter swirl ice cream cone"})  
    }),
	

]);

private static string kind = one_of_list(m_indices(flavor));

public nomask int
is_dessert(void)         { return 1; }

	
private void
config_flavor(string what)
{
    string *arr = explode(kind, " ");

    if (strlen(what))
    {
/*		
	remove_adj(arr[0]);
	remove_name(arr[0]);
	remove_name(arr[1]);

	remove_adj(explode(flavor[kind][0], " "));
*/
	kind = what;
	arr = explode(kind, " ");
    }
	
    set_adj(({"ice", "cream"}));
    set_name(({ "ice cream cone", "dessert", "ice cream", "scoop", "cone" }));
    add_adj((flavor[kind][1]));
	add_adj(kind);
	add_adj((flavor[kind][2]));
	add_name(kind);
	add_name((flavor[kind][2]));
    set_short(kind +" ice cream cone");
    set_long("It is a small scoop of "+ kind +" ice cream made from the "+
        "sweetest and creamiest milk of the sybarun goat, resting "+
        "in a cone made of a thin, crispy cookie. "+
    	"This decadent, cold dessert is "+ flavor[kind][0] +
		" It looks so delicious you feel an almost irresistible urge "+
        "to lick it.\n");

    add_prop(HEAP_S_UNIQUE_ID,"fort:flavor:" + kind);
	
	add_item(({"thin cone", "crispy cone", "cookie cone", "cookie"}),
	    "It looks like a thin cookie or pancake was shaped "+
        "into a cone and allowed to harden. It contains a scoop of "+
        kind +" ice cream.\n");

    add_item(({"scoop of "+ kind +" ice cream", "scoop of ice cream"}),
        "This "+ kind +" ice cream is going to melt if you just "+
        "keep looking at it!\n");		
}

public void
create_food(void)
{
    setuid();
    seteuid(getuid());

    config_flavor("");
    set_amount(100);

    current = food_amount;
    portion = food_amount / size;
}

public void
hook_smelled(string str)
{
	string smell = (flavor[kind][1]);
    write("The scent is tantalizing. It smells like "+
	smell +".\n");
}

public void
special_effect(int amnt)
{
    write("The ice cream floods your mouth with "+
    "the taste of "+ flavor[kind][1] +".\n");
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

    obs = filter(all_inventory(TP), is_dessert);

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
    case "lick":
	if (how[1] == NO_DEFAULT_ADVERB_WITH_SPACE)
	    how[1] = ADD_SPACE_TO_ADVERB("carefully");

	write("You"+ how[1] +" run your tongue along the scoop of "+ kind +
        " ice cream, delighting your taste buds.\n");
	say(QCTNAME(TP)+ " runs "+ POSSESS(TP) +" tongue along "+
       "the scoop "+ kind +" ice cream.\n");
	if (!try_to_eat(1))
	    return 1;	   
	break;
	
    case "nibble":
	write("You nibble at the "+  singular_short()+
        ", smearing it on your lips.\n");
	say(QCTNAME(TP)+ " nibbles on the "+ singular_short() +
	    ", smearing it on "+ POSSESS(TP) +" lips.\n");
	break;

    case "taste":
    case "sample":
	if (!try_to_eat(1))
	    return 1;

	if (how[1] == NO_DEFAULT_ADVERB_WITH_SPACE)
	    how[1] = ADD_SPACE_TO_ADVERB("carefully");

	write("You"+ how[1] +" sample the "+ singular_short() +
	    ", getting a small taste of its decadent sweetness.\n"); 
	say(QCTNAME(TP) + how[1] +" samples "+ POSSESS(TP) +" "+
	    singular_short() +".\n");

	break;

    case "bite":

	if (!try_to_eat(2))
	    return 1;
	if (how[1] == NO_DEFAULT_ADVERB_WITH_SPACE)
	    how[1] = NO_ADVERB;

	write("You bite"+ how[1] +" into the "+ singular_short() +
	    ", relishing its sweet richness.\n");
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
    add_action( do_savour, "lick"  );
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
    config_flavor(what);
}

public string
query_kind(void)	{ return kind; }

public void
set_kind(string str)
{
    if (flavor[str])
	config_flavor(str);
    else
	write("Choose from: "+ COMPOSITE_WORDS(m_indices(flavor)) +".\n");
}

public void
config_split(int num, object orig)
{
    ::config_split(num, orig);
    config_flavor(orig->query_kind());
}

public string
stat_object(void)
{
    return ::stat_object() +
	"Unique ID: "+ query_prop(HEAP_S_UNIQUE_ID) + "\n";
}
