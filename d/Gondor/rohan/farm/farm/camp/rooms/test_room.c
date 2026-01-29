/*
 * Dunlending Camp Outdoor Room
 *
 * --Raymundo, March 2020
 */

#pragma strict_types

inherit "/d/Gondor/rohan/farm/farm/camp/lib/base_room";

#include <macros.h>
#include "/d/Gondor/defs.h"
#include "defs.h"




void
create_dunlending()
{
    set_short("Northern edge of a forest in Anorien.\n");
    set_long("You're standing near the northen edge of a forest in Anorien. "
        + "The forest continues to the north, but the underbrush is too "
        + "overgrown for you to walk any further. To the south the forest "
        + "opens up and you can even see between the trees for a surprising "
        + "distance. Pine needles cover the ground like carpet, preventing "
        + "you from even seeing any dirt. Here and there some herbs poke "
        + "through the pine needles.\n");


    add_item( ({"underbrush", "brush"}), "The brush looks a lot like poison "
        + "oak! It's very thick and overgrown here, so you think it'd be "
        + "best not to walk through it.\n");
    add_item( ({"floor", "forest", "forest floor"}), "The forest floor is "
        + "covered in pine needles.\n");

    set_no_exit_msg( ({"north", "northwest", "northeast", "east", "west"}),
        "Thick underbrush prevents you from walking that direction.\n");

    add_forest();
    forest_herbs_1();
    if(!random(3))
    {
    forest_climb("test_room_up");
    }
    add_guard_down();

}

void
remove_guards()
{
    object guard, scout, captain, *players;
    if (sizeof( players = FILTER_PLAYERS( all_inventory(TO) ) ))
    {
        return;
    }
    if (objectp(guard = present("guard", this_object())))
    {
        guard->remove_object();
    }
    if (objectp(scout = present("scout", this_object())))
    {
        scout->remove_object();
    }
    if (objectp(captain = present("captain", this_object())))
    {
        captain->remove_object();
    }
    
    return;
} 
void
reset_room()
{
    set_searched(0);
    remove_guards();
    set_alarm(1.0, 0.0, add_guard_down);
}

