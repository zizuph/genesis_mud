/*
 *  /d/Gondor/guilds/rangers/ithilien/start.c
 *
 * Created by Elessar.
 *
 * Modification history:
 * 26 August 1998, Gnadnar: make real curtain (door) so can
 *  block access to training recess if officers are using it 
 *  for privacy, add some items, tidy up.
 *
 * 13 October 1998, Gnadnar: determine curtain status every time
 *  long is called, rather than storing it and only updating
 *  when it changes. less efficient, but the stored strings
 *  were sometimes getting out of sync. :-(
 *
 * 20 July 2001, Alto: revise inheritance and make minor changes
 * to fit new rangers theme.
 *
 * 24 March 2002, Gwyneth: added a function call to the weapon rack
 *      to aid in managing the listings.
 *
 * 12 August 2002, Alto: limited exits for non-RoI.
 * 29 Oct. 2003, Tigerlily: commented out janitor
 * 29 October 2003, Gwyneth: Commented out the wind tunnel with defines.
 *                           Neatened up.
 * 24 March 2004, Tigerlily: Removed torch object and curtain to recess
 *                    added note on syntax for sorting weapons, etc.
 * 22 April 2005, ?: last update?
 * 30 October 2010, Lavellan: Changed for new saving rack system
 *
 */
inherit "/d/Gondor/std/room.c";

#include "../rangers.h"

inherit RANGERS_ITH_DIR + "ith_funcs.c";

#include <composite.h>
#include <filter_funs.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "exit.c"


public void     create_gondor();
public string   read_plaque();
public void     add_stuff();
static object   jar, a_rack, w_rack, crate, shelf;


public void
create_gondor()
{
    object curtain;

    FIX_EUID;

    set_short("the east end of the rock chamber");
    set_long( "You are standing at the eastern edge of a large cave which " +
        "begins to narrow slightly as it moves west. The rough contours of " +
        "the stone walls and the low slope of the rocky ceiling above " +
        "suggest that most of this cavern is natural, save perhaps for " +
        "the floor which is smoothly flat. Several flickering toches have " +
        "been mounted in iron brackets, gently illuminating a plaque which " +
        "hangs on the southern wall. In the middle of this chamber, " +
        "several racks have been placed for the purpose of storing " +
        "equipment for the brave warriors who live here. Openings in the " +
        "walls to the north, east and southeast appear to tunnel into some " +
        "smaller chambers within these caves. \n");

    /* Standard Ithilien add_items */
    ith_add_items();

    add_prop(ROOM_I_INSIDE, 1);

    add_exit((RANGERS_ITH_DIR + "rockchamber"), "west", &check_ranger());
    add_exit((RANGERS_ITH_DIR + "start"), "north", &check_ranger(1));
    add_exit((RANGERS_ITH_DIR + "foodchamber"), "southeast", &check_ranger());
    add_exit((RANGERS_ITH_DIR + "train"), "east", &check_ranger(1));
    add_prop(ROOM_I_LIGHT, 1);

#ifdef TUNNEL_OPEN
    add_exit((RANGERS_NOR_DIR + "n_drop_tun"), "northwest", 0);
#endif

    add_item(({"cave", "chamber", "rock chamber", "cavern", "here"}), &long_desc());
    add_item(({"passage", "passages"}), "The passages, dark and narrow, lead "
        + "away to the north and southeast.\n");
    add_item("containers", "These containers have been placed here to "
        + "assist in tidying this cave. You may <sort weapons>, "
        + "<sort armours>, and <sort herbs> to put saving/non-saving "
        + "items into their appropriate containers./n");
    add_item(({"ceiling", "roof", "up"}), 
        "The craggy ceiling above you appears " +
        "to be in constant movement as flickering shadows from the torches " +
        "dance and play across the rough surface.\n");
    add_item(({"torch", "torch stand", "stand", "torches", "stands", "torch stands"}), 
        "A small handful of torches have been set inside iron stands which " +
        "have been mounted at regular intervals around the perimeter of " +
        "the chamber. Flickering brightly, the light from the torches " +
        "dances along the rough surface of the walls and ceiling in an " +
        "erratic fashion.\n");
    add_item(({"passage", "passages", "opening", "openings"}), 
        "Three passages tunnel through the walls here, to the north, east " +
        "and southeast.\n");
    add_item(({"wall", "walls"}), 
        "The walls of this sleeping chamber seem like they would be " +
        "quite rough and jagged to the touch, as " +
        "the stone has been left in a more or less natural state. A few " +
        "iron stands have been mounted on the walls, each bearing the " +
        "spluttering fire of a small wooden torch, helping to provide just " +
        "enough light to see by. Openings to the north, east and southeast " +
        "lead into smaller chambers while this cavern extends to the west.\n");
    add_item(({"shadow", "shadows"}), 
        "Many dark shadows dance along the walls of this chamber, hiding " +
        "from the flickering light of the torches as they crouch behind " +
        "jagged outcroppings of rock on the walls and ceiling.\n");
    add_item(({"floor", "ground"}), 
        "The floor of this chamber has been carved out of the same stone " +
        "as the walls and ceiling, but made flat and worn smooth by years "+
        "of traffic as the Rangers who serve in Ithilien have made their " +
        "home here.\n");
    add_item(({"stone", "rock", "crag", "crags", "outcropping", "outcroppings"}), 
        "This entire chamber has been carved from the rough grey stone " +
        "of the land itself. Several craggy outcroppings follow the walls " +
        "and ceiling, casting shadows across the cave.\n");

    add_item(({"plaque"}), &read_plaque());

#ifdef TUNNEL_OPEN
    add_item(({"tunnel", "strange tunnel"}), "The tunnel is very dark. "
        + "It is difficult to determine what awaits inside.\n");
#endif
    add_cmd_item(({"plaque"}), "read", &read_plaque());
    add_cmd_item(({"floor", "wall", "walls", "stone", "grey stone"}),
        ({"touch", "feel"}), "The stone is cool and slightly rough to "
        + "the touch.\n");
    /* Add crate, racks, jar and shelf */
    add_stuff();
 
}


/*
 * Function   : add_stuff
 * Description: Adds a crate, armour rack, weapon rack, shelf and jar.
 *              It also handles any initialization the objects need.
 */
void
add_stuff()
{
    if (!objectp(crate))
    {
//        crate = clone_object(RANGERS_OBJ + "crate");
        crate = clone_object(RANGERS_OBJ + "racks/ith_crate");
        crate->move(TO);
    }

    if (!objectp(a_rack))
    {
//        a_rack = clone_object(RANGERS_OBJ + "a_rack");
        a_rack = clone_object(RANGERS_OBJ + "racks/ith_a_rack");
        a_rack->move(TO);
    }

    if (!objectp(w_rack))
    {
//        w_rack = clone_object(RANGERS_OBJ + "w_rack");
        w_rack = clone_object(RANGERS_OBJ + "racks/ith_w_rack");
        w_rack->set_save_file(RANGERS_OBJ + "ith_list");
        w_rack->remove_non_glowing();
        w_rack->move(TO);
    }

    if (!objectp(shelf))
    {
//        shelf = clone_object(RANGERS_OBJ + "shelf");
        shelf = clone_object(RANGERS_OBJ + "racks/ith_shelf");
        shelf->move(TO);
    }

    if (!objectp(jar))
    {
    // using old herbjar so as not to confuse sort and
    // hsort commands
//        jar = clone_object(RANGERS_OBJ + "herbjar2");
        jar = clone_object(RANGERS_OBJ + "racks/ith_herbjar");
        jar->add_prop(OBJ_M_NO_GET, "The jar seems to have been glued "
            + "to the floor!\n");
        jar->move(TO);
    }
}

public string
read_plaque()
{
    write(read_file(RANGERS_ITH_DIR + "lib/roi_plaque.txt"));
    return "";
}
