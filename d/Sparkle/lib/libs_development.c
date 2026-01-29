/*******************************************************************\
| LIBS_DEVELOPMENT.C                                                |
\*******************************************************************/

/*
 * 08/01/15 Arandir     Complete rewrite to work with a single alarm
 * 08/01/14 Arandir     Changed traversal order to minimize alarms
 *                      Added the option to ignore files
 * 06/03/18 Arandir     Debugged
 * 06/02/23 Arandir	Created
 *
 */

#include <time.h>

#include "defs.h"

inherit S_LIB_TEXT;

//-------------------------------------------------------------------

// S_UPDATE_GRANULARITY         Number of entries to scan per alarm
// S_UPDATE_INTENSITY           Number of seconds between alarms
#define S_UPDATE_GRANULARITY    10
#define S_UPDATE_INTENSITY      1.0

// S_UPDATE_CHANGELOG           Number of lines to scan for changelog entries
#define S_UPDATE_CHANGELOG      500

// S_UPDATE_IGNORE              File with the list of entries to ignore
// S_UPDATE_LAST                File with the time of last report
#define S_UPDATE_IGNORE         (S_DOMAIN_VAR_DIR + "update_ignore")
#define S_UPDATE_LAST           (S_DOMAIN_VAR_DIR + "update_last")

// S_LAST_TIME                  Index of time of last report in file
#define S_LAST_TIME             "time"

private static mapping mUpdateIgnore = ([ ]);
private static mapping mUpdateLast = ([ ]);

private static string *asCurrentEntries = ({ });
private static string *asStackDirectories = ({ });
private static mixed  mStackEntries = ({ });

private static string sReportDirectory = "";
private static string sReportListing = "";

private static int iUpdateSinceTime;
private static int iUpdateSinceWeird;

//-------------------------------------------------------------------

void s_partial_report_single_file (string sDirectory, string sEntry);

//-------------------------------------------------------------------

/*
 * Function name : s_report_file_updates
 * Description   : Reports files updated since last call. The search
 *                 splits itself with alarms to avoid overloading
 *                 the game.
 *   bInitial      : Indicates beginning of search
 *
 */


// S_REPORT_NEXT_ENTRY
// Notes a scanned entry and schedules an alarm for next scan if necessary.
#define S_REPORT_NEXT_ENTRY                             \
{                                                       \
  iEntries ++;                                          \
  if (iEntries > S_UPDATE_GRANULARITY)                  \
  {                                                     \
    set_alarm (S_UPDATE_INTENSITY, 0.0,                 \
               &s_report_file_updates (FALSE));         \
    return;                                             \
  }                                                     \
}


void s_report_file_updates (int bInitial = TRUE)
{
  int iDepth;
  string sPath;
  string sName;
  string sFull;

  int iEntries = 0;

  // This function splits itself with alarms to avoid overloading the
  // game with frequent disk activity. The internal state is kept in
  // global variables between alarms. The variables are erased
  // afterwards to maintain reasonable memory usage.

  // Races will occur when the directory structure is changed
  // during scanning. So what ...

  // Many file operations check access rights.

  S_FIXUID;

  // Check whether this is the beginning of the search.

  if (bInitial)
  {
    mUpdateIgnore = restore_map (S_UPDATE_IGNORE);
    mUpdateLast = restore_map (S_UPDATE_LAST);

    // Because there is no handy function in the game to convert
    // from textual date to integer time, we use a weird substitute.

    iUpdateSinceTime = mUpdateLast [S_LAST_TIME];
    mUpdateLast [S_LAST_TIME] = time ();
    string sSinceText = TIME2FORMAT (iUpdateSinceTime, "yyyymmdd");
    int iSinceYear  = atoi (sSinceText [0..3]);
    int iSinceMonth = atoi (sSinceText [4..5]);
    int iSinceDay   = atoi (sSinceText [6..7]) - 1;
    iUpdateSinceWeird = (((iSinceYear) * 100 + iSinceMonth) * 100 + iSinceDay);

    sReportDirectory = "";
    sReportListing = "";

    asStackDirectories = ({ S_DOMAIN_DIR });
    asCurrentEntries = NULL;
    mStackEntries = ({ });
  }

  // This cycle can be entered at any time. The pivotal part of
  // the internal state is kept in the following variables:
  //
  //   asStackDirectories : array of directories forming a path
  //                        to current position in the search
  //
  //   asCurrentEntries   : array of entries not yet
  //                        traversed in current
  //                        position
  //
  //   mStackEntries      : array of directories not yet
  //                        traversed in the path
  //
  //   sReportDirectory   : last directory where file was reported
  //   sReportListing     : accummulated text of the entire report

  while (TRUE)
  {
    // Assemble the current path ...

    sPath = s_remove_doubleslash (implode (asStackDirectories, "/") + "/");
    iDepth = sizeof (asStackDirectories) - 1;

    // Read entries in the current position if not yet read.

    if (asCurrentEntries == NULL)
    {
      asCurrentEntries = get_dir (sPath);
      mStackEntries += ({ ({ }) });
    }

    // If any entries are not yet traversed in the current
    // position, traverse them first ...

    while (sizeof (asCurrentEntries) > 0)
    {
      sName = asCurrentEntries [0];
      asCurrentEntries = asCurrentEntries [1 ..];
      sFull = sPath + sName;

      if (!wildmatch("*.o", sName) && !mUpdateIgnore [sFull])
      {
        // Directories are stored for later traversal ...
        if (S_IS_DIR (sFull))
        {
          mStackEntries [iDepth] += ({ sName });
        }

        // Files are processed on the fly ...
        if (S_IS_FILE (sFull) && (file_time (sFull) > iUpdateSinceTime))
        {
          s_partial_report_single_file (sPath, sName);
        }
      }

      S_REPORT_NEXT_ENTRY;
    }

    // If any directories are not yet traversed in the current
    // position, traverse them next ...

    if (sizeof (mStackEntries [iDepth]) > 0)
    {
      sName = mStackEntries [iDepth] [0];
      mStackEntries [iDepth] = mStackEntries [iDepth] [1 ..];
      asStackDirectories += ({ sName });
      asCurrentEntries = NULL;

      // Rather than using recursion, we return to the
      // main cycle, which resumes the search. Recursion
      // would not work easily with alarms and global state.

      S_REPORT_NEXT_ENTRY;
    }
    else
    {
      // Backtrack ...

      if (iDepth)
      {
        asStackDirectories = asStackDirectories [0 .. iDepth - 1];
        mStackEntries = mStackEntries [0 .. iDepth - 1];
      }
      else
      {
        break;
      }
    }
  }

  // All that is left now is reporting and tidying up.

  if (strlen (sReportListing))
  {
    S_DOMAIN_BOARD->s_post_note (
      "Updates since " + ctime (iUpdateSinceTime),
      "Sparkle",
      sReportListing);
  }

  // Record time of last report now that we know it succeeded.

  S_FIXUID;

  save_map (mUpdateLast, S_UPDATE_LAST);

  // Free large global variables ...

  asStackDirectories = NULL;
  asCurrentEntries = NULL;
  mStackEntries = NULL;

  mUpdateIgnore = ([ ]);
  mUpdateLast = ([ ]);

  sReportDirectory = "";
  sReportListing = "";
}


/*
 * Function name : s_partial_report_single_file
 * Description   : Processes one entry to form the list of files
 *                 updated after a given time.
 *
 */

void s_partial_report_single_file (string sDirectory, string sEntry)
{
  S_FIXUID;

  string sFile = sDirectory + sEntry;

  // Report the directory in which the entry resides but just once.

  if (sDirectory != sReportDirectory)
  {
    sReportDirectory = sDirectory;
    sReportListing += sDirectory + "\n";
  }

  string sMessage = "- " + sEntry;

  // We could really use a function that would calculate the time integer
  // from year, month, day. The game does not support it, hence the
  // somewhat awkward comparison on year, month, day instead.

  string sText = read_file (sFile, 1, S_UPDATE_CHANGELOG);
  if (stringp (sText))
  {
    string *asText = explode (read_file (sFile, 1, S_UPDATE_CHANGELOG), "\n");
    string *asLines = regexp (asText, "^ \\* [0-9][0-9]/[0-9][0-9]/[0-9][0-9] ");
    foreach (string sLine : asLines)
    {
      int iYear, iMonth, iDay;
      string sRest;

      if (sscanf (sLine, " * %d/%d/%d %s", iYear, iMonth, iDay, sRest) == 4)
      {
        if (iYear < 70) iYear += 2000;
                   else iYear += 1900;

        int iWeird = (((iYear) * 100 + iMonth) * 100 + iDay);
        if (iWeird > iUpdateSinceWeird)
        {
          sRest = s_remove_whitespace (sRest);
          sRest = s_remove_doublespace (sRest);
          if (strlen (sRest))
          {
            sMessage += " - " + sRest [0 .. S_TERMINAL_WIDTH - strlen (sMessage) - 4];
          }
          break;
        }
      }
    }

    sMessage += "\n";
  }

  sReportListing += sMessage;
}

//-------------------------------------------------------------------

void s_development_hook_create ()
{
  // The random start time should help avoid load peaks every day,
  // which is simply chosen too often as a period for regular alarms.
  set_alarm (itof (random (60)), 86400.0, &s_report_file_updates ());
}

//-------------------------------------------------------------------

