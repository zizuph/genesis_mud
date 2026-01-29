/*******************************************************************\
| LAWN_EAST_2.C                                                     |
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
  set_short ("Eastern side of the monastery");
  set_long  ("Furious and unrestrained, the bitter easterly wind " +
             "buffets the craggy western wall of the high monastery. The " +
             "grassy path is very narrow here, between the wall and the " +
             "edge of the plateau, which drops off the sheer edge " +
             "to the dizzying depths below. The grass covering the " +
             "ground is well-trod and lifeless.\n");

  add_exit ("lawn_south", "southwest");
  add_exit ("lawn_east_1", "north");

  m_item_cliff_drop ();
  m_item_grass_crushed ();
  m_item_monastery_overhead ();
  m_item_monastery_stones ();
}

//-------------------------------------------------------------------
