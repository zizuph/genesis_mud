/*
 * Bank of the Elemental Temple of Calia
 * 
 * Created by Petros, April 2010
 */

#pragma strict_types

#include <money.h>
#include "defs.h"

inherit TEMPLE_ROOM_BASE;
inherit "/lib/bank";

// Defines

// Prototypes

public void
create_temple_room()
{
    set_short("A golden temple treasury");
    set_long("You find yourself in a golden temple treasury. This particular "
        + "room is quite ornamented. Gemstones bejewel the heavy gold panels "
        + "on the walls. Set into the southeast wall is a heavy golden vault "
        + "with thick hinges. A few robed gnomes are busy processing "
        + "transactions, oiling the hinges, and polishing gemstones, the "
        + "gold panels, and the crystalline floor. A golden plaque is "
        + "prominently displayed for all to see and beneath it is a sign "
        + "written in a whimsical script. You can see the hallway of "
        + "the outer circle through the northwest exit.\n\n");
                   
    try_item( ({ "treasury", "golden treasury", "temple treasury",
        "golden temple treasury", }),
        "This treasury is certainly impressive. Everything just gleams, from "
      + "the gold panels on the walls to the crystalline floor to the "
      + "inlaid gemstones.\n");
    
    try_item( ({ "gold panels", "panels", "panel", "gold panel",
        "heavy panels", "heavy gold panels", "heavy panel", "heavy gold panel",
        "walls", "wall" }),
        "Gemstones bejewel the heavy gold panels that cover most of the walls.\n");
    
    try_item( ({ "gemstones", "gemstone" }),
        "Lots of different types of gemstones are inlaid into the gold panels "
      + "making it a rather beautiful, if rather expensive, display. There is "
      + "no doubt where all the expensive fees for treasury transactions "
      + "go.\n");
    
    try_item( ({ "vault", "golden vault", "heavy golden vault", "heavy vault",
            "thick hinges", "hinges", "hinge", "thick hinge" }),
        "One would think that a vault made out of gold would be rather "
      + "easy to break into. However, from the relaxed manner of the gnomes "
      + "who manage this treasury, you are assured that you money is going "
      + "to be safe. After all, who messes with the GoG?!?!\n");
    
    try_item( ({ "gnomes", "gnome", "robed gnomes" }),
        "The gnomes of Genesis are busy managing this branch of the GoG "
      + "bank, also known as the temple treasury. Some are busy with "
      + "customers, while others are busy cleaning and making sure that "
      + "the bank sparkles.\n");

    try_item( ({ "hallway", "nortwest", "northwest exit" }),
        "There is only one exit here and it is to the northwest. You can "
      + "see the hallway of the outer circle of the temple just outside "
      + "the treasury.\n");
            
    try_item( ({ "plaque", "golden plaque" }),
        "@@standard_bank_sign");
    add_cmd_item("plaque", "read", "@@standard_bank_sign");

    // Clone the bank deposit here.
    object bank = clone_object("/d/Genesis/obj/deposit");
    // Setting the bank id allows gems to be stored here. Make sure
    // to update /d/Calia/open/SHOPS when adding new bank ids.
    bank->set_bank_id(1404, "the Elemental Temple of Calia");
    bank->move(this_object(), 1);
    bank->set_no_show_composite(1);
    
    // All the configuration for a bank goes below
    config_default_trade();
    set_bank_fee(24);
    config_trade_data();
    set_money_give_out(({100000,100000,100000,100000}));
    set_money_give_reduce(({0,0,0,0}));
    set_money_give_max(100000);
    
    // Add exits below
    add_exit(ELEMENTALIST_TEMPLE + "outer12", "northwest");
}

void
init()
{
    ::init();
    bank_init();
}
