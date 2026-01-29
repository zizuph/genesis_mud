/*******************************************************************\
| SOUL_ELDER.H                                                      |
\*******************************************************************/

/*
 * 07/12/04 Arandir     Punishment votes are now majority
 * 03/12/12 Arandir     Added logging of punishment vote
 *          Arandir     Added safeguard to resign command
 * 03/12/09 Arandir     Fixed bug with applying punishments
 * 03/09/09 Arandir     Moved the elderlist command
 * 03/07/08 Arandir     Created
 *
 */

// This file is included rather than inherited
// because LPC cannot handle diamond inheritance

//-------------------------------------------------------------------

#define M_PUNISHMENT_DECIDE_DURATION    14

//-------------------------------------------------------------------

int m_punishment_to_int (string sPunishment)
{
  switch (sPunishment)
  {
    case "banish"   : return (M_PUNISH_BANISH);
    case "disgrace" : return (M_PUNISH_DISGRACE);
    case "exile"    : return (M_PUNISH_EXILE);
    case "nobuy"    : return (M_PUNISH_NOBUY);
    case "notrain"  : return (M_PUNISH_NOTRAIN);
    case "novote"   : return (M_PUNISH_NOVOTE);
    default         : return (0);
  }
}


string m_punishment_to_str (int iPunishment)
{
  string *asPunishments = ({ });

  if (iPunishment & M_PUNISH_BANISH)   asPunishments += ({ "banish" });
  if (iPunishment & M_PUNISH_DISGRACE) asPunishments += ({ "disgrace" });
  if (iPunishment & M_PUNISH_EXILE)    asPunishments += ({ "exile" });
  if (iPunishment & M_PUNISH_NOBUY)    asPunishments += ({ "nobuy" });
  if (iPunishment & M_PUNISH_NOTRAIN)  asPunishments += ({ "notrain" });
  if (iPunishment & M_PUNISH_NOVOTE)   asPunishments += ({ "novote" });

  return (COMPOSITE_WORDS (asPunishments));
}

//-------------------------------------------------------------------

int m_action_punish (string sArgs)
{
  object oHim = this_player ();
  string sName, sNameCap;
  string sPunishment;
  int    iPunishment;
  string sVote;

  // This command is reserved for the elders and the council.

  if (!m_is_elder_member (oHim) && !m_is_council_member (oHim)) return (FALSE);

  notify_fail ("Syntax: " + query_verb () + " <name>, <punishment>\n" +
               "  <name>             - the monk to punish\n" +
               "  <punishment>       - the punishment to use\n" +
               "    banish               must leave the guild\n" +
               "    disgrace             may not pray in the monastery\n" +
               "    exile                may not enter the monastery\n" +
               "    nobuy                may not buy in the monastery\n" +
               "    notrain              may not train skills\n" +
               "    novote               may not cast votes\n");

  if (!strlen (sArgs)) return (FALSE);
  if (sscanf (sArgs, "%s,%s", sName, sPunishment) != 2) return (FALSE);

  sName = dg_remove_whitespace (sName);
  sNameCap = capitalize (sName);
  sPunishment = dg_remove_whitespace (sPunishment);

  iPunishment = m_punishment_to_int (sPunishment);
  if (!iPunishment) return (FALSE);

  // We have everything, just cast the vote for the punishment.

  if (m_is_punished (sName, iPunishment))
  {
    write (sNameCap + " is already punished by the punishment " + sPunishment + ".\n");
    return (TRUE);
  }

  sVote = sName + " punishment " + sPunishment;

  if (m_is_vote (sVote))
  {
    write ("The punishment " + sPunishment + " for " + sNameCap + " is already being considered.\n");
    return (TRUE);
  }

  m_add_vote (sVote,
              "Should " + sNameCap + " be punished by the punishment " + sPunishment + " ?",
              dg_get_name (oHim),
              M_VOTE_COUNCILONLY | M_VOTE_YESNOVOTES | M_VOTE_MAJORITY,
              M_PUNISHMENT_DECIDE_DURATION,
              MASTER, "m_finish_vote_punishment");
  write ("A vote to punish " + sNameCap + " by the punishment " +
         sPunishment + " has been started.\n");

  return (TRUE);
}


int m_action_punishlist (string sArgs)
{
  object oHim = this_player ();
  string *asPunished;
  string sPunished;
  int    iPunished;

  // This command is reserved for the elders and the council.

  if (!m_is_elder_member (oHim) && !m_is_council_member (oHim)) return (FALSE);

  asPunished = m_get_punished ();

  if (sizeof (asPunished))
  {
    for (iPunished = 0 ; iPunished < sizeof (asPunished) ; iPunished ++)
    {
      sPunished = asPunished [iPunished];
      write (capitalize (sPunished) + " has been punished by the punishment " +
             m_punishment_to_str (m_get_punishment (sPunished)) + ".\n");
    }
  }
  else
  {
    write ("No punishments are meted out at the moment.\n");
  }

  return (TRUE);
}


int m_action_resign (string sArgs)
{
  object oWho = this_player ();

  notify_fail ("Syntax: " + query_verb () + " elder | council\n");

  if (oWho->query_prop (M_PROP_TMP_I_SAFEGUARD) != query_verb ())
  {
    oWho->add_prop (M_PROP_TMP_I_SAFEGUARD, query_verb ());
    write ("Are you sure you want to resign ? " +
           "Type the command again to confirm.\n");
    return (TRUE);
  }

  switch (sArgs)
  {
    case "elder":
      if (m_is_elder_member (oWho))
      {
        m_remove_elder_member (oWho);
        write ("You have been removed as an elder member.\n");
      }
      else
      {
        write ("You are not an elder member.\n");
      }
      break;

    case "council":
      if (m_is_council_member (oWho))
      {
        m_remove_council_member (oWho);
        write ("You have been removed as a council member.\n");
      }
      else
      {
        write ("You are not a council member.\n");
      }
      break;

    default:
      return (FALSE);
  }

  return (TRUE);
}

//-------------------------------------------------------------------

/*******************************************************************\
| Vote finishing functions                                          |
\*******************************************************************/

void m_finish_vote_punishment (string sName)
{
  string  sDescShort, sDescLong;
  string  sWho, sWhoCap;
  string  sPunishment;
  int     iPunishment;
  int     iResult;

  sscanf (sName, "%s punishment %s", sWho, sPunishment);
  sWhoCap = capitalize (sWho);
  iPunishment = m_punishment_to_int (sPunishment);
  iResult = m_tally_decision (sName);

  if (iResult) m_punish (sWho, iPunishment);

  sDescShort = "The punishment of " + sWhoCap + " by the " +
               "punishment " + sPunishment + " has been " +
               (iResult ? "accepted" : "rejected") + ".";
  sDescLong = sDescShort + "\n\n" +
              m_summarize_votes (sName) + "\n" +
              m_summarize_voters (sName) + "\n";

  s_log (M_LOG_WIZARD | M_LOG_COUNCIL, sDescShort);
  M_OBJ_BOARD_COUNCIL->m_post_note ("Punishment results: " + sWhoCap,
                                    "Ballot",
                                    dg_framed_text (sDescLong));
}

//-------------------------------------------------------------------

