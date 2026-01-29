/*******************************************************************\
| LIBS_PLAYER.C                                                     |
\*******************************************************************/

/*
 * 08/02/06 Arandir     Fixed a missing inherit used in porting quest bits
 * 08/01/29 Arandir     More robust when querying the character fails
 * 07/06/03 Arandir     Support for configurable learning in combat
 * 07/06/01 Arandir     Fixed an incorrect call to m_get_kins
 * 07/05/19 Arandir     Merged with extraneous include
 *                      Added support for council activity
 * 06/09/02 Arandir     Fixed use of XOBJ style macros
 * 06/08/27 Arandir     Accommodated the new forming skills
 * 06/08/16 Arandir     Removed the focus skill
 * 06/02/01 Arandir     Incorporated domain quest support
 * 06/01/01 Arandir     New council member was added using old data version
 * 05/06/04 Arandir     Layman skills caused layman rank titles to be low
 * 05/05/30 Arandir     Fixed missing title configuration for new players
 * 05/05/07 Arandir     Minor changes to titles
 * 05/04/24 Arandir     New rank titles
 * 05/04/06 Arandir     Fixed alignment title range
 * 04/11/17 Arandir     Support for new rank titles
 * 04/11/14 Arandir     Added querying of guild master status
 * 04/08/28 Arandir     Support for top kins and top character
 * 04/08/25 Arandir     Default of any punishment for m_is_punished
 * 04/01/22 Arandir     Added fixing of damaged players
 * 03/12/20 Arandir     Added missing checks on joining and
 *                      transfering when other guilds block it
 * 03/12/12 Arandir     Added extra cleanup code on leaving guild
 *                      Moved the penalty on leaving guild here
 * 03/10/21 Arandir     Added support for council terms
 * 03/10/06 Arandir     Made arches and up authorized
 * 03/09/06 Arandir     Moved the kinship support into soul
 * 03/07/21 Arandir     Support for kinship with dragons
 * 03/07/03 Arandir     Support for titles for the top stats
 * 03/06/24 Arandir     Ported the support for guild titles
 * 03/06/13 Arandir     Revamped to cooperate with a data holder
 * 03/03/29 Arandir     Support for past members
 * 02/01/17 Arandir	Ported some fragments to the new area
 * 01/02/16 Manat	Changed alignment in the titles to be a toggle
 * 01/02/02 Manat	Added alignment to the titles with a choice
 * 01/01/30 Manat	Removed alignment from the titles
 * 00/12/26 Manat	Fixed typo in the titles
 * 98/04/25 Cirion	Created
 *
 */

#include <std.h>
#include <files.h>
#include <macros.h>
#include <formulas.h>
#include <ss_types.h>

#include "../defs.h"
#include "hook_training.h"

#include S_DOMAIN_SYS_QUESTS

inherit S_LIB_PLAYER;
inherit DG_TEXT_LIBS;
inherit DG_PLAYER_LIBS;
inherit M_LOGGING_LIBS;

//-------------------------------------------------------------------

// Data file definitions

#define M_ACCESS_MONK_MEMBERS           mapping mMonkMembers = M_MONK_SRVR->m_get_monk_members ()
#define M_DELETE_MONK_MEMBERS(sKey)     mMonkMembers = M_MONK_SRVR->m_delete_monk_members (sKey)

#define M_ACCESS_MONK_COUNCIL           mapping mMonkCouncil = M_MONK_SRVR->m_get_monk_council ()
#define M_DELETE_MONK_COUNCIL(sKey)     mMonkCouncil = M_MONK_SRVR->m_delete_monk_council (sKey)

#define M_ACCESS_MONK_FORMER            mapping mMonkFormer = M_MONK_SRVR->m_get_monk_former ()

#define M_ACCESS_MONK_GUILD             mixed *axMonkGuild = M_MONK_SRVR->m_get_monk_guild ()

#define M_SAVE_ACCESSED                 M_MONK_SRVR->m_save_object ()


#define M_MONK_MEMBERS_JOIN_AGE         0
#define M_MONK_MEMBERS_JOIN_TIME        1
#define M_MONK_MEMBERS_BRANCH           2
#define M_MONK_MEMBERS_POSITION         3
#define M_MONK_MEMBERS_PUNISHMENTS      4
#define M_MONK_MEMBERS_TITLE            5
#define M_MONK_MEMBERS_LEARNING         6

#define M_POSITION_MEMBER               BIT (0)
#define M_POSITION_ELDER                BIT (1)
#define M_POSITION_COUNCIL              BIT (2)


#define M_MONK_COUNCIL_DESC             0
#define M_MONK_COUNCIL_TERM             1


#define M_FORMER_MEMBERS_DESC	        0


#define M_MONK_GUILD_KINS               0
#define M_MONK_GUILD_STATS              1
#define M_MONK_GUILD_CHARACTER          2
#define M_MONK_GUILD_AGE                3
#define M_MONK_GUILD_TIME               4
#define M_MONK_GUILD_COUNCIL            5

#define M_MONK_ACTIVE_THRESHOLD         14

//-------------------------------------------------------------------

void m_limit_skills (object oWho);

//-------------------------------------------------------------------

/*******************************************************************\
| Functions for managing monk membership                            |
\*******************************************************************/

/*
 * Function name : m_add_monk
 * Returns       : Zero as an indication of success or an error message
 *
 */

mixed m_add_monk (object oWho, int iBranch)
{
  M_ACCESS_MONK_MEMBERS;

  string sWho = dg_get_name (oWho);
  string sWhoCap = capitalize (sWho);
  object oShadow;
  int    iTax;
  string sType;
  string sStyle;
  string sMessage;

  if (member_array (sWho, m_indices (mMonkMembers)) >= 0)
  {
    return ("You are already a member.\n");
  }

  switch (iBranch)
  {
    case SS_OCCUP:  iTax = M_TAX_OCC;
                    sType = M_TYPE_OCC;
                    sStyle = M_STYLE_OCC;
                    oShadow = clone_object (M_SHADOW_OCC);
                    break;

    case SS_LAYMAN: iTax = M_TAX_LAY;
                    sType = M_TYPE_LAY;
                    sStyle = M_STYLE_LAY;
                    oShadow = clone_object (M_SHADOW_LAY);
                    break;
  }

  switch (oShadow->shadow_me (oWho, sType, sStyle, M_NAME_LONG))
  {
    case 1:

      // Create the guild membership record.

      // Note that the order of items in the structure must
      // correspond with the constants defined in the
      // include file.

      mMonkMembers +=
        ([ sWho :
          ({
            oWho->query_age (),     // M_MONK_MEMBERS_JOIN_AGE
            time (),                // M_MONK_MEMBERS_JOIN_TIME
            iBranch,                // M_MONK_MEMBERS_BRANCH
            M_POSITION_MEMBER,      // M_MONK_MEMBERS_POSITION
            0,                      // M_MONK_MEMBERS_PUNISHMENTS
            ({ "", "", "", "" }),   // M_MONK_MEMBERS_TITLE
            TRUE                    // M_MONK_MEMBERS_LEARNING
          })
        ]);

      oWho->add_cmdsoul (M_SOUL);
      oWho->update_hooks ();

      oWho->clear_guild_stat (iBranch);
      oWho->set_guild_pref (iBranch, iTax);

      m_limit_skills (oWho);

      s_log (M_LOG_WIZARD | M_LOG_COUNCIL, sWhoCap + " joined the guild.");
      M_OBJ_BOARD_MEMBER->m_post_note (
        "New member: " + sWhoCap, M_SPIRIT_UPPER,
        dg_framed_text (
          "Welcome a new member of the Ancient Order of the Dragon ! " +
          XCPNOUN (oWho) + " is " +
          LANG_ADDART (dg_get_pretty_description (oWho)) + ", " +
          "going by the name of " + sWhoCap + ".\n"));

      M_SAVE_ACCESSED;
      return (FALSE);

    // All the remaining cases are failures.

    case  0: sMessage = "You are already a member of another guild.\n";
             break;
    case -4: sMessage = "Your other guilds do not allow you to join this guild.\n";
             break;
    default: sMessage = "A rift in the fabric of space does not allow you to join this guild.\n";
             break;
  }

  oShadow->remove_shadow ();
  return (sMessage);
}


/*
 * Function name : m_remove_monk
 * Returns       : Zero as an indication of success or an error message
 *
 */

mixed m_remove_monk (object oWho)
{
  M_ACCESS_MONK_MEMBERS;
  M_ACCESS_MONK_COUNCIL;

  string sWho = dg_get_name (oWho);
  string sWhoCap = capitalize (sWho);
  object oShadow;
  mixed  *axMember;
  int    iBranch;

  if (member_array (sWho, m_indices (mMonkMembers)) < 0)
  {
    return ("You not a member.\n");
  }

  axMember = mMonkMembers [sWho];
  iBranch = axMember [M_MONK_MEMBERS_BRANCH];

  M_DELETE_MONK_MEMBERS (sWho);
  M_DELETE_MONK_COUNCIL (sWho);

  // Remove the command soul and the shadow. Note that the shadow
  // itself is removed from an alarm, to prevent cutting a branch
  // that we might be sitting on.

  oWho->remove_cmdsoul (M_SOUL);
  oWho->update_hooks ();

  oShadow = oWho->m_query_shadow ();
  oWho->remove_autoshadow (MASTER_OB (oShadow));
  set_alarm (1.0, 0.0, &oShadow->remove_shadow ());

  // Clean up the stats and prefs and administer penalty for
  // leaving the guild, which is one sixth of combat exp.

  oWho->clear_guild_stat (iBranch);
  oWho->set_guild_pref (iBranch, 0);

  m_limit_skills (oWho);

  oWho->add_exp_combat (-(oWho->query_exp_combat ()) / 6);

  s_log (M_LOG_WIZARD | M_LOG_COUNCIL, sWhoCap + " left the guild.");

  M_SAVE_ACCESSED;
  return (FALSE);
}


/*
 * Function name : m_transfer_monk
 * Returns       : Zero as an indication of success or an error message
 *
 */

mixed m_transfer_monk (object oWho)
{
  M_ACCESS_MONK_MEMBERS;

  string sWho = dg_get_name (oWho);
  string sWhoCap = capitalize (sWho);
  mixed  *axMember;
  object oOldShadow, oNewShadow;
  int    iOldBranch, iNewBranch;
  int    iTax;
  string sType;
  string sStyle;
  string sMessage;

  if (member_array (sWho, m_indices (mMonkMembers)) < 0)
  {
    return ("You are not a member.\n");
  }

  axMember = mMonkMembers [sWho];
  iOldBranch = axMember [M_MONK_MEMBERS_BRANCH];
  oOldShadow = oWho->m_query_shadow ();

  switch (iOldBranch)
  {
    case SS_OCCUP:  iTax = M_TAX_LAY;
                    sType = M_TYPE_LAY;
                    sStyle = M_STYLE_LAY;
                    iNewBranch = SS_LAYMAN;
                    oNewShadow = clone_object (M_SHADOW_LAY);
                    break;

    case SS_LAYMAN: iTax = M_TAX_OCC;
                    sType = M_TYPE_OCC;
                    sStyle = M_STYLE_OCC;
                    iNewBranch = SS_OCCUP;
                    oNewShadow = clone_object (M_SHADOW_OCC);
                    break;
  }

  switch (oNewShadow->shadow_me (oWho, sType, sStyle, M_NAME_LONG))
  {
    case 1:

      // Update the guild membership record.

      axMember [M_MONK_MEMBERS_BRANCH] = iNewBranch;

      oWho->remove_autoshadow (MASTER_OB (oOldShadow));
      set_alarm (1.0, 0.0, &oOldShadow->remove_shadow ());

      oWho->set_guild_stat (iNewBranch, oWho->query_acc_exp (iOldBranch));
      oWho->clear_guild_stat (iOldBranch);
      oWho->set_guild_pref (iOldBranch, 0);
      oWho->set_guild_pref (iNewBranch, iTax);

      m_limit_skills (oWho);

      s_log (M_LOG_WIZARD, sWhoCap + " transferred a branch.");

      M_SAVE_ACCESSED;
      return (FALSE);

    // All the remaining cases are failures.

    case  0: sMessage = "You are already a member of another guild.\n";
             break;
    case -4: sMessage = "Your other guilds do not allow you to transfer in this guild.\n";
             break;
    default: sMessage = "A rift in the fabric of space does not allow you to transfer in this guild.\n";
             break;
  }

  oNewShadow->remove_shadow ();
  return (sMessage);
}


/*
 * Function name : m_get_monks
 *
 */

string *m_get_monks ()
{
  M_ACCESS_MONK_MEMBERS;

  return (m_indexes (mMonkMembers));
}


/*
 * Function name : m_is_monk
 *
 */

varargs int m_is_monk (mixed xWho, int iBranch = 0)
{
  M_ACCESS_MONK_MEMBERS;

  string sWho = objectp (xWho) ? dg_get_name (xWho) : xWho;

  if (member_array (sWho, m_indices (mMonkMembers)) >= 0)
  {
    return ((iBranch == 0) ||
            (mMonkMembers [sWho][M_MONK_MEMBERS_BRANCH] == iBranch));
  }
  else return (FALSE);
}

//-------------------------------------------------------------------

/*******************************************************************\
| Functions for managing elder membership                           |
\*******************************************************************/

/*
 * Function name : m_add_elder_member
 *
 */

void m_add_elder_member (mixed xWho)
{
  M_ACCESS_MONK_MEMBERS;

  string sWho = objectp (xWho) ? dg_get_name (xWho) : xWho;
  string sWhoCap = capitalize (sWho);

  if (member_array (sWho, m_indices (mMonkMembers)) >= 0)
  {
    mMonkMembers [sWho][M_MONK_MEMBERS_POSITION] |= M_POSITION_ELDER;
  }

  s_log (M_LOG_WIZARD | M_LOG_COUNCIL, sWhoCap + " was added to the elders.");

  M_SAVE_ACCESSED;
}


/*
 * Function name : m_remove_elder_member
 *
 */

void m_remove_elder_member (mixed xWho)
{
  M_ACCESS_MONK_MEMBERS;

  string sWho = objectp (xWho) ? dg_get_name (xWho) : xWho;
  string sWhoCap = capitalize (sWho);

  if (member_array (sWho, m_indices (mMonkMembers)) >= 0)
  {
    mMonkMembers [sWho][M_MONK_MEMBERS_POSITION] &= ~M_POSITION_ELDER;
  }

  s_log (M_LOG_WIZARD | M_LOG_COUNCIL, sWhoCap + " was removed from the elders.");

  M_SAVE_ACCESSED;
}


/*
 * Function name : m_get_elder_members
 *
 */

string *m_get_elder_members ()
{
  M_ACCESS_MONK_MEMBERS;

  string *asMembers = m_indices (mMonkMembers);
  string *asElders = ({ });
  string sMember;
  int    iMember;

  for (iMember = 0 ; iMember < sizeof (asMembers) ; iMember ++)
  {
    sMember = asMembers [iMember];
    if (mMonkMembers [sMember][M_MONK_MEMBERS_POSITION] & M_POSITION_ELDER)
    {
      asElders += ({ sMember });
    }
  }

  return (asElders);
}


/*
 * Function name : m_is_elder_member
 *
 */

int m_is_elder_member (mixed xWho)
{
  M_ACCESS_MONK_MEMBERS;

  string sWho = objectp (xWho) ? dg_get_name (xWho) : xWho;

  if (member_array (sWho, m_indices (mMonkMembers)) >= 0)
  {
    return (mMonkMembers [sWho][M_MONK_MEMBERS_POSITION] & M_POSITION_ELDER);
  }
  else return (FALSE);
}

//-------------------------------------------------------------------

/*******************************************************************\
| Functions for managing council membership                         |
\*******************************************************************/

/*
 * Function name : m_add_council_member
 *
 */

void m_add_council_member (mixed xWho)
{
  M_ACCESS_MONK_MEMBERS;
  M_ACCESS_MONK_COUNCIL;

  string sWho = objectp (xWho) ? dg_get_name (xWho) : xWho;
  string sWhoCap = capitalize (sWho);

  if (member_array (sWho, m_indices (mMonkMembers)) >= 0)
  {
    mMonkMembers [sWho][M_MONK_MEMBERS_POSITION] |= M_POSITION_COUNCIL;
  }

  // Note that the order of items in the structure must
  // correspond with the constants defined in the
  // include file.

  if (member_array (sWho, m_indices (mMonkCouncil)) >= 0)
  {
    // The councillor already exists, change the entry.

    mMonkCouncil [sWho] = ({ "", time () });
  }
  else
  {
    // The councillor does not exist yet, create a new entry.

    mMonkCouncil += ([ sWho : ({ "", time () }) ]);
  }

  s_log (M_LOG_WIZARD | M_LOG_COUNCIL, sWhoCap + " was added to the council.");

  M_SAVE_ACCESSED;
}


/*
 * Function name : m_remove_council_member
 *
 */

void m_remove_council_member (mixed xWho)
{
  M_ACCESS_MONK_MEMBERS;
  M_ACCESS_MONK_COUNCIL;

  string sWho = objectp (xWho) ? dg_get_name (xWho) : xWho;
  string sWhoCap = capitalize (sWho);

  if (member_array (sWho, m_indices (mMonkMembers)) >= 0)
  {
    mMonkMembers [sWho][M_MONK_MEMBERS_POSITION] &= ~M_POSITION_COUNCIL;
  }

  M_DELETE_MONK_COUNCIL (sWho);

  s_log (M_LOG_WIZARD | M_LOG_COUNCIL, sWhoCap + " was removed from the council.");

  M_SAVE_ACCESSED;
}


/*
 * Function name : m_get_council_members
 *
 */

string *m_get_council_members ()
{
  M_ACCESS_MONK_COUNCIL;

  return (m_indexes (mMonkCouncil));
}

/*
 * filter function for active players
 */
int m_is_active(string who)
{
  return (file_time(PLAYER_FILE(who)+".o") +
    M_MONK_ACTIVE_THRESHOLD * DG_SEC2DAY) > time();
}

/*
 * Function name : m_get_active_council_members
 *
 */

string *m_get_active_council_members()
{
  M_ACCESS_MONK_COUNCIL;

  return filter(m_indexes(mMonkCouncil), m_is_active);
}


/*
 * Function name : m_is_council_member
 *
 */

int m_is_council_member (mixed xWho)
{
  M_ACCESS_MONK_MEMBERS;

  string sWho = objectp (xWho) ? dg_get_name (xWho) : xWho;

  if (member_array (sWho, m_indices (mMonkMembers)) >= 0)
  {
    return (mMonkMembers [sWho][M_MONK_MEMBERS_POSITION] & M_POSITION_COUNCIL);
  }
  else return (FALSE);
}


/*
 * Function name : m_get_council_desc
 *
 */

string m_get_council_desc (mixed xWho)
{
  M_ACCESS_MONK_COUNCIL;

  string sWho = objectp (xWho) ? dg_get_name (xWho) : xWho;

  if (member_array (sWho, m_indices (mMonkCouncil)) >= 0)
  {
    return (mMonkCouncil [sWho][M_MONK_COUNCIL_DESC]);
  }
  else return ("");
}


/*
 * Function name : m_set_council_desc
 *
 */

void m_set_council_desc (mixed xWho, string sDesc)
{
  M_ACCESS_MONK_COUNCIL;

  string sWho = objectp (xWho) ? dg_get_name (xWho) : xWho;

  if (member_array (sWho, m_indices (mMonkCouncil)) >= 0)
  {
    mMonkCouncil [sWho][M_MONK_COUNCIL_DESC] = sDesc;
  }

  M_SAVE_ACCESSED;
}


/*
 * Function name : m_get_council_term
 *
 */

int m_get_council_term (mixed xWho)
{
  M_ACCESS_MONK_COUNCIL;

  string sWho = objectp (xWho) ? dg_get_name (xWho) : xWho;

  if (member_array (sWho, m_indices (mMonkCouncil)) >= 0)
  {
    return (mMonkCouncil [sWho][M_MONK_COUNCIL_TERM] + M_TERM_COUNCIL - time ());
  }
  else return (0);
}


/*
 * Function name : m_get_council_activity
 * Description   : Returns the time of the last council activity.
 *
 */

int m_get_council_activity ()
{
  M_ACCESS_MONK_GUILD;

  return (axMonkGuild [M_MONK_GUILD_COUNCIL]);
}

//-------------------------------------------------------------------

/*******************************************************************\
| Functions for managing former membership                          |
\*******************************************************************/

/*
 * Function name : m_get_former_descs
 *
 */

string *m_get_former_descs (int iMinPercentage, int iMaxPercentage)
{
  M_ACCESS_MONK_FORMER;

  mixed   *amRecords;
  string  *asDescriptions = ({ });
  int     iIndex;

  amRecords = m_values (mMonkFormer);

  for (iIndex = (sizeof (amRecords) * iMinPercentage) / 100 ;
       iIndex < (sizeof (amRecords) * iMaxPercentage) / 100 ;
       iIndex ++)
  {
    asDescriptions += ({ amRecords [iIndex][M_FORMER_MEMBERS_DESC] });
  }

  return (asDescriptions);
}

//-------------------------------------------------------------------

/*******************************************************************\
| Functions for punishments                                         |
\*******************************************************************/

void m_punish (mixed xWho, int iHow)
{
  M_ACCESS_MONK_MEMBERS;

  string sWho = objectp (xWho) ? dg_get_name (xWho) : xWho;

  if (member_array (sWho, m_indices (mMonkMembers)) >= 0)
  {
    mMonkMembers [sWho][M_MONK_MEMBERS_PUNISHMENTS] |= iHow;
  }

  M_SAVE_ACCESSED;
}


void m_reprieve (mixed xWho, int iHow)
{
  M_ACCESS_MONK_MEMBERS;

  string sWho = objectp (xWho) ? dg_get_name (xWho) : xWho;

  if (member_array (sWho, m_indices (mMonkMembers)) >= 0)
  {
    mMonkMembers [sWho][M_MONK_MEMBERS_PUNISHMENTS] &= ~iHow;
  }

  M_SAVE_ACCESSED;
}


string *m_get_punished ()
{
  M_ACCESS_MONK_MEMBERS;

  string *asMembers = m_indices (mMonkMembers);
  string *asPunished = ({ });
  string sMember;
  int    iMember;

  for (iMember = 0 ; iMember < sizeof (asMembers) ; iMember ++)
  {
    sMember = asMembers [iMember];
    if (mMonkMembers [sMember][M_MONK_MEMBERS_PUNISHMENTS])
    {
      asPunished += ({ sMember });
    }
  }

  return (asPunished);
}


int m_is_punished (mixed xWho, int iHow = ALLONES)
{
  M_ACCESS_MONK_MEMBERS;

  string sWho = objectp (xWho) ? dg_get_name (xWho) : xWho;

  if (member_array (sWho, m_indices (mMonkMembers)) >= 0)
  {
    return (mMonkMembers [sWho][M_MONK_MEMBERS_PUNISHMENTS] & iHow);
  }

  return (FALSE);
}


int m_get_punishment (mixed xWho)
{
  M_ACCESS_MONK_MEMBERS;

  string sWho = objectp (xWho) ? dg_get_name (xWho) : xWho;

  if (member_array (sWho, m_indices (mMonkMembers)) >= 0)
  {
    return (mMonkMembers [sWho][M_MONK_MEMBERS_PUNISHMENTS]);
  }

  return (0);
}

//-------------------------------------------------------------------

/*******************************************************************\
| Functions for titles                                              |
\*******************************************************************/

#define M_TITLE_CLASS_RANK               M_TITLE_BASE_RANK
#define M_TITLE_CLASS_CHAR               M_TITLE_BASE_CHAR
#define M_TITLE_CLASS_CLERGY             M_TITLE_BASE_CLERGY

#define M_TITLE_CLASS_STATS              "stats"
#define M_TITLE_CLASS_ELDER              "elder"
#define M_TITLE_CLASS_COUNCIL            "council"
#define M_TITLE_CLASS_BROTHERHOOD        "brotherhood"


/*
 * Function name : m_get_title_configuration
 *
 */

string *m_get_title_configuration (mixed xWho)
{
  M_ACCESS_MONK_MEMBERS;

  string sWho = objectp (xWho) ? dg_get_name (xWho) : xWho;

  if (member_array (sWho, m_indices (mMonkMembers)) >= 0)
  {
    return (mMonkMembers [sWho][M_MONK_MEMBERS_TITLE]);
  }
  else return (({ M_TITLE_ADJ_NONE, M_TITLE_BASE_CHAR,
                  M_TITLE_ADJ_RANK, M_TITLE_BASE_RANK }));
}


/*
 * Function name : m_set_title_configuration
 *
 */

void m_set_title_configuration (mixed xWho,
                                string sAdj1, string sBase1,
                                string sAdj2, string sBase2)
{
  M_ACCESS_MONK_MEMBERS;

  string sWho = objectp (xWho) ? dg_get_name (xWho) : xWho;

  if (member_array (sWho, m_indices (mMonkMembers)) >= 0)
  {
    mMonkMembers [sWho][M_MONK_MEMBERS_TITLE] = ({ sAdj1, sBase1,
                                                   sAdj2, sBase2 });
  }

  M_SAVE_ACCESSED;
}


/*
 * Function name : m_get_normalized_rank
 * Description   : Returns a numeric rank in the guild
 * Returns       : The rank from 0 to 100
 *
 */

int m_get_normalized_rank (object oWho)
{
  M_ACCESS_MONK_MEMBERS;

  string sWho = dg_get_name (oWho);

  int    iStrikeSkill, iPlexusSkill, iUnarmedSkill;
  int    iAge;
  int    iTime;
  int    iGuildStat;
  int    iGuildBonus;

  float  fAgeFactor;
  float  fStatFactor;
  float  fSkillFactor;
  float  fSkillCeiling;

  mixed  *axMember;

  iStrikeSkill = oWho->query_skill (M_SKILL_STRIKE);
  iPlexusSkill = oWho->query_skill (M_SKILL_PLEXUS);
  iUnarmedSkill = oWho->query_skill (SS_UNARM_COMBAT);

  if (member_array (sWho, m_indexes (mMonkMembers)) >= 0)
  {
    // This branch is for players to have a correct title.

    axMember = mMonkMembers [sWho];

    iGuildStat = oWho->query_stat (axMember [M_MONK_MEMBERS_BRANCH]);
    iAge = oWho->query_age () - axMember [M_MONK_MEMBERS_JOIN_AGE];
    iTime = time () - axMember [M_MONK_MEMBERS_JOIN_TIME];

    switch (axMember [M_MONK_MEMBERS_BRANCH])
    {
      case SS_OCCUP:  fSkillCeiling = itof (M_SKILL_MAX_OCC_STRIKE +
                                            M_SKILL_MAX_OCC_PLEXUS +
                                            M_SKILL_MAX_OCC_UNARMED);
                      break;

      case SS_LAYMAN: fSkillCeiling = itof (M_SKILL_MAX_LAY_STRIKE +
                                            M_SKILL_MAX_LAY_PLEXUS +
                                            M_SKILL_MAX_LAY_UNARMED);
                      break;
    }
  }
  else
  {
    // This branch is for monsters to have a decent title.

    iGuildStat = 80;
    iAge = 20 * DG_SEC2DAY / F_SECONDS_PER_BEAT;
    iTime = 1 * DG_SEC2YRS;

    fSkillCeiling = itof (M_SKILL_MAX_OCC_STRIKE +
                          M_SKILL_MAX_OCC_PLEXUS +
                          M_SKILL_MAX_OCC_UNARMED);
  }

  // The formula to calculate the rank was chosen so that
  // it starts at 0 for a novice monk, arrives at 50 for
  // an average monk, and reaches 90 for a big monk.

  // The main factors are guild stat and age once
  // all the skills are maxed as they should be.

  fAgeFactor = pow ( itof (iAge * F_SECONDS_PER_BEAT) +
                     itof (iTime / 7), 0.5
                   ) / 200.0;

  fStatFactor = itof (iGuildStat) / 4.0;

  fSkillFactor = itof (iStrikeSkill + iPlexusSkill + iUnarmedSkill) / fSkillCeiling;

  return (MIN (100, ftoi ((fAgeFactor + fStatFactor) * fSkillFactor)));
}


/*
 * Function name : m_get_title_rank_list
 * Description   : Returns a list of available rank titles
 *
 */

string *m_get_title_rank_list (int iRank)
{
  string *asResult = ({ });

  // Note the importance of the order and missing breaks !

  switch (iRank)
  {
    case 45 .. 100 : asResult += ({ "Monk of the Dragon Order" });
    case 34 .. 44  : asResult += ({ "Disciple of the Dragon Order" });
    case 23 .. 33  : asResult += ({ "Initiate of the Dragon Order" });
    case 12 .. 22  : asResult += ({ "Seeker of the Dragon Order" });
    case  0 .. 11  : asResult += ({ "Novice of the Dragon Order" });
  }

  return (asResult);
}


/*
 * Function name : m_get_title_rank_adjective
 * Description   : Returns a rank adjective
 *
 */

string m_get_title_rank_adjective (int iRank)
{
  switch (iRank)
  {
    case 0: return ("Utter");

    case 1 .. 55:

      return (({
                 "Fresh",      "Young",     "Hopeful",
                 "Promising",  "Aspiring",  "Attentive",
                 "Studious",   "Adept",     "Skilled",
                 "Seasoned",   "Insightful"
              })
                 [ (iRank - 1) % 11 ]);

    case 56 .. 59: return ("Insightful");
    case 60 .. 64: return ("Learned");
    case 65 .. 69: return ("Respected");
    case 70 .. 74: return ("Illustrious");
    case 75 .. 79: return ("Distinguished");
    case 80 .. 84: return ("Renowned");
    case 85 .. 89: return ("Revered");
    default:       return ("Ancient");
  }
}


/*
 * Function name : m_get_title_elder_list
 * Description   : Returns a list of available elder titles
 *
 */

string *m_get_title_elder_list (object oWho)
{
  string *asResult = ({ });

  if (m_is_elder_member (oWho))
  {

    // Standard title for the elder members

    asResult += ({
      "Elder of the Dragon Order"
    });
  }

  return (asResult);
}


/*
 * Function name : m_get_title_council_list
 * Description   : Returns a list of available council titles
 *
 */

string *m_get_title_council_list (object oWho)
{
  string *asResult = ({ });

  if (m_is_council_member (oWho))
  {

    // Standard title for the council members

    asResult += ({
      "Councillor of the Dragon Order"
    });

    // Additional titles for the council members

    asResult += ({
      "Body of the Dragon",
      "Claw of the Dragon",
      "Ear of the Dragon",
      "Eye of the Dragon",
      "Flame of the Dragon",
      "Heart of the Dragon",
      "Joy of the Dragon",
      "Mind of the Dragon",
      "Passion of the Dragon",
      "Rage of the Dragon",
      "Soul of the Dragon",
      "Talon of the Dragon",
      "Tear of the Dragon",
      "Tooth of the Dragon",
      "Will of the Dragon",
      "Wing of the Dragon",
      "Wrath of the Dragon"
    });
  }

  return (asResult);
}


/*
 * Function name : m_get_title_brotherhood_list
 * Description   : Returns a list of available brotherhood titles
 *
 */

string *m_get_title_brotherhood_list (object oWho, int iRank)
{
  string *asResult = ({ });

  if (iRank == M_TITLE_SELECT_ALL)
  {
    // Standard title for the brotherhood members.

    asResult += ({
      DG_GENDER_SWITCH (oWho, "Brother", "Sister") + " of Dragons" });

    // Nature phenomenon titles for the brotherhood members.

    asResult += ({
      "Pilgrim of Cold Springs",
      "Pilgrim of Flooded Rivers",
      "Pilgrim of Vast Rivers",
      "Pilgrim of Clear Lakes",
      "Pilgrim of Deep Oceans",
      "Pilgrim of Deep Waters",
      "Pilgrim of Steep Cliffs",
      "Pilgrim of White Cliffs",
      "Pilgrim of Steep Hills",
      "Pilgrim of Jagged Peaks",
      "Pilgrim of Grassy Plains",
      "Pilgrim of Silent Forests",
      "Pilgrim of Deep Forests",
      "Pilgrim of Long Roads",
      "Pilgrim of Muddy Roads",
      "Pilgrim of Dusty Roads",
      "Pilgrim of Winding Roads",
      "Pilgrim of Cave Echoes"
    });

    // Time of day titles for the brotherhood members.

    asResult += ({
      "Pilgrim of Cold Mornings",
      "Pilgrim of Red Sunrise",
      "Pilgrim of Distant Clouds",
      "Pilgrim of Coppery Sunset",
      "Pilgrim of Evening Fire"
    });

    // Time of year titles for the brotherhood members.

    asResult += ({
      "Pilgrim of Spring Floods",
      "Pilgrim of Spring Flowers",
      "Pilgrim of Melting Snowcaps",
      "Pilgrim of Autumn Rain",
      "Pilgrim of Autumn Trees",
      "Pilgrim of Autumn Leaves",
      "Pilgrim of Falling Leaves",
      "Pilgrim of Migrating Birds",
      "Pilgrim of Deep Snow",
      "Pilgrim of Winter Fire",
      "Pilgrim of Falling Snowflakes"
    });
  }

  return (asResult);
}


/*
 * Function name : m_get_title_clergy_list
 * Description   : Returns a list of available clergy titles
 *
 */

string *m_get_title_clergy_list (object oWho, int iRank)
{
  string *asResult = ({ });

  // Note the importance of the order and missing breaks !

  switch (iRank)
  {
    case 91 .. 100: asResult += ({ "Dancer on the West Wind" });
    case 81 .. 90:  asResult += ({ DG_GENDER_SWITCH (oWho, "Dragonmaster", "Dragonmistress") + " of the Tempest Moon" });
    case 71 .. 80:  asResult += ({ DG_GENDER_SWITCH (oWho, "Dragonmaster", "Dragonmistress") + " of the Harvest Twilight" });
    case 61 .. 70:  asResult += ({ DG_GENDER_SWITCH (oWho, "Dragonmaster", "Dragonmistress") + " of the Elyzerin Sun" });
    case 56 .. 60:  asResult += ({ DG_GENDER_SWITCH (oWho, "Dragonmaster", "Dragonmistress") + " of the Rising Dawn" });
    case 51 .. 55:  asResult += ({ "Dragon Sage of the Ancient Gremayre" });
    case 46 .. 50:  asResult += ({ "Dragon Adept of the Chimerical Vision" });
    case 41 .. 45:  asResult += ({ DG_GENDER_SWITCH (oWho, "Master", "Mistress") + " of Mysteries" });
    case 36 .. 40:  asResult += ({ "Adept of Mysteries" });
    case 31 .. 35:  asResult += ({ "Initiate of Mysteries" });
    case 26 .. 30:  asResult += ({ "Disciple of Dragons" });
    case 21 .. 25:  asResult += ({ "Initiate of Dragons" });
    case 16 .. 20:  asResult += ({ DG_GENDER_SWITCH (oWho, "Loremaster", "Loremistress") + " of Segoy" });
    case 11 .. 15:  asResult += ({ "Learned of Segoy" });
    case  6 .. 10:  asResult += ({ "Seeker of Segoy" });
    default:        asResult += ({ "Fledgling of Segoy" });
  }

  return (asResult);
}


/*
 * Function name : m_get_title_stats_list
 * Description   : Returns a list of available stats titles
 *
 */

string *m_get_title_stats_list (object oWho)
{
  M_ACCESS_MONK_GUILD;
  M_ACCESS_MONK_MEMBERS;

  string sWho = dg_get_name (oWho);

  mixed  *axMember;
  string *asResult = ({ });

  if (member_array (sWho, m_indexes (mMonkMembers)) >= 0)
  {
    axMember = mMonkMembers [sWho];

    if (itof (oWho->query_base_stat (SS_STR)) >= axMonkGuild [M_MONK_GUILD_STATS][M_STAT_STR])
      asResult += ({ "Guardian of Dragon Strength" });
    if (itof (oWho->query_base_stat (SS_DEX)) >= axMonkGuild [M_MONK_GUILD_STATS][M_STAT_DEX])
      asResult += ({ "Guardian of Dragon Grace" });
    if (itof (oWho->query_base_stat (SS_CON)) >= axMonkGuild [M_MONK_GUILD_STATS][M_STAT_CON])
      asResult += ({ "Guardian of Dragon Endurance" });
    if (itof (oWho->query_base_stat (SS_INT)) >= axMonkGuild [M_MONK_GUILD_STATS][M_STAT_INT])
      asResult += ({ "Guardian of Dragon Brilliance" });
    if (itof (oWho->query_base_stat (SS_WIS)) >= axMonkGuild [M_MONK_GUILD_STATS][M_STAT_WIS])
      asResult += ({ "Guardian of Dragon Knowledge" });
    if (itof (oWho->query_base_stat (SS_DIS)) >= axMonkGuild [M_MONK_GUILD_STATS][M_STAT_DIS])
      asResult += ({ "Guardian of Dragon Valor" });

    if (itof (sizeof (M_SHADOW_SRVR->m_get_kins (oWho))) >= axMonkGuild [M_MONK_GUILD_KINS])
      asResult += ({ "Nexus of Dragon Kinship" });

    if ((itof (oWho->query_age () - axMember [M_MONK_MEMBERS_JOIN_AGE]) >= axMonkGuild [M_MONK_GUILD_AGE]) ||
        (itof (time () - axMember [M_MONK_MEMBERS_JOIN_TIME]) >= axMonkGuild [M_MONK_GUILD_TIME]))
    {
      asResult += ({ "Nexus of Dragon Memories" });
    }
  }

  return (asResult);
}


/*
 * Function name : m_get_title_alignment_adjective
 * Description   : Returns an alignment adjective
 *
 */

string m_get_title_alignment_adjective (object oWho)
{
  switch (oWho->query_alignment ())
  {
    case 860 .. 1200:   return ("Resplendent");
    case 600 .. 859:    return ("Radiant");
    case 400 .. 599:    return ("Luminescent");
    case 200 .. 399:    return ("Lustrous");
    case -199 .. 199:   return ("Shadowwalking");
    case -399 .. -200:  return ("Onyx");
    case -599 .. -400:  return ("Ebon");
    case -859 .. -600:  return ("Obsidian");
    case -1200 .. -860: return ("Stygian");
  }
  return ("");
}


/*
 * Function name : m_get_normalized_character
 * Description   : Returns a normalized value of the most
 *                 distinguished character trait
 * Returns       : Integer array of the most distinguished
 *                 character trait and its normalized value
 *
 */

int *m_get_normalized_character (object oWho)
{
  M_ACCESS_MONK_GUILD;

  mixed *axCharacter;
  int iNormalized;
  int *aiNormalized;
  float fGuildPositive;
  float fGuildNegative;
  int iTrait;

  // Normalize the values in the character array by making them
  // relative to the recently observed maximum guild values and
  // by subtracting the negative ones from the positive ones.

  // The recently observed maximum guild values are adjusted
  // so that positives and negatives never differ by a factor
  // greater than three. This is to avoid overreacting on idle
  // traits.

  aiNormalized = ({ });

  axCharacter = M_SHADOW_SRVR->m_get_character (oWho);

  if (pointerp (axCharacter))
  {
    for (iTrait = 0 ; iTrait < sizeof (axCharacter [0]) ; iTrait ++)
    {
      fGuildPositive = MAX (1.0,
                            MAX (axMonkGuild [M_MONK_GUILD_CHARACTER][0][iTrait],
                                 axMonkGuild [M_MONK_GUILD_CHARACTER][1][iTrait] / 3.0));
      fGuildNegative = MAX (1.0,
                            MAX (axMonkGuild [M_MONK_GUILD_CHARACTER][1][iTrait],
                                 axMonkGuild [M_MONK_GUILD_CHARACTER][0][iTrait] / 3.0));

      iNormalized = ftoi ((itof (axCharacter [0][iTrait]) / fGuildPositive) * 100.0 -
                          (itof (axCharacter [1][iTrait]) / fGuildNegative) * 100.0);

      iNormalized = MAX (iNormalized, -100);
      iNormalized = MIN (iNormalized, 100);

      aiNormalized += ({ iNormalized });
    }
  }

  return (aiNormalized);
}


/*
 * Function name : m_get_distinguishing_character
 * Description   : Returns a normalized value of the most
 *                 distinguishing character trait
 * Returns       : Integer array of the most distinguished
 *                 character trait and its normalized value
 *
 */

int *m_get_distinguishing_character (object oWho)
{
  int *aiNormalized;
  int iBestTrait;
  int iBestValue;
  int iTrait;

  // Pick the most significant trait of the normalized
  // character array, which will determine the title.

  aiNormalized = m_get_normalized_character (oWho);

  iBestTrait = 0;
  iBestValue = 0;

  for (iTrait = 0 ; iTrait < sizeof (aiNormalized) ; iTrait ++)
  {
    if (ABS (aiNormalized [iTrait]) > ABS (iBestValue))
    {
      iBestTrait = iTrait;
      iBestValue = aiNormalized [iTrait];
    }
  }

  return (({ iBestTrait, iBestValue }));
}


/*
 * Function name : m_get_title_character_short
 * Description   : Returns the short character title
 *
 */

string m_get_title_character_short (int iTrait, int iValue)
{
  switch (iTrait)
  {
    case M_TRAIT_PERFECTION:
      switch (iValue)
      {
        case -100 .. -90: return ("Pariah");
        case  -89 .. -79: return ("Shunned");
        case  -78 .. -68: return ("Disfavored");
        case  -67 .. -57: return ("Insensitive");
        case  -56 .. -45: return ("Indifferent");
        case  -44 .. -33: return ("Careless");
        case  -32 .. -21: return ("Blunt");
        case  -20 .. -9:  return ("Candid");
        case   -8 .. 8:   return ("Unremarked");
        case    9 .. 20:  return ("Favored");
        case   21 .. 32:  return ("Laudable");
        case   33 .. 44:  return ("Acclaimed");
        case   45 .. 56:  return ("Meritorious");
        case   57 .. 67:  return ("Illustrious");
        case   68 .. 78:  return ("Cherished");
        case   79 .. 89:  return ("Venerated");
        case   90 .. 100: return ("Hallowed");
      }
      return ("");

    case M_TRAIT_HONESTY:
      switch (iValue)
      {
        case -100 .. -90: return ("Nefarious");
        case  -89 .. -79: return ("Duplicitous");
        case  -78 .. -68: return ("Shifty");
        case  -67 .. -57: return ("Shrewd");
        case  -56 .. -45: return ("Cagey");
        case  -44 .. -33: return ("Wily");;
        case  -32 .. -21: return ("Artful");
        case  -20 .. -9:  return ("Crafty");
        case   -8 .. 8:   return ("Drifting");
        case    9 .. 20:  return ("Direct");
        case   21 .. 32:  return ("Mindful");
        case   33 .. 44:  return ("Reputable");
        case   45 .. 56:  return ("Reliable");
        case   57 .. 67:  return ("Fortright");
        case   68 .. 78:  return ("Genuine");
        case   79 .. 89:  return ("Ethical");
        case   90 .. 100: return ("Virtuous");
      }
      return ("");

    case M_TRAIT_EFFORT:
      switch (iValue)
      {
        case -100 .. -90: return ("Faineant");
        case  -89 .. -79: return ("Indolent");
        case  -78 .. -68: return ("Sluggish");
        case  -67 .. -57: return ("Lackadaisical");
        case  -56 .. -45: return ("Resting");
        case  -44 .. -33: return ("Dreaming");
        case  -32 .. -21: return ("Preoccupied");
        case  -20 .. -9:  return ("Watchful");
        case   -8 .. 8:   return ("Simmering");
        case    9 .. 20:  return ("Effective");
        case   21 .. 32:  return ("Quickwitted");
        case   33 .. 44:  return ("Bustling");
        case   45 .. 56:  return ("Swift");
        case   57 .. 67:  return ("Restless");
        case   68 .. 78:  return ("Mercurial");
        case   79 .. 89:  return ("Impelling");
        case   90 .. 100: return ("Dynamic");
      }
      return ("");

    case M_TRAIT_RESPECT:
      switch (iValue)
      {
        case -100 .. -90: return ("Brazen");
        case  -89 .. -79: return ("Defiant");
        case  -78 .. -68: return ("Impertinent");
        case  -67 .. -57: return ("Flippant");
        case  -56 .. -45: return ("Impudent");
        case  -44 .. -33: return ("Brash");
        case  -32 .. -21: return ("Cheeky");
        case  -20 .. -9:  return ("Teasing");
        case   -8 .. 8:   return ("Unvarnished");
        case    9 .. 20:  return ("Urbane");
        case   21 .. 32:  return ("Considerate");
        case   33 .. 44:  return ("Gallant");
        case   45 .. 56:  return ("Affable");
        case   57 .. 67:  return ("Magnanimous");
        case   68 .. 78:  return ("Reverential");
        case   79 .. 89:  return ("Gracious");
        case   90 .. 100: return ("Courtly");
      }
      return ("");

    case M_TRAIT_PEACEFULNESS:
      switch (iValue)
      {
        case -100 .. -90: return ("Merciless");
        case  -89 .. -79: return ("Voracious");
        case  -78 .. -68: return ("Feral");
        case  -67 .. -57: return ("Savage");
        case  -56 .. -45: return ("Vicious");
        case  -44 .. -33: return ("Fierce");
        case  -32 .. -21: return ("Menacing");
        case  -20 .. -9:  return ("Impulsive");
        case   -8 .. 8:   return ("Grim");
        case    9 .. 100: return ("");
      }
      return ("");
  }

  return ("");
}


/*
 * Function name : m_get_title_character_long
 * Description   : Returns the long character title
 *
 */

string m_get_title_character_long (int iTrait, int iValue)
{
  switch (iTrait)
  {
    case M_TRAIT_PERFECTION:
      switch (iValue)
      {
        case -100 .. -90: return ("Repulsive Gust of Dragon Breath");
        case  -89 .. -75: return ("Stench of Rotting Dragon Egg");
        case  -74 .. -50: return ("Remnants of Chewed Dragon Bone");
        case  -49 .. 49:  return ("Mellow Shade of Dragon");
        case   50 .. 74:  return ("Faint Glitter of Dragon Scales");
        case   75 .. 89:  return ("Welcome Sparkle of Dragon Smile");
        case   90 .. 100: return ("Revered Warmth of Dragon Kinship");
      }
      return ("");

    case M_TRAIT_HONESTY:
      switch (iValue)
      {
        case -100 .. -90: return ("Everchanging Morass of Dragon Lies");
        case  -89 .. -75: return ("Beguiling Swamp of Dragon Night");
        case  -74 .. -50: return ("Wavering Flame of Dragon Mirage");
        case  -49 .. 49:  return ("Mellow Shade of Dragon");
        case   50 .. 74:  return ("Steadfast Walker of Dragon Path");
        case   75 .. 89:  return ("Sheltering Oak of Dragon Rest");
        case   90 .. 100: return ("Constant Light of Dragon Heart");
      }
      return ("");

    case M_TRAIT_EFFORT:
      switch (iValue)
      {
        case -100 .. -90: return ("Sleepy Dweller of Dragon Racks");
        case  -89 .. -75: return ("Lazy Watcher of Dragon Lair");
        case  -74 .. -50: return ("Silent Dreamer of Dragon Dream");
        case  -49 .. 49:  return ("Mellow Shade of Dragon");
        case   50 .. 74:  return ("Smouldering Spark of Dragon Fire");
        case   75 .. 89:  return ("Bright Blaze of Dragon Heavens");
        case   90 .. 100: return ("Tireless Chaser of Dragon Stars");
      }
      return ("");

    case M_TRAIT_RESPECT:
      switch (iValue)
      {
        case -100 .. -90: return ("Sneering Grimace of Dragon Disdain");
        case  -89 .. -75: return ("Mannerless Oaf of Dragon Arrogance");
        case  -74 .. -50: return ("Impish Child of Dragon Impatience");
        case  -49 .. 49:  return ("Mellow Shade of Dragon");
        case   50 .. 74:  return ("Courtly Spiral of Dragon Flight");
        case   75 .. 89:  return ("Gentle Soul of Dragon Dignity");
        case   90 .. 100: return ("Temperate Ocean of Dragon Harmony");
      }
      return ("");

    case M_TRAIT_PEACEFULNESS:
      switch (iValue)
      {
        case -100 .. -90: return ("Bloodthirsty Scream of Dragon Retribution");
        case  -89 .. -75: return ("Vengeful Bringer of Dragon Fate");
        case  -74 .. -50: return ("Taloned Heart of Dragon Rage");
        case  -49 .. 100: return ("Mellow Shade of Dragon");
      }
      return ("");
  }

  return ("");
}


/*
 * Function name : m_validate_title_adjective
 * Function name : m_validate_title_base
 * Function name : m_validate_title_ranking
 * Function name : m_validate_title_combination
 * Description   : Helper functions for validating a specific title
 *
 */

mixed m_validate_title_adjective (
  string sPosition,
  string sAdj)
{
  sAdj = lower_case (sAdj);

  if ((sAdj != M_TITLE_ADJ_NONE) &&
      (sAdj != M_TITLE_ADJ_RANK) &&
      (sAdj != M_TITLE_ADJ_CHAR) &&
      (sAdj != M_TITLE_ADJ_ALIGN))
  {
    return ("The " + sPosition + " adjective part of the title is invalid.\n");
  }

  return (({ sAdj }));
}


mixed m_validate_title_base (
  string sPosition,
  string sBase,
  object oWho,
  int iRank)
{
  string sClass;
  string sCapitalized;
  int    iDecapitalized;
  string *asCapitalized;
  string *asDecapitalized;

  sBase = lower_case (sBase);

  if ((sBase == M_TITLE_BASE_RANK) ||
      (sBase == M_TITLE_BASE_CHAR) ||
      (sBase == M_TITLE_BASE_CLERGY))
  {
    // Generic classes are inherently valid.

    sClass = sBase;
    sCapitalized = sBase;
  }
  else
  {
    // Specific titles must be located in generic classes.

    asCapitalized = m_get_title_rank_list (iRank);
    asDecapitalized = dg_decapitalize_array (asCapitalized);
    iDecapitalized = member_array (sBase, asDecapitalized);
    if (iDecapitalized >= 0)
    {
      sClass = M_TITLE_CLASS_RANK;
      sCapitalized = asCapitalized [iDecapitalized];
    }
    else
    {
      asCapitalized = m_get_title_clergy_list (oWho, iRank);
      asDecapitalized = dg_decapitalize_array (asCapitalized);
      iDecapitalized = member_array (sBase, asDecapitalized);
      if (iDecapitalized >= 0)
      {
        sClass = M_TITLE_CLASS_CLERGY;
        sCapitalized = asCapitalized [iDecapitalized];
      }
      else
      {
        asCapitalized = m_get_title_stats_list (oWho);
        asDecapitalized = dg_decapitalize_array (asCapitalized);
        iDecapitalized = member_array (sBase, asDecapitalized);
        if (iDecapitalized >= 0)
        {
          sClass = M_TITLE_CLASS_STATS;
          sCapitalized = asCapitalized [iDecapitalized];
        }
        else
        {
          asCapitalized = m_get_title_elder_list (oWho);
          asDecapitalized = dg_decapitalize_array (asCapitalized);
          iDecapitalized = member_array (sBase, asDecapitalized);
          if (iDecapitalized >= 0)
          {
            sClass = M_TITLE_CLASS_ELDER;
            sCapitalized = asCapitalized [iDecapitalized];
          }
          else
          {
            asCapitalized = m_get_title_council_list (oWho);
            asDecapitalized = dg_decapitalize_array (asCapitalized);
            iDecapitalized = member_array (sBase, asDecapitalized);
            if (iDecapitalized >= 0)
            {
              sClass = M_TITLE_CLASS_COUNCIL;
              sCapitalized = asCapitalized [iDecapitalized];
            }
            else
            {
              asCapitalized = m_get_title_brotherhood_list (oWho, iRank);
              asDecapitalized = dg_decapitalize_array (asCapitalized);
              iDecapitalized = member_array (sBase, asDecapitalized);
              if (iDecapitalized >= 0)
              {
                sClass = M_TITLE_CLASS_BROTHERHOOD;
                sCapitalized = asCapitalized [iDecapitalized];
              }
              else
              {
                return ("The " + sPosition + " base part of the title is invalid.\n");
              }
            }
          }
        }
      }
    }
  }

  return (({ sClass, sCapitalized }));
}


mixed m_validate_title_ranking (
  string sPosition,
  string sBase,
  string sClass,
  int iRank)
{
  if (((iRank < M_TITLE_SELECT_FEW) &&
       (sBase != M_TITLE_BASE_RANK) &&
       (sBase != M_TITLE_BASE_CHAR) &&
       (sBase != M_TITLE_BASE_CLERGY))
      &&
      ((iRank < M_TITLE_SELECT_ALL) &&
       (sClass != M_TITLE_CLASS_RANK) &&
       (sClass != M_TITLE_CLASS_CLERGY))
      &&
      ((sClass != M_TITLE_CLASS_STATS) &&
       (sClass != M_TITLE_CLASS_ELDER) &&
       (sClass != M_TITLE_CLASS_COUNCIL) &&
       (sClass != M_TITLE_CLASS_BROTHERHOOD)))
  {
    return ("The " + sPosition + " base part of the title is invalid.\n");
  }

  return (0);
}


mixed m_validate_title_combination (
  string sBase,
  string sClass,
  string sAdj,
  int iRank)
{
  if (((sClass == M_TITLE_CLASS_RANK) &&
       ((sAdj == M_TITLE_ADJ_NONE) && (iRank < M_TITLE_SELECT_ALL)))
      ||
      ((sClass == M_TITLE_CLASS_CHAR) &&
       (sAdj != M_TITLE_ADJ_NONE))
      ||
      (((sClass == M_TITLE_CLASS_CLERGY) ||
        (sClass == M_TITLE_CLASS_STATS) ||
        (sClass == M_TITLE_CLASS_ELDER) ||
        (sClass == M_TITLE_CLASS_COUNCIL) ||
        (sClass == M_TITLE_CLASS_BROTHERHOOD)) &&
       (sAdj == M_TITLE_ADJ_RANK)))
  {
    return ("The combination of base part '" + sBase + "' with adjective part '" + sAdj + "' is invalid.\n");
  }

  return (0);
}


/*
 * Function name : m_validate_title
 * Description   : Validates a specific title
 *   oWho          : Whose title to validate
 *   sAdj1         : Adjective of first part
 *   sBase1        : Base of first part
 *   sAdj2         : Adjective of second part
 *   sBase2        : Base of second part
 * Returns       : Zero as an indication of success or an error message
 *
 */


mixed m_validate_title (object oWho, string sAdj1, string sBase1,
                                     string sAdj2, string sBase2)
{
  int iRank;
  string sClass1;
  string sClass2;
  string sCapitalized1;
  string sCapitalized2;
  mixed xResult;

  iRank = m_get_normalized_rank (oWho);

  // Basic sanity checks on first pair of arguments.

  xResult = m_validate_title_adjective ("first", sAdj1);
  if (stringp (xResult)) return (xResult);
  sAdj1 = xResult [0];

  xResult = m_validate_title_base ("first", sBase1, oWho, iRank);
  if (stringp (xResult)) return (xResult);
  sClass1 = xResult [0];
  sCapitalized1 = xResult [1];

  // Basic sanity checks on second pair of arguments.

  if (strlen (sBase2))
  {
    xResult = m_validate_title_adjective ("second", sAdj2);
    if (stringp (xResult)) return (xResult);
    sAdj2 = xResult [0];

    xResult = m_validate_title_base ("second", sBase2, oWho, iRank);
    if (stringp (xResult)) return (xResult);
    sClass2 = xResult [0];
    sCapitalized2 = xResult [1];
  }
  else
  {
    sAdj2 = "";
    sClass2 = "";
    sCapitalized2 = "";
  }

  // Basic sanity checks on both pairs of arguments.

  if ((sAdj1 == sAdj2) &&
      (sAdj1 != M_TITLE_ADJ_NONE) &&
      (sAdj2 != M_TITLE_ADJ_NONE))
  {
    return ("The adjective parts of the title cannot be the same.\n");
  }

  if (sCapitalized1 == sCapitalized2)
  {
    return ("The base parts of the title cannot be the same.\n");
  }

  // Configuration restrictions depend on rank.

  if (iRank < 40)
  {
    if ((sClass1 != M_TITLE_CLASS_RANK) && (sClass2 != M_TITLE_CLASS_RANK))
    {
      return ("One of the base parts of the title must be '" + M_TITLE_BASE_RANK + "'.\n");
    }
  }

  if (iRank < 55)
  {
    if (((sClass1 != M_TITLE_CLASS_CHAR) && (sClass2 != M_TITLE_CLASS_CHAR)) &&
        ((sAdj1 != M_TITLE_ADJ_CHAR) && (sAdj2 != M_TITLE_ADJ_CHAR)))
    {
      return ("One of the base parts of the title must be '" + M_TITLE_BASE_CHAR + "', " +
              "or one of the adjectives of the title must be '" + M_TITLE_ADJ_CHAR + "'.\n");
    }
  }

  if (iRank < 70)
  {
    if (!strlen (sBase2))
    {
      return ("The second base part of the title cannot be empty.\n");
    }
  }

  // Specific titles can be selected only when available in ranking.
  // Only some combinations of base part and adjective part are valid.

  xResult = m_validate_title_ranking ("first", sBase1, sClass1, iRank);
  if (stringp (xResult)) return (xResult);

  xResult = m_validate_title_combination (sBase1, sClass1, sAdj1, iRank);
  if (stringp (xResult)) return (xResult);

  if (strlen (sBase2))
  {
    xResult = m_validate_title_ranking ("second", sBase2, sClass2, iRank);
    if (stringp (xResult)) return (xResult);

    xResult = m_validate_title_combination (sBase2, sClass2, sAdj2, iRank);
    if (stringp (xResult)) return (xResult);
  }

  return (({ sAdj1, sCapitalized1, sAdj2, sCapitalized2 }));
}


/*
 * Function name : m_expand_title_base
 * Function name : m_expand_title_adjective
 * Description   : Helper functions for returning a title
 *
 */

string m_expand_title_base (string sBase, object oWho, int iRank, int iTrait, int iValue)
{
  if (sBase == M_TITLE_BASE_RANK) return (m_get_title_rank_list (iRank) [0]);
  if (sBase == M_TITLE_BASE_CHAR) return (m_get_title_character_long (iTrait, iValue));
  if (sBase == M_TITLE_BASE_CLERGY) return (m_get_title_clergy_list (oWho, iRank) [0]);

  return (sBase);
}


string m_expand_title_adjective (string sAdj, object oWho, int iRank, int iTrait, int iValue)
{
  if (sAdj == M_TITLE_ADJ_NONE) return ("");
  if (sAdj == M_TITLE_ADJ_RANK) return (m_get_title_rank_adjective (iRank));
  if (sAdj == M_TITLE_ADJ_CHAR) return (m_get_title_character_short (iTrait, iValue));
  if (sAdj == M_TITLE_ADJ_ALIGN) return (m_get_title_alignment_adjective (oWho));

  return (sAdj);
}


/*
 * Function name : m_get_title
 * Description   : Returns a title
 *
 */

string m_get_title (object oWho)
{
  int    iRank;
  int    *aiCharacter;
  string *asTitleConfiguration;

  string sAdj;
  string sTitle;

  iRank = m_get_normalized_rank (oWho);
  aiCharacter = m_get_distinguishing_character (oWho);
  asTitleConfiguration = m_get_title_configuration (oWho);

  sTitle = "";

  // First part of the title. Can replace adjective with punishment.

  if (m_is_punished (oWho, M_PUNISH_DISGRACE))
  {
    sAdj = "Disgraced";
  }
  else
  {
    sAdj = m_expand_title_adjective (asTitleConfiguration [0], oWho, iRank, aiCharacter [0], aiCharacter [1]);
  }
  if (strlen (sAdj)) sTitle += sAdj + " ";
  sTitle += m_expand_title_base (asTitleConfiguration [1], oWho, iRank, aiCharacter [0], aiCharacter [1]);

  // Second part of the title. Can be optional.

  if (strlen (asTitleConfiguration [2] + asTitleConfiguration [3]))
  {
    sTitle += ", ";
    sAdj = m_expand_title_adjective (asTitleConfiguration [2], oWho, iRank, aiCharacter [0], aiCharacter [1]);
    if (strlen (sAdj)) sTitle += sAdj + " ";
    sTitle += m_expand_title_base (asTitleConfiguration [3], oWho, iRank, aiCharacter [0], aiCharacter [1]);
  }

  return (sTitle);
}

//-------------------------------------------------------------------

/*******************************************************************\
| Functions for learning                                            |
\*******************************************************************/

/*
 * Function name : m_get_learning
 *
 */

int m_get_learning (mixed xWho)
{
  M_ACCESS_MONK_MEMBERS;

  string sWho = objectp (xWho) ? dg_get_name (xWho) : xWho;

  if (member_array (sWho, m_indices (mMonkMembers)) >= 0)
  {
    return (mMonkMembers [sWho][M_MONK_MEMBERS_LEARNING]);
  }
  else return (TRUE);
}


/*
 * Function name : m_set_learning
 *
 */

void m_set_learning (mixed xWho, int iLearning)
{
  M_ACCESS_MONK_MEMBERS;

  string sWho = objectp (xWho) ? dg_get_name (xWho) : xWho;

  if (member_array (sWho, m_indices (mMonkMembers)) >= 0)
  {
    mMonkMembers [sWho][M_MONK_MEMBERS_LEARNING] = iLearning;
  }

  M_SAVE_ACCESSED;
}

//-------------------------------------------------------------------

/*******************************************************************\
| Functions for authorization                                       |
\*******************************************************************/

int m_is_guru (object oWho)
{
  QUEST_PORT (oWho, Q_OLD_MONK_GURU, Q_MONK_GURU, "ported bits for monk guru.");
  return (QUEST_TEST (oWho, Q_MONK_GURU));
}

int m_is_acrobat_guru (object oWho)
{
  return (QUEST_TEST (oWho, Q_MONK_ACROBAT_GURU));
}

int m_is_guild_wizard (mixed xWho)
{
  int iFromSource;
  int iFromSecurity;

  string sWho = objectp (xWho) ? dg_get_name (xWho) : xWho;

  iFromSource = (member_array (sWho, M_MASTERS_ACTIVE) >= 0);
  iFromSecurity = SECURITY->query_guild_is_master (M_NAME_SHORT, sWho);

  if (iFromSource != iFromSecurity)
  {
    s_log (M_LOG_DEBUG, "Guild wizard list mismatch.");
  }

  return (iFromSource || iFromSecurity);
}


int m_is_authorized_wizard (mixed xWho)
{
  string sWho = objectp (xWho) ? dg_get_name (xWho) : xWho;

  return (m_is_guild_wizard (sWho) || (SECURITY->query_wiz_rank (sWho) >= WIZ_ARCH));
}

//-------------------------------------------------------------------

/*******************************************************************\
| Functions to gather utility statistics                            |
\*******************************************************************/

// The following constants say how fast the tops degrade
// and thus how long before an idle player no longer
// influences the tops.
//
// The degradation for kins and stats is subtractive.
// The degradation for character is multiplicative.
// The degradation for age and time is multiplicative.
//
// There are 720 hours in a month. Multiplication by
// 0.9 ^ (1/720) each hour equals multiplication by
// 0.9 each month. 0.9 ^ (1/720) = 0.99985367665678.

#define M_HOURLY_DEGRADATION_KINS       (1.0/720.0)
#define M_HOURLY_DEGRADATION_STATS      (10.0/720.0)
#define M_HOURLY_DEGRADATION_CHARACTER  (0.99985367665678)
#define M_HOURLY_DEGRADATION_AGE        (0.99985367665678)
#define M_HOURLY_DEGRADATION_TIME       (0.99985367665678)


void m_collect_statistics (object oWho)
{
  M_ACCESS_MONK_GUILD;
  M_ACCESS_MONK_MEMBERS;

  string sWho = dg_get_name (oWho);

  mixed *axMember;

  mixed *axCharacter;
  int iCharacter;
  int iTrait;
  string *asKins;
  string sDesc;
  int iAge;
  int iTime;

  if (member_array (sWho, m_indexes (mMonkMembers)) >= 0)
  {
    axMember = mMonkMembers [sWho];

    // Statistics for regular members ...

    if (!dg_is_junior (oWho) &&
        !dg_is_wizard (oWho))
    {
      // Gather information needed for the relative titles.

      asKins = M_SHADOW_SRVR->m_get_kins (oWho);
      axMonkGuild [M_MONK_GUILD_KINS] = MAX (itof (sizeof (asKins)), axMonkGuild [M_MONK_GUILD_KINS]);

      axMonkGuild [M_MONK_GUILD_STATS][M_STAT_STR] = MAX (itof (oWho->query_base_stat (SS_STR)), axMonkGuild [M_MONK_GUILD_STATS][M_STAT_STR]);
      axMonkGuild [M_MONK_GUILD_STATS][M_STAT_DEX] = MAX (itof (oWho->query_base_stat (SS_DEX)), axMonkGuild [M_MONK_GUILD_STATS][M_STAT_DEX]);
      axMonkGuild [M_MONK_GUILD_STATS][M_STAT_CON] = MAX (itof (oWho->query_base_stat (SS_CON)), axMonkGuild [M_MONK_GUILD_STATS][M_STAT_CON]);
      axMonkGuild [M_MONK_GUILD_STATS][M_STAT_INT] = MAX (itof (oWho->query_base_stat (SS_INT)), axMonkGuild [M_MONK_GUILD_STATS][M_STAT_INT]);
      axMonkGuild [M_MONK_GUILD_STATS][M_STAT_WIS] = MAX (itof (oWho->query_base_stat (SS_WIS)), axMonkGuild [M_MONK_GUILD_STATS][M_STAT_WIS]);
      axMonkGuild [M_MONK_GUILD_STATS][M_STAT_DIS] = MAX (itof (oWho->query_base_stat (SS_DIS)), axMonkGuild [M_MONK_GUILD_STATS][M_STAT_DIS]);

      axCharacter = M_SHADOW_SRVR->m_get_character (oWho);
      for (iCharacter = 0 ; iCharacter < sizeof (axCharacter) ; iCharacter ++)
        for (iTrait = 0 ; iTrait < sizeof (axCharacter [iCharacter]) ; iTrait ++)
          axMonkGuild [M_MONK_GUILD_CHARACTER][iCharacter][iTrait] = MAX (
            axMonkGuild [M_MONK_GUILD_CHARACTER][iCharacter][iTrait],
            itof (axCharacter [iCharacter][iTrait]));

      iAge = oWho->query_age () - axMember [M_MONK_MEMBERS_JOIN_AGE];
      iTime = time () - axMember [M_MONK_MEMBERS_JOIN_TIME];
      axMonkGuild [M_MONK_GUILD_AGE] = MAX (itof (iAge), axMonkGuild [M_MONK_GUILD_AGE]);
      axMonkGuild [M_MONK_GUILD_TIME] = MAX (itof (iTime), axMonkGuild [M_MONK_GUILD_TIME]);
    }

    // Statistics for council members ...

    if (axMember [M_MONK_MEMBERS_POSITION] & M_POSITION_COUNCIL)
    {
      // Track the time of the last council activity.
      axMonkGuild [M_MONK_GUILD_COUNCIL] = time ();

      // Gather information needed for the council frescoes.
      m_set_council_desc (oWho, dg_get_pretty_description (oWho));
    }

    M_SAVE_ACCESSED;
  }
}


void m_degrade_statistics ()
{
  M_ACCESS_MONK_GUILD;

  int iCharacter;
  int iTrait;
  int iStat;

  // This routine ignores the possibility of getting
  // negative values when degrading by subtracting.
  // In normal guild life that should never happen.

  axMonkGuild [M_MONK_GUILD_KINS] -= M_HOURLY_DEGRADATION_KINS;

  for (iStat = 0 ; iStat < sizeof (axMonkGuild [M_MONK_GUILD_STATS]) ; iStat ++)
    axMonkGuild [M_MONK_GUILD_STATS][iStat] -= M_HOURLY_DEGRADATION_STATS;

  for (iCharacter = 0 ; iCharacter < sizeof (axMonkGuild [M_MONK_GUILD_CHARACTER]) ; iCharacter ++)
    for (iTrait = 0 ; iTrait < sizeof (axMonkGuild [M_MONK_GUILD_CHARACTER][iCharacter]) ; iTrait ++)
      axMonkGuild [M_MONK_GUILD_CHARACTER][iCharacter][iTrait] *= M_HOURLY_DEGRADATION_CHARACTER;

  axMonkGuild [M_MONK_GUILD_AGE] *= M_HOURLY_DEGRADATION_AGE;
  axMonkGuild [M_MONK_GUILD_TIME] *= M_HOURLY_DEGRADATION_TIME;

  M_SAVE_ACCESSED;
}

//-------------------------------------------------------------------

/*******************************************************************\
| Functions to perform utility settings                             |
\*******************************************************************/


/*
 * Function name : m_limit_skills
 * Returns       : Limits the guild skills to correspond with the
 *                 maximum given for the particular branch the
 *                 monk is in.
 *
 */

#define M_LIMIT_SKILL(iSkill,iMax) \
  oWho->set_skill (MIN (iMax, oWho->query_skill (iSkill)))

void m_limit_skills (object oWho)
{
  if (m_is_monk (oWho, SS_OCCUP))
  {
    M_LIMIT_SKILL (M_SKILL_STRIKE, M_SKILL_MAX_OCC_STRIKE);
    M_LIMIT_SKILL (M_SKILL_PLEXUS, M_SKILL_MAX_OCC_PLEXUS);
    M_LIMIT_SKILL (M_SKILL_FORMING_CLUB, M_SKILL_MAX_FORMING);
    M_LIMIT_SKILL (M_SKILL_FORMING_BLADE, M_SKILL_MAX_FORMING);
    M_LIMIT_SKILL (M_SKILL_FORMING_STICK, M_SKILL_MAX_FORMING);
  }
  else if (m_is_monk (oWho, SS_LAYMAN))
  {
    M_LIMIT_SKILL (M_SKILL_STRIKE, M_SKILL_MAX_LAY_STRIKE);
    M_LIMIT_SKILL (M_SKILL_FORMING_CLUB, M_SKILL_MAX_FORMING);
    M_LIMIT_SKILL (M_SKILL_FORMING_BLADE, M_SKILL_MAX_FORMING);
    M_LIMIT_SKILL (M_SKILL_FORMING_STICK, M_SKILL_MAX_FORMING);
  }
  else
  {
    oWho->remove_skill (M_SKILL_STRIKE);
    oWho->remove_skill (M_SKILL_PLEXUS);
    oWho->remove_skill (M_SKILL_FORMING_CLUB);
    oWho->remove_skill (M_SKILL_FORMING_BLADE);
    oWho->remove_skill (M_SKILL_FORMING_STICK);
  }
}

#undef M_LIMIT_SKILL


/*
 * Function name : m_fix
 * Description   : Fixes whatever might need fixing at login.
 *
 */

void m_fix (object oWho)
{
  string sWho = dg_get_name (oWho);
  string sWhoCap = capitalize (sWho);

  string *asTitle;

  // The title of the player might have become invalid.

  asTitle = m_get_title_configuration (oWho);
  if (stringp (m_validate_title (oWho,
                                 asTitle [0], asTitle [1],
                                 asTitle [2], asTitle [3])))
  {
    m_set_title_configuration (oWho,
                               M_TITLE_ADJ_RANK, M_TITLE_BASE_RANK,
                               M_TITLE_ADJ_NONE, M_TITLE_BASE_CHAR);
  }
}


//-------------------------------------------------------------------

/*******************************************************************\
| Hooks                                                             |
\*******************************************************************/

void m_player_hook_create ()
{
  set_alarm (0.0, 3600.0, m_degrade_statistics);
}

//-------------------------------------------------------------------

