/* Plaque for retired council members to be listed.

   Coded by Maniac 7.7.95

   History:
*/

#include <stdproperties.h>

#include "defs.h"
#include CALIAN_HEADER
#include COUNCIL_HEADER

#define MAX_RETIRED 30

#pragma save_binary

inherit "/std/object";

mapping retired = ([ ]);
static string *vals = ({ });
static string *ind = ({ });

string
my_long()
{
    object tp = this_player();
    string str, s;
    int i;

    str = "On this plaque are listed retired members of the Calian Council:\n"; 
    if (!sizeof(ind))
        str += "The list is currently empty.\n";
    else
        for (i = 0; i < sizeof(ind); i++) { 
            s = retired[ind[i]] + ", retired " + ctime(atoi(ind[i])); 
            str += (s + ".\n");
        }

    seteuid(getuid());
    if (COUNCIL_CODE->is_council_member(tp->query_name()))
        str += ("\nCouncil Commands:\n" +
               "addret <name> : Add player to retirement list.\n" +
               "remret <name> : Remove player from retirement list.\n");
                
    return str;
}


void
organise_retired()
{
    if (!retired)
        retired = ([ ]);
    vals = m_values(retired);
    if (!vals) 
       vals = ({ }); 
    ind = m_indexes(retired);
    if (!ind)
       ind = ({ });
    if (sizeof(ind))
       ind = sort_array(ind);
}


void
create_object()
{
    set_name("plaque");
    set_short("plaque on the east wall");
    set_long("@@my_long");
    add_prop(OBJ_M_NO_GET, 1);
    seteuid(getuid());
    restore_object(GLYKRON_TEXTS+"retired");
    organise_retired();
}


/* Remove retired council member */
int
remret(string str)
{
    object tp = this_player();
    int i;

    seteuid(getuid());
    if (!COUNCIL_CODE->is_council_member(tp->query_name()))
        return 0;

    if (!str) {
        notify_fail("Remove who from the retired list?\n");
        return 0;
    }
         
    str = capitalize(str);
    if (!sizeof(vals)) {
        notify_fail("No one on the list to remove!\n"); 
        return 0;
    }

    if (member_array(str, vals) == -1) {
        notify_fail("No such player on the list!\n");
        return 0;
    }

    for (i = 0; i < sizeof(ind); i++)
        if (retired[ind[i]] == str)  
            retired = m_delete(retired, ind[i]); 

   organise_retired();
   tp->catch_msg("Ok.\n");
   save_object(GLYKRON_TEXTS+"retired");
   return 1;
}


/* Add retired council member */
int
addret(string str)
{
    object tp = this_player();

    seteuid(getuid());
    if (!COUNCIL_CODE->is_council_member(tp->query_name()))
        return 0;

    if (!str) {
        notify_fail("Add who to the retired list?\n");
        return 0;
    }
         
    str = capitalize(str);

    if (member_array(str, ind) != -1) {
        notify_fail("Player already on the list!\n");
        return 0;
    }

    if (sizeof(ind) >= MAX_RETIRED) {
        notify_fail("Too many retired people on list, please remove " +
                    "one or more and try again.\n");
        return 0;
    }

    retired += ([ ("" + time()) : str ]);
    organise_retired();
    tp->catch_msg("Ok.\n");

    save_object(GLYKRON_TEXTS+"retired");
    return 1;
}


void
init()
{
    ::init();
    add_action("addret", "addret");
    add_action("remret", "remret"); 
}
