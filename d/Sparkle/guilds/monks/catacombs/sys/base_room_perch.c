/*******************************************************************\
| BASE_ROOM_PERCH.C                                                 |
+-------------------------------------------------------------------+
| Base room module for perches in the catacomb area.                |
\*******************************************************************/

/*
 * 04/08/15 Arandir     Added the missing inside property
 * 03/09/09 Arandir     Walkways cannot be crossed drunk
 * 03/07/19 Arandir	Created
 *
 */

#include <tasks.h>
#include <macros.h>
#include <ss_types.h>
#include <composite.h>
#include <filter_funs.h>
#include <stdproperties.h>

#include "../defs.h"
#include "../../monastery/defs.h"

inherit CC_ROOM_BASE;

inherit "/sys/global/math";
inherit M_PLAYER_LIBS;

//-------------------------------------------------------------------

int    iCircle;
int    iPerch;

string sDragonName      = "";
string sDragonDesc      = "";
string sDescOpening     = "";
string sReliefKinsman   = "";
string sReliefForeigner = "";


// Number of circles and perches per circle

#define CC_CIRCLES              5
#define CC_PERCHES              5

// Number of dragons on each of the circles and
// an index of each perch with a dragon

#define CC_DRAGONS_PER_CIRCLE   ({ 3, 3, 3, 3, 3 })
#define CC_DRAGONS_ON_CIRCLES   ({ ({ 0, 2, 4 }), \
                                   ({ 0, 2, 4 }), \
                                   ({ 0, 2, 4 }), \
                                   ({ 0, 2, 4 }), \
                                   ({ 0, 2, 4 }) })

// Positions of perches on a circle

#define CC_PERCHES_ODD          ({ "southwest", "northwest", "north", "northeast", "southeast" })
#define CC_PERCHES_EVEN         ({ "south", "southwest", "northwest", "northeast", "southeast" })

//-------------------------------------------------------------------

/*
 * Function name : cc_is_friend
 * Description   : Tells whether a monk is a friend of the dragon
 *                 whose soul is present on this particular perch
 *
 */

int cc_is_friend (object oWho)
{
  string sWho = dg_get_name (oWho);
  int iDragons = CC_DRAGONS_PER_CIRCLE [iCircle];
  int iHash = name_to_random (sWho, iCircle, iDragons);

  // Every player can be a friend with two dragons on a circle.

  return (oWho->m_is_kin (sDragonName) &&
          ((iPerch == CC_DRAGONS_ON_CIRCLES [iCircle][iHash]) ||
           (iPerch == CC_DRAGONS_ON_CIRCLES [iCircle][(iHash + iDragons / 2) % iDragons])));
}


int cc_exit_cross_tangential ()
{
  object oHim = this_player ();

  if (oHim->query_intoxicated ())
  {
    write ("You set out to cross the narrow walkway, but a quick " +
           "glance to the depths below makes your head spin. It " +
           "strikes you as a good idea to only try crossing " +
           "the walkway when sober.\n");
    return (TRUE);
  }

  return (FALSE);
}


int cc_exit_cross_radial ()
{
  object oHim = this_player ();
  string sHim = dg_get_name (oHim);

  if (oHim->query_intoxicated ())
  {
    write ("You set out to cross the narrow walkway, but a quick " +
           "glance to the depths below makes your head spin. It " +
           "strikes you as a good idea to only try crossing " +
           "the walkway when sober.\n");
    return (TRUE);
  }

  if (cc_is_friend (oHim)) return (FALSE);

  if (oHim->m_is_kin (sDragonName))
  {
    write ("The more you advance along the steep walkway towards the " +
           "center of the cave, the more slippery it becomes. Not even " +
           "halfway, you turn around and return, understanding that you " +
           "were not meant to cross here.\n");
  }
  else
  {
    write ("You feel that the joining of the column with the steep " +
           "walkway towards the center of the cave is not strong " +
           "enough. It is as if something was missing from the " +
           "column itself, preventing you from crossing.\n");
  }

  return (TRUE);
}


int cc_exit_cross_center ()
{
  object oHim = this_player ();
  object *aoPlayers;
  object *aoItems;
  int    iItem;

  // Only one player can fight for his guru level at the podium,
  // otherwise the opponent avatar gets confused.

  DG_LOAD (CC_ROOM_CENTER);

  aoPlayers = FILTER_PLAYERS (all_inventory (find_object (CC_ROOM_CENTER)));
  if (sizeof (aoPlayers))
  {
    write ("You see " + COMPOSITE_LIVE (aoPlayers) + " already standing " +
           "on the podium. Feeling that the podium is a sacred place, " +
           "you decide not to intrude.\n");
    return (TRUE);
  }

  // We do not want players to come equipped too well so as not
  // to have too easy a time defeating the opponent avatar.

  aoItems = all_inventory (oHim);
  for (iItem = 0 ; iItem < sizeof (aoItems) ; iItem ++)
  {
    if (!aoItems [iItem]->query_prop (OBJ_M_NO_DROP))
    {
      write ("Feeling that the podium is a sacred place, you decide " +
             "not to cross with all the things you are carrying.\n");
      return (TRUE);
    }
  }

  return (cc_exit_cross_radial ());
}

//-------------------------------------------------------------------

string cc_perch_long ()
{
  object oHim = this_player ();

  if (oHim->m_is_kin (sDragonName))
  {
    if (cc_is_friend (oHim))
    {
      return (sDescOpening + sReliefKinsman + " The shimmering shape radiates a feeling of kinship.\n");
    }
    else
    {
      return (sDescOpening + sReliefKinsman + "\n");
    }
  }

  return (sDescOpening + sReliefForeigner + "\n");
}

//-------------------------------------------------------------------

string cc_desc_dais ()
{
  object oHim = this_player ();

  if (oHim->m_is_kin (sDragonName))
  {
    return ("The dais is made of black stone, " + sReliefKinsman + "\n");
  }
  else
  {
    return ("The dais is made of black stone, " + sReliefForeigner + "\n");
  }
}


string cc_desc_dragon ()
{
  object oHim = this_player ();

  if (oHim->m_is_kin (sDragonName))
  {
    return (sDragonDesc + "\n");
  }
  else
  {
    return ("You see no such thing.\n");
  }
}


string cc_desc_dragon_touch ()
{
  object oHim = this_player ();
  object oRoom = environment (oHim);

  if (strlen (sDragonName))
  {
    if (oHim->m_is_kin (sDragonName))
    {
      if (cc_is_friend (oHim))
      {
        tell_room (oRoom,
                   QCTNAME (oHim) + " reaches out towards the relief. " +
                   "Suddenly, the relief springs into life, covered " +
                   "with silvery aura.\n",
                   oHim);
        return ("You reach out and touch the shape of the dragon. " +
                "As your hand draws near, the faint shimmer that " +
                "permeates the shape grows more intense, forming " +
                "a silvery aura that extends from the dragon to " +
                "envelop your entire arm.\n");
      }
      else
      {
        tell_room (oRoom,
                   QCTNAME (oHim) + " reaches out towards the relief, " +
                   "causing faint flashes of silvery light to appear " +
                   "across its surface.\n",
                   oHim);
        return ("You reach out and touch the shape of the dragon. " +
                "As your hand draws near, you see a faint flash " +
                "of silvery light glisten across the relief.\n");
      }
    }

    tell_room (oRoom,
               QCTNAME (oHim) + " traces the contours of the relief.\n",
               oHim);
    return ("You reach out and touch the surface of the relief. As your " +
            "hand traces the contours, you suddenly feel a presence of " +
            "life inside the stone, faint but unmistakable.\n");
  }
  else
  {
    tell_room (oRoom,
               QCTNAME (oHim) + " brushes the smooth surface of the dais.\n",
               oHim);
    return ("You reach out and brush the smooth surface of the dais.\n");
  }
}

//-------------------------------------------------------------------

void cc_create_perch (
  int iArgCircle,
  int iArgPerch,
  string sArgReliefForeigner,
  string sArgReliefKinsman,
  string sArgDragonName,
  string sArgDragonDesc)
{
  string sFragmentOpening;
  string sFragmentPosition;

  iCircle = iArgCircle;
  iPerch = iArgPerch;
  sReliefForeigner = sArgReliefForeigner;
  sReliefKinsman = sArgReliefKinsman;
  sDragonName = sArgDragonName;
  sDragonDesc = sArgDragonDesc;

  switch (iCircle)
  {
    case 0:

      sFragmentOpening = "You find yourself on top of a wide and tall stone " +
                         "column, one of five that form a circle lining " +
                         "the walls of a large underground cave.";
      sFragmentPosition = CC_PERCHES_EVEN [iPerch];

      cc_item_columns_outer ();
      cc_item_walkways_outer ();

      break;

    case 1:

      sFragmentOpening = "You stand on top of a wide and tall stone column, " +
                         "one of five that form the second concentric circle " +
                         "of columns inside a large underground cave. You can " +
                         "see the columns of the first circle well, them being " +
                         "the tallest columns in the cave.";
      sFragmentPosition = CC_PERCHES_ODD [iPerch];

      cc_item_columns_outer ();
      cc_item_walkways_outer ();

      break;

    case 2:

      sFragmentOpening = "You stand on top of a stone column that forms the " +
                         "third circle of columns inside a large underground " +
                         "cave. The columns of the other circles rise from " +
                         "the shadows around you in an intriguingly regular " +
                         "pattern.";
      sFragmentPosition = CC_PERCHES_EVEN [iPerch];

      cc_item_columns_inner ();
      cc_item_walkways_inner ();

      break;

    case 3:

      sFragmentOpening = "You are on a top of a stone column of the fourth " +
                         "circle. Around you is an intricate patern of the " +
                         "other stone columns and the walkways that connect " +
                         "them.";
      sFragmentPosition = CC_PERCHES_ODD [iPerch];

      cc_item_columns_inner ();
      cc_item_walkways_inner ();

      break;

    case 4:

      sFragmentOpening = "You are on top of a column of the fifth and smallest " +
                         "circle. Outside, the arcane pattern of columns and " +
                         "walkways disappears into the darkness. In stark " +
                         "contrast, the inside of the circle is formed by " +
                         "five straight walkways, all headed towards a " +
                         "podium in the very center of the cave.";
      sFragmentPosition = CC_PERCHES_EVEN [iPerch];

      cc_item_columns_inner ();
      cc_item_walkways_inner ();

      break;
  }

  cc_item_cave_inside ();

  // Compose a description out of the fragments that we have.
  // The proper description is selected depending on the observer.

  sDescOpening =
    sFragmentOpening +
    " The column is situated in the " +
    sFragmentPosition + "ern part " +
    "of the cave and is connected with its left and right " +
    "neighbors via narrow arches of stone walkways. In the " +
    "middle of the column is a waist-high dais of black stone, ";

  set_short ("tall stone column");
  set_long (&cc_perch_long ());

  // Add the necessary properties.

  add_prop (ROOM_I_INSIDE, TRUE);

  // Add the items describing the relief.

  add_item (({ "dais", "relief" }),
            &cc_desc_dais ());

  add_cmd_item (({ "dais", "relief", "dragon", "shape", "dragon shape" }),
                ({ "touch", "trace", "brush", "feel" }),
                &cc_desc_dragon_touch ());

  if (strlen (sDragonName))
  {
    add_item (({ "dragon", "shape", "dragon shape", "shimmering shape" }),
              &cc_desc_dragon () );
  }

  // Add the exits to the other perches.

  add_exit ("perch_" + iCircle + "_" + (iPerch + 1) % CC_PERCHES,
            "clockwise", &cc_exit_cross_tangential ());
  add_exit ("perch_" + iCircle + "_" + ((iPerch + CC_PERCHES - 1) % CC_PERCHES),
            "counterclockwise", &cc_exit_cross_tangential ());

  if (iCircle == 0)
  {
    if (iPerch == 0)
    {
      add_exit ("cave_entrance", "south");
    }
  }
  else
  {
    add_exit ("perch_" + (iCircle - 1) + "_" + iPerch, "outward");
  }

  if (iCircle == CC_CIRCLES - 1)
  {
    add_exit ("cave_center", "inward", &cc_exit_cross_center ());
  }
  else
  {
    add_exit ("perch_" + (iCircle + 1) + "_" + iPerch, "inward", &cc_exit_cross_radial ());
  }
}

//-------------------------------------------------------------------

