/*******************************************************************\
| LIBS_VOTING.C                                                     |
\*******************************************************************/

/*
 * 07/05/19 Arandir     Support for majority decision votes
 *                      Merged with extraneous include
 * 07/05/18 Arandir     Support for infinite duration votes
 *                      Got rid of useless vote start time
 * 06/09/06 Arandir     Fixed a typo
 *                      Few more cosmetic fixes
 * 03/11/07 Arandir     Fixed an incorrect use of mappings
 * 03/06/23 Arandir     Council and elder votes now also close
 *                      when all authorized voters have voted
 * 03/06/13 Arandir     Revamped to cooperate with a data holder
 * 02/02/09 Arandir	Created
 *
 */

#include <time.h>
#include <macros.h>
#include <language.h>
#include <composite.h>

#include "../defs.h"

inherit DG_MISC_LIBS;
inherit DG_TEXT_LIBS;
inherit M_PLAYER_LIBS;

//-------------------------------------------------------------------

// Data file definitions

#define M_ACCESS_MONK_VOTES             mapping mMonkVotes = M_MONK_SRVR->m_get_monk_votes ()
#define M_DELETE_MONK_VOTES(sKey)       mMonkVotes = M_MONK_SRVR->m_delete_monk_votes (sKey)

#define M_SAVE_ACCESSED                 M_MONK_SRVR->m_save_object ()


#define M_VOTES_DESC                    0
#define M_VOTES_OWNER                   1
#define M_VOTES_FLAGS                   2
#define M_VOTES_VOTES                   3
#define M_VOTES_FINISH_TIME             4
#define M_VOTES_FINISH_FILE             5
#define M_VOTES_FINISH_FUNCTION         6

//-------------------------------------------------------------------

#define M_VOTE_MAX_NAME_LEN             37

#define M_VOTE_MIN_DURATION             1
#define M_VOTE_MAX_DURATION             100


mapping m_tally_votes (string sName);

//-------------------------------------------------------------------

/*******************************************************************\
| Basic vote manipulation functions                                 |
\*******************************************************************/

/*
 * Function name : m_is_vote
 *
 */

int m_is_vote (string sName)
{
  M_ACCESS_MONK_VOTES;

  return (member_array (sName, m_indices (mMonkVotes)) >= 0);
}


/*
 * Function name : m_is_closed_vote
 *
 */

int m_is_closed_vote (string sName)
{
  M_ACCESS_MONK_VOTES;

  mixed   *axVote;
  int     iVoters;
  int     iFlags;

  if (member_array (sName, m_indices (mMonkVotes)) >= 0)
  {
    axVote = mMonkVotes [sName];

    // The simplest condition to test is the end time

    if ((axVote [M_VOTES_FINISH_TIME] > 0) &&
        (axVote [M_VOTES_FINISH_TIME] < time ())) return (TRUE);

    // If the end time has not been reached yet,
    // check the number of authorized voters ...

    iFlags = axVote [M_VOTES_FLAGS];

    if ((iFlags & M_VOTE_COUNCILONLY) && (iFlags & M_VOTE_ELDERSONLY))
    {
      // The lists of councillors and elders might overlap ...
      string *asCouncil = m_get_council_members ();
      string *asElders = m_get_elder_members ();
      string *asBoth = (asCouncil - asElders) + asElders;
      iVoters = sizeof (asBoth);
    }
    else if (iFlags & M_VOTE_COUNCILONLY)
    {
      iVoters = sizeof (m_get_active_council_members ());
    }
    else if (iFlags & M_VOTE_ELDERSONLY)
    {
      iVoters = sizeof (m_get_elder_members ());
    }
    else if (iFlags & M_VOTE_MEMBERSONLY)
    {
      iVoters = sizeof (m_get_monks ());
    }
    else return (FALSE);

    // For majority votes, it is enough when there is a vote
    // with more than half of the authorized voters ...

    if (iFlags & M_VOTE_MAJORITY)
    {
      mapping mTally = m_tally_votes (sName);
      if (m_sizeof (mTally) > 0)
      {
        int *aiCounts = sort_array (m_indexes (mTally), &dg_sort_int_descending ());
        int iCount = aiCounts [0];

        if (sizeof (mTally [iCount]) == 1)
        {
          return (iCount > iVoters / 2);
        }
      }
      return (FALSE);
    }

    // For other votes, it is enough when all
    // the authorized voters have voted ...

    return (m_sizeof (axVote [M_VOTES_VOTES]) == iVoters);
  }
  return (FALSE);
}


/*
 * Function name : m_is_past_voter
 *
 */

int m_is_past_voter (mixed xWho, string sName)
{
  M_ACCESS_MONK_VOTES;

  string sWho = objectp (xWho) ? dg_get_name (xWho) : xWho;

  if (member_array (sName, m_indices (mMonkVotes)) >= 0)
  {
    return (member_array (sWho, m_indices (mMonkVotes [sName][M_VOTES_VOTES])) >= 0);
  }
  else return (FALSE);
}


/*
 * Function name : m_is_authorized_voter
 *
 */

int m_is_authorized_voter (mixed xWho, string sName)
{
  M_ACCESS_MONK_VOTES;

  int     iFlags;

  if (member_array (sName, m_indices (mMonkVotes)) >= 0)
  {
    if (m_is_closed_vote (sName)) return (FALSE);

    iFlags = mMonkVotes [sName][M_VOTES_FLAGS];
    if ((iFlags & M_VOTE_COUNCILONLY) &&
        (iFlags & M_VOTE_ELDERSONLY))
    {
      // In an attempt at flexibility, a combination of the
      // M_VOTE_COUNCILONLY and M_VOTE_ELDERSONLY flags
      // works as a logical OR.

      return (m_is_council_member (xWho) || m_is_elder_member (xWho));
    }
    else if (iFlags & M_VOTE_COUNCILONLY) return (m_is_council_member (xWho));
    else if (iFlags & M_VOTE_ELDERSONLY)  return (m_is_elder_member (xWho));
    else if (iFlags & M_VOTE_MEMBERSONLY) return (m_is_monk (xWho));
    else                                  return (TRUE);
  }
  else return (FALSE);
}


/*
 * Function name : m_is_supervisor_voter
 *
 */

int m_is_supervisor_voter (mixed xWho, string sName)
{
  M_ACCESS_MONK_VOTES;

  string sWho = objectp (xWho) ? dg_get_name (xWho) : xWho;

  if (member_array (sName, m_indices (mMonkVotes)) >= 0)
  {
    return (mMonkVotes [sName][M_VOTES_OWNER] == sWho);
  }
  else return (FALSE);
}


/*
 * Function name : m_get_total_vote_count
 *
 */

int m_get_total_vote_count (mixed xWho)
{
  M_ACCESS_MONK_VOTES;

  string  *asVotes;
  int     iCount;

  asVotes = m_indices (mMonkVotes);

  iCount = 0;
  foreach (string sVote : asVotes)
  {
    if (m_is_authorized_voter (xWho, sVote))
    {
      iCount ++;
    }
  }
  return (iCount);
}


/*
 * Function name : m_get_pending_vote_count
 *
 */

int m_get_pending_vote_count (mixed xWho)
{
  M_ACCESS_MONK_VOTES;

  string  *asVotes;
  int     iVoter;
  int     iCount;

  asVotes = m_indices (mMonkVotes);

  iCount = 0;
  foreach (string sVote : asVotes)
  {
    if (m_is_authorized_voter (xWho, sVote) && !m_is_past_voter (xWho, sVote))
    {
      iCount ++;
    }
  }
  return (iCount);
}


/*
 * Function name : m_add_vote
 * Description   : Adds a vote as per the arguments.
 * Returns       : An error message or FALSE as an indication of success.
 *
 */

mixed m_add_vote (string sName, string sDesc,
                  string sOwner, int iFlags, int iDuration,
                  string sFinishFile, string sFinishFunction)
{
  M_ACCESS_MONK_VOTES;

  int iFinishTime;

  if (member_array (sName, m_indices (mMonkVotes)) >= 0)
    return ("A vote of this name already exists.\n");

  // This is a new vote, just add it to the mapping.
  // Note that the order of items in the structure
  // must correspond with the constants defined
  // in the include file.

  if (iDuration == M_VOTE_INFINITE) iFinishTime = 0;
                               else iFinishTime = time () + iDuration * DG_SEC2DAY;

  mMonkVotes += ([ sName : ({ sDesc, sOwner, iFlags, ([ ]),
                              iFinishTime, sFinishFile, sFinishFunction }) ]);

  M_SAVE_ACCESSED;
  return (FALSE);
}


/*
 * Function name : m_cast_vote
 * Description   : Casts a vote as per the arguments.
 * Returns       : An error message or FALSE as an indication of success.
 *
 */

mixed m_cast_vote (mixed xWho, string sName, string sVote)
{
  M_ACCESS_MONK_VOTES;

  string sWho = objectp (xWho) ? dg_get_name (xWho) : xWho;

  mixed   *axVote;
  mapping mVotes;
  int     iFlags;

  if (!m_is_authorized_voter (sWho, sName))
    return ("A vote of this name does not exist.\n");
  if (m_is_punished (sWho, M_PUNISH_NOVOTE))
    return ("You are forbidden to vote by the council.\n");

  // We can be sure the vote exists here.

  axVote = mMonkVotes [sName];

  // Check whether the vote is a valid choice.

  sVote = lower_case (sVote);
  iFlags = axVote [M_VOTES_FLAGS];
  if (iFlags & M_VOTE_YESNOVOTES)
  {
    if ((sVote != "yes") &&
        (sVote != "no") &&
        (sVote != "abstain"))
    {
      return ("You can only cast your vote for yes, no or abstain.\n");
    }
  }
  else if (iFlags & M_VOTE_PLAYERVOTES)
  {
    if (!dg_is_player (sVote))
    {
      return ("You can only cast your vote for a person.\n");
    }
    sVote = capitalize (sVote);
  }

  mVotes = axVote [M_VOTES_VOTES];

  // If this player already cast a vote, replace it,
  // otherwise just add the vote to the list.

  if (member_array (sWho, m_indexes (mVotes)) >= 0)
  {
    mVotes [sWho] = sVote;
  }
  else
  {
    mVotes += ([ sWho : sVote ]);
  }

  M_SAVE_ACCESSED;
  return (FALSE);
}


/*
 * Function name : m_close_vote
 * Description   : Close a vote as per the argument.
 * Returns       : An error message or FALSE as an indication of success.
 *
 */

mixed m_close_vote (string sName)
{
  M_ACCESS_MONK_VOTES;

  mixed *axVote;

  if (member_array (sName, m_indices (mMonkVotes)) < 0)
    return ("A vote of this name does not exist.\n");

  axVote = mMonkVotes [sName];
  call_other (axVote [M_VOTES_FINISH_FILE], axVote [M_VOTES_FINISH_FUNCTION], sName);

  M_DELETE_MONK_VOTES (sName);
  M_SAVE_ACCESSED;
  return (FALSE);
}



/*
 * Function name : m_remove_vote
 * Description   : Removes a vote as per the argument.
 * Returns       : An error message or FALSE as an indication of success.
 *
 */

mixed m_remove_vote (string sName)
{
  M_ACCESS_MONK_VOTES;

  if (member_array (sName, m_indices (mMonkVotes)) < 0)
    return ("A vote of this name does not exist.\n");

  M_DELETE_MONK_VOTES (sName);
  M_SAVE_ACCESSED;
  return (FALSE);
}

//-------------------------------------------------------------------

/*******************************************************************\
| Basic vote tallying functions                                     |
\*******************************************************************/

/*
 * Function name : m_check_votes
 * Description   : Closes all due votes
 *
 */

void m_check_votes ()
{
  M_ACCESS_MONK_VOTES;

  string  *asVotes;

  asVotes = m_indices (mMonkVotes);

  foreach (string sVote : asVotes)
  {
    if (m_is_closed_vote (sVote))
    {
      m_close_vote (sVote);
    }
  }
}


/*
 * Function name : m_tally_decision
 * Description   : Returns a decision of tallied votes, which
 *                 is FALSE if the majority of the yes and no
 *                 votes was negative and TRUE otherwise
 *
 */

int m_tally_decision (string sName)
{
  M_ACCESS_MONK_VOTES;

  string  *asVotes;
  int     iCountNo = 0;
  int     iCountYes = 0;

  if (member_array (sName, m_indexes (mMonkVotes)) >= 0)
  {
    asVotes = m_values (mMonkVotes [sName][M_VOTES_VOTES]);
    foreach (string sVote : asVotes)
    {
      switch (sVote)
      {
        case "yes" : iCountYes ++; break;
        case "no"  : iCountNo ++; break;
      }
    }
    return (iCountNo <= iCountYes);
  }
  else return (TRUE);
}


/*
 * Function name : m_tally_votes
 * Description   : Returns a mapping of tallied votes
 *
 */

mapping m_tally_votes (string sName)
{
  M_ACCESS_MONK_VOTES;

  mapping mTallyInverted = ([ ]);
  mapping mTallyUnsorted = ([ ]);
  int     *aiTallyCounts;
  string  *asTallyVotes;
  string  *asVotes;
  int     iCount;

  if (member_array (sName, m_indexes (mMonkVotes)) >= 0)
  {
    // Create a mapping holding a count for each vote.

    asVotes = m_values (mMonkVotes [sName][M_VOTES_VOTES]);
    foreach (string sVote : asVotes)
    {
      if (member_array (sVote, m_indexes (mTallyInverted)) >= 0)
      {
        mTallyInverted [sVote] ++;
      }
      else
      {
        mTallyInverted += ([ sVote : 1 ]);
      }
    }

    // For the yes or no votes, ignore the abstain vote.

    if (mMonkVotes [sName][M_VOTES_FLAGS] & M_VOTE_YESNOVOTES)
    {
      mTallyInverted = m_delete (mTallyInverted, "abstain");
    }

    // Invert the mapping and merge votes with the same count.

    asTallyVotes = m_indexes (mTallyInverted);
    foreach (string sVote : asTallyVotes)
    {
      iCount = mTallyInverted [sVote];
      if (member_array (iCount, m_indexes (mTallyUnsorted)) >= 0)
      {
        mTallyUnsorted [iCount] += ({ sVote });
      }
      else
      {
        mTallyUnsorted += ([ iCount : ({ sVote }) ]);
      }
    }

    // We have to return the results unsorted because mapping
    // does not guarantee preserving the order of its keys.

    return (mTallyUnsorted);
  }
  else return (([ ]));
}


/*
 * Function name : m_tally_voters
 * Description   : Returns a mapping of tallied voters
 *
 */

mapping m_tally_voters (string sName)
{
  M_ACCESS_MONK_VOTES;

  mapping mVotes;
  mapping mTallyUnsorted = ([ ]);
  mapping mTallySorted = ([ ]);
  string  *asTallyVotes;
  string  *asVoters;
  string  sVoterCap;
  string  sVoterVote;
  int     iCount;

  if (member_array (sName, m_indexes (mMonkVotes)) >= 0)
  {
    // Create a mapping holding voters for each vote.

    mVotes = mMonkVotes [sName][M_VOTES_VOTES];
    asVoters = m_indices (mVotes);
    foreach (string sVoter : asVoters)
    {
      sVoterCap = capitalize (sVoter);
      sVoterVote = mVotes [sVoter];
      if (member_array (sVoterVote, m_indexes (mTallyUnsorted)) >= 0)
      {
        mTallyUnsorted [sVoterVote] += ({ sVoterCap });
      }
      else
      {
        mTallyUnsorted += ([ sVoterVote : ({ sVoterCap }) ]);
      }
    }

    // Sort the results by the vote and by the voter.

    asTallyVotes = sort_array (m_indexes (mTallyUnsorted));
    foreach (string sVote : asTallyVotes)
    {
      mTallySorted += ([ sVote : sort_array (mTallyUnsorted [sVote]) ]);
    }
    return (mTallySorted);
  }
  else return (([ ]));
}


/*
 * Function name : m_summarize_votes
 * Description   : Returns a text summarizing a tally of votes
 *
 */

string m_summarize_votes (string sName)
{
  M_ACCESS_MONK_VOTES;

  string  sSummary;
  mapping mTally;
  int     *aiCounts;
  int     iCount;
  int     iFlags;
  int     iIndex;

  // Make sure the vote exists.

  if (member_array (sName, m_indexes (mMonkVotes)) < 0) return ("");
  iFlags = mMonkVotes [sName][M_VOTES_FLAGS];

  mTally = m_tally_votes (sName);
  if (m_sizeof (mTally) > 0)
  {
    aiCounts = sort_array (m_indexes (mTally), &dg_sort_int_descending ());
    if (iFlags & M_VOTE_WINNER)
    {
      // Some votes require that only the winner is announced.

      iCount = aiCounts [0];
      if (sizeof (mTally [iCount]) > 1)
      {
        sSummary = "The shared winners are the votes for " +
                    COMPOSITE_WORDS (mTally [iCount]) + ", each ";
      }
      else
      {
        sSummary = "The winner is the vote for " +
                    mTally [iCount][0] + ", ";
      }
      sSummary += "with " + iCount + " " + (iCount > 1 ? "votes" : "vote") + ".\n";
    }
    else
    {
      // Some votes require that all votes are announced.

      sSummary = "The votes are as follows:\n";
      for (iIndex = 0 ; iIndex < sizeof (aiCounts) ; iIndex ++)
      {
        iCount = aiCounts [iIndex];
        if (sizeof (mTally [iCount]) > 1)
        {
          sSummary += "  In the shared " + LANG_WORD (iIndex + 1) + " place are the votes for " +
                      COMPOSITE_WORDS (mTally [iCount]) + ", each ";
        }
        else
        {
          sSummary += "  In the " + LANG_WORD (iIndex + 1) + " place is the vote for " +
                      mTally [iCount][0] + ", ";
        }
        sSummary += "with " + iCount + " " + (iCount > 1 ? "votes" : "vote") + ".\n";
      }
    }

    return (sSummary);
  }

  return ("There is no valid vote.\n");
}


/*
 * Function name : m_summarize_voters
 * Description   : Returns a text summarizing a tally of voters
 *
 */

string m_summarize_voters (string sName)
{
  M_ACCESS_MONK_VOTES;

  string  sSummary;
  mapping mTally;
  string  *asVotes;
  int     iFlags;

  // Make sure the vote exists and is not anonymous.

  if (member_array (sName, m_indexes (mMonkVotes)) < 0) return ("");
  iFlags = mMonkVotes [sName][M_VOTES_FLAGS];
  if (iFlags & M_VOTE_ANONYMOUS) return ("");

  mTally = m_tally_voters (sName);
  if (m_sizeof (mTally) > 0)
  {
    asVotes = m_indexes (mTally);
    sSummary = "The voters are as follows:\n";
    foreach (string sVote : asVotes)
    {
      sSummary += "  " + COMPOSITE_WORDS (mTally [sVote]) + " voted for " + sVote + ".\n";
    }

    return (sSummary);
  }

  return ("There is no voter.\n");
}

//-------------------------------------------------------------------

/*******************************************************************\
| Vote actions                                                      |
\*******************************************************************/

/*
 * Function name : m_action_vote
 *
 */

int m_action_vote (string sArgs)
{
  object oHim = this_player ();
  string sName;
  string sVote;
  mixed  xResult;

  notify_fail ("Syntax: " + query_verb () + " <vote name>, <vote>\n" +
               "  <vote name>        - a name of the vote\n" +
               "  <vote>             - the vote to cast\n" +
               "Example: " + query_verb () + " monk, segoy\n");

  // Now that we prepared the help, let us parse the input.

  if (stringp (sArgs))
  {
    if (sscanf (sArgs, "%s,%s", sName, sVote) != 2)
    {
      return (FALSE);
    }
  }
  else return (FALSE);

  sName = dg_remove_whitespace (sName);
  sVote = dg_remove_whitespace (sVote);

  // We have everything, just cast the vote.

  xResult = m_cast_vote (oHim, sName, sVote);
  if (stringp (xResult))
  {
    notify_fail (xResult);
    return (FALSE);
  }
  else
  {
    write ("Your vote has been cast.\n");
    return (TRUE);
  }
}


/*
 * Function name : m_action_voteadd
 *
 */

int m_action_voteadd (string sArgs)
{
  object oHim = this_player ();
  string *asProperties, sProperties;
  string sName, sDesc;
  int    iDuration;
  int    iFlags;
  string sHelp;
  mixed  xResult;

  sHelp =
    "Syntax: " + query_verb () + " <vote name>, <properties>, <duration>, <description>\n" +
    "  <vote name>        - a unique name of the vote\n" +
    "  <properties>       - a list of properties separated by spaces\n" +
    "    membersonly          only guild members may vote\n";

  if (m_is_elder_member (oHim)) sHelp +=
    "    eldersonly         only elders may vote\n";
  if (m_is_council_member (oHim)) sHelp +=
    "    councilonly        only council may vote\n";

  sHelp +=
    "    playervotes          a vote for a player is expected\n" +
    "    yesnovotes           a vote of yes or no is expected\n" +
    "    anonymous            keep the voters secret\n" +
    "    secret               keep the progress secret\n" +
    "    winner               announce only the winner\n" +
    "    majority             announce majority decision\n" +
    "  <duration>         - how many days to keep the vote open\n" +
    "  <description>      - a brief description of the vote\n";

  sHelp +=
    "Example: " + query_verb () + " monk, playervotes anonymous secret, 14, " +
    "Who embodies the ideal of a monk in your eyes ?\n";

  notify_fail (sHelp);

  // Now that we prepared the help, uff, let us parse the input.

  if (stringp (sArgs))
  {
    if (sscanf (sArgs, "%s,%s,%d,%s", sName, sProperties, iDuration, sDesc) != 4)
    {
      if (sscanf (sArgs, "%s,,%d,%s", sName, iDuration, sDesc) != 3)
      {
        return (FALSE);
      }
      sProperties = "";
    }
  }
  else return (FALSE);

  sName = dg_remove_whitespace (sName);
  sDesc = dg_remove_whitespace (sDesc);

  asProperties = explode (sProperties, " ");
  iFlags = 0;
  foreach (string sProperty : asProperties)
  {
    switch (sProperty)
    {
      case "membersonly":       iFlags |= M_VOTE_MEMBERSONLY; break;
      case "eldersonly":        iFlags |= M_VOTE_ELDERSONLY; break;
      case "councilonly":       iFlags |= M_VOTE_COUNCILONLY; break;
      case "playervotes":       iFlags |= M_VOTE_PLAYERVOTES; break;
      case "yesnovotes":        iFlags |= M_VOTE_YESNOVOTES; break;
      case "anonymous":         iFlags |= M_VOTE_ANONYMOUS; break;
      case "secret":            iFlags |= M_VOTE_SECRET; break;
      case "winner":            iFlags |= M_VOTE_WINNER; break;
      case "majority":          iFlags |= M_VOTE_MAJORITY; break;
      case "":                  break;
      default:                  return (FALSE);
    }
  }

  if ((strlen (sName) > M_VOTE_MAX_NAME_LEN) ||
      (iDuration < M_VOTE_MIN_DURATION) ||
      (iDuration > M_VOTE_MAX_DURATION))
  {
    return (FALSE);
  }

  // We have everything, just add the vote.

  xResult = m_add_vote (sName, sDesc, dg_get_name (oHim),
                        iFlags, iDuration,
                        MASTER, "m_finish_vote_post");
  if (stringp (xResult))
  {
    notify_fail (xResult);
    return (FALSE);
  }

  write ("Your vote has been added.\n");
  return (TRUE);
}


/*
 * Function name : m_action_voteinfo
 *
 */

int m_action_voteinfo (string sArgs)
{
  M_ACCESS_MONK_VOTES;

  object  oHim = this_player ();
  mixed   *axVote;
  int     iDuration;
  int     iFinish;
  int     iFlags;

  notify_fail ("Syntax: " + query_verb () + " <vote name>\n");

  if (m_is_authorized_voter (oHim, sArgs))
  {
    // We can be sure the vote exists here.

    axVote = mMonkVotes [sArgs];
    iFlags = axVote [M_VOTES_FLAGS];
    iFinish = axVote [M_VOTES_FINISH_TIME];

    // Display basic characteristics of the vote.

    write ("The vote has been created by " +
           capitalize (axVote [M_VOTES_OWNER]) + " " +
           "and is described as follows:\n" +
           axVote [M_VOTES_DESC] + "\n");

    // Display the duration of the vote.

    if (iFinish == 0)
    {
      if (iFlags & M_VOTE_MAJORITY) write ("The vote will finish when a majority vote is cast. ");
                               else write ("The vote will finish when all votes are cast. ");
    }
    else
    {
      iDuration = iFinish - time ();
      if (iDuration > 0) write ("The vote will finish in " + CONVTIME ((iDuration / DG_SEC2MIN) * DG_SEC2MIN) + ". ");
                    else write ("The vote has finished " + CONVTIME ((-iDuration / DG_SEC2MIN) * DG_SEC2MIN) + " ago. ");
    }

    // Display the settings of the vote.

    if ((iFlags & M_VOTE_COUNCILONLY) &&
        (iFlags & M_VOTE_ELDERSONLY))
    {
      write ("Only the council and elder members can vote, ");
    }
    else if (iFlags & M_VOTE_COUNCILONLY) write ("Only the council members can vote, ");
    else if (iFlags & M_VOTE_ELDERSONLY)  write ("Only the elder members can vote, ");
    else if (iFlags & M_VOTE_MEMBERSONLY) write ("Only monks can vote, ");
    else                                  write ("Anyone can vote, ");

         if (iFlags & M_VOTE_YESNOVOTES)  write ("votes are for yes, no or abstain. ");
    else if (iFlags & M_VOTE_PLAYERVOTES) write ("votes are for any player. ");
    else                                  write ("votes are for anything. ");

    write ("Voters are " + ((iFlags & M_VOTE_ANONYMOUS) ? "" : "not ") + "anonymous, ");
    write ("progress is " + ((iFlags & M_VOTE_SECRET) ? "" : "not ") + "secret, ");

         if (iFlags & M_VOTE_WINNER) write ("only the winner will be reported.\n");
    else                             write ("complete results will be reported.\n");

    // Depending on the settings, display the progress of the vote.

    if (!(iFlags & M_VOTE_SECRET))
    {
      write (m_summarize_votes (sArgs));
      write (m_summarize_voters (sArgs));
    }

    return (TRUE);
  }
  else return (FALSE);
}


/*
 * Function name : m_action_votelist
 *
 */

int m_action_votelist (string sArgs)
{
  M_ACCESS_MONK_VOTES;

  object  oHim = this_player ();
  string  *asVotes;
  int     iFinish;
  int     iDuration;
  string  sDuration;

  if (m_get_total_vote_count (oHim) > 0)
  {
    write ("+---------------------------------------+-------+-----------------------------+\n");
    write ("| Vote Name                             | Voted | Time Remaining              |\n");
    write ("+---------------------------------------+-------+-----------------------------+\n");
    foreach (string sVote, mixed axVote : mMonkVotes)
    {
      if (m_is_authorized_voter (oHim, sVote))
      {
        iFinish = axVote [M_VOTES_FINISH_TIME];
        if (iFinish == 0)
        {
          sDuration = "Infinite";
        }
        else
        {
          iDuration = iFinish - time ();
          if (iDuration < 0) sDuration = "Finished";
                        else sDuration = CONVTIME ((iDuration / DG_SEC2MIN) * DG_SEC2MIN);
        }

        write (sprintf ("| %-37s |  %-3s  | %-27s |\n",
                        sVote,
                        m_is_past_voter (oHim, sVote) ? "Yes" : "No ",
                        sDuration));
      }
    }
    write ("+---------------------------------------+-------+-----------------------------+\n");
  }
  else
  {
    write ("There are currently no active votes.\n");
  }

  return (TRUE);
}


/*
 * Function name : m_action_voteclose
 *
 */

int m_action_voteclose (string sArgs)
{
  object  oHim = this_player ();
  mixed   xResult;

  notify_fail ("Syntax: " + query_verb () + " <vote name>\n" +
               "Note: You can only close a vote that you have started.\n");

  if (m_is_supervisor_voter (oHim, sArgs))
  {
    xResult = m_close_vote (sArgs);
    if (stringp (xResult))
    {
      notify_fail (xResult);
      return (FALSE);
    }
    else
    {
      write ("Your vote has been closed.\n");
      return (TRUE);
    }
  }
  else return (FALSE);
}


/*
 * Function name : m_action_voteremove
 *
 */

int m_action_voteremove (string sArgs)
{
  object  oHim = this_player ();
  mixed   xResult;

  notify_fail ("Syntax: " + query_verb () + " <vote name>\n" +
               "Note: You can only remove a vote that you have started.\n");

  if (m_is_supervisor_voter (oHim, sArgs))
  {
    xResult = m_remove_vote (sArgs);
    if (stringp (xResult))
    {
      notify_fail (xResult);
      return (FALSE);
    }
    else
    {
      write ("Your vote has been removed.\n");
      return (TRUE);
    }
  }
  else return (FALSE);
}

//-------------------------------------------------------------------

/*******************************************************************\
| Vote hooks                                                        |
\*******************************************************************/

void m_voting_hook_create ()
{
  setuid();
  seteuid(getuid());
  set_alarm (0.0, 3600.0, m_check_votes);
}


void m_voting_hook_init ()
{
  add_action (m_action_vote, "vote");
  add_action (m_action_voteadd, "voteadd");
  add_action (m_action_voteinfo, "voteinfo");
  add_action (m_action_votelist, "votelist");
  add_action (m_action_voteclose, "voteclose");
  add_action (m_action_voteremove, "voteremove");
}


void m_voting_hook_enter_inv (object oWho, object oFrom)
{
  int iVotes;

  if (interactive (oWho))
  {
    iVotes = m_get_pending_vote_count (oWho);
    if (iVotes > 0)
    {
      if (iVotes == 1)
      {
        set_alarm (1.0, 0.0, &oWho->catch_tell (
          "There is one vote you have not yet participated in.\n"));
      }
      else
      {
        set_alarm (1.0, 0.0, &oWho->catch_tell (
          "There are " + LANG_WNUM (iVotes) + " votes you have not yet participated in.\n"));
      }
    }
  }
}

//-------------------------------------------------------------------

/*******************************************************************\
| Vote finishing functions                                          |
\*******************************************************************/

void m_finish_vote_post (string sName)
{
  M_ACCESS_MONK_VOTES;

  mixed  *axVote;
  string sDesc;

  axVote = mMonkVotes [sName];

  sDesc = axVote [M_VOTES_DESC] + "\n\n" +
          m_summarize_votes (sName) + "\n" +
          m_summarize_voters (sName) + "\n";

  M_OBJ_BOARD_MEMBER->m_post_note ("Vote results: " + sName,
                                   "Ballot",
                                   dg_framed_text (sDesc));
}

//-------------------------------------------------------------------

