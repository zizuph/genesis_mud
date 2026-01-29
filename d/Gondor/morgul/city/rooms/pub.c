/* 
 * A sleazy joint in Minas Morgul
 * Olorin, July 1993, copied from
 * The Proud Stag Pub of Edoras - modified by Elessar,
 * coded by Nick.
 */
#pragma strict_types

inherit "/d/Gondor/morgul/city/morgul.c";
inherit "/lib/trade";

#include <macros.h>
#include <money.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define NUM sizeof(MONEY_TYPES) /* How many types of money do we use? */

/* Prototypes */
object make_drink(string name, string adj, string long, int weight,
		  int volume, int soft, int alco);
public void    reset_room();

object keeper, drunk;

public int
block_keeper()
{
    if (TP == keeper)
        return 1;
    return check_exit();
}

public void
create_morgul_room()
{
  config_default_trade();
  set_extraline(
      "Here human and orc subjects of the Lord of Morgul gather to "
    + "celebrate victories and to laugh at their dead foes. Several "
    + "wooden tables and chairs are standing here. In front of the "
    + "east wall is a counter. Behind the counter, you can see several "
    + "bottles on a shelf and a menu hanging on the wall. "
    + "The exit out to the street is west.");
  set_road(9);
  set_short_desc("in the Dead Tark Pub in Minas Morgul");
    
  add_item(({"menu","sign"}), "@@exa_menu");
  add_cmd_item(({"menu","sign"}), "read", "@@exa_menu");
  add_item(({"bottles","bottle","shelf"}), BSN(
    "The shelf behind the counter of bottles of all sizes and " +
    "shapes. Most of them are close to empty, all are exceptionally " +
    "dirty. "));
  add_item(({"table","tables","chair","chairs"}), BSN(
    "The tables and chairs all have seen better days. Some are " +
    "completely broken, none look as if you would be comfortable using them. " +
    "Certainly, there is not a single chair here on which you could " +
   "sit down without risking to break the chair and fall to the " +
   "ground. So you don't even try to sit down. "));
  add_item(({"counter"}), BSN(
    "A large wooden counter, running along the north wall. Behind it you " +
    "can see a shelf with bottles. "));
  add_item(({"floor","ground"}), BSN(
    "The floor is made from old uneven wooden planks. "));

  add_exit(MORGUL_DIR + "city/darkstr2", "west", block_keeper);
  add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

  reset_room();
}

string
exa_menu()
{
  return ("\nDead Tark Pub - Ahyando, proprietor - Menu\n\n"+
    "  Morgul Beer     (fresh out of the Morgulduin) -   1 sc.\n"+
    "  Harad Wine                   (special-import) -   2 sc.\n"+
    "  Mirkwood Booze      (from the blood of elves) -   6 sc.\n"+
    "  Ghash Water            (from the Isen-Mouthe) -  24 sc\n\n");
}

void
reset_room() 
{
    if (!objectp(drunk))
        drunk = clone_npc(drunk, MORGUL_DIR + "npc/drunk");
    if (!objectp(keeper))
        keeper = clone_npc(keeper, MORGUL_DIR + "npc/ahyando");
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
  object drink;
  string name, adj, long, str1, str2, str3;
  int *arr, price, alco, soft, silent, i;

  TP->reveal_me(1);

  if(!keeper || !present(keeper,TO))
  {
    NF("You cannot do that, since there is no barkeeper here.\n");
    return 0;
  }
  if (!str) 
  {
    NF("The barkeeper says: What do you wanna order?\n");
    return 0;
  }

/* Has the player defined how payment will be done and what change to get back? */  
  if (sscanf(str, "%s for %s and get %s", str1, str2, str3) != 3)
  {
  /* Well, maybe player has defined how payment will be done at least? */
    str3 = "";
    if (sscanf(str, "%s for %s", str1, str2) != 2)
    {
       str2 = "";
       str1 = str;
    }
  }

  switch(str1)
  {
    case "beer":
    case "brew":
    /* Beer, alco is 5 / 2% */
      name = "beer";
      adj = "Morgul";
      long = "It's of a murky brown clour, but smells like a beer.\n";
      soft = 270;
      alco = 5;
      price = 12;
      break;
    case "wine":
    /* Wine, alco is 10 / 10% */
      name = "wine";
      adj = "Harad";
      long = "It's a dark red wine, probably rather strong.\n";
      soft = 100;
      alco = 10;
      price = 24;
      break;
    case "booze":
    /* Booze, alco is 25 / 31% */
      name = "booze";
      adj = "Mirkwood";
      long = "A colourless liquid, smelling strongly, probably made from berries.\n";
      soft = 80;
      alco = 25;
      price = 72;
      break;
    case "water":
    /* Brandy, alco is 50 / 67% */
      name = "water";
      adj = "Ghash";
      long = "A strong colourless brandy distilled somewhere in Mordor. \n";
      soft = 75;
      alco = 50;
      price = 288;
      break;
    default:
      NF("The barkeeper says: I don't understand what you want to buy.\n");
      return 0;
    }
  
    drink = make_drink(name, adj, long, soft, soft, soft, alco);
    /* No drink messege  */
    if (!drink)
    {
      NF("Error in creating drink.\n");
      return 0;
    }

    silent = 0;
    
    if (sizeof(arr = pay(price, TP, str2, 0, 0, str3, silent)) == 1)
    {
      if (arr[0] == 1)
        NF("You have to give me more to choose from, that isn't enough.\n");
      else if(arr[0] == 2)
        NF("You don't carry that kind of money!!!!!!!!!\n");
      return 0;  /* pay() handles notify_fail() call */
    }

/* This is how to detect if the player dropped some of the change. */
/* Then if you had set the silent flag in the pay command you would */
/* then say something about it here. */
/*
    if (arr[sizeof(arr) - 1] 
      write("The barkeeper drops some of your change on the floor,\n"+
        "as you couldn't carry more.\n");
*/

    write("You give the barkeeper " + text(exclude_array(arr, NUM, NUM*2-1)) + ".\n");
    if (text(exclude_array(arr, 0, NUM-1)))
      write("You get " + text(exclude_array(arr, 0, NUM-1)) + ".\n");
    
    if (drink->move(TP))
    {
      write("You drop the " + name + " on the floor.\n");
      say(QCTNAME(TP) + " drops a " + name + " on the floor.\n");
      drink->move(TO);
    }
    else
    {
      write("You get your " + name + ".\n");
      say(QCTNAME(TP) + " buys a " + name + ".\n");
    }

    return 1;
}

/*
 * Function name: make_drink
 * Description:   Set up the drinks
 * Arguments:     A lot of drink data to be set
 */
object
make_drink(string name, string adj, string long, int weight,
	   int volume, int soft, int alco)
{
  object drink;
    
  drink = clone_object("/std/drink");

  /* Some silly functions you have to call inorder to get rid of the name
    and short, already set by /std/drink. Hope this will change. */
  drink->set_short();
  /* There now we can do what weve come for. */

  drink->set_name(name);
  drink->set_pname(name + "s");

  if (strlen(adj)>0)
    drink->set_adj(adj);

  drink->set_long(long);
  drink->set_soft_amount(soft);
  drink->set_alco_amount(alco);
  drink->add_prop(OBJ_I_WEIGHT, weight);
  drink->add_prop(OBJ_I_VOLUME, volume);

  return drink;
}

int
do_sit(string str)
{
    NF(BSN("No, you don't. Those chairs don't look like you " +
      "could sit down on them without breaking them and falling " +
      "to the ground."));
    return 0;
}

void
init()
{
    ::init();

    add_action(order, "buy");
    add_action(order, "order");
    add_action(do_sit,"sit");
}

