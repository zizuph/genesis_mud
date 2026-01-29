/*
 *  /d/Genesis/room/item_mod_generator.c
 *
 *  So that Genesis can add a bit of interest to the exp grind beyond
 *  mere exp growth, the item mod generator is designed to apply random
 *  magic modifications to any weapon in the game that can beat a dice
 *  roll (1/100) in the spirit of Diablo II.
 *
 *  All weapons and armours get a dice roll when they are cloned, provided
 *  that the first environment they enter is that of an npc.
 *
 *  All modded weapons are added to a datafile and kept track of by this
 *  object, which is also a control room.
 *
 *  Created October 2009, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/room";


/* Prototypes */
public void        create_room();


/*
 * Function name:        create_room
 * Description  :        the constructor for the room object
 */
public void
create_room()
{
    set_short("the Item Mod Generator Control Room");
    set_long(short() + "\n");
} /* create_room */


