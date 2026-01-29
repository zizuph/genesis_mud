/*******************************************************************\
| LIBRARY_TABLE.C                                                   |
\*******************************************************************/

/*
 * 98/06/07 Cirion	Created
 * 02/02/12 Arandir	Ported to new area
 * 03/12/23 Arandir     Added synonymous name
 *
 */

#include "../defs.h"

inherit DG_OBJ_TABLE_BASE;

//-------------------------------------------------------------------

void create_container ()
{
  ::create_container ();

  set_name (({ "table", "desk" }));
  set_adj (({ "low", "short", "wide", "wooden", "library", "wood" }));

  set_short ("short wooden table");
  set_long ("This is a low wooden table, held up by four thick, " +
            "unadorned legs. The surface of the table is very " +
            "smooth. Sunlight from the window falls directly on the " +
            "table, making it suitable for reading at.\n");

  dg_set_description_prefix ("In the center of the room is a short " +
                             "and wide wooden table");
}

//-------------------------------------------------------------------

