#include "defs.h"
#define RAUMDOR_TRAP_FOUND_MOSS "_raumdor_trap_found_moss"
inherit "/std/object";

int ripped;

public int
query_ripped()
{
    return ripped;
}

public void
reset_ripped()
{
    ripped = 0;
}

void
create_object()
{
    set_name(({"moss", "dark moss", "vein"}));
    set_long("@@description");
    set_no_show_composite(1);
    add_prop(OBJ_I_NO_GET, 1);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");

    reset_ripped();
}

mixed
do_search(object searcher, string what)
{
    if (id(what))
    {
        return "You do not find anything, but you might be able to " +
                "rip out the moss.\n";
    }
    return 0;
}

string
description()
{
    if (query_ripped())
        return "It a vein of dark moss that has been partly ripped out " +
            "of the wall, exposing a crevice.\n";
    return "It is a vein of dark moss, growing in an upward vein.\n";
}

public int
check_seen(object for_obj)
{
    if (for_obj->query_prop(RAUMDOR_TRAP_FOUND_MOSS))
        return ::check_seen(for_obj);
    return 0;
}

int
do_rip(string str)
{
    string target;

    if (!check_seen(TP) || !TP->can_see_in_room())
        return 0;

    notify_fail("Rip what?\n");
    if (!str)
        return 0;

    if (!parse_command(str, ({ environment() }), " [out] [the] %s ", target))
        return 0;

    notify_fail("Rip what? The moss?\n");    
    if (!id(target))
        return 0;

    if (query_ripped())
    {
        write("It's already ripped out!\n");
        return 1;
    }

    ripped = 1;
    write("You rip some moss out of the wall, exposing a crevice!\n");
    TELL_SEEN(TP, QCTNAME(TP) + " pulls at an area on the wall.\n");

    return 1; 
}

void
init()
{
    ::init();
    add_action(do_rip, "rip");
}


