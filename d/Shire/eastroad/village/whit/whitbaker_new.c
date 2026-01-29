/*
 * Changed cloning process for supplies and changed defs, to 
 * /d/Shire/sys/defs.h
 * Taveren January 2001
 */
inherit "/d/Shire/std/room";
inherit "/lib/trade";

#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <money.h>

#define NUM           sizeof(MONEY_TYPES)
#define PRICELIST_ID  ({"pricelist","list","prices", "sign"})
#define MIN_AWARE 13
#define SUPL_DIR "/d/Shire/eastroad/village/whit/supplies/"

/* Prototype */

static object hathorpe;

object pan;

void
create_shire_room()
{
    config_default_trade();
    set_short("Whitfurrows Bakery");
    set_long("This is the bakery in Whitfurrows, as you "+
      "can quickly detect from the delicious smell of yeast and cooking "+
      "bread and pastries that floats through the shop.  There is a counter "+
      "full of delectable treats, and a pricelist listing all "+
      "the treats that you can buy in here.\n");
    add_item("counter", "@@counter_desc");
    add_item(PRICELIST_ID, "@@pricelist_desc");

    add_prop(ROOM_I_INSIDE,1);
    add_prop("_obj_s_search_fun","do_search");
    add_exit("/d/Shire/eastroad/village/whit/whitlane1","out");

    reset_shire_room();
}

string
counter_desc()
{
    string my_desc;

    if(pan)
    {
    my_desc = "The counter is tall and narrow at the top, only a few things "+
       "could be placed on it at once, and nothing is there now.\n";
    }

    if(!pan)
    {
    my_desc = "The counter is tall and narrow at the top, and piled high with "+
    "things.  You could search the counter to see if anything of value is there.\n";
    }

    return my_desc;
}
string
pricelist_desc()
{
    return "\nRolls:\n\n"+
    "1. 'Sourdough Roll ............   5 cc\n"+
    "2. 'Cheese Roll ...............   8 cc\n"+
    "3. 'Rye Roll ..................   10 cc\n"+
    "\nLoaves:\n\n"+
    "4. 'White Loaf' ...............   35 cc\n"+
    "5. 'Wholemeal Loaf' ...........   20 cc\n"+
    "6. 'Multigrain Loaf' ..........   25 cc\n"+
    "\nTarts:\n\n"+
    "7. 'Cherry Tart ...............   40 cc\n"+
    "8. 'Strawberry Tart' ..........   40 cc\n"+
    "9. 'Custard Tart'..............   30 cc\n\n"+
    "\nPastrieas:\n\n"+
    "10. Hathorpe Pastry............   50 cc\n\n\n";
}

void
reset_shire_room()
{
    pan = 0;
    if (!hathorpe)
        hathorpe = clone_object("/d/Shire/eastroad/village/whit/npc/hathorpe");
    hathorpe->arm_me();
    if (!present(hathorpe))
        hathorpe->move(this_object());
}

void
init()
{
    ::init();
    add_action("do_read", "read", 0);
    add_action("do_buy","buy",0);
    add_action("do_buy","order",0);
}


string
do_search(object searcher, string str)
{
    int awareness;

    awareness = searcher->query_skill(SS_AWARENESS);
    if(awareness < MIN_AWARE + random (MIN_AWARE)) return 0;
    if(!str || (str!= "counter" && str != "counter top")) return 0;
    if(pan) return 0;
    seteuid(getuid(TO));
    pan = clone_object(MICH_DIR + "obj/pan");
    pan->move(searcher,1);
    say(QCTNAME(searcher)+ " finds something on the baker's counter.\n");
    return "You find a "+pan->short()+" on the counter.\n";
}


int
do_read(string str)
{
   if (!str)
        return 0;
    if (member_array(str, PRICELIST_ID) == -1)
        return 0;
    write(pricelist_desc());
    return 1;
}

int
do_buy(string str) 
{
    object order;
    string str1, str2, str3;
    int *arr, price, silent, i;

    if (!str)
    {
    notify_fail("Buy 'item' with 'type of money' and get 'type of money'.\n");
        return 0;
 }
if (!hathorpe || !present(hathorpe))
    {
        notify_fail("The baker is not present... you will have to wait "+
          "until he returns.\n");
        return 0;
    }
    if (sscanf(str, "%s with %s and get %s", str1, str2, str3) != 3) {
        str3 = "";
        if (sscanf(str, "%s with %s", str1, str2) != 2) {
            str2 = "";
            str1 = str;
        }
    }
    switch (str1)
    {
    case "sourdough":
    case "sourdough roll":
    case "1":
        order = clone_object(SUPL_DIR + "roll");
        price = 5;
        break;
    case "cheese":
    case "cheese roll":
    case "2":
        order = clone_object(SUPL_DIR + "croll");
        price = 8;
        break;
    case "rye":
    case "rye roll":
    case "3":
        order = clone_object(SUPL_DIR + "rroll");
        price = 10;
        break;
    case "white":
    case "white loaf":
    case "4":
        order = clone_object(SUPL_DIR + "loaf");
        price = 35;
        break;
    case "wholemeal":
    case "wholemeal loaf":
    case "5":
        order = clone_object(SUPL_DIR + "wloaf");
        price = 20;
        break;
    case "multigrain":
    case "multigrain loaf":
    case "6":
        order = clone_object(SUPL_DIR + "mloaf");
        price = 25;
        break;
    case "cherry":
    case "cherry tart":
    case "7":
        order = clone_object(SUPL_DIR + "ctart");
        price = 40;
        break;
    case "strawberry":
    case "strawberry tart":
    case "8":
        order = clone_object(SUPL_DIR + "start");
        price = 40;
        break;
    case "custard":
    case "custard tart":
    case "9":
        order = clone_object(SUPL_DIR + "cutart");
        price = 30;
        break;
    case "hathorpe":
    case "hathorpe pastry":
    case "10":
        order = clone_object(SUPL_DIR + "pastry");
        price = 50;
        break;

    default:
        notify_fail("Buy 'item' with 'type of money' and get "+
          "'type of money'.\n");
        return 0;
    }

    arr = pay(price, 0, str2, 0, 0, str3, 0);

    if (sizeof(arr) == 1) {
     if (arr[0] == 1) notify_fail("You have to give me more to choose from.\n");
        else if (arr[0] == 2) notify_fail("You don't carry that kind of money!\n");
        return 0;
    }

    write("You pay " + text(exclude_array(arr, NUM, NUM*2-1)) + ".\n");
    if (text(exclude_array(arr, 0, NUM-1))) {
        write("You get " + text(exclude_array(arr, 0, NUM-1)) + ".\n");
        say(QCTNAME(this_player())+" and " + QCTNAME(hathorpe)+" exchange "+
          "some coins.\n");
    }
    else say(QCTNAME(this_player())+" gives "+QCTNAME(hathorpe)+" some "+
          "money.\n");
    write("The baker hands you "+order->short()+".\n");
    say(QCTNAME(hathorpe)+" hands "+QCTNAME(this_player())+" "+
      order->short()+".\n"); 
    if (order->move(this_player())) {
        write("You place the " + order->short() + " on the counter.\n");
        say(QCTNAME(this_player())+" places a " + order->short()+" on the "+
          "counter.\n");
        order->move(this_object());
    }
    return 1;
}
