// file name:   /d/Avenir/common/bazaar/intr/ice_cream_parlor.c
// creator(s):  Lilith, June 2022
// purpose:     Ice cream parlor. Goldbezie talked me into it ;)
// note:	    
// revisions
 
#pragma strict_types

#include "../bazaar.h"
#include "/d/Avenir/include/relation.h"

#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include <cmdparse.h>

inherit "/std/room";
inherit "/lib/trade";

#define TYP sizeof(MONEY_TYPES)

#define HELPER       NPC +"scooper"
#define HELP_FLAVORS BAZAAR +"help/icecream.txt"
#define SEE_EAST     ({ EXTR +"", })

object host;
int    test;
int    move_item(mixed arg);
int    do_ring(string str);
int    do_list(string str);
string menu();

string 
east_view()
{
  object *inv, *live, room;
  int i;
 
  inv = ({ });
  for(i = 0; i < sizeof(SEE_EAST); i++)
    if((room = find_object(SEE_EAST[i])))
      inv += all_inventory(room);
 
  if(sizeof(inv)) 
  {
    live = FILTER_LIVE(inv);
    live = FILTER_CAN_SEE(live, TP);
    if(sizeof(live))
       return " East you can see "+ COMPOSITE_LIVE(live) +
       " walking about in the bazaar. ";
  }
  return " Through the doorway to the east the sounds of the busy "+
         "bazaar can be heard. ";
}

string 
menu()
{
   cat(HELP_FLAVORS);
   return "";
}

public string
price_long(void)
{
    cat(HELP_FLAVORS);
	return "";	
}


public string
view_flavors(void)
{
    write("You examine the display counter.\n"+
        "You can see many different containers of ice cream in the display "+
        "case, along with a sign:\n");
    say(QCTNAME(TP) + " examines the contents of the display case.\n");
    cat(HELP_FLAVORS);
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
 * Description  : Called to clone in a new helper if she has
 *                disappeared.
 */
public void
reset_room()
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
create_room()
{
    setuid();
    seteuid(getuid());
	
    set_short("Dancing Goat Ice Cream Parlor");
    set_long(my_long);

    add_npc(NPC + "defender", 1);	

    add_exit(EXTR +"str4","east",0);

	IN_IN;

	add_item(({"doorway"}),
        "It leads east into the bazaar.\n" );
	add_item(({"back wall", "west wall", "stripes", "pink stripes",
        "white stripes"}),
        "The west wall is painted pink and white. It has a large menu posted "+   
        "on it, which a goat dancing above it.\n");
    add_item(({"goat", "dancing goat", "image"}),
        "This is a sybarun goat, known to produce very sweet milk with a "+
        "high cream content... the very stuff the ice cream is made of.\n");
    add_item(({"counter", "bell"}), 
        "A counter made of stone runs parallel to the back wall. "+
        "There is a bell on the counter that you can ring for "+
        "service. There is a display of ice cream flavors on the "+
		"counter, as well as a menu.\n");
    add_cmd_item("bell", "ring", do_ring);	  
    add_item(({"pricelist","list","prices","menu","sign","poster"}),
        menu);
    add_cmd_item(({"pricelist","list","prices","menu","sign"}),
        "read", menu);
    add_item(({"ice cream", "flavors", "flavours", "ice cream display", 
        "display", "ice cream flavors", "display case", "case"}), menu);
  	  
    config_default_trade();    	
    reset_room();

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

    str = "This is a bright and cheery room that smells delicious. "+
	      "The walls are painted in pink and white stripes. "+ 
          "There is an image of a dancing goat painted on the back "+
          "wall, with a menu beneath it. A long counter runs north-"+		  
		  "south across the center of the space, and on it is a "+
	      "display case filled with a variety of ice cream flavors."+
		  "\n";

    return str + east_view() +"\n";
}

/* Ring bell to summon shop host for service if missing. */
public int
do_ring(string str)
{
    write("You ring the bell, the sound resonating throughout the room.\n");
    say(QCTNAME(TP) +" rings the bell on the counter, and the ringing "+
      "resonates throughout the room.\n");

    if (!host)
    {
        host = clone_object(HELPER);
        host->move_living("M", TO);
        host->command("emote arrives from the back room, "+
          "wiping her hands on her apron.\n");
        host_speak("Intios! What flavour of ice cream do you want?");
    }
    else
    {
        host_speak("Intios! What flavour of ice cream do you want?");
    }

    return 1;
}

public int
do_list(string str)
{
    cat(HELP_FLAVORS);
    return 1;
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
        notify_fail("There isn't anyone here to take your order. "+
        "perhaps you should try ringing the bell?\n");
        return 0;
    }

    if (!strlen(str))
    {
        notify_fail("Buy what?\n");
        return 0;
    }

    if (IS_INFIDEL(this_player()))
    {
        host->command("say Begone, lest ae call the punishers on ye!");
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
     // ice cream  -- host's choice 		
        case "ice cream":
        case "ice cream cone":
        case "scoop":
        case "cone":
        case "scoop of ice cream":
        name = "ice_cream_cone";       		
        price = num * 144;
         break;	

        case "vanilla ice cream":
        case "vanilla ice cream cone":
        case "vanilla scoop":
        case "vanilla cone":
        case "vanilla":
        case "scoop of vanilla ice cream":
        kind = "vanilla";
        name = "ice_cream_cone";       		
        price = num * 144;
         break;	
		 
        case "chocolate":		 
        case "chocolate ice cream":
        case "chocolate ice cream cone":
        case "chocolate scoop":
        case "chocolate cone":
        case "scoop of chocolate ice cream":
        kind = "chocolate";
        name = "ice_cream_cone";       		
        price = num * 144;
         break;	

        case "strawberry ice cream":
        case "strawberry ice cream cone":
        case "strawberry scoop":
        case "strawberry cone":
        case "strawberry":
        case "scoop of strawberry ice cream":
        kind = "strawberry";
        name = "ice_cream_cone";       		
        price = num * 144;
         break;	

        case "neapolitan ice cream":
        case "neapolitan ice cream cone":
        case "neapolitan scoop":
        case "neapolitan cone":
        case "neapolitan":
        case "scoop of neapolitan ice cream":
        kind = "neapolitan";
        name = "ice_cream_cone";       		
        price = num * 144;
         break;	

        case "vanilla caramel swirl ice cream":
        case "vanilla caramel swirl ice cream cone":
        case "vanilla caramel swirl scoop":
        case "vanilla caramel swirl cone":
        case "vanilla caramel swirl":
        case "caramel swirl":
        case "scoop of vanilla caramel swirl ice cream":
        kind = "vanilla caramel swirl";
        name = "ice_cream_cone";       		
        price = num * 144;
         break;	
		 
        case "cookies and cream ice cream":
        case "cookies and cream ice cream cone":
        case "cookies and cream scoop":
        case "cookies and cream cone":
        case "cookies and cream":
        case "scoop of cookies and cream ice cream":
        kind = "cookies and cream";
        name = "ice_cream_cone";       		
        price = num * 144;
         break;	

        case "mint chocolate chip ice cream":
        case "mint chocolate chip ice cream cone":
        case "mint chocolate chip scoop":
        case "mint chocolate chip cone":
        case "mint chocolate chip":
        case "mint chocolate chip and cream ice cream":
        kind = "mint chocolate chip";
        name = "ice_cream_cone";       		
        price = num * 144;
         break;	

        case "banana ice cream":
        case "banana ice cream cone":
        case "banana scoop":
        case "banana cone":
        case "banana":
        case "scoop of banana ice cream":
        kind = "banana";
        name = "ice_cream_cone";       		
        price = num * 144;
         break;	

        case "pistachio ice cream":
        case "pistachio ice cream cone":
        case "pistachio scoop":
        case "pistachio cone":
        case "pistachio":
        case "scoop of pistachio ice cream":
        kind = "pistachio";
        name = "ice_cream_cone";       		
        price = num * 144;
         break;	
		 
        case "kahve ice cream":
        case "kahve ice cream cone":
        case "kahve scoop":
        case "kahve cone":
        case "kahve":
        case "scoop of kahve ice cream":
        kind = "kahve";
        name = "ice_cream_cone";       		
        price = num * 144;
         break;	
		 
        case "cookie dough ice cream":
        case "cookie dough ice cream cone":
        case "cookie dough scoop":
        case "cookie dough cone":
        case "cookie dough":
        case "scoop of cookie dough ice cream":
        kind = "cookie dough";
        name = "ice_cream_cone";       		
        price = num * 144;
         break;	
		 
        case "butter rum ice cream":
        case "butter rum ice cream cone":
        case "butter rum scoop":
        case "butter rum cone":
        case "butter rum":
        case "scoop of butter rum ice cream":
        kind = "butter rum";
        name = "ice_cream_cone";       		
        price = num * 144;
         break;	
		 
        case "white chocolate raspberry swirl ice cream":
        case "white chocolate raspberry swirl ice cream cone":
        case "white chocolate raspberry swirl scoop":
        case "white chocolate raspberry swirl cone":
        case "raspberry swirl":
        case "raspberry swirl ice cream":
        case "raspberry swirl cone":
        case "white chocolate raspberry swirl":
        case "scoop white chocolate raspberry swirl ice cream":
        kind = "white chocolate raspberry swirl";
        name = "ice_cream_cone";       		
        price = num * 144;
         break;	
		 
        case "chocolate peanut butter swirl ice cream":
        case "chocolate peanut butter swirl ice cream cone":
        case "chocolate peanut butter swirl scoop":
        case "chocolate peanut butter swirl cone":
        case "peanut butter swirl":
        case "chocolate peanut butter":
        case "chocolate peanut butter ice cream":
        case "chocolate peanut butter cone":
        case "white chocolate raspberry swirl":
        case "scoop white chocolate raspberry swirl ice cream":
        kind = "chocolate peanut butter swirl";
        name = "ice_cream_cone";       		
        price = num * 144;
         break;	
        default:
        notify_fail("She doesn't appear to understand what you want to buy.\n");
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
        file = FOOD + name;
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
                        " from the cook.\nHe gives you "+ arg[1] +".\n");
                    say(QCTNAME(ob) + " orders " + drink->short() +" from "+
                        "the server.\nHe gives "+ ob->query_objective() +" "+ 
                        inum +".\n", ob);
                } 
                else 
                {
                    ob->catch_msg("You buy " + drink->short() + " from the server.\n");
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
    add_action(do_list,  "list"  );	
}
