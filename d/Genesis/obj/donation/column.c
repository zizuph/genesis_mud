/*
 * /d/Genesis/obj/donation/column.c
 *
 * Genesis is a toroid. Holy is the donut! This column can be cloned into
 * places that want to recognise the generosity of those who have donated
 * money, making it possible to purchase a machine dedicated to running
 * Genesis.
 *
 * Author: Mercade
 * Date  : August 4, 1998
 */

#pragma no_inherit
#pragma strict_types

inherit "/std/object.c";

#include "/d/Genesis/login/login.h"
#include "/d/Genesis/race/racial_abilities.h"
#include "donation.h"
#include <language.h>
#include <macros.h>
#include <stdproperties.h>

/*
 * Function name: long_description
 * Description  : Called to create a dynamic register of the total amount of
 *                donations.
 * Returns      : string - the long description
 */
string
long_description()
{
    return "Its modern design is the most distinctive feature about this " +
        "column. A total of twelve toroid shaped rings of the finest white " +
        "marble are placed on a low pedestal. Six small spheres, made of " +
        "solid gold, support each ring, keeping each pair at a distance of " +
        "two thumbs.\nThe column is raised by the mightiest wizards of " +
        "Genesis to honour the many individuals who generously contributed " +
        "to beating unknown threats in the Great Battle. When the " +
        "continued existance of Genesis was at stake, the bravest forces of " +
        "the realms gathered and gained a stunning victory! The lands of " +
        "Genesis shall remain open to travellers and explorers who shall " +
        "fight their own battles within.\nOn the top, the year 1998 and " +
        "amount of EUR " + DONATION_TOTAL_1998_EUR + " (USD " +
        DONATION_TOTAL_1998_USD + ") is engraved, and just below that the " +
        "amount of EUR " + DONATION_MASTER->query_total_donations() +
        " and the year 2003.\n" +
        "Below, scattered over the lower marble rings, are engraved the " +
        "names of those nobles who made a contribution. They can be read " +
        "using the commands 'read all names' or 'read names <...>'. The " +
        "<...> may contain wildcards, like 'a*' to read all names starting " +
        "with an 'a'. The general overview can also be examined. Players " +
        "who contributed, and who do not have a toroid shaped brooch, may " +
        "'claim' one here.\n";
}

/*
 * Function name: overview_description
 * Description  : This function calls the statistics generator in the central
 *                donation registry.
 * Returns      : string "" - an empty string, as the description is already
 *                    printed.
 */
string
overview_description()
{
    DONATION_MASTER->report_statistics(0);

    return "";
}

/*
 * Function name: create_object
 * Description  : Constructor.
 */
void
create_object()
{
    set_short("marble column");
    set_long(long_description);
    set_name("column");
    set_adj( ({ "marble", "white" }) );

    add_item( ({ "overview", "general overview" }),
        overview_description);

//    add_prop(OBJ_I_INVIS, 100);
    add_prop(OBJ_I_WEIGHT, 22345978);
    add_prop(OBJ_I_VOLUME, 2565764);
    add_prop(OBJ_M_NO_GET, "Oh, sure! Don't forget the elephants and the " +
        "army of slaves to move this column.\n");
}

/*
 * Function name: claim
 * Description  : Using this command, the player can claim a toroid brooch when
 *                he has lost his.
 * Arguments    : string str - the command line argument.
 * Returns      : int - success/failure.
 */
int
claim(string str)
{
    string metal;

    if (!strlen(str) ||
        !parse_command(str, ({ }), "[a] [toroid] [shaped] 'brooch'"))
    {
        notify_fail("Why not? Claim the world! However, here you will only " +
            "get a result if you claim a toroid shaped brooch.\n");
        return 0;
    }

    metal = (string)(DONATION_MASTER->query_brooch_metal_type(this_player()->query_real_name()));
    if (!strlen(metal))
    {
        write("For you, we have not registered a donation. Therefore, we " +
            "cannot give you a brooch. Should you not agree with this, " +
            "please mail with the wizard named 'Donation' and he will get " +
            "back to you as soon as possible.\n");
        return 1;
    }

    setuid();
    seteuid(getuid());

    clone_object(DONATION_BROOCH)->move(this_player(), 1);
    write("In recognition of your generous donation to Genesis to ensure " +
        "final victory in the Great Battle, the mightiest wizards of " +
        "Genesis have the honour of presenting you " + LANG_ADDART(metal) +
        " toroid shaped brooch.\n");
    say("In recognition of " + this_player()->query_possessive() +
        " generous donation to Genesis to ensure final victory in the Great " +
        "Battle, the mightiest wizards of Genesis have the honour of " +
        "presenting " + QTNAME(this_player()) + " a toroid shaped brooch.\n");
    return 1;
}

/*
 * Function name: read
 * Description  : Using this command, the player can read the names of those
 *                who have contributed money to the game.
 * Arguments    : string str - the command line argument.
 * Returns      : int - success/failure.
 */
int
read(string str)
{
    string *names;

    if (!strlen(str))
    {
        notify_fail("Read what?\n");
        return 0;
    }

    str = lower_case(str);
    if (str == "all names")
    {
        str = "names *";
    }

    if (str[0..5] != "names ")
    {
        notify_fail("Syntax: 'read all names' or 'read names <mask>'.\n");
        return 0;
    }

    str = str[6..];
    names = DONATION_MASTER->query_donors(str);

    if (!sizeof(names))
    {
        write("None of the names match the mask '" + str + "'.\n");
        return 1;
    }

    names = map(names, capitalize);
    write("You read the following names:\n\n");

    /* Print in batches of 25 names. */
    while(sizeof(names))
    {
        /* Increase the length of the first name to 11 characters. */
        names[0] = (names[0] + "         ")[..10];
        write(sprintf("%-75#s\n", implode(names[..24], "\n")) + "\n");
        names = names[25..];
    }

    return 1;
}

/*
 * Function name: init
 * Description  : Links the commands to the player.
 */
void
init()
{
    ::init();

    add_action(claim, "claim");
    add_action(read,  "read");
}
