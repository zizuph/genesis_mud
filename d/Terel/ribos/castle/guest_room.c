/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * guest_room.c
 *
 * A generic guest room in the Ribos castle.
 *
 * Vader
 * Recoded by Sorgum 950708
 *
 * Modification history:
 *    05/22/2017 (Gorboth) - enabled reset of quest variables on reset
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

int clue_found = 0;

/*
 * Function name: room_search
 * Description:   called when the player seacrhes here.
 * Arguments:     player - the player who searches
 *                str    - what they search
 * Returns:       The message the player will should see.
 */
public string
room_search(object player, string str)
{
    return("You didn't find anything of value.\n");
}

/* 
 * Function name: create_room
 * Description:   Default constructor
 *
 */
public void
create_room()
{
    ::create_room();
    set_short("Guests quarters");
    set_long("You have entered a large, luxurious room.  This is " +
	     "where the king's most treasured of guests stay.  The " +
	     "rugs are exquisite, the quilt on the bed is laced with " +
	     "gold, and the artwork upon the walls are too good for " +
	     "the finest museums.  Along one side of this room stands " +
	     "a dresser and mirror.  A night table rests " +
	     "beside the bed, and light spills in from a large " +
	     "window which overlooks some farmland near the castle.\n");

    add_item(({"bed"}), 
	     "This a a large, king sized bed that looks to be as " +
	     "soft as the clouds themselves, though you will never " +
	     "know because the likes of you will never get to sleep " +
	     "on it.  It is covered by soft clean sheets, and a " +
	     "luxurious red quilt with gold lacing.\n");

    add_item(({"window", "windows"}), 
	     "Gazing out the window, you notice several small " +
	     "donkeys pulling the plows.  The farmers behind them " +
	     "using all sorts of measures to encourage the stubborn " +
	     "beasts.  A person could get caught up looking out this " +
	     "window for hours.\n");

    add_item(({"rug", "rugs"}), 
	     "Soft to the bare foot, and exquisitely designed with many " +
	     "extremely intricate patterns.  It looks very heavy.\n");

    add_item(({"dresser", "mirror", "dresser and mirror"}),
	     "Made of solid oak, it is very heavy and should last a " +
	     "very long time.  The mirror containes an image of a " +
	     "very strange looking individual, that looks familiar, " +
	     "in a strange sort of way.\n");

    add_item(({"table", "night table"}), 
	     "Made of solid oak, it is slightly heavy, and should " +
	     "last a very long time.  There is a candle atop it.\n");
    
    clue_found = 0;

    add_prop(OBJ_I_SEARCH_TIME, 2);
    add_prop(OBJ_S_SEARCH_FUN, "room_search");
    
    INSIDE;
}

    

   
/*
 * Function name:    reset_room
 * Description  :    Update the status of the quest, if there is one
 */
public void
reset_room()
{
    clue_found = 0;
} /* reset_room */
