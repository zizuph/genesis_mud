/*******************************************************************\
| LAWN_EAST_1.C                                                     |
\*******************************************************************/

/*
 * 98/12/04 Cirion	Created
 * 01/12/24 Arandir	Ported to new area
 * 02/07/27 Arandir	Modified to reflect the new surroundings
 *
 */

#include "../defs.h"

inherit M_ROOM_BASE;

//-------------------------------------------------------------------

void create_room ()
{
  set_short ("Eastern side of the monastery.");
  set_long  ("The northeast corner of the monastery is circular, " +
             "and rises up the height of the structure. The edge of the " +
             "plateau to the east is sheer, and winding between it and " +
             "the western monastery wall is a narrow, well-trodden " +
             "path through the dying grass.\n");

  add_exit ("lawn_ne", "northwest");
  add_exit ("lawn_east_2", "south");

  m_item_cliff_drop ();
  m_item_grass_crushed ();
  m_item_monastery_overhead ();
  m_item_monastery_stones ();
}

//-------------------------------------------------------------------
