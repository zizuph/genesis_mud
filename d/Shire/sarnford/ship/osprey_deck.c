#pragma save_binary

inherit "/d/Genesis/ship/deck";
inherit "/d/Gondor/common/lib/time.c";

#include <stdproperties.h>
#include "/d/Shire/common/defs.h"


void
create_deck()
{
    set_short("inside a small, slender boat");

    set_long("You are on the wooden deck of a small, slender sailing ship " +
        "named 'Osprey', which rides eagerly on the waves, as if in anticipation " +
        "of getting out in the open sea to race against the open wind. " +
        "The ship has a single mast with a large, white sail which has been " +
        "raised, which captures even the slightest breeze. A tall, wooden " +
        "railing circles the edge of the ship, helping to avoid any " +
        "potential accidents where a passenger might fall overboard. A " +
        "small cabin is nestled in the stern of the ship, yet remains " +
        "clearly off-limits to passengers. A narrow opening on the port " +
        "side allows a plank to be extended for people to get on or " +
        "off the ship when lodged at a berth.\n");
    add_item(({"mast", "single mast"}),
        "This wooden mast seems quite tall for such a small ship, with one " +
        "great, white sail billowing out in the wind. There are several " +
        "handholds on the side of the mast, allowing sailors to climb " +
        "up the mast if needed.");
    add_item(({"sail", "white sail"}),
        "There is a large, white sail which rides open on the mast, catching " +
        "the wind fully in its bosom. You notice with some interest that " +
        "the sail is in remarkably good repair.");
    add_item(({"deck", "wooden deck", "down"}), 
        "This wooden deck looks a little worn from what you assume to " +
        "be years of heavy use. However, you notice that occasionally " +
        "there is one sailor or another vigorously scrubbing the deck, " +
        "keeping it clean and tip-top shape.");
    add_item(({"ship", "sailing ship"}),
        "You are on the wooden deck of a small, slender sailing ship " +
        "which rides eagerly on the waves, as if in anticipation of " +
        "getting out in the open sea to race against the open wind. " +
        "The ship has a single mast with a large, white sail which has been " +
        "raised, which captures even the slightest breeze. A tall, wooden " +
        "railing circles the edge of the ship, helping to avoid any " +
        "potential accidents where a passenger might fall overboard. A " +
        "small cabin is nestled in the stern of the ship, yet remains " +
        "clearly off-limits to passengers. A narrow opening on the port " +
        "side allows a plank to be extended for people to get on or " +
        "off the ship when lodged at a berth.");    
    add_item(({"up", "sky"}), 
        "It looks like a wonderful day for sailing.");
    add_item(({"railing", "rail", "wooden railing"}), 
        "There is a tall, wooden railing which encircles the ship, preventing " +
        "people from falling overboard. This railing is not very ornate, but " +
        "appears to be clean, polished and generall well-maintained. A " +
        "small opening on the port side allows a plank to be placed for " +
        "people boarding or disembarking the ship.");
    add_item(({"cabin", "small cabin"}), 
        "Occasionally, you see a variety of sailors coming in or out " +
        "of the small cabin which sits at the stern of the ship. However, " +
        "it is quite clear that this cabin is only accessible to memebrs " +
        "of the crew.");
    add_item(({"plank", "port side", "opening"}), 
        "There is a narrow opening on the port side of the ship, with a " +
        "long, sturdy plank tied up beside it. This was where you " +
        "entered the ship, and undoubtedly where you will exit at the " +
        "end of your journey.");

}
