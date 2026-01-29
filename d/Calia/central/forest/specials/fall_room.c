// ROOM:  fall_room.c

/* Calia Domain

HISTORY

[May 5, 1998] created by Uhclem from
[C:\CALIA\CENTRAL\FOREST\SPECIALS\FALL_ROO.DOC].

PURPOSE

This room represents the space below the trees and above the ground in the
central forest. A player who falls from the trees occupies this room for about
2 seconds. All movement is controlled by FOREST_FALLING_OBJECT.

*/
// INCLUSIONS AND DEFINITIONS

inherit "/std/room";

#include <stdproperties.h>
#include "defs.h"
// FUNCTIONS
// Function:  no_can_do()

/*

Purpose:  Although a player will only spend about 2 seconds in this room,
there's a chance he'll be able to execute a command. All he'll get is a rude
retort.

Arguments:  none.

Returns: 1.

*/

int
no_can_do()
    {
    string *responses = ({
        "Sorry, no can do.",
        "Perhaps after you land.",
        "You should have thought of that sooner.",
        "That will have to wait.",
        "In your dreams!",
        "Not likely."
        });
    if (query_verb() == "down")
        {
        write ("That's hardly necessary.\n");
        }
    else
        {
        write(responses[random(sizeof(responses))] + "\n");
        }
    return 1;
    }
// Function:  init()

/*

Purpose:  add local commands. In actuality, it overrides ALL commands to
prevent the player from quitting, teleporting, or doing anyting else that might
prevent his orderly descent to the forest floor.

Arguments:  none.

Returns: nothing.

*/

void
init()
    {

    ::init();
    if (!this_player()->query_wiz_level()) add_action(no_can_do, "", 1);
    }
// ROOM DEFINITION

void
create_room()
    {
    string *part1 =
        ({
        "The air around you is still, yet it roars past because" +
        " you are not. ",
        "For a moment you seem suspended mid-way between the canopy" +
        " and forest floor, disoriented and confused about which is" +
        " which, but soon your motion makes the difference apparent. ",
        "The solid and supportive limbs of the tree just elude your" +
        " grasp, and within a heartbeat they seem as far away as" +
        " any mythical sea or mountain. "
        });
    string *part2 =
        ({
        "You plunge ever downwards, ",
        "You accelerate quite literally to breakneck speed, ",
        "You plummet downwards with ever-increasing speed, ",
        });
    string *part3 =
        ({
        "the tree trunks forming a blurry tunnel as you descend toward ",
        "the tranquil green light of the canopy giving way to ",
        "your eyes transfixed on ",
        });
    string *part4 =
        ({
        "the shadows of the forest floor.",
        "the onrushing ground below.",
        "the solid-looking ground below."
        });
    set_long("\n" +
        part1[random(sizeof(part1))] +
        part2[random(sizeof(part2))] +
        part3[random(sizeof(part3))] +
        part4[random(sizeof(part4))] + "\n" +
        "There is one inevitable exit: down.\n\n");
    set_short("Free fall");

    }
