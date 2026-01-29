#pragma strict_types

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>

#include "/d/Khalakhor/sys/defs.h"

inherit "/std/weapon";

public void
create_weapon()
{
    set_name("herring");
    add_name("fish");
    set_adj("eric");
    add_adj("the half");
    set_long("It's a herring! Affenctionately known as Eric the " +
        "half-herring, possession of this means you excel in " +
        "the fields of silly walking and are a conesseur of " +
        "fine australian wine.\n");
    set_hit(100);
    set_pen(100);
    set_wt(W_CLUB);
    set_hands(W_ANYH);
    set_dt(W_BLUDGEON);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_VALUE, 0);
}

public int
do_squeeze(string str)
{
    if (!str || !strlen(str))
        return 0;

    if (this_object()->id(str))
    {
        write("You squeeze the eric the half herring.\n");
        say(QCTNAME(TP) + " squeezes eric the half herring.\n");
        tell_room(environment(TP), "Eric the half herring " +
            "angrily squeaks out 'Ni!' in response to the " +
            "rude fondling.\n");
        return 1;
    }
}

public int
do_slap(string str)
{
    object *target;

    if (!str || !strlen(str))
        return 0;

    target = FIND_STR_IN_OBJECT(str, environment(TP));

    if (!sizeof(target))
        return 0;

    write("You do a silly little dance step backwards, " +
        "then dance towards " +
        target[0]->query_the_name(TP) +
        " and slap him with Eric the half herring!\n");
    target[0]->catch_msg(QCTNAME(TP) + " does a silly " +
        "little dance step backwards, then danced back " +
        "towards you and slaps you with Eric the half " +
        "herring!\n");
    tell_room(environment(TP), QCTNAME(TP) + " does a " +
        "silly little dance step backwards, then dances " +
        "towards " + QTNAME(target[0]) + " and slaps " +
        target[0]->query_objective() + " with Eric " +
        "the half herring!\n", ({TP, target[0]}));
    target[0]->add_prop("_been_eric_slapped",
        target[0]->query_prop("_been_eric_slapped") + 1);

    if (target[0]->query_prop("_been_eric_slapped") > random(3))
    {
        write("Unfortunately, " + target[0]->query_the_name(TP) +
            " seems to have had enough, and knocks you senseless " +
            "with Bruce the Halibut.\n");
        target[0]->catch_msg("Having had enough, you whip out " +
            "Bruce the Halibut and knock " + QTNAME(TP) + 
            " senseless with it!\n");
        tell_room(environment(TP), QCTNAME(target[0]) + " seems " +
            "to have had enough, and knocks " + QTNAME(TP) + 
            " senseless with Bruce the Halibut.\n", ({TP, target[0]}));
        target[0]->remove_prop("_been_eric_slapped");
    }
    return 1;
}

public void
init()
{
    ::init();
    add_action(do_squeeze, "squeeze");
    add_action(do_slap, "slap");
}

public int
remove_object()
{
    if (living(environment()))
    {
        tell_room(environment(environment()), "Eric the " +
            "half herring shouts: Help, Help, I'm being repressed!\n");
    }
    else
        tell_room(environment(), "Eric the half herring shouts: " +
            "Help, Help, I'm being repressed!\n");

    return ::remove_object();
}
