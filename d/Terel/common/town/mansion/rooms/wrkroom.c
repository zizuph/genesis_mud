inherit "/std/room.c";

/*  Workroom/study/office of the Master of the house
 *
 *  Coded by Vader on 10/26/92
 *
 */

#include <macros.h>
#include <stdproperties.h>

#include "/d/Terel/common/terel_defs.h"

create_room()
{
    set_short("A workroom");
   set_long(break_string(
    "A small, musty chamber faces the west wall of this once great mansion.  " +
    "In the center of this room, atop an ancient woven rug, stands a fine " +
    "oak desk.  On the west wall is a window which provides the room with " +
    "a view of the town of Calathin.  Several paintings are aligned on the " +
    "west and east walls.  A small brass chandelier hangs from the ceiling, " +
    "at one time filled with candles, but now empty.\n", 70));

   add_item(({"desk", "oak desk", "fine oak desk"}), break_string(
    "Hand crafted from the finest trees in Calathin, it is one of the " +
    "few items in the mansion to retain its original beauty over the years.  " +
    "Several things are carved in the sides, and the surface top of the desk " +
    "is covered with a fine tanned leather, to provide a smooth writing " +   
    "surface.\n", 70));

   add_item(({"window"}), break_string(
    "This large window affords a view of the town of Calathin.  Many trees " +
    "stand in the way, but you can definitely make out part of the town " +    
    "square.\n", 70));

   add_item(({"rug", "ancient rug", "woven rug", "ancient woven rug"}), 
    break_string(
    "A marvelous red rug, with the family Coat of Arms woven towards the " + 
    "bottom half, cutting off right where the desk stands.\n", 70));

   add_item(({"paintings", "painting", "pictures", "picture"}), break_string(
    "The paintings on the walls depict various heads of family through the " +
    "years.  Each one is wearing the same armour and wields the same " +    
    "weapons.\n", 70));

   add_item(({"chandelier"}), break_string(
    "This brass chandelier hangs from the ceiling.  The candles that once " +
    "filled it have long since been 'borrowed' for other purposes.\n", 70));

   add_prop(ROOM_I_INSIDE, 1);

   add_exit(MANSION + "wing_w2", "east", 0);

}
