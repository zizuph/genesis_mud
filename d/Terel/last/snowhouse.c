/*
 * snowhouse.c
 *
 * The Snowhouse
 * Thanks to Khail of Khalakhor
 * Shinto, March 98
 */
#pragma strict_types

#include "/d/Terel/include/Terel.h"
inherit STDROOM;
inherit "/lib/pub";

#include <stdproperties.h>
#include <money.h>
#include <macros.h>


object owner;

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
    if (!owner)
    {
        owner = clone_object(LAST_DIR+"npc/brownshort");
        owner->move(TO);
        tell_room(TO, QCTNAME(owner) + " wanders in from " +
            "the kitchen.\n");
        return;
    }
}


/*
 * Function name: create_room
 * Description  : Turns this object into a pub.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_room()
{
    set_short("The Snowhouse of Last");
    set_long("The Snowhouse of Last. A well liked establishment of "+
                   "the town. A fire burns to the left as you enter, the bar "+
                   "directly ahead. A number of wooden tables and chairs "+
                   "fill the empty spaces inbetween. In the background you "+
                   "can hear the frying and steaming of food being prepared. "+
                   "Above the bar posted on the wall is the menu.\n");

    add_item(({"fire","fireplace","hearth"}), 
        "The fireplace sits to the west wall of the pub, made of stones  "+
        "to keep the hall warm longer.\n");
    add_item(({"table","tables","chairs","chair"}),"Spread throughout "+
        "the room are several wooden tables and chairs for customers.\n");
    add_item(({"bar"}),
        "A long, wooden bar stands against the north wall, " +
        "behind which the owner keeps all the good stuff.\n");
    add_item(({"menu", "sign"}),
        "It looks worth reading.\n");
	add_prop(ROOM_S_MAP_FILE, "town_last.txt");

    INSIDE;

    add_drink(({"silver ale","ale"}),
        ({"ale","pint","silver ale"}),
        "silver",
        250, 12, 24,
        "pint of silver ale", "pints of silver ale",
        "The pint contains a pale Silver ale.\n","");

    add_drink(({"lager","calathin lager"}),
        ({"lager","pint","calathin lager"}),
        "calathin",
        250, 24, 60,
        "pint of Calathin lager", "pints of Calathin lager",
        "The pint contains a rich brew of  Calathin lager.\n","");

    add_drink(({"last stout","Last stout","stout"}),
        ({"last stout","pint","stout"}),
        "dark",
        550, 40, 82,
        "pint of Last stout", "pints of Last stout",
        "The glass contains a full pint of a rich brew of " +
        "dark, foamy Last stout.\n", "");
    add_drink("rum",
        ({"rum","glass"}),
        "dark",
        100, 45, 170,
        "glass of rum", "glasses of rum",
        "The small glass contains a dark rum with a " +
        "strong, smooth aroma.\n", "");

    add_food("clams",
        ({"clams","bowl"}),
        "steamed",
        50, 20,
        "bowl of steamed clams", "bowls of steamed clams",
        "The bow of clams have been steamed.\n", "");

    add_food(({"salmon", "smoked salmon"}),
        ({"salmon","plate"}),
        "smoked",
        250, 80,
        "plate of smoked salmon", "plates of smoked salmon",
        "The smoked salmon, isn't very big, " +
        "but has been well cooked.\n", "");
    add_food(({"crab","crab legs","legs"}),
        ({"legs", "legs","plate"}),
        "crab",
        400, 270,
        "plate of crab legs", "plates of crab legs",
        "The crab legs has been slowly bowled over an open " +
        "fire.\n", "");
    add_food("lobster", ({"lobster","plate"}),
        "",
        600, 605,
        "plate of lobster", "plates of lobsters",
        "The lobster is huge, bowled in water over a open fire.\n","");

    add_exit(LAST_DIR + "lroad7", "south");

    reset_room();
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
        (str != "menu" &&
        str != "sign"))
        return 0;

    write("Welcome to The Snowhouse!\n" +
              "Owned and run by Brownshort Littlehand\n"+
              "Drinks:\n" +
          "    Silver ale             - 24 coppers\n" +
          "    Calathin Lager     - 60 coppers\n" +
          "    Last stout           - 82 coppers\n" +
          "    Rum                     - 170 coppers\n");
    write("\nFood:\n" +
          "    bowl of clams                  - 20 coppers\n" +
          "    plate of salmon            - 80 coppers\n" +
          "    plate of crab legs            - 270 coppers\n" +
          "    plate of lobster                  - 605 coppers\n");

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
    init_pub();
}

/*
 * Function name: order
 * Description:   The player has ordered something, let's see if we can satisfy
 *								  him.
 * Arguments:		  str - The order from the player
 * Returns:				  1 or 0
 */
int
order(string str)
{
    string *words;
    int num, tmp, i, price;
    object ob;

    if (!str)
    {
					notify_fail(capitalize(query_verb()) + " what?\n");
					return 0;
    }

    words = explode(str, " ");
    num = 1;
    if (sizeof(words) > 1)
    {
					tmp = LANG_NUMW(words[0]);
					if (!tmp)
					    sscanf(words[0], "%d", tmp);
					if (tmp > 0)
					{
					    num = tmp;
					    str = implode(words[1 .. sizeof(words)], " ");
					}
    }

    if (num > 40)
    {
					return pub_hook_ordered_too_many(num);
    }

    for (i = 0; i < sizeof(dr_id); i++)
					if (member_array(str, dr_id[i]) >= 0)
					{
					    ob = fix_drink(drinks[i]);
					    price = num * drinks[i][4];
					    ob->set_heap_size(num);
					    break;
					}

    if (!ob)
					for (i = 0; i < sizeof(fo_id); i++)
					    if (member_array(str, fo_id[i]) >= 0)
					    {
										ob = fix_food(food[i]);
										price = num * food[i][3];
										ob->set_heap_size(num);
										break;
					    }

    if (!ob)
    {
					notify_fail("No " + str + " in stock.\n");
					return 0;
    }

    if (!MONEY_ADD(this_player(), -price))
    {
					pub_hook_cant_pay(price);
					ob->remove_object();
					return 1;
    }

    pub_hook_player_buys(ob, price);

    ob->move(this_player(), 1);
/*
 * I can't get this to work so let the players be loaded down with food if
 * they want to. Anyone willing to fix this bug, please send us a patch.
 * /Nick
 *
    tmp = num - ob->num_heap();
    if (tmp > 0)
    {
					ob->set_heap_size(tmp);
					ob->remove_remove_object_call();
					ob->move(environment(this_player()));
					pub_hook_cant_carry(ob);
    }
 */

    return 1;
}


