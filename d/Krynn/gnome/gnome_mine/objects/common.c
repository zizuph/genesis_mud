/*  
    Common functions to dissarm gizmos to get clockwork for pickaxe quest

    Made by: Maelstrom, 2016/05

*/

#include "../defs.h"

int
do_dissarm(string str)
{
    int found = 0;
    object c_item;
	object tp = this_player();

    if (!str)
    {
        notify_fail("Disarm what?\n");
        return 0;
    }

    found = 1;
	c_item = clone_object(OBJ_DIR + "clockwork_quest");

    if (c_item->move(tp))
    {
        tp->catch_msg("You are too heavily loaded to " +
                    "do that.\n");
        c_item->remove_object();
    }
    else
    {
        tp->catch_msg("You take apart the clockwork from the item and throw away the rest.\n");
        remove_object();
    }


    if (found > 0)
    {
        return 1;
    }

    notify_fail("Disarm what?\n");
    return 0;
}

int
do_press(string str)
{
    object tp = this_player();


    if (!str)
    {
        notify_fail("Press what?\n");
        return 0;
    }


    if (str == "switch" || str == "switch on toothbrush")
    {
        tp->catch_msg("You curiously press the switch, but nothing happens; probably broken.\n");
        return 1;
    }

    notify_fail("Press what?\n");
    return 0;    
}

void
init()
{
    ::init();
    add_action(do_dissarm, "disarm");
    add_action(do_dissarm, "break");
    add_action(do_dissarm, "smash");
    add_action(do_press, "press");
    add_action(do_press, "activate");
    add_action(do_press, "turn");
    add_action(do_press, "flick");
}