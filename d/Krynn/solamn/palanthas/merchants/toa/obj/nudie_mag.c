/*
 * Food available from the Draft Pub in the Tower of Arms in Palanthas.
 *
 * Mortis 09.2014
 */

#pragma save_binary
#pragma strict_types

#include <macros.h>
#include <composite.h>
#include "../../../local.h"

inherit "/std/object.c";
inherit "/lib/keep";

public void
create_object()
{
    set_name("pamphlet");
    set_pname("pamphlets");
    add_name(({"nudie_mag"}));
    set_adj("well-worn");
    add_adj(({"well", "worn"}));
    set_short("well-worn pamphlet");
    set_long("Many small, sheets of paper have been bound together with "
    + "rings. They contain images of people. Would you like to <peruse "
    + "pamphlet>? Or <flash pamphlet> so that others can have a look?\n");
}

void
init()
{
    ::init();
    ADA("peruse");
    ADA("flash");
}

int
peruse(string str)
{
    if (!str || !parse_command(str, ({}), "[well-worn] [well] [worn] 'pamphlet'"))
    { return 0; }

    string response = one_of_list(({"gasp", "blush", "giggle exci",
        "moan softly", "choke", "cough", "fondle myself",
        "fondle pamphlet", "wiggle erotic", "smile shy", "grin hung",
        "boggle", "snarl lust", "ponder naked people gyrating."}));

    TP->catch_msg("You delve into the " + short() + ". It's filled with "
    + "drawn images of naked people gyrating wildly! They're naked!\n");
    tell_room(E(TP), QCTNAME(TP)+ " peruses " + HIS(TP) + " " + short()
    + ", and " + HIS(TP) + " eyes suddenly widen.\n", ({TO, TP}));
    TP->command(response);

    return 1;
}

int
flash(string str)
{
    if (!str || !parse_command(str, ({}), "[well-worn] [well] [worn] 'pamphlet'"))
    { return 0; }

    string response = one_of_list(({"gasp", "blush", "giggle exci",
        "moan softly", "choke", "cough", "fondle myself",
        "fondle pamphlet", "wiggle erotic", "smile shy", "grin hung",
        "boggle", "snarl lust", "ponder naked people gyrating."}));

    TP->catch_msg("You flash your " + short() + " to everyone exposing "
    + "them to images of naked people gyrating! It's contraband!\n");
    tell_room(E(TP), QCTNAME(TP)+ " throws open " + HIS(TP) + " " + short()
    + ". It is filled with drawn images of people gyrating. They're naked!\n"
    + "You gasp in response!\n", ({TO, TP}));

    return 1;
}

string
query_recover()
{
    return MASTER + ":" + query_keep_recover();
}

void
init_recover(string arg)
{
    init_keep_recover(arg);
}
