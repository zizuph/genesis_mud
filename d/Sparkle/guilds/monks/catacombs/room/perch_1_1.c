/*******************************************************************\
| PERCH_1_1.C                                                       |
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
    1, 1,
    "with a polished but otherwise empty top.",
    "with a polished but otherwise empty top.",
    "",
    "");
}

//-------------------------------------------------------------------

