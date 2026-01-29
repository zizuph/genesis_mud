
/* 
    Calian recruitment officers code.

    History:
      3/5/2000   command to set minimum applicant level  Maniac
      25/8/98    applicant record handling               Maniac
      27/7/98    tunnel access option added              Maniac 
       3/7/98    applicant opinion system added          Maniac 
       3/7/98    application cap command added           Maniac 
       26/7/96   improvements                            Maniac
       31/5/96   query_prevent_shadow added              Maniac
       9/10/95   assigning ROs to applicants added       Maniac        
        4/8/95          RCO details added                Maniac  
        20.4.95         typo fixed                       Maniac  
        6.4.95          accepted Calian system added     Maniac
        9.2.95          record of applicants added       Maniac
        9.1.95          query_wiz_dom for query_domain   Maniac
        6.12.94         typo fixed                       Maniac
	20.11.94	created				         Glykron

    This is adapted from Maniac's council code.
*/

#pragma save_binary
#pragma no_inherit

#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <std.h>
#include <composite.h>
#include <state_desc.h>
#include "defs.h"
#include CALIAN_HEADER
#include COUNCIL_HEADER
#include RECRUITER_HEADER
#define APP_CAP_MIN 0
#define APP_CAP_MAX 50

void nullify_ass_for_rec(string rec); 
void rem_ass(string nm); 

int applications_cap = APP_CAP_MAX; 
mapping opinions = ([ ]); 
string *roc = ({ });
string *recruiters = ({ });
string *accepted = ({ });
string *tunnel_access = ({ }); 
mixed assignments = ({ }); /*i.e. ({ ({"ap1", "r01"}), ({"ap2", "ro2"}) });*/

static string *sd_av_levels = SD_AV_TITLES; 
string minimum_level = sd_av_levels[0]; 

int
query_prevent_shadow()
{
    return 1;
}


string
my_time()
{
    return (ctime(time())[4..9] + ": ");
}


/* Here we get rid of any applicants or recruiters who have been deleted */ 
void
remove_non_existant()
{
    int i;
    string *rdel; 

    rdel = ({ }); 

    for (i = 0; i < sizeof(recruiters); i++)
        if (!SECURITY->exist_player(lower_case(recruiters[i])))
            rdel += ({ recruiters[i] });

    for (i = 0; i < sizeof(rdel); i++)  
        nullify_ass_for_rec(rdel[i]); 

    roc -= rdel; 
    recruiters -= rdel; 

    rdel = ({ }); 
    for (i = 0; i < sizeof(assignments); i++) 
        if (!SECURITY->exist_player(lower_case(assignments[i][0])))
            rdel += ({ assignments[i][0] });

    for (i = 0; i < sizeof(rdel); i++)  
        rem_ass(rdel[i]); 

    save_object(RECRUITERS); 
}


void
create()
{
    object po; 
    int i = 0; 

    seteuid(getuid());
    restore_object(RECRUITERS);
    set_alarm(1.0, 0.0, remove_non_existant);

    while (objectp(po = previous_object(i--))) { 
        log_file("old_palace_code", "recruiter code: " + 
                 file_name(po) + " (" + 
                 po->query_real_name() + ").\n"); 
    } 
}



string
query_recruiters_string()
{
    string rstr;

    if (sizeof(recruiters) == 0)
	rstr = "There are currently no Recruitment Officers for " +
               "the Calian guild.\n";
    else  
        rstr = "The Calian guild has the following Recruitment " +
               "Officers:\n" + COMPOSITE_WORDS(recruiters) + ".\n";
    if (sizeof(roc)) 
        rstr += ("The current Recruitment Officer Coordinator is: " +
                 roc[0] + ".\n");

    return rstr;
}


string
*query_applicants()
{
    int i;
    string *applicants = ({ });

    for (i = 0; i < sizeof(assignments); i++) 
        applicants += ({assignments[i][0]});
    return applicants;
}


string
query_applicants_string()
{
    int i;
    string as;
    string *applicants = ({ });

    if (sizeof(assignments) == 0)
        return ("There are currently no applicants for the Calian " +
                "guild.\n");     

    as = ("The following applications are still pending for the " +
          "Calian guild (assigned recruiters are given in brackets): \n"); 

    for (i = 0; i < sizeof(assignments); i++) 
        applicants += ({ (assignments[i][0] + 
                         " (" + assignments[i][1] + ")") });

    as += (COMPOSITE_WORDS(applicants) + ".\n");
    return as;
}


/* Return a text listing of those who have been accepted into
   the guild. */
string
query_accepted_string()
{
    string rstr;

    if (sizeof(accepted) == 0)
        rstr = "There are currently no approved players for the Calian " +
                "guild.\n";     
    else
        rstr = "The folling players have been approved by the ROs and " +
               "may be admitted to the Calian guild by any Calian:\n" + 
               COMPOSITE_WORDS(accepted) + ".\n";
    return rstr;
}


int
is_calian_wiz(object tp)
{
    if (SECURITY->query_wiz_dom(tp->query_real_name()) == "Calia") 
        return 1;
    else
        return 0;
}


/* Returns 1 if player is an applicant, 0 otherwise */
int
is_calian(object player)
{
    return (player->query_guild_name_occ() == GUILD_NAME);
}


/* Returns 1 if str is the name of an applicant, 0 otherwise */
int 
is_applicant(string str)
{
    int i, m;

    if (!str)
	return 0;
    str = capitalize(lower_case(str));

    m = -1;
    for (i = 0; i < sizeof(assignments); i++) 
        if (assignments[i][0] == str)
            m = i;

    return (m != -1);
}


/* Returns 1 if str is the name of a recruiter, 0 otherwise */ 
int
is_recruiter(string str)
{
    if (!str)
	return 0;
    str = capitalize(lower_case(str));

    return (member_array(str, recruiters) != -1);
}


/* Returns 1 if str is the name of an accepted applicant, 0 otherwise */
int
is_accepted(string str)
{
    if (!str)
	return 0;
    str = capitalize(lower_case(str));

    return (member_array(str, accepted) != -1);
}


/* Returns an array with the recruiters names */
string
*query_recruiters()
{
    return recruiters + ({ });
}


/* Sends a text description of the recruiters to this_player() */
int
see_recruiters(string str)
{
    tell_object(TP, query_recruiters_string()); 
    return 1;
}


/* Sends a text description of the applicants to this_player() */
int
see_applicants(string str)
{   
    tell_object(TP, query_applicants_string());
    return 1;
}


/* Sends a text description of the accepted applicants to this_player() */
int
see_accepted(string str)
{
    tell_object(TP, query_accepted_string());
    return 1;
}



/* Function to remove any assignments in which nm is the recruiter 
   or the applicant. Used in rem_app. */
void
rem_ass(string nm)
{
    int i; 
    string *el;

    for (i = 0; i < sizeof(assignments); i++) {
        el = assignments[i];
        if ((el[0] == nm) || (el[1] == nm))
            assignments[i] = 0;
    }
    assignments -= ({ 0 });
}


/*
 * Function:    query_level_block
 * Description: Returns 1 if the player's level is too low to be
 *              allowed to apply, 0 otherwise.  
 */ 
int
query_level_block(object player)
{
    if (member_array(player->query_exp_title(), sd_av_levels) >=  
        member_array(minimum_level, sd_av_levels)) 
        return 0; 

    return 1; 
}


/*
 * Function:    query_application_level
 * Description: Returns the minimum level a player has to attain
 *              in order to apply, e.g. "adventurer".   
 */ 
string
query_application_level()
{
    return minimum_level; 
}


/*
 * Function:    application_level
 * Description: Sets the minimum level of allowed applicants. 
 */ 
int
application_level(string str)
{
    object tp = this_player(); 

    if (!stringp(str)) {
        tell_object(tp, "Possible levels are: " + 
                    COMPOSITE_WORDS(sd_av_levels) + ".\n" +
                    "The current minimum level is: " +
                    minimum_level + ".\n"); 
        return 1; 
    } 

    if (COUNCIL_CODE->is_council_member(tp->query_real_name()) ||
	  is_calian_wiz(tp)) {
        if (member_array(str, sd_av_levels) == -1) {
            tell_object(tp, "No such level!\n"); 
            return 1; 
        }
        minimum_level = str; 
        tell_object(tp, "Ok, the minimum level is now set to: " +
                    minimum_level + ".\n");
        save_object(RECRUITERS); 
        return 1;
    }
    notify_fail("You do not have the authority to change " +
                "the minimum application level.\n"); 
    return 0; 
}


/* Execute the removal of an applicant */
void
rem_app(string str)
{
    if (is_applicant(str)) {
        str = lower_case(str); 
        opinions = m_delete(opinions, str); 
        str = capitalize(str); 
        tunnel_access -= ({ str });  
        rm(APPLICANT_RECORDS+str); 
        rem_ass(str); /* Remove the assignment with that
                         applicant's name */
        save_object(RECRUITERS);
    }
}


/* Execute the removal of an accepted applicant */
void
rem_acc(string str)
{
    if (is_accepted(str)) {
        accepted -= ({ str }); 
        save_object(RECRUITERS);
    }
}


/* Execute the addition of a new applicant */
void
add_app(string str)
{
    str = capitalize(lower_case(str));
    if (!is_applicant(str)) {
        assignments += ({ ({str, NO_ASSIGNMENT}) }); 
        save_object(RECRUITERS);
        write_file(APPLICANT_RECORDS+str, 
              my_time() + str + " registered as applicant.\n");
    }
}


/* Execute the addition of a new accepted applicant */
void
add_acc(string str)
{
    if (!is_accepted(str)) {
        accepted += ({ str }); 
        save_object(RECRUITERS);
    }
}


/* Action to add an applicant to the assignment list */
int
add_applicant(string str)
{
    object tp = TP; 
    string adder;
 
    if (!str) return 0;
    adder = capitalize(tp->query_real_name());
    str = capitalize(lower_case(str));
    seteuid(getuid());
    restore_object(RECRUITERS);

    if (!SECURITY->exist_player(lower_case(str)))
    {
        NF("No such player!\n");
        return 0;
    }

    if (is_applicant(str)) {
        NF("That person is already on the applicants list!\n");
        return 0;
    }

    if (is_recruiter(adder) || COUNCIL_CODE->is_council_member(adder) ||
	  is_calian_wiz(tp) )
    {
        add_app(str);
        tell_object(tp, "Ok.\n");
        return 1;
    }
    else
    {
        NF("You do not have the authority to do that.\n");
        return 0;
    }
}



/* Action to remove an applicant from the assignment list. */
int
remove_applicant(string str)
{
    object tp = TP;
    string remover;

    if (!str)
	return 0;
    remover = capitalize(tp->query_real_name());
    str = capitalize(lower_case(str));
    
    seteuid(getuid());
    restore_object(RECRUITERS);
    if (sizeof(assignments) == 0)
    {
         NF("There are no current applicants!\n");
         return 0;
    } 

    if (is_recruiter(remover) || COUNCIL_CODE->is_council_member(remover) ||
	  is_calian_wiz(tp) )
    { 
        if (is_applicant(str))
	{
            rem_app(str);
            tell_object(tp, "Ok.\n");
            return 1;
        }
        else
	{
            NF("No such applicant!\n");
            return 0; 
        }
    }
    else
    {
        NF("You do not have the authority to do that.\n");
        return 0;
    }
}


/* Action to add an applicant to the accepted list. */
int
add_accepted(string str)
{
    object tp = TP; 
    string adder;

    if (!str) return 0;
    adder = capitalize(tp->query_real_name());
    str = capitalize(lower_case(str));
    seteuid(getuid());
    restore_object(RECRUITERS);

    if (!SECURITY->exist_player(lower_case(str)))
    {
        NF("No such player!\n");
        return 0;
    }

    if (is_accepted(str)) {
        NF("That person is already on the accepted list!\n");
        return 0;
    }

    if (is_recruiter(adder) || COUNCIL_CODE->is_council_member(adder) ||
	  is_calian_wiz(tp) )
    {
        add_acc(str);
        write_file(APPLICANT_RECORDS+str, 
                   my_time() + str + " accepted by " +
                   capitalize(tp->query_real_name()) + ".\n");
        tell_object(tp, "Ok.\n");
        return 1;
    }
    else
    {
        NF("You do not have the authority to do that.\n");
        return 0;
    }
}



/* Action to remove an applicant from the accepted list. */
int
remove_accepted(string str)
{
    object tp = TP;
    string remover;

    if (!str)
	return 0;
    remover = capitalize(tp->query_real_name());
    str = capitalize(lower_case(str));

    seteuid(getuid());
    restore_object(RECRUITERS);
    if (sizeof(accepted) == 0)
    {
         NF("There are currently no accepted players!\n");
         return 0;
    } 

    if (is_recruiter(remover) || COUNCIL_CODE->is_council_member(remover) ||
	  is_calian_wiz(tp) )
    { 
        if (is_accepted(str))
	  {
            rem_acc(str);
            write_file(APPLICANT_RECORDS+str, 
                   my_time() + str + " unaccepted by " +
                   capitalize(tp->query_real_name()) + ".\n");
            tell_object(tp, "Ok.\n");
            return 1;
        }
        else
	{
            NF("No such accepted player!\n");
            return 0; 
        }
    }
    else
    {
        NF("You do not have the authority to do that.\n");
        return 0;
    }
}


/* Action to add a recruiter to the list of recruiters. */
int
add_recruiter(string str)
{
    object tp = TP; 
    string adder;
 
    if (!str) return 0;
    adder = capitalize(tp->query_real_name());
    str = capitalize(lower_case(str));
    seteuid(getuid());
    restore_object(RECRUITERS);

    if (!SECURITY->exist_player(lower_case(str)))
    {
        NF("No such player!\n");
        return 0;
    }

    if (COUNCIL_CODE->is_council_member(adder) ||
	is_calian_wiz(tp) )
    {
        recruiters += ({ str });
        OBJECT("council_log_book")->update_log_book(my_time() + str +
	    " has been made a recruiter by " + adder + ".\n");
        save_object(RECRUITERS);
        tell_object(tp, "Ok.\n");
        return 1;
    }
    else
    {
        NF("You do not have the authority to do that.\n");
        return 0;
    }
}



/* Function to nullify any assignments for a given recruiter.  
   Used by remove_recruiter function only. */
void
nullify_ass_for_rec(string rec)
{
    mixed a2 = ({ });
    int i; 
    string *el;

    for (i = 0; i < sizeof(assignments); i++) {
        el = assignments[i];
        if (el[1] == rec) {
            write_file(APPLICANT_RECORDS+el[0], 
                       my_time() + el[0] + " unassigned.\n"); 
            a2 += ({ ({ el[0], NO_ASSIGNMENT }) });
        } 
        else 
            a2 += ({ el });
    }
    assignments = a2;
}


/* Action of removing a recruiter from the recruiter list. */
int
remove_recruiter(string str)
{
    object tp = TP;
    string remover;

    if (!str)
	return 0;
    remover = capitalize(tp->query_real_name());
    str = capitalize(lower_case(str));
    seteuid(getuid());
    restore_object(RECRUITERS);
    
    if (sizeof(recruiters) == 0)
    {
         NF("No one is a recruiter yet!\n");
         return 0;
    } 

    if ((is_recruiter(remover) && (remover == str)) || 
        COUNCIL_CODE->is_council_member(remover) ||
	is_calian_wiz(tp) )
    { 
        if (member_array(str, recruiters) > -1)
	{
            recruiters -= ({ str }); 
            roc -= ({ str });
            nullify_ass_for_rec(str);
            save_object(RECRUITERS);
            OBJECT("council_log_book")->update_log_book(my_time() + str +
		" has been removed from the recruiters by " +
		remover + ".\n");
            tell_object(tp, "Ok.\n");
            return 1;
        }
        else
	{
            NF("No such recruiter!\n");
            return 0; 
        }
    }
    else
    {
        NF("You do not have the authority to do that.\n");
        return 0;
    }
}




/* 
   Function to execute the change of an assignment for a given 
   applicant i.e. s/he has been assigned a new RO. 
   Used in change_assignment. 
 */
void
change_ass_for_app(string app, string new_ro)
{
    mixed a2 = ({ });
    int i; 
    string *el;

    for (i = 0; i < sizeof(assignments); i++) {
        el = assignments[i];
        if (el[0] == app)
            a2 += ({ ({ el[0], new_ro }) });
        else 
            a2 += ({ el });
    }
    assignments = a2;
}


/* Action to change an assignment. */
int
change_assignment(string str)
{
    object tp;
    string s1, s2, changer;

    tp = this_player(); 
    changer = capitalize(tp->query_real_name());

    if (!stringp(str)) {
        notify_fail("Usage: assign <recruiter> to <applicant>.\n");
        return 0;
    }

    if (sscanf(str, "%s to %s", s1, s2) != 2) {
        notify_fail("Usage: assign <recruiter> to <applicant>.\n");
        return 0;
    }

    s1 = capitalize(lower_case(s1));
    s2 = capitalize(lower_case(s2));

    seteuid(getuid());
    restore_object(RECRUITERS);

    if (!is_applicant(s2)) {
        notify_fail("No such applicant!\n");
        return 0;
    }

    if (!is_recruiter(s1)) {
        notify_fail("No such recruiter!\n");
        return 0;
    }

    /* Just allow the ROC or Council to change assignments. */
    if ((sizeof(roc) && (roc[0] == changer)) || 
        COUNCIL_CODE->is_council_member(changer) ||
	is_calian_wiz(tp) )
    {
        change_ass_for_app(s2, s1);
        write_file(APPLICANT_RECORDS+s2, 
                   my_time() + s1 + " assigned to " + s2 + 
                   " by " + capitalize(tp->query_real_name()) + ".\n");
        tell_object(tp, "Ok.\n"); 
        save_object(RECRUITERS);
        return 1;
    }
    else
    {
        notify_fail("You do not have the authority to do that.\n");
        return 0;
    }
}


int
is_roc(string str)
{
    if (sizeof(roc) && roc[0] == str)
        return 1;
   
    return 0;
}


/* Action to make someone the roc (recruitment officer coordinator) */
int
make_roc(string str)
{
    object tp = TP;
    string maker;

    if (!str)
	return 0;
    maker = capitalize(tp->query_real_name());
    str = capitalize(lower_case(str));
    seteuid(getuid());
    restore_object(RECRUITERS);
    
    if (sizeof(recruiters) == 0)
    {
         NF("No one is a recruiter yet!\n");
         return 0;
    } 

    if (COUNCIL_CODE->is_council_member(maker) ||
	is_calian_wiz(tp) )
    { 
        if (member_array(str, recruiters) > -1)
	{
            roc = ({str});
            save_object(RECRUITERS);
            OBJECT("council_log_book")->update_log_book(my_time() + str +
		" has been made ROC by " + maker + ".\n");
            tell_object(tp, "Ok.\n"); 
            return 1;
        }
        else
	{
            NF("No such recruiter!\n");
            return 0; 
        }
    }
    else
    {
        NF("You do not have the authority to do that.\n");
        return 0;
    }
}


int
query_applications_blocked()
{
    if (applications_cap <= sizeof(assignments))
        return 1;
    
    return 0;
}


int
cap_applications(string str)
{
    string n = this_player()->query_real_name(); 
    int num; 

    if (!stringp(str) || !strlen(str) || sscanf(str, "%d", num) != 1 ||
        num < APP_CAP_MIN || num > APP_CAP_MAX) {
        notify_fail("Cap applications at what number (" + 
                    APP_CAP_MIN + "-" + APP_CAP_MAX + ")? " + 
                    "The current cap is " + applications_cap + ".\n");  
        return 0;
    }

    seteuid(getuid()); 
    if (!COUNCIL_CODE->is_council_member(n) && 
        /* !is_roc(n) && */ 
        !is_calian_wiz(this_player())) {  
        notify_fail("You do not have the authority to do that.\n"); 
        return 0;
    } 

    applications_cap = num;  
    save_object(RECRUITERS); 
    write("Ok, the number of applications is capped at " + 
          LANG_WNUM(num) + ".\n"); 
    return 1;
}



int
query_tunnel_access(string str)
{
    if (member_array(capitalize(lower_case(str)), tunnel_access) > -1)
        return 1;
  
    return 0;
}


int
list_tunnel_access(string str)
{
    if (!sizeof(tunnel_access)) {
        notify_fail("No applicants currently have tunnel access.\n"); 
        return 0;
    } 

    write("The following applicants have tunnel access:\n" + 
          COMPOSITE_WORDS(tunnel_access) + ".\n"); 
    return 1;
}


int
add_tunnel_access(string str)
{
    string n = this_player()->query_real_name(); 

    seteuid(getuid()); 
    if (!COUNCIL_CODE->is_council_member(n) && 
        /* !is_roc(n) && */ 
        !is_calian_wiz(this_player())) {  
        notify_fail("You do not have the authority to do that.\n"); 
        return 0;
    } 

    if (!is_applicant(str)) { 
        notify_fail("There is no such applicant!\n"); 
        return 0;
    } 

    str = capitalize(lower_case(str)); 

    if (member_array(str, tunnel_access) > -1) {
        notify_fail("That character has access to the tunnels.\n"); 
        return 0;
    } 

    tunnel_access += ({ str });  
    save_object(RECRUITERS); 
    write_file(APPLICANT_RECORDS+str, 
               my_time() + str + " granted tunnel access by " +  
               capitalize(n) + ".\n");

    write("Ok.\n"); 
    return 1;
}


int
remove_tunnel_access(string str)
{
    string n = this_player()->query_real_name(); 

    seteuid(getuid()); 
    if (!COUNCIL_CODE->is_council_member(n) && 
        /* !is_roc(n) && */ 
        !is_calian_wiz(this_player())) {  
        notify_fail("You do not have the authority to do that.\n"); 
        return 0;
    } 
    str = capitalize(lower_case(str)); 
    if (member_array(str, tunnel_access) == -1) {
        notify_fail("No-one by that name has access to the tunnels.\n"); 
        return 0;
    } 

    tunnel_access -= ({ str });  
    save_object(RECRUITERS); 
    write_file(APPLICANT_RECORDS+str, 
               my_time() + str + " has tunnel access removed by " +  
               capitalize(n) + ".\n");

    write("Ok.\n"); 
    return 1;
}


/* Action function for giving an opinion for the admittance of an applicant */ 
int
opinion(string str)
{
    object tp = this_player();     
    mapping op; 
    int val; 
    string app, n; 

    if (!is_calian(tp)) {
        notify_fail("You are not a Calian.\n");  
        return 0;
    } 

    notify_fail("Syntax: opinion <num> <applicant>.\n" + 
            "The number you give should be between -5 and 5, " +
            "where -5 means that in your opinion the applicant is an " +
            "extremely bad prospect, 5 means an extremely good one, 0 " +
            "means you don't have an opinion on the applicant (this can " +
            "be used to remove your opinion from the system). " +
            "Only the council and recruiting officers will be " +
            "able to read your input. Note that this is not a voting " +
            "system, it is just a central summary of " +
            "opinions that can help to make recruitment a more " +
            "manageable process.\n"); 

    if (!stringp(str) || !strlen(str)) 
        return 0;

    if (sscanf(str, "%d %s", val, app) != 2) 
        return 0;

    app = lower_case(app); 
    if (!is_applicant(app)) { 
        notify_fail("There is no such applicant.\n");  
        return 0;
    }  

    if (val < -5 || val > 5) { 
        notify_fail("You must give a number between -5 and 5 inclusive.\n");  
        return 0;
    } 

    n = tp->query_real_name(); 

    op = opinions[app];  
    if (!mappingp(op)) 
        op = ([ ]); 
    else if (val == 0) {
        op = m_delete(op, n); 
        opinions += ([ app : op ]); 
        save_object(RECRUITERS); 
        write("Ok, you have no opinion on that applicant.\n"); 
        return 1;
    }

    op += ([ n : val ]);  
    opinions += ([ app : op ]); 
    save_object(RECRUITERS); 
    write("Ok.\n"); 
    return 1;
}


/* 
 * Action function for checking details and opinions for an applicant 
 */ 
int
check(string app)
{
    mapping op; 
    string *ix; 
    int i; 
    string str, n, tmp; 

    if (!stringp(app) || !strlen(app)) {
        notify_fail("Check information on which applicant?\n");  
        return 0;
    } 

    seteuid(getuid()); 
    n = this_player()->query_real_name(); 
    if (!COUNCIL_CODE->is_council_member(n) && 
        !is_recruiter(n) && 
        !is_calian_wiz(this_player())) {  
        notify_fail("You do not have the authority to do that.\n"); 
        return 0;
    } 

    app = lower_case(app); 
    if (!is_applicant(app)) { 
        notify_fail("There is no such applicant.\n");  
        return 0;
    }  

    op = opinions[app]; 

    app = capitalize(app); 
    tmp = read_file(APPLICANT_RECORDS+app); 

    if (!mappingp(op) || !m_sizeof(op)) { 
        if (!stringp(tmp)) { 
            notify_fail("There is no information available " +
                        "on that applicant.\n"); 
            return 0;
        } 
    } 
    else { 
        ix = m_indexes(op);  

        str = ""; 
        for (i = 0; i < sizeof(ix); i++) 
            str += (capitalize(ix[i]) + ": " + op[ix[i]] + "\n"); 

        if (stringp(tmp)) 
            tmp += "\n"; 
        else
            tmp = ""; 

        tmp +=  ("Opinions on the worthiness of the " +
                 "applicant " + app + ":\n" + 
                 sprintf("%-80#s\n", str)); 
    }

    this_player()->more(tmp); 
    return 1;
}


/* Action to remove the ROC. */
int
remove_roc(string str)
{
    object tp = TP;
    string remover;

    if (!str)
	return 0;
    remover = capitalize(tp->query_real_name());
    str = capitalize(lower_case(str));
    seteuid(getuid());
    restore_object(RECRUITERS);
    
    if (sizeof(recruiters) == 0)
    {
         NF("No one is a recruiter yet!\n");
         return 0;
    } 

    if ((sizeof(roc) && (remover == roc[0])) || 
        COUNCIL_CODE->is_council_member(remover) ||
	  is_calian_wiz(tp) )
    { 
        if (roc[0] == str)
	  {
            roc -= ({str});
            save_object(RECRUITERS);
            OBJECT("council_log_book")->update_log_book(my_time() + str +
               	 " has been removed as ROC by " + remover + ".\n");
            tell_object(tp, "Ok.\n");
            return 1;
        }
        else
	{
            NF("That person is not the ROC!\n");
            return 0; 
        }
    }
    else
    {
        NF("You do not have the authority to do that.\n");
        return 0;
    }
}
