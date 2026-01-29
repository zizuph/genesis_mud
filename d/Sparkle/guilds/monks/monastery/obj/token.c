/*******************************************************************\
| TOKEN.C                                                           |
\*******************************************************************/

/*
 * 99/03/02 Cirion      Created
 * 01/09/17 Manat       Removed dependency on monklib
 * 02/06/02 Manat       Reading information from a file
 * 02/06/13 Manat       Functions for setting location and saving
 * 03/07/09 Arandir     Rewrote to use the monk guild data holder
 * 04/08/27 Arandir     Added fixing of UID and EUID in constructor
 *
 */

#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>

#include "../defs.h"

inherit "/std/object";
inherit "/lib/wearable_item";

inherit M_TOKEN_LIBS;

//-------------------------------------------------------------------

private static string sGiver;
private static string sPossessor;

//-------------------------------------------------------------------

void m_configure_token (string sArgGiver, string sArgPossessor)
{
  string sGiverCap;
  string sPossessorCap;
  int    iLocation;
  string *asShortDesc;
  string sShortDesc;
  string sLongDesc;
  int    iAdjective;

  sGiver = sArgGiver;
  sGiverCap = capitalize (sGiver);
  sPossessor = sArgPossessor;
  sPossessorCap = capitalize (sPossessor);

  add_prop (OBJ_S_WIZINFO,
            "This object is a trinket that a monk council member may " +
            "create and bestow upon others as a token of recognition. " +
            "Any abuse should be reported to the monk guildmaster.\n");

  iLocation = m_get_token_location (sGiver);
  if (iLocation)
  {
    sShortDesc = m_get_token_desc_short (sGiver);
    asShortDesc = explode (sShortDesc, " ");
    for (iAdjective = 0 ; iAdjective < sizeof (asShortDesc) - 1 ; iAdjective ++)
    {
      add_adj (asShortDesc [iAdjective]);
    }
    set_name (asShortDesc [iAdjective]);
    add_name ("token");

    sLongDesc = m_get_token_desc_long (sGiver);
    set_long (sLongDesc + "\n" +
              "This token was bestowed upon " +
              sPossessorCap + " by " + sGiverCap + ".\n");

    config_wearable_item (iLocation, 1, 1, this_object ());
  }
  else
  {
    set_name ("token");
    set_short ("damaged token");
    set_long ("A damaged token.\n");

    config_wearable_item (0, 1, 1, this_object ());

    set_alarm (1.0, 0.0, remove_object);
  }
}

//-------------------------------------------------------------------

void create_object ()
{
  string sMessage;

  // Fixing the UID and EUID is needed when this happens
  // to be the very first monk object loaded, because then
  // it needs to load the guild server as it queries various
  // guild functions.

  DG_FIXUID;

  // This is really just a guess but as good as any ...

  add_prop (OBJ_I_VALUE, 0);
  add_prop (OBJ_I_WEIGHT, 750);
  add_prop (OBJ_I_VOLUME, 750);

  sMessage = "You would not want to leave it lying around. " +
             "You can <destroy> it if you no longer want it.\n";
  add_prop (OBJ_M_NO_DROP, sMessage);
  add_prop (OBJ_M_NO_SELL, sMessage);
  add_prop (OBJ_M_NO_STEAL, "The token seems to resist your grasp.\n");
}

//-------------------------------------------------------------------

void leave_env (object oFrom, object oTo)
{
  wearable_item_leave_env (oFrom, oTo);
  ::leave_env (oFrom, oTo);
}


void appraise_object (int iNumber)
{
  ::appraise_object (iNumber);
  appraise_wearable_item ();
}

//-------------------------------------------------------------------

/*
 * Function name : query_auto_load
 * Description   : Saves the giver and the possessor of the token.
 *
 */

string query_auto_load ()
{
  return (MASTER + ":" + sGiver + ":" + sPossessor);
}


/*
 * Function name : init_arg
 * Description   : Restores the giver and the possessor of the token.
 *
 */

void init_arg (string sArgs)
{
  string sLocGiver = "";
  string sLocPossessor = "";

  sscanf (sArgs, "%s:%s", sLocGiver, sLocPossessor);

  m_configure_token (sLocGiver, sLocPossessor);
}

//-------------------------------------------------------------------

int m_action_destroy (string sArgs)
{
  notify_fail ("Destroy what, " + LANG_THESHORT (this_object ()) + " ?\n");

  if (!strlen (sArgs)) return (FALSE);
  if (sArgs != short ()) return (FALSE);

  write ("You destroy " + LANG_THESHORT (this_object ()) + ".\n");
  set_alarm (1.0, 0.0, &remove_object ());

  return (TRUE);
}


void init ()
{
  ::init ();

  add_action (m_action_destroy, "destroy");
}

//-------------------------------------------------------------------

