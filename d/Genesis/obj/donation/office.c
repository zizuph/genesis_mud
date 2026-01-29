/*
 * /d/Genesis/obj/donation/office.c
 *
 * Genesis is a toroid. Holy is the donut! This is the office of the treasurer
 * of Genesis. The treasurer will keep the accounts of the generous people
 * who contributed to Genesis, making it possible to purchase a machine
 * dedicated to running Genesis.
 *
 * Author: Mercade
 * Date  : August 4, 1998 - Original design for 1998 donation campaign.
 * Date  : August 18, 2003 - Updated for 2003 donation campaign.
 * Date  : November 23, 2004 - Removed capitalize_word() routine.
 * Date  : June 8, 2009 - Added ROOM_S_MAP_FILE prop and changed exit to
 *                        integrate into New Sparkle. (Gorboth)
 */

#pragma no_clone
#pragma no_inherit
#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "donation.h"

#include <language.h>
#include <macros.h>
#include <stdproperties.h>

/*
 * Function name: long_description
 * Description  : Build the long description for the person individually,
 */
nomask string
long_description()
{
    string str = "The office of the treasurer of Genesis is comfortable, " +
        "yet not luxurious. Skilled craftsmen created a functional " +
        "environment without rich decorations. Smooth wooden panels cover " +
        "the brick walls and a red carpet covers the stone slabbed floor. " +
        "An iron strongbox, bolted to the floor, is placed behind the old " +
        "oak desk. The oak desk is prominently situated against the side " +
        "wall. Straight opposite of the entrance door, the current balance " +
        "is clearly visible on a chalkboard. It reads:\nIn 1998, the amount " +
        "of EUR " + DONATION_TOTAL_1998_EUR + " (USD " +
        DONATION_TOTAL_1998_USD + ") was kindly donated.\nGenerously " +
        "donated in 2003 was the amount of EUR " +
        DONATION_MASTER->query_total_donations() + ".\n";

    str += "\nSeveral posters on the walls contain the information also " +
        "listed in the help pages: donation, donation_rights, "+
        "donation_token and donation_trust. Please read those help pages!\n";

    if (member_array(this_player()->query_real_name(),
        DONATION_COLLECTORS) != -1)
    {
        str += "\nFor donation collectors, there are a few commands to handle " +
            "donations:\n" +
            "    donation add <name> <currency> <amount> <EUR equivalent>\n" +
            "    donation second <name> <name of second>\n" +
            "    donation remove <name>\n" +
            "    donation stats\n\n";
    }

    return str;
}

/*
 * Function name: chalkboard_description
 * Description  : Players examining the chalkboard should get the current
 *                ballance.
 * Returns      : string - the description.
 */
nomask string
chalkboard_description()
{
    return "Straight opposite of the entrance door, a chalkboard is hung on " +
        "the wall. The treasurer uses the board to show the current balance " +
        "to all visitors. It reads:\nIn 1998, the amount of EUR " +
        DONATION_TOTAL_1998_EUR + " (USD " + DONATION_TOTAL_1998_USD +
        ") was kindly donated.\nGenerously donated in 2003 was the " +
        "amount of EUR " + DONATION_MASTER->query_total_donations() + ".\n";
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
 * Function name: create_room
 * Description  : Constructor.
 */
nomask void
create_room()
{
    set_short("the office of the treasurer of Genesis");
    set_long(long_description);

    add_item( ({ "panel", "panels", "wooden panels", "smooth wooden panels",
        "wall", "walls", "brick walls" }),
        "Oak panelling covers the brick walls. The wooden panels have been " +
        "sanded and polished until they became as smooth as they are today. " + 
        "Onto the walls, various posters are nailed. They contain details " +
        "about the work of the treasurer.\n");
    add_item( ({ "poster", "posters" }),
        "A total of seven posters is nailed to the wall. Each poster " +
        "contains the text of one of the help pages related to the donation " +
        "gathering campaign. The titles of the posters are: donation, " +
        "donation_rights, donation_token and donation_trust. Please read " +
        "the help pages with the same title.\n" );
    add_item( ({ "carpet", "red carpet", "floor", "ground" }),
        "The stone slabbed floor is covered by a red carpet. The quality of " +
        "the carpet is quite decent, but not extraordinary. As everything " +
        "else in this office, it breathes thoroughness without superfluous " +
        "luxury. Behind the old oak desk, an iron strongbox is placed.\n" );
    add_item( ({ "box", "strongbox", "iron strongbox" }),
        "The iron strongbox is placed behind the old oak desk. It is bolted " +
        "to the floor to prevent miscreants from taking it along. No lock " +
        "is visible; Dwarven carpenters must have crafted this strongbox " +
        "with the same skill they display when making their famous doors. "+
        "The treasurer undoubtably uses the box to store money from far " +
        "away lands, filling it with currencies unusable in these realms.\n");
    add_item( ({ "lock"}),
        "Nope, a lock really is not visible. Dwarves know their trade! " +
        "Ask a skilled craftsman to make a strongbox without obvious lock " +
        "and you can bet your beard you never find it.\n");
    add_item( ({ "desk", "oak desk", "old oak desk" }),
        "The old oak desk dominates almost the complete west wall of the " +
        "office. With age comes beauty and this antique desk is of a simple " +
        "yet sturdy design. Untold fortunes have been administered at this " +
        "desk. Behind the desk, an iron strongbox is bolted to the floor. " +
        "On the desk itself, several typical clerical items can be found, " +
        "like a bottle of ink and a quill pen. Prominently in the middle of " +
        "the desk sits a leather ledger with the records of all donations " +
        "made. The general overview of the contributions can also be " +
        "examined.\n");
    add_item( ({ "ink", "bottle of ink", "pen", "quill pen", "quill" }),
        "The bottle of ink and the quill pen are two of the typical " +
        "clerical utensils found on the oak desk. The lie on the desk just " +
        "above the leather ledger.\n.");
    add_item( ({ "ledger", "leather ledger" }),
        "In the middle of the desk this leather ledger sits. It contains " +
        "the central administration of the treasurer, keeping the names of " +
        "those who generously contributed to the continued existance of the " +
        "realms, along with the exact sum they donated. The gnomish " +
        "assistant of the treasurer is responsible for keeping the records " +
        "up to date. The names of the contributors can be read using the " +
        "commands 'read all names' or 'read names <...>'. The <...> may " +
        "contain wildcards, like 'a*' to read all names starting with an " +
        "'a'. The general overview of the contributions can also be " +
        "examined.\n"); 
    add_item( ({ "door", "entrance door" }),
        "The door in the east wall is quite sturdy, made of oak wood and " +
        "polished to a smooth and stylish barrier against unwanted elements " +
        "when the treasurer is away.\n" );
    add_item( ({ "board", "chalkboard", "balance", "current balance" }),
        chalkboard_description);
    add_item( ({ "overview", "general overview" }),
        overview_description);

    add_exit("/d/Sparkle/area/city/rooms/streets/market_square", "south");
 
    add_prop(ROOM_S_MAP_FILE, "sparkle_city_genesis.txt");

    clone_object(DONATION_BOARD)->move(this_object(), 1);
}

/*
 * Function name: donation
 * Description  : Allows one of the collectors to add a donation.
 * Arguments    : string str - the command line argument.
 * Returns      : int - Success/failure.
 */
nomask int
donation(string str)
{
    string *words;
    int    amount;
    int    foreign_amount;

    /* Access failure. */
    if (member_array(this_interactive()->query_real_name(),
        DONATION_COLLECTORS) == -1)
    {
        notify_fail("This command is for donation collectors only.\n");
        return 0;
    }

    if (!strlen(str))
    {
        notify_fail("What donation?\n");
        return 0;
    }

    words = explode(lower_case(str), " ");
    switch(words[0])
    {
    case "add":
        if (sizeof(words) != 5)
        {
            notify_fail("Syntax: donation add <name> <currency> " +
                 "<amount> <EUR equivalent>\n");
            return 0;
        }
        DONATION_MASTER->add_donation(words[1], upper_case(words[2]),
            atoi(words[3]), atoi(words[4]));
        return 1;

    case "remove":
        if (sizeof(words) != 2)
        {
            notify_fail("Syntax: donation remove <name>\n");
            return 0;
        }
        DONATION_MASTER->remove_donation(words[1]);
        return 1;

    case "second":
        if (sizeof(words) != 3)
        {
            notify_fail("Syntax: donation seconds <name> <name of second>\n");
            return 0;
        }
        DONATION_MASTER->add_second(words[1], words[2]);
        return 1;

    case "stats":
        DONATION_MASTER->report_statistics(1);
        return 1;

    default:
        notify_fail("There is no subcommand '" + words[0] +
            "' to donation.\n");
        return 0;
    }

    notify_fail("Impossible end of donation command. Please report!\n");
    return 0;
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
    return DONATION_COLUMN->read(str);
}

/*
 * Function name: init
 * Description  : Links the commands to the player.
 */
nomask void
init()
{
    ::init();

    add_action(donation, "donation");
    add_action(read,     "read");
}
