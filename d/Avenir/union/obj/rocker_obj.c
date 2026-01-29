#pragma strict_types
/*
 * An item for the rocking chair to capture
 * linkdeath events.
 */
inherit "/std/object";

#include <cmdparse.h>

public int block;
public object chair;

public void
set_rocker(object ob)	{ chair = ob; } 

public void
set_blocking(int val)	{ block = val; }

public void
create_object(void)
{
    set_short("__rocker_obj");
    set_long("Do not see me.");
    set_name("__rocker_obj");
    set_no_show();
}

public void
linkdeath_hook(object player, int linkdeath)
{
    if (!linkdeath)
	return;

    chair->do_rise(0);
}

public int
nothing(string str)
{
    string *exits = environment(this_player())->query_exit_cmds();

    if (member_array(query_verb(), exits) == -1)
	return 0;

    if (block)
    {
	write("You must stand up before you can do that.\n");
	return 1;
    }

    return !chair->do_rise(0);
}

public int
init(void)
{
    ::init();

    if (environment() == this_player())
	add_action(nothing, "", 1);
}
