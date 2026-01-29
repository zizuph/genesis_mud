/*******************************************************************\
| LAWN_NW.C                                                         |
\*******************************************************************/

/*
 * 98/11/26 Cirion	Created
 * 01/12/25 Arandir	Ported to new area
 * 02/07/27 Arandir	Modified to reflect the new surroundings
 *
 */

#include "../defs.h"

inherit M_ROOM_BASE;

inherit DG_OBJ_LIBS;

//-------------------------------------------------------------------

void create_room ()
{
  set_short ("Northwest lawn");
  set_long  ("Furious gusts of cold, hard wind blow up over the " +
             "sheer edge of the plateau to the north and west. The " +
             "grass underfoot is neat and well-tended. To the southeast, " +
             "the massive stone monastery rises up from the earth, " +
             "an ancient edifice made from craggy stone. The wide lawn continues " +
             "to the east, and to the south it narrows between the high " +
             "stone wall and the edge of the cliff to the west." +
             dg_embed_livings ("lawn_ne", " Standing on the lawn to the east, you see ", ".", "") +
             "\n");

  add_exit ("lawn_ne", "east");
  add_exit ("lawn_west_1", "south");

  m_item_cliff_drop ();
  m_item_grass_manicured ();
  m_item_monastery_overhead ();
  m_item_monastery_stones ();
}

//-------------------------------------------------------------------
