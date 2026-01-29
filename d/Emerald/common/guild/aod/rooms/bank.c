/*
 *  /d/Emerald/common/guild/aod/rooms/bank.c
 *
 *  This is the Bank for the Army of Darkness. It is only operable if
 *  the guild has collected a sufficient number of Gnome skulls.
 *
 *  Created July 2006, by Cooper Sherry (Gorboth)
 */
#pragma save_binary
#pragma strict_types
#include "../defs.h"

inherit AOD_ROOM_DIR + "cave_room";
inherit AOD_LIB_DIR + "add_spike";
inherit "/lib/bank";

/* prototypes */
public void        create_cave_room();
public void        init();
public void        reset_room();


/*
 * Function name:        create_cave_room
 * Description  :        set up the room
 */
public void
create_cave_room()
{
    set_short("the Army of Darkness bank");
    set_em_long("The octagonal walls of this chamber are only barely"
      + " large enough to contain the massive strongroom that has"
      + " been erected here. This is the bank of the Army of"
      + " Darkness. Apparently, enough gnomish mind fluid has"
      + " been consumed for at least one ogre to understand the"
      + " art of banking. You can see him sitting beside a plaque"
      + " inside the strongroom.\n");

    add_item( ({ "here", "area", "room", "chamber", "bank" }), long);
    add_item( ({ "perimeter", "octagonal perimeter", "wall",
                 "walls", "octagonal walls", "octagonal wall",
                 "octagon" }),
        "The perimeter of the room has been much more carefully"
      + " constructed than most things in these caves.\n");
    add_item("plaque","@@standard_bank_sign");
    add_cmd_item("plaque","read", "@@standard_bank_sign");

    config_default_trade();
    set_bank_fee(30);        /* not too low */
    config_trade_data();

    add_spike("bank");

    add_exit("tunnel2", "west");
    reset_room();
} /* create_cave_room */


/*
 * Function name:        init
 * Description  :        initialize the bank features
 */
public void
init()
{
    ::init();
    bank_init();
} /* init */


/*
 * Function name:       reset_room
 * Description  :       add the bank deposit
 */
public void
reset_room()
{
    object  deposit;

    if (!present("deposit"))
    {
        deposit = clone_object("/d/Genesis/obj/deposit");
        deposit->set_short("enormous strongroom");
        deposit->add_adj("enormous");
        deposit->set_long("Though much like a typical gnomish"
          + " strongroom in shape, this is by far the most enormous"
          + " one you have ever seen! It is a huge fort-like hut."
          + " It has a massive opening protected by thick steel"
          + " bars that are at least two inches thick. A sign hangs"
          + " near the bars, and a teller sits perched behind the"
          + " bars.\n");
        deposit->remove_item("gnome");
        deposit->add_item( ({ "ogre", "teller", "bank teller",
                              "ogre bank teller", "ogre teller" }),
            "The ogre who sits inside the strongroom has a curious"
          + " gleam in his eye ... you could almost say a gnomish"
          + " gleam. It is the closest an ogre has ever come to"
          + " looking intelligent.\n");
        deposit->remove_item("opening");
        deposit->add_item( ({ "opening", "counter", "massive opening" }),
            "It is the counter, protected by steel bars. Behind it you"
          + " find an ogre bank teller.\n");
        deposit->set_bank_id(3202, "Army of Darkness");
        deposit->move(this_object());
    }
} /* reset_room */