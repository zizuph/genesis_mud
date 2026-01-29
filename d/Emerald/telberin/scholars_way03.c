#include "defs.h"
#include "/d/Emerald/blackwall/delrimmon/defs.h"

inherit TELBERIN_SCHOLARS_WAY;

#include <macros.h>
#include <language.h>
#include <stdproperties.h>

public void
create_scholars_way()
{
    set_em_long("Scholars Way curves sharply to the northwest as it"
      + " travels in that direction toward a large open plaza. To the"
      + " south it curves gradually along its eliptical arc toward"
      + " the center of Telberin and the Royal Circle. A strange device"
      + " has been erected to the west, just beside the reflecting pool"
      + " which spans the length of the boulevard.\n");

    add_item( ({ "plaza", "scholars plaza", "scholar plaza",
                 "large plaza", "open plaza", "large open plaza",
                 "northwest" }),
        "Northwest of here, Scholars Way opens into a plaza which"
      + " is ringed by many buildings.\n");
    add_item( ({ "device", "strange device" }),
        "The device beside the pool appears to be slowly drawing"
      + " water up a beam of light which disappears into an opening"
      + " along a section of the device which hangs over the pool.\n");
    add_item( ({ "beam", "beam of light" }),
        "Somehow, the beam of light has captured water from the pool,"
      + " and is drawing it up into the device through a hole which"
      + " is on the underbelly of a section of the device which"
      + " hangs over the water.\n");
    add_item( ({ "section", "section of the device" }),
        "A section of the device hangs over the reflecting pool."
      + " It shudders every so often when things such as leaves or"
      + " other debris are carried along with the water into a hole"
      + " on its underbelly by a beam of light.\n");
    add_item( ({ "hole", "opening" }),
        "A hole on the device is constantly receiving small amounts"
      + " of water from the pool which are carried into it within"
      + " a beam of light. Sometimes sparks flash from inside the"
      + " hole.\n");
    add_item( ({ "spark", "sparks" }),
        "Each time a spark appears, from the hole, you hear a slight"
      + " 'whump' as the device shudders.\n");
    add_item( ({ "underbelly", "underbelly of the device" }),
        "A hole in the underbelly of the device is apparently the"
      + " source of the beam of light.\n");

    add_exit("/d/Emerald/telberin/science/scholars_plaza", "northwest");
    add_exit("scholars_way02", "south");

    FIX_EUID
}


/*
 * Function name:        mess_with_device
 * Description  :        allow the player to try to figure out
 *                       this nasty red-herring
 * Arguments    :        string arg -- what the player typed
 * Returns      :        1 -- success, 0 -- failure
 *
 */
public int
mess_with_device(string arg)
{
    mixed   fail;
    object  drop_ob;

    if (!strlen(arg))
    {
        NFN0(CAP(QVB) + " what?");
    }

    if (!parse_command(arg, all_inventory(TP),
        "[the] %o [in] [to] [into] [the] [strange]"
      + " 'hole' / 'opening' / 'device' [of] [on] [the]"
      + " [strange] [device]", drop_ob))
    {
        return 0; /* can't parse player syntax */
    }

    if (drop_ob->query_prop(OBJ_M_NO_DROP))
    {
        NFN0("You cannot get rid of the " +drop_ob->short()+ ".");
    }

    write("You try to " + QVB + " the " + drop_ob->short() + " into"
        + " the strange device. Sparks fly from the opening and the"
        + " entire thing shudders violently as it rejects your"
        + " attempt!\n");
    say(QCTNAME(TP) + " tries to " + QVB + " " + LANG_ADDART(drop_ob->short())
        + " into the strange device, but only succeeds in causing"
        + " the thing to shudder violently.\n");

    return 1;
} /* mess_with_device */


/* 
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(mess_with_device, "put");
    add_action(mess_with_device, "place");
    add_action(mess_with_device, "insert");
    add_action(mess_with_device, "stick");
    add_action(mess_with_device, "shove");
} /* init */

