/*
 *	/d/Gondor/common/guild/sponsors.c
 *
 *	The master keeping track of sponsors and pupils in the 
 *	Rangers of the Westlands.
 *
 *	Copyright (c) 1995 by Rolf Braun,
 *	Copyright (c) 1997 by Christian Markus.
 *
 *	Coded by Elessar, 1995.
 *
 *	Modification log:
 *	19-Feb-1997, Olorin:	Major revision.
 */
#pragma save_binary
#pragma strict_types

#include <composite.h>
#include <language.h>
#include <std.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild/lib/ranger_defs.h"

#define SPONSOR_SAVE	"/d/Gondor/common/guild/sponsors"
#define DATE       0
#define APPROVALS  1
#define OFFICER    2
#define RECRUIT    3
#define MENTOR     4

public void check_sponsors();
public mixed remove_applicant(string name);

/* 
 * Current pupils for a sponsor:
 *	"Sponsor" : ({ "Pupil1", "Pupil2", }), ...
 */
mapping Sponsors = ([ ]);
/*
 * Current applicants and their respective status:
 *    "Applicant" : ({ "OfficerWhoApproved", "RecruiterWhoApproved",  
 *                     "MentorWhoApproved", }), ...
 */
mapping Applicants = ([ ]);
/*
 * Denied Applicants and date when new application is possible.
 *    "Denied1" : 81934723, "Denied2" : 0, "Denied3" : 82523478, ...
 */
mapping Denied = ([ ]);
/*
 * Current sponsor for pupils:
 *	"Pupil" : "Sponsor", ...
 */ 
mapping Pupils   = ([ ]); 
/* 
 * History of who sponsored who   
 *	"Pupil" : "Sponsor", ...
 */
mapping History  = ([ ]);
/*
 * List of people who can sponsor
 *	"Mentor1", "Mentor2", ....
 */
string *Mentors  = ({ }); 

/*
 * Function name: create
 * Description  : Object constructor, called directly after load / clone.
 *                Set up global variables.
 */
public nomask void
create()
{
    FIX_EUID;
    restore_object(SPONSOR_SAVE);
    seteuid(0);

    set_alarm(60.0, 0.0, check_sponsors);
}

/* 
 * Function name: query_sponsor
 * Description:   Returns current sponsor for a pupil.
 * Argument:      The name of the pupil.
 * Returns:       The name of the sponsor, or the Sponsors mapping. 
 */
public varargs mixed 
query_sponsor(string name) 
{
    if (stringp(name))
        return Pupils[CAP(LOW(name))];
    else
        return secure_var(Sponsors);
}

/*
 * Function name: query_pupil
 * Description:   Returns current pupils for a sponsor
 * Argument:      The name of the sponsor.
 * Returns:       An array of string with the names of the pupils, or
 *                if no argument given, the Pupils mapping.
 */
public varargs mixed 
query_pupil(string name) 
{
    if (stringp(name))
        return Sponsors[CAP(LOW(name))];
    else
        return secure_var(Pupils);
}

/*
 * Function name: query_applicant
 * Description:   Check if a person is an applicant
 * Arguments:     name - name of the applicant
 * Returns:       1 if name is applicant, else 0.
 */
public int
query_applicant(string name)
{
    if (!strlen(name))
        return 0;
    name = CAP(LOW(name));

    if (Applicants[name])
        return 1;
}

/* 
 * Function name: query_sp_list
 * Description:   Returns a nice list with pupils and their sponsors
 * Returns: 
 */
public mixed
query_sp_list()
{
    int     n;
    string *sp_list = m_indexes(Sponsors),
            list = "";
    
    if (!(n = sizeof(sp_list)))
        return "There are no Mentors with pupils at the moment.\n";

    while (n--)
    {
	list += sp_list[n] + " is the Mentor of " +
	    COMPOSITE_WORDS(Sponsors[sp_list[n]]);
	if (n > 0)
	    list += ",\n";
    }
    list += ".";
    return list;
}

/*
 * Function name: query_history
 * Description:   Returns who was sponsored by whom in the past.
 * Argument:      Name of the former pupil.
 * Returns:       Name of the sponsor, or the History mapping.
 */
public varargs mixed 
query_history(string name) 
{
    if (stringp(name))
        return History[CAP(LOW(name))];
    else
        return secure_var(History);
}

/* 
 * Function name: query_history_string
 * Description:   Function to make a small list of who has been
 *                sponsored by whom in the past.
 * Returns:       The list in a string.
 */
public string 
query_history_string() 
{
    string  str = "", 
           *keys = m_indexes(History);
    int     i = sizeof(keys);

    while (i--)
    {
        str += keys[i] + " was Mentored by " + History[keys[i]];
	if (i > 0)
	    str += ",\n";
    }
    str += ".\n";
    return str;
}

/* 
 * Function name: add_pupil
 * Description:   Adds a pupil to a sponsor.
 * Arguments:     sponsor - name of the sponsor,
 *                pupil   - name of the pupil.
 *                test    - just check if the pupil could be added,
 *                          but don't add him or her.
 * Returns:       0 on success,
 *                error string on failure.
 */
public mixed
add_pupil(string sponsor, string pupil, int test = 0) 
{
    sponsor = CAP(LOW(sponsor));
    pupil   = CAP(LOW(pupil));

    if (pointerp(Sponsors[sponsor]) && 
	(sizeof(Sponsors[sponsor]) >= MAX_PUPILS))
        return ("You are already the Mentor of " +
		COMPOSITE_WORDS(Sponsors[sponsor]) + 
		", and a ranger may only mentor up to " +
		LANG_WNUM(MAX_PUPILS) + " pupils at a time.\n");
    if (strlen(Pupils[pupil]))
        return (pupil + " is already mentored by " +
		Pupils[pupil] + ".\n");

    if (test)
	return 0;

    Pupils[pupil] = sponsor;

    if (Sponsors[sponsor])
        Sponsors[sponsor] += ({ pupil });
    else
        Sponsors[sponsor] = ({ pupil });

    remove_applicant(pupil);

    FIX_EUID;
    save_object(SPONSOR_SAVE);
    seteuid(0);

    return 1;
}

/*
 * Function name:       add_applicant
 * Description:         Adds a new applicant to the list,
 *                      and sets her status to Fresh.
 * Returns:             1 if successful, message if not.
 */
varargs public mixed
add_applicant(string name, int date = time(), int test = 0)
{
    name = CAP(LOW(name));
    if (sizeof(Applicants[name]))
    {
        return "You are already listed as an applicant since "
          + Applicants[name][0] + ", and you have the status of "
          + Applicants[name][1] + ".\n";
    }
    if (Denied[name])
    {
        if (Denied[name] > time())
            return "You may not apply again to join the Rangers until "
              + ctime(Denied[name]) + ".\n";
    }

    if (test)
        return 0;

    Applicants[name] = ({ time(), 0, 0, 0, 0 });

    FIX_EUID;
    save_object(SPONSOR_SAVE);

    return 1;
}

/*
 * Function name:      remove_applicant
 * Description:        Removes an applicant from the list for whatever
 *                     reason.
 * Arguments:          name - the applicant's name.
 * Returns:            1 on success, 0 for failure, -1 if not listed.
 */
public mixed remove_applicant(string name)
{
    name = CAP(LOW(name));
    if (!sizeof(Applicants[name]))
        return -1;

    Applicants = m_delete(Applicants, name);
    if (sizeof(Applicants[name]))
        return 0;

    save_object(SPONSOR_SAVE);
    return 1;
}

/* 
 * Function name: remove_pupil
 * Description:   Removes a pupil from a sponsor and adds the pupil to
 *                the history list 
 * Argument:      the name of the pupil.
 */
public void 
remove_pupil(string pupil) 
{
    pupil = CAP(LOW(pupil));

    if (!stringp(Pupils[pupil]))
        return;
    /* To be able to see who sponsored who in the future */
    History[pupil] = Pupils[pupil];
    if (sizeof(Sponsors[Pupils[pupil]]) <= 1) 
        Sponsors = m_delete(Sponsors, Pupils[pupil]);
    else 
	Sponsors[Pupils[pupil]] -= ({ pupil });
    Pupils = m_delete(Pupils, pupil);
    FIX_EUID;
    save_object(SPONSOR_SAVE);
    seteuid(0);
}

/*
 * Function name: remove_sponsor
 * Description:   Removes a sponsor and the pupils of that sponsor 
 * Argument:      the name of the sponsor
 */
public void 
remove_sponsor(string sponsor)
{
    sponsor = CAP(LOW(sponsor));

    if (!pointerp(Sponsors[sponsor]))
        return;

    while (sizeof(Sponsors[sponsor]))
    {
        History[Sponsors[sponsor][0]] = sponsor;
        Pupils = m_delete(Pupils, Sponsors[sponsor][0]);
	Sponsors[sponsor] -= ({ Sponsors[sponsor][0] });
    }
    Sponsors = m_delete(Sponsors, sponsor);
    FIX_EUID;
    save_object(SPONSOR_SAVE);
    seteuid(0);
}

/* 
 * Function name: list_pupils
 * Description:   Lists only pupils, neatly arranged in a string.
 * Returns:       The list of pupils.
 */
public string 
list_pupils()
{
    return COMPOSITE_WORDS(m_indexes(Pupils));
}

/*
 * Function name: list_applicant_status
 * Description:   List the info on a particular applicant
 * Argument:      applicant's name
 * Returns:       Date of application, and names of approving rangers.
 */
public string
list_applicant_status(string arg)
{
    string  ltxt;
 
    if (!strlen(arg))
        return 0;
    arg = CAP(LOW(arg));
    if (!sizeof(Applicants[arg]))
        return "No such applicant.\n";

    ltxt = "Applicant: " + arg + ".\n" + "Date of application: " 
      + ctime(Applicants[arg][DATE]) + ".\n";
    ltxt += "Approved by:   Officer: " + (strlen(Applicants[arg][OFFICER]) ?
      Applicants[arg][OFFICER] : "none yet") + ".\n";
    ltxt += "               Recruiter: " + (strlen(Applicants[arg][RECRUIT]) ?
      Applicants[arg][RECRUIT] : "none yet") + ".\n";
    ltxt += "               Mentor: " + (strlen(Applicants[arg][MENTOR]) ?
      Applicants[arg][MENTOR] : "none yet") + ".\n";
    ltxt += "Status: " + (Applicants[arg][APPROVALS] == 3 ? "Ready to join" :
      "Not yet ready to join") + ".\n";
    return ltxt;
}

/*
 * Function name: list_applicants
 * Description:   List all applicants and their status, neatly arranged
 *                in a string.
 * Returns:       The list of applicants and status.
 */
public string
list_applicants(string arg)
{
    int     s,
            n,
            m,
            i;
    string  ltxt = "",
            tmp;

    arg = LOW(arg);
    if (!m_sizeof(Applicants))
        return "No current applicants.\n";

    if (!strlen(arg) || (member_array(arg, ({"fresh", "worthy", "approved",
        "undecided", "waiting"})) == -1))
    {
        s = m_sizeof(Applicants);
        while (i < s)
        {
            tmp = m_indexes(Applicants)[i];
            ltxt += tmp + ", applied on " + ctime(Applicants[tmp][0])
              + ". ";
            if (Applicants[tmp][1] < 3)
                ltxt += "Not yet approved.\n";
            else
                ltxt += "Approved.\n";
            i++;
        }
    }
    else
    {
        arg = LOW(arg);
        s = m_sizeof(Applicants);
        if (arg == "worthy" || arg == "approved")
        {
            while (i < s)
            {
                tmp = m_indexes(Applicants)[i];
                if (Applicants[tmp][APPROVALS] == 3)
                {
                    ltxt += tmp + ", applied on "
                      + ctime(Applicants[tmp][DATE])
                      + ". Approved by: " + COMPOSITE_WORDS(
                        Applicants[tmp][OFFICER..MENTOR]) + ".\n";
                    m++;
                }
                i++;
            }
        }
        else
        {
            while (i < s)
            {
                tmp = m_indexes(Applicants)[i];
                if (Applicants[tmp][APPROVALS] < 3)
                {
                    ltxt += tmp + ", applied on "
                      + ctime(Applicants[tmp][DATE])
                      + ". Still missing " + Applicants[tmp][APPROVALS] 
                      + " approval"
                      + (Applicants[tmp][APPROVALS] > 1 ? "s" : "")
                      + ".\n";
                    m++;
                }
                i++;
            }
        }
    }
    if (m < 1)
        return "No " + arg + " applicants currently.\n";
    else
        return ltxt;
}

public string
list_denied_applicants()
{
    int     s, i;
    string  lstr = "",
            tmp;

    if (!m_sizeof(Denied))
        return "No applicants have been refused.\n";

    s = m_sizeof(Denied);
    lstr = "Name of applicant:       Can soonest apply again:\n";
    while (i < s)
    {
        tmp = m_indexes(Denied)[i];
        lstr += tmp + "\t\t " + ctime(Denied[tmp]) + ".\n";
        i++;
    }
    return lstr;
}

/* 
 * Function name: query_sponsors_only
 * Description:   Returns a list of current sponsors.
 * Returns:       The list of sponsors.
 */
public string 
query_sponsors_only()
{
    return COMPOSITE_WORDS(m_indexes(Sponsors));
}

/*
 * Function name: add_can_sponsor
 * Description:   Add another possible sponsor to the list.
 * Argument:      The name of the new master.
 * Returns:       0/1/-1 - failure/success/already added.
 */
public int
add_can_sponsor(string mentor)
{
    if (!stringp(mentor) || !strlen(mentor))
        return 0;

    mentor = CAP(LOW(mentor));

    if (member_array(mentor, Mentors) >= 0) 
        return -1;
    if (!pointerp(Mentors)) 
	Mentors = ({ });
    Mentors += ({ mentor });

    FIX_EUID;
    save_object(SPONSOR_SAVE);
    seteuid(0);

    return 1;
}

/*
 * Function name: remove_mentor
 * Description:   Remove a name from the list of people who
 *                are allowed to sponsor.
 * Argument:      The name of the mentor.
 * Returns:       0/1/-1
 */
public int
remove_mentor(string name)
{
    int n;
    if (!stringp(name) || !strlen(name)) 
        return 0;

    name = CAP(LOW(name));
    if (member_array(name, Mentors) < 0) 
        return -1;

    Mentors -= ({ name });

    FIX_EUID;
    save_object(SPONSOR_SAVE);
    seteuid(0);

    return 1;
}

/*
 * Function name: query_can_sponsor
 * Description:   Check for possible sponsors.
 * Argument:      the name of the sponsor.
 * Returns:       1 if player has been sanctioned for sponsoring.
 */
public int
query_can_sponsor(string name)
{
    if (!stringp(name) || !strlen(name)) 
        return 0;

    name = CAP(LOW(name));
    if (member_array(name, Mentors) >= 0) 
        return 1;
    return 0;
}

/*
 * Function name: list_mentors
 * Description:   This function returns a list of all who are allowed to
 *                be mentors, except for the Officers.
 * Returns:       The list of potential sponsors.
 */
public string
list_mentors()
{
    if (!sizeof(Mentors)) 
        return "No current Mentors";
    return COMPOSITE_WORDS(Mentors);
}

/*
 * Function name: list_free_sponsors
 * Description:   Returns a list of sponsors without pupils.
 * Returns:       A list of sponsors without pupils.
 */
public string
list_free_sponsors()
{
    string *free_sponsors = ({ });

    free_sponsors += COUNCIL->query_officers();
    if (sizeof(Mentors)) 
	free_sponsors += Mentors;
    if (m_sizeof(Sponsors))
	free_sponsors -= m_indexes(Sponsors);

    if (!sizeof(free_sponsors)) 
        return "None";
    else 
        return COMPOSITE_WORDS(free_sponsors);
}

/*
 * Function name: list_free_pupils
 * Description:   Lists pupils without sponsors.
 * Returns:       The list.
 */
public string
list_free_pupils()
{
    string *all_p, 
           *sp_p  = m_indexes(Pupils);
    int     n;

    // Add array to existing array, otherwise we just get a pointer!
    all_p = ({ }) + RANGER_GUILD->query_company_members(0);

    all_p = map(all_p, capitalize);
    all_p -= sp_p;
    return COMPOSITE_WORDS(all_p);
}

/*
 * Function name: change_applicant_status
 * Description:   changes the status of a current applicant
 * Arguments:     Name of applicant, variable to change, value to change to.
 * Returns:       1 on success, 0 if no change, -1 if no such applicant.
 */
public int
change_applicant_status(string name, string what, mixed value)
{
    if (!strlen(name))
        return -1;

    name = CAP(LOW(name));
    if (!sizeof(Applicants[name]))
        return -1;

    what = LOW(what);
    if (what == "approve")
    {
        if (value == "officer" && !strlen(Applicants[name][OFFICER]))
            Applicants[name][OFFICER] = CAP(TP->query_real_name());
        else if (value == "recruiter" &&
          !strlen(Applicants[name][RECRUIT]))
            Applicants[name][RECRUIT] = CAP(TP->query_real_name());
        else if (value == "mentor" && !strlen(Applicants[name][MENTOR]))
            Applicants[name][MENTOR] = CAP(TP->query_real_name());
        else 
            return 0;

        Applicants[name][APPROVALS] += 1;
        return 1;
    }
    else if (what == "deny")
    {
        if (Denied[name])
        {
            Denied[name] = time() + 31536000;
            remove_applicant(name);
            write_file(APPLICANT_LOG, name + " denied for one year, by " +
              TP->query_name() + ". " + ctime(time()) + ".\n");
            return 1;
        }
        else
        {
            Denied[name] = time() + 2592000;
            remove_applicant(name);
            write_file(APPLICANT_LOG, name + "'s application denied for "
              + "30 days, by " + TP->query_name() + ". " 
              + ctime(time()) + ".\n");
            return 1;
        }
    }
    else if (what == "joined")
    {
        remove_applicant(name);
        return 1;
    }
    else
        return 0;
}

public int
query_approved(string name)
{
    if (!m_sizeof(Applicants))
        return -1;
    name = CAP(LOW(name));
    if (!sizeof(Applicants[name]))
        return -1;
    return Applicants[name][APPROVALS];
}

/*
 * Function name: check_sponsors
 * Description:   Check that all players listed in the mappings still
 *                exist as players in the game.
 */
public void
check_sponsors()
{
    string *arr;

    Mentors = filter(Mentors, &SECURITY->exist_player() @ lower_case);

    arr = m_indexes(Sponsors);
    arr -= filter(arr, &SECURITY->exist_player() @ lower_case);
    if (sizeof(arr))
        map(arr, remove_sponsor);

    arr = m_indexes(Pupils);
    arr -= filter(arr, &SECURITY->exist_player() @ lower_case);
    if (sizeof(arr))
        map(arr, remove_pupil);

    FIX_EUID;
    save_object(SPONSOR_SAVE);
    seteuid(0);
}
