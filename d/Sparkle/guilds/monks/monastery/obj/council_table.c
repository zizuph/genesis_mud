/*******************************************************************\
| COUNCIL_TABLE.C                                                   |
\*******************************************************************/

/*
 * 98/06/07 Cirion	Created
 * 01/09/18 Manat       Moved to council directory
 * 03/05/08 Arandir	Ported to new area and removed typos
 * 03/12/23 Arandir     Added synonymous name
 *
 */

#include <language.h>

#include "../defs.h"

inherit DG_OBJ_TABLE_BASE;

//-------------------------------------------------------------------

void create_container ()
{
  ::create_container ();

  set_name (({ "table", "desk" }));
  set_adj (({ "round", "hardwood", "low", "short",
              "wide", "wooden", "library", "wood" }));

  set_short ("round hardwood table");
  set_long ("The round table is made from strong black " +
            "hardwood, with a smooth-carved lip. In the " +
            "center of the table is a small depresion, " +
            "in which a blue candle burns.\n");
}

//-------------------------------------------------------------------

