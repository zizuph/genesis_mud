/*******************************************************************\
| DINING_HALL.C                                                     |
\*******************************************************************/

/*
 * 98/06/01 Cirion	Created
 * 01/04/22 Manat	Added a mirror
 * 01/05/11 Manat       Added the mirror to the short desc
 * 03/04/25 Arandir     Ported and removed the mirror
 * 03/08/05 Arandir     Fixed references to sunlight
 * 04/02/08 Arandir     Added the sign with list hint
 * 04/08/15 Arandir     Added the missing inside property
 *
 */

#include <macros.h>
#include <language.h>
#include <composite.h>
#include <stdproperties.h>

#include "../defs.h"

inherit M_ROOM_BASE;

inherit DG_OBJ_LIBS;
inherit M_PLAYER_LIBS;

//-------------------------------------------------------------------

private object oTable;

//-------------------------------------------------------------------

/*
 * Function name : m_get_table
 * Description   : Returns the table to place items on
 *
 */

object m_get_table ()
{
  return (oTable);
}

//-------------------------------------------------------------------

int m_public_filter (string sWho)
{
  return (!dg_is_junior (sWho) && !dg_is_wizard (sWho));
}

/*
 * Function name : m_get_chairs
 * Description   : Returns member names that are visible on
 *                 chairs in the dining hall. Note that this
 *                 function is also called by the table object
 *                 in this room.
 *
 */

string *m_get_chairs ()
{
  return (dg_capitalize_array (filter (m_get_monks (), &m_public_filter ())));
}

//-------------------------------------------------------------------

string m_desc_table ()
{
  string sDesc = oTable->dg_get_description () + " ";

  sDesc += "Around the table are " +
           LANG_WNUM (sizeof (m_get_chairs ())) +
           " oak chairs.";

  return (sDesc);
}

string m_desc_chairs ()
{
  return ("The chairs are all identical, and are arranged " +
          "evenly around the table. The chairs each have a name " +
          "written on the back in a delicate script. The names read: " +
          COMPOSITE_WORDS (m_get_chairs ()) + ".\n");
}

//-------------------------------------------------------------------

void create_room ()
{
  oTable = dg_clone_here (M_PATH_OBJ + "/dining_table");

  set_short ("dining hall");
  set_long ("This is a long, warm room with a very high ceiling. " +
            VBFC_ME ("m_desc_table") + " " +
            dg_embed_composite () +
            "Set within the eastern wall is a large stone fireplace, " +
            "above which is a circular, green-glass window. Through the " +
            "window, pale rays of " +
            dg_embed_when_night ("starlight fall upon the table, covering everything in an eerie radiance. ") +
            dg_embed_when_not_night ("sunlight fall upon the table, bathing everything in a friendly, warm radiance. ") +
            "A doorway in the west wall leads out into a dark hall.\n");

  add_prop (ROOM_I_INSIDE, TRUE);

  add_exit ("hall_lower_south", "west");

  dg_add_entrance ("west", "You pass through the doorway into the large dining hall.");

  add_item (({ "floor", "tile", "tiles", "ground", "stone" }),
            "The square tiles that make up the floor are rough stone, " +
            "fitted together evently and with great care. The stone, " +
            "although rough, is worn down by the passage of many " +
            "feet over the years.\n" +
            dg_embed_action ("stoops down to examine the stone tiles that make up the floor."));
  add_item (({ "glass", "window", "glass window", "green window" }),
            "The window is made from four panes of smooth green " +
            "glass, separated by thin slates of old wood. The window " +
            "softens the light that hits it, making it seem to " +
            "flow like water into the room and come to rest on the " +
            "redwood table and hard stone floor.\n" +
            dg_embed_action ("peers up at the window, and is bathed in green light."));
  add_item (({ "fireplace", "fire", "fire pit" }),
            "The fireplace is very large, its mantle almost level " +
            "with the bottom of the window. Some cold ashes lie " +
            "in the fireplace, a remnant of the last cold winter.\n" +
            dg_embed_action ("stoops to examine the fireplace."));
  add_item (({ "ash", "ashes" }),
            "They are a reminder of the cold winters.\n" +
            dg_embed_action ("sifts through the ashes."));
  add_item (({ "mantle", "mantlepiece" }),
            "The mantle atop the fireplace is a long, heavy slab of " +
            "dark marble. Aside from some dust, only a small sign " +
            "rests atop it.\n");
  add_item (({ "sign", "note" }),
            "A small sign rests atop the mantle. In ornate lettering, " +
            "the sign informs you that you can <list prices> here.\n");
  add_item (({ "sun", "stars", "sunlight", "starlight", "light", "radiance" }),
            "The light is given a green tint by the green glass " +
            "window as it falls on the table and the floor.\n");

  add_item (({ "chair", "chairs"}), &m_desc_chairs ());

  // Clone the livings that populate the dining hall.

  dg_clone_here (M_PATH_NPC + "/maiko", 0,
                 "Standing next to the table is an elderly wrinkled " +
                 "human, his wizened and serene face indicating years " +
                 "of dedicated service to the order. ");
}

//-------------------------------------------------------------------

