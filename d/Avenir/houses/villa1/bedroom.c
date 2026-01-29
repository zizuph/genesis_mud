/*
 * villa1/bedroom.c
 *
 * Lilith, Feb 2021
 *
 */

#pragma strict_types

#include "villa1.h"
#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>

inherit V1 +"housebase";
inherit "/lib/commands";
inherit "/d/Avenir/inherit/emotes";

int do_terrace();
int do_sleep(string str);

/*
 * Function name:        create_house_room()
 * Description  :        Creates a house room from from the base file
 *                       "housebase.c"
 */
void 
create_house_room()
{
    room_add_object(HOBJ + "wardrobe_v1");
    room_add_object(HOBJ + "bed_v1");

    add_exit("garden", "north", do_terrace);
    add_exit("front_hall", "west");
 //   add_exit("bath", "east");

    set_short("luxurious bedroom");
    set_long("This is the large, elegantly simple bedroom of the villa. "+
      "Fur pelts have been scattered on the floor alongside the big, "+
      "luxurious bed which dominates the space. It has been placed " +
      "against a north-facing privacy wall made from a slab of " +
      "red carnelian. Behind the privacy wall is a hallway with " +
      "a floor-to-ceiling wardrobe where the owner may put things "+
      "for safekeeping. " +
      "To the north, a beautiful potted plant graces a large window "+
      "overlooking a terrace garden and nearby pool. "+
      "West is a doorway leading back to the front hall.\n");

    set_items_bedroom();
    set_items_stone();

    add_help_topic("here",  "/d/Avenir/houses/help/bed_help");
    add_help_topic("room",  "/d/Avenir/houses/help/bed_help");

    add_item(({"fur", "furs", "pelts", "pelt", "fur pelts"}),
      "Scattered on the floor along side the bed are numerous "+
      "fur pelts that must feel marvellous under bare feet.\n");
    add_item(({"south wall", "southern wall"}),
      "There are two walls to the south. One of them is a "+
      "privacy wall and the other is an exterior wall with "+
      "a large wardrobe.\n");
    add_item(({"privacy wall", "short wall", "carnelian wall",
	"red carnelian wall", "carvings", "trefoils knots",
	"wisteria leaves", "red wall" }),
      "This privacy wall is slab of semi-translucent red "+
      "carnelian about two meters high. It has been carved "+
      "with trefoil knots and wisteria leaves.\n");
    add_item(({"exterior wall", "south exterior wall"}),
      "This is the exterior wall of the villa. A large "+
      "wardrobe has been placed against it.\n");
    add_item( ({"east wall", "eastern wall"}),
      "The eastern wall here is made from slabs of white onyx " +
      "that are striped with milky opaque and translucent bands " +
      "that glow when light shines through.\n");
    add_item( ({"north wall", "northern wall"}),
      "The northern wall is mostly glass. It has a giant window "+
      "overlooking a garden area and a nearby pool.\n");
    add_item( ({ "window", "north window"}), 
      "@@exa_window|You look through the window.\n|" + V1 +"garden@@");
    add_item(({"garden", "garden area", "pool", "terrace"}),
      "Why don't you go out on the terrace and have a good look?\n");
    add_item( ({"west wall", "western wall"}),
      "The western wall here is made from slabs of white onyx " +
      "that are striped with milky opaque and translucent bands " +
      "that glow when light shines through.\n");

}


/*
 * Function name: init
 * Description  : initialize couch & time
 */

public void
init()
{   
    ::init();
    add_action("do_sleep","sleep");
    add_action("do_sleep","nap");
    add_action("do_start","start");
}

/*
 * Function name: exa_window
 * Description  : This lets people see the adjacent outside room.
 */

public string
exa_window(string desc, string room_file)
{
    object room = find_object(room_file),
    *in_room_p, *in_room_o;

    in_room_p = FILTER_CAN_SEE(
      FILTER_SHOWN_COMPOSITE(FILTER_LIVE(all_inventory(room))),
      this_player());
    in_room_o = FILTER_CAN_SEE(
      FILTER_SHOWN_COMPOSITE(FILTER_DEAD(all_inventory(room))),
      this_player());

    write((room_file)->long());

    if (sizeof(in_room_p))
	this_player()->catch_msg(capitalize(COMPOSITE_LIVE(in_room_p)) + 
	  ".\n");

    if (sizeof(in_room_o))   
	this_player()->catch_msg(capitalize(COMPOSITE_DEAD(in_room_o))+ 
	  ".\n");

    tell_room(ENV(TP), QCTNAME(TP) + " gazes through the window.\n", TP);

    return "";
} 

/*
 * Function name:        do_sleep
 * Description  :        Provides an emote to sleep in the bed
 * Returns      :        int 0 - Prompt for proper syntax
 *                       int 1 - Returns the emote
 */
int
do_sleep(string str)
{
    if(!str)
    {
	notify_fail("What are you trying to sleep on? The bed?\n");
	return 0;
    }

    if (!parse_command(str, ({}),
	"[on] / [in] [the] [big] [luxurious] 'bed'", str))
    { 
	write("What are you trying to sleep on? The bed?\n");
	return 1;
    }
    write("You climb into the big, luxurious bed and discover " +
      "that it is even more comfortable than it looks! " +
      "Closing your eyes, you enjoy a nice little nap.\n");
    say(" takes a short nap on the wide luxurious bed.\n");
    return 1;
}

/*
 *  do_terrace - fake door to the outside
 */
int
do_terrace()
{
    write("You open the door and step out onto the terrace.\n");
    return 0;
}


public int
query_prevent_snoop(void)       { return 1; }
