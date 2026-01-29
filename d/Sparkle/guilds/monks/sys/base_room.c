/*******************************************************************\
| BASE_ROOM.C                                                       |
+-------------------------------------------------------------------+
| Base room module for everything in the dragon area.               |
\*******************************************************************/

/*
 * 10/06/30 Lavellan    Fixed dg_get_livings to not show your steed
 * 08/02/02 Arandir     Using domain base room
 * 06/09/26 Arandir     Fixed a superfluous argument to herb function
 * 06/09/16 Arandir     Added herbs inspired by Elessar in Khalakhor
 * 03/12/22 Arandir     Added room check to dg_get_livings
 * 03/03/25 Arandir     Fixed a misdirected message in climb.
 * 03/03/04 Arandir     Teams now follow leader in climb
 * 02/09/18 Arandir     Added items
 * 02/01/19 Arandir	Added support for composite descriptions
 * 01/12/24 Arandir	Fixed typo when reporting time of day
 * 01/12/22 Arandir	Added support for movement messages, and
 *			for seeing livings in other rooms, based
 *			on the code Cirion developed for monks
 * 01/12/21 Arandir	Added support for entrance messages, based
 *			on the code Cirion developed for monks
 * 01/12/16 Arandir	Added support for climbing
 * 01/11/10 Arandir	Created
 *
 */

#include <tasks.h>
#include <macros.h>
#include <ss_types.h>
#include <composite.h>
#include <filter_funs.h>
#include <stdproperties.h>

#include "../defs.h"

inherit S_BASE_ROOM;

inherit DG_CLOCK_LIBS;

//-------------------------------------------------------------------

// What a pity LPC does not support structures, is it not ? :-)

// These are used to remember exits that are to be climbed

private string *asClimbRoom = ({ });
private mixed  maClimbExits = ({ });
private int    *aiClimbDifficulty = ({ });
private string *asClimbSuccessPlayer = ({ });
private string *asClimbSuccessOthers = ({ });
private string *asClimbSuccessTarget = ({ });
private string *asClimbFailurePlayer = ({ });
private string *asClimbFailureOthers = ({ });

// These are used to remember exits that display entry messages

private mixed  maEntranceExits = ({ });
private string *asEntranceMessage = ({ });

// These are used to remember rooms that receive movement messages

private int    iMovementTime = 0;
private mixed  maMovementRooms = ({ });
private string *asMovementMessage = ({ });

// These are used to remember object with composite description

private object oCompositeObject = 0;
private string sCompositeDesc = "";

//-------------------------------------------------------------------

/*
 * Function name : dg_normalize_room
 * Description   : Normalizes a room name by adding path to it if
 *                 necessary. Mostly copied from MudLib where
 *                 add_exit uses it but does not export it.
 *
 */

string dg_normalize_room (string sRoom)
{
  string *asParsed;
  string sNormalized;

  if (sRoom [0] != '/')
  {
    asParsed = explode (file_name (this_object ()), "/");
    asParsed [sizeof (asParsed) - 1] = sRoom;
    sNormalized = implode (asParsed, "/");
    return (sNormalized);
  }

  return (sRoom);
}

/*
 * Function name : dg_normalize_room_array
 * Description   : Normalizes an array of rooms.
 *
 */

string *dg_normalize_room_array (string *asRooms)
{
  // Note that we have to use an extra array here to prevent
  // the input argument from being overwritten.

  string *asResult = ({ });
  int    i;

  for (i = 0 ; i < sizeof (asRooms) ; i ++)
    asResult += ({ dg_normalize_room (asRooms [i]) });

  return (asResult);
}

//-------------------------------------------------------------------

/*******************************************************************\
| Support for climbing.                                             |
\*******************************************************************/

/*
 * Function name : dg_add_climb
 * Description   : Adds an exit that can be climbed.
 *
 */

void dg_add_climb (
  string sRoom,
  mixed  mExits,
  int    iDifficulty,
  string sSuccessPlayer,
  string sSuccessOthers,
  string sSuccessTarget,
  string sFailurePlayer,
  string sFailureOthers)
{
  asClimbRoom          += ({ dg_normalize_room (sRoom) });
  maClimbExits         += pointerp (mExits) ? ({ mExits })
                                            : ({ ({ mExits }) });
  aiClimbDifficulty    += ({ iDifficulty });
  asClimbSuccessPlayer += ({ sSuccessPlayer });
  asClimbSuccessOthers += ({ sSuccessOthers });
  asClimbSuccessTarget += ({ sSuccessTarget });
  asClimbFailurePlayer += ({ sFailurePlayer });
  asClimbFailureOthers += ({ sFailureOthers });
}

/*
 * Function name : dg_action_climb
 * Description   : Executed when somebody issues the climb action.
 *
 */

int dg_action_climb (string sWhere)
{
  object oMe = this_player ();
  int    iLocation;

  // We purposefuly do not call notify_fail here, because it is
  // simply too easy to notice something can be climbed then.

  for (iLocation = 0 ; iLocation < sizeof (maClimbExits) ; iLocation ++)
    if (member_array (sWhere, maClimbExits [iLocation]) >= 0)
    {
      // We have found the location the player wants to climb.

      if (oMe->resolve_task (aiClimbDifficulty [iLocation],
                             ({ SKILL_AVG, TS_STR, TS_DEX, SKILL_END,
                                SS_CLIMB })) > 0)
      {
        string sCommand = "$" + query_verb () + " " + sWhere;
        object *aoTeam = oMe->query_team ();
        object *aoLead = ({ });
        int    iMember;

        // Using set_dircmd causes move_living to call itself recursively,
        // which messes up the order of messages. This is why we make the
        // leader drag the team manually.

        for (iMember = 0 ; iMember < sizeof (aoTeam) ; iMember ++)
        {
          if ((oMe->check_seen (aoTeam [iMember])) &&
              (environment (oMe) == environment (aoTeam [iMember])))
          {
            aoLead += ({ aoTeam [iMember] });
          }
        }

        write (asClimbSuccessPlayer [iLocation] + "\n");
        say (QCTNAME (oMe) + " " + asClimbSuccessOthers [iLocation] + "\n");
        oMe->move_living ("M", asClimbRoom [iLocation], TRUE, FALSE);
        say (QCTNAME (oMe) + " " + asClimbSuccessTarget [iLocation] + "\n");

        for (iMember = 0 ; iMember < sizeof (aoLead) ; iMember ++)
        {
          aoLead [iMember]->command ("$" + sCommand);
        }
      }
      else
      {
        write (asClimbFailurePlayer [iLocation] + "\n");
        say (QCTNAME (oMe) + " " + asClimbFailureOthers [iLocation] + "\n");
      }
      return (TRUE);
    }

  return (FALSE);
}

//-------------------------------------------------------------------

/*******************************************************************\
| Support for entrance messages.                                    |
\*******************************************************************/

/*
 * Function name : dg_add_entrance
 * Description   : Adds an entrance that displays arrival message.
 *
 */

void dg_add_entrance (
  mixed mExits,
  string sMessage)
{
  maEntranceExits   += pointerp (mExits) ? ({ mExits })
                                         : ({ ({ mExits }) });
  asEntranceMessage += ({ sMessage });
}

/*
 * Function name : dg_hook_entrance
 * Description   : Executed when somebody enters this room.
 *
 */

private nomask void dg_hook_entrance (
  object oWho,
  object oFrom)
{
  // Only players can appreciate the messages :-) ...

  if (interactive (oWho))
  {
    // Find the name of the exit that leads to the room we came
    // from. If there are no bugs in the map, this will be the
    // exit we want to look up the message for.

    int iExitIndex = member_array (MASTER_OB (oFrom), query_exit_rooms ());

    if (iExitIndex >= 0)
    {
      string sExitCommand = query_exit_cmds () [iExitIndex];

      int iEntrance;

      for (iEntrance = 0 ; iEntrance < sizeof (maEntranceExits) ; iEntrance ++)
      {
        if (member_array (sExitCommand, maEntranceExits [iEntrance]) >= 0)
        {
          oWho->catch_msg (asEntranceMessage [iEntrance] + "\n");
          break;
        }
      }
    }
  }
}

//-------------------------------------------------------------------

/*******************************************************************\
| Support for movement messages.                                    |
\*******************************************************************/

/*
 * Function name : dg_add_movement
 * Description   : Adds a room that displays movement message.
 *
 */

void dg_add_movement (
  mixed  mRooms,
  string sMessage)
{
  maMovementRooms   += pointerp (mRooms) ? ({ dg_normalize_room_array (mRooms) })
                                         : ({ ({ dg_normalize_room (mRooms) }) });
  asMovementMessage += ({ sMessage });
}

/*
 * Function name : dg_hook_movement
 * Description   : Executed when somebody enters this room.
 *
 */

private nomask void dg_hook_movement ()
{
  // We only send movement messages to those rooms that were
  // already loaded. Probably gains nothing in terms of
  // performance, but that happens :-) ...

  int iMessage, iRoom;

  for (iMessage = 0 ; iMessage < sizeof (asMovementMessage) ; iMessage ++)
    for (iRoom = 0 ; iRoom < sizeof (maMovementRooms [iMessage]) ; iRoom ++)
    {
      object oRoom = find_object (maMovementRooms [iMessage] [iRoom]);
      if (oRoom) oRoom->dg_show_movement (asMovementMessage [iMessage]);
    }
}

/*
 * Function name : dg_show_movement
 * Description   : Executed when movement is observed.
 *
 */

void dg_show_movement (
  string sMessage)
{
  // Certain amount of time must expire since the last movement
  // message was shown, to prevent spamming the room.

  int iTime = time ();

  if ((iTime - iMovementTime) < 10) return;
  iMovementTime = iTime;
  tell_room (this_object (), sMessage + "\n");
}

//-------------------------------------------------------------------

/*******************************************************************\
| Support for living messages.                                      |
\*******************************************************************/

/*
 * Function name : dg_embed_livings
 * Description   : Returns a function describing livings in a room.
 *
 */

string dg_embed_livings (
  string sRoom,
  string sPrefix,
  string sSuffix,
  string sEmpty)
{
  // We have to load the room for which we return the function
  // otherwise the function will not get expanded correctly.
  // The call is what should load the room, and has been
  // copied from the LOAD_ERR standard macro.

  string sRoomFile = dg_normalize_room (sRoom);

  DG_LOAD (sRoomFile);

  return (VBFC ("dg_get_livings:" + sRoomFile +
                "|" + sPrefix + "|" + sSuffix + "|" + sEmpty));
}

/*
 * Function name : dg_get_livings
 * Description   : Returns a string describing livings in this room.
 *
 */

string dg_get_livings (
  string sPrefix,
  string sSuffix,
  string sEmpty)
{
  object oActor = this_player ();
  object *aoLivings;

  if (CAN_SEE_IN_ROOM (oActor))
  {
    aoLivings = FILTER_CAN_SEE (FILTER_LIVE (all_inventory ()), oActor);
    aoLivings -= ({ this_player()->query_steed() });
    if (sizeof (aoLivings))
    {
      return (sPrefix + COMPOSITE_LIVE (aoLivings) + sSuffix);
    }
  }

  return (sEmpty);
}

//-------------------------------------------------------------------

/*******************************************************************\
| Support for action messages.                                      |
\*******************************************************************/

/*
 * Function name : dg_embed_action
 * Description   : Returns a function describing an action in this room.
 *
 */

string dg_embed_action (
  string sMessage)
{
  return (VBFC ("dg_show_action:" + file_name (this_object ()) +
                "|" + sMessage));
}

/*
 * Function name : dg_show_action
 * Description   : Executed when action is observed.
 *
 */

string dg_show_action (
  string sMessage)
{
  object oMe = this_player ();

  tell_room (this_object (), QCTNAME (oMe) + " " + sMessage + "\n", oMe);

  return ("");
}

//-------------------------------------------------------------------

/*******************************************************************\
| Support for composite messages.                                   |
\*******************************************************************/

/*
 * Function name : dg_set_composite
 * Description   : One object in the room can be a part of the
 *                 room description rather than existing on its
 *                 own. This function sets the object and its
 *                 description.
 *
 */

void dg_set_composite (
  object oObject,
  string sDesc)
{
  if (oCompositeObject) throw ("dg_set_composite: Composite object already set.");

  oCompositeObject = oObject;
  sCompositeDesc = sDesc;
}

/*
 * Function name : dg_is_composite
 * Description   : This function tells whether the object passed
 *                 as its argument is the object that is a part of
 *                 the room description.
 *
 */

int dg_is_composite (
  object oObject)
{
  return (oCompositeObject == oObject);
}

/*
 * Function name : dg_embed_composite
 * Description   : This function embeds the description of the object
 *                 that is a part of the room description.
 *
 */

string dg_embed_composite ()
{
  return (VBFC_ME ("dg_get_composite"));
}

/*
 * Function name : dg_get_composite
 * Description   : This function returns the descripiton of the object
 *                 that is a part of the room description if the object
 *                 is present in the room.
 *
 */

string dg_get_composite ()
{
  if ((oCompositeObject) && present (oCompositeObject))
  {
    return (sCompositeDesc);
  }
  else
  {
    return ("");
  }
}

//-------------------------------------------------------------------

/*******************************************************************\
| Support for herbs.                                                |
\*******************************************************************/

/*
 * Function name : dg_add_herbs
 * Description   : Adds herbs to the room based on the room style.
 *
 */

void dg_add_herbs (int iStyle)
{
  // Set up properties required for searching to work.

  add_prop (OBJ_S_SEARCH_FUN, "dg_search_herbs");
  add_prop (OBJ_I_SEARCH_TIME, 5);

  // Throw in a few herbs depending on the room style.

  switch (iStyle)
  {
    case DG_HERBS_CLIFFS:
      add_herb_file ("/d/Gondor/common/herbs/frostheal");
      add_herb_file ("/d/Gondor/common/herbs/madwort");
      add_herb_file ("/d/Shire/common/herbs/nasturtium");
      add_herb_file ("/d/Shire/common/herbs/pindan");
      break;
    case DG_HERBS_FOREST:
      add_herb_file ("/d/Earthsea/herbs/herb_files/aspen_bark");
      add_herb_file ("/d/Earthsea/herbs/herb_files/morel");
      add_herb_file ("/d/Earthsea/herbs/herb_files/oakmoss");
      add_herb_file ("/d/Earthsea/herbs/herb_files/wintergreen");
      add_herb_file ("/d/Khalakhor/common/herbs/green_pine");
      add_herb_file ("/d/Shire/common/herbs/bilberry");
      add_herb_file ("/d/Shire/common/herbs/khuz");
      break;
    case DG_HERBS_GARDEN:
      add_herb_file ("/d/Earthsea/herbs/herb_files/blue_gentian");
      add_herb_file ("/d/Earthsea/herbs/herb_files/ginseng");
      add_herb_file ("/d/Earthsea/herbs/herb_files/moly");
      add_herb_file ("/d/Earthsea/herbs/herb_files/monkshood");
      add_herb_file ("/d/Earthsea/herbs/herb_files/spinach");
      add_herb_file ("/d/Earthsea/herbs/herb_files/tomato");
      add_herb_file ("/d/Earthsea/herbs/herb_files/yarrow");
      add_herb_file ("/d/Gondor/common/herbs/blackberry");
      add_herb_file ("/d/Gondor/common/herbs/raspberry");
      add_herb_file ("/d/Gondor/common/herbs/culkas");
      add_herb_file ("/d/Gondor/common/herbs/curugwath");
      add_herb_file ("/d/Gondor/common/herbs/yam");
      add_herb_file ("/d/Shire/common/herbs/glimmer");
      add_herb_file ("/d/Shire/common/herbs/lamia");
      add_herb_file ("/d/Shire/common/herbs/lianor_berry");
      break;
    case DG_HERBS_MEADOW:
      add_herb_file ("/d/Gondor/common/herbs/dill");
      add_herb_file ("/d/Gondor/common/herbs/fennel");
      add_herb_file ("/d/Gondor/common/herbs/marjoram");
      add_herb_file ("/d/Gondor/common/herbs/nettle");
      add_herb_file ("/d/Gondor/common/herbs/rosemary");
      add_herb_file ("/d/Gondor/common/herbs/thyme");
      add_herb_file ("/d/Khalakhor/common/herbs/honeysuckle");
      add_herb_file ("/d/Khalakhor/common/herbs/shamrock");
      add_herb_file ("/d/Shire/common/herbs/blackroot");
      add_herb_file ("/d/Shire/common/herbs/calendula");
      add_herb_file ("/d/Shire/common/herbs/grass");
      add_herb_file ("/d/Shire/common/herbs/hensbane");
      add_herb_file ("/d/Shire/common/herbs/laranthas");
      add_herb_file ("/d/Shire/common/herbs/maroea");
      add_herb_file ("/d/Shire/common/herbs/marshmallow");
      add_herb_file ("/d/Shire/common/herbs/oreste");
      break;
  }
}


string dg_search_herbs (object oWho, string sArgs)
{
  string sWhere;
  string sWhat;

  string *asHerbs;

  if (sscanf (sArgs, "%s for %s", sWhere, sWhat) != 2) return ("");
  if (member_array (sWhere, ({ "here", "ground" })) < 0) return ("");

  if (sWhat == "herbs")
  {
    return (search_for_herbs (oWho));
  }
  else
  {
    asHerbs = query_herb_files ();
    foreach (string sHerb : asHerbs)
    {
      DG_LOAD (sHerb);
      if (sWhat == sHerb->query_herb_name ())
      {
        return (search_for_herbs (oWho, sHerb));
      }
    }
    return ("");
  }
}

//-------------------------------------------------------------------

/*******************************************************************\
| Support for time.                                                 |
\*******************************************************************/

/*
 * Function name : dg_action_time
 * Description   : Executed when somebody issues the time action.
 *
 */

int dg_action_time ()
{
  if ((query_prop (ROOM_I_INSIDE)) || dg_is_night ())
  {
    write ("It's " +
           LANG_ADDART (dg_get_stime_season ()) + " " +
           dg_get_stime_period () + ", " +
           "but you are not sure what time it is exactly.\n");
  }
  else
  {
    write ("It's " +
           dg_get_stime_hour_of_period () + " o'clock on " +
           LANG_ADDART (dg_get_stime_season ()) + " " +
           dg_get_stime_period () + ".\n");
  }
  return (TRUE);
}

//-------------------------------------------------------------------

/*******************************************************************\
| Generic function hooks.                                           |
\*******************************************************************/

/*
 * Function name : create_room
 * Description   : Called when somebody loads the room.
 *
 */

void create_room ()
{
  ::create_room ();
  set_short ("Base room");
  set_long  ("Base room.\n");
}

/*
 * Function name : init
 * Description   : Called whenever somebody comes our way.
 *
 */

void init ()
{
  ::init ();

  add_action (dg_action_time, "time");
  add_action (dg_action_climb, "climb");
  add_action (dg_action_climb, "scale");
}

/*
 * Function name : enter_inv
 * Description   : Called whenever somebody comes our way.
 *
 */

void enter_inv (
  object oWho,
  object oFrom)
{
  ::enter_inv (oWho, oFrom);

  dg_hook_entrance (oWho, oFrom);
  dg_hook_movement ();
}

//-------------------------------------------------------------------

/*******************************************************************\
| Items A-F                                                         |
\*******************************************************************/

/*******************************************************************\
| Items G-L                                                         |
\*******************************************************************/

/*******************************************************************\
| Items M-R                                                         |
\*******************************************************************/

/*******************************************************************\
| Items S-Z                                                         |
\*******************************************************************/

string dg_desc_sky_outside_sky ()
{
  string sDesc;

  if (dg_is_night ())
  {
    if (dg_is_winter ())
      sDesc = "The night sky is very dark, with heavy winter " +
              "clouds obscuring whatever stars would be visible.";
    else
      sDesc = "The night sky is dark, but as you gaze up, you " +
              "notice a few stars flickering at the edge of " +
              "your vision.";
  }
  else
  {
    switch (dg_get_stime_season ())
    {
      case "spring":
        sDesc = "The sky is a bright blue, with the remnants of " +
                "winter clouds still visible.";
        break;
      case "summer":
        sDesc = "The sky is a marvellously deep blue. Only few bits " +
                "and threads of clouds remain, decorating the blue " +
                "background with often intriguing patterns.";
        break;
      case "autumn":
        sDesc = "The sky is a grey blue, with clouds growing " +
                "gradually every day.";
        break;
      case "winter":
        sDesc = "The sky is grey, with heavy winter clouds " +
                "hanging low and obscuring the weak rays of " +
                "the winter sun.";
        break;
    }
  }

  sDesc += "\n";
  return (sDesc);
}


string dg_desc_sky_outside_sun ()
{
  string sDesc;

  if (dg_is_night ())
  {
    sDesc = "It takes a better sight than yours to see the sun at night.";
  }
  else
  {
    switch (dg_get_stime_season ())
    {
      case "spring":
        sDesc = "The sun still travels low on the horizon, but " +
                "even the weakest of its rays are a welcome " +
                "change after the cold winter.";
        break;
      case "summer":
        sDesc = "The sun is at its full strength, a blazing ball " +
                "of fire impossible to look at for long. Still, " +
                "its rays do not provide much warmth.";
        break;
      case "autumn":
        sDesc = "The sun is getting obscured by clouds more often " +
                "every day, a sure sign of coming winter.";
        break;
      case "winter":
        sDesc = "The sun is barely visible behind the heavy " +
                "cover of the clouds.";
        break;
    }
  }

  sDesc += "\n";
  return (sDesc);
}


string dg_desc_sky_outside_moon ()
{
  string sDesc;

  if (dg_is_night ())
  {
    if (dg_is_winter ())
    {
      sDesc = "The clouds are so heavy the moon is not visible at all.";
    }
    else
    {
      sDesc = "The moon covers everything with a surreal silvery light.";
    }
  }
  else
  {
    sDesc = "It takes a better sight than yours to see the moon at daytime.";
  }

  sDesc += "\n";
  return (sDesc);
}


string dg_desc_sky_outside_clouds ()
{
  string sDesc;

  if (dg_is_night ())
  {
    sDesc = "The clouds are barely visible at night as lighter " +
            "patches of sky illuminated by moonlight.";
  }
  else
  {
    switch (dg_get_stime_season ())
    {
      case "spring":
        sDesc = "The remnants of winter clouds are still visible, " +
                "scattered all over the blue of the sky.";
        break;
      case "summer":
        sDesc = "Very few clouds are actually visible, their white " +
                "color contrasting with the blue sky.";
        break;
      case "autumn":
        sDesc = "The clouds appear to gather in increasing " +
                "numbers, their bright white color turning " +
                "to dark shades of grey as the winter nears.";
        break;
      case "winter":
        sDesc = "The clouds are heavy and low, covering the " +
                "sky in an impenetrable sea of dark grey.";
        break;
    }
  }

  sDesc += "\n";
  return (sDesc);
}


dg_item_sky_outside ()
{
  add_item (({ "sky" }),
    &dg_desc_sky_outside_sky ());
  add_item (({ "sun", "sun rays", "sunrays", "sun beams", "sunbeams", "sun light", "sunlight" }),
    &dg_desc_sky_outside_sun ());
  add_item (({ "moon", "moon rays", "moonrays", "moon beams", "moonbeams", "moon light", "moonlight" }),
    &dg_desc_sky_outside_moon ());
  add_item (({ "cloud", "clouds" }),
    &dg_desc_sky_outside_clouds ());
}

//-------------------------------------------------------------------

