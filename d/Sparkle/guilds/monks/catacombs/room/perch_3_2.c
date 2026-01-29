/*******************************************************************\
| PERCH_3_2.C                                                       |
\*******************************************************************/

/*
 * 07/05/26 Arandir     Fixed the dragon name
 * 03/07/23 Arandir     Created
 *
 */

#include "../defs.h"

inherit CC_ROOM_PERCH_BASE;

//-------------------------------------------------------------------

void create_room ()
{
  cc_create_perch (
    3, 2,
    "carrying a relief of a damp and dank cave, once closed with " +
    "what are now only broken remains of an iron door.",
    "carrying a relief of a cave with broken door, occupied by a " +
    "shimmering shape of a huge and evil dragon with sharp claws.",
    "ribos evil dragon",
    "The shimmering shape of the huge dragon looks dangerous, with " +
    "razor sharp claws and teeth. Its scaly skin is so tough that " +
    "no ordinary sword can penetrate it.");
}

//-------------------------------------------------------------------

