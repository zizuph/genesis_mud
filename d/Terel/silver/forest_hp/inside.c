#include "/d/Terel/include/Terel.h"
#include "../include/defs.h"

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <composite.h>
#include <money.h>

#define PLAYER_I_SOLVED_DEC_Q   "_player_i_solved_dec_q"

inherit STDROOM;

/* Coins are lying on the floor, until someone picks them up. */
public int coins_here = 1, searched = 2;

/* Handles action for leaving the cave*/
public int get_out(string a);

/* Handles action for gathering coins from the ground */
public void
create_terel_room()
{
    FIX_EUID;
    set_short("inside a small cave");
    set_long("You're standing inside a small cave. It's quite "+
        "obvious it's a treasure room of some kind. A few large "+
        "closets and chests are standing against the walls, "+
        "and the floor is covered with some less valuable coins. "+
        "You notice the shape of a door on the north wall.\n");             

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(OBJ_I_SEARCH_TIME, 1);
    add_prop(OBJ_S_SEARCH_FUN, "room_search");

    add_item(({"shape", "door"}),
        "A small crack, surrounding door-sized rectangle on "+
        "the north wall. You might try pushing it.\n");
    add_item(({"closet", "closets"}),
        "Closets made of oak wood, are standing against "+
        "each wall except north one.\n");
    add_item(({"chests", "chest"}),
        "Few large chests filled with all kinds of goods "+
        "are standing by the wall.\n");
    add_item(({"coins", "copper coins"}),
        "Copper coins are covering entire floor.\n");
}

public string
room_search(object player, string str)
{	
    if (str == "chest" || str == "chests")
    {
        object obj;
	if (searched == 1 && player->query_prop(PLAYER_I_SOLVED_DEC_Q))
	{
	    searched--;
	    player->remove_prop(PLAYER_I_SOLVED_DEC_Q);

            obj = clone_object(WEAPON + "flamberge");
            if (obj->move(TP))
            {
                obj->move(TO, 1);
                return "You've found a sword in one of the chests "+
                    "but are unable to carry it and drop it.\n";
            }
	    return "You've found a sword in one of the chests.\n";
	}

	if (searched)
	{
	    searched--;
	    obj = MONEY_MAKE_GC(50 + random(50));
            if (obj->move(TP))
            {
                obj->move(TO, 1);
                return "You found some coins but cannot carry them.\n";
            }
	    return "You found some coins.\n";
	}
    }
    return "You find nothing of value, except for a ton of copper coins.\n";
}

public void
reset_terel_room()
{
    coins_here = 1;
    searched = 2;
}

public int
get_out(string a)
{
    if (!strlen(a))
    {
	notify_fail("Push what?\n");
	return 0;
    }

    a = lower_case(a);
    if (!parse_command(a, ({}), "[stone] 'door' / 'rectangle'"))
    {
	notify_fail("Push what?\n");
	return 0;
    }

    write("You open the door and go through it\n");
    tell_room(FOREST_HP + "gate",
        QCTNAME(TP) + " suddenly arrives from nowhere.\n");

    TP->move_living("M", FOREST_HP + "gate");
    return 1;
}

/* He gets as much coins as he can carry - copper coins of course ;] */
public int
get_coins(string a)
{ /* % of encumeberence left, times how much he can carry,
   * devided by 100 and weight of a single cc
   */
    int how_many = (100 - TP->query_encumberance_weight()) *
                        TP->max_weight() / 1800;

    if (a != "coins")
    {
	notify_fail("Chests are to heavy to carry, "+
            "but maybe you can gather some coins from the ground.\n");
	return 0;
    }

    if (!coins_here)
    {
	notify_fail("Most of the coins have been taken already, "+
            "few broken copper coins of no value is all you find.\n");
	return 0;
    }

    coins_here = 0;
    MONEY_MAKE_CC(how_many)->move(TP);
    write("You gather as many coins as you can carry!\n");
    return 1;
}

public void
init()
{
    ::init();
    add_action(get_out, "push");
    add_action(get_coins, "get");
}
