/*******************************************************************\
| LIBS_PLAYER.C                                                     |
\*******************************************************************/

/*
 * 06/09/02 Arandir     Extended the list of races that are humanoid
 * 03/12/11 Arandir     Changed m_get_pretty_description to omit article
 * 03/07/28 Arandir     Fixed m_get_present_living_str in empty room
 * 03/07/24 Arandir     Added support for querying constitution
 * 03/07/06 Arandir     Ported and bugfixed hitloc querying code
 * 03/07/01 Arandir     Ported and bugfixed the support for emotes
 * 03/06/24 Arandir     Ported the pretty description support
 * 03/04/02 Arandir     Added some trivial functions
 * 02/02/01 Arandir	Created
 *
 */

//-------------------------------------------------------------------

#include <std.h>
#include <files.h>
#include <macros.h>
#include <language.h>
#include <composite.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include </std/combat/combat.h>

#include "../defs.h"

//-------------------------------------------------------------------

/*******************************************************************\
| Functions related to names and descriptions                       |
\*******************************************************************/

/*
 * Function name : dg_get_name
 *
 */

varargs string dg_get_name (object oWho = this_player ())
{
  return (lower_case (oWho->query_real_name ()));
}


/*
 * Function name : dg_get_nonmet_name
 *
 */

varargs string dg_get_nonmet_name (object oWho = this_player ())
{
  return (lower_case (oWho->query_nonmet_name ()));
}


/*
 * Function name : dg_get_pretty_description
 * Description   : Returns a pretty description of a living
 *
 */

string dg_get_pretty_description (object oWho)
{
  string sDesc;
  string sHair = "";
  string sEyes = "";
  int    iHasExtra = FALSE;

  sDesc = oWho->query_nonmet_name ();

  // Augment the description with hair as per
  // /d/Calia/gelan/specials/hair_shadow if
  // there is no mention of the hair yet

  if (!wildmatch ("*hair*", sDesc))
  {
    sHair = oWho->query_hair_style ();
    if (strlen (sHair) > 0)
    {
      sDesc += " with ";
      if (wildmatch ("* *", sHair))
      {
        sDesc += oWho->query_hair_length ();
      }
      else
      {
        sDesc += sHair;
      }
      sDesc += " hair";
      iHasExtra = TRUE;
    }
  }

  // Augment the description with eyes as per
  // /d/Calia/gelan/specials/eyes_shadow if
  // there is no mention of the eyes yet

  if (!(wildmatch ("*eye*", sDesc)))
  {
    sEyes = oWho->query_eyes_colour ();
    if (strlen (sEyes) > 0)
    {
      if (iHasExtra) sDesc += " and ";
                else sDesc += " with ";
      sDesc += oWho->query_eyes_type () + " " + sEyes + " eyes";
      iHasExtra = TRUE;
    }
  }

  return (sDesc);
}

//-------------------------------------------------------------------

/*******************************************************************\
| Functions related to state                                        |
\*******************************************************************/

/*
 * Function name : dg_is_hidden
 *
 */

int dg_is_hidden (object oWho)
{
  return (oWho->query_prop (OBJ_I_HIDE) > 0);
}

/*
 * Function name : dg_is_invisible
 *
 */

int dg_is_invisible (object oWho)
{
  return (oWho->query_prop (OBJ_I_INVIS) > 0);
}

//-------------------------------------------------------------------

/*******************************************************************\
| Functions related to position                                     |
\*******************************************************************/

/*
 * Function name : dg_is_player
 *
 */

int dg_is_player (mixed xWho)
{
  string sWho = objectp (xWho) ? dg_get_name (xWho) : xWho;
  return (SECURITY->exist_player (sWho));
}

/*
 * Function name : dg_is_junior
 *
 */

int dg_is_junior (mixed xWho)
{
  string sWho = objectp (xWho) ? dg_get_name (xWho) : xWho;
  return (wildmatch ("*jr", sWho));
}

/*
 * Function name : dg_is_wizard
 *
 */

varargs int dg_is_wizard (mixed xWho, int iLevel = WIZ_APPRENTICE)
{
  string sWho = objectp (xWho) ? dg_get_name (xWho) : xWho;
  return (SECURITY->query_wiz_level (sWho) >= iLevel);
}

//-------------------------------------------------------------------

/*******************************************************************\
| Functions related to constitution                                 |
\*******************************************************************/

/*
 * Function name : dg_is_dragon
 *
 */

int dg_is_dragon (object oWho)
{
  string sRace = oWho->query_race_name ();
  return ((sRace == "dragon") ||
          (sRace == "drake"));
}


/*
 * Function name : dg_is_humanoid
 * Description   : A more reliable function to detect whom we can
 *                 consider of human shape, for certain monsters
 *                 do not inherit the proper class even though
 *                 they are decidedly humanoid in nature.
 *
 */

int dg_is_humanoid (object oWho)
{
  if (oWho->query_humanoid ()) return (TRUE);
  return (member_array (oWho->query_race (),
                        ({ "troll", "yeti" })) >= 0);
}

//-------------------------------------------------------------------

/*******************************************************************\
| Functions related to presence                                     |
\*******************************************************************/

/*
 * Function name : dg_get_present_livings
 *
 */

object *dg_get_present_livings ()
{
  object *oLivings;
  object oRoom;

  // This is a bit tricky, because we do not know whether this
  // function was inherited into a room or into an object in
  // a room.

  oRoom = environment ();
  if (!oRoom) oRoom = this_object ();

  oLivings = filter (all_inventory (oRoom), living);

  return (oLivings);
}

/*
 * Function name : dg_get_present_living_obj
 *
 */

object dg_get_present_living_obj ()
{
  object *oLivings;

  oLivings = dg_get_present_livings ();
  if (sizeof (oLivings)) return (one_of_list (oLivings));
                    else return (NULL);
}

/*
 * Function name : dg_get_present_living_str ()
 *
 */

string dg_get_present_living_str ()
{
  object oLiving = dg_get_present_living_obj ();
  if (objectp (oLiving)) return (OB_NAME (oLiving));
                    else return ("");
}

//-------------------------------------------------------------------

/*******************************************************************\
| Support for combat                                                |
\*******************************************************************/

/*
 * Function name : dg_get_hitlocs
 *
 */

string *dg_get_hitlocs (object oWho)
{
  object oCombat;
  int    *aiHitlocs;
  string *asHitlocs;
  mixed  *axHitloc;
  int    iHitloc;

  oCombat = oWho->query_combat_object ();
  if (!oCombat) return (({ "somewhere" }));

  aiHitlocs = oCombat->query_hitloc_id ();
  if (!sizeof (aiHitlocs)) return (({ "somewhere" }));

  asHitlocs = ({ });

  for (iHitloc = 0 ; iHitloc < sizeof (aiHitlocs) ; iHitloc ++)
  {
    axHitloc = oCombat->query_hitloc (aiHitlocs [iHitloc]);
    if (sizeof (axHitloc) >= HIT_M_AC)
    {
      asHitlocs += ({ axHitloc [HIT_DESC] });
    }
  }

  if (!sizeof (asHitlocs)) return (({ "somewhere" }));

  return (asHitlocs);
}


/*
 * Function name : dg_get_hitloc_id
 *
 */

int dg_get_hitloc_id (object oWho, string sWhere)
{
  object oCombat;
  int    *aiHitlocs;
  mixed  *axHitloc;
  int    iHitloc;

  oCombat = oWho->query_combat_object ();
  if (!oCombat) return (HITLOC_ANY);

  aiHitlocs = oCombat->query_hitloc_id ();
  if (!sizeof (aiHitlocs)) return (HITLOC_ANY);

  for (iHitloc = 0 ; iHitloc < sizeof (aiHitlocs) ; iHitloc ++)
  {
    axHitloc = oCombat->query_hitloc (aiHitlocs [iHitloc]);
    if (sizeof (axHitloc) > HIT_M_AC)
    {
      if (axHitloc [HIT_DESC] == sWhere)
      {
        return (aiHitlocs [iHitloc]);
      }
    }
  }

  return (HITLOC_ANY);
}

//-------------------------------------------------------------------

/*******************************************************************\
| Support for emotes                                                |
\*******************************************************************/

/*
 * Function name : m_map_descriptions
 *
 */

string *m_map_descriptions (object oWho, object *aoList)
{
  string *asResult = ({ });
  object oItem;
  int    iItem;

  for (iItem = 0 ; iItem < sizeof (aoList) ; iItem ++)
  {
    oItem = aoList [iItem];
    if (oItem == oWho)
    {
      asResult += ({ "you" });
    }
    else if (living (oItem))
    {
      asResult += ({ XTNAME (oWho, oItem) });
    }
    else
    {
      asResult += ({ LANG_THESHORT (oItem) });
    }
  }

  return (asResult);
}


/*
 * Function name : target2actbb
 * Description   : Prints a message for a target of an emote. The
 *                 difference between this and the library functions
 *                 is that this supports primary and secondary targets.
 * Example       : target2actbb (" holds his hand up towards ", primary,
 *                               " and beckons you to listen", " to ",
 *                               secondary);
 *
 *                  Fatty holds his hand up towards you and beckons you to
 *                    listen to the darkly robed human wizard.
 *                  Fatty holds his hand up towards you and beckons you to
 *                    listen.
 *
 */

varargs void target2actbb (
  string sFirst, object *aoPrimary,
  string sSecond, string sThird = "",
  object *aoSecondary = ({ }),
  string sFourth = "",
  string sAdverb = "",
  int iAttribs = 0)
{
  object oWho = this_player ();
  object *aoMonsters, *aoPlayers;
  object oPlayer;
  object *aoSeeingPrimary;
  object *aoLocalPrimary;
  object *aoLocalSecondary;
  int    iTarget;

  // Only consider those targets that can see the actor.

  aoSeeingPrimary = FILTER_CAN_SEE_IN_ROOM (aoPrimary);
  aoSeeingPrimary = FILTER_IS_SEEN (oWho, aoSeeingPrimary);

  // Separate the players from the monsters. The monsters need
  // not see the emotes, just have the hook called to know.

  aoPlayers = FILTER_PLAYERS (aoSeeingPrimary);
  aoMonsters = aoSeeingPrimary - aoPlayers;

  // Optimize for a situation when no secondary targets are
  // present, for then we can simply use catch_msg.

  if (sizeof (aoSecondary))
  {
    for (iTarget = 0 ; iTarget < sizeof (aoPlayers) ; iTarget ++)
    {
      oPlayer = aoPlayers [iTarget];
      aoLocalPrimary = FILTER_CAN_SEE (aoSeeingPrimary, oPlayer);
      aoLocalSecondary = FILTER_CAN_SEE (aoSecondary, oPlayer);
      oPlayer->catch_tell (XCTNAME (oWho, oPlayer) + sFirst +
                           COMPOSITE_WORDS (m_map_descriptions (oPlayer, aoLocalPrimary)) +
                           sSecond +
                           (sizeof (aoLocalSecondary)
                             ? sThird +
                               COMPOSITE_WORDS (m_map_descriptions (oPlayer, aoLocalSecondary)) +
                               sFourth
                             : ".")
                           + "\n");
    }
  }
  else
  {
    aoPlayers->catch_msg (QCTNAME (oWho) + sFirst + ".\n");
  }

  aoMonsters->emote_hook (query_verb(), oWho, sAdverb, aoSeeingPrimary, iAttribs, TRUE);
}

//-------------------------------------------------------------------

