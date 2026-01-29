// OBJECT:  watering_can

    /* Calia Domain

    HISTORY

    [96-02-22] Created by Uhclem from [C:\CALIA\MOUNTAIN\OBJ\WATERING.DOC].

    PURPOSE

    This watering can is a quest item found which may be purchased in the Calia
    palace hardware shop.  Watering the seed you have just planted is the last
    step in the garden quest.  Acquiring this watering can is not a difficult
    task, so no provision is made for recovery.  This item isn't good for
    holding anything but water, so I use std/object rather than std/container
    and provide "fill" and "water" functions. */

// INCLUSIONS AND DEFINITIONS

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "obj.h"
#include GARDEN_QUEST

// FUNCTIONS

// Function:  set_can_desc

/*

Purpose:  Sets descriptions and weight according to whether the can is empty or
full.

Arguments:  none.

Returns:  nothing.

*/

void
set_can_desc()

    {

    if (query_prop(OBJ_I_CONTAIN_WATER))

        {

        set_long("This watering can is made of tin.  " +
            "It has a handle and a long spout for easy watering " +
            "of garden plants.  It is full of water.\n");

        set_short("watering can filled with water");
        set_pshort("watering cans filled with water");
        add_prop(OBJ_I_WEIGHT, 1000);

        }

    else

        {

        set_long("This watering can is made of tin.  " +
            "It has a handle and a long spout for easy watering " +
            "of garden plants.  It is empty.\n");

        set_short("watering can");
        set_pshort("watering cans");
        add_prop(OBJ_I_WEIGHT, 250);

        }

    return;

    }

// Function:  fill_can

/*

Purpose:  fill the can with water.  For the function to succeed, player must be
in a room where water is available and the can must be empty.

Arguments:  string with text typed by the player.  He should "fill can".

Returns:  0/1

*/

int
fill_can(string str)

    {

    object tp = this_player();
    object thisroom = environment(tp);

    /*  Next statement ensures that variable str contains string data to avoid
    type mismatch if player enters "fill" with no argument.  */

    if(!stringp(str)) str = " ";

    if(!wildmatch("*can", str))

        {

        notify_fail("Fill what?\n");
        return 0;

        }

    if(((thisroom->query_prop(ROOM_I_TYPE)) == ROOM_IN_WATER) ||
        ((thisroom->query_prop(ROOM_I_TYPE)) == ROOM_BEACH) ||
        ((thisroom->query_prop(ROOM_I_TYPE)) == ROOM_UNDER_WATER) ||
        thisroom->query_prop(OBJ_I_CONTAIN_WATER))

        {

        if(query_prop(OBJ_I_CONTAIN_WATER))

            {

            notify_fail("The can is already full of water!\n");
            return 0;

            }

        else

            {

            write("You fill the watering can.\n");
            say(QCTNAME(tp) + " fills a watering can.\n");
            add_prop(OBJ_I_CONTAIN_WATER, 1);
            set_can_desc();
            return 1;

            }

        }

    else

        {

        notify_fail("There doesn't seem to be any water around here.\n");
        return 0;

        }

    }

// Function:  water_something

/*

Purpose:  You can water almost anything or anybody with this command.  In room
garden14 there is a special water command that completes the garden quest.

Arguments:  string with text typed by the player.

Returns:  0/1

*/

int
water_something(string str)

    {

    object tp = this_player();
    object thisroom = environment(tp);
    object ob;    /* target of watering if it isn't the "ground". */

    if(!stringp(str))

        {

        notify_fail("Water what - the ground?\n");
        return 0;

        }

    if(!query_prop(OBJ_I_CONTAIN_WATER))

        {

        notify_fail("Your watering can is empty!\n");

        say(QCTNAME(tp) + " slaps " + tp->query_objective() + "self on the " +
            "forehead and shouts, 'Doh!'\n");

        return 0;

        }

    if(wildmatch("*ground", str))

        {

        if(((thisroom->query_prop(ROOM_I_TYPE)) == ROOM_IN_WATER) ||
            ((thisroom->query_prop(ROOM_I_TYPE)) == ROOM_UNDER_WATER))

            {

            write("You add the contents of your watering can to this " +
                "already wet place.\n");

            say(QCTNAME(tp) + " sprinkles some water from a " +
                "watering can, but it doesn't seem to make this " +
                "area significantly wetter.\n");

            }

        else

            {

            write("You water the ground, patiently waiting while " +
                "the watering can drains through the tiny holes " +
                "in its spout.\n");

            say(QCTNAME(tp) + " waters the ground, patiently waiting " +
                "while " + tp->query_possessive() + " watering can " +
                "drains through the tiny holes in its spout.");

            }



        add_prop(OBJ_I_CONTAIN_WATER, 0);

        set_can_desc();
        return 1;

        }

    /*  The user has typed something other than "ground" as the target of the
        watering.  Let's see if there's an object in the room's inventory that
        matches what he typed.  */

    ob = present(str, thisroom);

    if(!objectp(ob))

        {

        notify_fail("You don't see any " + str + " to water here.\n");
        return 0;

        }

    /*  The target object is in this room!  Of course, living things are
        watered somewhat differently from non-living.  */

    if(living(ob))

        {

        tp->catch_msg("You hold the watering can high overhead and give " +
            QTNAME(ob) + " a nice cold shower!\n");

        ob->catch_msg(QCTNAME(tp) + " holds a watering can high " +
            "over your head and gives you a nice cold shower!\n");

        tell_room(thisroom,
            QCTNAME(tp) + " holds a watering can high overhead and gives " +
            QTNAME(ob) + " a nice cold shower!\n", ({tp, ob}));

        }

    else

        {

        write("You hold out a watering can and " +
            "sprinkle the " + str + " liberally with water.\n");

        say(QCTNAME(tp) + " holds out a watering can and " +
            "sprinkles the " + str + " liberally with water.\n");

        }

    add_prop(OBJ_I_CONTAIN_WATER, 0);

    set_can_desc();
    return 1;

    }

// Function:  init

/*

Purpose:  define commands available in this location (called by system when
room is entered)

Arguments:  none

Returns:  nothing

*/

void
init()

    {

    ::init();
    add_action(fill_can, "fill");
    add_action(water_something, "water");

    }

// OBJECT DEFINITION

void
create_object()

    {

    /*  DESCRIPTION  */

    /*  Description and weight, which vary depending on whether the can is
        empty or full, are set by function set_can_desc().  */

    set_name("can");
    add_name("watering can");
    set_adj("watering");

    /*  PROPERTIES  */

    add_prop(OBJ_I_VALUE, 12);
    add_prop(OBJ_I_CONTAIN_WATER, 0);
    set_can_desc();

    /*  ITEMS  */

    add_item(("spout"),
        "The end of the spout is perforated with tiny holes that " +
        "let the water sprinkle gently on delicate plants.\n");

    add_item(("handle"),
        "The tin handle gives you a secure grip on the can so " +
        "that you can easily fill it even in a fast-moving stream " +
        "and water just about anything.\n");

    }
