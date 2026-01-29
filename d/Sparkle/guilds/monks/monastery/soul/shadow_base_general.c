/*******************************************************************\
| SHADOW_BASE_GENERAL.C                                             |
\*******************************************************************/

/*
 * 10/10/05 Lavellan    Recall doesn't clear received telioy log now
 * 07/12/09 Arandir     Mercade thinks this has to be renamed from H to C
 * 06/08/26 Arandir     Removed the focus skill
 * 04/08/18 Arandir     Mild changes for familiar support
 * 04/01/22 Arandir     Added fixing of damaged players
 * 03/10/21 Arandir     Added monitoring of council terms
 * 03/09/10 Arandir     Added support for recalling telioys
 * 03/08/10 Arandir     Copied off the base file
 *
 */

// This file is included rather than inherited
// because LPC cannot handle diamond inheritance

//-------------------------------------------------------------------

/*******************************************************************\
| Functions for managing communication                              |
\*******************************************************************/

static private mixed *axMonkTelioys = ({ });

/*
 * Function name : m_remember_telioy
 * Description   : Remembers a telioy.
 *
 */

void m_remember_telioy (string sFrom, string sText)
{
  int iCapacity;

  axMonkTelioys += ({ ({ sFrom, sText }) });

  // The capacity of the list is limited by the monk intelligence.

  iCapacity = shadow_who->query_base_stat (SS_INT) / 11;
  if (sizeof (axMonkTelioys) > iCapacity)
  {
    axMonkTelioys = axMonkTelioys [sizeof (axMonkTelioys) - iCapacity ..];
  }
}


/*
 * Function name : m_recall_telioys
 * Description   : Recalls the telioys
 *
 */

mixed *m_recall_telioys ()
{
  /*mixed *axTelioys = axMonkTelioys;
  axMonkTelioys = ({ });
  return (axTelioys);*/
  return (axMonkTelioys);
}

//-------------------------------------------------------------------

/*******************************************************************\
| Functions related to guild membership                             |
\*******************************************************************/

/*
 * Function name : query_guild_skill_name
 * Description   : Return the name of any special guild skills.
 *
 */

mixed query_guild_skill_name (int iType)
{
  switch (iType)
  {
    case M_SKILL_STRIKE: return ("strike");
    case M_SKILL_PLEXUS: return ("plexus");
    default:             return (shadow_who->query_guild_skill_name (iType));
  }
}


/*
 * Function name : m_query_shadow
 * Description   : A simple way of obtaining this shadow
 *
 */

object m_query_shadow ()
{
  return (this_object ());
}


/*
 * Function name : query_guild_keep_player
 * Description   : Check to see if we keep the player or not. Since we do
 *                 quite a bit of additional bookkeeping, we handle this
 *                 in the m_login function of the shadow.
 *
 */

int query_guild_keep_player (object oWho)
{
  return (TRUE);
}


/*
 * Function name : query_def_post
 * Description   : Returns the name of the default post office for this player.
 *
 */

string query_def_post ()
{
  return (M_PATH_ROOM + "/member_post");
}

//-------------------------------------------------------------------

/*
 * Function name : m_shadow_general_init
 * Description   : Called shortly one second after the player logs in.
 *                 Does a lot of sanity checks besides initialization.
 * Returns       : Zero as an indication of success or error message.
 *
 */

mixed m_shadow_general_init ()
{
  string sWho = dg_get_name (shadow_who);
  string sWhoCap = capitalize (sWho);
  string sText;

  // Sanity check for dead people ...

  if (!living (shadow_who))
  {
    return (sWhoCap + " logged in with the shadow but was not living.");
  }

  // Players have to be in the guild list ...

  if (interactive (shadow_who) &&
      !m_is_monk (shadow_who))
  {
    shadow_who->remove_autoshadow (this_object ());
    return (sWhoCap + " logged in with the shadow but was not a member.");
  }

  // Fix damaged players ...

  m_fix (shadow_who);

  // Add the command soul ...

  shadow_who->add_cmdsoul (M_SOUL);
  shadow_who->update_hooks ();

  // Handle the support for member banishment.

  if (m_is_punished (shadow_who, M_PUNISH_BANISH))
  {
    shadow_who->catch_tell (dg_framed_text ("You have been banished from the Order."));
    s_log (M_LOG_WIZARD | M_LOG_COUNCIL, sWhoCap + " was removed because of banishment.");
    set_alarm (1.0, 0.0, &m_remove_monk (shadow_who));
  }

  // Handle the support for council terms.

  if (m_get_council_term (shadow_who) < 0)
  {
    shadow_who->catch_tell (dg_framed_text (
      "Your council term has expired. Please make the " +
      "necessary arangements and resign to start the " +
      "new election."));
  }

  return (FALSE);
}

//-------------------------------------------------------------------

