/*

   Removes the command to introduce yourself as a polymorphed creature.

   Can be used to remove commands unsuitable for the polymorph creatures.

   Arman - 2017
*/

inherit "/std/object";
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include "/d/Krynn/common/defs.h"

public int no_command();
public int quit_message();

int time;
object victim;

create_object() 
{
    seteuid(getuid());
    set_name("wohs_polymorph_self_no_intro_obj");

    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    add_prop(OBJ_I_VALUE, 0);

    set_no_show();
}

init()
{
    ::init();
    add_action("do_all_commands", "", 1);
}

public int
do_all_commands(string str)
{
    string verb;
    string *not_allowed;
    string *quit_attempted;

    not_allowed = ({ "introduce", "present" });
    quit_attempted = ({ "quit" });

    if (TP->query_wiz_level()) 
	return 0;

    verb = query_verb();

    if(str == "quit")
        return quit_message();

    if (member_array(verb, not_allowed) == -1)
    {
      if (member_array(verb, quit_attempted) == -1)
	return 0;
      else
        return quit_message();
    }
    else
	return no_command();

    return 1;
}

int
no_command()
{
    write("You can't introduce yourself in this form.\n");
    return 1;
}

int
quit_message()
{
    write("You need to return to your original form before quitting." +
       " [dispel all] to end your polymorph self spell.\n");
    return 1;
}


void
enter_env(object to, object from)
{
    ::enter_env(to, from);
    if(!objectp(to))
    {
	remove_object();
	return;
    }

    if(!living(to))
    {
	remove_object();
	return;
    }

    victim = to;
}
