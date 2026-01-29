/*
 * /d/Calia/pond/objects/frog_shadow
 * 
 *  Shadow for the frog quest in Calia 
 *  borrowed by Amelia
 *
 *  Modifications by Maniac, October 1997
 */

inherit "/std/shadow";
#include "../pond.h"


varargs public mixed
query_adj(int arg)
{
    if (!arg) 
         return "green";
    else 
         return ({"green", "warty"});
}


int
adjectiv_id(string str)
{
    return (member_array(str, query_adj(1)) >= 0);
}

string *
parse_command_adjectiv_id_list()
{
    return query_adj(1);
}

string
query_m_in()
{
    return "arrives hopping.";
}

string
query_m_out()
{
	return "leaves hopping";
}


/*
string
query_race_name()
{
	return "frog";
}
*/

string
race_sound()
{
    return "croaks"; 
}

string
actor_race_sound()
{
    return "croak"; 
}

int
query_frog_shadow()
{
	return 666;
}

void
destruct_frog_shadow()
{
    set_alarm(1000.0, 0.0, remove_shadow);
}

public void
remove_shadow()
{
    shadow_who->set_m_in("arrives.");
    shadow_who->set_m_out("leaves");
    ::remove_shadow();
}

public void
remove_object()
{
    shadow_who->set_m_in("arrives.");
    shadow_who->set_m_out("leaves");
    ::remove_object();
}
