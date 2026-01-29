/*******************************************************************\
| DINING_TABLE.C                                                    |
\*******************************************************************/

/*
 * 98/05/29 Cirion	Created
 * 98/06/07 Cirion      Modularized
 * 00/12/26 Manat       Fixed number of chairs
 * 03/05/08 Arandir	Ported to new area
 * 03/12/23 Arandir     Added synonymous name
 *
 */

#include <language.h>

#include "../defs.h"

inherit DG_OBJ_TABLE_BASE;

//-------------------------------------------------------------------

string m_long ()
{
  object oRoom = environment ();

  return ("This massive table is made from dark redwood. It " +
          "extends the entire length of the dining hall, and " +
          "arranged neatly around the table are " +
          LANG_WNUM (sizeof (oRoom->m_get_chairs ())) + " " +
          "sturdy wooden chairs. The surface of the table is scarred " +
          "and stained from countless meals and celebrations over the " +
          "years.\n");
}

//-------------------------------------------------------------------

void create_container ()
{
  ::create_container ();

  set_name (({ "table", "desk" }));
  set_adj (({ "heavy", "redwood", "red", "massive", "wood" }));

  set_short ("massive redwood table");
  set_long (&m_long ());

  dg_set_description_prefix ("Dominating the room is a massive " +
                             "redwood dining table");
}

//-------------------------------------------------------------------

