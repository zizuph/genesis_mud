// ROOM:  Dome - Baths and fountain
//        DOME_ROOMS + bath

    /*  Calia Domain

        HISTORY
        1998-09-06 Created by Khon.
        1999-07-11 Heavily revamped by Khon.

        PURPOSE
        The water source of the fortress has been converted
        into a marvelous fountain and bath area, luxerious
        in the extreme.

        AREA HISTORY
        Benobodrome chose this sight for its wonderful
        defensive position and fresh water. Origionally a
        well and water storage area, craftsmen slowly
        transformed it into a work of sculptured engineering
        wonder.

    */

// INCLUSIONS AND DEFINITIONS

inherit "/std/room.c";

#include "defs.h"
#include <stdproperties.h>

// ROOM DEFINITION

void
create_room()
{

    /* DESCRIPTION */

    set_short("Pleasure Dome bath and fountain");

    set_long("Sparkling white marble and glistening " +
        "sculptures set an enchanting atmosphere for " +
        "this large chamber. A large pool of steaming " +
        "water dominates the middle of the room. " +
        "Surrounding the pool are racks holding " +
        "multicolored towels and bottles.\n");

    /* ITEMS */

    add_item(({"marble", "blocks", "stone", "walls", "floor"}),
        "The walls and floor of this chamber are made of " +
        "white marble blocks. The stone is perfectly fitted " +
        "and polished smooth.\n");

    add_item(({"pool", "water", "steam"}), 
        "The waters of the pool is a deep blue in color, " +
	  "almost purple. Steam rises from its surface, " +
        "indicating the water is heated.\n");

    add_item(({"sculptures"}),
        "Highly detailed sculptures of fantastic ocean " +
        "creatures line the pool, carved from the same " +
        "marble as the walls and floor.\n");

    add_item(({"rack", "racks", "towels"}),
        "Racks arranged around the pool hold neatly folded " +
        "fluffy towels. They also hold several multicolored " +
        "bottles that catch your interest.\n");

    add_item(({"bottles"}),
        "Colored glass bottles are filled with different " +
        "oils, apparently bath oils. They give off varying " +
        "odors, each color having a different smell. There " +
        "are red, blue, green, purple, yellow and orange " +
        "bottles.\n");

     add_item(({"red bottle"}),
        "The red bottle gives off a faint strawberry smell.\n");

     add_item(({"blue bottle"}),
        "The blue bottle gives off the faint smell of blueberries.\n");

     add_item(({"green bottle"}),
        "The green bottle gives off the faint smell of spearmint.\n");

     add_item(({"purple bottle"}),
        "The purple bottle gives off the faint smell of grapes.\n");

     add_item(({"yellow bottle"}),
        "The yellow bottle gives off the faint smell of lemons.\n");

     add_item(({"orange bottle"}),
        "The orange bottle gives off the faint smell of oranges.\n");

   /* TELLS */

     set_tell_time(80);

     add_tell("You hear water dripping into the pool.\n");
     add_tell("A gentle breeze causes the mists to swirl.\n");
     add_tell("You hear the sound of water lapping against " +
         "the side of the pool.\n");

   /* EXITS */

    add_exit("hall", "south", 0, 05);

    /* PROPERTIES */

    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_HIDE, 50);

FUNCTIONS

/* Function name: bath
 * Description:   Allows people to wash in the pool.
 * Arguments:     bath, take a bath, bathe, wash, wash up,
 *                enter pool, bathe in pool, wash in pool
 * Returns:       1 if successful, 0 if fail
 */

int bath
{
       write("You step into the steaming water of the pool " +
       "and let it wash the sweat and grime from your body.\n");
       say(QCTNAME(this_player())+ " steps into the steaming " +
       "water of the pool and lets it wash the sweat and " +
       "grime from their body.\n");

       return 1;
} 

ACTIONS

public void
init()
{
 * Arguments:     bath, take a bath, bathe, wash, wash up,
 *                enter pool, bathe in pool, wash in pool
    ::init();
    add_action(bath, "take a bath");
    add_action(bath, "bathe");
    add_action(bath, "wash");
    add_action(bath, "wash up");
    add_action(bath, "enter pool");
    add_action(bath, "bathe in pool");
    add_action(bath, "wash in pool");
} 

    }
