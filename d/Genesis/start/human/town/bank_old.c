/*
 * /d/Genesis/start/human/town/bank.c
 *
 * This is the headquarters of the Gnomes of Genesis.
 *
 * Created by Arandir, 26 January 2008
 *
 * Revision History:
 *   June 8, 2009 - Moved exits and added ROOM_S_MAP_FILE for integration
 *                  into New Sparkle (Gorboth)
 */

#pragma strict_types

inherit "/std/room";

inherit "/lib/commands";
inherit "/lib/trade";
inherit "/lib/bank";

#include <cmdparse.h>
#include <macros.h>
#include <money.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Genesis/sys/deposit.h"

//-------------------------------------------------------------------

#define S_BANK_SOUTH_EXIT       "/d/Genesis/start/human/town/square"
#define S_BANK_WEST_EXIT        "/d/Genesis/obj/donation/office"

//-------------------------------------------------------------------

int s_bank_listen (string sArgs)
{
  if (!IN_ARRAY(sArgs, ({ "conversation", "to conversation" }) )) return (0);

  write ("You strain to listen to the low murmur of conversation around you but are unable to understand anything.\n");
  allbb (" pauses as if listening to something.", "", ACTION_VISUAL | ACTION_BLIND);

  return (1);
}


int s_bank_stomp (string sArgs)
{
  object oHim = this_player ();

  write ("You stomp your foot but the sound gets muffled by the thick carpet.\n");
  all (" stomps " + oHim->query_possessive () + " foot against the thick carpet.", "", ACTION_AURAL | ACTION_VISUAL | ACTION_MACTIVITY);

  return (1);
}


int s_bank_shout (string sArgs)
{
  object oHim = this_player ();

  if (strlen (sArgs))
  {
    write ("Thinking twice about shouting here, you decide to tone your voice down.\n");
    oHim->command ("$say " + sArgs);
  }
  else
  {
    write ("You take a deep breath but then decide against shouting in here.\n");
    all (" takes a deep breath, then lets it out again.", "", ACTION_AURAL | ACTION_VISUAL | ACTION_LACTIVITY);
  }

  return (1);
}


int s_bank_open (string sArgs)
{
  object oHim = this_player ();

  if (!IN_ARRAY(sArgs, ({ "cabinet", "cabinets" }) )) return (0);

  write ("Not knowing better, you walk towards one of the cabinets and " +
         "try to open it. As you reach for the handle, you feel a shadow " +
         "pass over you ... too late, you realize that a bank this big is " +
         "rather unlikely to have no guard.\n");
  allbb (" walks over to one of the cabinets and tries to grasp the handle. " +
         "In a blur, " + oHim->query_pronoun () + " is intercepted by the " +
         "guard and dumped through the front door.", "", ACTION_VISUAL | ACTION_HACTIVITY);

  oHim->move_living ("M", S_BANK_SOUTH_EXIT, 1, 0);

  write ("Wheee! You never knew revolving doors could spin that fast!\n");
  allbb (" flies out of the revolving door and lands in the middle " +
         "of the square, with a slightly bewildered expression on " +
         oHim->query_possessive () + " face.");

  return (1);
}

//-------------------------------------------------------------------

void create_room ()
{
  object bank;

  set_short ("bank");
  set_long ("Spacious but discreet, the entrance hall of the Gnomes Treasury " +
            "opens up before you. To both sides, passages between sturdy stone " +
            "columns lead to adjacent waiting rooms, brightly lit through windows " +
            "in a domed ceiling. Straight in front of you, a row of counters is " +
            "available for clients conducting their transactions. On one of the " +
            "columns, a large sign is affixed in wooden frame. Occasional " +
            "whiffs of silent conversation give the entire place a slightly " +
            "subdued atmosphere.\n");

  add_item (({"room", "hall", "place", }),
            "This is the entrance hall of the Gnomes Treasury in Sparkle. Expecting " +
            "merely a village branch office, you are surprised to realize that this " +
            "is in fact the headquarters of the Gnomes Treasury of Genesis. Every " +
            "detail within the hall seems to radiate moderation and reliability, " +
            "from the spotless carpeted floor to the fine wooden furniture. To " +
            "the west, the donation office can be found.\n");

  add_item (({"office", "donation", "donation office" }),
            "Between the columns on the west side of the entrance hall, next " +
            "to the waiting rooms, lies the office where the donations of those " + 
            "who helped sustain the donut, are tallied and kept.\n");

  add_item (({"floor", "carpet", "carpets"}),
            "The floor of the hall is covered with a thick, perfectly maintained " +
            "carpet, which muffles your footsteps down to barely audible taps.\n");

  add_item (({"wall", "walls", "furniture", "wooden furniture"}),
            "In places, the walls of the hall are obscured by wooden furniture, " +
            "mostly cabinets made of white oak wood, which has darkened to a " +
            "deep color with straight coarse tecture. The counters in front " +
            "of you are made of the same material.\n");

  add_item (({"cabinet", "cabinets"}),
            "The sturdy cabinets along the walls are made of white oak wood, known " +
            "for its excellent durability. Indeed, it is hard to spot any marks of " +
            "wear on the cabinets, even though their deep color attests to their " +
            "age. From time to time, a gnome carefully retrieves something from " +
            "the cabinet or deposits something into the cabinet.\n");

  add_item (({"counter", "counters", "row", "rows"}),
            "Across the entire width of the hall is a row of counters. The counters " +
            "are made of durable wood, except for their tops, which are covered with " +
            "polished granite. Transactions take place at the counters, with helpful " +
            "gnomes ready to accommodate your every request. Discreetly, reliably, " +
            "and for a small fee, of course.\n");

  add_item (({"detail", "details"}),
            "Your eyes are caressed by the attention to detail evident throughout " +
            "the hall. Somebody evidently went to great lengths to make sure you " +
            "feel comfortable while visiting here.\n");

  add_item (({"entry", "entrance", "door", "doors", "revolving door", "revolving doors"}),
            "A tall set of revolving doors is perhaps the only concession to " +
            "novelty the otherwise conservative gnomes made when constructing " +
            "their headquarters. Even though slightly mistrustful of gnomish " +
            "inventions, you appreciate the savings on heating costs. After " +
            "all, they are bound to be part of the fees you pay here.\n");

  add_item (({"side", "sides", "passage", "passages"}),
            "To both sides of the hall, passages between stone columns lead to " +
            "waiting rooms. With the business down these days, however, the " +
            "passages are closed off with ropes tied between the columns. " +
            "There is enough space for waiting in the hall anyway.\n");

  add_item (({"column", "columns"}),
            "Sturdy stone columns line the hall to the sides. Placed far apart, " +
            "they outline wide passages to the waiting rooms beyond. Ropes are " +
            "tied between the columns though, cordoning off the access. On one " +
            "of the columns, a large sign is affixed in wooden frame.\n");

  add_item (({"frame", "wooden frame"}),
            "A wooden frame is affixed to one of the columns. Inside it, a "+
            "large sign lists the terms of deposit and gives instructions " +
            "on using the deposit.\n");

  add_item (({"rope", "ropes"}),
            "Ropes tied between the columns make it clear to the clients that " +
            "the waiting rooms are currently off limits. With enough space in " +
            "the hall itself, this is not even an inconvenience though.\n");

  add_item (({"waiting room", "waiting rooms"}),
            "The waiting rooms beyond the stone columns are brightly lit through " +
            "large windows in the domed ceiling. The wide spacing of the columns " +
            "lets plenty of light into the hall itself, creating a pleasant " +
            "ambient illumination.\n");

  add_item (({"window", "windows", "illumination", "ceiling"}),
            "The hall itself has no windows, but plenty of light comes in from " +
            "the large windows set in the domed ceiling of the waiting rooms.\n");

  add_item (({"talk", "murmur", "conversation"}),
            "A faint murmur is all you hear from the conversation around you.\n");

  add_item (({"guard", "guardsman", "guardsmen"}),
            "A guard is nowhere in evidence, but a bank this big is bound to have some.\n");

  add_prop (ROOM_I_INSIDE, 1);
  add_prop (ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_city_genesis.txt");

    add_exit("/d/Sparkle/area/city/rooms/streets/center_g", "south");
//add_exit (S_BANK_WEST_EXIT, "west");

  /* Add the Gnome Deposit to the room, but don't let it be visible. */
  bank = clone_object(GOG_DEPOSIT);
  bank->set_no_show_composite(1);
  bank->set_bank_id(5101, "Sparkle");
  bank->move(this_object(), 1);
  remove_my_desc(bank);
  config_default_trade();
  set_bank_fee(25);
  config_trade_data();
}

//-------------------------------------------------------------------

void init ()
{
  ::init ();

  add_action (s_bank_listen, "listen", 0);
  add_action (s_bank_shout, "shout", 0);
  add_action (s_bank_stomp, "stomp", 0);
  add_action (s_bank_open, "open", 0);
    bank_init(); /* Add the bank commands */
}

//-------------------------------------------------------------------



/*
 * Function name: bank_hook_minimized
 * Description:   Player minimized his coins
 */
void
bank_hook_minimized(string pay_text, string got_text)
{
    write("You pay "+pay_text+" and get "+got_text+" in return.\n"
       +  "Your coins are now minimized.\n");
    say(QCTNAME(this_player()) + " minimized " +
        this_player()->query_possessive() + " coins.\n");
}


/*
 * Function name:   discriminate
 * Description:     Don't treat all players equal by giving different prices.
 * Returns:         A percentage.   100   pay normal price.
 *                                 >100   annoy player
 *                                 <100   help player
 */
int
discriminate()
{
    string race;
    int bargain; 

    bargain = this_player()->query_skill(SS_TRADING);

    if(bargain > 30) bargain = 30;
    {
        bargain = 103 - bargain/5;
    }

    return bargain + 25;
}


/*
 * Function name: minimize
 * Description:   changes all coins into the most expensive type, minus a fee
 *                BUGS - This function still not supports unstandard coins
 * Arguments:     str: predicate
 * Returns:       success
 */
int
minimize(string str)
{
    int *money_arr, *money_arr2, value, i, new_sum, total_sum;
    int my_fee;
    string change;

    money_arr = what_coins(this_player());

    money_arr2 = split_values(total_sum = money_merge(money_arr));
    for (i = 0; i < money_num; i++)
    {
        money_arr2[i] -= money_arr[i];
        if (money_arr2[i] < 0)
            money_arr2[i] = 0;
    }
    value = money_merge(money_arr2);
    if (!value)
    {
        bank_hook_already_minimized();
        return 1;
    }
    new_sum = total_sum - (check_call("@@discriminate") - 100) * value / 100;
    money_arr2 = split_values(new_sum);
    for (i = 0; i < money_num; i++)
    {
        money_arr2[i] -= money_arr[i];
        if (money_arr2[i] < 0)
            money_arr2[i] = 0;
    }
    value = money_merge(money_arr2);
    if (!value)
    {
        bank_hook_no_idea();
        return 1;
    }

    MONEY_ADD(this_player(), new_sum);
    MONEY_ADD(this_player(), -total_sum);

    money_arr2 = what_coins(this_player());

    bank_hook_minimized(text(money_arr),text(money_arr2));

    return 1;
}
