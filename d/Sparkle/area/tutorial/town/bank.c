/*
 *  /d/Sparkle/area/tutorial/town/bank.c
 *
 *  This is the Bank of Greenhollow. It teaches about money and
 *  banking.
 *
 *  Created August 2005, by Cooper Sherry (Gorboth)
 */
#pragma save_binary
#pragma strict_types
#include "../defs.h"

inherit SD_ROOM;
inherit "/lib/bank";

#include <stdproperties.h>

/* definitions */
#define  TUTORIAL_CHAPTER    25  /* the chapter for the sign */


/* prototypes */
public void        create_silverdell();
public void        init();
public void        hint(string arg);


/*
 * Function name:        create_silverdell
 * Description  :        set up the room
 */
public void
create_silverdell()
{
    set_short("the Bank of Greenhollow");
    set_long("This is the Bank of Greenhollow. In banks you can store your"
      + " money for safekeeping and make change with the coins you"
      + " have. A sign is posted beside the deposit, and a large"
      + " plaque has been mounted on the wall. For tutorial"
      + " information, you can <read poster> to read a poster that"
      + " has been placed near the door.\n\n");

    add_item( ({ "bank", "here", "building", "area",
                 "silverdell bank", "bank of greenhollow" }), long);

    add_item("plaque","@@standard_bank_sign");
    add_cmd_item("plaque","read", "@@standard_bank_sign");

    config_default_trade();
    set_bank_fee(1);       /* super low for newbie area */
    config_trade_data();

    add_door_items();
    add_indoor_items();

    prevent_attacks();
    reset_room();

    add_prop(ROOM_I_INSIDE, 1);

    add_exit("street_4", "east");
} /* create_silverdell */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();
    bank_init();

    add_action(hint, "hint");
} /* init */


/*
 * Function name:        hint
 * Description  :        give the player a hint if they get stuck
 * Arguments    :        string - what the player typed
 * Returns      :        int 1
 */
public int
hint(string arg)
{
    write("Sure, here's a hint. <Deposit> your money here in the bank."
      + " You can always come back and <withdraw> it later when you"
      + " need to spend your coins. This way, if you happen to die,"
      + " your money is right here, and you won't have to go and get"
      + " the coins off your corpse.\n");
 
    return 1;
} /* hint */


/*
 * Function name:       reset_room
 * Description  :       restore npcs and signs as needed
 */
public void
reset_room()
{
    if (!present("_tutorial_sign"))
    {
        add_sign(TUTORIAL_CHAPTER, "poster");
    }

    if (!present("deposit"))
    {
        room_add_object("/d/Genesis/obj/deposit");
    }
} /* reset_room */
