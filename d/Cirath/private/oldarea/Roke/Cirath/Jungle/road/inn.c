/* Modified copy of inn in solace, coded by Nick */
/* Improved (?) by Ged & Gresolle */

inherit  "/std/room";
inherit "/lib/trade";

#include "/d/Roke/common/defs.h"
#include "/d/Roke/Cirath/defs.h"

#include <stdproperties.h>
#include <macros.h>
#include <money.h>

#define NUM sizeof(MONEY_TYPES) /* How many types of money do we use? */

int test; /* to indicate that a test is going on, no money given. */
object tika; /* Kroll */
object t;

/*
 * Prototypes
 */
int move_item(mixed arg);
                  
/*
 * Function name: reset_room
 * Description:   Set up the objects at reset
 */
void
reset_room()
{
    if (!tika)
    {
        tika = clone_object(MONSTER+"kroll");
        tika->move_living("xxx", TO);
    }
    
}

int
pressa(string str)
{
  write("You can't read anything on the plaque, just look at it.\n"+
        "When you try to read it, you feel that there are a serious problem comin\nthe future.\n");
  t = clone_object(DROOMS+"monster/vultra");
  t->move_living("xxx", E(TP));
  return 1;
}

/*
 * Function name: create_room
 * Description:   Set up default trade and cofigure it if wanted.
 */
void
create_room()
{
    config_default_trade();
    set_short("Krolls Inn And Out");
    set_long(BS(
        "You are standing in a large room at Kroll's Inn And Out. The "+
        "interior is very spartan, but has a special touch about it. "+
        "Everything is made of wood, the furniture, the roof, the walls, "+
        "you name it. Here you can order some food or sleep a night.",60));
    
    add_item("bar", "A spartan bar made of wood.\n"+
             "There is a small plaque attached to the bar.\n");
    add_item("menu", "It has a lot of readable words on it.\n");
    add_item("plaque","This bar was borrowed from Nick and altered\n"+
                      "by Gresolle and then altered by Conan.\n");
    add_item("chairs",
        "They're made of wood.\n"); 
    add_item("tables", "They're mad of wood.\n");
    add_cmd_item("menu", "read", "@@read");
    add_cmd_item("plaque","reada","@@pressa");

    add_exit("/d/Roke/conan/workroom", "west","@@wiz_check");
    add_exit(JUNGLE+"road/r5","south",0); 
    add_exit(JUNGLE+"road/hotel","up","@@block");

    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */
    reset_room();
}

block()
{
  if(!(present("krollsbille",TP)))
    {
      write("You don't have a ticket!\n");
      return 1;
    }
  return 0;
}

/*
 * Function name:   wiz_check
 * Description:     Check if a player is a wizard
 * Returns:         0 if the player is a wizard
 *                  1 otherwise
 */

int
wiz_check()
{
    if (this_player()->query_wiz_level())
        return 0;
    write("Some magic force keeps you from going west.\n");
    say(QCTNAME(this_player()) + " tries to go west but fails because "+
        "he's not a true barbarian leader.\n");
    return 1;
}


/*
 * Function name: init
 * Description:   Initalize the pub actions
 */
void
init()
{
    ::init(); /* Since it's a room this must be done. */
    add_action("order", "buy");
    add_action("order", "order");
}

/*
 * Function name: read
 * Description:   Read the menu
 * Arguments:     str - hopefully the menu
 */
int
read(string str)
{
    write("" +
        "   Bier                        10 copper\n" +
        "   A hotel ticket             144 copper\n" +
        "   Some food                   30 copper\n" +
        "Try 'buy bier with gold' if you want to specify what to\n" +
        "pay with. You can also do  'buy 10 bier' would get you\n" +
        "ten biers from the bar, but it takes a little while to\n" +
        "give them all to you. You can't buy more than 10 at a time.\n");
    return 1;
}

/*
 * Function name: order
 * Description:   The buyer orders a drink
 * Arguments:     str - name of drink an possibly description on how to pay and
 *                      get the change
 */
int
order(string str)
{
    string name, str1, str2, str3;
    int *arr, price, num;

    NF("Kroll isn't here to answer your call.\n");
    if (!tika || !P(tika, TO))
        return 0;

    NF("buy what?\n");
    if (!str)
        return 0;

    if (sscanf(str, "%s with %s and get %s", str1, str2, str3) != 3)
    {
    /* Well, maybe player has defined how payment will be done atleast? */
        str3 = "";
        if (sscanf(str, "%s with %s", str1, str2) != 2)
        {
            str2 = "";
            str1 = str;
        }
    }

    if (sscanf(str1, "%d %s", num, str1) != 2)
        num = 1;

    if (num > 10) num = 10;

    switch(str1)
    { 
    case "bier":
    case "biers":
      name = "bier";
      price = num * 10;
      break;
    case "food":
    case "some food":
      name = "fressen";
      price = num * 30;
      break;
    case "ticket":
    case "hotel ticket":
      name = "ticket";
        price = num * 144;
        break;
    default:
        NF("I don't understand what you want to buy.\n");
        return 0;
    }

    if (sizeof(arr = pay(price, this_player(), str2, test, 0, str3)) == 1)
        return 0;  /* pay() handles notify_fail() call */
    
    write("You pay " + text(exclude_array(arr, NUM, NUM*2-1)) + ".\n");
    if (text(exclude_array(arr, 0, NUM-1)))
        write("You get " + text(exclude_array(arr, 0, NUM-1)) + ".\n");
    write("Kroll goes to fix the stuff you ordered.\n");

    return move_item(({name, num, TP}));
}

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
        file = OBJ + name;
        drink = clone_object(file);

        if (!test && (drink->move(ob)))
        {
            ob->catch_msg("You drop the " + drink->short() +
                " on the floor.\n");
            say(QCTNAME(ob) + " drops a " + drink->short() +
                " on the floor.\n", ob);
            drink->move(TO);
        } else if (!test) {
            if (num == 0)
            {
                if (arg[1] > 1)
                {
                    ob->catch_msg("You get some " + drink->plural_short() +
                        ".\n");
                    say(QCTNAME(ob) + " buys some " + drink->plural_short() +
                        ".\n", ob);
                } else {
                    ob->catch_msg("You get the " + drink->short() + ".\n");
                    say(QCTNAME(ob) + " buys " + drink->short() + ".\n",
                        ob);
                }
            }
        } else {
            say(QCTNAME(ob) + " seems to be estimating something.\n",
                ob);
        return 1;
        }
        if (num < 1)
            break;
    }

    if (num > 0)
        call_out("move_item", 1, ({name, num, ob}));
    return 1;
}

/*
 * Function name: test
 * Description:   To allow the buyer to see what would happen with change and
 *                payment depending on how the buyer chooses to pay.
 * Arguments:     str - name of drink an possibly description on how to pay and
 *                      get the change
 */
int
test(string str)
{
    int i;
    string str1;
    
    NF("Test what?\n");
    
    if (sscanf(str, "buy %s", str1)) {
        test = 1;
        write("This would be the result of a buy:\n");
        i = order(str1);
        test = 0;
        return i;
    }
}





