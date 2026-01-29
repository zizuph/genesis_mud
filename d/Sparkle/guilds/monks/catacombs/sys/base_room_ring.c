/*******************************************************************\
| BASE_ROOM_RING.C                                                  |
+-------------------------------------------------------------------+
| Base room module for rings in the catacomb area. The purpose of   |
| the rings is to give a hint as to which form is useful for        |
| acquiring the hit and pen of specific classes of weapons.         |
\*******************************************************************/

/*
 * 06/09/26 Arandir     Added more items
 * 06/09/24 Arandir	Created
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

//-------------------------------------------------------------------

int iRing;
int iSkill;

string sFormDesc = "";
string sViewDesc = "";
string sFacingDesc = "";


// Number of rings

#define CC_RINGS                9

// Positions of rings on a circle

#define CC_RINGS_FACING         ({ "northeast", "east", "east", \
                                   "southeast", "south", "southwest", \
                                   "west", "west", "northwest" })

//-------------------------------------------------------------------

string cc_ring_long ()
{
  string sResult = "The wide ledge that you stand on is facing "
                   + sFacingDesc + "wards, ";

  if (dg_is_night ())
  {
    sResult += "opening into an empty space filled with " +
               "a chilling darkness that makes you wary " +
               "of moving anywhere.";
  }
  else
  {
    sResult += "revealing a view of the mountains that " +
               "is breathtaking in both its beauty and " +
               "in the awe that a random thought of " +
               "falling down evokes.";
  }

  sResult += " The rough texture of the stone behind your " +
             "back is comforting to lean against, even if " +
             "not exactly warm. ";

  if ((iRing == 0) || (iRing == CC_RINGS - 1))
  {
    sResult += "You note with surprise that besides the crevice in " +
               "the steep side of the spire, another ledge also " +
               "seems reachable.";
  }
  else
  {
    sResult += "Similar ledges are reachable to both sides of you.";
  }

  sResult += "\n";
  return (sResult);
}


string cc_desc_view ()
{
  if (dg_is_night ())
  {
    return ("You can see only darkness all around you.\n");
  }
  else
  {
    return (sViewDesc + "\n");
  }
}


string cc_desc_ledge ()
{
  if (dg_is_night ())
  {
    return ("Feeling around the ledge you are standing on, " +
            "you conclude it is of a wide regular shape. " +
            "There seems to be a slight draft of air " +
            "coming from under the ledge.\n");
  }
  else
  {
    return ("The ledge you are standing on is of a wide regular " +
            "shape. There is a slight draft coming from under " +
            "the ledge. Leaning over the edge to see more, " +
            "you notice a large opening just below.\n");
  }
}


string cc_desc_column ()
{
  string sResult;

  if (dg_is_night ())
  {
    sResult = "After you strain for a while to see into the opening " +
              "just below, you realize it is too dark right now to " +
              "see anything. Better wait for daylight.";
  }
  else
  {
    sResult = "Leaning over the ledge to get a better look into the " +
              "opening just below, you see a base of a grand column " +
              "of stone. The base appears to be adorned with a " +
              "scene of a fight where a robed figure with " +
              "bare hands faces a warrior ";

    switch (iSkill)
    {
      case M_SKILL_FORMING_CLUB:
        sResult += "wielding a glistening weapon, most likely a mace or an axe.";
        break;
      case M_SKILL_FORMING_BLADE:
        sResult += "armed with a long sword and a short knife.";
        break;
      case M_SKILL_FORMING_STICK:
        sResult += "brandishing what must be a spike or a halberd.";
        break;
    }

    sResult += " Strangely, the robed figure does not look at all " +
               "cowed, but instead fights back with " + sFormDesc + ".";
  }

  sResult += "\n";
  return (sResult);
}

//-------------------------------------------------------------------

void cc_create_ring (
  int iArgRing,
  int iArgSkill,
  string sArgFormDesc,
  string sArgViewDesc)
{
  iRing = iArgRing;
  iSkill = iArgSkill;
  sFormDesc = sArgFormDesc;
  sViewDesc = sArgViewDesc;
  sFacingDesc = CC_RINGS_FACING [iRing];

  set_short ("wide " + sFacingDesc + "ern ledge");
  set_long (&cc_ring_long ());

  // Add the items describing the form and all.

  add_item (({ "view", "mountains" }),
            &cc_desc_view ());
  add_item (({ "ledge", "ledges", "moulding" }),
            &cc_desc_ledge ());
  add_item (({ "waft", "draft" }),
            "A slight draft seems to come from under the ledge, " +
            "as if there was an opening of some kind right " +
            "underneath it.\n");
  add_item (({ "opening", "column", "relief", "figure", "painting" }),
            &cc_desc_column ());

  add_item (({ "stone", "texture" }),
            "The stone of the spire is rough and cold to the touch.\n");

  dg_item_sky_outside ();

  // Add the exits to the other rings.

  if (iRing == 0)
  {
    add_exit (DG_PATH + "/mountains/room/spire", "crevice");
  }
  else
  {
    add_exit ("ring_" + ((iRing + CC_RINGS - 1) % CC_RINGS), "counterclockwise");
    dg_add_entrance ("counterclockwise", "You gingerly walk towards the end of the ledge and slowly step across the gap separating it from its neighbor.");
  }

  if (iRing == CC_RINGS - 1)
  {
    add_exit (DG_PATH + "/mountains/room/spire", "crevice");
  }
  else
  {
    add_exit ("ring_" + (iRing + 1) % CC_RINGS, "clockwise");
    dg_add_entrance ("clockwise", "You gingerly walk towards the end of the ledge and slowly step across the gap separating it from its neighbor.");
  }
}

//-------------------------------------------------------------------

/*******************************************************************\
| Items A-F                                                         |
\*******************************************************************/

void cc_item_crevice ()
{
  add_item (({ "crevice" }),
            "The crevice you have used to get onto the ledge is " +
            "easily within your reach. From this angle, it " +
            "looks almost like you could simply walk back " +
            "into it.\n");
}

/*******************************************************************\
| Items G-L                                                         |
\*******************************************************************/

/*******************************************************************\
| Items M-R                                                         |
\*******************************************************************/

/*******************************************************************\
| Items S-Z                                                         |
\*******************************************************************/

//-------------------------------------------------------------------

