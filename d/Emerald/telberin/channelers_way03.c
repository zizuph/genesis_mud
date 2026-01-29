#include "defs.h"

inherit TELBERIN_CHANNELERS_WAY;

public void
create_channelers_way()
{
    set_em_long("There is a strange air about the travellers on this"
      + " road, as they go about their business. You stand on the"
      + " southwestern rim of Channelers Way as it loops around to"
      + " meet with a plaza to the southeast. To the north it runs"
      + " back toward the city, arcing elegantly alongside the clear"
      + " waters of a reflecting pool which runs from this point"
      + " directly to the foundations of the Tower of Telan-Ri."
      + " Buildings crowd the street to the west and south. A plain"
      + " brick building stands out from the others. A sign hangs above"
      + " its doorway.\n");

    add_item( ({ "shop", "store", "magic supplies", 
                 "magic supply store", "plain building",
                 "plain brick building", "magic supply shop",
                 "supply store", "supply shop", "brick building" }),
        "A plain brick building, directly to the west, has a large"
      + " plaque mounted above its doorway.\n");
    add_item( ({ "plaque", "sign", "white sign", "alabaster sign" }),
        "The sign is in the shape of an ellipse, much like the layout"
      + " of the city streets. It reads in bold letters, 'Magic"
      + " Supply Shop - Closed for Repairs.'\n");

    add_cmd_item( ({ "sign", "white sign", "alabaster sign",
                     "letters", "plaque" }),
                  ({ "read" }),
        "It reads, 'Magic Supply Shop.'\n");

    set_no_exit_msg( ({ "west" }),
        "The door to the store is closed and locked.\n");
    add_exit("/d/Emerald/telberin/magic/channelers_plaza", "southeast");
    add_exit("channelers_way02", "north");
}


/*
 * Function name:        do_enter
 * Description  :        allow players to try to enter the library
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_enter(string arg)
{
    if (!strlen(arg))
    {
//      notify_fail("Enter what?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[the] [plain] [brick] [magic] [supply]"
      + " 'shop' / 'store' / 'building'"))
    {
        return 0; /* can't parse the player's syntax */
    }

    if (this_player()->query_wiz_level())
    {
        write("Normally, we would move the player 'west' here, using"
          + " 'command.' Since you are a wizard, that won't work. Simply"
          + " go 'west' yourself.\n");
        return 1;
    }

    this_player()->command("west");
    return 1;
} /* do_enter */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(do_enter, "enter");
} /* init */
