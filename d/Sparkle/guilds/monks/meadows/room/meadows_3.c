/*******************************************************************\
| MEADOWS_3.C                                                       |
\*******************************************************************/

/*
 * 20/08/06 Lucius	Reset herbs
 * 06/09/17 Arandir     Added herbs
 * 03/12/12 Arandir     Made brook work as stream for drinking
 * 03/09/17 Arandir     Made the stream visible in autumn
 * 02/09/17 Arandir     Items added
 * 02/09/11 Arandir     Small description changes
 * 02/07/21 Arandir     Made it possible to drink here
 * 01/12/24 Arandir	First version of the description
 * 01/11/10 Arandir	Created
 *
 */

#include <macros.h>
#include <stdproperties.h>

#include "../defs.h"

inherit MD_ROOM_BASE;

inherit DG_CLOCK_LIBS;

//-------------------------------------------------------------------

string dg_long ();
int md_action_drink (string sWhat);

//-------------------------------------------------------------------

/*
 * Function name : init
 *
 */

void init ()
{
  ::init ();

  add_action (&md_action_drink (), "drink");
}

/*
 * Function name : reset_room
 */

void reset_room ()
{
    set_searched(0);
}

/*
 * Function name : create_room
 *
 */

void create_room ()
{
  ::create_room ();
  set_short ("meadows near the forest");
  set_long  (&dg_long ());

  add_prop (OBJ_I_CONTAIN_WATER, PROP_WATER_INFINITE);
  add_prop(ROOM_S_MAP_FILE, "sparkle_wide.txt");

  dg_add_herbs (DG_HERBS_MEADOW);

  add_exit ("meadows_2", "west");
  add_exit ("/d/Genesis/start/human/wild2/s_road2", "east");

  dg_add_entrance ("east", "You walk from under the trees into an open grassland.");

  dg_item_sky_outside ();

  md_item_countryside ();
  md_item_grass ();
  md_item_mountains ();

  add_item (({ "cliff", "cliffs" }),
    "Jagged cliffs line the mountains further north and west.\n");

  add_item (({ "spring", "stream", "brook", "water" }),
    dg_embed_when_winter (
      "The stream is ice cold, with shards of ice lining its " +
      "path down from the mountains and through the meadows.") +
    dg_embed_when_not_winter (
      "The brook gathers its strength as it hurries down the " +
      "mountains and through the grass of the meadows.") +
    "\n");

  add_item (({ "forest", "tree", "trees", "foliage" }),
    "The forest looks calm and pleasant, with foliage high above " +
    "swaying gently in the wind. The trees obscure your view " +
    "everywhere but towards the north.\n");
}

/*
 * Function name : dg_long
 *
 */

string dg_long ()
{
  string sDesc;

  sDesc = "Standing in the meadows near the forest, you look over the " +
          dg_get_stime_season () + " countryside.";

  if (dg_is_spring ()) sDesc +=
    " Bright green grass is all around you, well watered " +
    "by a nearby stream that cascades down from the mountains " +
    "to your north.";
  else if (dg_is_summer ()) sDesc +=
    " Lush grass covers the ground, with flowers blossoming " +
    "in the warm summer. Quiet gurgling of a nearby brook " +
    "underscores the peaceful atmosphere.";
  else if (dg_is_autumn ()) sDesc +=
    " Tall stalks reach eagerly towards the last rays " +
    "of the autumn sun, dark in the anticipation of the " +
    "coming winter. A cold stream hurries down from the " +
    "nearby mountains.";
  else if (dg_is_winter ()) sDesc +=
    " Dark grass, turning from green to brown, covers " +
    "the cold ground next to an icy stream that hurries " +
    "down from the nearby mountains.";

  if (!dg_is_night ()) sDesc +=
    dg_normalize_room ("meadows_2")->dg_get_livings (
      " You can see ", " in the forest west of the meadows.", "");

  sDesc += "\n";
  return (sDesc);
}

//-------------------------------------------------------------------

/*
 * Function name : md_action_drink
 * Description   : Drink a bit of water from the stream.
 *
 */

int md_action_drink (string sWhat)
{
  object oMe = this_player ();
  int    iMax, iNow;

  if (strlen (sWhat) &&
      parse_command (sWhat, ({ }), "[water] [from] 'stream' / 'brook'"))
  {
    // The difference between querying before and after drinking
    // is negligible, seeing as it is only for messages ...

    iMax = oMe->query_prop (LIVE_I_MAX_DRINK);
    iNow = oMe->query_soaked ();
    if (oMe->drink_soft (iMax / 22))
    {
      if (iNow < iMax/2)
      {
        write ("You scoop up a handful of water from the stream and drink it eagerly.\n");
        say (QCTNAME (oMe) + " scoops up a handful of water from the stream and drinks it eagerly.\n");
      }
      else
      {
        write ("You scoop up a handful of water from the stream and drink it slowly.\n");
        say (QCTNAME (oMe) + " scoops up a handful of water from the stream and drinks it slowly.\n");
      }
    }
    else
    {
      write ("You scoop up a handful of water from the stream but are unable to drink it.\n");
      say (QCTNAME (oMe) + " scoops up a handful of water from the stream and lets it drop again.\n");
    }

    return (TRUE);
  }

  return (FALSE);
}

//-------------------------------------------------------------------
