/*
 * /d/Gondor/guilds/rangers/manager/manager.c
 *
 * This room keeps track of and manages these variables:
 *
 * mapping gAdminCmds
 * mapping gApprenticeTime
 * mapping gBanished
 * mapping gCouncil
 * mapping gCandidates
 * mapping gElection
 * mapping gExpelled
 * mapping gImpeachers
 * mapping gLogBook
 * mapping gMasters
 * mapping gNominators
 * mapping gNotoriousOutlaw
 * mapping gOutlaw
 * mapping gPunish
 * mapping gRangers
 * mapping gRejoinTime
 * mapping gReward
 * mapping gSpecialists
 * mapping gTasks
 * mapping gUnpunish
 * mapping gVirtues
 * mapping gVotedIn
 * mapping gVotedOut
 * mapping gVotes
 *
 * Coded by Gwyneth on April 25, 2001
 *
 * Modification log:
 *   Gwyneth, July 14, 2004, Fixed election bug.
 *   Gwyneth, July 20, 2004, Master/specialist additions
 *   Tigerlily, July 29, 2004, Reset ranger rewards for promoted and
 *      removed approved apprentices
 *      Dec. 28, 2004: fixed bug to nominate after nominations are closed
 *      Aug. 29, 2005: updated startup_checks function to fix bug when 
 *                     rangers.o file is erased during/after armies, possibly
 *                     relating to election functions and/or to delete_player 
 *                     function in preload (simplified and reordered load
 *                     process)
 *      Dec. 26, 2005: Fixed process in check_vote_end() to restart 
 *                     election automatically when there is no captain
 *                     Also set up 6 month period rejoin time for rangers
 *                     voted out of both companies--and remove from votedout.o
 *                     when time is expired (remove_no_rejoin)
 */

#pragma save_binary
inherit "/std/room";

#include "../rangers.h"
#include "/d/Gondor/defs.h"
#include "../titles.h"

#include <files.h>
#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <time.h>

#define MANAGER_NAME "The Secretary"

#define VIRTUE_MAJOR_VIRTUE_IDX      0
#define VIRTUE_MAJOR_VIRTUE_TIME_IDX 1
#define VIRTUE_MINOR_VIRTUE_IDX      2
#define VIRTUE_MINOR_VIRTUE_TIME_IDX 3


/* Global Variables, when adding a global variable that is
   kept track of through reboots, don't forget to add it to
   restore_manager(). */

mapping gAdminCmds        = ([]);
mapping gApprenticeTime   = ([]);
mapping gBanished         = ([]);
mapping gCandidates       = (["north" : ({}), "ithilien" : ({})]);
mapping gCouncil          = ([ "north"    : ({ "", "", "" }),
                               "ithilien" : ({ "", "", "" }) ]);
mapping gElection         = ([ "north" : ({0,0}), "ithilien" : ({0,0}) ]);
mapping gExpelled         = ([]);
mapping gImpeachers       = (["north" : ({}), "ithilien" : ({})]);
mapping gLogBook          = ([]);
mapping gMasters          = ([]);
mapping gNominators       = (["north" : ({}), "ithilien" : ({}) ]);
mapping gNotoriousOutlaw  = ([]);
mapping gPunish           = ([]);
mapping gOutlaw           = ([]);
mapping gRangers          = (["north" : ({}),    "ithilien" : ({}),
                              "approved" : ({}), "apprentice" : ({}), ]);
mapping gRejoinTime       = ([]);
mapping gReward           = ([]);
mapping gSpecialists      = ([]);
mapping gTasks            = ([]);
mapping gUnpunish         = ([]);
mapping gVirtues          = ([]);
mapping gVotedIn          = (["north" : ({}), "ithilien" : ({}) ]);
mapping gVotedOut         = (["north" : ({}), "ithilien" : ({}) ]);
mapping gVotes            = (["north" : ([]), "ithilien" : ([]) ]);


/* Prototypes */

public void        startup_checks();
public void        check_vote_end();

public void        move_old(string str);
public void        cleanup_backups();
public void        test_backup(string filename);
public void        backup_manager();

private nomask int cycle_file(string filename, int size);
public int         rlog(string company, string text);
public varargs int send_message(object target, string text, string sender);
private void       save_manager(mapping map, string filename);
public void        restore_manager();
public void        save_manager_temp();
public void        backup_manager();

public int         query_apprentice_time(string name);
public int         query_apprentice_join_time(string name);
public string      query_apprentice_log(string name, int view_all);
public string *    query_log_writers(string name);
public string      add_apprentice_log(string name, string writer,
                                      string message, int restricted);
public void        remove_apprentice_log(string name);

public int         query_voted_in(string name, string company);
public void        add_voted_in(string name, string company);
public void        remove_voted_in(string name, string company);
public int         query_voted_out(string name, string company);
public void        add_voted_out(string name, string company);
public void        remove_voted_out(string name, string company);

public int         query_ranger_level(string name);
public string      query_ranger_company(string name);
public string *    query_company_members(int company);

public varargs int query_ranger(string name, string company);
public varargs int add_ranger(string name, string company, int overide);
public varargs int remove_ranger(string name, int rem_reward);

public varargs int query_council(string name, string company);
public varargs int add_council(string name, int position, string company);
public int         remove_council(string name);

public int         query_is_council(string name);
public string      query_council_name(int position, string company);
public string      query_title_name(string name);

public string *    query_admin_cmds(string name);
public int         add_admin_cmd(string name, string cmd);
public int         remove_admin_cmd(string name, string cmd);
public int         remove_all_admin_cmds(string name);

public int         increment_task_number(string apprentice);
public void        remove_task_number(string apprentice);

public int         query_is_master(string name);
public string      query_master_specialty(string name);
public int         add_master(string name);
public int         remove_master(string name);

public int         query_is_specialist(string name);
public string      query_specialist_specialty(string name);
public varargs int advance_specialist(string name, int i);
public int         query_specialist_rank(string name);
public int         add_specialist(string name, string specialty_type);
public int         remove_specialist(string name);

public string *    query_to_be_expelled(string name);
public varargs int add_to_be_expelled(string name, string reason, int soft);
public int         remove_to_be_expelled(string name);

public int         query_no_rejoin(string name);
public int         add_no_rejoin(string name);
public int         remove_no_rejoin(string name);

public string *    query_to_be_rewarded(string name, string reward_type);
public int         add_to_be_rewarded(string name, string reward, string why);
public varargs int remove_to_be_rewarded(string name, string reward_type);
public varargs int reward_ranger(string name, string reward_type);

public string *    query_to_be_punished(string name);
public int         add_to_be_punished(string name, string punish, string why);
public int         remove_to_be_punished(string name);
public varargs int punish_ranger(string name, string punish_type, string why);
public int         lower_skills(object ranger);

public int         query_to_be_unpunished(string name);
public int         add_to_be_unpunished(string name);
public int         remove_to_be_unpunished(string name);
public int         unpunish_ranger(string name);

public int         query_outlaw(string name);
public int         query_is_outlaw(string name);
public int         add_outlaw(string name);
public int         remove_outlaw(string name);
public string *    query_outlaw_members();

public int         query_notorious_outlaw(string name);
public int         add_notorious_outlaw(string name);
public int         remove_notorious_outlaw(string name);
public string *    query_notorious_members();

public int         query_banished(string name);
public int         add_banished(string name);
public int         remove_banished(string name);

public int         end_election(string company);
public int         start_election(string company, int election);
public int         query_election(string company);
public void        post_election_results(string company, int election_type,
                   mapping results);

public string *    query_candidates(string company);
public int         query_is_candidate(string name, string company);
public varargs int add_candidate(string name, string company, string nominator);
public int         remove_candidate(string name, string company);
public varargs mapping find_winners(string company, int num = 1);

public int         query_nominator(string name, string company);
public int         add_nominator(string name, string company);
public varargs int remove_nominator(int all, string company, string name = "");

public int         query_voted(string company, string name);
public int         cast_vote(string company, string name, string vote_choice);

public string *    query_impeaching(string company);
public int         add_impeaching(string name, string company);
public int         remove_impeaching(string name, string company);

public int         query_major_virtue(string name);
public int         set_major_virtue(string name, int virtue);
public int         query_minor_virtue(string name);
public int         set_minor_virtue(string name, int virtue);
public int         can_change_major_virtue(string name);
public int         can_change_minor_virtue(string name);

public void
create_room()
{
    set_short("Ranger Manager Room");
    set_long("Here is where the Ranger guild is managed.\n");
    seteuid(getuid());

    // Uncomment this and comment restore_manager to start
    // when you don't have any .o files to work with yet.
    // save_manager_temp(); 

    // else restore manager global lists and mappings
    restore_manager();

    /* Maintenance functions, step into them after
     * armie, so as not to trip up file functions
     */

    //clean up lists
    set_alarm(5.0, 0.0, &startup_checks());

    // check for times of council votes: set one up or
    // finalize one in progress if needed
    set_alarm(300.0, 0.0, &check_vote_end());

    // schedule backups if needed
    set_alarm(420.0, 0.0, &backup_manager());
}

/* Function name: startup_checks
 * Description  : Cleans up non-existant players and apprentices who
 *                have run out of time.
 */
public void
startup_checks()
{
    int i, j;
    string *player_list, *company_list;

/*************************************/
/* Clean-up checks for various lists */
/************************************/

    /* Check for timed out apprentices here. */
    player_list = m_indexes(gApprenticeTime);
    for (i = sizeof(player_list) - 1; i >= 0; i--)
    {
        /* The apprentice has not been approved in time. Remove him.
         * If there is a vote in process, give them a break.
         * Check also to make sure that they aren't an approved or full 
         * ranger, that is victim of lost rangers.o problem 
         */
        if (gApprenticeTime[player_list[i]] <= time() &&
          !MEMBER_VOTE_ITH->query_vote(player_list[i]) &&
          !MEMBER_VOTE_NOR->query_vote(player_list[i]) &&
          SECURITY->exist_player(player_list[i]) &&
          (MANAGER->query_ranger_level(player_list[i]) < APPROVED_APP_LEVEL))
              add_to_be_expelled(player_list[i],
                "You have been an apprentice for too long.\n", 1);
    }

    /* Check for timed out players on no-rejoin list. */
    player_list = m_indexes(gRejoinTime);
    for (i = sizeof(player_list) - 1; i >= 0; i--)
    {
        /* More than 2 months have passed. Remove from no-rejoin list. */
        if (gRejoinTime[player_list[i]] <= time())
            remove_no_rejoin(player_list[i]);
    }

    /* Check for timed out outlaws. */
    player_list = query_outlaw_members();
    for (i = sizeof(player_list) - 1; i >= 0; i--)
    {
        /* The outlaw has served their time, remove him now. */
        if (gOutlaw[player_list[i]] <= time())
            remove_outlaw(player_list[i]);
    }

/* Per councils request, notorious removed by appeal only */
/*
    player_list = query_notorious_members();
    for (i = sizeof(player_list) - 1; i >= 0; i--)
    {
        if (gNotoriousOutlaw[player_list[i]] <= time())
        {
            remove_notorious_outlaw(player_list[i]);
            add_outlaw(player_list[i]);
        }
    }
*/

    /* Make an array of each company and step through 
     * to determine whether player exists or not. Remove
     * from roster if player is gone from game. 
     */
    company_list = m_indexes(gRangers);
    for (i = sizeof(company_list) - 1; i >= 0; i--)
    {
        /* Get a list of the players in this company. */
        player_list = gRangers[company_list[i]];
        /* Check for non-existant Rangers and remove them. */
        for (j = sizeof(player_list) - 1; j >= 0; j--)
        {
            /* Remove from list if Ranger no longer exists. */
            if (!SECURITY->exist_player(gRangers[company_list[i]][j]))
                remove_ranger(gRangers[company_list[i]][j]);
        }
    }
    return;
}

/* Function name: check_vote_end
 * Description  : Does some checking on elections, whether to end a current
 *                election or start a regular captain election.
 */
public void
check_vote_end()
{
    int time_to_end;

    if (query_election("north"))
    {
        /* If the election should be over, end it. Otherwise, set
           an alarm to do so at the right time. */
        time_to_end = gElection["north"][0] + ELECTION_TIME_OUT;
        if (time_to_end <= time())
            end_election("north");
        else if (time_to_end < (SECURITY->query_uptime_limit() +
          SECURITY->query_start_time()))
        {
            /* Set an alarm to end the vote only if it will end before
               Armageddon. */
            set_alarm(itof(time_to_end - time()), 0.0,
                &end_election("north"));
        }
    }

    if (query_election("ithilien"))
    {
        /* If the election should be over, end it. Otherwise, set
           an alarm to do so at the right time. */
        time_to_end = gElection["ithilien"][0] + ELECTION_TIME_OUT;
        if (time_to_end <= time())
            end_election("ithilien");
        else if (time_to_end < (SECURITY->query_uptime_limit() +
          SECURITY->query_start_time()))
        {
            /* Set an alarm to end the vote only if it will end before
               Armageddon. */
            set_alarm(itof(time_to_end - time()), 0.0,
              &end_election("ithilien"));
        }

    }

    /* Check for regular elections here. Start nominations if time is up. */
    if (!query_election("north") &&
      gElection["north"][0] + REGULAR_ELECTION_TIME <= time())
        start_election("north", 1);

    if (!query_election("ithilien") &&
      gElection["ithilien"][0] + REGULAR_ELECTION_TIME <= time())
        start_election("ithilien", 1);

// if there is no captain (e.g., captain has stepped down. quit, etc.),
// then start company election
    if (!query_election("ithilien") &&
        (strlen(query_council_name(0,"ithilien")) == 0))
        start_election("ithilien", 1);
    if (!query_election("north") &&
        (strlen(query_council_name(0,"north")) == 0))
        start_election("north", 1);
}

/* Function name: move_old
 * Description  : Moves old backup files.
 */
public void
move_old(string str)
{
    if (file_size(str + ".o") > 0)
        rename(str + ".o",
            str + "." + TIME2FORMAT(file_time(str + ".o"), "mmddyyyy"));
}

/* Function name: cleanup_backups
 * Description  : Gets rid of backups that are older than six months.
 */
public void
cleanup_backups()
{
    string *backups = get_dir(RANGERS_MANAGER + "backups/");
    int i, month;

    for (i = sizeof(backups) - 1; i >= 0; i--)
    {
        backups[i] = RANGERS_MANAGER + "backups/" + backups[i];
        /* Over 182 days old (6 months) */
        if (TIME2NUM(time() - file_time(backups[i]))[0] > BACKUP_CLEANUP)
        {
            rm(RANGERS_MANAGER + "backups/" + backups[i]);
          /* Too spammy, removed. */
          /*  rlog(RANGERS_WIZ_LOG, "Cleaned up: " + backups[i]); */
        }
    }
}

/* Function name: test_backup
 * Description  : Tests if a file needs to be backed up.
 * Arguments    : string filename
 */
public void
test_backup(string filename)
{
    string buffer, backup = RANGERS_MANAGER + "backups/" + filename;
    int fdays = TIME2NUM(time() - file_time(backup + ".o"))[0];
    
    if (fdays < BACKUP_DAYS && file_size(backup + ".o") > 0)
        return;

    buffer = read_file(RANGERS_MANAGER + filename + ".o");
    if (!strlen(buffer))
        return;

    move_old(backup);

    write_file(backup + ".o", buffer);
    rlog(RANGERS_WIZ_LOG, "Backed up: " + filename);
    return;
}

/* Function name: backup_manager
 * Description  : Backups up the .o files every once in a while.
 */
public void
backup_manager()
{
    test_backup("admincmds");
    test_backup("apprenticetime");
    test_backup("banished");
    test_backup("candidates");
    test_backup("council");
    test_backup("election");
    test_backup("expelled");
    test_backup("impeachers");
    test_backup("logbook");
    test_backup("masters");
    test_backup("nominators");
    test_backup("notoriousoutlaw");
    test_backup("punish");
    test_backup("outlaw");
    test_backup("rangers");
    test_backup("rejointime");
    test_backup("reward");
    test_backup("specialists");
    test_backup("tasks");
    test_backup("unpunish");
    test_backup("votedin");
    test_backup("votedout");
    test_backup("votes");

    cleanup_backups();
}

/* Function name: cycle_file
 * Description  : Cycles a file so that it does not get too big.
 * Arguments    : string filename - the name of the file
 *                int size - the number of bytes to preserve
 * Returns      : 1 if successful, 0 if not
 */
private nomask int
cycle_file(string filename, int size)
{
    int filesize;

    /* To prevent any abuse. */
    if (filename[0..strlen(RANGERS_DIR)-1] != RANGERS_DIR)
        return 0;

    filesize = file_size(filename);

    /* File doesn't exist (-1), is a directory (-2) or is of 0 bytes */
    if (filesize == -1 || filesize == -2 || filesize == 0)
        return 0;

    if (size > filesize)
        return 0;

    rename(filename, filename + ".old");
    return 1;
}

/* Function name: rlog
 * Description  : Log an action according to company.
 * Arguments    : string log - Should be one of: north, ithilien, or all
 *                             otherwise, it will log that file in the
 *                             ranger log directory.
 *                string text - the text to log
 * Returns      : 1 on success, 0 on failure
 */
public int
rlog(string log, string text)
{
    string *log_arr;

    if (!strlen(text))
        return 0;

    if (!strlen(log))
        log = "all";

    log = lower_case(log);

    switch(log)
    {
    case RANGERS_WIZ_LOG:
        /* This cycles itself */
        log_file(RANGERS_WIZ_LOG, ctime(time()) + ": " + text + "\n");
        return 1;
    case "north":
    case NORTH_LOG:
        cycle_file(NORTH_LOG, LOG_SIZE);
        write_file(NORTH_LOG, ctime(time()) + ": " + text + "\n");
        return 1;
    case "ithilien":
    case ITHILIEN_LOG:
        cycle_file(ITHILIEN_LOG, LOG_SIZE);
        write_file(ITHILIEN_LOG, ctime(time()) + ": " + text + "\n");
        return 1;
    case "apprentice":
    case APPRENTICE_LOG:
        cycle_file(APPRENTICE_LOG, LOG_SIZE);
        write_file(APPRENTICE_LOG, ctime(time()) + ": " + text + "\n");
        return 1;
    case "approved":
    case "all":
    case RANGERS_LOG:
        cycle_file(RANGERS_LOG, LOG_SIZE);
        write_file(RANGERS_LOG, ctime(time()) + ": " + text + "\n");
        return 1;
    default:
        log_arr = (explode(log, "/"));
        if (sizeof(log_arr) > 1)
            log = log_arr[sizeof(log_arr) - 1];

        cycle_file(RANGERS_LOG_DIR + log, LOG_SIZE);
        write_file(RANGERS_LOG_DIR + log, ctime(time()) + ": " + text + "\n");
        return 1;
    }
}

/* Function name: send_message
 * Description  : Sends a message to a Ranger
 * Arguments    : object target - who to send the message from
 *                string text   - What the message says
 *                string sender - (optional) Who sent the message,
 *                                default: The Council of Rangers
 * Returns      : 1/0 success/failure
 */
public varargs int
send_message(object target, string text, string sender)
{
    object note;

    if (!objectp(target) || !strlen(text))
        return 0;

    if (!strlen(sender))
        sender = "The Council of Rangers";

    if (environment(target)->query_domain() == "Gondor")
        target->catch_tell("A small ferret scurries up to you.\n" +
            "You retrieve the message tied around his neck.\n" +
            "The small ferret scurries away again.\n");
    else
        target->catch_tell("A white carrier pigeon lands on your shoulder.\n" +
          "You retrieve a message from the holster bound to its foot.\n" +
          "The pigeon flaps its wings and flies away again.\n");

    note = clone_object(RANGERS_OBJ + "message");
    note->set_message("\n" + text);
    note->set_sender(sender);
    note->move(target, 1);
    return 1;
}

/* Function name: save_manager
 * Description  : Saves the mappings of manager to individual .o files.
 * Arguments    : mapping map - name of the mapping
 *                string filename - filename to save it to
 */
private void
save_manager(mapping map, string filename)
{
    save_map(map, RANGERS_MANAGER + filename);
}

public void
save_manager_temp()
{
    save_manager(gAdminCmds , RANGERS_MANAGER + "admincmds");
    save_manager(gApprenticeTime , RANGERS_MANAGER + "apprenticetime");
    save_manager(gBanished , RANGERS_MANAGER + "banished");
    save_manager(gCandidates , RANGERS_MANAGER + "candidates");
    save_manager(gCouncil , RANGERS_MANAGER + "council");
    save_manager(gElection , RANGERS_MANAGER + "election");
    save_manager(gExpelled , RANGERS_MANAGER + "expelled");
    save_manager(gImpeachers , RANGERS_MANAGER + "impeachers");
    save_manager(gLogBook , RANGERS_MANAGER + "logbook");
    save_manager(gMasters , RANGERS_MANAGER + "masters");
    save_manager(gNominators , RANGERS_MANAGER + "nominators");
    save_manager(gNotoriousOutlaw , RANGERS_MANAGER + "notoriousoutlaw");
    save_manager(gPunish , RANGERS_MANAGER + "punish");
    save_manager(gOutlaw, RANGERS_MANAGER + "outlaw");
    save_manager(gRangers, RANGERS_MANAGER + "rangers");
    save_manager(gRejoinTime, RANGERS_MANAGER + "rejointime");
    save_manager(gReward, RANGERS_MANAGER + "reward");
    save_manager(gSpecialists, RANGERS_MANAGER + "specialists");
    save_manager(gTasks, RANGERS_MANAGER + "tasks");
    save_manager(gUnpunish, RANGERS_MANAGER + "unpunish");
    save_manager(gVotedIn, RANGERS_MANAGER + "votedin");
    save_manager(gVotedOut, RANGERS_MANAGER + "votedout");
    save_manager(gVotes, RANGERS_MANAGER + "votes");
}

/* Function name: restore_manager
 * Description  : Called once upon startup to restore the mapping
 *                variables from the individual .o files they're
 *                stored in.
 */
public void
restore_manager()
{
    gAdminCmds       = restore_map(RANGERS_MANAGER + "admincmds");
    gApprenticeTime  = restore_map(RANGERS_MANAGER + "apprenticetime");
    gBanished        = restore_map(RANGERS_MANAGER + "banished");
    gCandidates      = restore_map(RANGERS_MANAGER + "candidates");
    gCouncil         = restore_map(RANGERS_MANAGER + "council");
    gElection        = restore_map(RANGERS_MANAGER + "election");
    gExpelled        = restore_map(RANGERS_MANAGER + "expelled");
    gImpeachers      = restore_map(RANGERS_MANAGER + "impeachers");
    gLogBook         = restore_map(RANGERS_MANAGER + "logbook");
    gMasters         = restore_map(RANGERS_MANAGER + "masters");
    gNominators      = restore_map(RANGERS_MANAGER + "nominators");
    gNotoriousOutlaw = restore_map(RANGERS_MANAGER + "notoriousoutlaw");
    gPunish          = restore_map(RANGERS_MANAGER + "punish");
    gOutlaw          = restore_map(RANGERS_MANAGER + "outlaw");
    gRangers         = restore_map(RANGERS_MANAGER + "rangers");
    gRejoinTime      = restore_map(RANGERS_MANAGER + "rejointime");
    gReward          = restore_map(RANGERS_MANAGER + "reward");
    gSpecialists     = restore_map(RANGERS_MANAGER + "specialists");
    gUnpunish        = restore_map(RANGERS_MANAGER + "unpunish");
    gTasks           = restore_map(RANGERS_MANAGER + "tasks");
    gVotedIn         = restore_map(RANGERS_MANAGER + "votedin");
    gVotedOut        = restore_map(RANGERS_MANAGER + "votedout");
    gVotes           = restore_map(RANGERS_MANAGER + "votes");
    gVirtues         = restore_map(RANGERS_MANAGER + "virtues");
}

/* Function name: post_note
 * Description  : Post a note on a specified board object.
 * Arguments    : object board - the board object to post to
 *                string header - the header of the note
 *                string poster - the name to post as
 *                string content - the content of the note
 * Returns      : 1 for success, 0 for failure
 */
public int
post_note(object board, string header, string poster, string content)
{
    if (!objectp(board) || !strlen(header) || !strlen(poster) ||
      !strlen(content))
        return 0;

    if (!SECURITY->exist_player(poster))
        return(board->create_note(header, poster, content));
}

/* Function name: query_apprentice_time
 * Description  : Returns the time that an apprentice will timeout
 * Arguments    : string name - the name of the apprentice
 * Returns      : the time
 */
public int
query_apprentice_time(string name)
{
    if (!strlen(name))
        return -1;

    name = capitalize(name);

    if (member_array(name, m_indexes(gApprenticeTime)) != -1)
        return gApprenticeTime[name];
    else
        return -1;
}

/*
 * Function name: query_apprentice_join_time
 * Description  : When is the soonest an apprentice can join?
 *                Two weeks from join time is the minimum currently.
 * Arguments    : string name - the name of the apprentice
 * Returns      : the time
 */
public int
query_apprentice_join_time(string name)
{
    if (!strlen(name))
        return -1;

    name = capitalize(name);

    if (member_array(name, m_indexes(gApprenticeTime)) != -1)
        return (gApprenticeTime[name] - FOURTEEN_WEEKS);
    else
        return -1;
}

/* Function name: query_apprentice_log
 * Description  : Returns the log for the indicated apprentice
 * Arguments    : string name - the apprentice
 *                int view_all - return open and restricted comments
 *                               if 1, only open if 0
 * Returns      : The log entries and their writers.
 */
public string
query_apprentice_log(string name, int view_all = 0)
{
    int i, size;
    string text = "";

    if (!strlen(name))
        return ("No name received.\n");

    name = capitalize(name);

    if (member_array(name, m_indexes(gLogBook)) == -1)
        return ("No log entry for " + name + ".\n");

    for (i = 0, size = sizeof(gLogBook[name]); i < size; i +=3)
    {
        /* This should read: If we are viewing restricted messages
           and the message is restricted, go ahead. Or if the message
           is unrestricted, go ahead. */
        if ((view_all && gLogBook[name][i + 2]) ||
          (!gLogBook[name][i + 2]))
            text += (gLogBook[name][i + 1] + " wrote: " +
                gLogBook[name][i] + "\n");
    }

    return text;
}

/* Function name: query_log_writers
 * Description  : Returns the writers of an apprentice's logs.
 * Arguments    : string name - the name of the apprentice
 * Returns      : string * - the names of the writers of
 *                an apprentice's logs.
 */
public string *
query_log_writers(string name)
{
    int i, size;
    string *writers = ({});

    if (!strlen(name))
        return ({});

    name = capitalize(name);

    if (member_array(name, m_indexes(gLogBook)) == -1)
        return ({});

    for (i = 0, size = sizeof(gLogBook[name]); i < size; i +=3)
            writers += ({ gLogBook[name][i + 1] });

    return writers;
}

/* Function name: add_apprentice_log
 * Description  : Adds an entry into an apprentice's logbook.
 * Arguments    : string name - the name of the apprentice
 *                string writer - the name of the person making the entry
 *                string message - the message entered
 *                int restricted - is the message restricted reading?
 * Returns      : A string of success or specific failure message
 */
public string
add_apprentice_log(string name, string writer, string message,
  int restricted = 1)
{
    string text;

    if (!strlen(name) || !strlen(writer) || !strlen(message))
        return ("Not enough arguments.\n");

    name = capitalize(name);
    writer = capitalize(writer);

    if (!query_ranger_level(writer))
        return("Only Rangers may write in an apprentice's logbook!\n");

    if ((query_ranger_level(name) > APPROVED_APP_LEVEL) ||
      (!query_ranger_level(name)))
        return("Only apprentices and approved apprentices have a " +
            "logbook.\n");

    if (member_array(name, m_indexes(gLogBook)) == -1)
        gLogBook += ([name : ({ message, writer, restricted }) ]);
    else
        gLogBook[name] += ({ message, writer, restricted });

    save_manager(gLogBook, "logbook");

    text = ((restricted ? "Restricted" : "Open") + " log entry added for " +
        name);

    /* Add it to the log viewable by all council. */
    rlog("all", text + " by " + writer + ".");

    return text + ".\n";
}

/* Function name: remove_apprentice_log
 * Description  : Removes the entire logbook for an apprentice. Used
 *                when an approved apprentice is advanced to a company
 *                or an apprentice or approved apprentice leaves the Rangers.
 * Arguments    : string - name
 */
public void
remove_apprentice_log(string name)
{
    if (!strlen(name))
        return;

    name = capitalize(name);

    if (member_array(name, m_indexes(gLogBook)) != -1)
    {
        gLogBook = m_delete(gLogBook, name);
        save_manager(gLogBook, "logbook");
    }

    return;
}

/* Function name: query_voted_in
 * Description  : Checks to see if an apprentice has been voted
 *                into a company.
 * Arguments    : string name - the name of the apprentice
 *                string company - the name of the company
 * Returns      : 1 for true, 0 for false
 */
public int
query_voted_in(string name, string company)
{
    if (!strlen(name))
        return 0;

    name = capitalize(name);
    company = lower_case(company);

    return (member_array(name, gVotedIn[company]) != -1);
}

/* Function name: add_voted_in
 * Description  : Adds an apprentice to a company's voted in list.
 * Arguments    : string name - the name of the apprentice
 *                string company - the name of the company
 */
public void
add_voted_in(string name, string company)
{
    if (!strlen(name) || !strlen(company))
        return;

    company = lower_case(company);
    name = capitalize(name);

    if (member_array(name, gVotedIn[company]) == -1)
    {
        gVotedIn[company] += ({ name });
        save_manager(gVotedIn, "votedin");
        add_ranger(name, "approved", 1);
        rlog(company, name + " is now allowed to join " +
            capitalize(company) + ".");
    }
}

/* Function name: remove_voted_in
 * Description  : Removes a name from the voted-in list for a company
 * Arguments    : string name - the name to be removed
 *                string company - the company to remove from or 'all'
 */
public void
remove_voted_in(string name, string company)
{
    if (!strlen(name) || !strlen(company))
        return;

    company = lower_case(company);
    name = capitalize(name);

    if (member_array(name, gVotedIn[company]) != -1)
    {
        gVotedIn[company] -= ({ name });
        save_manager(gVotedIn, "votedin");
    }
}

/* Function name: query_voted_out
 * Description  : Checks if a name is on a company's voted out list
 * Arguments    : string name - the name to check
 *                string company - the company to check for
 * Returns      : 1 if true, 0 if false
 */
public int
query_voted_out(string name, string company)
{
    if (!strlen(name) || !strlen(company))
        return 0;

    company = lower_case(company);
    name = capitalize(name);

    return (member_array(name, gVotedOut[company]) != -1);
}

/* Function name: add_voted_out
 * Description  : Adds a name to a company's voted-out list
 *                Adds an apprentice to the expell list if
 *                this is the second company that has voted
 *                them out.
 * Arguments    : string name - the name to add
 *                string company - the company to add it to
 */
public void
add_voted_out(string name, string company)
{
    if (!strlen(name) || !strlen(company))
        return;

    company = lower_case(company);
    name = capitalize(name);

    if ((company == "north" && query_voted_out(name, "ithilien")) ||
      (company == "ithilien" && query_voted_out(name, "north")))
    {
        add_to_be_expelled(name, "Could not join a company.\n");
        return;
    }

    if (member_array(name, gVotedOut[company]) == -1)
    {
        gVotedOut[company] += ({ name });
        save_manager(gVotedOut, "votedout");
        rlog(company, name + " was not allowed to join " +
            capitalize(company) + ".");
    }
}

/* Function name: remove_voted_out
 * Description  : Removes a name from a company's voted out list
 * Arguments    : string name - the name to remove
 *                string company - the company to remove it from
 */
public void
remove_voted_out(string name, string company)
{
    if (!strlen(name) || !strlen(company))
        return;

    company = lower_case(company);
    name = capitalize(name);

    if (company == "all")
    {
        remove_voted_out(name, "ithilien");
        remove_voted_out(name, "north");
    }

    if (member_array(name, gVotedOut[company]) != -1)
    {
        gVotedOut[company] -= ({ name });
        save_manager(gVotedOut, "votedout");
    }
}


/* Function name: query_ranger_level
 * Description  : Returns the membership level
 * Arguments    : string name - the name of the person to give status on
 * Returns      : 0 - Not a Ranger at all
 *                1 - Apprentice
 *                2 - Approved Apprentice
 *                3 - Ranger of North
 *                4 - Ranger of Ithilien
 */
public int
query_ranger_level(string name)
{
    if (!strlen(name))
        return 0;

    name = capitalize(name);

    if (member_array(name, gRangers["ithilien"]) != -1)
        return ITHILIEN_LEVEL;
    else if (member_array(name, gRangers["north"]) != -1)
        return NORTH_LEVEL;
    else if (member_array(name, gRangers["approved"]) != -1)
        return APPROVED_APP_LEVEL;
    else if (member_array(name, gRangers["apprentice"]) != -1)
        return APPRENTICE_LEVEL;
    else
        return 0;
}

/* Function name: query_ranger_company
 * Description  : Returns the string company name
 * Arguments    : string name - the name of the person to give status on
 * Returns      : apprentice, approved, north, ithilien
 */
public string
query_ranger_company(string name)
{
    if (!strlen(name))
        return "";

    name = capitalize(name);

    switch(query_ranger_level(name))
    {
    case ITHILIEN_LEVEL:
        return "ithilien";
    case NORTH_LEVEL:
        return "north";
    case APPROVED_APP_LEVEL:
        return "approved";
    case APPRENTICE_LEVEL:
        return "apprentice";
    default:
        return "";
    }
}

/* Function name: query_company_members
 * Description  : What players belong to this company?
 * Arguments    : int company - the company to check
 *                   APPRENTICE_LEVEL = apprentice
 *                   APPROVED_APP_LEVEL = approved
 *                   NORTH_LEVEL = north
 *                   ITHILIEN_LEVEL = ithilien
 * Returns      : an array of company members
 */
public string *
query_company_members(int company)
{
    if (!intp(company))
        return ({});

    switch (company)
    {
        case APPRENTICE_LEVEL:
            return gRangers["apprentice"];
        case APPROVED_APP_LEVEL:
            return gRangers["approved"];
        case NORTH_LEVEL:
            return gRangers["north"];
        case ITHILIEN_LEVEL:
            return gRangers["ithilien"];
        default:
            return ({});
    }
}

/* Function name: query_ranger
 * Description  : Returns 1 if the person is a Ranger or in the indicated
 *                company
 * Arguments    : string name - the name to check
 *                string company - the company to check against (optional)
 * Returns      : 1 if matches, 0 if not
 */
public varargs int
query_ranger(string name, string company = "")
{
    if (!strlen(name))
        return 0;

    name = capitalize(name);

    if (!strlen(company))
    {
        if (query_ranger_level(name))
            return 1;
        return 0;
    }

    if (lower_case(company) == query_ranger_company(name))
        return 1;
    return 0;
}

/* Function name: add_ranger
 * Description  : Add a Ranger to the indicated company
 * Arguments    : string name - the person to add
 *                string company - the company to add them to: apprentice,
 *                approved, ithilien, north
 *                int overide - Overide the checks and add them to a
 *                company no matter the previous status.
 * Returns      : 1 if successful, 0 if not
 */
public varargs int
add_ranger(string name, string company, int overide = 0)
{
    string current_company;

    if (!strlen(name) || !strlen(company))
        return 0;

    name = capitalize(name);
    company = lower_case(company);

    /* They're already a member of this company. */
    if (query_ranger(name, company))
        return 0;

    current_company = query_ranger_company(name);

    if (overide)
    {
        /* Remove him from his previous company if necessary. */
        if (strlen(current_company))
            remove_ranger(name, 0);

        /* Add him to the new company. */
        gRangers[company] += ({ name });

        /* Set the time that the apprentice will be kicked out. */
        if (company == "apprentice")
        {
            gApprenticeTime += ([ name : time() + APPRENTICE_TIME_OUT ]);
            save_manager(gApprenticeTime, "apprenticetime");
        }
        rlog(company, name + " was made " + LANG_ADDART(company) + " Ranger " +
            "by a wizard or due to transfering from the old guild.");
        save_manager(gRangers, "rangers");
        return 1;
    }

    /* Must be an apprentice first. */
    if (!strlen(current_company) && company != "apprentice")
        return 0;

    if (strlen(current_company))
    {
        /* Can't approve non-apprentices. */
        if (company == "approved" && current_company != "apprentice")
            return 0;

        /* Remove their logbook longer need approval. */
        if (current_company == "approved" && company != "apprentice")
            remove_apprentice_log(name);

        /* Remove him from his present company (with no punishment) so
           we can add him to his new company. */
        remove_ranger(name, 0);
    }

    /* Add him to the new company. */
    gRangers[company] += ({ name });

    /* Set the time that the apprentice will be kicked out. */
    if (company == "apprentice")
    {
        gApprenticeTime += ([ name : time() + APPRENTICE_TIME_OUT ]);
        save_manager(gApprenticeTime, "apprenticetime");
    }
    if ((company == "ithilien") || (company == "north"))
    {
        remove_voted_in(name, "ithilien");
        remove_voted_in(name, "north");
    }

    rlog(company,
        (this_interactive()->query_real_name() ?
        capitalize(this_interactive()->query_real_name()) : MANAGER_NAME ) +
        " made " + name + " " + LANG_ADDART(company) + " Ranger.");
    save_manager(gRangers, "rangers");
    return 1;
}

/* Function name: remove_ranger
 * Description  : Update the lists when a Ranger is removed
 * Arguments    : string name - the ranger to remove
 *                int rem_reward - Should rewards be removed (are they
 *                                 being kicked out completely or just
 *                                 moving around ranks?)
 *                    1 to remove rewards
 *                    0 to leave rewards
 * Returns      : 1 if successful, 0 if not
 */
public varargs int
remove_ranger(string name, int rem_reward = 1)
{
    int i;
    string company;

    if (!strlen(name))
        return 0;

    name = capitalize(name);

    /* They aren't a ranger anymore, no reason to reward them. */
    if (rem_reward)
        remove_to_be_rewarded(name);

    /* Find out the Ranger's company name. */
    company = query_ranger_company(name);
    if (!strlen(company))
        return 0;

    /* Remove them from council if necessary. */
    remove_council(name);

    /* Remove them as a master if necessary. */
    remove_master(name);

    /* Remove them as a specialist if necessary. */
    remove_specialist(name);

    /* Remove their logbook. The Ranger is either being companied or
       leaving. Either way, the logbook is no longer needed.
       and the reward base must be reset to 0 */
    if (company == "approved")
    {
        remove_apprentice_log(name);
        (find_player(lower_case(name)))->set_skill(SS_REWARDED, 0);
        remove_task_number(name);
    }

    if (company == "apprentice")
    {
        /* Remove their logbook */
        if (rem_reward)
            remove_apprentice_log(name);

        /* Remove time they will be kicked out since they're leaving. */
        gApprenticeTime = m_delete(gApprenticeTime, name);

        save_manager(gApprenticeTime, "apprenticetime");

    }

    /* They must wait for a pre-determined period before they can rejoin. */
    if (rem_reward)
        add_no_rejoin(name);

//remove traces from other files
    if (query_voted_out(name, "ithilien") &&
        query_voted_out(name, "north"))
        remove_voted_out(name, "all");

    company = lower_case(company);

    rlog(company, (this_interactive()->query_real_name() ?
        capitalize(this_interactive()->query_real_name()) : MANAGER_NAME ) +
        " removed " + name + " as " + LANG_ADDART(company) + " Ranger.");



    /* Finally, remove the ranger from the ranger array by company. */
    gRangers[company] -= ({ name });

    save_manager(gRangers, "rangers");
    return 1;
}

/* Function name: query_council
 * Description  : Is this person on council?
 * Arguments    : string name - the person to test
 *                string company - optional company to test
 * Returns      : The position on council or -1 if not on council
 */
public varargs int
query_council(string name, string company = "")
{
    if (!strlen(name))
        return 0;

    name = capitalize(name);
    company = lower_case(company);

    /* company not given, find the company of the Ranger */
    if (!strlen(company))
        company = query_ranger_company(name);

    /* name isn't even a (full) Ranger, much less council */
    if (!strlen(company) || company == "apprentice" || company == "approved")
        return -1;

    return (member_array(name, gCouncil[company]));
}

/* Function name: add_council
 * Description  : Adds a name to the list of council members
 * Arguments    : string name - the name to add
 *                int position - the position to add them to:
 *                               0 - Captain
 *                               1 - Lieutenant
 *                               2 - Sergeant
 *                string company - optional company to add to
 * Returns      : 1 if successful, 0 if not
 */
public varargs int
add_council(string name, int position, string company = "")
{
    string old, pos_name;

    /* No name, nothing more to do */
    if (!strlen(name) || !intp(position))
        return 0;

    name = capitalize(name);
    company = lower_case(company);

    /* Company not given, find it now */
    if (!strlen(company))
        company = query_ranger_company(name);

    /* Not a (full) Ranger, can't be on council. */
    if (!strlen(company) || company == "apprentice" || company == "approved")
        return 0;

    /* Position must fall within the bounds. */
    if (position >= CAPTAIN_POSITION && position <= SERGEANT_POSITION)
    {

        /* Set the time for the next election if new captain. */
        if (position == CAPTAIN_POSITION)
        {
            /* Reset regular election time. */
            gElection[company][0] = time();

            /* Remove Lt. and Sgt. */
            remove_council(gCouncil[company][LIEUTENANT_POSITION]);
            remove_council(gCouncil[company][SERGEANT_POSITION]);
        }

        /* Check for previous Ranger of this position and remove if needed. */
        old = gCouncil[company][position];
        if (strlen(old))
            remove_council(old);

        /* Check for previous positions of this Ranger and remove if needed. */
        if (member_array(name, gCouncil[company]) != -1)
            remove_council(name);

        /* Get the string name of the company for logging. */
        pos_name = (position == CAPTAIN_POSITION ? "Captain" : "");
        if (position > 0)
        {
            pos_name = (position ==
                LIEUTENANT_POSITION ? "Lieutenant" : "Sergeant");
        }

        /* Log the addition to the council. */
        rlog(company, name + " was added to the " + capitalize(company) +
            " council as " + pos_name + " by " +
            (this_interactive()->query_real_name() ?
            capitalize(this_interactive()->query_real_name()) :
            MANAGER_NAME ));
        rlog("all", name + " was added to the " + capitalize(company) +
            " council as " + pos_name + " by " +
            (this_interactive()->query_real_name() ?
            capitalize(this_interactive()->query_real_name()) :
            MANAGER_NAME ));

        /* Add the person to the position indicated in the company indicated */
        gCouncil[company][position] = name;
        save_manager(gCouncil, "council");
        return 1;
    }

    /* Somehow the position passed to the function was out of bounds. */
    return 0;
}

/* Function name: remove_council
 * Description  : Removes a name from the list of council members.
 * Arguments    : string name - the name to remove
 * Returns      : 1 if successful, 0 if not
 */
public int
remove_council(string name)
{
    int position;
    string company;

    if (!strlen(name))
        return 0;

    name = capitalize(name);
    company = lower_case(query_ranger_company(name));
    position = query_council(name, company);

    if (position >= CAPTAIN_POSITION && position <= SERGEANT_POSITION)
    {
        /* Remove their list of commands */
        if (member_array(name, m_indexes(gAdminCmds)) != -1)
            remove_all_admin_cmds(name);

        rlog(company, name + " was removed from the " + capitalize(company) +
            " council by " + (this_interactive()->query_real_name() ?
            capitalize(this_interactive()->query_real_name()) :
            MANAGER_NAME ));
        rlog("all", name + " was removed from the " + capitalize(company) +
            " council by " + (this_interactive()->query_real_name() ?
            capitalize(this_interactive()->query_real_name()) :
            MANAGER_NAME ));

        gCouncil[company][position] = "";
        save_manager(gCouncil, "council");
        return 1;
    }


    return 0;
}

/* Function name: query_is_council
 * Description  : Checks if someone is on council or not.
 * Arguments    : string name - the name to check
 * Returns      : 1 if on council, 0 if not, rather than the position
 */
public int
query_is_council(string name)
{
    if (!strlen(name))
        return 0;

    return (query_council(capitalize(name)) != -1);
}

/* Function name: query_council_name
 * Description  : what is the name of the player in a council position?
 * Arguments    : int position - the position to check
 *                    0 = captain = CAPTAIN_POSITION
 *                    1 = lieutenant = LIEUTENANT_POSITION
 *                    2 = sergeant = SERGEANT_POSITION
 *                string company - the company to check for
 * Returns      : the name of the player in that council position
 */
public string
query_council_name(int position, string company)
{
    company = lower_case(company);

    if (member_array(company, m_indexes(gCouncil)) != -1)
        return gCouncil[company][position];

    return "";
}

/* Function name: query_title_name
 * Description  : What is this person's title?
 * Arguments    : string name - the name of the ranger
 * Returns      : <Captain/Lieutenant/Sergeant/Ranger> of <the North/Ithilien>
 *                or Apprentice of the Rangers
 */
public string
query_title_name(string name)
{
    string company;

    name = capitalize(name);
    if (!strlen(name) || !query_ranger(name))
        return "Non-Ranger";

    company = query_ranger_company(name);
    if (company == "approved" || company == "apprentice")
        return "Apprentice of the Rangers";

    company = capitalize(company);
    if (company == "North")
        company = "the North";

    switch(query_council(name))
    {
    case CAPTAIN_POSITION:
        return ("Captain of " + company);
    case LIEUTENANT_POSITION:
        return ("Lieutenant of " + company);
    case SERGEANT_POSITION:
        return ("Sergeant of " + company);
    default:
        return ("Ranger of " + company);
    }
}

/* Function name: query_admin_cmds
 * Description  : Which commands does this person have access to?
 * Arguments    : string name - the name to check
 * Returns      : string * - an array of commands they are able to use.
 */
public string *
query_admin_cmds(string name)
{
    if (!strlen(name))
        return 0;

    name = capitalize(name);

    if (member_array(name, m_indexes(gAdminCmds)) != -1)
        return gAdminCmds[name];

    return ({ });
}

/* Function name: add_admin_cmd
 * Description  : Adds a command that a person has access to.
 *                Checking for valid admin command is done in the
 *                admin soul where this function is used, as it is
 *                easier to manage the list of commands from there.
 * Arguments    : string name - the name to add a command for
 *                string cmd - the command to add
 * Returns      : 1 if successful, 0 if not
 */
public int
add_admin_cmd(string name, string cmd)
{
    if (!strlen(name) || !strlen(cmd))
        return 0;

    name = capitalize(name);
    cmd = lower_case(cmd);

    /* Only officers can get commands. */
    if (!query_is_council(name))
        return 0;

    if (member_array(name, m_indexes(gAdminCmds)) != -1)
        gAdminCmds[name] += ({ cmd });
    else
        gAdminCmds += ([ name : ({ cmd }) ]);


    rlog(query_ranger_company(name), name + " was granted the " +
        "ability to " + cmd + " by " + (this_interactive()->query_real_name() ?
        capitalize(this_interactive()->query_real_name()) : MANAGER_NAME ) +
        ".");
    save_manager(gAdminCmds, "admincmds");
    return 1;
}

/* Function name: remove_admin_cmd
 * Description  : Removes access to a command for a person.
 * Arguments    : string name - the name to remove the command from
 *                string cmd - the command to remove
 * Returns      : 1 if successful, 0 if not
 */
public int
remove_admin_cmd(string name, string cmd)
{
    if (!strlen(name) || !strlen(cmd))
        return 0;

    name = capitalize(name);
    cmd = lower_case(cmd);

    if (member_array(name, m_indexes(gAdminCmds)) != -1)
    {
        rlog(query_ranger_company(name), name + " had the " +
            "ability to " + cmd + " removed by " +
            (this_interactive()->query_real_name() ?
            capitalize(this_interactive()->query_real_name()) :
            MANAGER_NAME ) + ".");
        gAdminCmds[name] -= ({ cmd });
        save_manager(gAdminCmds, "admincmds");
        return 1;
    }

    return 0;
}

/* Function name: remove_all_admin_cmds
 * Description  : Remove all commands for this name.
 * Arguments    : string name - the name to remove commands for
 * Returns      : 1 if successful, 0 if not
 */
public int
remove_all_admin_cmds(string name)
{
    if (!strlen(name))
        return 0;

    name = capitalize(name);

    if (member_array(name, m_indexes(gAdminCmds)) != -1)
    {
        rlog(query_ranger_company(name), name + " had all " +
            "council commands removed by " +
            (this_interactive()->query_real_name() ?
            capitalize(this_interactive()->query_real_name()) :
            MANAGER_NAME ) + ".");
        gAdminCmds = m_delete(gAdminCmds, name);
        save_manager(gAdminCmds, "admincmds");
        return 1;
    }

    return 0;
}

/* Function name: query_task_number
 * Description  : Which task did we complete last?
 * Arguments    : string name - the name of the apprentice
 * Returns      : The number of the task last completed.
 */
public int
query_task_number(string name)
{
    if (!strlen(name))
        return 0;

    name = capitalize(name);
    if (member_array(name, m_indexes(gTasks)) == -1)
        return 0;
    else
        return gTasks[name];
}

/* Function name: increment_task_number
 * Description  : Increment the task number that the apprentice is on.
 * Arguments    : string apprentice - the name of an apprentice
 * Returns      : 1/0 - successfully incremented/not successfully
 *                      incremented
 */
public int
increment_task_number(string apprentice)
{
    if (!strlen(apprentice))
        return 0;

    apprentice = capitalize(apprentice);

    /* Only apprentices have tasks kept track of */
    if (query_ranger_level(apprentice) != APPRENTICE_LEVEL)
        return 0;

    if (member_array(apprentice, m_indexes(gTasks)) == -1)
        gTasks += ([ apprentice : 1 ]);
    else
        gTasks[apprentice]++;

    /*
     * This would automatically start a vote for the
     * apprentice when they completed their seventh task.
     * I'm commenting it out for now, though I may put it
     * back in later.
    if (gTasks[apprentice] >= 7)
    {
        if (!MEMBER_VOTE_NOR->query_vote(apprentice) &&
          !MEMBER_VOTE_ITH->query_vote(apprentice))
        {
            MEMBER_VOTE_NOR->start_vote(apprentice);
            MEMBER_VOTE_ITH->start_vote(apprentice);
        }
    }
    */

    save_manager(gTasks, "tasks");
    return 1;
}

/* Function name: remove_task_number
 * Description  : Removes the apprentice from the task list.
 * Arguments    : string apprentice - the name of the apprentice
 */
public void
remove_task_number(string apprentice)
{
    if (!strlen(apprentice))
        return;

    apprentice = capitalize(apprentice);

    gTasks = m_delete(gTasks, apprentice);
    save_manager(gTasks, "tasks");
    return;
}

/* Function name: query_is_master
 * Description  : Is this person a master ranger?
 * Arguments    : string name - the name to check
 * Returns      : 1/0 - on the list/not on the list
 */
public int
query_is_master(string name)
{
    if (!strlen(name))
        return 0;

    name = capitalize(name);

    if (member_array(name, m_indexes(gMasters)) != -1)
        return 1;

    return 0;
}

/* Function name: query_master_specialty
 * Description  : What is the specialty of this master?
 * Arguments    : string name - the name to check
 * Returns      : string - the specialty of the master.
 */
public string
query_master_specialty(string name)
{
    if (!strlen(name))
        return "";

    name = capitalize(name);

    if (member_array(name, m_indexes(gMasters)) != -1)
        return gMasters[name];

    return "";
}

/* Function name: add_master
 * Description  : Adds a name and specialty type to the list of master rangers
 * Arguments    : string name - the name to add
 * Returns      : 1 if successful, 0 if not
 */
public int
add_master(string name)
{
    string specialty_type;

    if (!strlen(name))
        return 0;

    name = capitalize(name);

    if (!query_ranger(name))
        return 0;

    specialty_type = query_specialist_specialty(name);

    if (!strlen(specialty_type))
        return 0;

    if (member_array(specialty_type, MASTER_TITLES) == -1)
        return 0;

    gMasters += ([ name : specialty_type ]);
    remove_specialist(name);

    rlog(query_ranger_company(name), name + " was made a Master " +
        specialty_type + " by " + (this_interactive()->query_real_name() ?
        capitalize(this_interactive()->query_real_name()) :
        MANAGER_NAME ) + ".");

    save_manager(gMasters, "masters");
    return 1;
}

/* Function name: remove_master
 * Description  : Removes a name from the list of master rangers.
 * Arguments    : string name - the name to remove
 * Returns      : 1 if successful, 0 if not
 */
public int
remove_master(string name)
{
    object who;

    if (!strlen(name))
        return 0;

    who = find_player(lower_case(name));

    name = capitalize(name);

    if (query_is_master(name))
    {
        if (objectp(who))
            who->catch_tell("You have been removed as a Master " +
                query_master_specialty(name) + ".\n");

        rlog(query_ranger_company(name), name + " was removed as Master " +
            query_master_specialty(name) + " by " +
            (this_interactive()->query_real_name() ?
            capitalize(this_interactive()->query_real_name()) :
            MANAGER_NAME ) + ".");
        gMasters = m_delete(gMasters, name);
        save_manager(gMasters, "masters");
        return 1;
    }

    return 0;
}

/* Function name: query_is_specialist
 * Description  : Is this person a specialist?
 * Arguments    : string name - the name to check
 * Returns      : 1/0 - on the list/not on the list
 */
public int
query_is_specialist(string name)
{
    if (!strlen(name))
        return 0;

    name = capitalize(name);

    if (member_array(name, m_indexes(gSpecialists)) != -1 &&
      (gSpecialists[name][1] > 0))
        return 1;
    else
        return 0;
}

/* Function name: query_specialist_specialty
 * Description  : What is this person's specialty?
 * Arguments    : string name - the name to check
 * Returns      : string - the specialty of the master.
 */
public string
query_specialist_specialty(string name)
{
    if (!strlen(name))
        return "";

    name = capitalize(name);

    if (member_array(name, m_indexes(gSpecialists)) != -1)
        return gSpecialists[name][0];
    else
        return "";
}

/*
 * Function name: advance_specialist
 * Description  : Raises a specialist's rank
 * Arguments    : string name - the name of the specialist
 *                int i - Used to raise the rank of a 0 level specialist
 * Returns      : 1/0 success/failure
 */
public varargs int
advance_specialist(string name, int i = 0)
{
    if (!strlen(name))
        return 0;

    name = capitalize(name);

    if (query_specialist_rank(name) >= 5 || query_specialist_rank(name) < 0)
        return 0;

    if (!query_specialist_rank(name) && !i)
        return 0;

    gSpecialists[name][1] += 1;
    save_manager(gSpecialists, "specialists");
    return 1;
}

/*
 * Function name: query_specialist_rank
 * Description  : Checks the rank of the specialist.
 * Arguments    : string name - the name of the player to check
 * Returns      : The rank of the specialist
 */
public int
query_specialist_rank(string name)
{
    name = capitalize(name);
    if (member_array(name, m_indexes(gSpecialists)) != -1)
        return min(max(gSpecialists[name][1], 0), 5);
    else
        return -1;
}

/* Function name: add_specialist
 * Description  : Adds a name and specialty type to the list of ranger
 *                specialists
 * Arguments    : string name - the name to add
 *                string specialty_type - the specialty to add
 * Returns      : 1 if successful, 0 if not
 */
public int
add_specialist(string name, string specialty_type)
{
    object who;
    string company;

    if (!strlen(name) || !strlen(specialty_type))
        return 0;

    name = capitalize(name);
    specialty_type = capitalize(specialty_type);

    if (!query_ranger(name))
        return 0;

    if (member_array(specialty_type, MASTER_TITLES) == -1)
        return 0;

    who = find_player(lower_case(name));

    /* Player is not in the realms. We need to note this fact with
       a 0 in the rank category for the shadow to check when they
       next log in to make sure they are of high enough rank to
       become a specialist. */
    if (!objectp(who))
    {
        if (strlen(query_is_specialist(name)))
            gSpecialists[name] = ({ specialty_type, 0 });
        else
            gSpecialists += ([ name : ({ specialty_type, 0 }) ]);

        rlog(query_ranger_company(name), name + " was logged to " +
            "be made a " + specialty_type + " by " +
            (this_interactive()->query_real_name() ?
            capitalize(this_interactive()->query_real_name()) :
            MANAGER_NAME ) + ".");
    }
    else
    {
        if (who->query_ranger_rank() < SPECIALTY_RANK)
        {
            /* Too low rank for specialty */
            rlog(query_ranger_company(name), "Failed to assign a specialty to " + name +
                " as they are not yet experienced enough as a Ranger.");
            return 0;
        }
        else
        {
            who->catch_tell("\nYou have been assigned the new " +
                "task of being a " + specialty_type + ".\n");
            rlog(query_ranger_company(name), name + " was made a " +
                specialty_type);

            if (strlen(query_is_specialist(name)))
                gSpecialists[name] = ({ specialty_type, 1 });
            else
                gSpecialists += ([ name : ({ specialty_type, 1 }) ]);
        }
    }

    save_manager(gSpecialists, "specialists");
    return 1;
}

/* Function name: remove_specialist
 * Description  : Removes a name from the list of ranger specialists.
 * Arguments    : string name - the name to remove
 * Returns      : 1 if successful, 0 if not
 */
public int
remove_specialist(string name)
{
    object who;

    if (!strlen(name))
        return 0;

    name = capitalize(name);
    who = find_player(lower_case(name));

    if (query_is_specialist(name))
    {
        if (objectp(who))
            who->catch_tell("You have been removed as " +
                LANG_ADDART(query_specialist_specialty(name)) + ".\n");

        rlog(query_ranger_company(name), name + " was removed as " +
            query_specialist_specialty(name) + " by " +
            (this_interactive()->query_real_name() ?
            capitalize(this_interactive()->query_real_name()) :
            MANAGER_NAME ) + ".");
        gSpecialists = m_delete(gSpecialists, name);
        save_manager(gSpecialists, "specialists");
        return 1;
    }

    return 0;
}

/* Function name: query_to_be_expelled
 * Description  : Is this person on the list of rangers to be expelled?
 * Arguments    : string name - the name to check
 * Returns      : the reason for being expelled and the soft level
 */
public string *
query_to_be_expelled(string name)
{
    if (!strlen(name))
        return ({});

    name = capitalize(name);
    if (member_array(name, m_indexes(gExpelled)) != -1)
        return gExpelled[name];
    else
        return ({});
}

/* Function name: add_to_be_expelled
 * Description  : Adds a name to the list of rangers to be expelled.
 * Arguments    : string name - the name to add
 *                string reason - the reason for being expelled
 *                int soft - Will there be a punishment or not?
 * Returns      : 1 if successful, 0 if not
 */
public varargs int
add_to_be_expelled(string name, string reason, int soft = 0)
{
    if (!strlen(name))
        return 0;

    name = capitalize(name);

    if (!query_ranger(name))
        return 0;

    if (!stringp(reason))
        reason = "";

    if (query_ranger_level(name) < APPROVED_APP_LEVEL)
        soft = 1;

    if (!sizeof(query_to_be_expelled(name)))
    {
        if (!objectp(find_player(lower_case(name))))
            rlog(query_ranger_company(name), name + " was marked to be " +
                "expelled by " + (this_interactive()->query_real_name() ?
                capitalize(this_interactive()->query_real_name()) :
                MANAGER_NAME ) + " for " +
                reason + ".");
        else
            rlog(query_ranger_company(name), name + " was expelled by " +
                (this_interactive()->query_real_name() ?
                capitalize(this_interactive()->query_real_name()) :
                MANAGER_NAME ) + " for " + reason + ".");
        gExpelled += ([ name : ({ reason, soft }) ]);
        save_manager(gExpelled, "expelled");
        return 1;
    }

    return 0;
}

/* Function name: remove_to_be_expelled
 * Description  : Removes a name from the list of rangers to be expelled.
 * Arguments    : string name - the name to remove
 * Returns      : 1 if successful, 0 if not
 */
public int
remove_to_be_expelled(string name)
{
    if (!strlen(name))
        return 0;

    name = capitalize(name);
    if (sizeof(query_to_be_expelled(name)))
    {
        rlog(query_ranger_company(name), name + " was removed from the " +
            "list of Rangers to be expelled by " +
            (this_interactive()->query_real_name() ?
            capitalize(this_interactive()->query_real_name()) :
            MANAGER_NAME ) + ".");

        gExpelled = m_delete(gExpelled, name);
        save_manager(gExpelled, "expelled");
        return 1;
    }

    return 0;
}

/* Function name: query_no_rejoin
 * Description  : Is this person on the list of those who cannot rejoin?
 * Arguments    : string name - the name to check
 * Returns      : 1 - on the list, 0 - not on the list
 */
public int
query_no_rejoin(string name)
{
    if (!strlen(name))
        return 0;

    name = capitalize(name);
    return (member_array(name, m_indexes(gRejoinTime)) != -1);
}

/* Function name: add_no_rejoin
 * Description  : Adds a name to the list of players mapped to the time
 *                they left the rangers. If they are already on the list,
 *                overwrites the old time and adds the new time.
 * Arguments    : string name - the name to add
 */
public int
add_no_rejoin(string name)
{
    int rejoin_time = time() + REJOIN_TIME;

    if (!strlen(name))
        return 0;

    name = capitalize(name);

// if player had been voted out from both companies, has to wait 3 months
// to be allowed to rejoin since there was no confidence in player
    if (query_voted_out(name, "ithilien") &&
        query_voted_out(name, "north"))
        rejoin_time = time() + 3 * REJOIN_TIME;

//else just the regular rejoin time for timed out apprentices and 
//players who left guild voluntarily
    if (!query_no_rejoin(name))
        gRejoinTime += ([ name : rejoin_time ]);
    else
        gRejoinTime[name] = rejoin_time;
    
    rlog("all", (this_interactive()->query_real_name() ?
        capitalize(this_interactive()->query_real_name()) :
        MANAGER_NAME ) + " banned " + name + " from rejoining " +
        "the Rangers until " + ctime(rejoin_time) + ".");

    save_manager(gRejoinTime, "rejointime");
    return 1;
}

/* Function name: remove_no_rejoin
 * Description  : Removes a name from the list of those who may not rejoin.
 * Arguments    : string name - the name to remove
 * Returns      : 1 if successful, 0 if not
 */
public int
remove_no_rejoin(string name)
{
    if (!strlen(name))
        return 0;

    name = capitalize(name);
    if (query_no_rejoin(name))
    {
        rlog("all", (this_interactive()->query_real_name() ?
            capitalize(this_interactive()->query_real_name()) :
            MANAGER_NAME ) + " allowed " + name + " to rejoin the Rangers.");

        gRejoinTime = m_delete(gRejoinTime, name);
        save_manager(gRejoinTime, "rejointime");

        return 1;
    }
    return 0;
}

/* Function name: query_to_be_rewarded
 * Description  : Is this person on the list of rangers to be rewarded?
 * Arguments    : string name - the name to check
 *                string reward_type - what type of reward to check
 * Returns      : the reasons for being rewarded
 */
public string *
query_to_be_rewarded(string name, string reward_type)
{
    if (!strlen(name))
        return ({});

    if (!strlen(reward_type))
        return ({});

    name = capitalize(name);
    reward_type = lower_case(reward_type);

    if (member_array(name, m_indexes(gReward)) != -1 &&
      sizeof(gReward[name][reward_type]))
        return gReward[name][reward_type];
    else
        return ({});
}

/* Function name: add_to_be_rewarded
 * Description  : Adds a name and reason to the list of rangers to be
 *                rewarded if not already there. Adds another reason if
 *                a reward is already waiting.
 * Arguments    : string name - the name to add
 *                string reward_type - the kind of reward to add
 *                string reason - the reason for being rewarded
 * Returns      : 1 if successful, 0 if not
 */
public int
add_to_be_rewarded(string name, string reward_type = "moderately",
  string reason = "meritorious deeds")
{
    if (!strlen(name))
        return 0;

    name = capitalize(name);

    if (!query_ranger(name))
        return 0;

    /* Is it a valid reward type? */
    reward_type = lower_case(reward_type);
    if (member_array(reward_type,
      ({"slightly", "moderately", "generously"})) == -1)
        return 0;

    if (!m_sizeof(gReward[name]))
        gReward += ([ name : ([ reward_type : ({ reason })]) ]);
    else if (!sizeof(gReward[name][reward_type]))
        gReward[name] += ([ reward_type : ({ reason }) ]);
    else
        gReward[name][reward_type] += ({ reason });

    save_manager(gReward, "reward");
    return 1;
}

/* Function name: remove_to_be_rewarded
 * Description  : Removes a name from the list of rangers to be rewarded.
 * Arguments    : string name - the name to remove
 *                string reward_type - The reward type list to remove
 * Returns      : 1 if successful, 0 if not
 */
public varargs int
remove_to_be_rewarded(string name, string reward_type = "")
{
    if (!strlen(name))
        return 0;

    name = capitalize(name);

    if (!strlen(reward_type))
    {
        if (m_sizeof(gReward[name]))
        {
            gReward = m_delete(gReward, name);
            save_manager(gReward, "reward");
            return 1;
        }

        return 0;
    }

    reward_type = lower_case(reward_type);

    if (sizeof(query_to_be_rewarded(name, reward_type)))
    {
        gReward = m_delete(gReward[name], reward_type);
        save_manager(gReward, "reward");
        return 1;
    }

    return 0;
}

/* Function name: reward_ranger
 * Description  : Do the actual reward of the Ranger if reward waiting
 *                Logging for rewards will be handled in soul/admin.c.
 * Arguments    : string ranger - The Ranger to reward
 * Returns      : 1 if successful
 */
public varargs int
reward_ranger(string ranger, string reward_type = "")
{
    int i, total_reward = 0;
    object target;
    string note_txt = "", *rewards = ({});

    if (!strlen(ranger))
        return 0;

    ranger = capitalize(ranger);
    target = find_player(lower_case(ranger));
    if (!objectp(target))
        return 0;

    if (strlen(reward_type))
    {
        reward_type = lower_case(reward_type);
        switch(reward_type)
        {
        case "moderately":
            total_reward = MODERATE_REWARD;
            break;
        case "generously":
            total_reward = GENEROUS_REWARD;
            break;
        case "slightly":
        default:
            total_reward = SLIGHT_REWARD;
            break;
        }

        target->set_skill(SS_REWARDED, target->query_skill(SS_REWARDED) +
            total_reward);

        /* No messages if the reward is being given directly. */
        /* The reward command will handle those messages. */
        return 1;
    }

    if (member_array(ranger, m_indexes(gReward)) == -1)
        return 0;

    rewards = query_to_be_rewarded(ranger, "slightly");
    if (sizeof(rewards))
    {
        for (i = sizeof(rewards) - 1; i >= 0; i--)
        {
            total_reward += SLIGHT_REWARD;
            note_txt += "You have been slightly rewarded for " +
                rewards[i] + "\n";
        }
    }

    rewards = query_to_be_rewarded(ranger, "moderately");
    if (sizeof(rewards))
    {
        for (i = sizeof(rewards) - 1; i >= 0; i--)
        {
            total_reward += MODERATE_REWARD;
            note_txt += "You have been moderately rewarded for " +
                rewards[i] + "\n";
        }
    }

    rewards = query_to_be_rewarded(ranger, "generously");
    if (sizeof(rewards))
    {
        for (i = sizeof(rewards) - 1; i >= 0; i--)
        {
            total_reward += GENEROUS_REWARD;
            note_txt += "You have been generously rewarded for " +
                rewards[i] + "\n";
        }
    }

    total_reward += target->query_skill(SS_REWARDED);
    target->set_skill(SS_REWARDED, total_reward);
    send_message(target, note_txt);
    remove_to_be_rewarded(ranger);
    return 1;
}

/* Function name: query_to_be_punished
 * Description  : Is this person on the list of rangers to have their
 *                punishment added?
 * Arguments    : string name - the name to check
 * Returns      : string * - the punishment to deal out and why
 */
public string *
query_to_be_punished(string name)
{
    if (!strlen(name))
        return ({ "", "" });

    name = capitalize(name);

    if (member_array(name, m_indexes(gPunish)) != -1)
        return gPunish[name];
    else
        return ({ "", "" });
}

/* Function name: add_to_be_punished
 * Description  : Adds a name and punish type to the list of rangers to
 *                have their punishment added if not already there.
 * Arguments    : string name - the name to add
 *                string punish_type - the kind of punishment/removal to add
 *                punish options - no spells, no skills, no brawl
 *                string why - Why is this ranger being punished?
 * Returns      : 1 if successful, 0 if not
 */
public int
add_to_be_punished(string name, string punish_type, string why)
{
    if (!strlen(name))
        return 0;

    if (!strlen(punish_type))
        return 0;

    punish_type = lower_case(punish_type);
    name = capitalize(name);

    if (!query_ranger(name))
        return 0;

    if (member_array(punish_type, m_indexes(PUNISHMENTS)) == -1)
        return 0;

    if (strlen(query_to_be_punished(name)[0]))
    {
        gPunish[name] = ({ punish_type, why });
        /* Punishment logged to be given next time target logs in. */
        rlog(MANAGER->query_ranger_company(name), name +
            " marked to be punished with " + punish_type + " for " + why +
            " by " + capitalize(this_player()->query_real_name()));
    }
    else
    {
        gPunish += ([ name : ({ punish_type, why }) ]);
        /* Punishment logged to be given next time target logs in. */
        rlog(MANAGER->query_ranger_company(name), name +
            " marked to be punished with " + punish_type + " for " + why +
            " by " + capitalize(this_player()->query_real_name()));
    }

    save_manager(gPunish, "punish");
    return 1;
}

/* Function name: remove_to_be_punished
 * Description  : Removes a name from the list of rangers to be punished.
 * Arguments    : string name - the name to remove
 * Returns      : 1 if successful, 0 if not
 */
public int
remove_to_be_punished(string name)
{
    if (!strlen(name))
        return 0;

    name = capitalize(name);

    if (!strlen(query_to_be_punished(name)[0]))
        return 0;

    gPunish = m_delete(gPunish, name);
    save_manager(gPunish, "punish");
    return 1;
}

/* Function name: punish_ranger
 * Description  : Do the actual punishment of the Ranger if punishment waiting
 * Arguments    : string ranger - The Ranger to punish
 *                string punish_type - type of punishment
 *                string why - Why is this Ranger being punished?
 * Returns      : 1 if successful
 */
public varargs int
punish_ranger(string name, string punish_type, string why)
{
    object target;

    if (!strlen(name))
        return 0;

    name = capitalize(name);

    if (!query_ranger(name))
        return 0;

    target = find_player(lower_case(name));
    if (!objectp(target))
        return 0;

    if (strlen(punish_type))
    {
        punish_type = lower_case(punish_type);
        if (member_array(punish_type, m_indexes(PUNISHMENTS)) == -1)
            return 0;

        if (punish_type != "no_skills")
            target->set_skill(SS_PUNISHMENT, PUNISHMENTS[punish_type]);
        else
            lower_skills(target);

        rlog(MANAGER->query_ranger_company(name), name + " punished with "
            + punish_type + " for " + why +
            " by " + (this_interactive()->query_real_name() ?
            capitalize(this_interactive()->query_real_name()) :
            MANAGER_NAME ) + ".");

        /* No messages if the punishment is being given directly. */
        /* The punish command will handle those messages. */
        return 1;
    }
    else
        punish_type = query_to_be_punished(name)[0];

    if (!strlen(punish_type))
        return 0;

    if (!strlen(why))
        why = query_to_be_punished(name)[1];

    if (punish_type != "no_skills")
        target->set_skill(SS_PUNISHMENT, PUNISHMENTS[punish_type]);
    else
        lower_skills(target);

    send_message(target, "You have been punished with " + punish_type +
        " for your actions.\n");

    remove_to_be_punished(name);
    return 1;
}

/* Function name: lower_skills
 * Description  : Carry out the lowering of skills punishment. It is
 *                immediate and requires no lifting, as it simply lowers
 *                specific Ranger skills.
 * Arguments    : object ranger - the punished ranger
 * Returns      : 1/0 - successful, unsuccessful
 */
public int
lower_skills(object ranger)
{
    int i, size;

    if (!objectp(ranger))
        return 0;

    for (i = 0, size = sizeof(SKILLS); i < size; i++)
    {
        if (SKILLS[i] != SS_WEP_SWORD)
        {
            ranger->set_skill(SKILLS[i],
                (ranger->query_skill(SKILLS[i]) * 3) / 4);
        }
        else
        {
            if (ranger->query_skill(SKILLS[i]) > BLADEMSTR_SWRD)
                ranger->set_skill(SKILLS[i]),
                    max(((ranger->query_skill(SKILLS[i]) * 3) / 4),
                    BLADEMSTR_SWRD);
        }
    }
}

/* Function name: query_to_be_unpunished
 * Description  : Is this person on the list of rangers to have their
 *                punishment removed?
 * Arguments    : string name - the name to check
 * Returns      : 1/0 - on the list/not on the list
 */
public int
query_to_be_unpunished(string name)
{
    if (!strlen(name))
        return 0;

    name = capitalize(name);

    if (member_array(name, m_indexes(gUnpunish)) != -1)
        return 1;
    else
        return 0;
}

/* Function name: add_to_be_unpunished
 * Description  : Adds a name list of rangers to have their punishment
 *                removed if not already there.
 * Arguments    : string name - the name to add
 * Returns      : 1 if successful, 0 if not
 */
public int
add_to_be_unpunished(string name)
{
    if (!strlen(name))
        return 0;

    name = capitalize(name);

    if (!query_ranger(name))
        return 0;

    if (strlen(query_to_be_punished(name)[0]))
    {
        remove_to_be_punished(name);
        return 1;
    }

    if (!query_to_be_unpunished(name))
    {
        gUnpunish += ([ name : 1 ]);
        save_manager(gUnpunish, "unpunish");
        return 1;
    }
    else
        return 0;
}

/* Function name: remove_to_be_unpunished
 * Description  : Removes a name from the list of rangers to have their
 *                punishment removed.
 * Arguments    : string name - the name to remove
 * Returns      : 1 if successful, 0 if not
 */
public int
remove_to_be_unpunished(string name)
{
    if (!strlen(name))
        return 0;

    name = capitalize(name);

    if (!query_to_be_unpunished(name))
        return 0;

    gUnpunish = m_delete(gUnpunish, name);
    save_manager(gUnpunish, "unpunish");
    return 1;
}

/* Function name: unpunish_ranger
 * Description  : Do the actual punishment removal of the Ranger if waiting
 * Arguments    : string name - The Ranger to unpunish
 * Returns      : 1 if successful
 */
public int
unpunish_ranger(string name)
{
    object target;

    if (!strlen(name))
        return 0;

    name = capitalize(name);

    if (!query_ranger(name))
        return 0;

    target = find_player(lower_case(name));
    if (!objectp(target))
        return 0;

    if (!query_to_be_unpunished(name))
        return 0;

    if (target->query_skill(SS_PUNISHMENT))
    {
        target->remove_skill(SS_PUNISHMENT);
        send_message(target, "Your punishment has been lifted!\n");
        rlog(MANAGER->query_ranger_company(name), name + " had punishment " +
            "lifted by " + (this_interactive()->query_real_name() ?
            capitalize(this_interactive()->query_real_name()) :
            MANAGER_NAME ) + ".");
    }

    remove_to_be_unpunished(name);
    return 1;
}

/* Function name: query_is_outlaw
 * Description  : Is this person on the list of outlaws?
 * Arguments    : string name - the name to check
 * Returns      : 1 - on the list, 0 - not on the list
 */
public int
query_is_outlaw(string name)
{
    if (!strlen(name))
        return 0;

    name = capitalize(name);
    return (member_array(name, m_indexes(gOutlaw)) != -1);
}

/* Function name: query_outlaw
 * Description  : Is this person on the list of outlaws?
 * Arguments    : string name - the name to check
 * Returns      : 1 - on the list, 0 - not on the list
 */
public int
query_outlaw(string name)
{
    if (!strlen(name))
        return 0;

    name = capitalize(name);
    return (member_array(name, m_indexes(gOutlaw)) != -1);
}

/* Function name: add_outlaw
 * Description  : Adds a name to the list of outlaws mapped to the time
 *                they become an outlaw. If they are already on the list,
 *                overwrites the old time and adds the new time to expire.
 * Arguments    : string name - the name to add
 */
public int
add_outlaw(string name)
{
    if (!strlen(name))
        return 0;

    name = capitalize(name);

    if (!SECURITY->exist_player(name))
        return 0;

    /* We don't want to outlaw a Ranger! */
    if (!query_ranger(name))
    {
        if (!query_is_outlaw(name))
        {
            gOutlaw += ([ name : time() + OUTLAW_TIME_OUT]);
            rlog("all", name + " was made an outlaw of the Rangers by " +
                (this_interactive()->query_real_name() ?
                capitalize(this_interactive()->query_real_name()) :
                MANAGER_NAME ));
        }
        else
            gOutlaw[name] = time() + OUTLAW_TIME_OUT;


        save_manager(gOutlaw, "outlaw");
        return 1;
    }

    return 0;
}

/* Function name: remove_outlaw
 * Description  : Removes a name from the list of outlaws.
 * Arguments    : string name - the name to remove
 * Returns      : 1 if successful, 0 if not
 */
public int
remove_outlaw(string name)
{
    if (!strlen(name))
        return 0;

    name = capitalize(name);
    if (query_is_outlaw(name))
    {
        gOutlaw = m_delete(gOutlaw, name);
        rlog("all", name + " was removed as an outlaw of the Rangers by " +
            (this_interactive()->query_real_name() ?
            capitalize(this_interactive()->query_real_name()) :
            MANAGER_NAME ));
        save_manager(gOutlaw, "outlaw");
        return 1;
    }

    return 0;
}

/* Function name: query_outlaw_members
 * Description  : who are the present outlaws of the Westlands?
 * Arguments    : none
 * Returns      : an array of outlaws
 */
public string *
query_outlaw_members()
{
    return m_indexes(gOutlaw);
}

/* Function name: query_notorious_outlaw
 * Description  : Is this person on the list of notorious outlaws?
 * Arguments    : string name - the name to check
 * Returns      : 1 - on the list, 0 - not on the list
 */
public int
query_notorious_outlaw(string name)
{
    if (!strlen(name))
        return 0;

    name = capitalize(name);
    return (member_array(name, m_indexes(gNotoriousOutlaw)) != -1);
}

/* Function name: add_notorious_outlaw
 * Description  : Adds a name to the list of notorious outlaws.
 * Arguments    : string name - the name to add
 */
public int
add_notorious_outlaw(string name)
{
    if (!strlen(name))
        return 0;

    name = capitalize(name);

    /* Don't add an outlaw that doesn't exist. */
    if (!SECURITY->exist_player(name))
        return 0;

    if (!query_ranger(name))
    {
        if (!query_notorious_outlaw(name))
        {
            gNotoriousOutlaw += ([ name : time() + NOTORIOUS_TIME_OUT ]);
            rlog("all", name + " was made a notorious outlaw of the " +
                "Rangers by " + (this_interactive()->query_real_name() ?
                capitalize(this_interactive()->query_real_name()) :
                MANAGER_NAME ));
            save_manager(gNotoriousOutlaw, "notoriousoutlaw");
            return 1;
        }
        else
        {
            gNotoriousOutlaw[name] = (time() + NOTORIOUS_TIME_OUT);
            rlog("all", name + " had notorious outlaw time extended by " +
                (this_interactive()->query_real_name() ?
                capitalize(this_interactive()->query_real_name()) :
                MANAGER_NAME ));
            save_manager(gNotoriousOutlaw, "notoriousoutlaw");
            return 1;
        }
    }
    return 0;
}

/* Function name: remove_notorious_outlaw
 * Description  : Removes a name from the list of notorious outlaws.
 * Arguments    : string name - the name to remove
 */
public int
remove_notorious_outlaw(string name)
{
    if (!strlen(name))
        return 0;

    name = capitalize(name);
    if (query_notorious_outlaw(name))
    {
        gNotoriousOutlaw = m_delete(gNotoriousOutlaw, name);
        rlog("all", name + " was removed as notorious outlaw of the " +
            "Rangers by " + (this_interactive()->query_real_name() ?
            capitalize(this_interactive()->query_real_name()) :
            MANAGER_NAME ));
        save_manager(gNotoriousOutlaw, "notoriousoutlaw");
        return 1;
    }
    return 0;
}

/* Function name: query_notorious_members
 * Description  : who are the present notorious outlaws of the Rangers?
 * Arguments    : none
 * Returns      : an array of notorious outlaws
 */
public string *
query_notorious_members()
{
    return m_indexes(gNotoriousOutlaw);
}

/* Function name: query_banished
 * Description  : Is this person on the banished list?
 * Arguments    : string name - the name to check
 * Returns      : 1/0 - Banished/Not
 */
public int
query_banished(string name)
{
    if (!strlen(name))
        return 0;

    name = capitalize(name);
    return (member_array(name, m_indexes(gBanished)) != -1);
}

/* Function name: query_major_virtue
 * Description  : What major virtue has been selected by this ranger
 * Arguments    : string name - the name to check
 * Returns      : 1-7 one of the RANGER_MAJOR_VIRTUE values
 */
public int
query_major_virtue(string name)
{
    if (!strlen(name))
        return 0;

    name = capitalize(name);
    
    int* virtue = gVirtues[name];
    
    if (!sizeof(virtue))
    {
        set_major_virtue(name, RANGER_MAJOR_VIRTUE_DEFAULT);
        return RANGER_MAJOR_VIRTUE_DEFAULT;
    }
    
    return virtue[VIRTUE_MAJOR_VIRTUE_IDX];
}

/* Function name: set_major_virtue
 * Description  : Update which major virtue has been selected by this ranger
 * Arguments    : string name - the name to check
 *  Virtue      : 1-7 one of the RANGER_MAJOR_VIRTUE values
 */
public int
set_major_virtue(string name, int virtue)
{
    name = capitalize(name);
    
    int* virtues = gVirtues[name];
    if (!sizeof(virtues))
    {
        virtues = ({ RANGER_MAJOR_VIRTUE_DEFAULT, time(),
                     RANGER_MINOR_VIRTUE_DEFAULT, time() });
    }
    
    virtues[VIRTUE_MAJOR_VIRTUE_IDX] = virtue;
    virtues[VIRTUE_MAJOR_VIRTUE_TIME_IDX] = time();
    
    gVirtues += ([ name : virtues ]);

    rlog(RANGERS_WIZ_LOG, name + " has selected major virtue " +
         MAJOR_VIRTUES_TO_NAME[virtue] + ".");

    save_manager(gVirtues, "virtues");
    return 1;
}

/* Function name: set_minor_virtue
 * Description  : Update which minor virtue has been selected by this ranger
 * Arguments    : string name - the name to check
 *  Virtue      : 1-7 one of the RANGER_MINOR_VIRTUE values
 */
public int
set_minor_virtue(string name, int virtue)
{
    name = capitalize(name);
    
    int* virtues = gVirtues[name];
    if (!sizeof(virtues))
    {
        virtues = ({ RANGER_MAJOR_VIRTUE_DEFAULT, time(),
                     RANGER_MINOR_VIRTUE_DEFAULT, time() });
    }
    
    virtues[VIRTUE_MINOR_VIRTUE_IDX] = virtue;
    virtues[VIRTUE_MINOR_VIRTUE_TIME_IDX] = time();
    
    gVirtues += ([ name : virtues ]);

    rlog(RANGERS_WIZ_LOG, name + " has selected minor virtue " +
         MINOR_VIRTUES_TO_NAME[virtue] + ".");

    save_manager(gVirtues, "virtues");
    return 1;
}

public int can_change_minor_virtue(string name)
{
    int current = query_minor_virtue(name);
    if (current == RANGER_MINOR_VIRTUE_DEFAULT)
    {
        return 1;
    }
    name = capitalize(name);
    
    int* virtues = gVirtues[name];
    if (time() > virtues[VIRTUE_MINOR_VIRTUE_TIME_IDX] +
        RANGER_MINOR_VIRTUE_CHANGE_TIME)
    {
        return 1;
    }
        
    return 0;   
}

public int can_change_major_virtue(string name)
{
    int current = query_major_virtue(name);
    if (current == RANGER_MAJOR_VIRTUE_DEFAULT)
    {
        return 1;
    }
    name = capitalize(name);
    
    int* virtues = gVirtues[name];
    if (time() > virtues[VIRTUE_MAJOR_VIRTUE_TIME_IDX] +
        RANGER_MAJOR_VIRTUE_CHANGE_TIME)
    {
        return 1;
    }
        
    return 0;   
}


/* Function name: query_minor_virtue
 * Description  : What minor virtue has been selected by this ranger
 * Arguments    : string name - the name to check
 * Returns      : 1-7 one of the RANGER_MINOR_VIRTUE values
 */
public int
query_minor_virtue(string name)
{
    if (!strlen(name))
        return 0;

    name = capitalize(name);
    
    int* virtue = gVirtues[name];
    
    if (!sizeof(virtue))
    {
        set_minor_virtue(name, RANGER_MINOR_VIRTUE_DEFAULT);
        return RANGER_MINOR_VIRTUE_DEFAULT;
    }
    
    return virtue[VIRTUE_MINOR_VIRTUE_IDX];
}


/* Function name: add_banished
 * Description  : Adds a name to the banished list.
 * Arguments    : string name - the name to add
 */
public int
add_banished(string name)
{
    if (!strlen(name))
        return 0;

    name = capitalize(name);

    if (!SECURITY->exist_player(name) || query_ranger(name))
        return 0;

    if (!query_banished(name))
    {
        gBanished += ([ name : 1 ]);
        rlog("all", name + " was banished from the Rangers by " +
            (this_interactive()->query_real_name() ?
            capitalize(this_interactive()->query_real_name()) :
            MANAGER_NAME ) + ".");
        save_manager(gBanished, "banished");
        return 1;
    }

    return 0;
}

/* Function name: remove_banished
 * Description  : Removes a name from the banished list.
 * Arguments    : string name - the name to remove
 */
public int
remove_banished(string name)
{
    if (!strlen(name))
        return 0;

    name = capitalize(name);

    if (query_banished(name))
    {
        gBanished = m_delete(gBanished, name);
        rlog("all", name + " was unbanished from the Rangers by " +
            (this_interactive()->query_real_name() ?
            capitalize(this_interactive()->query_real_name()) :
            MANAGER_NAME ) + ".");
        save_manager(gBanished, "banished");
        return 1;
    }
    return 0;
}

/* Function name: end_election
 * Description  : Ends the election
 * Arguments    : string company - the company to end the election for
 * Returns      : 1 on success, 0 on failure
 */
public int
end_election(string company)
{
    int election_type;
    mapping final_winners = ([]);

    if (!strlen(company))
        return 0;

    company = lower_case(company);
    if (!query_election(company))
        return 0;

    election_type = gElection[company][1];
    post_election_results(company, election_type, gVotes[company]);

    gElection[company][1] = 0;

    switch(election_type)
    {
    case 1:
        final_winners = find_winners(company, 2);
        gCandidates[company] = m_indexes(final_winners);
        remove_nominator(1, company);
        start_election(company, 2);
        break;
    case 2:
        final_winners = find_winners(company, 1);

        /* Uh oh, there was a tie. Better call another vote on the ties. */
        if (m_sizeof(final_winners) > 1)
        {
            gCandidates[company] = m_indexes(final_winners);
            start_election(company, 2);
        }

         /* Change Captain here */
        if (!add_council(m_indexes(final_winners)[0], CAPTAIN_POSITION,
          company))
        {

        /* Eeks! Something went wrong. Call the vote over again with
            the last candidates, minus the winner. */
            remove_candidate(m_indexes(final_winners)[0], company);
            start_election(company, 2);
        }
        else
        {
            /* Reset the candidates. */
            gCandidates[company] = ({});

            /* Reset the election */
            gElection[company][1] = 0;
        }

        /* Reset votes */
        gVotes[company] = ([]);
        break;
    case 3:
        /* Do impeachments */
        final_winners = find_winners(company, 1);
        if (m_sizeof(final_winners) > 1 ||
          m_indexes(final_winners)[0] == "Yes")
        {
            /* It was a tie or the impeachers won. */
            remove_council(gCouncil[company][CAPTAIN_POSITION]);
        }

        /* Reset votes */
        gVotes[company] = ([]);

        /* Reset the candidates. */
        gCandidates[company] = ({});

        /* Reset the election */
        gElection[company][1] = 0;
        break;
    default:
        break;
    }

    save_manager(gCandidates, "candidates");
    save_manager(gVotes, "votes");
    save_manager(gElection, "election");
    return 1;
}

/* Function name: start_election
 * Description  : Starts an election
 * Arguments    : string company - the company to start an election for
 *                int election - the type of election to start
 *                               1 for nominations
 *                               2 for captain election
 *                               3 for impeachments
 * Returns      : 1 on success, 0 on failure
 */
public int
start_election(string company, int election)
{
    /* No arguments */
    if (!strlen(company) || !intp(election))
        return 0;

    company = lower_case(company);

    /* Election already in progress */
    if (query_election(company))
        return 0;

    /* No known type of election */
    if (election < 0 || election > 3)
        return 0;

    /* Clear the votes, but not the candidates. Something might have
       gone wrong with a previous vote and have to be called over again. */
    gVotes[company] = ([]);

    /* Add the election */
    gElection[company] = ({ time(), election });

    /* Save the .o file */
    save_manager(gElection, "election");
    save_manager(gVotes, "votes");
    rlog(RANGERS_WIZ_LOG, "Election started: " + capitalize(company) +
        " type: " + election);
    return 1;
}

/* Function name: query_election
 * Description  : Gives the type of election being held
 * Arguments    : string company - which company to check for
 * Returns      : 0 for no election, 1 for nominations, 2 for captain
 *                elections, 3 for an impeachment vote
 */
public int
query_election(string company)
{
    if (!strlen(company))
        return 0;

    company = lower_case(company);

    if (member_array(company, m_indexes(gElection)) == -1)
        return 0;

    if (gElection[company][1] >= 0 && gElection[company][1] <= 3)
        return gElection[company][1];
    else
        return 0;
}

/* Function name: post_election_results
 * Description  : Posts the results of the election
 * Arguments    : string company - the company to post for
 *                int election_type - what kind of election?
 *                mapping results - ([ vote_option : vote_tally ])
 */
public void
post_election_results(string company, int election_type, mapping results)
{
    int i, size;
    object library;
    string book, *candidates, text = "";

    if (!strlen(company) || !intp(election_type) || !mappingp(results))
        return;

    candidates = m_indexes(results);
    for (i = 0, size = sizeof(candidates); i < size; i++)
    {
        text += capitalize(candidates[i]) + " got " +
            results[candidates[i]] + " votes.\n";
    }

    company = capitalize(company);

    switch(election_type)
    {
    case 1:
        text += "In the nominations for Captain of " + company +
            ", the final results are as follows:\n";
        break;
    case 2:
        text += "In the election for Captain of " + company +
            ", the final results are as follows:\n";
        break;
    case 3:
        text += "In the vote for impeachment of the Captain of " +
            company + ", the final results are as follows:\n";
        break;
    default:
        break;
    }

    book = RANGERS_LIBRARY + "Elections_" + capitalize(company);

    write_file(book, text);

    return;
}

/* Function name: query_candidates
 * Description  : What players are candidates in this election?
 * Arguments    : string company - the company to check
 *                   "north" or "ithilien"
 * Returns      : an array of election candidates
 */
public string *
query_candidates(string company)
{
    if (!strlen(company))
        return ({});

    company = lower_case(company);

    if (!query_election(company))
        return ({});

    return gCandidates[company];
}

/* Function name: query_is_candidate
 * Description  : Is this player a candidate in this company election?
 * Arguments    : string name - the name of the player to check
 *                string company - the company to check
 * Returns      : 1 if the player is candidate in that company, 0 if not
 */
public int
query_is_candidate(string name, string company)
{
    if (!strlen(name) || !strlen(company))
        return 0;

    name = capitalize(name);
    company = lower_case(company);

    if (!query_election(company))
        return 0;

    if (member_array(name, gCandidates[company]) != -1)
        return 1;
    else
        return 0;
}

/* Function name: add_candidate
 * Description  : Adds a name to the list of candidates in the company election. 
 * Arguments    : string name - the name to add
 *                string company - the company in which the election is held
 *                string nominator - the person who nominated the candidate
 * Returns      : 1 if successful, 0 if not
 */
public varargs int
add_candidate(string name, string company, string nominator = "")
{
    if (!strlen(name) || !strlen(company))
        return 0;

    name = capitalize(name);
    company = lower_case(company);
    nominator = capitalize(nominator);

    if (!query_election(company))
        return 0;
    if (!query_ranger(name, company))
        return 0;
    if (query_is_candidate(name, company))
        return 0;
    if (strlen(nominator) && query_nominator(nominator, company))
        return 0;

    // nominations are closed
    if (query_election(company) != 1)
    {
        find_player(nominator)->catch_tell("Nominations are " +
            "closed.\n");
        return 0;
    }

    add_nominator(nominator, company);

    gCandidates[company] += ({ name });

    rlog(RANGERS_WIZ_LOG, CAP(nominator) + " nominated " + CAP(name) +
        " for Captain of " + CAP(company));
    save_manager(gCandidates, "candidates");
    return 1;
}

/* Function name: remove_candidate
 * Description  : Removes a name of someone who was a candidate.
 * Arguments    : string name - the name to remove
 *                string company - company to which name belongs
 * Returns      : 1 if successful, 0 if not
 */
public int
remove_candidate(string name, string company)
{
    int i, size;
    string *voters;

    if (!strlen(name))
        return 0;

    name = capitalize(name);
    company = lower_case(company);

    if (member_array(name, gCandidates[company]) != -1)
    {
        gCandidates[company] -= ({ name });
        rlog(RANGERS_WIZ_LOG, CAP(name) + " removed as candidate.");

        /* Remove the votes cast for that candidate */
        voters = m_indexes(gVotes[company]);
        for (i = 0, size = sizeof(voters); i < size; i++)
        {
            if (gVotes[company][voters[i]] == name)
            {
                gVotes[company] = m_delete(gVotes[company], voters[i]);
                rlog(RANGERS_WIZ_LOG, voters[i] + " had vote " +
                    "removed when " + name + " removed as candidate.");
            }
        }

        save_manager(gCandidates, "candidates");
        save_manager(gVotes, "votes");
    }
    return 1;
}

/* Function name: query_nominator
 * Description  : Finds out if the player has nominated someone already
 * Arguments    : string name - name of the player
 *                string company - name of the player's company
 * Returns      : 1 if they have, 0 if not
 */
public int
query_nominator(string name, string company)
{
    if (!strlen(name) || !strlen(company))
        return 1;

    name = capitalize(name);
    company = lower_case(company);

    if (member_array(name, gNominators[company]) == -1)
        return 0;


    return 1;
}

/* Function name: add_nominator
 * Description  : Adds a person to the nominator list if not there already.
 * Arguments    : string name - the name of the nominator
 *                string company - the name of the nominator's company
 * Returns      : 1 if successful, 0 if not
 */
public int
add_nominator(string name, string company)
{
    if (!strlen(name) || !strlen(company))
        return 0;

    name = capitalize(name);
    company = lower_case(company);

    if (query_nominator(name, company))
        return 0;

    gNominators[company] += ({ name });
    save_manager(gNominators, "nominators");
    return 1;
}

/* Function name: remove_nominator
 * Description  : Removes a person from the nominator list.
 * Arguments    : string name, string company, int all
 * Returns      : 1 if successful, 0 if not
 */
public varargs int
remove_nominator(int all, string company, string name = "")
{
    if (!strlen(company))
        return 0;

    company = lower_case(company);
    name = capitalize(name);

    if (member_array(company, m_indexes(gNominators)) == -1)
        return 0;

    if (all)
    {
        gNominators[company] = ({});
        save_manager(gNominators, "nominators");
        return 1;
    }

    if (!strlen(name))
        return 0;

    if (!query_nominator(name, company))
        return 0;

    gNominators[company] -= ({ name });
    save_manager(gNominators, "nominators");
    return 1;
}

/* Function name: find_winners
 * Description  : Find the winner(s). Will return more than 'num' if
 *                there is a tie.
 * Arguments    : string company - the company to check for winners
 *                int num - the number of winners to return
 * Returns      : string * winners
 */
public varargs mapping
find_winners(string company, int num = 1)
{
    int i, size, *tallies, counter = 0;
    mapping vote_tally = ([]), final_votes = ([]);
    string *votes;

    /* No company or less than 1 winner requested */
    if (!strlen(company) || num < 1)
        return ([]);

    company = lower_case(company);

    if (!sizeof(gCandidates[company]))
        return ([]);

    /* Get the actual votes here. The voter names don't matter anymore. */
    votes = m_values(gVotes[company]);

    /* Sort the array for more efficiency. */
    votes = sort_array(votes);

    /* Put the votes into a mapping and tally them. */
    for (i = 0, size = sizeof(votes); i < size; i++)
    {
        if (member_array(votes[i], m_indexes(vote_tally)) == -1)
            vote_tally += ([ votes[i] : 1 ]);
        else
            vote_tally[votes[i]] += 1;
    }

    /* Get only one instance of each vote into the array. */
    votes = m_indexes(vote_tally);

    /* The final vote tallies into an array */
    tallies = m_values(vote_tally);

    /* Sort tallies, lowest number first. */
    tallies = sort_array(tallies);

    /* This takes ties into account, and will return a greater array
       than requested if there is a tie. */
    i = sizeof(tallies) - num;
    while((i > 0) && (tallies[i] == tallies[i-1]))
    {
        i--;
        num++;
    }

    if (sizeof(tallies) < num)
        num = sizeof(tallies);
    /* Puts the tallies of the winners in an array. */
    tallies = tallies[sizeof(tallies) - num..sizeof(tallies) - 1];

    /* Puts the winners in a mapping with their tally numbers. */
    for (i = 0, size = sizeof(votes); i < size; i++)
    {
        if (member_array(vote_tally[votes[i]], tallies) != -1)
        {
            final_votes += ([ votes[i] : vote_tally[votes[i]] ]);
        }
    }

    return final_votes;
}

/* Function name: query_voted
 * Description  : Checks if a player has voted in the current election
 * Arguments    : string company - the company of the player
 *                string name - the name of the player
 * Returns      : 1 if they have voted, 0 if not
 */
public int
query_voted(string company, string name)
{
    if (!strlen(company) || !strlen(name))
        return 0;

    name = capitalize(name);
    company = lower_case(company);
    /* Player has voted. */
    if (member_array(name, m_indexes(gVotes[company])) != -1)
        return 1;

    /* Player has not voted. */
    return 0;
}

/* Function name: cast_vote
 * Description  : Attemps to cast a vote. Checks if vote_choice is a
 *                valid vote option.
 * Arguments    : string company - the company of the player
 *                string name - the name of the player
 *                string vote_choice - the vote
 * Returns      : 1 if successful, 0 if not
 */
public int
cast_vote(string company, string name, string vote_choice)
{
    if (!strlen(company) || !strlen(name) || !strlen(vote_choice))
        return 0;

    company = lower_case(company);
    name = capitalize(name);
    vote_choice = capitalize(vote_choice);

    /* No election ongoing */
    if (!query_election(company))
        return 0;

    /* Failed to cast vote, already voted.
    if (query_voted(company, name))
        return 0;
    */

    /* Failed to cast vote, invalid vote_choice. */
    if (!query_is_candidate(vote_choice, company))
        return 0;

    /* Vote cast successfully */
    gVotes[company] += ([name : vote_choice]);
    rlog(RANGERS_WIZ_LOG, capitalize(name) + " voted " + vote_choice);
    save_manager(gVotes, "votes");
    return 1;
}

/* Function name: query_impeaching
 * Description  : Gives a list of people attempting to impeach within the
 *                last IMPEACH_GRACE_TIME (originally set to three days)
 *                Names and times will remain on the list until the next
 *                election, at which point the impeach list will be cleared.
 *                If a person wants to sign their name again after it's
 *                been expired (add_impeaching()), then the time is simply
 *                changed. If a vote is called to impeach a captain, the
 *                ones getting the vote called will be unable to impeach
 *                until after the next regular election.
 * Arguments    : string company - the company to check
 * Returns      : an array with the names of those impeaching for the
 *                given company within the last three days, or an empty array
 */
public string *
query_impeaching(string company)
{
    int i, size;
    string *impeachers = ({});

    if (!strlen(company))
        return 0;

    company = lower_case(company);

    /* Add names to the list that have been added within the last 3 days. */
    for (i = 0, size = sizeof(gImpeachers[company]); i < size; i +=2)
    {
        if (gImpeachers[company][i + 1] + IMPEACH_GRACE_TIME < time())
            impeachers += gImpeachers[company][i];
    }

    return impeachers;
}

/* Function name: add_impeachers
 * Description  : Adds a name and time of addition of someone who
 *                tried to impeach the captain to a list of impeachment voters.
 *                If the name is already there, swaps out the time.
 * Arguments    : string name - the name to add
 *                string company - the company in which the impeachment
 *                attempt occurred
 * Returns      : 1 if successful, 0 if not
 */
public int
add_impeaching(string name, string company)
{
    int index;

    if (!strlen(name) || !strlen(company))
        return 0;

    name = capitalize(name);
    company = lower_case(company);

    /* No impeachment attempts during an election! */
    if (query_election(company))
        return 0;

    /* Not a Ranger of the given company */
    if (!query_ranger(name, company))
        return 0;

    /* They signed less than 3 days ago. Don't add again until expired. */
    if (member_array(name, query_impeaching(company)) != -1)
    {
        return 0;
    }

    /* Don't add their name if it's already on, just change the time. */
    index = member_array(name, gImpeachers[company]);
    if (index != -1)
    {
        gImpeachers[company][index+1] = time();
    }
    else
    {
        /* Add to the list */
        gImpeachers[company] += ({ name, time() });
    }

    save_manager(gImpeachers, "impeachers");
    return 1;
}

/* Function name: remove_impeaching
 * Description  : Removes a name of someone who voted to impeach the captain.
 * Arguments    : string name - the name to remove
 *                string company - company to which name belongs
 * Returns      : 1 if successful, 0 if not
 */
public int
remove_impeaching(string name, string company)
{
    int index, max, last_index;

    if (!strlen(name) || !strlen(company))
        return 0;

    name = capitalize(name);
    company = lower_case(company);

    last_index = sizeof(query_impeaching(company)) - 1;
    max = sizeof(query_impeaching(company)) - 2;

    /* Find index number of the name. */
    index = member_array(name, gImpeachers[company]);

    switch(index)
    {
    case -1:
        return 0;
    case 0:
        gImpeachers[company] = gImpeachers[company][2..max+1];
        break;
    default:
        if (index == max)
        {
            gImpeachers[company] = gImpeachers[company][0..max-3];
            break;
        }
        else
        {
            gImpeachers[company] = gImpeachers[company][0..index-1] +
                               gImpeachers[company][index+2..last_index];
            break;
        }
    }

    save_manager(gImpeachers, "impeachers");
    return 1;
}

