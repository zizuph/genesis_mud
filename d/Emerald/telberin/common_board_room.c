/*
 *  /d/Emerald/telberin/common_board_room.c
 * 
 *  This is the room which houses the common board
 *  in Telberin.
 * 
 *  Copyright (c) April 2003 by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/telberin/telberin_room";

#include <stdproperties.h>


/*
 * Function name:        create_telberin_room
 * Description  :        set up the room
 */
public void
create_telberin_room()
{
    object board;

    set_short("in a common-board room in Telberin");
    set_em_long("This room is extremely small, and seems to"
      + " have no purpose other than to accomodate the"
      + " information-seeker. White wooden walls form an"
      + " octagonal perimeter beneath a pointed roof above."
      + " The floor boards part where a narrow stair leads"
      + " down to the main floor below.\n");

    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

    add_item( ({ "room", "here", "area" }), long());
    add_item( ({ "floor", "down", "board", "boards",
                 "floor board", "floor boards" }),
        "The floor boards are a light-colored hardwood, which"
      + " has been treated with a thick oil finish.\n");
    add_item( ({ "oil", "oil finish", "finish",
                 "thick oil finish" }),
        "The finish is intended to keep the footfalls from"
      + " damaging the wood beneath.\n");
    add_item( ({ "wall", "walls", "white wall", "white walls",
                 "wooden wall", "wooden walls",
                 "white wooden wall", "white wooden walls" }),
        "The walls are made of wooden boards which have been"
      + " painted white.\n");
    add_item( ({ "paint", "white", "white paint" }),
        "The paint which coveres the walls here is glossy and"
      + " bright white.\n");
    add_item( ({ "wood" }),
        "This entire room is made of wood.\n");
    add_item( ({ "perimeter", "octagonal perimeter",
                 "octagon" }),
        "The octagonal perimeter would suggest that this room"
      + " is housed within the center of the gazebo.\n");
    add_item( ({ "roof", "up", "above", "ceiling",
                 "pointed roof" }),
        "The roof above is most likely the underbelly of the"
      + " peak from outside.\n");
    add_item( ({ "stair", "stairs", "narrow stair",
                 "narrow stairs", "stairway", "step",
                 "steps" }),
        "Steps lead down between the floor boards to the main"
      + " floor below.\n");
    add_item( ({ "main floor", "below", "main floor below" }),
        "You can't see much of the main floor of the gazebo from"
      + " up here. Only a bit of it peeks from the opening at"
      + " the bottom of the stairs.\n");
    add_item( ({ "opening" }),
        "It is at the bottom of the stairs, and leads to the"
      + " main floor of the gazebo.\n");

    add_exit("/d/Emerald/telberin/gazebo", "down");

    board = clone_object("/d/Genesis/obj/board");
    board->move(this_object());
} /* create_telberin_room */

