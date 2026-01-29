/* 	

    this is a room of the town Gelan

    coder(s):   Merlin

    history:     
                  2.9.10    typo                            Lavellan
                  4.7.98    last update                     ?
                  2/7/98      fixed typos                    Maniac
                 14.9.95     surgery street, square room    Maniac
                 14.2.95     lions->wolves                  Maniac
                  7.9.94     descriptions added             Maniac 
                20. 2.93    path system                     Merlin
                17. 1.93    new guard system                Merlin
                 9. 1.93    townrooms.h -> room.h           Merlin
                 6.11.92    installed help system           Merlin
                 3.11.92    created                         Merlin   

    purpose:    road for further development
    exits:      east to square

    objects:    none
    npcs:       none

    quests:     none
    special:    none

    to do:      none
    bug:        none known
*/


#include "room.h"
#pragma save_binary

inherit SQUARE_ROOM;
#include <stdproperties.h>
#include <macros.h>

void
create_room()
{
    /* descriptions */

    create_square_room();

    set_short("Surgery street");

    set_long("You are walking down Surgery street, which leads off " 
           + "the west side of the town square. "
           + "This is one of the major residential streets in Gelan, " 
           + "with well kept and picturesque houses on " 
           + "either side. On both sides of the street " 
           + "you also see a long row of grand stone wolves. " 
           + "To your east the square of Gelan opens out.\n");


	/* properties */

    add_prop(ROOM_I_INSIDE, 0);		/* this room is outside */

    /* exits */

    add_exit(GELAN_ROOMS + "square_westend","east",0);

    /* items in the room */

   add_item(({"house", "houses"}), "You see many residences on each " 
          + "side of the street. They each have their individual charm " 
          + "and style, many of them with fine gardens. " 
          + "It seems like poverty is not something very common here.\n");

   add_item(({"garden", "gardens", "flower beds", "flowers"}), 
          "Many of the houses have fine gardens with flower beds.\n");
           
   add_item(({"statue", "statues", "wolf","wolves","row"}),
             "The wolves are somewhat bigger "
          + "than you and beautifully carven. They almost look like "
          + "they're alive.\n");


} /* create_room */

/*
 * Function name: none
 * Description:   none
 * Arguments:     none
 * Returns:       none
 */
