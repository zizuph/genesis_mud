
/* 
 * /d/Genesis/start/human/town/tower_office.c
 * 
 * This is an inheritable domain office to provide some basic commands 
 * for mortals who access the domain offices in the tower of realms.    
 * If you inherit from it, use the create function is create_tower_office(). 
 * Players will get the command "wizards" to list domain wizards, and 
 * and "projects <domain/wizard>" to read project files about the domain 
 * or wizard. By default the path to your projects directory is 
 * "/d/Domain/open/" (e.g "/d/Wiz/open/"), but you can change it using 
 * set_project_dir(your_dir);  
 * Project file names should take the form like Maniac.prj, Wiz.prj etc. 
 * By default players will be informed of the ranks of wizards in the
 * domain and whether they are logged in when they use the "wizards" 
 * command. You can change this if you want with the functions 
 * disable_logged_in_display() and disable_rank_display()
 * Note: to add the exit back to the correct level in the tower from 
 * your office, use add_tower_link(exit_name); for instance 
 * add_tower_link("tower");  This will set up the exit to the correct 
 * floor in the tower, but you must have visited it and used <addoffice> 
 * in order for this to be possible. If you want to set up the standard
 * office sign, use add_office_sign(); 
 * 
 * Coded by Maniac, December 1996
 */ 

#pragma save_binary
#pragma strict_types

#include <std.h>
#include <composite.h>
#include <stdproperties.h>

#include "tower.h"

inherit "/std/room";

void enable_rank_display(); 
void disable_rank_display(); 
void enable_logged_in_display(); 
void disable_logged_in_display(); 
void set_project_dir(string pd); 
void set_project_path(string pp); 
void create_tower_office(); 
void add_tower_link(string exit_name); 
void add_office_sign(); 

static int logged_in_display; 
static int rank_display; 
static string projdir; 

nomask void
create_room()
{
     set_short("Tower office of " + query_domain());   
     enable_logged_in_display(); 
     enable_rank_display(); 
     set_project_dir("/d/" + query_domain() + "/open/"); 
     create_tower_office(); 
     add_prop(ROOM_I_INSIDE, 1); 
}

void
create_tower_office()
{
     set_long("Tower office of " + query_domain() + ".\n"); 
     add_office_sign(); 
     add_tower_link("tower"); 
}

void
add_office_sign()
{
     add_my_desc("There is a sign here that you can read.\n"); 
     add_item("sign", OFFICE_SIGN_TEXT); 
     add_cmd_item("sign", "read", OFFICE_SIGN_TEXT); 
}

void
enable_logged_in_display()
{
    logged_in_display = 1; 
}

void
disable_logged_in_display()
{
    logged_in_display = 0; 
}

void
enable_rank_display()
{
    rank_display = 1; 
}

void
disable_rank_display()
{
    rank_display = 0; 
}

void
set_project_dir(string pd)
{
    projdir = pd;
}

void
set_project_path(string pp)
{
    projdir = pp; 
}

void
add_tower_link(string exit_name)
{
    string ep;

    if (!stringp(exit_name) || (strlen(exit_name) > 20)) 
        return;

    ep = OFFICE_FLOOR(query_domain()); 
    if (!stringp(ep)) 
        return;

    remove_exit(exit_name); 
    add_exit(ep, exit_name);  
}


/* logged in tag */ 
string
ltag(string pn)
{
    object tp;

    if (objectp(tp = find_player(pn)) && !tp->query_invis())  
        return " (logged in)"; 
    else 
        return ""; 
}


/* Rank tag */ 
string
rtag(string pn)
{
    int r;
    object tp;

    if (intp(r = SECURITY->query_wiz_rank(pn)) && rank_display)    
         return (" (" + capitalize(WIZ_RANK_NAME(r)) + ")");     
    else
         return "";
}

string 
wizard_list()
{
   int i;
   string o, *w; 
 
   w = SECURITY->query_domain_members(query_domain()); 

   if (!pointerp(w)) 
       return ""; 

   o = ""; 

   for (i = 0; i < sizeof(w); i++)  
        o += (capitalize(w[i]) + (logged_in_display ? ltag(w[i]) : "") + 
                      rtag(w[i]) + "\n"); 

   return sprintf("%-70#s", o); 
}

int
do_list_wizards()
{
    object tp = this_player(); 

    tell_object(tp, 
           "Wizards of the " + query_domain() + " domain:\n" + 
            wizard_list() + "\n");  
    return 1;
}


int
do_list_projects(string str)
{
    object tp = this_player(); 
    string *w, fp; 

    if (!stringp(str)) 
        str = query_domain(); 
    else
        str = capitalize(lower_case(str)); 


    fp = (projdir + str + PROJ_EXT); 
    if (file_size(fp) == -1) {  
        w = SECURITY->query_domain_members(query_domain());  
        if (member_array(lower_case(str), w) > -1) {  
            notify_fail("There doesn't appear to be a projects entry for " + 
                        "the wizard " + str + ".\n"); 
            return 0;
        } 
        else if (str == query_domain()) { 
            notify_fail("There doesn't appear to be a projects entry " +
                        "for the domain " + str + ".\n"); 
            return 0;
        } 
        else { 
           notify_fail("There doesn't appear to be a projects entry for " +
                       "the topic " + str + ".\n"); 
           return 0;
        } 
    } 

    tp->more("You read the projects entry for " + capitalize(str) + 
             ":\n" + read_file(fp));
    return 1;
}

void
init()
{
    ::init(); 
    add_action(do_list_wizards, "wizards");  
    add_action(do_list_projects, "projects"); 
}

