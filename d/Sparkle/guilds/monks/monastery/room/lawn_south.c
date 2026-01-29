/*******************************************************************\
| LAWN_SOUTH.C                                                      |
\*******************************************************************/

/*
 * 98/12/04 Cirion	Created
 * 01/12/24 Arandir	Ported to new area
 * 02/07/27 Arandir	Modified to reflect the new surroundings
 *
 */

#include "../defs.h"

inherit M_ROOM_BASE;

inherit DG_OBJ_LIBS;

//-------------------------------------------------------------------

#define NUM_GOATS 	(4 + random (4))

private object *aoGoats = ({ });

void reset_room ();

//-------------------------------------------------------------------

void create_room ()
{
  set_short ("South lawn");
  set_long  ("Spreading away to the south past the edge of the plateau is " +
             "a vertiginous panorama of the valley below. The cold wind is " +
             "little but a breeze here, blocked by the low stone wall of " +
             "the monastery to the north. The grass is thick and high " +
             "here, untended and breathing with verdant life.\n");

  add_exit ("lawn_west_2", "northwest");
  add_exit ("lawn_east_2", "northeast");
  
  m_item_cliff_drop ();
  m_item_grass_high_untended ();
  m_item_monastery_overhead ();
  m_item_monastery_stones ();

  reset_room ();
}

void reset_room()
{
  object oGoat;

  // This will remove references to goats that somebody has
  // killed from our array of goats this room spawned.

  aoGoats -= ({ 0 });

  // Now just regenerate enough goats to keep the numbers.

  while (sizeof (aoGoats) < NUM_GOATS)
  {
    aoGoats += ({ dg_clone_here (M_PATH_NPC + "/goat") });
  };
}

//-------------------------------------------------------------------
