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

public void check_sponsors();

/* 
 * Current pupils for a sponsor:
 *	"Name" : ({ "Pupil1", "Pupil2", }), ...
 */
mapping Sponsors = ([ ]);
/*
 * Current sponsor for pupils:
 *	"Name" : "Sponsor", ...
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
        return "There are no sponsors with pupils at the moment.\n";

    while (n--)
    {
	list += sp_list[n] + " is the mentor of " +
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
        str += keys[i] + " was taught by " + History[keys[i]];
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
        return ("You are already the instructor of " +
		COMPOSITE_WORDS(Sponsors[sponsor]) + 
		", and a ranger may only instruct up to " +
		LANG_WNUM(MAX_PUPILS) + " pupils at a time.\n");
    if (strlen(Pupils[pupil]))
        return (pupil + " is already sponsored by " +
		Pupils[pupil] + ".\n");

    if (test)
	return 0;

    Pupils[pupil] = sponsor;

    if (Sponsors[sponsor])
        Sponsors[sponsor] += ({ pupil });
    else
        Sponsors[sponsor] = ({ pupil });

    FIX_EUID;
    save_object(SPONSOR_SAVE);
    seteuid(0);

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
 * Function name: list_sponsors
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
 * Function name: remove_master
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
 *                be sponsors, except for the Officers.
 * Returns:       The list of potential sponsors.
 */
public string
list_mentors()
{
    if (!sizeof(Mentors)) 
        return "";
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
