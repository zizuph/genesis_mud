/*******************************************************************\
| LAWN_NE.C                                                         |
\*******************************************************************/

/*
 * 98/11/26 Cirion	Created
 * 00/12/26 Manat	Fixed typos
 * 01/12/24 Arandir	Ported to new area
 * 02/07/27 Arandir	Modified to reflect the new surroundings
 * 02/09/29 Arandir     Added items
 * 03/08/05 Arandir     Typofixed an extra newline
 * 03/09/07 Arandir     Added the event tree object
 *
 */

#include <tasks.h>

#include "../defs.h"

inherit M_ROOM_BASE;

inherit DG_OBJ_LIBS;

//-------------------------------------------------------------------

void create_room ()
{
  set_short ("A peaceful lawn outside the monastery");
  set_long  ("The thin blades of verdant grass growing upon this " +
             "high plateau shiver in the strong, cold wind that " +
             "blows across the lawn. A path leads from the edge of " +
             "the cliff towards south, where the ancient stones " +
             "of a great monastery loom. A large wooden doorway " +
             "opens into the dark halls." +
             dg_embed_livings ("lawn_nw", " Standing on the lawn to the west, you see ", ".", "") +
             "\n");

  add_exit ("lawn_east_1", "southeast");
  add_exit ("lawn_nw", "west");
  add_exit ("hall_lower_north", "south");

  dg_add_climb (DG_PATH + "/mountains/room/spire",
                ({ "down", "slope", "spire", "cliff" }), TASK_ROUTINE,
                "You climb down the spire.",
                "climbs down the spire.",
                "arrives climbing down the spire.",
                "You try to climb down the spire but fail.",
                "tries to climb down the spire but fails.");

  dg_add_entrance ("south",
                   "You pass through the doorway and " +
                   "out onto the windy front lawn.");

  m_item_cliff_path ();
  m_item_grass_manicured ();
  m_item_monastery_stones ();

  add_item (({ "door", "doorway" }),
            "It is a massive, curved wooden arch that leads " +
            "into the ancient monastery to the south. Its " +
            "frame appears to have once held strong doors, " +
            "long since removed.\n");

  add_item (({ "monastery", "building" }),
            "Its ancient stones rise high overhead, and the " +
            "open doorway to the south leads into it.\n");


  // Add the event tree object the guild won
  dg_clone_here ("/d/Genesis/ateam/aoe/obj/monk_tree");
  dg_clone_here ("/d/Genesis/ateam/aoe/obj/monk_tree_2008");
}

//-------------------------------------------------------------------
