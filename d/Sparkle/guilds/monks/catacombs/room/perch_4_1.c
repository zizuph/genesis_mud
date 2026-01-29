/*******************************************************************\
| PERCH_4_1.C                                                       |
\*******************************************************************/

/*
 * 03/07/23 Arandir     Created
 *
 */

#include "../defs.h"

inherit CC_ROOM_PERCH_BASE;

//-------------------------------------------------------------------

void create_room ()
{
  cc_create_perch (
    4, 1,
    "with a polished but otherwise empty top.",
    "with a polished but otherwise empty top.",
    "",
    "");
}

//-------------------------------------------------------------------

