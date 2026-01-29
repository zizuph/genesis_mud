// The Bazaar Bakery
// file name:    /d/Avenir/common/bazaar/intr/bakery.c
// creator(s):   Triana 
// last update:  Lilith, Aug 1999: updated food and ambiance
//               Kazz, May 1995
// purpose:      Food for the hungry masses :)
// note:        
// bug(s):
// to-do:	

inherit "/std/room";
inherit "/lib/trade";

#include "/d/Avenir/include/defs.h"
#include "/d/Avenir/include/macros.h"
#include "/d/Avenir/include/relation.h"
#include <language.h>
#include <stdproperties.h>
#include <macros.h>
#include <money.h>

#define STAND_DIR "/d/Avenir/common/bazaar/Obj/food/"
#define TYP sizeof(MONEY_TYPES)

object host;     
int    test;

int    move_item(mixed arg);

string price_long();

void
reset_room()
{
    if (!host)
    {
        host = clone_object("/d/Avenir/common/bazaar/NPCS/baker");
        host->move_living("xxx", TO);
    }
}

void
create_room()
{
    set_short("Moody Muffin Bakery");
    set_long("Even without the sign hanging outside, you would know "+
        "this was a bakery by the smell.  The air is warm and moist "+
        "and heavy with the scents of cinnamon and nutmeg and rising "+
        "bread.  The old stone walls are white-washed and lined with "+
        "shelves, each of which is piled high with loaves ranging in "+
        "colour from palest gold to dark brown.  On the gray slate "+
        "floor is a scattering of seeds and a slight dusting of flour."+
        "  In the display counter can be seen a wide array of baked "+
        "goods: pastries, pies, cookies, and the muffins after which "+
        "this establishment is named.  A sign hangs from the ceiling, "+
        "just behind the counter.\n");

    add_item(({"seeds", "flour", "dusting of flour", "slate", 
        "slate floor", "gray slate floor"}), "The gray slate floor "+
        "radiates a small amount of heat.  Flour and seeds have "+
        "fallen from the baked goods onto the floor.\n");
    add_item(({"walls", "wall", "stone walls", "old stone walls"}),
        "These old walls are white-washed stone.\n");
    add_item(({"counter","glass counter","display","display counter", 
        "baked goods"}), 
        "The baked goods artfully displayed inside the glass counter "+
        "are a sampling of the items offered for sale here.\n");
    add_item(({"pricelist","list","prices","menu","sign"}), 
        price_long);
   add_cmd_item(({"pricelist","list","prices","menu","sign"}), 
        "read", price_long);
 
    add_exit("/d/Avenir/common/bazaar/extr/str22.c", "west", 0);

	
	IN;       // Avenir is an undergound domain.
	IN_IN;    // Interior room, no flux msgs, steeds etc.


    config_default_trade();
    reset_room();
}

string
price_long()
{
    return ("Celebrate the Source and Welcome to the Moody Muffin!\n\n"+
        "    Today we are offering the following delicious baked goods:\n"+
        "    Crusty loaf of bread   155 coppers \n"+
        "    Hearty loaf of bread   210 coppers \n"+
        "    Berry muffin            24 coppers \n"+
        "    Buckler muffin          24 coppers \n"+
        "    Elderflower cheesecake  48 coppers \n"+
        "    Bryndon cake            12 coppers \n"+
        "    Savory meat pie        120 coppers \n"+        
        " \n");
} 



/*    
 * Function name: 
 * Description:   
 * Arguments:     
 * Returns: 	  
 */
mixed
order(string str)
{
    string name, str1, str2, str3;
    int *arr, price, num;

    notify_fail("The baker isn't here to take your order.\n");
    if (!host || !present(host, TO))
        return 0;

    notify_fail("Buy what?\n");
    if (!str)
        return 0;

    if (IS_INFIDEL(this_player()))
    {
        tell_object(this_player(), "The baker frowns furiously "+
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
        case "hearty bread":
        case "hearty loaf":
        case "hearty loaves":
        case "hearty loaf of bread":
        case "hearty bread loaf":
        case "hearty bread loaves":
            name = "hearty_bread";
            price = num * 155;
            break;
        case "crusty bread":
        case "crusty loaf":
        case "crusty loaves":
        case "crusty loaf of bread":
        case "crusty bread loaf":
        case "crusty bread loaves":
            name = "crusty_bread";
            price = num * 155;  
            break;
        case "berry":
        case "berry muffin":  
        case "berries":
        case "berry muffins":  
            name = "muffin_berry";
            price = num * 24;
            break;
        case "buckler":
        case "buckler muffin":
        case "buckler muffins":
        case "bucklers":
            name = "muffin_buckler";
            price = num * 24;
            break;
        case "elder flower":
        case "elderflower":
        case "elderflower cheesecake":
        case "elderflower cheesecakes":
        case "cheesecake":
        case "cheesecakes":
            name = "cheesecake";
            price = num * 48;
            break;
        case "bryndon":
        case "bryndons":
        case "bryndon cake":
        case "bryndon cakes":
            name = "bryndon";
            price = num * 12;
            break;
        case "pie":
        case "pies":
        case "meat pie":
        case "meat pies":
        case "savory meat pie":
        case "savory meat pies":
        case "savory pie":
        case "savory pies":
            name = "meat_pie";
            price = num * 120;
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
    return move_item(({name, num, TP}));
}

/*    
 * Function name: 
 * Description:   
 * Arguments:     
 * Returns: 	  
 */
int
move_item(mixed arg)
{
    object drink, ob;
    string file, name;
    int i, num;

    name = arg[0];
    num = arg[1];
    ob = arg[2];

    for (i = 0; i < 10; i++)
    {
        num--;
        file = STAND_DIR + name;
        drink = clone_object(file);

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
                        " from the baker.\nShe gives you "+ arg[1] +".\n");
                    say(QCTNAME(ob) + " orders " + drink->short() +" from "+
                        "the baker.\nShe gives "+ ob->query_objective() +" "+ 
                        arg[1] +".\n", ob);
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
 * Function name: 
 * Description:   
 * Arguments:     
 * Returns: 	  
 */

void
init() 
{
    ::init();
    add_action(order,  "buy");
    add_action(order,  "order");

}


/*    
 * Function name: 
 * Description:   
 * Arguments:     
 * Returns: 	  
 */
