/*
 *  The standard post office for the domain Gondor
 *
 *  - Olorin, January 1995
 *
 * Usage:
 * Call create_post() from your create_room() function,
 * if desired, use set_poster_name() to add additional
 * names to the poster.
 * Define the function mail_message() if the post office
 * is defined in a query_post() function in a guild shadow.
 *
 * Modification log:
 * 13-Jul-1997, Olorin: Added feathers.
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/room.c";
inherit "/lib/trade";
inherit "/d/Genesis/lib/post";

#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <std.h>

#include "/d/Gondor/defs.h"

#define PIGEON_VALUE	12
#define NUM		sizeof(MONEY_TYPES)

public string  exa_feathers();
public string  gather_feathers();
public string  exa_poster();
public int     do_hire(string str);

static  string *poster_names = ({"poster", "intructions", });
static  int     Feathers = 10 + random(21);

void
set_poster_name(mixed names)
{
    if (stringp(names))
        names = ({ names });
    if (!pointerp(names))
        return;

    poster_names = names + poster_names;
}

string * query_poster_names() { return poster_names; }

void
create_post() 
{
    add_item(poster_names, exa_poster());
    add_cmd_item(poster_names, "read", exa_poster());
    add_item( ({ "floor", "ground", "feather", "feathers", }), 
	exa_feathers);
    add_cmd_item( ({ "feather", "feathers", }), 
	({ "gather", "collect" }), gather_feathers);

    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_INSIDE,1);

    config_default_trade();  /* Set up the trading system */
                         /* Copper Silver Gold Platinum  */
    set_money_give_out(   ({ 10000,    32,   2,    1 })); /* Max_pay   */
    set_money_give_reduce(({     0,     4,   2,    1 })); /* Threshold */
}

void
init() 
{
    ::init();
    add_action(do_hire, "hire",0);

    post_init();
}

public string
exa_poster()
{
    return "\n" + break_string(
        "Use our reliable carrier-pigeons to deliver urgent messages "
      + "throughout the world! You can hire a pigeon for the low price "
      + "of only "+PIGEON_VALUE+" copper coins!\n", 40, "\t") + "\n";
}

public string
exa_feathers()
{
    string  desc = " You could try to collect them.";

    switch (Feathers)
    {
    default:
    case 20 .. 100:
	desc = "Many feathers are lying around on the ground, "
	    + "probably lost by the pigeons here." + desc;
	break;
    case 4 .. 19:
	desc = "Some feathers are lying around on the "
	    + "ground." + desc;
	break;
    case 2 .. 3:
	desc = "There are " + LANG_WNUM(Feathers)
	    + " lying on the ground." + desc;
	break;
    case 1:
	desc = "There is one white feather lying on the ground. " +
	    "You could try to collect it.";
	break;
    case 0:
	desc = "Strangely, not a single feather is lying " 
	    + "around on the ground. Someone must have collected "
	    + "them all.";
	break;
    }

    return BSN(desc);
}

public string
gather_feathers()
{
    int     n;
    object  feather;

    if (!Feathers)
    {
	write("There are no feathers here!\n");
	return "";
    }

    n = 2 + random(TP->query_skill(SS_HUNTING) / 5);
    if (n > Feathers)
	n = Feathers;

    feather = clone_object(OBJ_DIR + "feather");
    feather->set_heap_size(n);
    if (feather->move(TP))
    {
	write("You cannot carry the " + feather->short() +
	      ", so you drop them again!\n");
	feather->remove_object();
    }
    else
    {
	write("You pick up " + feather->short() +
	      " from the ground.\n");
	Feathers -= n;
    }

    return "";
}

public int
do_hire(string str) 
{
   object  pigeon;
   string  item_name,
           pay_type,
           get_type,
           str1,
           coin_pay_text,
           coin_get_text;
   int    *money_arr;

   if (!str)
   {
       NF("Hire what?\n");
       return 0;
   }

   TP->reveal_me(1);
 /*   Check if the player defines what she wants to pay with
  *   and what you would like in return.
 */
   if (sscanf(str, "%s for %s and get %s",item_name,pay_type,get_type) != 3)
   {
      get_type = "";
    /* Hmmm... Maybe she only wishes to pay with a certain type */
      if (sscanf(str, "%s for %s", item_name, pay_type) != 2)
      {
         pay_type = "";
         item_name = str;
      }
   }

   if (!(item_name == "pigeon" || item_name == "carrier pigeon"))
   {
      NF("Hire what?\n");
      return 0;
   }

   if (sizeof(money_arr = pay(PIGEON_VALUE, TP, pay_type, 0, 0, get_type)) == 1)
   {
      if (money_arr[0] == 1)
      {
         tell_room(this_object(), BSN(
            "The post master says: You cannot afford a carrier pigeon "
          + "with only those coins, "
          + TP->query_race_name() + "."));
         return 1;
      }
      if (money_arr[0] == 2)
      {
         tell_room(this_object(), BSN(
            "The post master says: You have no " + pay_type + " coins on you, "
          + TP->query_race_name() + "."));
         return 1;
      }
      else
      {
         tell_room(this_object(), BSN(
            "The post master says: You cannot afford a carrier pigeon, "
          + TP->query_race_name() + "."));
         return 1;
      }
   }

 /* Okay, the pigeon is paid for, now give it to the player */
   pigeon = clone_object("/d/Genesis/obj/pigeon");
   if(pigeon->move(TP))
   {
      write("You cannot carry that much!\n");
      pigeon->remove_object();
      return 1;
   }

   coin_pay_text = text(exclude_array(money_arr, NUM, NUM*2-1));
   coin_get_text = text(exclude_array(money_arr, 0, NUM-1));

   write("You pay " +coin_pay_text+ " and hire yourself a pigeon.\n");
   if (coin_get_text)
      write("You get " + coin_get_text + " back from the small gnome.\n");
   say(QCTNAME(TP) + " hires " + TP->query_objective()
     + "self a carrier pigeon.\n");
   return 1;
}

void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    post_leave_inv(ob, to);
}

public void
reset_room()
{
    Feathers = 10 + random(21);
}


/*
 * Function name: silent_room
 * Description  : This function catches all commands. Players will be allowed
 *                to use various commands related to mail, the game and the
 *                exits, but disallows all others.
 *                Mask parent to accept the allowed gondor po verbs.
 * Arguments    : string str - the command line argument.
 * Returns      : int 1/0 - player blocked/player not blocked.
 */
public int
silent_room(string str)
{
    string verb = query_verb();

    if (member_array(verb, ALLOWED_PO_VERBS) >= 0)
    {
        return 0;
    }
    return ::silent_room(str);
}

public int
query_prevent_snoop()
{
    FIX_EUID;
    if (SECURITY->query_wiz_dom(this_interactive()->query_real_name()) == "Gondor")
    {
        return 0;
    }
    return ::query_prevent_snoop();
}

