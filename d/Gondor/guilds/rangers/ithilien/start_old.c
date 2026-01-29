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
public int      start(string str);
public string   read_plaque();
/*
 * public void     add_stuff();
 * static object   jar, a_rack, w_rack, crate, shelf;
 */


public void
create_gondor()
{
    object curtain;

    FIX_EUID;

    set_short("the east end of the rock chamber");
    set_long( "An uneven stooping roof makes this rock chamber look smaller "
        + "than it actually is. The cave extends westwards, and passages "
        + "lead north and southeast. A few low beds are placed in a corner, "
        + "for the use of rangers who start here. A plaque hangs next to an "
        + "iron torch stand on the south wall of the chamber. You notice "
        + "that there are some containers placed here for weapons, herbs "
        + "and armours.\n");

    /* Standard Ithilien add_items */
    ith_add_items();

    add_prop(ROOM_I_INSIDE, 1);

    add_exit((RANGERS_ITH_DIR + "rockchamber"), "west", &check_ranger());
    add_exit((RANGERS_ITH_DIR + "boardchamber"), "north", &check_ranger(1));
    add_exit((RANGERS_ITH_DIR + "foodchamber"), "southeast", &check_ranger());
    add_exit((RANGERS_ITH_DIR + "train"), "east", &check_ranger(1));
    add_prop(ROOM_I_LIGHT, 1);

#ifdef TUNNEL_OPEN
    add_exit((RANGERS_NOR_DIR + "n_drop_tun"), "northwest", 0);
#endif

    add_item(({"cave", "chamber", "rock chamber"}), &long_desc());
    add_item(({"low bunks", "bunks", "bunk", "low bunk", "bed", "beds"}),
        "The beds are simply low bunks with straw mattresses. If you wish "
        + "to 'start here', they will provide at least some comfort during "
        + "the night. Henneth Annun provides little in the way of luxury.\n");
    add_item(({"sack", "sacks", "straw mattress", "straw mattresses",
    "straw", "mattress", "mattresses"}), "The mattresses are simply rough "
        + "sacks of straw -- softer than the floor, but far from luxurious.\n");
    add_item(({"ceiling", "roof"}), "The roof is uneven, and stoops "
        + "down at several points. It seems to have been shaped only "
        + "by nature itself.\n");
    add_item(({"torch", "torch stand", "stand"}), "A torch is contained "
        + "within the iron torch stand and casts a warm light in the " 
        + "room.\n");
    add_item(({"passage", "passages"}), "The passages, dark and narrow, lead "
        + "away to the north and southeast.\n");
    add_item("containers", "These containers have been placed here to "
        + "assist in tidying the sleeping quarters. You may <sort weapons>, "
        + "<sort armours>, and <sort herbs> to put saving/non-saving "
        + "items into their appropriate containers./n"); 

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
    /*
    add_stuff();
    */
 
}


/*
 * Function   : add_stuff
 * Description: Adds a crate, armour rack, weapon rack, shelf and jar.
 *              It also handles any initialization the objects need.
 */

/*

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

*/


int
start(string str)
{
    if (!strlen(str) || lower_case(str) != "here")
    {
        notify_fail("Start here?\n");
        return 0;
    }

    if (TP->query_company() != "ithilien" && 
      !MANAGER->query_voted_in(TP->query_real_name(), "ithilien"))
    {
        notify_fail("Only Rangers of Ithilien or those Apprentices " +
            "voted into the company may sleep here!\n");
        return 0;
    }
    else if (this_player()->set_default_start_location(RANGERS_ITH_START))
    {
        write("You decide to start your day out here.\n");
        return 1;
    }
    else
    {
        notify_fail("Some problem prevents you from starting here.\n" +
            "Please make a bug report.\n");
        return 0;
    }
}


public void
init()
{
    ::init();
    add_action(start, "start");
}



public string
read_plaque()
{
    write(read_file(RANGERS_ITH_DIR + "lib/roi_plaque.txt"));
    return "";
}
