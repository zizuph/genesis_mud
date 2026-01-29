/*
 * /d/Gondor/guilds/rangers/obj/tracker.c
 *
 * Coded by Gwyneth
 * Tracks actions of those that shouldn't be in the guild.
 *
 * Modifications
 * - Petros, May 2011 - changed so that this object won't be cloned
 *                      onto an arch.
 *
 */
inherit "/std/object";

#include <composite.h>
#include <filter_funs.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "../rangers.h"

void
create_object()
{
    set_name("_ranger_tracker");
    set_short("piece of wood");
    set_no_show();

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GIVE, 1);
}

int
track_things(string str)
{
    object *oblist = all_inventory(ENV(ENV(TO)));
    string txt;
    int i;

    oblist = FILTER_PLAYERS(oblist);

    txt = extract(ctime(time()), 4) + " in " + file_name(ENV(ENV(TO)))
        + "\n" + CAP(ENV(TO)->query_real_name()) + " executed " + query_verb()
        + " " + str + "\nPresent: " + COMPOSITE_LIVE(oblist) + "\n";

    log_file("intruder", txt);
    return 0;
}

void
init()
{
    ::init();

    add_action(track_things, "exa");
    add_action(track_things, "examine");
    add_action(track_things, "look");
    add_action(track_things, "l");
    add_action(track_things, "read");
    add_action(track_things, "improve");
    add_action(track_things, "list");
    add_action(track_things, "view");
    add_action(track_things, "More");
    add_action(track_things, "stat");
    add_action(track_things, "Cat");
    add_action(track_things, "Tail");
    add_action(track_things, "Items");
    add_action(track_things, "At");
    add_action(track_things, "Call");
    add_action(track_things, "Dump");
    add_action(track_things, "execr");
    add_action(track_things, "exec");
}

/*
 * Function name: enter_env
 * Description  : This function is called each time this object enters a
 *                new environment. If you mask it, be sure that you
 *                _always_ call the ::enter_env(dest, old) function.
 * Arguments    : object dest - the destination we are entering.
 *                object old  - the location we came from. This can be 0.
 */
public void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);
    
    // This object cannot be cloned onto an arch wizard    
    if (objectp(dest)
        && dest->query_wiz_level()
        && SECURITY->query_wiz_level(dest->query_real_name()) >= WIZ_ARCH)
    {
        set_alarm(0.0, 0.0, remove_object);
    }
}
