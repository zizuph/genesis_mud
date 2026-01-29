/*
 * Startroom for the Elemental Seekers in the Elemental Temple of Calia
 * 
 * Created by Petros, April 2010
 */

#pragma strict_types

#include "defs.h"
#include <macros.h>

inherit TEMPLE_ROOM_BASE;

// Defines

// Prototypes
public string
describe_long()
{
    string rest_message = "";
    if (IS_MEMBER(this_player()) || IS_SEEKER(this_player()))
    {
        rest_message = ", and you feel as if you could <rest here> in any "
            + "of them. ";
    }
    else
    {
        rest_message = ". ";
    }

    return "This is the sleeping quarters for all who are seeking to be "
        + "guided by the Elementals. You notice rows of beds along the northern and "
        + "southern walls. Each bed is separated by its own small "
        + "nightstand coupled with its own lantern. None of the beds are "
        + "marked" + rest_message
        + "Light dances over you, bringing your attention to the "
        + "domed crystalline ceiling. You are able to make out the sky "
        + "above. To the south, you see the doorway that leads into the "
        + "Outer Circle of the Temple.\n\n";
}

public void
create_temple_room()
{
    set_short("Bunkroom for the Elemental Seekers");
    set_long("@@describe_long@@");

    try_item( ({ "beds", "bed", "rows of beds", "rows", "row of beds",
                 "row", "northern wall", "southern wall",
                 "wood", "petrified wood" }),
          "The beds are organized into rows along the walls. They are are "
        + "made up of dark petrified wood, the same wood which is used "
        + "throughout the rest of the Temple. The wood retains all "
        + "the original structure and detail of the wood and looks to be "
        + "extremely sturdy. Each bed has a mattress, a pillow, and a single "
        + "blanket.\n");
    
    try_item( ({ "mattress", "mattresses", "blanket", "blankets", "pillow",
                 "feathers", "feather", "osprey feathers" }),
          "Each bed has a single mattress and a finely woven wool blanket "
        + "made from the finest wool of Argos. The mattress and the "
        + "accompanying pillow seem to be filled with osprey feathers. It "
        + "looks quite comfy!\n");
    
    try_item( ({ "nightstand", "nightstands" }),
          "Between each bed rests a nightstand. While simple in design, the "
        + "nightstands all seem to be extremely well made. Like the beds, they "
        + "are made from dark petrified wood. The surface of the material "
        + "is smooth to the touch. A tiny marble knob is centered on the "
        + "drawers of the nightstands, allowing one to place their personal "
        + "items within.\n");
    
    try_item( ({ "lantern", "brass lantern", "small lantern", "small brass lantern" }),
          "Small brass lanterns sit on top of each nightstand and can be lit "
        + "or extinguished as necessary. Four colums rise on each corner, and "
        + "a thin piece of glass has been placed between each corner with a "
        + "wax candle in the middle. They are quite simple in design and look "
        + "brand new. \n");
      
    add_exit(ELEMENTALIST_TEMPLE + "middle11", "west");    
    add_exit(ELEMENTALIST_TEMPLE + "outer14a", "south");
}

/*
 * Function:    init
 * Description: Init function to add the actions available in this room.
 */
public void
init()
{
    ::init();
    add_action("do_rest", "rest");
    add_action("do_rest", "start");
}

/*
 * Function:    do_rest
 * Description: The function that allows a person to set this starting
 *              location as their default starting location. Ideally, this
 *              command should only allow those who actually follow the
 *              particular Elemental to rest here.
 */
public int
do_rest(string arg)
{
    if (!IS_MEMBER(this_player()))
    {
        return 0;
    }

    if (!strlen(arg)
        || lower_case(arg) != "here")
    {
        notify_fail("Do you wish to <rest here>?\n");
        return 0;
    }
    
    this_player()->set_default_start_location(MASTER);
    write("Ok.\n");
    return 1;
}
