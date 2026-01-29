// grace
// 13 dec 1994
// last update 5 May 1995
// modified from the Inn in solace, coded by Nick 
//  10+(amt*amt/10) cc drink
//  5+(amt*amt/600) cc food

#include "../local.h"
#include <stdproperties.h>
#include <macros.h>
#include <money.h>

inherit SPURRM;
inherit "/lib/trade";
 

#define TYP sizeof(MONEY_TYPES)         /* How many types of money do we use? */

int alrm;
int move_item(mixed arg);
int test;                                 // Test-buy items
object willa;                           // Serving Girl 

void
reset_spur_room()
{
    if (!willa)
    {
        willa = clone_object(SNPC + "willa");
        willa->move_living("xxx", TO);
    }
}

void
create_spur_room()
{
config_default_trade();
SHORT("Refectory at Knights' Spur");
LONG("This refectory is directly above the Great Hall on the second " +
     "floor.  Nearly as large, but much less formal, this is a favorite place " +
     "for Knights to relax over a good meal.\n   Tables extend in neat " +
     "rows from the south wall, each row providing seating for upwards " +
     "of fifty people.  The sleeping quarters of the Knights' Spur lie " +
     "east, while a large archway opens onto the main passage in the " +
     "west.  From the north can be heard the muted clanging of pots.\n"+
     "   A menu.\n");

   add_exit(ROOM + "pass1l3", "west", 0);
   add_exit(ROOM + "spur_start", "east", "@@knight");
   add_exit(ROOM + "kitchen", "north", 0);
   set_noshow_obvious(1);

    AI("menu", "It has a lot of readable words on it.\n");
    ACI("menu", "read", "@@read");
    AI(({"table", "tables", "refectory table"}), "A long, narrow "+
       "table supported by heavy trestles.\n");
    AI(({"trestles", "trestle"}), "Getting down on your knees to "+
       "examine the trestles, you notice that they are composed "+
       "of horizontal pieces of wood attached to the top of a "+
       "transverse A-frame. They look to be sturdier than "+
       "ordinary table legs.\n");
    AI(({"row", "rows"}), "The rows are made of refectory "+
       "tables lined up end-to-end.\n");
    AI("south wall", "It is plain, unadorned stone.\n");
    AI(({"arch", "archway"}), "The simple arch is carved from "+
      "the same stone as the rest of the Spur. Through it you "+
      "can see the main passage.\n");

  set_tell_time(60);
    add_tell("The scent of roasting meat tantalizes your nose.\n");
    add_tell("Herbs and tomatoes fill the air with heavenly aroma.\n");
    add_tell("A knight gets up from a nearby table and hurries west.\n");
    add_tell("An archer rises from his table and shoulders his quiver.\n");
    add_tell("The rich smell of chocolate causes your stomach "+
          "to grumble hungrily at you.\n");
    add_tell("A human voice shouts: Wood! Willa! Get me some wood "+
          "for these ovens!\n");
    add_tell("You aren't sure, but you think you hear snoring coming "+
         "from the room to the east.\n");
    add_tell("Muted voices from the far table reach your ears.\n"+
          "The knights there seem to be discussing a 'draconian "+
          "prisoner'.\n");
    add_tell("A resounding CRASH comes from the room to the north.\n"+
          "A human voice shouts: You stupid, clumsy idiot! Pick those "+
          "up right now!\n");

    reset_spur_room();
}

void
init()
{
    ::init(); 
    add_action("order", "buy");
    add_action("order", "order");
    add_action("test", "test");
}

void
enter_inv(object ob, object from)
{
    start_room_tells();
    ::enter_inv(ob, from);
}


/*
 * check for non-knights
 */

int
knight()
{
    if (!(MEMBER(TP) || LAYMAN(TP)))
      {
	  write("Only Solamnian Knights may avail themselves "+
                "of the sleeping quarters here.\n");
	  return 1;
      }
    return 0;
}


int
read(string str)
{
   write("" +
"------------------------------------------------------------------\n"+
"                 The Refectory at the Knights' Spur\n"+
"                            Main Dishes:\n" +
"                Roast Capon with Aspic ----- 1670 cc\n"+
"                Crock of Vegetable Stew ---- 1670 cc\n"+
"                Large plate of pasta -------  100 cc\n"+
"                Small dish of pasta --------   30 cc\n"+
" Cheeses:                           Beverages:\n"+
"   Wedge -------------  70 cc          Cognac -------------  OUT\n"+
"   Ball --------------  30 cc          Porter ----------     OUT\n"+
"   Slice -------------  12 cc          Water --------------    ask\n"+
"   Cube --------------   5 cc       Loaf of Bread ---------  30 cc\n"+
"Fruits:                             Desserts:\n"+
"   Berry Compote -----  85 cc          Chocolate Cake -----  35 cc\n" +
"   Dried Fruit ------- 155 cc          Rice Pudding -------  15 cc\n"+
"-------------------------------------------------------------------\n");
    return 1;
}

int
order(string str)
{
    string name, str1, str2, str3;
    int *arr, price, num;

    NF("The server isn't here to take your order.\n");
    if (!willa || !P(willa, TO))
        return 0;

    NF("buy what?\n");
    if (!str)
        return 0;

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
    case "capon":
    case "capons":
    case "roast capon":
    case "roast capons":
    case "roast capon with aspic":
        name = "capon";
        price = num * 1670;
        break;
    case "crock":
    case "stew":
    case "crocks":
    case "stews":
    case "crock of stew":
    case "crocks of stew":
        name = "stew";
        price = num * 1670;
        break;
    case "large pasta":
    case "large pastas":
    case "plate":
    case "plates":
    case "large plate of pasta":
    case "large plates of pasta":
        name = "l_pasta";
        price = num * 100;
        break;
    case "small pasta":
    case "small pastas":
    case "dish":
    case "small dish":
    case "small dish of pasta":
    case "small dishes of pasta":
        name = "s_pasta";
        price = num * 30;
        break;
    case "wedge":
    case "wedges":
    case "cheese wedge":
    case "cheese wedges":
        name = "brie";
        price = num * 70;
        break;
    case "ball":
    case "balls":
    case "cheese balls":
    case "cheese ball":
        name = "gouda";
        price = num * 30;
        break;
    case "slice":
    case "slices":
    case "cheese slices":
    case "cheese slice":
        name = "jarles";
        price = num * 12;
        break;
    case "cube":
    case "cubes":
    case "cheese cubes":
    case "cheese cube":
        name = "gjetoest";
        price = num * 5;
        break;
    case "compote":
    case "berry":
    case "berry compotes":
    case "berry compote":
        name = "compote";
        price = num * 85;
        break;
    case "dried fruit":
    case "fruit":
    case "fruits":
    case "dried fruits":
        name = "d_fruit";
        price = num * 155;
        break;
    case "bread":
    case "loaf of bread":
    case "loaf":
    case "bread loaf":
    case "loaves":
         name = "w_bread";
         price = num * 30;
         break;
    case "rice":
    case "pudding":
    case "rice pudding":
    case "puddings":
        name = "pudding";
        price = num * 15;
        break;
    case "cake":
    case "chocolate":
    case "cakes":
    case "chocolate cake":
    case "chocolate cake":
        name = "cake";
        price = num * 35;
        break;
    default:
        NF("Willa says: I don't understand what you want to buy.\n");
        return 0;
    }
if (num > 10)
{
NF("Willa's tray isn't large enough to carry that much.\n");
return 0;
}

    if (sizeof(arr = pay(price, this_player(), str2, test, 0, str3)) == 1)
        return 0;  /* pay() handles notify_fail() call */

    write("You pay " + text(exclude_array(arr, TYP, TYP * 2 - 1)) + ".\n");
    if (text(exclude_array(arr, 0, TYP - 1)))
        write("You get " + text(exclude_array(arr, 0, TYP - 1)) + ".\n");
    say("Willa rushes north into the kitchen.\n");
    write("Willa rushes north into the kitchen.\n");
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
        file = SOBJ + name;
        drink = clone_object(file);

        if (!test && (drink->move(ob)))
        {
            write("Willa returns from the kitchen with a loaded tray.\n");
            say("Willa returns from the kitchen with a loaded tray.\n");
            ob->catch_msg("Willa hands you a " + drink->query_short()+ ". "+
                "You drop the " + drink->query_short() + " on the floor.\n");
            say("Willa hands a " + drink->query_short() + " to " + QCTNAME(ob) +
                ".\n" + QCTNAME(ob) + " drops the " + drink->query_short() +
                ".\n", ob);
            drink->move(TO);
        } else if (!test) {
            if (num == 0)
            {
                if (arg[1] > 1)
                {
                    say("Willa returns from the kitchen with a loaded tray.\n");
                    write("Willa returns from the kitchen with a loaded tray.\n");
                    ob->catch_msg("She gives you some " + drink->query_plural_short() +
                        ".\n");
                    say(QCTNAME(ob) + " buys some " + drink->query_plural_short() +
                        ".\n", ob);
                } else {
                    write("Willa returns from the kitchen with a loaded tray.\n");
                    say("Willa returns from the kitchen with a loaded tray.\n");
                   ob->catch_msg("You buy a " + drink->query_short() + " from her.\n");
                    say(QCTNAME(ob) + " buys a " + drink->query_short() + " from her.\n",
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

