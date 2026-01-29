/*******************************************************************\
| REGLIAK.C                                                         |
\*******************************************************************/

/*
 * 03/08/05 Arandir     Removed polishing of nonexistent mirror
 * 02/02/05 Arandir	Ported to new area
 * 01/01/26 Manat	Added functions for lizard amulet
 * 00/12/26 Manat	Fixed typos
 * 98/10/22 Cirion	Created
 *
 */

#include <const.h>
#include <macros.h>

#include "../defs.h"

inherit M_NPC_MONK_BASE;

//-------------------------------------------------------------------

/*
 * Function name : m_verify_home
 * Description   : Makes sure we are at the start of our trip.
 *
 */

string m_verify_home ()
{
  if (environment () != find_object (M_PATH_ROOM + "/hall_lower_north"))
  {
    move_living ("away", M_PATH_ROOM + "/hall_lower_north");
  };

  return ("stretch");
}

//-------------------------------------------------------------------

void create_monster ()
{
  ::create_monster ();

  set_name ("regliak");
  set_gender (G_MALE);
  set_race_name ("dwarf");
  set_adj (({ "ancient", "blind" }));
  set_long ("His eyes white and sightless, this ancient " +
            "dwarf stands with the dignity of one who " +
            "has led a long and difficult life.\n");

  m_init (80);
  m_equip (({ 50 + random (100) }));
  m_stature (100, 35);

  // This sets various duties performed in the monastery ...

  set_act_time (10);
  add_act (({
    VBFC_ME ("m_verify_home"),
    "s", "s",
    "emote trims some of the branches of the tree.",
    "emote picks up the trimmed branches and piles them neatly near the doorway to the monastery.",
    "n", "w",
    "emote peers sightlessly around.",
    "w",
    "emote polishes the base of the great statue.",
    "emote dusts the altar with great respect.",
    "e", "e", "e",
    "greet maiko",
    "emote cleans the table with great care.",
    "emote cleans the window above the fireplace.",
    "w", "n",
    "emote polishes the jade pillars.",
    "e",
    "pet mzenska",
    "w", "w",
    "emote dusts off the desk.",
    "e" }),
    ACT_UNOBSERVED);
}

//-------------------------------------------------------------------

