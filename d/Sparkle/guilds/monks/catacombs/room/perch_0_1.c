/*******************************************************************\
| PERCH_0_1.C                                                       |
\*******************************************************************/

/*
 * 03/07/21 Arandir     Created
 *
 */

#include "../defs.h"

inherit CC_ROOM_PERCH_BASE;

//-------------------------------------------------------------------

void create_room ()
{
  cc_create_perch (
    0, 1,
    "with a polished but otherwise empty top.",
    "with a polished but otherwise empty top.",
    "",
    "");
}

//-------------------------------------------------------------------

