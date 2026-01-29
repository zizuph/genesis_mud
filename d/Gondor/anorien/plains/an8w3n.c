/*
 * Anorien - /d/Gondor/anorien/plains/an8w3n.c
 *
 * Varian 2016
 */

#pragma strict_types

#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>
 
inherit ANORIEN_STD_DIR + "base";

/*
 * Function name:        create_plains_room()
 * Description  :        Creates the plains from from the base file
 *                       /d/Gondor/anorien/std/base.c
 */

void 
create_plains_room()
{
    set_items_plains();
    set_herbs_8();
    
    set_short("Anorien");
    set_long("You are wandering through fields of tall grass, their " +
        "green lengths brushing against you as the wind gently blows " +
        "past. Countless wildflowers of all colours sway under the " +
        "bright light of the " + VBFC("sun_moon") + " above, while " +
        "hundreds of trees gather in groves across the lengths of the " +
        "rolling plains. Hidden amongst the trees, you notice a small pool " +
        "of clean cool water fed by a small spring hidden amongst a small " +
        "pile of rocks. To the north, the Entwash flows east to empty " +
        "into the Anduin as it runs south towards the sea. Far to " +
        "the south, the jagged peaks of the White Mountains cover the " +
        "horizon, beautifully cloaked in the " + VBFC("light_type") +
        " that shines down upon them.\n");

    add_item(({"pool", "water"}),
        "There is a small pool of water here, fed by a spring that bubbles " +
        "out merrily from a pile of rocks nearby.\n");
    add_item(({"rocks", "pile", "pile of rocks"}),
        "This is an ordinary pile of rocks, made noticable only by the " +
        "cool spring of fresh water that is spilling out from them and " +
        "emptying into the nearby pool.\n");
    add_item(({"spring", "waterfall"}),
        "This spring bursts forth in a small waterfall of clean, cool " +
        "water that drops down the side of the rocks and into the pool " +
        "below.\n");

    add_prop(OBJ_I_CONTAIN_WATER, 1);

    add_trees(1);

    add_exit(PLAINS_DIR + "an7w4n","southwest",0,2,1);
    add_exit(PLAINS_DIR + "an8w4n","south",0,2,1);
    add_exit(PLAINS_DIR + "an9w4n","southeast",0,2,1);
    add_exit(PLAINS_DIR + "an7w3n","west",0,2,1);
    add_exit(PLAINS_DIR + "an9w3n","east",0,2,1);
    add_exit(PLAINS_DIR + "an7w2n","northwest",0,2,1);
    add_exit(PLAINS_DIR + "an8w2n","north",0,2,1);
    add_exit(PLAINS_DIR + "an9w2n","northeast",0,2,1);

    set_drink_from(({"water", "pool", "spring"}));
}
/*
 * Function name:        init
 * Description  :        Initializes commands for players
 */
void
init()
{
    ::init();
    init_drink();
    add_action("do_swim","swim");
}
/*
 * Function name:        drink_message
 * Description  :        Provides a description for drinking from the pool
 */
public void
drink_message(string from)
{
    write("You cup your hands, bend down near the pool and take a soothing " +
        "drink of cool, clean water that is bubbling forth from the " +
        "spring.\n");
    say(QCTNAME(TP) + " bends down near the pool and cupping their hands, " +
        "takes a drink of spring water.\n");
}
/* drink_message */

/*
 * Function name:        do_swim
 * Description  :        Provides an emote to swim in the pool
 * Returns      :        int 0 - Prompt for proper syntax
 *                       int 1 - Returns the emote
 */
int
do_swim(string str)
{
    if(!str)
    {
        notify_fail("Where are you trying to swim? In the pool?\n");
        return 0;
    }
    if((str != "water")  && (str != "pool") && (str != "in the pool")
            && (str != "in the water"))
    { 
        ("Where are you trying to swim? In the pool?\n");
        return 1;
    }
    write("Quickly and neatly stacking your belongings at the side of " +
        "the pool, you dive into the cold, refreshing waters of the " +
        "pool.\n\nYou find the swim rather invigorating and relaxing, " +
        "your own small slice of paradise where you can forget about " +
        "the bustle of the world.\n");
    SAYBB(" takes a relaxing dip in the small pool.\n");
    return 1;
}
/* do_swim */