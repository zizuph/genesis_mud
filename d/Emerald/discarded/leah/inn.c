inherit "/std/room";
inherit "/lib/trade";

#include "/d/Emerald/defs.h"

#define MONEY_TYPES  ({"copper","silver","gold","platinum"})

#define	NUM	sizeof(MONEY_TYPES)

int test;

object make_drink(string name,string adj,string long,int weight,int volume,int soft,int alco);

void
create_room()
{
    object drunk, minstrel;
    int    i;

    set_short("Bar at the Inn");
    set_long("   A large bar stretches along one of the walls. "+
      "This inn is cleaner than most you've been in. Tables and "+
"chairs are gathered around the large stone fireplace. "+
"Shelves of liquor and glasses are visible behind the long bar. "+
	     "On the bar, someone has placed a menu.\n\n");

    add_item("menu", "There seems to be writing on it.\n");

    add_exit(VILLAGE_DIR + "road3", "north");

    add_prop(ROOM_I_INSIDE, 1);
    config_default_trade();

    for (i=0 ; i<2 ; i++) {
	drunk=clone_object(VILLAGE_DIR + "npc/drunk");
	drunk->move(this_object());
    }
        minstrel = clone_object(VILLAGE_DIR + "npc/minstrel");
        minstrel->move( this_object());
}

void
init()
{
    ::init();
    add_action("read", "read");
    add_action("order", "buy");
    add_action("order", "order");
    add_action("test", "test");
}

string
menu_desc()
{
    return "The menu reads:\n\n"+
           "  Beer          - 12  cc\n"+
           "  House Special - 72  cc\n"+
           "  Stout         - 154 cc\n"+
           "  Vodka         - 260 cc\n";
}

int
read(string str)
{
    notify_fail("Read what?");
    if (str != "menu")
	return 0;
    write(menu_desc());
    return 1;
}

int
order(string str)
{
    object drink;
    string name, adj, long, str1, str2, str3, change;
    int    *arr, price, alco, weight, volume, soft, silent, i;

    if (!str) {
	notify_fail("buy what?\n");
	return 0;
    }

    if (sscanf(str, "%s with %s and get %s", str1, str2, str3) != 3) {
	str3 = "";
        if (sscanf(str, "%s with %s", str1, str2) != 2) {
	    str2 = "";
	    str1 = str;
	}
    }

    switch(str1) {
	case "stout":
	    /* Stout, alco is 7% */
	    name = "stout";
	    adj = "imperial";
	    long = "It's very dark but smells like beer.\n";
	    weight = 540;
	    volume = 540;
	    soft = 540;
	    alco = 38;
        price = 154;
	    break;
	case "beer":
	    /* Beer, alco is 4% */
	    name = "beer";
	    adj = "small";
	    long = "It's a small but refreshing beer.\n";
	    weight = 100;
	    volume = 100;
	    soft = 100;
	    alco = 4;
	    price = 12;
	    break;
	case "special":
	    /* Special, alco is 40% */
	    name = "special";
	    adj = "";
	    long = "It's a very special special of the house.\n";
	    weight = 62;
	    volume = 62;
	    soft = 62;
	    alco = 25;
	    price = 72;
	    break;
	case "vodka":
	    /* Vodka, alco is 60%, now that leaves 80% and 96% ;-/ */
	    name = "vodka";
	    adj = "hot";
	    long = "It looks hot and strong indeed.\n";
	    weight = 84;
	    volume = 84;
	    soft = 84;
	    alco = 50;
	    price = 260;
	    break;
	default:
	    notify_fail("I don't understand what you want to buy.\n");
	    return 0;
    }
  
    drink = make_drink(name, adj, long, weight, volume, soft, alco);
    if (!drink) {
	notify_fail("Error in creating drink.\n");
	return 0;
    }

    silent = 0;
    
    if (sizeof(arr = pay(price, this_player(), str2, test, 0, str3, silent)) == 1) {
	if (arr[0] == 1)
	    notify_fail("You have to give me more to choose from, that isn't enough.\n");
        else if(arr[0] == 2)
	    notify_fail("You don't carry that kind of money!!!!!!!!!\n");
	return 0;
    }

    write("You pay " + text(arr[0 .. NUM - 1]) + ".\n");
    if (change = text(arr[NUM .. NUM * 2 - 1]))
	write("You get " + change + ".\n");
    
    if (!test && (drink->move(this_player()))) {
	write("You drop the " + name + " on the floor.\n");
	say(QCTNAME(this_player()) + " drops one " + name + " on the floor.\n");
	drink->move(this_object());
    }
    else if (!test) {
	write("You get your " + name + ".\n");
	say(QCTNAME(this_player()) + " buys a " + name + ".\n");
    }
    else
	say(break_string(QCTNAME(this_player()) +
	    " seems to be estimating something.\n", 78));
    return 1;
}

object
make_drink(string name,string adj,string long,int weight,int volume,int soft,int alco)
{
    object drink;
    
    drink = clone_object("/std/drink");
    drink->set_name(name);

    if (strlen(adj)>0)
	drink->set_adj(adj);

    drink->set_long(long);
    drink->set_soft_amount(soft);
    drink->set_alco_amount(alco);
    drink->add_prop(OBJ_I_WEIGHT, weight);
    drink->add_prop(OBJ_I_VOLUME, volume);
    drink->add_prop(HEAP_S_UNIQUE_ID, long);

    return drink;
}

int
test(string str)
{
    int    i;
    string str1;
    
    notify_fail("Test what?\n");
    if (!str)
	return 0;
 
    if (sscanf(str, "buy %s", str1)) {
	test = 1;
	write("This would be the result of a buy:\n");
	i = order(str1);
	test = 0;
	return i;
    }
}
