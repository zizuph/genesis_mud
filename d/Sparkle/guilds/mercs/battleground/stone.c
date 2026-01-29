/* 
 * This is a modified version of the tell-relay object used
 * in the gladiator arena in Tyr. I have seriously lowered 
 * the processing that is performed on each action in an
 * attempt to lessen the lag these rooms cause. Rather than
 * check each person in the stands if they have gag misses
 * and see no fights on, we do a simple tell room to the 
 * stands and gag all misses by default.
 */

inherit "/std/object";

#include "../merc.h"

#define RINGSIDE MBATTLE + "stands"

create_object()
{
    set_name("stone1");
    add_name("test");
    set_short("small stone");
    set_long("A small stone.\n");
    add_prop(OBJ_I_NO_GET,1);
    enable_commands();
    set_no_show(1);
    seteuid(getuid(this_object()));
}

void catch_msg(mixed str, object obj)
{
    object stands = find_object(RINGSIDE);
    if (query_verb() == "shout")
	return;

    if (stringp(str) && !pointerp(str))
    {
        tell_room(stands, " * "+ str);
        return;
    }
}

int
query_option(int opt)
{
    if(opt == OPT_GAG_MISSES) return 1;
}

