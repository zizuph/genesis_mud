#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"

inherit "/std/object";

#define DRAUGHT_SUBLOC "draught_subloc"


void
create_object()
{
    seteuid(getuid());

    set_name("pass_out_object");
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    add_prop(OBJ_I_VALUE, 0);

    set_no_show();
}


void
init()
{
    ::init();
    add_action("do_all_commands", "", 1);
}


int
do_all_commands(string str)
{
    if (E(TO)->query_wiz_level())
    {
	return 0;
    }

    E(TO)->catch_msg("You are not in control of your senses.\n");
    return 1;
}


void
do_pass_out()
{
    int time;    /* time the player is passes out */

    E(TO)->add_subloc(DRAUGHT_SUBLOC, TO);

    time = (20 - (E(TO)->query_base_stat(SS_CON) / 20));

    E(TO)->catch_msg("You pass out on the ground.\n");
    tell_room(E(E(TO)), QCTNAME(E(TO)) + " passes out on " 
      + "the ground.\n", E(TO));
    E(TO)->add_prop(LIVE_S_EXTRA_SHORT, " " + "passed out on the "
      + "ground, in a drunken heap");

    set_alarm(itof(time), 0.0, "remove_pass_out");

}


void
remove_pass_out()
{
    E(TO)->catch_msg("You slowly regain your senses.\n");
    tell_room(E(E(TO)), QCTNAME(E(TO)) + " seems to regain "
      + POSSESSIVE(E(TO)) + " senses.\n", E(TO));

    E(TO)->remove_prop(LIVE_S_EXTRA_SHORT);

    E(TO)->remove_subloc(DRAUGHT_SUBLOC);
    remove_object();
}


string
show_subloc(string subloc, object carrier, object for_obj)
{
    string str;

    if (carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
    {
	return "";
    }

    if (for_obj == carrier)
    {
	str = "You are passed out on the ground, in a drunken heap.\n";
    }
    else
    {
	str = C(PRONOUN(E(TO))) + " is passed out on the ground, in a "
	+ "drunken heap.\n";
    }

    return str;
}

void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if (!objectp(to))
    {
	remove_object();
	return;
    }

    if (!living(to))
    {
	remove_object();
	return;
    }

    set_alarm(2.0, 0.0, "do_pass_out");
}
