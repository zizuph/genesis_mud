/*******************************************************************\
| STAIR_TOP.C                                                       |
\*******************************************************************/

/*
 * 98/06/14 Cirion	Created
 * 02/05/01 Arandir	Ported to new area without rewrite
 * 03/03/29 Arandir     Polished up
 * 04/08/15 Arandir     Added the missing inside property
 *
 */

#include <stdproperties.h>

#include "../defs.h"

inherit M_ROOM_BASE;

//-------------------------------------------------------------------

void create_room ()
{
  set_short ("stairwell");
  set_long  ("This is the top landing of the circular " +
             "stairwell. Worn stone steps descend into darkness. " +
             "An opening to the west leads into a small central " +
             "room.\n");

  add_prop (ROOM_I_INSIDE, TRUE);

  add_exit ("hall_top", "west");
  add_exit ("stair_upper", "down");

  dg_add_entrance ("down", "You walk up the gloomy stairwell to the top landing.");

  m_item_stair_worn ();
}

//-------------------------------------------------------------------

