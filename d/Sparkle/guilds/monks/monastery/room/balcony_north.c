/*******************************************************************\
| BALCONY_NORTH.C                                                   |
\*******************************************************************/

/*
 * 98/06/14 Cirion	Created
 * 00/12/26 Manat	Fixed a typo
 * 02/05/01 Arandir	Ported to new area without rewrite
 * 03/04/25 Arandir     Polished up
 * 04/03/06 Arandir     Made the tree visible from here
 *
 */

#include <language.h>

#include "../defs.h"

inherit M_ROOM_BASE;

//-------------------------------------------------------------------

void create_room ()
{
  object oRoom;
  object oTree;

  set_short ("northern balcony");

  oRoom = (M_PATH_ROOM + "/lawn_ne")->get_this_object ();
  oTree = present ("tree", oRoom);
  if (oTree)
  {
    set_long ("A fresh spring breeze blows across this wide stone balcony, " +
              "whistling in the leaves of " + LANG_ADDART (oTree->short ()) +
              ". Green grass covers the front entrance of the monastery. " +
              "A leaded glass door leads into the northern hall to the south." +
              dg_embed_livings ("lawn_ne", " Standing under the " + oTree->short () + " below, you see ", ".", "") +
              "\n");

    add_item ("tree", oTree->long ());
  }
  else
  {
    set_long ("A fresh spring breeze blows across this wide stone balcony which " +
              "overlooks the green grass that covers the front entrance of the " +
              "monastery. A leaded glass door leads into the northern hall to " +
              "the south." +
              dg_embed_livings ("lawn_ne", " Standing on the lawn below, you see ", ".", "") +
              "\n");
  }

  add_exit ("hall_upper_north", "south");

  dg_add_entrance ("south", "A fresh spring breeze meets you as you walk out onto the balcony.");

  add_item (({ "lawn", "grass" }),
            "The lawn stretching down below is fertile and " +
            "well kept. The wind washes over it, causing the " +
            "blades of grass to undulate in perfect harmony.\n");
  add_item (({ "door", "doors", "lead", "glass" }),
            "The leaded glass doors open to the south into the " +
            "upper hall of the monastery.\n");

  add_cmd_item (({ "wind", "breeze", "air"}),
                ({ "feel", "touch" }),
                "The spring breeze feels cool and refreshing on your face.\n" +
                dg_embed_action ("breathes in the fresh spring air."));
}

//-------------------------------------------------------------------

