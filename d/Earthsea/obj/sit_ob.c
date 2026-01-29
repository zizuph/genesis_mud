/*  This is a simple 'sit' object that works with the
 *  chair in the domain office. It prevents the player
 * from moving out of the room, until he/she stands up.
 * Amelia 5-24-98
 */
inherit "/std/object";



#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#define TO this_object()

public int do_all_commands(string str);
int no_command();


void
create_object()
{
    set_name("sit_ob");
    set_short("sit_ob");
    set_no_show();
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_M_NO_GIVE, 1);
    add_prop(OBJ_M_NO_DROP, 1);

}

void
init()
{
    ::init();

    ::init();
    add_action(&do_all_commands(), "", 1);
}



public int
do_all_commands(string str)
{
    string verb;
    string *not_allowed;

    not_allowed=({"n","north","s","south","w","west","e","east","nw",
      "northwest","sw","southwest","se","southeast",
      "northeast", "ne", "teleport", 
      "tower", "back",
      "u", "up", "d", "down" });

    verb = query_verb();

    if (member_array(verb,not_allowed)==-1)
	return 0;
    else 
	return TO->no_command();

    return 1; /* should never occur */
}

int
no_command()
{
    write("You have to stand up first to do that.\n");
    return 1;
}
