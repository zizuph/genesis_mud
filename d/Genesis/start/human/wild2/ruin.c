/* 	
 * ruin.c			Styles.    3 Mar 1993
 *
 *  Modified - Varian  March, 2016
 *
 *  Added fishing properties allowing fishing - Arman 2021
 */

#pragma strict_types

#include "wild.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/d/Genesis/start/human/wild2/base";

#define LIVE_I_CAN_FISH      "_live_i_can_fish"

public void drink_message(string from);

object ogre, compartment;
int open;

void reset_room();

/*
 * Function name:        create_wild_room()
 * Description  :        Creates a wild room from the base file
 *                       /d/Genesis/start/human/wild2/base.c
 */
void
create_wild_room()
{
    set_items_sparkle();
    set_items_field();
    set_items_driver();
    set_herbs();

    set_short("Ancient ruin");
    set_long("This appears to be the ruins of what was once a beautiful " +
        "cottage, nestled on the grassy fields of Sparkle Valley. The " +
        "west wall of the cottage is largely intact, a stout fireplace " +
        "and chimney still jutting up into the open sky, but a collapsed " +
        "roof and crumbling stone walls leave no doubt that this home " +
        "has been long deserted. A small path winds away from the cottage " +
        "to both the north and the east, while the rushing blue waters " +
        "of the Diamond River swirl past to the southwest. All across " +
        "the horizon, the rocky peaks of the Grey Mountains look down " +
        "upon the wide grassy fields of Sparkle Valley.\n");

    add_trees(1);

    add_exit(THIS_DIR + "field10","north");
    add_exit(THIS_DIR + "field9","northwest",0,1,1);
    add_exit(THIS_DIR + "field11","northeast",0,1,1);
    add_exit(THIS_DIR + "pond",   "west",0,1,1);
    add_exit(THIS_DIR + "field6", "south",0,1,1);
    add_exit(THIS_DIR + "bridge_n", "southeast",0,1,1);
    add_exit(THIS_DIR + "field7", "east");

    set_no_exit_msg(({"southwest"}),
        "The stream here is too wide to cross, you will have to find a " +
        "bridge or something.\n");

    add_item(({"wall","walls"}),
        "This cottage once had four walls, but now only the west " +
        "wall still stands.\n");
    add_item(({"water","river","diamond river","stream"}),
        "Swirling past, curving up to almost meet the edge of the " +
        "cottage, are the rushing waters of the Diamond River that " +
        "flow east across the valley towards the Pen Sea.\n");
    add_item(({"stone","stones","rock","rocks","rubble","ruin","ruins",
            "mound","mounds","pile","piles","cottage","building",
            "fieldstone","fieldstones"}),
        "Piled high in broken mounds, dozens of large fieldstones " +
        "rest as a lingering testament to what was undoubtedly a " +
        "fine cottage once upon a time.\n");
    add_item(({"foundation","foundations","stone foundation"}),
        "Aside from the west wall and piles of rubble, all that " +
        "remains of the cottage is the stone foundation.\n");
    add_item(({"west wall","western wall"}),
        "This wall is still largely intact, long after the rest of " +
        "the cottage has fallen apart. It appears to have been " +
        "reinforced by a stout fireplace with a tall chimney that " +
        "rises up high into the air.\n");
    add_item(({"fireplace","chimney"}),
        "@@fireplace");
    add_item(({"hatch" }),
        "@@hatch");
    add_item(({"ground","down"}),
        "Scattered around the ruins of the cottage, you see what appear " +
        "to be some very large footprints!\n");
    add_item(({"footprint","footprints" }),
        "These footprints appear to be rather fresh, and they look like " +
        "they belong to an ogre!\n");
    add_item(({"path","small path","dirt path","small dirt path","paths",
            "first path","second path"}),
        "There are two small dirt paths that appear to wind away from the " +
        "cottage to the north and east, both meeting up with the Dark Road " +
        "after it bends near the mountains to the northeast.\n");
    add_item(({"road","highway","dark road"}),
        "Just off in the distance to the north and east, you can see " +
        "the Dark Road that leads towards Sparkle in the south. Two small " +
        "dirt paths lead away from the cottage to meet up with the " +
        "highway\n");

    add_cmd_item( ({ "metal hatch", "hatch" }),
        "open", "@@open_hatch" );
    add_cmd_item( ({ "metal hatch", "hatch" }),
        "close", "@@close_hatch" );


    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(LIVE_I_CAN_FISH, "freshwater");
    add_prop(ROOM_S_MAP_FILE, "sparkle_wide.txt");

    compartment = clone_object("/d/Genesis/start/human/obj/compartment.c");
    compartment->set_no_show();
    compartment->move(TO);
    
    set_drink_from(({"stream", "river", "diamond river"}));

    reset_room();    
}

/*
 * Function name:        init
 * Description  :        Sets up commands for the players
 */
void
init()
{
    ::init();
    init_drink();
}
/* init */

/*
 * Function name:        drink_message
 * Description  :        Provides a description for drinking from the river
 */
public void
drink_message(string from)
{
    write("You bend down, cup your hands and drink a mouthful of water from " +
        "the river. It feels cool and refreshing going down your throat.\n");
    say(QCTNAME(TP) + " bends down to drink some water from the river.\n");
}
/* drink_message */

/*
 * Function name:        fireplace
 * Description  :        The fireplace in the chimney
 */
string
fireplace()
{
    TP->add_prop("_obj_i_hatch_found", 1);
    if (open)
	return "An open hatch in the back of the fireplace seems to\n"+
	       "reveal a hidden compartment.\n";
    return "There is a small hatch in the back of the fireplace.\n";
}
/* fireplace */

/*
 * Function name:        hatch
 * Description  :        The hatch in the fireplace
 */
string
hatch()
{
    TP->add_prop("_obj_i_hatch_found", 1);
    if (open)
	return "It is a small open metal hatch, revealing some kind of\n"+
	       "hidden compartment in the back of the fireplace.\n";
    return "It is a small metal hatch. It is closed.\n";
}
/* hatch */

/*
 * Function name:        open_hatch
 * Description  :        Allows players to open the hatch and find a gem
 */
int
open_hatch(string str)
{
    if (TP->query_prop("_obj_i_hatch_found") != 1)
    {
	   NF("What hatch?\n");
	   return 0;
    }

    if (open)
    {
	   write("It is already open.\n");
	   return 1;
    }

    write("You open the hatch.\n");
    say(QCTNAME(TP) + " walks over to the fireplace and does something.\n");
    open = 1;
    compartment->unset_no_show();
    return 1;
}
/* open_hatch */

/*
 * Function name:        close_hatch
 * Description  :        Allows players to close the hatch again
 */
int
close_hatch(string str)
{    
    if (TP->query_prop("_obj_i_hatch_found") != 1)
    {
	   NF("What hatch?\n");
	   return 0;
    }

    if (!open)
    {
        write("It is already closed.\n");
        return 1;
    }
    
    write("You close the hatch.\n");
    say(QCTNAME(TP) + " walks over to the fireplace and does something.\n");
    open = 0;
    compartment->set_no_show();
    return 1;
}
/* close_hatch */

/*
 * Function name:        get_gem
 * Description  :        Creates a gem for the hatch
 */
void
get_gem()
{
    object gem;

    if(!compartment)
        return;

    if(present("gemstone", compartment))
        return;

    gem = clone_object("/std/object");

    gem->set_name("gemstone");
    gem->add_name("gem");
    gem->add_name("jewel");
    gem->set_adj("shining");
    gem->set_long("This little jewel sparkles and shines as you look at it.\n"+
		  "It should bring you a nice price...\n");
    gem->add_prop(OBJ_I_VALUE,	96 + 12 * random(9));
    gem->add_prop(OBJ_I_WEIGHT,	3);
    gem->add_prop(OBJ_I_VOLUME,	1);

    gem->move(compartment);
}
/* get_gem */

/*
 * Function name:        reset_room
 * Description  :        Clones the NPC and loads the gem
 */
void
reset_room()
{
    int n;
    
    get_gem();

    if (ogre)
        return;

    ogre = clone_object("/d/Genesis/start/human/obj/ogre_mage");
    ogre->arm_me();
    ogre->move_living("foobar", TO);
}
/* reset_room */