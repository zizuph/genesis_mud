/*******************************************************************\
| LAWN_WEST_2.C                                                     |
\*******************************************************************/

/*
 * 98/11/26 Cirion	Created
 * 00/12/26 Manat	Fixed typos
 * 01/12/25 Arandir	Ported to new area
 * 02/07/27 Arandir	Modified to reflect the new surroundings
 *
 */

#include "../defs.h"

inherit M_ROOM_BASE;

//-------------------------------------------------------------------

void create_room ()
{
  set_short ("Between the monastery and the western edge of the plateau");
  set_long  ("The wall to the east is low here, topped with wide slabs " +
             "of smooth shale. The grass underfoot is soft and slightly damp " +
             "with dew captured from the sheltered wind. To the southeast, " +
             "the lawn opens up into a wide area south of the monastery." +
             dg_embed_livings ("lawn_nw", " Standing on the lawn to the north, you see ", ".", "") +
             "\n");

  add_exit ("lawn_south", "southeast");
  add_exit ("lawn_west_1", "north");

  m_item_cliff_drop ();
  m_item_grass_long_soft ();
  m_item_monastery_overhead ();
  m_item_monastery_stones ();
}

//-------------------------------------------------------------------
