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
 * 9 November 2015, Varian: Separated the start room from the rack room
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


public void
create_gondor()
{
    FIX_EUID;

    set_short("Sleeping chamber");
    set_long( "This is a wide chamber which has been carefully carved " +
        "inside the hidden rocky depths of Henneth Annun, lit only by the " +
        "handful of torches mounted on the walls, scattering dozens of " +
        "flickering shadows across the entire length of the cave. Dozens of " +
        "serviceable bunks huddle in the comfortable shadows which are " +
        "broken only by two large openings in the walls of this room. " +
        "There is one in the north and another in the south, both "+
        "leading off into other rooms within these caves. The floor of " +
        "this cavern has been worn rather smooth from what appears to " +
        "be years of heavy use. In sharp contrast, the walls and ceiling " +
        "are still rather rough and jagged having largely been left in " +
        "their natural state save where human hand was needed to make the " +
        "chamber servicable. You get the feeling that if you were so " +
        "inclined, this would be the perfect spot to set up your own " +
        "bed for sleeping in.\n");

    /* Standard Ithilien add_items */
    ith_add_items();

    add_prop(ROOM_I_INSIDE, 1);

    add_exit((RANGERS_ITH_DIR + "rackchamber"), "south", &check_ranger());
    add_exit((RANGERS_ITH_DIR + "boardchamber"), "north", &check_ranger(1));
    add_prop(ROOM_I_LIGHT, 1);

    add_item(({"cave", "chamber", "rock chamber", "cavern", "here"}), &long_desc());
    add_item(({"low bunks", "bunks", "bunk", "low bunk", "bed", "beds", "box", "boxes"}),
        "Dozens of low bunks serve as beds for the Rangers who serve in " +
        "Ithilien. The beds are not much more than wooden boxes filled " +
        "with large sacks of straw which serve as mattresses. \n\n " +
        "If you would like to stay with the other Rangers of Ithilien and " +
        "set up your own bunk here, simply type 'start here'.\n");
    add_item(({"sack", "sacks", "straw mattress", "straw mattresses",
    "straw", "mattress", "mattresses"}), 
        "The mattresses for the bunks are " +
        "nothing more than large sacks filled with straw. They are perhaps " +
        "not the most luxurious choice, but it is still a better option " +
        "than sleeping on the cold stone of the floor.\n");
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
        "Two large openings grace this chamber, one giving passage to the " +
        "north and another on the opposite wall leading south.\n");
    add_item(({"wall", "walls"}), 
        "The walls of this sleeping chamber seem like they would be " +
        "quite rough and jagged to the touch, as " +
        "the stone has been left in a more or less natural state. A few " +
        "iron stands have been mounted on the walls, each bearing the " +
        "spluttering fire of a small wooden torch, helping to provide just " +
        "enough light to see by. An opening in the north wall and another " +
        "in the south wall lead along passages to other parts of this " +
        "hideout.\n");
    add_item(({"south wall", "southern wall"}), 
        "The southern wall has a large opening which appears to lead into " +
        "a frequently visited chamber where racks for armours and weapons " +
        "have been set up to arm the Rangers who serve here in Ithilien.\n");
    add_item(({"north wall", "northern wall"}), 
        "The northern wall has a large opening which appears to lead into " +
        "a quiet chamber where a large bulletin board has been set up for " +
        "the exclusive use of the Rangers who live here.\n");
    add_item(({"west wall", "western wall"}), 
        "The western wall of the chamber is covered in shadows, as many " +
        "of the bunks have been set up in the darkness here.\n");
    add_item(({"east wall", "eastern wall"}), 
        "The eastern wall of the chamber is covered in shadows, as many " +
        "of the bunks have been set up in the darkness here.\n");
    add_item(({"shadow", "shadows"}), 
        "Many dark shadows dance along the walls of this chamber, hiding " +
        "from the flickering light of the torches as they crouch behind " +
        "jagged outcroppings of rock on the walls and ceiling. Placed within " +
        "the depths of these shadows are the huddled bunks of many Rangers " +
        "who are attempting to enjoy a quiet rest.\n");
    add_item(({"floor", "ground"}), 
        "The floor of this chamber has been carved out of the same stone " +
        "as the walls and ceiling, but made flat and worn smooth by years "+
        "of traffic as the Rangers who serve in Ithilien have made their " +
        "home here.\n");
    add_item(({"stone", "rock", "crag", "crags", "outcropping", "outcroppings"}), 
        "This entire chamber has been carved from the rough grey stone " +
        "of the land itself. Several craggy outcroppings follow the walls " +
        "and ceiling, casting shadows across the cave.\n");

    add_cmd_item(({"wall", "walls", "stone", "grey stone"}),
        ({"touch", "feel"}), "The stone is cool and rather rough and jagged to "
        + "the touch.\n");
 
}


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

