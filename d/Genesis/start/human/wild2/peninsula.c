/*
 * 	peninsula.c			Styles.   3 Mar 1993
 *
 *  Modified - Varian  March, 2016
 */

#pragma strict_types

#include "wild.h"
#include <stdproperties.h>
#include <macros.h>

inherit THIS_DIR + "base";

/*
#define BELLSOUND			" "
#define TELL_STY(str)       find_living("styles")->catch_tell( \
							ctime(time()) + BELLSOUND + str + "\n")
 */

void
create_wild_room()
{
    set_items_sparkle();
    set_herbs();

    set_short("At the peninsula");
    set_long("You are standing out on a peninsula that rises high up into " +
        "the air, gazing out across the rolling waves of the Pen Sea as " +
        "they crash up against the shore. The view from here is very good, " +
        "as you can clearly see the bustling port of Sparkle to the south . " +
        "While the sandy beaches that frame the moorlands, trail off into " +
        "the northern horizon. You can even see the jagged peaks of the " +
        "Grey Mountains as they surround surround Sparkle valley to the " +
        "west. Fresh air from a strong sea wind flutters through your hair, " +
        "invigorating your very soul. The stone path you have been " +
        "following ends here, leaving the mists that hang over the moors " +
        "to the west and allowing you to peek down a rocky hillside that " +
        "is too steep to descend safely.\n");

    add_trees(0);

    add_exit(THIS_DIR + "moor4","west");

    set_no_exit_msg(({"southeast","east","northeast"}),
        "It is far too steep and dangerous to reach the shore in that " +
        "direction! It looks like you can only follow the path west from " +
        "here.\n");
    set_no_exit_msg(({"south","north","northwest","southwest"}),
        "You take a step into the rolling waves of the Pen Sea that " +
        "are crashing up against the shore. It seems obvious that you " +
        "cannot go any further in this direction.\n");

    add_item(({"sparkle","walls","wall","wooden walls","wooden wall",
            "stockade","wooden stockade"}),
        "To the south, you are able to see the wooden walls of the " +
        "stockade that surrounds Sparkle, jutting out into the " +
        "blue waters of the Pen Sea.\n");
    add_item(({"moor","moorland","moors","fens","fen","mist","fog","mists"}),
        "Immediately to the west, a foggy mist settles over the low " +
        "hills of the moors that rest between the Diamond River and the " +
        "Pen Sea.\n");
    add_item(({"peninsula","beach","sandy beach","sand","hill",
            "hillside"}),
        "A long sandy beach has been created where the Pen Sea brushes " +
        "up against the moors here. The beach stretches out from the " +
        "walls of Sparkle just visible to the south and around this " +
        "peninsula before trailing off in the distance to the north.\n");
    add_item(({"sea","coast","shore","pen sea","water","waters","waves",
            "wave"}),
        "You can see the choppy waves of the Pen Sea rolling up to crash " +
        "against the shoreline that surrounds you on almost every side.");
    add_item(({"tree","trees","grove","groves"}),
        "There are some small groves of trees that are growing deeper into " +
        "the moors, away from the peninsula.\n");
    add_item(({"horizon"}),
        "You are standing high above the Pen Sea on a peninsula which " +
        "provides a great view in every direction\n\nWhich horizon " +
        "did you want to look at?\n");
    add_item(({"north horizon","northern horizon","north"}),
        "You can see a sandy beach separating the moors from the Pen Sea " +
        "winding off into the northern horizon.\n");
    add_item(({"west horizon","western horizon","west"}),
        "You can see some misty moorlands and then the rest of Sparkle " +
        "valley spreading out under the Grey Mountains west from here.\n");
    add_item(({"east horizon","eastern horizon","east"}),
        "Endless lines of massive blue waves roll across the Pen Sea as " +
        "you gaze out upon the eastern horizon.\n");
    add_item(({"south horizon","southern horizon","south"}),
        "To the south you can see the busy port of Sparkle, the cradle of " +
        "humanity, as it stands proudly on the coast of the Pen Sea.\n");
    add_item(({"northeast horizon","northeastern horizon","northeast"}),
        "Endless lines of massive blue waves roll across the Pen Sea as " +
        "you gaze out upon the horizon to the northeast.\n");
    add_item(({"northwest horizon","northwestern horizon","northwest"}),
        "You can see some misty moorlands and then the rest of Sparkle " +
        "valley spreading out under the Grey Mountains as you gaze " +
        "off to the northwest.\n");
    add_item(({"southeast horizon","southeastern horizon","southeast"}),
        "Endless lines of massive blue waves roll across the Pen Sea as " +
        "you gaze out upon the horizon to the southeast.\n");
    add_item(({"southwest horizon","southwestern horizon","southwest"}),
        "looking southwest you can see the busy port of Sparkle, the " +
        "cradle of humanity, as it stands proudly on the coast of the " +
        "Pen Sea.\n");
    
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_wide.txt");
}

/*
 * Function name: init()
 * Description  : Called when a living object enters the room.
 */
public void
init() {
    ::init();

	// Room actions
    //add_action("function_cmd", "cmd");
	
	//Alert Styles about the visitor. EDIT 200826 by Styles. This is currently not needed.
	//TELL_STY(TP->query_real_name() +" visited the peninsula.\n");
}