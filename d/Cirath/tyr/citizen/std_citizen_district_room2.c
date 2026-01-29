/*
 *  /d/Cirath/tyr/citizen/std_citizen_district_room2.c
 *
 *  Standard room for the Citizens District in which to keep all standard code.
 *
 *  This is the indoors version.
 *
 *  Created by Ardent, 10/01/2005
 *
 *  Modified by Ardent, 26/04/2006
 */

inherit "/std/room";

#include "defs.h"
#include <stdproperties.h>

create_citizen_room()
{
}

// Creating the room.
create_room()
{
   set_short("Standard short room description in Citizens District");
   set_long("Standard long room description in Citizens District.\n");

// Standard items that will be found in all houses. When time permits I will
// change the descriptions in some of the houses to make them all a bit
// different.

    add_item(({"stove"}),
       "This is a stove used to cook food on.\n");

    add_item(({"ziggurat"}),
       "The presence of the Ziggurat can be felt even inside this house.\n");

    add_item(({"sun", "dark sun"}),
       "A slight shade from the sun can be found behind the walls of this "   +
       "house, but rays of light filters in through the roof so no place is " +
       "completely hidden from the Dark Sun.\n");

    add_item(({"shelf"}),
    	 "Nothing of interest catches can be seen on this shelf.\n");

    add_item(({"table"}),
       "A few chairs have been placed around this table.\n");

    add_item(({"cabinet"}),
       "You rummage through the cabinet but find nothing special.\n");

    add_item(({"window", "windows"}),
       "The strong light of the Athasian Dark Sun shines brightly in through "+
       "these windows. These lands are so poor that not even the middle-class"+
       " citizens can afford to put glass panes in their windows. Small "     +
       "curtains are placed next to the windows, used to cover the windows "  +
       "and keep out the cold at night.\n");

    add_item(({"chair", "chairs"}),
       "Several chairs have been placed around the table. They are all made " +
       "of bone and seem rather plain.\n");

    add_item(({"doorway"}),
       "Calling this a doorway seems like a bit of an overstatement since the"+
       " shortage of wood means that only the rich actually have doors. This "+
       "doorway, like most others in Tyr, is covered by a curtain of animal " +
       "hide that has neither been cured nor tanned to retain its "           +
       "inflexibility.\n");

    add_item(({"roof"}),
       "The main structure of the roof is based on long animal bones being "  +
       "placed across from wall to wall. Smaller bone frames with animal "    +
       "hides stretched out across have then been tied to main bone "         +
       "structure. This leaves a lot of holes and cracks through which the "  +
       "powerful Athasian Dark Sun shines. No attempt has been made to "      +
       "shield this home from rain, as rain is such a very rare occasion that"+
       " no one bothers thinking about it. \n");

    add_item(({"bed"}),
       "This bed is made from a square bone structure with several animal "   +
       "skins stretched out and tied to the frame with animal sinews. Not a " +
       "pretty bed, but surprisingly comfortable when you try it.\n");



// Bright rooms due the very bright Athasian Dark Sun. Even indoors.
   add_prop(ROOM_I_LIGHT, 1);
// It is almost impossible to hide due to the bleakness in which nothing
// can be camouflaged, and because of the strong light. Also, Kalak hates
// sneakers and has placed a divination enchantment on the lands that makes
// it impossible to hide anything from his scrying eyes.
// His ban on magic is also in part due to the fact that he fears that
// someone will dispel his enchantments.
   add_prop(ROOM_I_HIDE, -1);

   add_prop(ROOM_I_INSIDE, 1);

   reset_room();

   create_citizen_room();
}


