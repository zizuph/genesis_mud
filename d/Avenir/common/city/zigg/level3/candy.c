// confectionery
// file name:    candy.c
// creator(s):   Zielia
// last update:
// purpose:
// note:
// bug(s):
// to-do:

#include "zigg.h"

inherit ZIG_ROOM;
inherit "/lib/trade";

#include <language.h>
#include <cmdparse.h>
#include <stdproperties.h>
#include <macros.h>

private static object keeper;

public void
reset_room(void)
{
    if (!keeper)
    {
	keeper = clone_object(ZIG_MON +"cyprian");
	keeper->move_living("M", TO);
    }
}

public int
keeper_speak(string msg)
{
    if (keeper && present(keeper, this_object()))
    {
	notify_fail("");
	return keeper->command("say "+ msg);
    }

    return 0;
}

public void
zig_room(void)
{
    setuid();
    seteuid(getuid());

    set_short("Confectionary");
    set_long("The walls of this cozy candy shop have been covered with "+
	"plaster and painted in soft pastels giving it a lighter look than "+
	"much of the Ziggurat, while still feeling luxurious. In front of "+
	"the back wall, stands a white marble counter swirled with blue "+
	"veins. On top of the counter, a small silver bell sits next to "+
	"an elegant sign displaying a pricelist. Several silver salvers "+
	"display the newest confections for sale while small glass jars "+
	"hold colorful hard candies. Behind the counter, an open doorway "+
	"leads to another room, presumably where the candies are made. "+
	"Along the other walls, bronze sconces capped with tinted "+
	"glass domes cast cheerfully colored lights.\n");

    add_exit("room5", "west", 0);

    add_cmd_item("bell", "ring", "@@do_ring");

    add_item(({"walls","stucco","stucco walls","pastel walls",
	"wall","stucco wall","pastel wall"}),
	"The walls are plastered over with a white stucco mixture "+
	"that lends a textured dimension of varied detail to them. "+
	"They were then painted with soft pastel colors reminiscent of "+
	"seashells. Colorful lights shine upon their pale surface "+
	"adding another layer of color.\n");
    add_item(({"north wall", "south wall"}),
	"The wall is plastered and painted a pale green color.\n");
    add_item(({"east wall"}),
	"The wall behind the counter is plastered over and painted a "+
	"pale yellow color. There is a doorway leading into another room "+
	"in the shop, presumably where the confections are made.\n");
    add_item(({"west wall"}),
	"The wall is plastered and painted a pale green color. An open "+
	"doorway at the center leads out into the galleria.\n");
    add_item(({"sconces","bronze sconces","sconce","bronze sconce"}),
	"The bronzed sconces are spaced regularly along the alabaster "+
	"walls and are capped with colored glass domes.\n");
    add_item(({"cap","caps","domes","glass domes","tinted glass domes",
	"tinted domes", "colored domes", "colored glass domes"}),
	"The tinted glass caps upon the bronze sconces cast "+
	"cheerful, colorful lights on everything in the shop.\n");
    add_item(({"ceiling", "shadows", "colorful shadows"}),
	"The ceiling is plastered over in the same alabaster stucco "+
	"as the walls and painted a pale blue color that compliments the "+
	"veins running through the marble counter.\n");
    add_item(({"floor","ground","tile","tiles","white tiles"}),
	"The floor is covered in pearly white tiles and peachy-pink tiles "+
	"that remind you of the inside of a seashell. The tiles are "+
	"arranged in a checkerboard pattern and the sconces cast "+
	"pools of colored light over their surface.\n");
    add_item(({"counter", "marble counter", "simple counter"}),
	"It seems to be made out of a solid slab of white marble swirled "+
	"with blue lines. Three silver salvers sit upon it along with "+
	"jars of hard candies, a small silver bell and an elegant "+
	"pricelist.\n");
    add_item(({"bell", "small bell"}), "A shiny silver bell. It looks like "+
	"it would ring with a lovely, clear tone.\n");
    add_item(({"salver", "silver salver"}), "Which salver?\n");
    add_item(({"salvers", "silver salvers"}),
	"Three silver salvers display the newest confections for sale "+
	"including truffles, marzipan treats and candied fruits.\n");
    add_item(({"pricelist","list","prices","menu","sign"}),
	"                       Welcome to Viziosamente!                 \n"+
	"                 -----------------------------------         \n\n"+
	"  In the Ziggurat, we are committed to creating not just "+
	"food, but a\n  sensual experience. We hope you'll find pleasure "+
	"in tasting, licking,\n  nibbling, biting, suckling and savouring "+
	"all of our candy temptations.\n\n @@price_long");
    add_cmd_item(({"pricelist","list","prices","menu","sign"}), "read",
	"                       Welcome to Viziosamente!                \n"+
	"                 -----------------------------------         \n\n"+
	"  In the Ziggurat, we are committed to creating not just "+
	"food, but a\n  sensual experience. We hope you'll find pleasure "+
	"in tasting, licking,\n  nibbling, biting, suckling and savouring "+
	"all of our candy temptations.\n\n @@price_long");

    /* special listing add_items */
    add_item(({"truffle", "truffles", "truffle salver", "first salver",
	"indulgences"}), "@@view_truffles");
    add_item(({"marzipan", "marzipan treats", "marzipan salver", "treats",
	"marzipan salvers", "second salver"}), "@@view_marzipan");
    add_item(({"fruits", "candied fruits", "fruits salver",
	"third salver"}), "@@view_fruits");
    add_item(({"jar", "glass jars", "glass jar", "sweets", "hard boiled sweets",
	"jars", "hard candies", "hard candy"}), "@@view_drops");
    add_item(({"candy", "candies", "confection", "confections",
	"temptations"}), "@@view_candy");

    config_default_trade();
    reset_room();
}

public string
price_long(void)
{
    return("\n" +
"  Chocolate Indulgences:    18 silver     Marzipan Treats:       12 silver\n"+
"  -----------------------------------     --------------------------------\n"+
"  Chocolate Truffle                       Marzipan Aglyna                 \n"+
"  Caramel Truffle                         Marzipan Frog                   \n"+
"  Kahve Truffle                           Marzipan Grape Bunch            \n"+
"  Kesoit Fruit Truffle                    Marzipan Heart                  \n"+
"  Lemon Cream Truffle                     Marzipan Leaf                   \n"+
"  Mint Cream Truffle                      Marzipan Mouse                  \n"+
"  Peanut Butter Truffle                   Marzipan Mushroom               \n"+
"  Raspberry Cream Truffle                 Marzipan Orange                 \n"+
"  Strawberry Cream Truffle                Marzipan Snake                  \n"+
"                                          Marzipan Spider                 \n"+
"                                          Marzipan Strawberry             \n"+
"  Hard Boiled Sweets:        4 silver                                     \n"+
"  -----------------------------------                                     \n"+
"  Butterscotch Button                     Candied Fruits:         6 silver\n"+
"  Cinnamon Button                         --------------------------------\n"+
"  Honey Drop                              Candied Blood Orange            \n"+
"  Lemon Drop                              Cherry Cordial                  \n"+
"  Peppermint Drop                         Chocolate-Dipped Strawberry     \n"+
"\n");
}

public int
do_list(string str)
{
    switch(str)
    {
    case "truffle":
    case "truffles":
	write(
	  "    Chocolate Indulgences:        18 silver    \n"+
	  "    ---------------------------------------    \n"+
	  "                                               \n"+
	  "    Chocolate Truffle                          \n"+
	  "    Caramel Truffle                            \n"+
	  "    Kahve Truffle                              \n"+
	  "    Kesoit Fruit Truffle                       \n"+
	  "    Lemon Cream Truffle                        \n"+
	  "    Mint Cream Truffle                         \n"+
	  "    Peanut Butter Truffle                      \n"+
	  "    Raspberry Cream Truffle                    \n"+
	  "    Strawberry Cream Truffle                   \n"+
	  "                                               \n");
	break;

    case "drop":
    case "drops":
    case "sweets":
    case "button":
    case "buttons":
    case "candies":
    case "hard candy":
    case "hard candies":
	write(
	  "    Hard Boiled Sweets:            4 silver    \n"+
	  "    ---------------------------------------    \n"+
	  "                                               \n"+
	  "    Butterscotch Button                        \n"+
	  "    Cinnamon Button                            \n"+
	  "    Honey Drop                                 \n"+
	  "    Lemon Drop                                 \n"+
	  "    Peppermint Drop                            \n"+
	  "                                               \n"+
	  "                                               \n");
	break;

    case "fruit":
    case "fruits":
    case "candied fruit":
    case "candied fruits":
	write(
	  "    Candied Fruits:                6 silver    \n"+
	  "    ---------------------------------------    \n"+
	  "                                               \n"+
	  "    Candied Blood Orange                       \n"+
	  "    Cherry Cordial                             \n"+
	  "    Chocolate-Dipped Strawberry                \n"+
	  "                                               \n");
	break;

    case "treat":
    case "treats":
    case "marzipan":
	write(
	  "    Marzipan Treats:              12 silver    \n"+
	  "    ---------------------------------------    \n"+
	  "                                               \n"+
	  "    Marzipan Aglyna                            \n"+
	  "    Marzipan Frog                              \n"+
	  "    Marzipan Grape Bunch                       \n"+
	  "    Marzipan Heart                             \n"+
	  "    Marzipan Leaf                              \n"+
	  "    Marzipan Mouse                             \n"+
	  "    Marzipan Mushroom                          \n"+
	  "    Marzipan Orange                            \n"+
	  "    Marzipan Snake                             \n"+
	  "    Marzipan Spider                            \n"+
	  "    Marzipan Strawberry                        \n"+
	  "                                               \n");
	break;

    default:
	write(price_long());
	break;
    }

    return 1;
}

public string
view_truffles(void)
{
    write("You examine the first silver salver.\n\n"+
	"You see many small chocolate confections, each shaped like half "+
	"an egg and made of either light or dark chocolate with a bit of "+
	"decoration on top which allows you to match them to the nearby "+
	"sign:\n\n");
    say(QCTNAME(TP) + " examines the contents of the first silver salver.\n");
    do_list("truffles");
    return "";
}

public string
view_marzipan(void)
{
    write("You examine the second silver salver.\n\n"+
	"There are many colorful, carefully crafted creations molded out "+
	"of marzipan as through it were clay. You see comical animals and "+
	"fruits in miniature, simple hearts and pretty leaves. You are "+
	"able to match each creation to its listing on the nearby sign:\n\n");
    say(QCTNAME(TP) + " examines the contents of the second silver salver.\n");
    do_list("marzipan");
    return "";
}

public string
view_fruits(void)
{
    write("You examine the third silver salver.\n\n"+
	"Plump strawberries coated in chocolate with only their stems "+
	"poking out, slices of blood red orange and round chocolate-"+
	"covered cherries fill the salver, easily recognizable even "+
	"without their listings on the nearby sign:\n\n");
    say(QCTNAME(TP) + " examines the contents of the third silver salver.\n");
    do_list("fruits");
    return "";
}

public string
view_drops(void)
{
    write("Bright red and dark yellow candy buttons fill glass jars along "+
	"the back of the counter along with yellow, white and pale gold "+
	"drops. By reading the nearby sign you are able to guess which "+
	"hard candy is which:\n\n");
    say(QCTNAME(TP) + " examines the contents of the glass jars.\n");
    do_list("drops");
    return "";
}

public string
view_candy(void)
{
    write("You examine the confections on display.\n\n"+
	"There are decadent truffles, imaginative marzipan creations, "+
	"flavorful hard candies and succulent fruit based candies. With "+
	"little effort you are able to match each of them with their "+
	"listing on the nearby sign:\n\n");
    say(QCTNAME(TP) + " examines the confections for sale.\n");
    do_list("candy");
    return "";
}

/* Ring bell to summon shop keeper for service if missing. */
public int
do_ring(string str)
{
    write("You ring the bell, the sound resonating throughout the room.\n");
    say(QCTNAME(TP) +" rings the bell on the counter, and the ringing "+
      "resonates throughout the room.\n");

    if (!keeper)
    {
	keeper = clone_object(ZIG_MON +"cyprian");
	keeper->move_living("M", TO);
	keeper->command("emote arrives from the back room, "+
	  "smiling attentively.\n");
	keeper_speak("Ta'haveth. How may I help you?");
    }
    else
    {
	keeper_speak("Ta'haveth. How may I help you?");
    }

    return 1;
}

/*
 * Function name:
 * Description:
 * Arguments:
 * Returns:
 */
private int
move_item(string name, int num, object ob, string kind)
{
    int i, onum;

    onum = num;

    for (i = 0; i < 10; i++)
    {
	object candy = clone_object(ZIG_FOOD + name);

	candy->set_kind(kind);

	if (candy->num_heap())
	{
	    candy->set_heap_size(num);
	    num = 0;
	}
	else
	{
	    num--;
	}

	if (candy->move(ob))
	{
	    ob->catch_tell("You order "+ candy->query_short() +".\n"+
	      "You drop "+ candy->query_short() +" on the floor.\n");
	    say(QCTNAME(ob) +" drops "+ candy->query_short() +".\n");
	    candy->move(TO);
	}
	else if (num == 0)
	{
	    if (onum > 1)
	    {
		ob->catch_tell("You order "+ candy->short() +
		    " from "+ keeper->query_the_name(TP) +".\n"+
		    CAP(HE(keeper)) +" gives you "+ onum +".\n");
		say(QCTNAME(ob) +" orders "+ candy->short() +" from "+
		    QTNAME(keeper) +".\n"+ CAP(HE(keeper)) +" gives "+
		    ob->query_objective() +" "+ onum +".\n", ob);
	    }
	    else
	    {
		ob->catch_tell("You buy "+ candy->short() +" from "+
		    keeper->query_the_name(TP) +".\n");
		say(QCTNAME(ob) +" buys "+ candy->short() +".\n", ob);
	    }
	}

	if (num < 1)
	    break;
    }

    if (num > 0)
	set_alarm(1.0, 0.0, &move_item(name, num, ob, kind));

    return 1;
}

public mixed
order(string str)
{
    int *arr, price, num;
    string name, kind, *arr2;

    if (!keeper || !present(keeper, TO) || keeper->query_no_show())
    {
	return NF("The confectioner isn't here to take your order.\n");
    }

    if (!strlen(str))
    {
	return NF(CAP(query_verb()) +" what?\n");
    }

    if (IS_INFIDEL(this_player()))
    {
	if (keeper_speak("I don't do business with infidels."))
	    return 1;

	notify_fail("This shop does not conduct business with infidels.\n");
	return 0;
    }

    str = lower_case(str);
    if (sscanf(str, "%d %s", num, str) != 2)
	num = 1;

    if (num < 0)
        num = 1;

    if (IN_ARRAY(str, ({ "button", "buttons", "drop", "drops",
	"marzipan", "fruit", "fruits", "truffle", "truffles" })))
    {
	keeper_speak("What kind of "+ str +" did you want?");
	return 0;
    }

    arr2 = explode(str, " ");

    if (IN_ARRAY("aglyna", arr2) || IN_ARRAY("aglynas", arr2))
    {
	name = "marzipan";
	kind = "aglyna";
	price = num * 144;
    }
    else if (IN_ARRAY("butterscotch", arr2))
    {
	name = "drop";
	kind = "butterscotch button";
	price = num * 48;
    }
    else if (IN_ARRAY("caramel", arr2))
    {
	name = "truffle";
	kind = "caramel";
	price = num * 288;
    }
    else if (IN_ARRAY("chocolate", arr2))
    {
	if (IN_ARRAY("strawberry", arr2) || IN_ARRAY("strawberries", arr2))
	{
	    name = "cstrawberry";
	    price = num * 72;
	}
	else
	{
	    name = "truffle";
	    kind = "chocolate";
	    price = num * 144;
	}
    }
    else if (IN_ARRAY("cinnamon", arr2))
    {
	name = "drop";
	kind = "cinnamon button";
	price = num * 48;
    }
    else if (IN_ARRAY("cordial", arr2) || IN_ARRAY("cordials", arr2) ||
	IN_ARRAY("cherry", arr2) || IN_ARRAY("cherries", arr2))
    {
	name = "ccherry";
	price = num * 72;
    }
    else if (IN_ARRAY("honey", arr2))
    {
	name = "drop";
	kind = "honey drop";
	price = num * 48;
    }
    else if (IN_ARRAY("frog", arr2) || IN_ARRAY("frogs", arr2))
    {
	name = "marzipan";
	kind = "frog";
	price = num * 144;
    }
    else if (IN_ARRAY("grape", arr2) || IN_ARRAY("grapes", arr2) ||
	IN_ARRAY("bunch", arr2) || IN_ARRAY("bunches", arr2))
    {
	name = "marzipan";
	kind = "grape bunch";
	price = num * 144;
    }
    else if (IN_ARRAY("heart", arr2) || IN_ARRAY("hearts", arr2))
    {
	name = "marzipan";
	kind = "heart";
	price = num * 144;
    }
    else if (IN_ARRAY("kahve", arr2))
    {
	name = "truffle";
	kind = "kahve";
	price = num * 288;
    }
    else if (IN_ARRAY("kesoit", arr2) || IN_ARRAY("fruit", arr2))
    {
	name = "truffle";
	kind = "kesoit fruit";
	price = num * 288;
    }
    else if (IN_ARRAY("leaf", arr2) || IN_ARRAY("leaves", arr2))
    {
	name = "marzipan";
	kind = "leaf";
	price = num * 144;
    }
    else if (IN_ARRAY("lemon", arr2))
    {
	if (IN_ARRAY("truffle", arr2) || IN_ARRAY("truffles", arr2) ||
	    IN_ARRAY("cream", arr2))
	{
	    name = "truffle";
	    kind = "lemon cream";
	    price = num * 288;
	}
	else
	{
	    name = "drop";
	    kind = "lemon drop";
	    price = num * 48;
	}
    }
    else if (IN_ARRAY("mint", arr2))
    {
	name = "truffle";
	kind = "mint cream";
	price = num * 288;
    }
    else if (IN_ARRAY("mouse", arr2) || IN_ARRAY("mice", arr2))
    {
	name = "marzipan";
	kind = "mouse";
	price = num * 144;
    }
    else if (IN_ARRAY("mushroom", arr2) || IN_ARRAY("mushrooms", arr2))
    {
	name = "marzipan";
	kind = "mushroom";
	price = num * 144;
    }
    else if (IN_ARRAY("orange", arr2) || IN_ARRAY("oranges", arr2))
    {
	if (IN_ARRAY("marzipan", arr2))
	{
	    name = "marzipan";
	    kind = "orange";
	    price = num * 144;
	}
	else
	{
	    name = "borange";
	    price = num * 72;
	}
    }
    else if (IN_ARRAY("peanut", arr2) || IN_ARRAY("butter", arr2))
    {
	name = "truffle";
	kind = "peanut butter";
	price = num * 288;
    }
    else if (IN_ARRAY("peppermint", arr2))
    {
	name = "drop";
	kind = "peppermint drop";
	price = num * 48;
    }
    else if (IN_ARRAY("raspberry", arr2))
    {
	name = "truffle";
	kind = "raspberry cream";
	price = num * 288;
    }
    else if (IN_ARRAY("snake", arr2) || IN_ARRAY("snakes", arr2))
    {
	name = "marzipan";
	kind = "snake";
	price = num * 144;
    }
    else if (IN_ARRAY("spider", arr2) || IN_ARRAY("spiders", arr2))
    {
	name = "marzipan";
	kind = "spider";
	price = num * 144;
    }
    else if (IN_ARRAY("strawberry", arr2) || IN_ARRAY("strawberries", arr2))
    {
	if (IN_ARRAY("marzipan", arr2))
	{
	    name = "marzipan";
	    kind = "stawberrry";
	    price = num * 144;
	}
	else if (IN_ARRAY("truffle", arr2) ||
	    IN_ARRAY("truffles", arr2) || IN_ARRAY("cream", arr2))
	{
	    name = "truffle";
	    kind = "strawberry cream";
	    price = num * 144;
	}
	else
	{
	    name = "cstrawberry";
	    price = num * 72;
	}
    }
    else
    {
	keeper_speak("I don't understand what you want to buy.");
	return 0;
    }

    if (sizeof(arr = pay(price, TP)) == 1)
	return 0;  /* pay() handles notify_fail() */

    string pay_text = text(exclude_array(arr,
	    sizeof(money_types), sizeof(money_types) * 2 - 1));
    string get_text = text(exclude_array(arr, 0,
	    sizeof(money_types) - 1));

    write("You pay "+ pay_text +".\n");
    if (strlen(get_text))
        write("You get "+ get_text +" in return.\n");

    return move_item(name, num, TP, kind);
}

public void
init(void)
{
    ::init();

    add_action( do_list, "list"  );
    add_action(   order, "buy"   );
    add_action(   order, "order" );
}
