/*******************************************************************\
| SOUL_COUNCIL.H                                                    |
\*******************************************************************/

/*
 * 07/12/04 Arandir     Punishment votes are now majority
 *                      Eldership votes are now majority
 * 05/04/23 Arandir     Moved titles to general
 * 04/08/17 Arandir     Few more council titles
 * 03/12/13 Arandir     Fixed parsing of arguments in elderadd and elderremove
 * 03/12/12 Arandir     Added logging of reprieval and elder votes
 * 03/12/02 Arandir     Tokens only work for council
 * 03/08/04 Arandir     Option to token oneself
 * 03/07/09 Arandir     Polished up and partially rewrote
 * 02/05/03 Arandir	Ported to new area without rewrite
 * 99/03/02 Cirion	Created
 *
 */

// This file is included rather than inherited
// because LPC cannot handle diamond inheritance

//-------------------------------------------------------------------

#define M_REPRIEVAL_DECIDE_DURATION     14
#define M_ELDER_DECIDE_DURATION         14

//-------------------------------------------------------------------

int m_location_to_int (string sLocation)
{
  switch (sLocation)
  {
    case "body"            : return (A_BODY);
    case "torso"           : return (A_TORSO);
    case "chest"           : return (A_CHEST);
    case "head"            : return (A_HEAD);
    case "neck"            : return (A_NECK);
    case "waist"           : return (A_WAIST);
    case "legs"            : return (A_LEGS);
    case "right arm"       : return (A_R_ARM);
    case "left arm"        : return (A_L_ARM);
    case "both arms"       : return (A_ARMS);
    case "either arm"      : return (A_ANY_ARM);
    case "right hand"      : return (A_R_HAND);
    case "left hand"       : return (A_L_HAND);
    case "both hands"      : return (A_HANDS);
    case "either hand"     : return (A_ANY_HAND);
    case "right finger"    : return (A_R_FINGER);
    case "left finger"     : return (A_L_FINGER);
    case "all fingers"     : return (A_FINGERS);
    case "any finger"      : return (A_ANY_FINGER);
    case "right foot"      : return (A_R_FOOT);
    case "left foot"       : return (A_L_FOOT);
    case "both feet"       : return (A_FEET);
    case "either foot"     : return (A_ANY_FOOT);
    case "right wrist"     : return (A_R_WRIST);
    case "left wrist"      : return (A_L_WRIST);
    case "both wrists"     : return (A_WRISTS);
    case "any wrist"       : return (A_ANY_WRIST);
    case "right ankle"     : return (A_R_ANKLE);
    case "left ankle"      : return (A_L_ANKLE);
    case "both ankles"     : return (A_ANKLES);
    case "any ankle"       : return (A_ANY_ANKLE);
    case "right ear"       : return (A_R_EAR);
    case "left ear"        : return (A_L_EAR);
    case "both ears"       : return (A_EARS);
    case "any ear"         : return (A_ANY_EAR);
    case "right hip"       : return (A_R_HIP);
    case "left hip"        : return (A_L_HIP);
    case "both hips"       : return (A_HIPS);
    case "either hip"      : return (A_ANY_HIP);
    case "right shoulder"  : return (A_R_SHOULDER);
    case "left shoulder"   : return (A_L_SHOULDER);
    case "both shoulders"  : return (A_SHOULDERS);
    case "either shoulder" : return (A_ANY_SHOULDER);
    case "eyebrow"         : return (A_BROW);
    case "eyes"            : return (A_EYES);
    case "back"            : return (A_BACK);
    default                : return (0);
  }
}

//-------------------------------------------------------------------

/*
 * Function name : m_action_elderadd
 *
 */

int m_action_elderadd (string sArgs)
{
  object oHim = this_player ();
  string sName, sNameCap;
  string sVote;

  // This command is reserved for the council.

  if (!m_is_council_member (oHim)) return (FALSE);

  notify_fail ("Syntax: " + query_verb () + " <name>\n" +
               "  <name>             - the monk to add as an elder\n");

  if (!strlen (sArgs)) return (FALSE);
  sName = dg_remove_whitespace (sArgs);
  sNameCap = capitalize (sName);

  // We have everything, just cast the vote for the addition.

  if (!m_is_monk (sName))
  {
    write (sNameCap + " is not a monk.\n");
    return (TRUE);
  }

  if (m_is_elder_member (sName))
  {
    write (sNameCap + " is already an elder.\n");
    return (TRUE);
  }

  sVote = "add elder " + sName;

  if (m_is_vote (sVote))
  {
    write ("The vote for adding " + sNameCap + " as an elder is already in progress.\n");
    return (TRUE);
  }

  m_add_vote (sVote,
              "Should " + sNameCap + " be added to the elders ?",
              dg_get_name (oHim),
              M_VOTE_COUNCILONLY | M_VOTE_YESNOVOTES | M_VOTE_MAJORITY,
              M_ELDER_DECIDE_DURATION,
              MASTER, "m_finish_vote_elderadd");
  write ("A vote to add " + sNameCap + " as an elder has been started.\n");

  return (TRUE);
}


/*
 * Function name : m_action_elderremove
 *
 */

int m_action_elderremove (string sArgs)
{
  object oHim = this_player ();
  string sName, sNameCap;
  string sVote;

  // This command is reserved for the council.

  if (!m_is_council_member (oHim)) return (FALSE);

  notify_fail ("Syntax: " + query_verb () + " <name>\n" +
               "  <name>             - the monk to remove as an elder\n");

  if (!strlen (sArgs)) return (FALSE);
  sName = dg_remove_whitespace (sArgs);
  sNameCap = capitalize (sName);

  // We have everything, just cast the vote for the removal.

  if (!m_is_elder_member (sName))
  {
    write (sNameCap + " is not an elder.\n");
    return (TRUE);
  }

  sVote = "remove elder " + sName;

  if (m_is_vote (sVote))
  {
    write ("The vote for removing " + sNameCap + " as an elder is already in progress.\n");
    return (TRUE);
  }

  m_add_vote (sVote,
              "Should " + sNameCap + " be removed from the elders ?",
              dg_get_name (oHim),
              M_VOTE_COUNCILONLY | M_VOTE_YESNOVOTES | M_VOTE_MAJORITY,
              M_ELDER_DECIDE_DURATION,
              MASTER, "m_finish_vote_elderremove");
  write ("A vote to remove " + sNameCap + " as an elder has been started.\n");

  return (TRUE);
}


/*
 * Function name : m_action_reprieve
 *
 */

int m_action_reprieve (string sArgs)
{
  object oHim = this_player ();
  string sName, sNameCap;
  string sPunishment;
  int    iPunishment;
  string sVote;

  // This command is reserved for the council.

  if (!m_is_council_member (oHim)) return (FALSE);

  notify_fail ("Syntax: " + query_verb () + " <name>, <punishment>\n" +
               "  <name>             - the monk to reprieve\n" +
               "  <punishment>       - the punishment to lift\n" +
               "    banish               must leave the guild\n" +
               "    disgrace             may not pray in the monastery\n" +
               "    exile                may not enter the monastery\n" +
               "    nobuy                may not buy in the monastery\n" +
               "    notrain              may not train skills\n" +
               "    novote               may not cast votes\n");

  // Now that we prepared the help, let us parse the input.

  if (!strlen (sArgs)) return (FALSE);
  if (sscanf (sArgs, "%s,%s", sName, sPunishment) != 2) return (FALSE);

  sName = dg_remove_whitespace (sName);
  sNameCap = capitalize (sName);
  sPunishment = dg_remove_whitespace (sPunishment);

  iPunishment = m_punishment_to_int (sPunishment);
  if (!iPunishment) return (FALSE);

  // We have everything, just cast the vote for the reprieval.

  if (!m_is_punished (sName, iPunishment))
  {
    write (sNameCap + " is not punished by the punishment " + sPunishment + ".\n");
    return (TRUE);
  }

  sVote = sName + " reprieval " + sPunishment;

  if (m_is_vote (sVote))
  {
    write ("The reprieval of the punishment " + sPunishment + " for " + sNameCap + " is already being considered.\n");
    return (TRUE);
  }

  m_add_vote (sVote,
              "Should " + sNameCap + " be reprieved of the punishment " + sPunishment + " ?",
              dg_get_name (oHim),
              M_VOTE_COUNCILONLY | M_VOTE_YESNOVOTES | M_VOTE_MAJORITY,
              M_REPRIEVAL_DECIDE_DURATION,
              MASTER, "m_finish_vote_reprieval");
  write ("A vote to reprieve " + sNameCap + " of the punishment " +
         sPunishment + " has been started.\n");

  return (TRUE);
}


/*
 * Function name : m_action_token
 *
 */

int m_action_token (string sArgs)
{
  object oWho = this_player ();
  string sWho = dg_get_name (oWho);
  object *aoWhom;
  object oWhom;
  string sWhom;
  object oToken;
  int    iResult;

  // This command is reserved for the council.

  if (!m_is_council_member (oWho)) return (FALSE);

  notify_fail ("Whom would you bestow your token upon ?\n");

  if (!strlen (sArgs)) return (FALSE);

  if ((sArgs == sWho) ||
      (sArgs == "me") ||
      (sArgs == "myself"))
  {
    DG_FIXUID;
    oToken = clone_object (M_PATH_OBJ + "/token");
    oToken->m_configure_token (sWho, sWho);
    iResult = oToken->move (oWho, MOVE_SUBLOC_ALWAYS);

    if (iResult)
    {
      write ("You fail to present yourself with " + LANG_ASHORT (oToken) + ".\n");
      oToken->remove_object ();
    }
    else
    {
      write ("You present yourself with " + LANG_ASHORT (oToken) + ".\n");
    }
  }
  else
  {
    aoWhom = parse_this (sArgs, "%l");
    if (sizeof (aoWhom) != 1) return (FALSE);
    oWhom = aoWhom [0];
    if (!oWhom) return (FALSE);
    sWhom = dg_get_name (oWhom);

    DG_FIXUID;
    oToken = clone_object (M_PATH_OBJ + "/token");
    oToken->m_configure_token (sWho, sWhom);
    iResult = oToken->move (oWhom, MOVE_SUBLOC_ALWAYS);

    if (iResult)
    {
      actor ("You fail to present", aoWhom, " with " + LANG_ASHORT (oToken) + ".");
      oToken->remove_object ();
    }
    else
    {
      actor ("You present", aoWhom, " with " + LANG_ASHORT (oToken) + ".");
      target (" presents you with " + LANG_ASHORT (oToken) + ".", aoWhom);
      all2actbb (" presents", aoWhom, " with " + LANG_ASHORT (oToken) + ".");
    }
  }

  return (TRUE);
}


/*
 * Function name : m_action_tokenadd
 *
 */

int m_action_tokenadd (string sArgs)
{
  object oHim = this_player ();
  string sHim = dg_get_name (oHim);
  string sLocation, sShortDesc, sLongDesc;
  int    iLocation;
  mixed  xResult;

  // This command is reserved for the council.

  if (!m_is_council_member (oHim)) return (FALSE);

  notify_fail ("Syntax: " + query_verb () + " <location>, <short desc>, <long desc>\n" +
               "  <location>         - the location of the token\n" +
               "  <short desc>       - a short description of the token\n" +
               "  <long desc>        - a long description of the token\n");

  // Now that we prepared the help, let us parse the input.

  if (!strlen (sArgs)) return (FALSE);
  if (sscanf (sArgs, "%s,%s,%s", sLocation, sShortDesc, sLongDesc) != 3) return (FALSE);

  sLocation = dg_remove_whitespace (sLocation);
  sShortDesc = dg_remove_whitespace (sShortDesc);
  sLongDesc = dg_remove_whitespace (sLongDesc);

  iLocation = m_location_to_int (sLocation);
  if (!iLocation) return (FALSE);

  // We have everything, just set the token.

  xResult = m_add_token (sHim, iLocation, sShortDesc, sLongDesc);
  if (stringp (xResult))
  {
    notify_fail (xResult);
    return (FALSE);
  }
  else
  {
    write ("The token has been created.\n");
    return (TRUE);
  }
}


/*
 * Function name : m_action_tokenremove
 *
 */

int m_action_tokenremove (string sArgs)
{
  object oHim = this_player ();
  string sHim = dg_get_name (oHim);
  mixed  xResult;

  // This command is reserved for the council.

  if (!m_is_council_member (oHim)) return (FALSE);

  xResult = m_remove_token (sHim);
  if (stringp (xResult))
  {
    notify_fail (xResult);
    return (FALSE);
  }
  else
  {
    write ("The token has been removed.\n");
    return (TRUE);
  }
}

//-------------------------------------------------------------------

/*******************************************************************\
| Vote finishing functions                                          |
\*******************************************************************/

void m_finish_vote_elderadd (string sName)
{
  string  sDescShort, sDescLong;
  string  sWho, sWhoCap;
  int     iResult;

  sscanf (sName, "add elder %s", sWho);
  sWhoCap = capitalize (sWho);
  iResult = m_tally_decision (sName);

  if (iResult) m_add_elder_member (sWho);

  sDescShort = "The addition of " + sWhoCap + " as an elder has been " +
               (iResult ? "accepted" : "rejected") + ".";
  sDescLong = sDescShort + "\n\n" +
              m_summarize_votes (sName) + "\n" +
              m_summarize_voters (sName) + "\n";

  s_log (M_LOG_WIZARD | M_LOG_COUNCIL, sDescShort);
  M_OBJ_BOARD_COUNCIL->m_post_note ("Add elder results: " + sWhoCap,
                                    "Ballot",
                                    dg_framed_text (sDescLong));
}


void m_finish_vote_elderremove (string sName)
{
  string  sDescShort, sDescLong;
  string  sWho, sWhoCap;
  int     iResult;

  sscanf (sName, "remove elder %s", sWho);
  sWhoCap = capitalize (sWho);
  iResult = m_tally_decision (sName);

  if (iResult) m_remove_elder_member (sWho);

  sDescShort = "The removal of " + sWhoCap + " as an elder has been " +
               (iResult ? "accepted" : "rejected") + ".";
  sDescLong = sDescShort + "\n\n" +
              m_summarize_votes (sName) + "\n" +
              m_summarize_voters (sName) + "\n";

  s_log (M_LOG_WIZARD | M_LOG_COUNCIL, sDescShort);
  M_OBJ_BOARD_COUNCIL->m_post_note ("Remove elder results: " + sWhoCap,
                                    "Ballot",
                                    dg_framed_text (sDescLong));
}


void m_finish_vote_reprieval (string sName)
{
  string  sDescShort, sDescLong;
  string  sWho, sWhoCap;
  string  sPunishment;
  int     iPunishment;
  int     iResult;

  sscanf (sName, "%s reprieval %s", sWho, sPunishment);
  sWhoCap = capitalize (sWho);
  iPunishment = m_punishment_to_int (sPunishment);
  iResult = m_tally_decision (sName);

  if (iResult) m_reprieve (sWho, iPunishment);

  sDescShort = "The reprieval of " + sWhoCap + " of the " +
               "punishment " + sPunishment + " has been " +
               (iResult ? "accepted" : "rejected") + ".";
  sDescLong = sDescShort + "\n\n" +
              m_summarize_votes (sName) + "\n" +
              m_summarize_voters (sName) + "\n";

  s_log (M_LOG_WIZARD | M_LOG_COUNCIL, sDescShort);
  M_OBJ_BOARD_COUNCIL->m_post_note ("Reprieval results: " + sWhoCap,
                                    "Ballot",
                                    dg_framed_text (sDescLong));
}

//-------------------------------------------------------------------

