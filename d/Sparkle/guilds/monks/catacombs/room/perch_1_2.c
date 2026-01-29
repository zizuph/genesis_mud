/*******************************************************************\
| PERCH_1_2.C                                                       |
\*******************************************************************/

/*
 * 03/07/22 Arandir     Created
 *
 */

#include "../defs.h"

inherit CC_ROOM_PERCH_BASE;

//-------------------------------------------------------------------

void create_room ()
{
  cc_create_perch (
    1, 2,
    "carrying a relief of an underground maze of tunnels, with " +
    "walls covered in fungi and the ground slick with fetid " +
    "water and moss.",
    "carrying a relief of a tunnel maze, dominated by a shimmering " +
    "shape of a massive cave drake.",
    "avenir cave drake",
    "The shimmering shape of the cave drake suggests speed and " +
    "intelligence. Catching your attention are its massive " +
    "jaws, doubtless used to catch and quickly devour " +
    "any prey within reach.");
}

//-------------------------------------------------------------------

