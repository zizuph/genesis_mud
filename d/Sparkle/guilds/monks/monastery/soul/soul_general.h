/*******************************************************************\
| SOUL_GENERAL.H                                                    |
\*******************************************************************/

/*
 * 07/05/22 Arandir     Depose changed to impeach
 * 07/05/22 Arandir     Added safety catch on the depose command
 * 07/05/19 Arandir     Added the depose command
 * 05/05/07 Arandir     Minor changes to titles
 * 05/04/24 Arandir     Added titles
 * 03/09/09 Arandir     Created for the councillist and elderlist commands
 *
 */

// This file is included rather than inherited
// because LPC cannot handle diamond inheritance

//-------------------------------------------------------------------

#define M_IMPEACHMENT_DECIDE_DURATION   14

//-------------------------------------------------------------------

/*******************************************************************\
| Impeachment related functions                                     |
\*******************************************************************/

int m_action_impeach (string sArgs)
{
  object oWho = this_player ();
  string sName, sNameCap;
  string sVote;

  notify_fail ("Syntax: " + query_verb () + " <name>\n" +
               "  <name>             - the councillor to impeach\n");

  if (oWho->query_prop (M_PROP_TMP_I_SAFEGUARD) != query_verb ())
  {
    oWho->add_prop (M_PROP_TMP_I_SAFEGUARD, query_verb ());
    write ("Are you sure you want to start a vote to impeach a councillor ? " +
           "Type the command again to confirm.\n");
    return (TRUE);
  }

  sName = dg_remove_whitespace (sArgs);
  sNameCap = capitalize (sName);

  if (!m_is_council_member (sName)) return (FALSE);

  // We have everything, just cast the vote for the impeachment.

  sVote = sName + " impeachment";

  if (m_is_vote (sVote))
  {
    write ("The impeachment of " + sNameCap + " is already being considered.\n");
    return (TRUE);
  }

  m_add_vote (sVote,
              "Should " + sNameCap + " be impeached from the council ?",
              M_SPIRIT_UPPER,
              M_VOTE_MEMBERSONLY | M_VOTE_YESNOVOTES | M_VOTE_ANONYMOUS | M_VOTE_SECRET,
              M_IMPEACHMENT_DECIDE_DURATION,
              MASTER, "m_finish_vote_impeachment");

  M_OBJ_BOARD_MEMBER->m_post_note (
    "Council impeachment", M_SPIRIT_UPPER,
    dg_framed_text ("Impeachment of " + sNameCap + " from the council " +
                    "has been proposed. Be sure to voice your " +
                    "opinion by casting your ballot in " +
                    "the impeachment vote !" ));

  write ("A vote to impeach " + sNameCap + " has been started.\n");

  return (TRUE);
}

//-------------------------------------------------------------------

/*******************************************************************\
| Member list related functions                                     |
\*******************************************************************/

int m_action_councillist (string sArgs)
{
  object oHim = this_player ();
  string *asCouncils;

  asCouncils = dg_capitalize_array (m_get_council_members ());

  switch (sizeof (asCouncils))
  {
    case 0:
      write ("There are no elected councillors.\n");
      break;
    case 1:
      write ("The only elected councillor is " + asCouncils [0] + ".\n");
      break;
    default:
      write ("The elected councillors are " + COMPOSITE_WORDS (asCouncils) + ".\n");
      break;
  }

  return (TRUE);
}


int m_action_elderlist (string sArgs)
{
  object oHim = this_player ();
  string *asElders;

  asElders = dg_capitalize_array (m_get_elder_members ());

  switch (sizeof (asElders))
  {
    case 0:
      write ("There are no elected elders.\n");
      break;
    case 1:
      write ("The only elected elder is " + asElders [0] + ".\n");
      break;
    default:
      write ("The elected elders are " + COMPOSITE_WORDS (asElders) + ".\n");
      break;
  }

  return (TRUE);
}

//-------------------------------------------------------------------

/*******************************************************************\
| Title related functions                                           |
\*******************************************************************/

/*
 * Function name : m_advertise_titles
 * Description   : Advertise the monk titles.
 *   asTitles      ; The list of titles
 *   sAchievement  : Related achievement
 *   iAchievement  : Indication of prior achievement
 * Returns       : Indication of non empty list of titles
 *
 */

int m_advertise_titles (string *asTitles, string sAchievement, int iAchievement)
{
  if (sizeof (asTitles))
  {
    write ("Your " + sAchievement + (iAchievement ? " also " : " " ) +
           "entitles you to using " + COMPOSITE_WORDS (asTitles) + " as your base " +
           DG_AMOUNT_SWITCH (sizeof (asTitles), "title", "titles") + ".\n");
    return (TRUE);
  }
  else return (FALSE);
}


/*
 * Function name : m_action_title
 * Description   : Process the monk title command.
 *
 */

int m_action_title (string sArgs)
{
  object oHim = this_player ();
  int iRank;
  int iAggregate;
  string sAdj1, sBase1;
  string sAdj2, sBase2;
  string *asSpecific;
  string *asAggregate;
  string *asConfiguration;
  string sHelp;
  mixed  xResult;

  sHelp = "Syntax: " + query_verb () + " show | list | <adjective>, <base> [, <adjective>, <base>]\n" +
          "  <adjective>        - the adjective part to use\n" +
          "    none                 do not use any adjective\n" +
          "    ancient              use the adjective from the 'ancient' series\n" +
          "    hallowed             use the adjective from the 'hallowed' series\n" +
          "    resplendent          use the adjective from the 'resplendent' series\n" +
          "  <base>             - the base part to use\n" +
          "    monk                 use the base from the 'monk' series\n" +
          "    heart                use the base from the 'heart' series\n" +
          "    dancer               use the base from the 'dancer' series\n";

  sHelp += "Note: Your achievements determine what configurations of " +
           "the title and what special titles are allowed. " +
           "See help for details.\n";

  sHelp += "Example: " + query_verb () + " hallowed, monk, resplendent, dancer\n";

  notify_fail (sHelp);

  // Now that we prepared the help, let us parse the input.

  if (!strlen (sArgs)) return (FALSE);
  sArgs = dg_remove_whitespace (sArgs);

  if (sscanf (sArgs, "%s,%s,%s,%s", sAdj1, sBase1, sAdj2, sBase2) != 4)
  {
    if (sscanf (sArgs, "%s,%s", sAdj1, sBase1) != 2)
    {
      // Process commands that query title configuration

      if (sArgs == "show")
      {
        asConfiguration = m_get_title_configuration (oHim);
        if (strlen (asConfiguration [2] + asConfiguration [3]))
        {
          write ("Your title configuration is set to 'mtitle " +
                 asConfiguration [0] + ", " + lower_case (asConfiguration [1]) +
                 ", " +
                 asConfiguration [2] + ", " + lower_case (asConfiguration [3]) +
                 "', giving you the title " + m_get_title (oHim) + ".\n");
        }
        else
        {
          write ("Your title configuration is set to 'mtitle " +
                 asConfiguration [0] + ", " + lower_case (asConfiguration [1]) +
                 "', giving you the title " + m_get_title (oHim) + ".\n");
        }

        return (TRUE);
      }

      if (sArgs == "list")
      {
        iAggregate = FALSE;
        iRank = m_get_normalized_rank (oHim);

        if (iRank >= M_TITLE_SELECT_FEW)
        {
          asAggregate = ({ });
          asSpecific = m_get_title_rank_list (iRank);
          asAggregate += asSpecific;
          asSpecific = m_get_title_clergy_list (oHim, iRank);
          asAggregate += asSpecific;

          iAggregate |= m_advertise_titles (asAggregate, "guild rank", iAggregate);
        }

        asSpecific = m_get_title_stats_list (oHim);
        iAggregate |= m_advertise_titles (asSpecific, "guild stature", iAggregate);

        asAggregate = ({ });
        asSpecific = m_get_title_elder_list (oHim);
        asAggregate += asSpecific;
        asSpecific = m_get_title_council_list (oHim);
        asAggregate += asSpecific;
        iAggregate |= m_advertise_titles (asAggregate, "guild position", iAggregate);

        asSpecific = m_get_title_brotherhood_list (oHim, iRank);
        iAggregate |= m_advertise_titles (asSpecific, "guild rank", iAggregate);

        if (!iAggregate)
        {
          write ("Your achievements do not entitle you to any special title yet.\n");
        }

        return (TRUE);
      }

      return (FALSE);
    }

    sAdj2 = "";
    sBase2 = "";
  }

  // Process commands that set title configuration

  sAdj1 = dg_remove_whitespace (sAdj1);
  sBase1 = dg_remove_whitespace (sBase1);
  sAdj2 = dg_remove_whitespace (sAdj2);
  sBase2 = dg_remove_whitespace (sBase2);

  xResult = m_validate_title (oHim, sAdj1, sBase1, sAdj2, sBase2);
  if (stringp (xResult))
  {
    notify_fail (xResult);
    return (FALSE);
  }

  m_set_title_configuration (oHim, xResult [0], xResult [1], xResult [2], xResult [3]);
  write ("You set your title to " + m_get_title (oHim) + ".\n");

  return (TRUE);
}

//-------------------------------------------------------------------

/*******************************************************************\
| Vote finishing functions                                          |
\*******************************************************************/

void m_finish_vote_impeachment (string sName)
{
  string  sDescShort, sDescLong;
  string  sWho, sWhoCap;
  int     iResult;

  sscanf (sName, "%s impeachment", sWho);
  sWhoCap = capitalize (sWho);
  iResult = m_tally_decision (sName);

  if (iResult) m_remove_council_member (sWho);

  sDescShort = "The impeachment of " + sWhoCap + " has been " +
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

