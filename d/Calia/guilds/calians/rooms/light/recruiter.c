
/* 
 * Recruiters' room in the Crystalline palace.
 *
 * History: 
 *        3/5/2000 added application level command             Maniac
 *         3/7/98  added new commands                          Maniac
 *        26/7/96  Call recruiter code instead of inheriting   Maniac
 *        9/11/95  added assignment command                    Maniac
 *         4.8.95  added ROC commands                          Maniac
 *         6.4.95  accepted Calians system added               Maniac
 *         9.2.95  Applicants commands added                   Maniac
 *         3.1.95         Created                Maniac & Malcontent
 *
 */


#pragma save_binary

inherit "std/room.c";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#include COUNCIL_HEADER
#include RECRUITER_HEADER

static object this;


void 
create_room()
{
    set_short("Calian Recruiters Office");
    set_long(
        "This is a trapezoidal-shaped room whose east and south walls " +
        "slope away from you to the northwest.  " +
        "The room is filled by a brilliant light.  " +
        "A recruitment desk sits against the north wall.  " +
        "On the east wall there is a large banner.  " +
        "\n");

    add_item( ({ "banner" }),
        "On the golden, silver-edged banner, are written the words " +
            "\"The selfless best know those who will be loyal.\"\n" + 
        "The words \"help banner\" seem somehow to suggest themselves to " +
            "you.\n");
    add_item( ({ "desk", "desks", "crystal desk", "crystal desks", }), "A " +
        "fine desk it is, this desk is made of pure crystal. You " +
            "could see right through it to the floor, if you could " +
            "see through the clutter of papers that is! \n");
    add_exit(ROOM("light_boardroom"), "south", 0, 0);
    this = THIS;
    seteuid(getuid(this));
    clone_object(OBJECT("calian_members_poster"))->move(this);
    add_prop(ROOM_I_INSIDE, 1); 
}


int
help(string str)
{
    object tp = TP; 

    if (str != "banner")
        return 0;
    else
    {
        tp->more("Commands available to all:\n" +
         "recruiters                  - check recruiters.\n" +
         "applicants                  - check applicants.\n" +
         "accepted                    - check accepted players.\n" +
         "access                      - list applicants with tunnel access.\n" + 
         "applev                      - shows the current minimum level of\n" + 
         "                              applicants and all possible levels.\n" + 
         "opinion <num> <applicant>   - give an opinion on an applicant.\n" +
         "opinion                     - information about the opinion command.\n\n" +  
         "Commands available to Recruiters and the Council:\n" + 
         "check <applicant>           - check information on an applicant.\n" + 
         "remrec <player>             - remove recruiter <player>.\n" +
         "addapp <player>             - add applicant <player>.\n" +
         "remapp <player>             - remove applicant <player>.\n" +
         "addacc <player>             - add accepted <player>.\n" +
         "remacc <player>             - remove accepted <player>.\n\n" +  
         "Commands available to Council only:\n" +
         "addrec <player>             - add recruiter <player>.\n" + 
         "aroc <player>               - make <player> the ROC.\n" +
         "cap <num>                   - cap the number of applications\n" + 
         "                              allowed at <num>.\n" + 
         "applev <level>              - set the minimum level of applicants.\n" +
         "permit <applicant>          - permission to use the tunnels.\n" +
         "revoke <applicant>          - no permission to use the tunnels.\n\n" +
         "Commands available to the ROC and Council only:\n" + 
         "cass <rec> to <app>         - assign recruiter to applicant.\n"+
         "rroc <player>               - remove <player> as ROC.\n");
        return 1;
    }
}


int
see_recruiters(string str)
{
    return RECRUITER_CODE->see_recruiters(str); 
}


int
see_applicants(string str)
{
    return RECRUITER_CODE->see_applicants(str); 
}


int
see_accepted(string str)
{
    return RECRUITER_CODE->see_accepted(str); 
}

int 
opinion(string str)
{
    return RECRUITER_CODE->opinion(str); 
}

int
check(string str)
{
    return RECRUITER_CODE->check(str); 
}

int
cap_applications(string str)
{
    return RECRUITER_CODE->cap_applications(str); 
}

int
add_recruiter(string str)
{
    return RECRUITER_CODE->add_recruiter(str); 
}

int
remove_recruiter(string str)
{
    return RECRUITER_CODE->remove_recruiter(str); 
}

/*
 * Function:    application_level
 * Description: Sets the minimum level of allowed applicants. 
 */ 
int
application_level(string str)
{
    return RECRUITER_CODE->application_level(str); 
}

int
add_applicant(string str)
{
    return RECRUITER_CODE->add_applicant(str); 
}

int
remove_applicant(string str)
{
    return RECRUITER_CODE->remove_applicant(str); 
}

int
add_accepted(string str)
{
    return RECRUITER_CODE->add_accepted(str); 
}


int
remove_accepted(string str)
{
    return RECRUITER_CODE->remove_accepted(str); 
}


int
remove_roc(string str)
{
    return RECRUITER_CODE->remove_roc(str); 
}


int
make_roc(string str)
{
    return RECRUITER_CODE->make_roc(str); 
}


int
change_assignment(string str)
{
    return RECRUITER_CODE->change_assignment(str); 
}


int
access(string str)
{
    return RECRUITER_CODE->list_tunnel_access(str); 
}


int
permit(string str)
{
    return RECRUITER_CODE->add_tunnel_access(str); 
}


int
revoke(string str)
{
    return RECRUITER_CODE->remove_tunnel_access(str); 
}


void 
init()
{
     ::init();
     add_action(help, "help");
     add_action(see_recruiters, "recruiters");
     add_action(see_applicants, "applicants");
     add_action(see_accepted, "accepted");
     add_action(opinion, "opinion"); 
     add_action(check, "check"); 
     add_action(cap_applications, "cap"); 
     add_action(add_recruiter, "addrec");
     add_action(remove_recruiter, "remrec");
     add_action(application_level, "applev"); 
     add_action(add_applicant, "addapp");
     add_action(remove_applicant, "remapp");
     add_action(add_accepted, "addacc");
     add_action(remove_accepted, "remacc");
     add_action(remove_roc, "rroc");
     add_action(make_roc, "aroc");
     add_action(change_assignment, "cass");
     add_action(access, "access"); 
     add_action(permit, "permit"); 
     add_action(revoke, "revoke"); 
}
