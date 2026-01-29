/* Inn in guild, coded by Nick */

/* Revision History:
 * /Rastlin, 950215, You can only by soup and drinks if you don't have
 *                   any teeth.
 * /Teth, 960329, Added a bard.
 * modified for the new Vingaard Keep, Dec. 6 1996, Teth
 *
 * Modified into a vegetable merchant in Haven town, 
 *     Tibbit, 10 Mar 98
 */

#include "../local.h"
#include <macros.h>
#include <money.h>

inherit HAVENINBASE;
inherit "/lib/trade";

#define NUM sizeof(MONEY_TYPES) /* How many types of money do we use? */

object merch;

/*
 * Prototypes
 */
int move_item(mixed arg);

void
reset_haven()
{
    reset_euid();

    if(!merch)
        (merch = clone_object(HNPC+"merchant"))->move(TO);
}

/*
 * Function name: create_room
 * Description:   Set up default trade and cofigure it if wanted.
 */
void
create_haven()
{
    config_default_trade();
    set_short("Vegetable merchant's stand");

    set_long("You find yourself at the "+
        "the simple booth of a local vegetable merchant. "+
        "The fare is simple but quite wholesome. "+
        "You note celery, parsnips, turnips, potatoes"+
        " and carrots for sale."+
        "\n");

    add_item("vegetables","You may purchase "+
        "celery, carrots, parsnips, turnips or potatoes.\n");
    add_item(({"booth","stand"}),
        "The stand is quite simple, made from wood, but "+
        "it appears sturdy.\n");
    add_item(({"carrot","carrots","celery","parsnips",
        "parsnip","turnip","turnips","potato","potatoes"}),
        "All of the local vegetable selections look quite good.\n");

    add_exit(HROOM+"st2","west");

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
 * Function name: order
 * Description:   The buyer orders a drink
 * Arguments:     str - name of drink an possibly description on how to pay and
 *                      get the change
 */
int
order(string str)
{
    string name, str1, str2, str3;
    int *arr,price,num;

    NF("Buy what?\n");
    if (!str)
        return 0;

    /* Has the player defined how payment will be done and what change to get back? */  
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

    switch(str1)
    {
    case "celery":
    case "celeries":
    case "celerys":
      name = "celery";
      price = num * 9;
      break;
    case "carrot":
    case "carrots":
      name = "carrot";
      price = num * 12;
      break;
    case "parsnip":
    case "parsnips":
      name = "parsnip";
      price = num * 17;
      break;
    case "turnip":
    case "turnips":
      name = "turnip";
      price = num * 21;
      break;
    case "potato":
    case "potatoes":
    case "potatoe":
    case "potatos":
      name = "potato";
      price = num * 23;
      break;
    default:
      NF("That is not available here.\n");
      return 0;
  }

    if(member_array(
        name, ({"potato","turnip","carrot","celery","parsnip"})) &&
	     present("cirath_broken_teeth",TP))
    {
        write("You are toothless, how do you plan to eat that?\n");
	    return 1;
    }


    if (sizeof(arr = pay(price, this_player(), str2, 0, 0, str3)) == 1)
      return 0;  /* pay() handles notify_fail() call */
    
    write("You pay " + text(exclude_array(arr, NUM, NUM*2-1)) + ".\n");
    if (text(exclude_array(arr, 0, NUM-1)))
      write("You get " + text(exclude_array(arr, 0, NUM-1)) + ".\n");
    
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

    if (num <= 0)
      return 1;

    for (i = 0; i < 10; i++)
      {
	  num--;
     file = HFOOD + name;
	  drink = clone_object(file);
	  
	  if (drink->move(ob))
	    {
		ob->catch_msg("You drop " + drink->short() +
			      " on the floor.\n");
		say(QCTNAME(ob) + " drops " + drink->short() +
		    " on the floor.\n", ob);
		drink->move(TO);
	  } else if (num == 0) {
	      if (arg[1] > 1)
		{
		    ob->catch_msg("You get some " + drink->plural_short() +
				  ".\n");
		    say(QCTNAME(ob) + " buys some " + drink->plural_short() +
			".\n", ob);
	      } else {
		  ob->catch_msg("You get " + drink->short() + ".\n");
		  say(QCTNAME(ob) + " buys " + drink->short() + ".\n",
		      ob);
	      }
	  }
	  
	  if (num < 1)
	    break;
      }
    
    if (num > 0)
      set_alarm(0.2,0.0,"move_item", ({name, num, ob}));
    return 1;
}



