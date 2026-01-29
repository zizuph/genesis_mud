/*******************************************************************\
| LIBS_JOINING.C                                                    |
\*******************************************************************/

/*
 * 08/02/16 Mercade     Use CMDPARSE_PARALYZE_CMD_IS_ALLOWED
 * 07/05/19 Arandir     Merged with extraneous include
 * 07/05/18 Arandir     Changed joining to be less time demanding
 * 04/11/13 Arandir     Minor typo fix
 * 04/08/15 Arandir     Dedication now requires council blessing
 * 03/12/16 Arandir     Added the initiation ceremony by Sionell
 * 03/12/12 Arandir     Added logging of application vote
 *          Arandir     Moved the penalty on leaving guild
 *          Arandir     Added safeguard to forsake command
 * 03/11/13 Arandir	Fixed an incorrect leaving penalty
 * 03/11/07 Arandir     Fixed an incorrect use of mappings
 * 03/11/04 Arandir     Shortened the council election duration
 * 03/10/21 Arandir     Added monitoring of council terms
 * 03/10/06 Arandir     Added logging of applicants
 * 03/06/10 Arandir	Created
 *
 */

#include <time.h>
#include <macros.h>
#include <cmdparse.h>
#include <language.h>
#include <ss_types.h>

#include "../defs.h"

inherit DG_MISC_LIBS;
inherit M_PLAYER_LIBS;
inherit M_VOTING_LIBS;

//-------------------------------------------------------------------

// Data file definitions

#define M_ACCESS_MONK_APPLICANTS        mapping mMonkApplicants = M_MONK_SRVR->m_get_monk_applicants ()
#define M_DELETE_MONK_APPLICANTS(sKey)  mMonkApplicants = M_MONK_SRVR->m_delete_monk_applicants (sKey)

#define M_SAVE_ACCESSED                 M_MONK_SRVR->m_save_object ()


#define M_APPLICANTS_BRANCH             0
#define M_APPLICANTS_TIME               1
#define M_APPLICANTS_STATUS             2

#define M_APPLICANT_WAITING             0
#define M_APPLICANT_ACCEPTED            1
#define M_APPLICANT_REJECTED            2

//-------------------------------------------------------------------

// How long in days until the resolved applications disappear
#define M_APPLICANT_RESOLVE_DURATION    30

// How long in days until the council is inactive
#define M_COUNCIL_INACTIVE_DURATION     30

// How long in days until the council votes finish
#define M_COUNCIL_DECIDE_DURATION       14

// Property for detecting the applicant trance
#define M_PROP_TMP_I_TRANCING           "_monk_tmp_i_trancing"

//-------------------------------------------------------------------

/*******************************************************************\
| Basic applicant manipulation functions                            |
\*******************************************************************/

/*
 * Function name : m_add_applicant
 * Description   : Adds an applicant as per the arguments.
 * Returns       : Zero as an indication of success or an error message
 *
 */

mixed m_add_applicant (string sWho, int iBranch)
{
  M_ACCESS_MONK_APPLICANTS;

  string sWhoCap = capitalize (sWho);

  // Perform a sanity check so that monks do not reapply.

  if (m_is_monk (sWho))
    return ("You are already a member, you can <transfer> to a different branch.\n");

  if (member_array (sWho, m_indices (mMonkApplicants)) >= 0)
    return ("You have already applied, you can <check> the status of your application or <withdraw> your application.\n");

  // This is a new application, just add it to the mapping.
  // Note that the order of items in the structure must
  // correspond with the constants defined in the
  // include file.

  mMonkApplicants += ([ sWho : ({ iBranch, time (), M_APPLICANT_WAITING }) ]);

  s_log (M_LOG_WIZARD | M_LOG_COUNCIL, sWhoCap + " applied to the guild.");
  m_add_vote (sWho + " application",
              "Should " + sWhoCap + " be allowed to enter the Dragon Order ?",
              "ballot",
              M_VOTE_COUNCILONLY | M_VOTE_YESNOVOTES | M_VOTE_MAJORITY,
              M_VOTE_INFINITE,
              MASTER, "m_finish_vote_applicant");

  M_SAVE_ACCESSED;
  return (FALSE);
}


/*
 * Function name : m_decide_applicant
 * Description   : Decides on an applicant as per the arguments.
 *
 */

void m_decide_applicant (string sName, int iResult)
{
  M_ACCESS_MONK_APPLICANTS;

  mixed *axApplicant;

  if (member_array (sName, m_indices (mMonkApplicants)) >= 0)
  {
    axApplicant = mMonkApplicants [sName];

    axApplicant [M_APPLICANTS_TIME] = time () + M_APPLICANT_RESOLVE_DURATION * DG_SEC2DAY;
    axApplicant [M_APPLICANTS_STATUS] = (iResult ? M_APPLICANT_ACCEPTED : M_APPLICANT_REJECTED);

    M_SAVE_ACCESSED;
  }
}

//-------------------------------------------------------------------

/*******************************************************************\
| Basic applicant talying functions                                 |
\*******************************************************************/

/*
 * Function name : m_check_applicants
 * Description   : Deletes all expired resolved applications
 *
 */

void m_check_applicants ()
{
  M_ACCESS_MONK_APPLICANTS;

  // Take a look at the time since the last council activity.

  if (m_get_council_activity () + M_COUNCIL_INACTIVE_DURATION * DG_SEC2DAY < time ())
  {
    // Council is inactive. Accept all waiting applicants.

    foreach (string sApplicant, mixed axApplicant : mMonkApplicants)
    {
      if (axApplicant [M_APPLICANTS_STATUS] == M_APPLICANT_WAITING)
      {
        m_decide_applicant (sApplicant, TRUE);
      }
    }
  }
  else
  {
    // Council is active. Remove all resolved applicants.

    foreach (string sApplicant, mixed axApplicant : mMonkApplicants)
    {
      if ((axApplicant [M_APPLICANTS_STATUS] != M_APPLICANT_WAITING) &&
          (axApplicant [M_APPLICANTS_TIME] < time ()))
      {
        M_DELETE_MONK_APPLICANTS (sApplicant);
        M_SAVE_ACCESSED;
      }
    }
  }
}


/*
 * Function name : m_check_council
 * Description   : Kicks out councillors whose term has expired.
 *                 Launches new council election when there are
 *                 too few councillors present and no vote in
 *                 progress.
 *
 */

void m_check_council ()
{
  string *asCouncils;

  foreach (string sCouncil : m_get_council_members ())
  {
    if (m_get_council_term (sCouncil) < - M_GRACE_COUNCIL)
    {
      m_remove_council_member (sCouncil);
    }
  }

  if (sizeof (m_get_council_members ()) < M_SIZE_COUNCIL)
  {
    if (!m_is_vote ("council"))
    {
      m_add_vote (
        "council",
        "Whom do you consider most suitable to serve in the council ?",
        M_SPIRIT_UPPER,
        M_VOTE_MEMBERSONLY | M_VOTE_PLAYERVOTES | M_VOTE_ANONYMOUS | M_VOTE_SECRET,
        M_COUNCIL_DECIDE_DURATION,
        MASTER, "m_finish_vote_council");

      M_OBJ_BOARD_MEMBER->m_post_note (
        "Council election", M_SPIRIT_UPPER,
        dg_framed_text ("The council election is in progress. Be sure to " +
                        "voice your opinion by casting your ballot in " +
                        "the council vote !" ));
    }
  }
}

//-------------------------------------------------------------------

/*******************************************************************\
| Applicant trance alarm                                            |
\*******************************************************************/

void m_dedicate_trance (object oWho, int iStep)
{
  switch (iStep)
  {
    case 0:
      oWho->catch_tell (
        "The eyes of the ancient dragon statue seem to draw " +
        "your attention more than ever before. Suddenly, a " +
        "light flares in the depths of the statue's eyes " +
        "and you feel yourself engulfed in its fierce " +
        "burning radiance.\n");
      set_alarm (20.0, 0.0, &m_dedicate_trance (oWho, iStep + 1));
      break;

    case 1:
      oWho->catch_tell (
        "A voice thunders in your mind, shaking the foundations " +
        "of all you knew to be reality. 'Why have you come, young " +
        "one ?' it asks you inescapably. You feel a searing pain as " +
        "if the very soul inside your body was being torn out and " +
        "examined. Every story of ancient dragons that you heard " +
        "as a child flashes through your mind.\n");
      set_alarm (20.0, 0.0, &m_dedicate_trance (oWho, iStep + 1));
      break;

    case 2:
      oWho->catch_tell (
        "'Am I worthy ?' you think in desperation, looking " +
        "at the power of the ancient dragon before you and " +
        "remembering your own insignificance.\n");
      set_alarm (30.0, 0.0, &m_dedicate_trance (oWho, iStep + 1));
      break;

    case 3:
      oWho->catch_tell (
        "'It is there !' the voice rejoices. 'I see the Spirit " +
        "of Segoy within you !' Suddenly, the statue above you " +
        "moves. Great wings, warm as shadow, enfold you in a " +
        "hushed and reverent silence.\n" +
        "'See !' the ancient dragon draws your attention to an " +
        "infintesimally small speck of light that seems to hover " +
        "within you. 'Segoy has chosen you, for your Spirit " +
        "contains the Essence of the Makers.'\n");
      set_alarm (20.0, 0.0, &m_dedicate_trance (oWho, iStep + 1));
      break;

    case 4:
      oWho->catch_tell (
        "The voice reverberates with thunder. 'Learn now what it " +
        "means to Dance on the West Wind.'\n");
      set_alarm (20.0, 0.0, &m_dedicate_trance (oWho, iStep + 1));
      break;

    case 5:
      oWho->catch_tell (
        "Wings of smoke surround you, penetrating your deepest heart. " +
        "Slowly, you feel them tighten around your form, stretching " +
        "and bending your body until your arms fly out beside you.\n");
      set_alarm (20.0, 0.0, &m_dedicate_trance (oWho, iStep + 1));
      break;

    case 6:
      oWho->catch_tell (
        "Leathery wings carry you far into the air above the monastery. " +
        "Below you, the world carries on, ignorant of your shadow as " +
        "you pass over the mountains and out towards the ocean. You " +
        "see many great islands spread out below you as a necklace " +
        "on a blue velvet cloth.\n");
      set_alarm (20.0, 0.0, &m_dedicate_trance (oWho, iStep + 1));
      break;

    case 7:
      oWho->catch_tell (
        "As you pass over the islands, a sense of kinship fills your " +
        "soul. But kinship quickly gives way to fear as a great dark " +
        "cloud rises from below and hovers before you, coalescing " +
        "into a black dragon. Ancient and terrible, the creature " +
        "seems made of your fears.\n");
      set_alarm (10.0, 0.0, &m_dedicate_trance (oWho, iStep + 1));
      break;

    case 8:
      oWho->catch_tell (
        "Your heart freezes in your breast ...\n" +
        "Wings grow silent ...\n" +
        "You fall ...\n");
      set_alarm (20.0, 0.0, &m_dedicate_trance (oWho, iStep + 1));
      break;

    case 9:
      oWho->catch_tell (
        "As you struggle to master your fear, the black dragon " +
        "begins to fade. Finally, your fear is gone and so is " +
        "the creature, leaving you flying free over the oceans. " +
        "The waters churn beneath you as you circle back to the " +
        "monastery. Slowly spiraling above the Talons, you descend " +
        "and settle back into your own body ...\n");
      set_alarm (20.0, 0.0, &m_dedicate_trance (oWho, iStep + 1));
      break;

    case 10:
      oWho->catch_tell (
        "... but not quite your own. For somewhere within, a dragon " +
        "has been set free.\n");
      set_alarm (10.0, 0.0, &m_dedicate_trance (oWho, iStep + 1));
      break;

    default:
      oWho->catch_tell ("Enter 'help monks' for a list of commands.\n");
      tell_room (this_object (), QCTNAME (oWho) + " straightens in a determined gesture.\n",oWho);

      oWho->remove_prop (M_PROP_TMP_I_TRANCING);

      break;
  }
}

//-------------------------------------------------------------------

/*******************************************************************\
| Basic applicant actions                                           |
\*******************************************************************/


/*
 * Function name : m_join_action_block
 * Description   : A command hook to stop players from executing
 *                 commands while in initiation trance.
 *
 */

int m_join_action_block (string sArgs)
{
  object oMe = this_player ();

  // Some commands are always allowed ...

  if (CMDPARSE_PARALYZE_CMD_IS_ALLOWED (query_verb ())) return (FALSE);

  // We must really be in trance ...

  if (!oMe->query_prop (M_PROP_TMP_I_TRANCING)) return (FALSE);

  write ("The tension around you prevents you from moving.\n");
  return (TRUE);
}


int m_join_action_apply (string sArgs)
{
  object oHim = this_player ();
  int    iBranch;
  mixed  xResult;

  notify_fail ("Syntax: " + query_verb () + " <branch>\n" +
               "  <branch>           - occupational or layman\n");

  switch (sArgs)
  {
    case "occupational": iBranch = SS_OCCUP; break;
    case "layman":       iBranch = SS_LAYMAN; break;
    default:             return (FALSE);
  }

  xResult = m_add_applicant (dg_get_name (oHim), iBranch);
  if (stringp (xResult))
  {
    notify_fail (xResult);
    return (FALSE);
  }
  else
  {
    write ("Your application has been noted.\n");
    return (TRUE);
  }
}


int m_join_action_check (string sArgs)
{
  M_ACCESS_MONK_APPLICANTS;

  object oHim = this_player ();
  string sHim = dg_get_name (oHim);
  mixed  *axApplicant;
  int    iTimeSinceApplying;
  int    iTimeUntilResolving;

  if (member_array (sHim, m_indexes (mMonkApplicants)) >= 0)
  {
    axApplicant = mMonkApplicants [sHim];

    if (axApplicant [M_APPLICANTS_STATUS] == M_APPLICANT_WAITING)
    {
      iTimeSinceApplying = time () - axApplicant [M_APPLICANTS_TIME];
      iTimeSinceApplying = (iTimeSinceApplying / DG_SEC2MIN) * DG_SEC2MIN;
    }
    else
    {
      iTimeUntilResolving = min (0, axApplicant [M_APPLICANTS_TIME] - time ());
      iTimeUntilResolving = (iTimeUntilResolving / DG_SEC2MIN) * DG_SEC2MIN;
    }

    switch (axApplicant [M_APPLICANTS_STATUS])
    {
      case M_APPLICANT_WAITING:
        write ("Your application for membership has been noted " +
               CONVTIME (iTimeSinceApplying) + " ago but no " +
               "decision has yet been made.\n");
        break;
      case M_APPLICANT_ACCEPTED:
        write ("Your application for membership has " +
               "been accepted. The record of your " +
               "application will expire in " +
               CONVTIME (iTimeUntilResolving) + ".\n");
        break;
      case M_APPLICANT_REJECTED:
        write ("Your application for membership has " +
               "been rejected. The record of your " +
               "application will expire in " +
               CONVTIME (iTimeUntilResolving) + ".\n");
        break;
    }
  }
  else
  {
    write ("You have not applied for membership, or you have applied " +
           "and your application has been resolved more than " +
           LANG_WNUM (M_APPLICANT_RESOLVE_DURATION) + " days ago.\n");
  }

  return (TRUE);
}


int m_join_action_forsake  (string sArgs)
{
  object oHim = this_player ();
  mixed  xResult;

  if (oHim->query_prop (M_PROP_TMP_I_SAFEGUARD) != query_verb ())
  {
    oHim->add_prop (M_PROP_TMP_I_SAFEGUARD, query_verb ());
    write ("Are you sure you want to forsake the Order ? " +
           "Type the command again to confirm.\n");
    return (TRUE);
  }

  xResult = m_remove_monk (oHim);
  if (stringp (xResult))
  {
    write (xResult);
  }
  else
  {
    write ("As you forsake the Order, you suddenly feel weaker than you were before. " +
           "With a sharp pang, you realize the sense of loss that washes over you.\n");
  }

  return (TRUE);
}


int m_join_action_dedicate (string sArgs)
{
  M_ACCESS_MONK_APPLICANTS;

  object oHim = this_player ();
  string sHim = dg_get_name (oHim);
  string *asCouncils;
  string sBlesser;
  mixed  *axApplicant;
  mixed  xResult;

  if (member_array (sHim, m_indexes (mMonkApplicants)) >= 0)
  {
    axApplicant = mMonkApplicants [sHim];
    switch (axApplicant [M_APPLICANTS_STATUS])
    {
      case M_APPLICANT_WAITING:

        // The applicant is still waiting.

        write ("You cannot dedicate yourself, your application " +
               "has not been accepted yet.\n");
        break;

      case M_APPLICANT_ACCEPTED:

        // The applicant has been accepted. If there is a council,
        // blessing by a council member is required to prevent
        // jumping the initiation ceremony.

        asCouncils = m_get_council_members ();
        if (sizeof (asCouncils))
        {
          sBlesser = oHim->query_prop (M_PROP_TMP_I_BLESSED);
          if (member_array (sBlesser, asCouncils) < 0)
          {
            write ("You cannot dedicate yourself, your soul " +
                   "lacks the blessing of a councillor.\n");
            break;
          }
        }

        xResult = m_add_monk (oHim, axApplicant [M_APPLICANTS_BRANCH]);
        if (stringp (xResult))
        {
          write (xResult);
          break;
        }

        M_DELETE_MONK_APPLICANTS (sHim);
        M_SAVE_ACCESSED;

        set_alarm (20.0, 0.0, &m_dedicate_trance (oHim, 0));
        oHim->add_prop (M_PROP_TMP_I_TRANCING, TRUE);

        write ("You steel your resolve and commit yourself to " +
               "the Order. Even as you do that, you feel " +
               "a surge of tension in the air around " +
               "you tugging at your senses.\n");
        say (QCTNAME (oHim) + " ceases moving as the air " +
             "surrounding " + QOBJ (oHim) + " cracks " +
             "with sudden tension.\n");

        break;

      case M_APPLICANT_REJECTED:

        // The applicant has been rejected.

        write ("You cannot dedicate yourself, your application " +
               "has been rejected.\n");
        break;
    }
  }
  else
  {
    write ("You cannot dedicate yourself, you have not " +
           "applied for membership.\n");
  }

  return (TRUE);
}


int m_join_action_transfer (string sArgs)
{
  object oHim = this_player ();
  mixed  xResult;

  xResult = m_transfer_monk (oHim);
  if (stringp (xResult))
  {
    write (xResult);
  }
  else
  {
    write ("You have transferred a branch.\n");
  }

  return (TRUE);
}


int m_join_action_withdraw (string sArgs)
{
  M_ACCESS_MONK_APPLICANTS;

  object oHim = this_player ();
  string sHim = dg_get_name (oHim);

  if (member_array (sHim, m_indexes (mMonkApplicants)) >= 0)
  {
    write ("Your application for membership has been withdrawn.\n");

    M_DELETE_MONK_APPLICANTS (sHim);
    M_SAVE_ACCESSED;
  }
  else
  {
    write ("You have not applied for membership, or you have applied " +
           "and your application has been resolved more than " +
           LANG_WNUM (M_APPLICANT_RESOLVE_DURATION) + " days ago.\n");
  }

  return (TRUE);
}

//-------------------------------------------------------------------

/*******************************************************************\
| Join hooks                                                        |
\*******************************************************************/

void m_joining_check_hourly ()
{
  m_check_applicants ();
  m_check_council ();
}


void m_joining_hook_create ()
{
  set_alarm (0.0, 3600.0, m_joining_check_hourly);
}


void m_joining_hook_init ()
{
  add_action (m_join_action_apply, "apply");
  add_action (m_join_action_check, "check");
  add_action (m_join_action_forsake, "forsake");
  add_action (m_join_action_dedicate, "dedicate");
  add_action (m_join_action_transfer, "transfer");
  add_action (m_join_action_withdraw, "withdraw");

  add_action (m_join_action_block, "", ACTION_PARTIAL);
}

//-------------------------------------------------------------------

/*******************************************************************\
| Vote finishing functions                                          |
\*******************************************************************/

void m_finish_vote_applicant (string sName)
{
  string  sDescShort, sDescLong;
  string  sWho;
  int     iResult;

  sscanf (sName, "%s application", sWho);
  iResult = m_tally_decision (sName);

  m_decide_applicant (sWho, iResult);

  sDescShort = "The application of " + capitalize (sWho) + " has been " +
               (iResult ? "accepted" : "rejected") + ".";
  sDescLong = sDescShort + "\n\n" +
              m_summarize_votes (sName) + "\n" +
              m_summarize_voters (sName) + "\n";

  s_log (M_LOG_WIZARD | M_LOG_COUNCIL, sDescShort);
  M_OBJ_BOARD_COUNCIL->m_post_note ("Application results: " + capitalize (sWho),
                                    "Ballot",
                                    dg_framed_text (sDescLong));
}


void m_finish_vote_council (string sName)
{
  mapping mTally;
  int     *aiCounts;
  string  *asWinners;
  string  sWho, sWhoCap;
  string  sDesc;

  mTally = m_tally_votes (sName);

  if (m_sizeof (mTally))
  {
    aiCounts = sort_array (m_indexes (mTally), &dg_sort_int_descending ());
    asWinners = mTally [aiCounts [0]];
    if (sizeof (asWinners) == 1)
    {
      sWhoCap = asWinners [0];
      sWho = lower_case (sWhoCap);

      if (m_is_monk (sWho) &&
          !dg_is_junior (sWho) &&
          !dg_is_wizard (sWho) &&
          !m_is_council_member (sWho))
      {
        m_add_council_member (sWho);

        sDesc = "The winner of the council election, and also " +
                "the newest councillor, is " + sWhoCap + " !";
      }
      else
      {
        sDesc = "The winner of the council election, but not " +
                "eligible for being a councillor, is " + sWhoCap + " !";
      }
    }
    else
    {
      sDesc = "The council election ended in a tie !";
    }
  }
  else
  {
    sDesc = "The council election had no winner !";
  }

  sDesc += "\n\n" +
           m_summarize_votes (sName) + "\n";

  M_OBJ_BOARD_MEMBER->m_post_note ("Election results",
                                    "Ballot",
                                    dg_framed_text (sDesc));
}

//-------------------------------------------------------------------

