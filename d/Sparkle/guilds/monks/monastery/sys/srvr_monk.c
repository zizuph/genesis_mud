/*******************************************************************\
| SRVR_MONK.C                                                       |
+-------------------------------------------------------------------+
| Data holder for the monk guild. This object is responsible for    |
| holding all persistent structures related to the monk guild.      |
| The monk guild libraries can use this object to obtain a          |
| reference to any structure. No structures are changed             |
| here except for the versioning related conversions.               |
\*******************************************************************/

/*
 * 07/06/03 Arandir     Support for configurable learning in combat
 * 07/05/19 Arandir     Removed extraneous includes
 *                      Support for council activity
 * 07/05/18 Arandir     Support for infinite votes
 * 05/04/24 Arandir     New support for titles
 * 04/11/18 Arandir     Added support for guild age and time
 * 04/08/15 Arandir     Tiny fix for default versioning bug
 * 03/10/21 Arandir     Added support for council terms
 * 03/09/06 Arandir     Fixed the versioned state to use mixed externals
 * 03/07/14 Arandir     Delayed save now not done during armageddon
 * 03/07/09 Arandir     Support for token state.
 * 03/07/03 Arandir     Support for delayed save
 * 03/07/03 Arandir     Support for guild state
 * 03/06/21 Arandir     Support for application state
 * 03/06/13 Arandir     Revamped into a data holder
 * 03/06/11 Arandir     Support for voting state
 * 03/06/10 Arandir     Support for versioned state
 * 03/03/29 Arandir     Support for past members
 * 02/01/19 Arandir	Ported over to the new area
 * 01/02/07 Manat	Owner can now close voting prematurely
 * 01/01/05 Manat	Fixed several typos
 * 98/06/01 Cirion	Created
 *
 */

#include <macros.h>
#include <files.h>

#include "../defs.h"

inherit DG_OBJ_LIBS;

//-------------------------------------------------------------------

// Managed by LIBS_TOKEN

private static mapping mMonkTokens = ([ ]);

// Managed by LIBS_PLAYER

private static mapping mMonkMembers = ([ ]);
private static mapping mMonkCouncil = ([ ]);
private static mapping mMonkFormer = ([ ]);
private static mixed *axMonkGuild = ({ });

// Managed by LIBS_VOTING

private static mapping mMonkVotes = ([ ]);

// Managed by LIBS_JOINING

private static mapping mMonkApplicants = ([ ]);


// Local data

#define M_SAVE_MIN_DELAY        30.0
#define M_SAVE_MAX_AGE          300

private static int iSaveAlarm = ALARM_NONE;
private static int iSaveTime;

//-------------------------------------------------------------------

/*******************************************************************\
| Versioned state export and import functions                       |
\*******************************************************************/

//-------------------------------------------------------------------

/*
 * Function name : m_export_state_monk_guild
 * Function name : m_import_state_monk_guild
 * Description   : Converts the state in the axMonkGuild variable.
 *
 */

#define M_MONK_GUILD_VERSION            3

public int iMonkGuildVersion = M_MONK_GUILD_VERSION;
public mixed xMonkGuildExternal = ({
                                    0.0,
                                    ({ 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 }),
                                    ({
                                      ({ 0.0, 0.0, 0.0, 0.0, 0.0 }),
                                      ({ 0.0, 0.0, 0.0, 0.0, 0.0 })
                                    }),
                                    0.0,
                                    0.0,
                                    0
                                  });


void m_export_state_monk_guild ()
{
  // Exporting the state is trivial, we simply enforce using
  // the latest version of the state information.

  iMonkGuildVersion = M_MONK_GUILD_VERSION;
  xMonkGuildExternal = axMonkGuild;
}


void m_import_state_monk_guild ()
{
  switch (iMonkGuildVersion)
  {
    // Version 0 has to be converted.
    // Differences between 0 and 1 are:
    //  - Grouped stats into an array
    //  - Added character tops
    //  - Added dragon tops

    case 0: xMonkGuildExternal = ({ 0.0,
                                    xMonkGuildExternal,
                                    ({
                                      ({ 0.0, 0.0, 0.0, 0.0, 0.0 }),
                                      ({ 0.0, 0.0, 0.0, 0.0, 0.0 })
                                    })
                                 });

            // Pass through to next version

    // Version 1 has to be converted.
    // Differences between 1 and 2 are:
    //  - Added guild age and time

    case 1: xMonkGuildExternal += ({ 0.0, 0.0 });

    // Version 2 has to be converted.
    // Differences between 2 and 3 are:
    //  - Added council activity

    case 2: xMonkGuildExternal += ({ time () });

    // Version 3 is the current version, which can be simply copied.

    case 3: axMonkGuild = xMonkGuildExternal;
            break;
  }
}

//-------------------------------------------------------------------

/*
 * Function name : m_export_state_monk_tokens
 * Function name : m_import_state_monk_tokens
 * Description   : Converts the state in the mMonkTokens variable.
 *
 */

#define M_MONK_TOKENS_VERSION           0

public int iMonkTokensVersion = M_MONK_TOKENS_VERSION;
public mixed xMonkTokensExternal = ([ ]);


void m_export_state_monk_tokens ()
{
  // Exporting the state is trivial, we simply enforce using
  // the latest version of the state information.

  iMonkTokensVersion = M_MONK_TOKENS_VERSION;
  xMonkTokensExternal = mMonkTokens;
}


void m_import_state_monk_tokens ()
{
  switch (iMonkTokensVersion)
  {
    // Version 0 is the current version, which can be simply copied.

    case 0: mMonkTokens = xMonkTokensExternal;
            break;
  }
}

//-------------------------------------------------------------------

/*
 * Function name : m_export_state_monk_members
 * Function name : m_import_state_monk_members
 * Description   : Converts the state in the mMonkMembers variable.
 *
 */

#define M_MONK_MEMBERS_VERSION          2

public int iMonkMembersVersion = M_MONK_MEMBERS_VERSION;
public mixed xMonkMembersExternal = ([ ]);


void m_export_state_monk_members ()
{
  // Exporting the state is trivial, we simply enforce using
  // the latest version of the state information.

  iMonkMembersVersion = M_MONK_MEMBERS_VERSION;
  xMonkMembersExternal = mMonkMembers;
}


void m_import_state_monk_members ()
{
  mixed  xConverted;
  mixed  xAddition;

  switch (iMonkMembersVersion)
  {
    // Version 0 has to be converted.
    // Differences between 0 and 1 are:
    //  - Added title configuration

    case 0: xConverted = ([ ]);
            xAddition = ({ ({ "", "", "", "" }) });
            foreach (string sItem, mixed *axItem : xMonkMembersExternal)
            {
              xConverted += ([ sItem : axItem + xAddition ]);
            }
            xMonkMembersExternal = xConverted;

            // Pass through to next version

    // Version 1 has to be converted.
    // Differences between 1 and 2 are:
    //  - Added learning configuration

    case 1: xConverted = ([ ]);
            xAddition = ({ TRUE });
            foreach (string sItem, mixed *axItem : xMonkMembersExternal)
            {
              xConverted += ([ sItem : axItem + xAddition ]);
            }
            xMonkMembersExternal = xConverted;

            // Pass through to next version

    // Version 2 is the current version, which can be simply copied.

    case 2: mMonkMembers = xMonkMembersExternal;
            break;
  }
}

//-------------------------------------------------------------------

/*
 * Function name : m_export_state_monk_council
 * Function name : m_import_state_monk_council
 * Description   : Converts the state in the mMonkCouncil variable.
 *
 */

#define M_MONK_COUNCIL_VERSION          2

public int iMonkCouncilVersion = M_MONK_COUNCIL_VERSION;
public mixed xMonkCouncilExternal = ([ ]);


void m_export_state_monk_council ()
{
  // Exporting the state is trivial, we simply enforce using
  // the latest version of the state information.

  iMonkCouncilVersion = M_MONK_COUNCIL_VERSION;
  xMonkCouncilExternal = mMonkCouncil;
}


void m_import_state_monk_council ()
{
  mixed  xConverted;
  mixed  xAddition;

  switch (iMonkCouncilVersion)
  {
    // Version 0 has to be converted.
    // Differences between 0 and 1 are:
    //  - Added council term item

    case 0: xConverted = ([ ]);
            xAddition = ({ time () - M_TERM_COUNCIL });
            foreach (string sItem, mixed axItem : xMonkCouncilExternal)
            {
              xConverted += ([ sItem : axItem + xAddition ]);
            }
            xMonkCouncilExternal = xConverted;

            // Pass through to next version

    // Version 1 has to be converted.
    // Differences between 1 and 2 are:
    //  - Removed council title item

    case 1: xConverted = ([ ]);
            foreach (string sItem, mixed axItem : xMonkCouncilExternal)
            {
              xConverted += ([ sItem : axItem [1 .. 2] ]);
            }
            xMonkCouncilExternal = xConverted;

            // Pass through to next version

    // Version 2 is the current version, which can be simply copied.

    case 2: mMonkCouncil = xMonkCouncilExternal;
            break;
  }
}

//-------------------------------------------------------------------

/*
 * Function name : m_export_state_former_members
 * Function name : m_import_state_former_members
 * Description   : Converts the state in the mMonkFormer variable.
 *
 */

#define M_FORMER_MEMBERS_VERSION                0

public int iFormerMembersVersion = M_FORMER_MEMBERS_VERSION;
public mixed xMonkFormerExternal = ([ ]);


void m_export_state_former_members ()
{
  // Exporting the state is trivial, we simply enforce using
  // the latest version of the state information.

  iFormerMembersVersion = M_FORMER_MEMBERS_VERSION;
  xMonkFormerExternal = mMonkFormer;
}


void m_import_state_former_members ()
{
  switch (iFormerMembersVersion)
  {
    // Version 0 is the current version, which can be simply copied.

    case 0: mMonkFormer = xMonkFormerExternal;
            break;
  }
}

//-------------------------------------------------------------------

/*
 * Function name : m_export_state_monk_votes
 * Function name : m_import_state_monk_votes
 * Description   : Converts the state in the mMonkVotes variable.
 *
 */

#define M_MONK_VOTES_VERSION            1

public int iMonkVotesVersion = M_MONK_VOTES_VERSION;
public mixed xMonkVotesExternal = ([ ]);


void m_export_state_monk_votes ()
{
  // Exporting the state is trivial, we simply enforce using
  // the latest version of the state information.

  iMonkVotesVersion = M_MONK_VOTES_VERSION;
  xMonkVotesExternal = mMonkVotes;
}


void m_import_state_monk_votes ()
{
  mixed  xConverted;
  mixed  xOriginal;

  switch (iMonkVotesVersion)
  {
    // Version 0 has to be converted.
    // Differences between 0 and 1 are:
    //  - Removed start vote timestamp
    //  - Moved end vote timestamp

    case 0: xConverted = ([ ]);
            foreach (string sItem, mixed axItem : xMonkVotesExternal)
            {
              xConverted += ([ sItem : axItem [0 .. 2] +
                                       axItem [5 .. 5] +
                                       axItem [4 .. 4] +
                                       axItem [6 .. 7] ]);
            }
            xMonkVotesExternal = xConverted;

            // Pass through to next version

    // Version 1 is the current version, which can be simply copied.

    case 1: mMonkVotes = xMonkVotesExternal;
            break;
  }
}

//-------------------------------------------------------------------

/*
 * Function name : m_export_state_monk_applicants
 * Function name : m_import_state_monk_applicants
 * Description   : Converts the state in the mMonkApplicants variable.
 *
 */

#define M_MONK_APPLICANTS_VERSION       0

public int iMonkApplicantsVersion = M_MONK_APPLICANTS_VERSION;
public mixed xMonkApplicantsExternal = ([ ]);


void m_export_state_monk_applicants ()
{
  // Exporting the state is trivial, we simply enforce using
  // the latest version of the state information.

  iMonkApplicantsVersion = M_MONK_APPLICANTS_VERSION;
  xMonkApplicantsExternal = mMonkApplicants;
}


void m_import_state_monk_applicants ()
{
  switch (iMonkApplicantsVersion)
  {
    // Version 0 is the current version, which can be simply copied.

    case 0: mMonkApplicants = xMonkApplicantsExternal;
            break;
  }
}

//-------------------------------------------------------------------

/*******************************************************************\
| State save and restore functions                                  |
\*******************************************************************/

/*
 * Function name : m_filename
 * Function name : m_save_immediate
 * Function name : m_save_object
 * Function name : m_restore_object
 * Description   : Functions to save and restore the object.
 *
 */

string m_filename ()
{
  return (M_PATH_VAR_SYS + "/" + dg_base_name ());
}


void m_save_immediate ()
{
  iSaveAlarm = ALARM_NONE;

  m_export_state_monk_guild ();
  m_export_state_monk_tokens ();
  m_export_state_monk_members ();
  m_export_state_monk_council ();
  m_export_state_former_members ();
  m_export_state_monk_votes ();
  m_export_state_monk_applicants ();
  DG_FIXUID;
  save_object (m_filename ());
}


void m_save_object ()
{
  // To prevent extreme load, we merge saves that are more
  // frequent than a given delay. To prevent consistency
  // problems during crashes, we enforce saves that are
  // older than a given age or during armageddon.

  if (ARMAGEDDON->shutdown_active ())
  {
    if (iSaveAlarm != ALARM_NONE)
    {
      remove_alarm (iSaveAlarm);
    }
    m_save_immediate ();
  }
  else
  {
    if (iSaveAlarm != ALARM_NONE)
    {
      if ((time () - iSaveTime) < M_SAVE_MAX_AGE)
      {
        remove_alarm (iSaveAlarm);
        iSaveAlarm = set_alarm (M_SAVE_MIN_DELAY, 0.0, m_save_immediate);
      }
    }
    else
    {
      iSaveAlarm = set_alarm (M_SAVE_MIN_DELAY, 0.0, m_save_immediate);
      iSaveTime = time ();
    }
  }
}


void m_restore_object ()
{
  DG_FIXUID;
  restore_object (m_filename ());
  m_import_state_monk_guild ();
  m_import_state_monk_tokens ();
  m_import_state_monk_members ();
  m_import_state_monk_council ();
  m_import_state_former_members ();
  m_import_state_monk_votes ();
  m_import_state_monk_applicants ();
}


/*
 * Function name : create
 *
 */

void create ()
{
  m_restore_object ();

  // We have to preload other servers.

  DG_LOAD (M_SHADOW_SRVR);

  // We have to preload rooms where the message boards reside to
  // make sure an instance of the board will always be ready when
  // a note is to be posted from within the code.

  DG_LOAD (M_PATH_ROOM + "/meeting");
  DG_LOAD (M_PATH_ROOM + "/council");

  // Launch activities that take care of various guild mechanics.

  M_PLAYER_LIBS->m_player_hook_create ();
  M_VOTING_LIBS->m_voting_hook_create ();
  M_JOINING_LIBS->m_joining_hook_create ();
}

//-------------------------------------------------------------------

/*******************************************************************\
| Reference export functions                                        |
\*******************************************************************/

/*
 * Function name : m_get_monk_guild
 * Function name : m_get_monk_tokens
 * Function name : m_get_monk_members
 * Function name : m_get_monk_council
 * Function name : m_get_monk_former
 * Function name : m_get_monk_votes
 * Function name : m_get_monk_applicants
 *
 */

mixed *m_get_monk_guild () { return (axMonkGuild); }
mapping m_get_monk_tokens () { return (mMonkTokens); }
mapping m_get_monk_members () { return (mMonkMembers); }
mapping m_get_monk_council () { return (mMonkCouncil); }
mapping m_get_monk_former () { return (mMonkFormer); }
mapping m_get_monk_votes () { return (mMonkVotes); }
mapping m_get_monk_applicants () { return (mMonkApplicants); }

//-------------------------------------------------------------------

/*******************************************************************\
| Mapping deletion functions                                        |
\*******************************************************************/

/*
 * Function name : m_delete_monk_tokens
 * Function name : m_delete_monk_members
 * Function name : m_delete_monk_council
 * Function name : m_delete_monk_votes
 * Function name : m_delete_monk_applicants
 * Description   : As it is not possible to delete a member from
 *                 a mapping without copying the mapping, the
 *                 deletion functions have to be here.
 *
 */

mapping m_delete_monk_tokens (string sKey)
{
  return (mMonkTokens = m_delete (mMonkTokens, sKey));
}


mapping m_delete_monk_members (string sKey)
{
  return (mMonkMembers = m_delete (mMonkMembers, sKey));
}


mapping m_delete_monk_council (string sKey)
{
  return (mMonkCouncil = m_delete (mMonkCouncil, sKey));
}


mapping m_delete_monk_votes (string sKey)
{
  return (mMonkVotes = m_delete (mMonkVotes, sKey));
}


mapping m_delete_monk_applicants (string sKey)
{
  return (mMonkApplicants = m_delete (mMonkApplicants, sKey));
}

//-------------------------------------------------------------------

/*******************************************************************\
| Mapping Addition functions                                        |
\*******************************************************************/

/*
 * Function:    m_add_monk_member
 * Description: This is a utility function that allows someone to add
 *              a monk member without going through the usual hassles
 *              via libs_player.c or libs_joining.c. This is important
 *              for setting up testing situations with test npcs and
 *              testing juniors.
 */
public int 
m_add_monk_member (object oWho, int iBranch)
{
  if (!objectp(oWho) || !IS_LIVING_OBJECT(oWho))
  {
    return 0;
  }
  
  if (!iBranch)
  {
    // If no branch specified, default to occupational
    iBranch = 7;
  }
  
  string sWho = oWho->query_real_name();
  if (mMonkMembers[sWho])
  {
    // player already added.
    return 0;
  }
  
  mMonkMembers +=
    ([ oWho->query_real_name() :
      ({
        oWho->query_age (),     // M_MONK_MEMBERS_JOIN_AGE
        time (),                // M_MONK_MEMBERS_JOIN_TIME
        iBranch,                // M_MONK_MEMBERS_BRANCH
        BIT (0),                // M_MONK_MEMBERS_POSITION
        0,                      // M_MONK_MEMBERS_PUNISHMENTS
        ({ "", "", "", "" }),   // M_MONK_MEMBERS_TITLE
        1                       // M_MONK_MEMBERS_LEARNING
      })
    ]);
  
  return 1;
}
        
//-------------------------------------------------------------------
