// OBJECT:  cymbals

    /* Calia Domain

    HISTORY

    [99-11-22] Created by Uhclem from [D:\CALIA\YULEWARE\TOYS\CYMBALS.DOC].

    PURPOSE

    A toy to be found under the Christmas tree in the domain office in the
    Tower of Realms. */

// INCLUSIONS AND DEFINITIONS

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <options.h>

// OBJECT DEFINITION

void
create_object()

{

    /*
     *  DESCRIPTION    
     */

    set_short("pair of toy brass cymbals");
    set_pshort("pairs of toy brass cymbals");
    set_name("cymbals");
    add_name("brass cymbals");
    add_name("toy brass cymbals");
    add_name("pair");
    add_name("toy");

    set_long("The cymbals are made of polished brass discs with" +
        " red ribbons for handles. They're only a bit bigger" +
        " around than your hand, so they're not for making" +
        " really loud sounds, but you can still clang or crash them" +
        " to make a little festive noise.\n");

    /*
     *  PROPERTIES    
     */

    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VOLUME, 250);
    add_prop(OBJ_I_VALUE, 10);

    add_prop(OBJ_M_NO_SELL, "Sell the traditional yuletide" +
        " cymbals? No, you wouldn't dare!\n");

    /*
     *  ITEMS    
     */

    add_item(({"brass", "discs", "brass discs"}),
        "The discs are slightly concave so that they strike each" +
        " other only at the edges, and a strong red ribbon is" +
        " riveted to the outside of each.\n");

    add_item(({"ribbon", "ribbons", "red ribbon", "red ribbons",
        "handle", "handles"}),
        "The ribbons are comfortable to hold so that you can" +
        " clang and crash all you want without getting your" +
        " fingers numb from the vibrating discs.\n");

}

// FUNCTIONS

// Function:  clang_cymbals

/*

Purpose:  clang the cymbals rather politely.

Arguments:  string indicating this pair of cymbals

Returns:  0/1

*/

int
clang_cymbals(string str)

{

    object tp = this_player();
    object target;

    if (!stringp(str)) /* Player did not specify what to clang. */

    {

        notify_fail("Clang what?\n");
        return 0;

    }

    if (parse_command(str, all_inventory(tp), "%o", target))

    {

        if (target != this_object()) return 0;

        say(QCTNAME(tp) + " clangs " + tp->query_possessive() +
            " toy brass cymbals in a brisk cadence, making a" +
            " festive sound as bright as the reflections" +
            " off their highly polished surfaces.\n");

        write("You clang your toy brass cymbals in a brisk" +
            " cadence, making a festive sound as bright as" +
            " the reflections off their highly polished surfaces.\n");

        return 1;

    }

    return 0;

}

// Function:  crash_cymbals

/*

Purpose:  crash the cymbals loudly.

Arguments:  string indicating this pair of cymbals

Returns:  0/1

*/

int
crash_cymbals(string str)

{

    object tp = this_player();
    object target;

    if (!stringp(str)) /* Player did not specify what to crash. */

    {

        notify_fail("Crash what?\n");
        return 0;

    }

    if (parse_command(str, all_inventory(tp), "%o", target))

    {

        if (target != this_object()) return 0;

        say(QCTNAME(tp) + " suddenly crashes " + tp->query_possessive() +
            " toy brass cymbals as loud as " + tp->query_pronoun() +
            " can! The vibrations linger for a surprisingly long" +
            " time, both in the cymbals and in your ears.\n");

        write("You crash your toy brass cymbals as loud as" +
            " you can! The vibrations linger for a surprisingly long" +
            " time, both in the cymbals and in your ears.\n");

        return 1;

    }

    return 0;

}

// Function:  init

/*

Purpose:  define commands available in this object (called by system when
object enters a player's inventory)

Arguments:  none

Returns:  nothing

*/

void
init()

{

    ::init();
    add_action(clang_cymbals, "clang");
    add_action(crash_cymbals, "crash");

}
