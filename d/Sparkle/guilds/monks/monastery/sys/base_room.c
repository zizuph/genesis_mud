/*******************************************************************\
| BASE_ROOM.C                                                       |
+-------------------------------------------------------------------+
| Base room module for everything in the monk area.                 |
\*******************************************************************/

/*
 * 02/07/27 Arandir	Created
 * 03/03/29 Arandir     Support for statues
 *
 */

#include <language.h>
#include <composite.h>

#include "../defs.h"

inherit DG_ROOM_BASE;

inherit DG_CLOCK_LIBS;
inherit M_PLAYER_LIBS;

//-------------------------------------------------------------------

/*******************************************************************\
| Items A-F                                                         |
\*******************************************************************/

void m_item_cliff_drop ()
{
  add_item (({ "cliff", "drop", "down" }),
    "The sheer edge of the cliff drops down to a dark valley below.\n");
}

void m_item_cliff_path ()
{
  add_item (({ "cliff", "drop", "down", "path" }),
    "The edge of the cliff is broken by a rocky path, but " +
    "you would have to switch from walking to climbing " +
    "if you were to follow it down.\n");
}

void m_item_floor_rough_tiles ()
{
  add_item (({ "floor", "tile", "tiles", "ground", "stone" }),
    "The square tiles that make up the floor are rough stone, fitted " +
    "together evenly and with great care. The stone, although rough, " +
    "is worn down by the passage of many feet over the years.\n" +
    dg_embed_action (
      "stoops down to examine the stone tiles that make up the floor."));
}

void m_cmd_item_floor_rough_tiles ()
{
  add_cmd_item (
    ({ "stone", "stones", "tile", "tiles", "ground" }),
    ({ "touch", "feel" }),
    "The stones of the floor are smooth with the passage of many feet.\n" +
    dg_embed_action ("reaches down and touches the stone tiles."));
}

/*******************************************************************\
| Items G-L                                                         |
\*******************************************************************/

void m_item_grass_crushed ()
{
  add_item (({ "grass", "lawn", "ground" }),
            "The grass is crushed down, dying, as if by the " +
            "passage of many feet along this way.\n");
}

void m_item_grass_high_untended ()
{
  add_item (({ "grass", "lawn", "blades" }),
    "The grass here is high and untended.\n");
}

void m_item_grass_long_soft ()
{
  add_item (({ "grass", "lawn", "blades" }),
    "The grass is long and soft here.\n");
}

void m_item_grass_manicured ()
{
  add_item (({ "grass", "lawn", "blades"}),
    "The grass is well manicured here, and quivers as the " +
    "wind blows across it.\n");
}

/*******************************************************************\
| Items M-R                                                         |
\*******************************************************************/

void m_item_monastery_overhead ()
{
  add_item (({ "monastery", "building" }),
    "Its ancient stones rise high overhead.\n");
}

void m_item_monastery_stones ()
{
  add_item (({ "stone", "stones" }),
    "The monastery is formed of enormous blocks of dark grey stone.\n");
}

/*******************************************************************\
| Items S-Z                                                         |
\*******************************************************************/

void m_item_stair_worn ()
{
  add_item (({ "steps", "stone" }),
            "The stone steps are worn smooth by the passage of " +
            "many feet.\n");
}

string m_desc_statues_former (int iMinPercentage, int iMaxPercentage)
{
  string *asDescriptions;
  int    iIndex;

  asDescriptions = m_get_former_descs (iMinPercentage, iMaxPercentage);
  for (iIndex = 0 ; iIndex < sizeof (asDescriptions) ; iIndex ++)
    asDescriptions [iIndex] = LANG_ADDART (asDescriptions [iIndex]);

  return ("You gaze up and see ancient statues of monks: " +
          COMPOSITE_WORDS (asDescriptions) + "." +
          "\n");
}

void m_item_statues_former (int iMinPercentage, int iMaxPercentage)
{
  add_item (({ "statue", "statues" }), &m_desc_statues_former (iMinPercentage, iMaxPercentage));
}

//-------------------------------------------------------------------

