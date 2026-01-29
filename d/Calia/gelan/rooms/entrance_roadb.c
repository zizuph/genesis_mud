/* 	this is a room of the town Gelan

	coder(s):	Merlin

    history:
                 6/3/2000   new connections added           Maniac
                 16.5.95    south connection changed        Maniac
                 14.2.95    lions->wolves                   Maniac
                  7.9.94    typos, timer & soul removed     Maniac
                15. 2.93    path system installed           Merlin
                 9. 1.93    townrooms.h -> room.h           Merlin
                 7. 1.93    installed dark at night test    Merlin
                 2. 1.93    slight mods                     Merlin
                28.12.92    installed cmdsoul               Merlin
                27.12.92    modified descs                  Merlin
                19.12.92    modified descriptions           Merlin
                 7.11.92    slight modifications            Merlin
                 6.11.92    installed help system           Merlin

	purpose:    connects crystalline palace to the town
	exits:      south towards the crystalline palace, north to the town

    objects:    none
    npcs:       none

    quests:     none
    special:    none

    to do:
    bug:        none known
*/

#pragma save_binary

inherit "/std/room";
#include "room.h"
#include <stdproperties.h>
#include <macros.h>
#include GUARD_INCLUDE
#define SOUTH_CONNECT "/d/Calia/mountain/road/road19"
#define SOUTHWEST_CONNECT "/d/Calia/mountain/road/road20"
#define SOUTHEAST_CONNECT "/d/Calia/argos/nwterr/rooms/r1"

/*
 * Function name: create_room
 * Description:   creates the room
 * Arguments:     none
 * Returns:       none
 */

void
create_room()
{
    /* descriptions */

	set_short("Road to Gelan");
	set_long(BS("You are standing on a well kept road heading northwards "
          + "towards the large gate of Gelan. To your south you can see "
          + "a large roundabout. On both sides of the road you see a "
          + "long row of grand stone wolves.\n"));

	/* properties */

	add_prop(ROOM_I_INSIDE, 0);		/* this room is outside */

        /* exits */

	add_exit(GELAN_ROOMS + "drawbridge","north",0);
      add_exit(SOUTH_CONNECT, "south", 0);
      add_exit(SOUTHWEST_CONNECT, "southwest"); 
      add_exit(SOUTHEAST_CONNECT, "southeast"); 

    /* items in the room */

    add_item(({"road","floor","ground","walk","street"}),BS("It's "
          + "something like a gravel walk, made with a lot of small pieces "
          + "of broken white marble. This road must be very well kept, "
          + "because there isn't the faintest trace of dirt anywhere.\n"));
    add_item(({"marble","pieces"}), BS("These are only simple pieces of "
          + "white marble. They are all about the same size.\n"));
    add_item("gate","It is huge, even from this distance. In front of "
          + "the gate you can see a drawbridge. On both sides of the gate "
          + "is a giant sandstone tower, followed by white shimmering "
          + "walls, stretching east and west as far as you can see.\n");
    add_item("palace","It's about 6 stories high and octogonal shaped. "
          + "It consists of some clear crystalline material, wonderfully "
          + "glittering and sparkling in the sunlight.\n");
    add_item(({"gelan","Gelan"}),"You sure know Gelan, don't you. If "
          + "not, you'd better have a look there.\n");
    add_item(({"wolf","wolves","row"}),"The wolves are somewhat bigger "
          + "than you and beautifully carven. They almost look like "
          + "they're alive.\n");
    add_item(({"roundabout", "large roundabout"}), "The large roundabout " +
              "to your south has much traffic going around it.\n");
    add_item(({"tower", "towers", "wall","drawbridge","walls","material"}),
             GO_CLOSER);

} /* create_room */
