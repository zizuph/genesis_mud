/*******************************************************************\
| STAIR_UPPER.C                                                     |
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
  set_short ("stairwell landing");
  set_long  ("Stone steps worn with the passage of many " +
             "feet over the years leads upwards and downwards. " +
             "This square landing opens to the west into " +
             "a large hallway from which a cool breeze " +
             "flows.\n");

  add_prop (ROOM_I_INSIDE, TRUE);

  add_exit("hall_upper_north", "west");
  add_exit("stair_lower", "down");
  add_exit("stair_top", "up");

  dg_add_entrance ("up", "You descend the stairwell to the second story landing.");
  dg_add_entrance ("down", "You walk up the circular stairwell and arrive at the second story landing.");
  dg_add_entrance ("west", "You walk through the opening into the cool confines of the stairwell landing.");

  m_item_stair_worn ();
}

//-------------------------------------------------------------------

