/*
 * fishmonger.c
 *
 * Shop of the fishmonger of Port MacDunn. At first glance a
 * simple shop, but the fishmonger himself is a spy for the goblin
 * clans, and is hiding a scouting party in tunnels beneath the
 * shop.
 *
 * Khail - April 18/97
 */
#pragma strict_types

inherit "/d/Khalakhor/std/room";

#include <stdproperties.h>
#include <money.h>
#include <macros.h>
#include <language.h>
#include "room.h"
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/se_speir/port/invade_quest.h"

#define LIVE_I_FOUND_FISH_PASSAGE "_live_i_found_fish_passage_k"

object monger;

public int *
query_local_coords()
{
    return ({17,8});
}

public int *
query_global_coords()
{
    return VILLAGE_COORDS;
}

/*
 * Function name: reset_room
 * Description  : Resets global vars, specifically
 *                makes sure the landlord is where he's
 *                supposed to be, behind the bar!
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
reset_room()
{
    ::reset_room();
    if (!monger)
    {
        monger = clone_object(NPC + "arroch");
        monger->arm_me();
        monger->move(TO);
        monger->set_shop(TO);
        tell_room(TO, QCTNAME(monger) + " wanders in from " +
            "the street.\n");
        return;
    }
    else if (!present(monger))
    {
        if (monger->query_attack())
            return;
        else
        {
            tell_room(environment(monger), QCTNAME(monger) +
                "suddenly looks around with a start, and rushes " +
                "off somewhere.\n");
            monger->move_living("M", TO);
            tell_room(TO, QCTNAME(monger) + " rushes in from " +
                "the street outside.\n");
        }
    }
}

/*
 * Function name: exa_opening
 * Description  : Lets the player attempt to examine the opening
 *                in the floor. If the player hasn't found it yet,
 *                they simply don't see it.
 * Arguments    : n/a
 * Returns      : String describing what the player sees.
 */
public string
exa_opening()
{
    if (!TP->query_prop(LIVE_I_FOUND_FISH_PASSAGE))
        return "You find no opening.\n";

    return "It's little more than a dark hole in the floor " +
        "hidden behind the fish barrels, you might be able " +
        "to climb down.\n";
}

/*
 * Function name: create_khalakhor_room
 * Description  : Turns this object into a fish store.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_khalakhor_room()
{
    set_short("a shop smelling strongly of fish");
    set_long("   You're in a small shop that reeks of fish. Looking " +
        "around the origin of the smell is obvious, as it appears " +
        "that's what is sold here. However, the smell appears to " +
        "be more from the age of the shop than of the fish, as " +
        "the laden barrels and bins you see all have clean, fresh " +
        "fish smelling of the sea. The only exceptions are the " +
        "bins with the prepared fish which have been salted or " +
        "smoked. A sign on a wall appears to be a pricelist.\n");

    add_item(({"barrels"}),
        "The barrels are all full to varying degrees of different " +
        "kinds of fish.\n");
    add_item(({"bins"}),
        "The bins are full of different kinds of fish and shellfish.\n");
    add_item(({"fish"}),
        "There's all kinds of them here.\n");
    add_item(({"shellfish"}),
        "There's lots of shellfish here, ready for cooking.\n");
    add_item(({"floor", "ground"}),
        "The floor of the shop is made simply from hard-packed " +
        "dirt, and looks as if it's been changed recently, " +
        "probably as a means of keeping down the odour of fish " +
        "oils which spill onto the floor and soak into the dirt.\n");
    add_item(({"walls", "wall"}),
        "The walls of the shop are made from various sized " +
        "pieces of hard grey stone, carefully placed together " +
        "and packed with clay.\n");
    add_item(({"roof", "ceiling"}),
        "The ceiling of the shop is a simple thatch and wooden " +
        "rafter construction.\n");
    add_item(({"thatch", "seaweed", "seagrass"}),
        "The thatch looks to be tightly-bundled mats of " +
        "some sort of seagrass or seaweed.\n");
    add_item(({"rafters"}),
        "The thatch of the roof is supported by a handful of " +
        "very thin wooden rafters.\n");
    add_item(({"pricelist", "sign"}),
        "It looks worth reading.\n");

    INSIDE;

    add_exit(ROOM + "road_17_7", "north");

#ifdef INVASION_OPEN
    add_item(({"opening"}),
        VBFC_ME("exa_opening"));

    add_prop(OBJ_I_SEARCH_TIME, 5);
    add_prop(OBJ_S_SEARCH_FUN, "search_for_opening");
#endif

    set_alarm(1.0, 0.0, &reset_room());
}

/*
 * Function name: search_for_opening
 * Description  : Allows players to search the barrels for the opening
 *                down to the tunnels.
 * Arguments    : str - What the player wanted to search.
 *                who - Object pointer to the searching player.
 * Returns      : A string, 0 strlen for a fail, otherwise a find
 *                message.
 */
public string
search_for_opening(object who, string str)
{
  /* Can't find the opening in the dark. */
    if (!CAN_SEE_IN_ROOM(who))
        return "It's too dark to see.\n";

  /* Monger won't let anyone search while he's around. */
    if (monger && present(monger, TO))
    {
        tell_room(TO, QCTNAME(monger) + " interrupts " +
            QTNAME(who) + " before " + who->query_pronoun() +
            " can complete " + who->query_possessive() + " search.\n",
            ({who, monger}));
        return monger->query_The_name(who) + " interrupts you " +
            "before you can complete your search.\n";
    }
    
  /* We're only interested if the player's searching the barrels. */
    if (!parse_command(str, TP, "[the] 'barrel' / 'barrels' [for] " +
        "[opening]"))
        return "";

  /* Silly player searching barrels twice. */
    if (who->query_prop(LIVE_I_FOUND_FISH_PASSAGE))
        return "You find the opening in the floor behind the " +
            "barrels hasn't moved since your last search.\n";

  /* Ok, reveal the passage. */
    who->add_prop(LIVE_I_FOUND_FISH_PASSAGE, 1);
    return "You find an opening in the floor behind the barrels.\n";
}

/*
 * Function name: do_read
 * Description  : Allows players to read the menu.
 * Arguments    : str - String containing arguments passed with the
 *                      'read' command.
 * Returns      : 0 - Keep threading. 
 *                1 - Stop threading.
 */
public int
do_read(string str)
{
    NF("Read what?\n");

  /* Fail if the player wasn't trying to read the menu or sign. */
    if (!str ||
        !strlen(str) ||
        (str != "pricelist" &&
        str != "sign"))
        return 0;

    write("\nFish:\n" +
          "  raw cod                  - 85 coppers\n" +
          "    salted cod             - 102 coppers\n" +
          "  raw haddock              - 85 coppers\n" +
          "  raw herring              - 25 coppers\n" +
          "    pickled herring        - 27 coppers\n" +
          "  raw monkfish             - 85 coppers\n" +
          "  raw salmon               - 93 coppers\n" +
          "    smoked salmon          - 110 coppers\n" +
          "  raw wolffish             - 85 coppers\n" +
          "Shellfish:\n" +
          "  raw crab                 - 85 coppers\n" +
          "  raw lobster              - 271 coppers\n" +
          "  raw mussel               - 5 coppers\n" +
          "  raw scallop              - 5 coppers\n" +
          "\n");

    return 1;
}

/*
 * Function name: do_buy
 * Description  : Allows players to attempt to buy something here.
 * Arguments    : str - What the player wants to buy.
 * Returns      : n/a
 */
public int
do_buy(string str)
{
    string file;
    object food;
    int price,
        mfail;

    NF("Buy what?\n");

    if (!str || !strlen(str))
        return 0;

    if (str == "herring")
        file = OBJ + "herring";
    else if (str == "pickled herring")
        file = OBJ + "p_herring";
    else if (str == "haddock")
        file = OBJ + "haddock";
    else if (str == "cod")
        file = OBJ + "cod";
    else if (str == "salted cod")
        file = OBJ + "s_cod";
    else if (str == "wolffish")
        file = OBJ + "wolffish";
    else if (str == "monkfish")
        file = OBJ + "monkfish";
    else if (str == "salmon")
        file = OBJ + "salmon";
    else if (str == "smoked salmon")
        file = OBJ + "s_salmon";
    else if (str == "mussel")
        file = OBJ + "mussel";
    else if (str == "scallop")
        file = OBJ + "scallop";
    else if (str == "lobster")
        file = OBJ + "lobster";
    else if (str == "crab")
        file = OBJ + "crab";

    if (!file)
        return 0;

    reset_euid();
    food = clone_object(file);

    price = food->query_prop(OBJ_I_VALUE);

    if (!MONEY_ADD(TP, -price))
    {
        write("You don't have enough money to pay for it.\n");
        return 1;
    }

    write("You pay " + price + " coppers for " + 
        LANG_THESHORT(food) + ".\n");
    say(QCTNAME(TP) + " pays " + price + " coppers for " +  
        LANG_ASHORT(food) + ".\n");

    if (mfail = food->move(TP))
    {
        write("You can't carry " + LANG_THESHORT(food) + " and " +
            "drop it to the floor.\n");
        say(QCTNAME(TP) + " appears unable to hold " + 
            LANG_THESHORT(food) + " and drops it to the floor.\n");
        food->move(environment(TP));
    }

    return 1;
}

/*
 * Function name: do_climb
 * Descripton   : Allows players to attempt to climb down through
 *                the hole in the floor (if they've found it) into 
 *                the tunnels below.
 * Arguments    : str - Arguments to the 'climb' command as a string.
 * Returns      : 0 - Keep threading. 
 *                1 - Stop threading.
 */
public int
do_climb(string str)
{
  /* Do nothing if player didn't say where to climb. */
    if (!str || !strlen(str))
        return 0;

  /* Do nothing if the player hasn't found the opening. */
    if (!TP->query_prop(LIVE_I_FOUND_FISH_PASSAGE))
        return 0;

  /* Fail if the player can't see in the room. */
    if (!CAN_SEE_IN_ROOM(TP))
    {
        NF("It's too dark!\n");
        return 0;
    }

  /* Fail if the monger blocks them. the can_block_me() function */
  /* takes care of any relevant messages to the player. */
    NF("Climb where? Down the opening?\n");
    if (monger && monger->can_block_me(TP))
        return 1;

  /* Do nothing if we can't understand the syntax of where */
  /* the player wants to climb. */
    if (!parse_command(str, TP, "[down] [in] [the] [opening]"))
        return 0;

    write("You slip behind the barrels and climb down through " +
        "the opening.\n");
    say(QCTNAME(TP) + " slips behind some barrels and vanishes.\n");
    TP->move_living("M", ROOM + "tunnel_1");
    say(QCTNAME(TP) + " climbs down the ladder.\n");
    return 1;
}
    
/*
 * FUnction name: init (MASK)
 * Description  : Called when another object meets this object.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
init()
{
    ::init();
    add_action(do_read, "read");
    add_action(do_buy, "buy");
    add_action(do_climb, "climb");
}
