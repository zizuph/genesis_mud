/*
 * /d/Cirath/tyr/outskirts/tcamp/base.c
 *
 * A base file for the market place in Tyr
 *
 * Eridani - May, 2016
 *
 */

#pragma strict_types
#include "defs.h"
#include "/d/Cirath/tyr/tyr.h"
#include "/d/Gondor/met_defs.h"

inherit "/std/room";
inherit "/d/Gondor/common/lib/room_tell";


#include <macros.h>

void set_items_wagon();
void set_items_tyr();
void set_items_market();

int do_haggle(string str);

/*
 * Function name:        create_market_room
 * Description  :        Use create_market_room() to make market rooms that use
 *                       information from this file
 */
void create_market_room() 
{
}
/* create_market_room */

nomask void create_room() 
{
    create_market_room();
/*
 * Function name:        add_tell - used when inheriting 
 *                       "/d/Gondor/common/lib/room_tell";
 * Description  :        Gives some atmosphere by providing some 'sounds'
 *                       in the room in a similar manner to echo
 */

        add_tell("A group of dirty urchins rush past you as they race " +
            "through the market, leaving you with a strong urge to " +
            "make sure your purse is safe.\n");
        add_tell("The horrible stench of dirty, unwashed bodies assaults " +
            "your nose with surprising vigor.\n");
/* add_tell */

/*
 * Function name:        set_tell_time
 * Description  :        Provides time increments between tells
 */
        set_tell_time(random(550) + 100);
}
/* set_tell_time */

/*
 * Function name:        enter_inv
 * Description  :        Needed to start the room tells
 */
public void
enter_inv(object ob, object from)
{
    start_room_tells();
    ::enter_inv(ob, from);
}
/* enter_inv */

/*
 * Function name:        set_items_wagon
 * Description  :        Items added to market rooms when you include the line
 *                       set_items_wagon(); 
 *                       Use for rooms located inside wagons
 */
public void
set_items_wagon()
{
    add_item(({"wall","walls"}),
        "There are walls inside this wagon, they might not seem interesting " +
        "right now, but you can describe all four separately!\n");
    add_item(({"ground","down","floor"}),
        "The floors of most wagons are made of wood, perhaps filled with " +
        "planks and nails that could also be examined?\n");
}
/* set_items_wagon */

/*
 * Function name:        set_items_tyr
 * Description  :        Items added to market rooms when you include the line
 *                       set_items_tyr(); 
 *                       Use for all market rooms in the city of Tyr
 */
public void
set_items_tyr()
{
    add_item(({"tyr","city"}),
        "You are currently in the city of Tyr. Perhaps describe the name " +
        "of the quarter/section of town? East side of the city? North?\n");
    add_item(({"market","marketplace","name of the market"}),
        "You are in the middle of the name-of-the-market in the city of " +
        "Tyr. There might be other notable areas nearby you can " +
        "mention and create add_items for.\n");
}
/* set_items_tyr */

/*
 * Function name:        set_items_market
 * Description  :        Items added to market rooms when you include the line
 *                       set_items_market(); 
 *                       Use for rooms located in the open market
 */
public void
set_items_market()
{
    add_item(({"booth","booths","wooden booth","wood booth", 
            "wooden booths","wooden booth"}),
        "This is a wooden booth that needs a nice description\n");
    add_item(({"ground","down","floor"}),
        "The ground could be made of packed dirt or perhaps some " +
        "paving stones. Be sure to make another add_item to describe " +
        "them too!\n");
}
/* set_items_market */

/*
 * Function name:        do_haggle
 * Description  :        Provides an emote to haggle in the marketplace
 * Returns      :        int 0 - Prompt for proper syntax
 *                       int 1 - Returns the emote
 */
public int
do_haggle(string str)
{
    if(!strlen(str))
    {
        notify_fail("Haggle with whom? A merchant?\n");
        return 0;
    }

    if (!parse_command(str, ({}),
        " [with] [a] [the] 'merchant' / 'merchants'"))
    {
        notify_fail("Haggle with whom? A merchant?\n");
        return 0;
    }
    write("You walk up to the booth of a nearby merchant and begin to " +
        "haggle long and loud over a small trinket which has caught your " +
        "eye.\n");
    SAYBB(" walks up to a nearby booth and haggles loudly.\n");
    return 1;
}
/* do_haggle */

/*
 * Function name:       init
 * description  :       Initiates the room actions for mortals to use
 */

public void
init()
{
    ::init();
    add_action("do_haggle","haggle");
    add_action("do_haggle","barter");
}
/* init */





