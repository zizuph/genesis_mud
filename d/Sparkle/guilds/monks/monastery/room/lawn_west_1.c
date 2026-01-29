/*******************************************************************\
| LAWN_WEST_1.C                                                     |
\*******************************************************************/

/*
 * 98/11/26 Cirion	Created
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
  set_long  ("The soft grass underfoot makes precarious footing near " +
             "the western edge of the plateau, which drops down to " +
             "the vally below. To the east stands the western wall " +
	     "of the monastery, made from craggy blocks of rough-hewn " +
	     "stone. The wind here is buffered by the monastery " +
             "wall, making it less bitter than in the open lawn to the " +
             "north. The path here continues to the south." +
             dg_embed_livings ("lawn_nw", " Standing on the lawn to the north, you see ", ".", "") +
             "\n");

  add_exit ("lawn_nw", "north");
  add_exit ("lawn_west_2", "south");

  m_item_cliff_drop ();
  m_item_grass_long_soft ();
  m_item_monastery_overhead ();
  m_item_monastery_stones ();
}

//-------------------------------------------------------------------
