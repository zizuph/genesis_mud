/*
   /d/Kalad/lib/extra_long.c
   
   Add an extra line of description to an npc.
   
   Taken from /d/Krynn/open/monster/monster.c
   Fysix@Genesis, Nov 1997
 */
#pragma save_binary
#pragma strict_types

#include <stdproperties.h>

#define SUBLOC "_my_extra_long_subloc"

static string extra_long;

/* Function name: set_extra_long
 * Description:   Add an extra long description to the mobile 
 * Arguments:     str - The string
 */
void
set_extra_long(string str)
{
    extra_long = str;
    this_object()->add_subloc(SUBLOC, this_object());
}

/* Function name: show_subloc
 * Description:   This function is called to get the extra str
 * Arguments:     subloc  - The name of this sublocation
 *		  me      - this_object()
 * 		  for_obj - Who wants this description
 * Returns:	  The extra string to write
 */
string
show_subloc(string subloc, object me, object for_obj)
{
    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "";

    return (extra_long);
    //return this_object()->check_call(extra_long);
}

