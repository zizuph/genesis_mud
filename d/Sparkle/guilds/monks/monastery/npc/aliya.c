/*******************************************************************\
| ALIYA.C                                                           |
\*******************************************************************/

/*
 * 02/02/05 Arandir	Ported to new area
 * 98/10/22 Cirion	Created
 *
 */

#include <const.h>
#include <macros.h>

#include "../defs.h"

inherit M_NPC_MONK_BASE;

//-------------------------------------------------------------------

void create_monster ()
{
  ::create_monster ();

  set_name ("aliya");
  set_gender (G_FEMALE);
  set_race_name ("elf");
  set_adj (({ "stern", "graceful" }));
  set_long ("While her face and figure of her race betray none " +
            "of her years, her dark blue eyes show the ages which " +
            "she has seen. She is dressed in a soft, flowing robe, " +
            "and holds a long feathered pen in her hand.\n");

  m_init ();
  m_equip (({ 20 + random (20) }));
  m_stature (195, 70);

  set_act_time (10);
  add_act (({ "emote reaches up and removes a book from the shelves.",
              "emote wipes the dust from the book.",
              "emote returns the book to the shelves." }));
  add_act ("peer sternly " + VBFC_ME ("dg_get_present_living_str"));
  add_act ("smile warmly " + VBFC_ME ("dg_get_present_living_str"));
  add_act ("sigh softly");
}

//-------------------------------------------------------------------

