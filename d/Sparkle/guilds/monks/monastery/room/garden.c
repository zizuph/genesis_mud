/*******************************************************************\
| GARDEN.C                                                          |
\*******************************************************************/

/*
 * 06/09/17 Arandir     Added herbs
 * 06/09/16 Arandir     Added support for sitting under the tree
 * 03/09/06 Arandir     Removed two extraneous newlines
 * 03/07/23 Arandir     Added the catacomb entrance
 * 03/04/25 Arandir     Polished up
 * 02/05/01 Arandir	Ported to new area without rewrite
 * 00/12/26 Manat	Fixed monastery typo
 * 98/06/14 Cirion	Created
 *
 */

#include <macros.h>

#include "../defs.h"

inherit M_ROOM_BASE;

//-------------------------------------------------------------------

int m_garden_leave (void)
{
  object oMe = this_player ();
  object oRoom = this_object ();

  if (oMe->query_prop (M_PROP_TMP_I_SITTING))
  {
    oMe->catch_tell ("You rise from the shadow of the linden tree.\n");
    tell_room (oRoom, QCTNAME (oMe) + " rises from the shadow of the linden tree.\n", oMe);
    oMe->remove_prop (M_PROP_TMP_I_SITTING);
  }

  return (FALSE);
}


int m_action_sit (string sArgs)
{
  object oMe = this_player ();
  object oRoom = this_object ();

  notify_fail (capitalize (query_verb()) + " down?\n");

  if (sArgs != "down") return (FALSE);

  if (oMe->query_prop (M_PROP_TMP_I_SITTING))
  {
    oMe->catch_tell ("You move a little in the shadow of the linden tree.\n");
    tell_room (oRoom, QCTNAME (oMe) + " moves a little in the shadow of the linden tree.\n", oMe);
  }
  else
  {
    oMe->catch_tell ("You sit in the shadow of the linden tree.\n");
    tell_room (oRoom, QCTNAME (oMe) + " sits in the shadow of the linden tree.\n", oMe);
    oMe->add_prop (M_PROP_TMP_I_SITTING, TRUE);
  }

  return (TRUE);
}


int m_action_stand (string sArgs)
{
  object oMe = this_player ();

  notify_fail (capitalize (query_verb()) + " up?\n");

  if (sArgs != "up") return (FALSE);

  m_garden_leave ();

  return (TRUE);
}


void create_room ()
{
  set_short ("garden");
  set_long ("Tiny red flowers carpet the soft ground of this " +
            "peaceful circular garden. Rising in the center of the " +
            "place is a tall linden tree in full bloom, creating an " +
            "area of cool shade around it. A small gravel path circles " +
            "the tree, parting from a small, ancient stone stairwell " +
            "that winds down into darkness. To the north, a wide archway " +
            "opens into the great hall, and enclosing the garden are four " +
            "small stone buildings, which open to the northwest, northeast, " +
            "southwest, and southeast. The whole garden breathes with life " +
            "and joy.\n");

  dg_add_herbs (DG_HERBS_GARDEN);

  add_exit ("hall_lower_south", "north", &m_garden_leave ());
  add_exit ("training_defence", "northeast", &m_garden_leave ());
  add_exit ("training_other", "southeast", &m_garden_leave ());
  add_exit ("training_focus", "southwest", &m_garden_leave ());
  add_exit ("training_unarmed", "northwest", &m_garden_leave ());
  add_exit (DG_PATH + "/catacombs/room/cave_entrance", "down", &m_garden_leave ());

  dg_add_entrance ("north",
                   "You walk down the short passage and emerge in a brightly lit garden.");
  dg_add_entrance ("down",
                   "You climb the stairs and emerge in a brightly lit garden.");

  add_item (({ "branch", "branches", "pile" }),
            "Besides the branches of the linden tree, there " +
            "is another small pile of branches stacked near " +
            "the entrance to the monastery, drying in the sun.\n");
  add_item (({ "sun", "sunlight" }),
            "The sunlight filters through the leaves of the " +
            "linden tree, forming mottled fragmented patterns " +
            "that dance around magically.\n");
  add_item (({ "ground", "path", "gravel" }),
            "The gravel path circles around the linden tree in " +
            "the center of the garden, branching out to the " +
            "four buildings at the corners.\n");
  add_item (({ "wall", "walls" }),
            "The garden walls around are made from neatly fitted " +
            "blocks of grey stone.\n");
  add_item (({ "building", "buildings" }),
            "There are four stone buildings at the corners of " +
            "the garden with open doorways.\n");
  add_item (({ "tree", "linden" }),
            "The soft light wood of the linden tree blossoms at " +
            "the end with cymes of light yellow flowers, and " +
            "large cordate leaves. It offers shade and " +
            "coolness to the garden, the movements of its " +
            "leaves causing the sunlight to dance gently upon " +
            "the gravel path.\n");
  add_item (({ "leaf", "leaves", "cordate" }),
            "They are heart-shaped, and sway in the breeze.\n");
  add_item (({ "flower", "flowers", "red flowers" }),
            "They are tiny red flowers, called by some Dragon Blood.\n");
  add_item (({ "archway" }),
            "It is a wide arch that opens north into the great hall.\n");
}

//-------------------------------------------------------------------

void init ()
{
  ::init ();

  add_action (m_action_sit, "sit");
  add_action (m_action_stand, "stand");
}

//-------------------------------------------------------------------

