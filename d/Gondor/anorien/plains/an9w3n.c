/*
 * Anorien - /d/Gondor/anorien/plains/an9w3n.c
 * Ruins, an old copy of the fort key in Cair Andros is hidden here
 *
 * Varian 2016
 */

#pragma strict_types

#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>
 
inherit ANORIEN_STD_DIR + "base";

object mbox;
int open;

/*
 * Function name:        create_plains_room()
 * Description  :        Creates the plains from from the base file
 *                       /d/Gondor/anorien/std/base.c
 */
void 
create_plains_room()
{
    set_items_plains();
    set_herbs_5();
    
    set_short("Anorien");
    set_long("You are standing atop a low hill in the middle of Anorien. " +
        "The gentle " + VBFC("daylight_desc") + " from the " + 
        VBFC("sun_moon") + " above reveals thousands of colourful " +
        "wildflowers nestled amongst the tall green grass of the fields " +
        "that surround you. Hundreds of trees have huddled together in " +
        "dozens of dense groves that have been sprinkled around the " +
        "nearby plains. To the north, you can see the grey water in the " +
        "mouths of the Entwash slowly emptying into the rushing waters " +
        "of the Anduin river in the east. Rising up across the " +
        "southern horizon, the jagged snow-capped peaks of the White " +
        "Mountains scrape at the " + VBFC("day_desc") + " sky above. A " +
        "small cluster of boulders seems to have gathered at the top of " +
        "the hill here.\n");

    add_item(({"hill","low hill"}),
        "This hill stands a little higher than many of the others nearby, " +
        "and has a small collection of boulders sitting on top.\n");
    add_item(({"boulder","boulders","collection"}),
        "These boulders appear to be the ruins of what was once a small " +
        "watchtower.\n");
    add_item(({"stones","stone","block","blocks"}),
        "@@block");
    add_item(({"box","metal box"}),
        "@@box");
    add_item(({"tower","ruins","watchtower","small tower","small watchtower"}),
        "A large collection of boulders and stones is all that remains of " +
        "what was once a small watchtower, now long abandoned and " +
        "forgotten.\n");

    add_trees(1);

    add_exit(PLAINS_DIR + "an8w4n","southwest",0,2,1);
    add_exit(PLAINS_DIR + "an9w4n","south",0,2,1);
    add_exit(PLAINS_DIR + "an10w4n","southeast",0,2,1);
    add_exit(PLAINS_DIR + "an8w3n","west",0,2,1);
    add_exit(PLAINS_DIR + "an10w3n","east",0,2,1);
    add_exit(PLAINS_DIR + "an8w2n","northwest",0,2,1);
    add_exit(PLAINS_DIR + "an9w2n","north",0,2,1);
    add_exit(PLAINS_DIR + "an10w2n","northeast",0,2,1);

    add_cmd_item( ({ "metal box", "box" }),
        "open", "@@open_box" );
    add_cmd_item( ({ "metal box", "box" }),
        "close", "@@close_box" );

    mbox = clone_object(AN_OBJ_DIR + "box.c");
    mbox->set_no_show();
    mbox->move(TO);

    reset_room();
}

string
block()
{
    TP->add_prop("_obj_i_mbox_found", 1);
    if (open)
    return "Hidden in the stone blocks is an open metal box.\n";
    return "Hidden in the stone blocks is a closed metal box.\n";
}

string
box()
{
    TP->add_prop("_obj_i_mbox_found", 1);
    if (open)
    return "This is an open metal box that is wedged between some heavy " +
        "stone blocks.\n";
    return "This is a closed metal box that is wedged between some heavy " +
        "stone blocks.\n";
}


/*
 * Function name:        open_box
 * Description  :        Allows players to open the box where they key is
 */
int
open_box(string str)
{
    if (TP->query_prop("_obj_i_mbox_found") != 1)
    {
       NF("What box?\n");
       return 0;
    }

    if (open)
    {
       write("The metal box is already open.\n");
       return 1;
    }

    write("You open the metal box.\n");
    say(QCTNAME(TP) + " opens a metal box they found hidden in the ruins.\n");
    open = 1;
    mbox->unset_no_show();
    return 1;
}
/* open_box */

/*
 * Function name:        close_box
 * Description  :        Allows players to close the box again
 */
int
close_box(string str)
{    
    if (TP->query_prop("_obj_i_mbox_found") != 1)
    {
       NF("What box?\n");
       return 0;
    }

    if (!open)
    {
        write("The metal box is already closed.\n");
        return 1;
    }
    
    write("You close the metal box.\n");
    say(QCTNAME(TP) + " moves closer to the ruins to inspect the stone " +
        "blocks.\n");
    open = 0;
    mbox->set_no_show();
    return 1;
}
/* close_box */

/*
 * Function name:        get_key
 * Description  :        Creates the fort key
 */
void
get_key()
{
    object key;

    if(!mbox)
        return;

    if(present("key", mbox))
        return;

    key = clone_object(AN_OBJ_DIR + "fort_hall_key.c");
    key->move(mbox,1);
}
/* get_key */

void
reset_room()
{
    int n;
    
    get_key();
}