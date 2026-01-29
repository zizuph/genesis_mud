// file name:   /d/Avenir/common/outpost/fort3.c
// creator(s):  Kazz    Feb '95
// purpose:     dining hall. sells food and drink.
// note:	    minstrels should be able to perform here.
// last update: Lilith May 2022: Fort Makeover.
 
#pragma strict_types

#include "/d/Avenir/common/outpost/outpost.h"
#include "/d/Avenir/include/defs.h"
#include "/d/Avenir/include/relation.h"

#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include <cmdparse.h>

inherit OUTPOST +"fort_base";
inherit "/lib/trade";

#define MUS_OBJ "/d/Avenir/common/outpost/obj/food/"
#define TYP sizeof(MONEY_TYPES)

#define HELPER      OUTPOST +"mon/dw_guard"
#define HELP_MENU   OUTPOST +"help/dining.txt"
#define HELP_DONUTS OUTPOST +"help/donuts.txt"
#define SEE_WEST   ({ OUTPOST + "fort1", })
#define SEE_SOUTH  ({ OUTPOST + "fort5"})
#define FFOOD_DIR   OUTPOST +"obj/food/"

object host;
int    test;
int    move_item(mixed arg);

string 
south_view()
{
  object *inv, *live, room;
  int i;
 
  inv = ({ });
  for(i = 0; i < sizeof(SEE_SOUTH); i++)
    if((room = find_object(SEE_SOUTH[i])))
      inv += all_inventory(room);
 
  if(sizeof(inv)) 
  {
    live = FILTER_LIVE(inv);
    live = FILTER_CAN_SEE(live, TP);
    if(sizeof(live))
       return " South is the eastern half of the central courtyard, "+   
         "where you can see "+ COMPOSITE_LIVE(live) +".";
  }
  return " Through the southern archway, you can see the limestone "+
         "cobbles of the courtyard glimmering in the light of the Source.";
}

string 
west_view()
{
  object *inv, *live, room;
  int i;
 
  inv = ({ });
  for(i = 0; i < sizeof(SEE_WEST); i++)
    if((room = find_object(SEE_WEST[i])))
      inv += all_inventory(room);
 
  if(sizeof(inv)) 
  {
    live = FILTER_LIVE(inv);
    live = FILTER_CAN_SEE(live, TP);
    if(sizeof(live))
       return " West you can see "+ COMPOSITE_LIVE(live) +
       " milling about in the common area for off-duty guards. ";
  }
  return " The western doorway opens into the common room "+
         "for off-duty guards. ";
}

public string
price_long(void)
{
    cat(HELP_MENU);
	return "";	
}


public string
view_donuts(void)
{
    write("You examine the first display.\n"+
        "You can see a dozen different delicious-looking donuts along "+
        "with a sign:\n");
    say(QCTNAME(TP) + " examines the contents of the donut display.\n");
    cat(HELP_DONUTS);
    return "";
}

string my_long();


public int
host_speak(string msg)
{
    if (host && present(host, this_object()))
    {
        notify_fail("");
        return host->command("say "+ msg);
    }

    return 0;
}

/*
 * Function name: reset_room
 * Description  : Called to clone in a new waitress if she has
 *                disappeared.
 */
public void
reset_fort_room()
{
    if (!host)
    {
        host = clone_object(HELPER);
        host->move_living("xxx", TO);
    }
}

/*
 * Function name: create_room
 * Description  : creator of rooms.
 */
public void
create_fort_room()
{
    setuid();
    seteuid(getuid());
	
    set_short("the Fort Sybarus Dining Hall");
    set_long(my_long);

    add_npc(MON + "dw_guard", 2);	
	room_add_object(OBJ +"table_commonrm", 1);
	room_add_object(OBJ +"table_diningrm", 1);	
	room_add_object(OBJ +"seats/obsidian_bench", 1);
	room_add_object(OBJ +"seats/basalt_bench", 1);	

    add_exit("fort1","west",0);
    add_exit("fort5","south",0);

	add_exit_views();
    add_fort_room();
 
	add_item(({"dwarves", "eating dwarves", "drinking dwarves"}),
        "The dwarves are enjoying a meal in good company.\n" );
	add_item(({"doorway"}),
        "It leads south to the middle of the fort.\n" );
	add_item(({"north wall"}),
        "The north wall is natural, uncarved "+   
        "stone, while the other walls are black stone blocks.\n" );
    set_tell_time(120);
    add_tell("A group of dwarves nearby roar with laughter and "+
        "bang their mugs on the table.\n");
    add_tell("Someone loadly starts telling a tall tale.\n");
    add_tell("An off-duty defender drinks deeply of his mug of cider "+
       "and lets out an impressive belch.\n");
    add_item(({"counter", "bell"}), 
        "A counter made of stone runs parallel to the back wall. "+
        "There is a bell on the counter that you can ring for "+
        "service. There is a display of donuts on the counter, "+
		"as well as a menu.\n");
    add_cmd_item("bell", "ring", "@@do_ring");	  
    add_item(({"pricelist","list","prices","menu","sign","poster"}),
        price_long);
    add_cmd_item(({"pricelist","list","prices","menu","sign"}),
        "read", price_long);	   
    add_item(({"donuts", "doughnuts", "donut display", "display",
	    "doughnut display"}), view_donuts);
  	  
    config_default_trade();    	
    reset_fort_room();

}
/*
 * Function name: my_long
 * Description  : The description of this room.
 * Returns      : (string)description
 */
public string
my_long()
{
    string str;

    str = "This noisy, rumbling room is full of long tables and "+
	      "benches. Dwarves are eating and drinking here, talking "+
	      "loudly and guffawing. The sounds of their merriment "+
          "bounces off of the dark stone walls of the dining hall. "+ 
          "Lamps set into the walls cast a cheerful light "+
          "upon the space. "+
          "Toward the back you can see a counter where food and "+
          "drink can be ordered, with a menu posted above it. ";

    return str + south_view() + west_view() +"\n";
}

/*
 * Function name: order
 * Description  : The order command.
 * Arguments    : The arguments to the command.
 * Returns      : (int)1/0 - My command/ Someone else got to handle this.
 */
public int
order(string str)
{
    string name, str1, str2, str3, kind;
    int *arr, price, num;

    if (!host || !present(host, TO))
    {
        notify_fail("The server isn't here to take your order.\n");
        return 0;
    }

    if (!strlen(str))
    {
        notify_fail("Buy what?\n");
        return 0;
    }

    if (IS_INFIDEL(this_player()))
    {
        tell_object(this_player(), "She frowns furiously "+
            "and waves you away.\n");
        return 1;
    }
    // Check for specified coins and what change to get back 
    if (sscanf(str, "%s with %s and get %s", str1, str2, str3) != 3)
    {
        str3 = "";
        if (sscanf(str, "%s with %s", str1, str2) != 2)
        {
            str2 = "";
            str1 = str;
        }
    }

    if (sscanf(str1, "%d %s", num, str1) != 2)
        num = 1;

    switch(str1)
    {
        case "mug":
		case "cider":
		case "pear cider":
		case "mug of pear cider":
        name = "pear_cider";
        price = num * 50;
         break;
        case "crock":
		case "jug":
		case "goat milk":
		case "milk":
		case "crock of goat milk":
		case "crock of milk":
        name = "goat_milk";
        price = num * 50;
         break;
        case "steak":
		case "phrynos":
		case "phrynos steak":
		case "seared steak":
		case "seared phrynos steak":		
        case "perfectly-seared phrynos steak":
        name = "steak";
        price = num * 500;
		 break;
        case "bowl of hearty goat stew":
		case "bowl of goat stew":
		case "bowl of stew":
        case "stew":
		case "goat stew":
		case "hearty goat stew":
        name = "stew";
        price = num * 400;
         break;
        case "seared sybarun eel rice bowl":
		case "eel":
		case "seared eel":
        case "sybarun eel":
		case "seared sybarun eel":
		case "eel rice bowl":
        case "rice bowl":
		case "sybarun eel rice bowl":
        name = "rice_bowl";
        price = num * 400;
         break;
        case "fish kebob":
		case "skewer of fish kebob":
		case "skewer":
        case "fish":
		case "kebob":
		case "kebab":
        name = "fish_kebob";
        price = num * 300;
         break;
        case "plate of sliced mushrooms in balsamic glaze":
		case "plate of sliced mushrooms in glaze":
		case "plate of sliced mushrooms":
		case "plate of mushrooms":
		case "plate of sliced mushrooms":
		case "glazed mushrooms":
		case "sliced mushrooms":
		case "mushrooms":
        name = "glazed_mushroom";
        price = num * 300;
         break;
        case "salad":
		case "seaweed salad":
		case "seaweed":
        name = "salad";
        price = num * 200;
         break;
        case "ball of soft goat cheese":
		case "ball of soft cheese":
		case "ball of goat cheese":
		case "soft cheese":
		case "goat cheese":
		case "cheese ball":
		case "ball of cheese":
		case "cheese":
        name = "cheese";
        price = num * 300;
         break;
        case "baguette of bread":
        case "bread":
        name = "baguette";      		
        price = num * 250;
         break;
        case "cup of spicy fried grubs":
        case "cup of fried grubs":
        case "cup of spicy grubs":
        case "cup of grubs":
        case "spicy grubs":
        case "fried grubs":
        case "grubs":
        case "cup":
        name = "fried_grubs";        		
        price = num * 200;
         break;

     // Donuts  -- host's choice 		
        case "donut":
        case "ring donut":
        name = "donut";       		
        price = num * 100;
         break;
        case "filled donut":
        name = "donut_filled";       		
        price = num * 144;
         break;	
		
        case "chocolate frosted donut":
        case "chocolate frosted":
        case "frosted donut":
        name = "donut";
        kind = "chocolate frosted donut";        		
        price = num * 100;
         break;	
        case "cinnamon cider donut":
        case "cinnamon cider":
        case "cider donut":
        case "cinnamon donut":
        name = "donut";
        kind = "cinnamon cider donut";        		
        price = num * 100;
		 break;
        case "maple bacon donut":
        case "maple bacon":		
        case "maple donut":
        case "bacon donut":
        name = "donut";
        kind = "maple bacon donut";        		
        price = num * 100;
         break;
        case "sprinkle covered donut":
        case "sprinkle donut":
        case "donut with sprinkles":
        case "sprinkles":
        name = "donut";
        kind = "sprinkle covered donut";        		
        price = num * 100;
		 break;
        case "sticky honeybun":
        case "sticky bun":
        case "sticky donut":
        case "honeybun":
        case "bun":
        name = "donut";
        kind = "sticky honeybun";        		
        price = num * 100;
         break;
        case "sweet airy cruller":
        case "sweet cruller":
        case "airy cruller":
        case "cruller":
        name = "donut";
        kind = "sweet airy cruller";        		
        price = num * 100;
         break;

        case "chocolate cream donut":
        case "chocolate cream":		
        name = "donut_filled";
        kind = "chocolate cream donut";        		
        price = num * 144;
         break;
        case "chocolate custard donut":
        case "chocolate custard":
        kind = "chocolate custard donut";
        name = "donut_filled";
        price = num * 144;
         break;
        case "glazed custard donut":
        case "glazed custard":
        name = "donut_filled";
        kind = "glazed custard donut";        		
        price = num * 144;
         break;
        case "lemon filled donut":
        case "lemon filled":
        name = "donut_filled";
        kind = "lemon filled donut";        		
        price = num * 144;
         break;
        case "raspberry filled donut":
        case "raspberry filled":
        name = "donut_filled";
        kind = "raspberry filled donut";        		
        price = num * 144;
         break;
        case "vanilla cream donut":
        case "vanilla cream":
        kind = "vanilla cream donut";
        name = "donut_filled";        		
        price = num * 144;
         break;
        default:
        notify_fail("I don't understand what you want to buy.\n");
        return 0;
    }

    if (sizeof(arr = pay(price, this_player(), str2, test, 0, str3)) == 1)
        return 0;  /* pay() handles notify_fail() */

    write("You pay " + text(exclude_array(arr, TYP, TYP * 2 - 1)) + ".\n");
    if (text(exclude_array(arr, 0, TYP - 1)))
        write("You get " + text(exclude_array(arr, 0, TYP - 1)) + ".\n");
    return move_item(({name, num, TP, kind}));
}

int
move_item(mixed arg)
{
    object drink, ob;
    string file, name, kind;
    int i, num, inum;

    name = arg[0];
    num = arg[1];
    inum = arg[1];
    ob = arg[2];
	kind = arg[3];

    for (i = 0; i < inum; i++)
    {
        num--;
        file = MUS_OBJ + name;
        drink = clone_object(file);
        if (kind)
	    drink->set_kind(kind);

        if (!test && (drink->move(ob)))
        {
            ob->catch_msg("You order "+ drink->query_short()+ ". "+
                "You drop "+ drink->query_short() +" on the floor.\n");
            say(QCTNAME(ob) + " drops " + drink->query_short() +".\n");
            drink->move(TO);
        } 
        else if (!test) 
        {
            if (num == 0)
            {
                if (arg[1] > 1)
                {
                    ob->catch_msg("You order "+ drink->short() + 
                        " from Mirmarin.\nShe gives you "+ arg[1] +".\n");
                    say(QCTNAME(ob) + " orders " + drink->short() +" from "+
                        "Mirmarin.\nShe gives "+ ob->query_objective() +" "+ 
                        inum +".\n", ob);
                } 
                else 
                {
                    ob->catch_msg("You buy " + drink->short() + " from her.\n");
                    say(QCTNAME(ob) + " buys " + drink->short() + ".\n",
                        ob);
                }
            }
        } 
        else 
        {
            say(QCTNAME(ob) + " seems to be estimating something.\n", ob);
            return 1;
        }
        if (num < 1)
            break;
    }
    if (num > 0)
        set_alarm(1.0,0.0,"move_item", ({name, num, ob}));
    return 1;
}

/*
 * Function name: test
 * Description:   To allow the buyer to see what would happen with change and
 *                payment depending on how the buyer chooses to pay.
 * Arguments:     str - name of drink an possibly description on how to pay and
 *                      get the change
 */
public int
test(string str)
{
    int i = 0;
    string str1 = "";

    if (sscanf(str, "buy %s", str1)) 
    {
        test = 1;
        write("This would be the result of a buy:\n");
        i = order(str1);
        test = 0;
    }
    else
        notify_fail("Test what?\n");
    return i;
}

/*
 * Function name: init
 * Description  : Init the local command set.
 */
public void
init()
{
    ::init();
    add_action(order,    "buy");
    add_action(order,    "order");
}
