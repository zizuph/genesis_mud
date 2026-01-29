#pragma strict_types

inherit "/cmd/std/command_driver";

#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <cmdparse.h>
#include <language.h>
#include <composite.h>
#include <options.h>
#include <std.h>
#include <filter_funs.h>
#include "/d/Khalakhor/sys/defs.h"

#define SOULDESC(x) (this_player()->add_prop(LIVE_S_SOULEXTRA, x))

/*
 * Function name: get_soul_id
 * Description  : Returns the id string for this cmdsoul
 * Arguments    : n/a
 * Returns      : "Blademasters"
 */
public string
get_soul_id()
{
    return "Pythonclub";
}

/*
 * Function name: query_cmd_soul
 * Description  : Identifies this object as a cmdsoul.
 * Arguments    : n/a
 * Returns      : 1
 */
int
query_cmd_soul()
{
    seteuid(getuid());
    return 1;
}

public int
do_sillywalk(string str)
{
    switch(random(3))
    {
        case 0:
            write("You being wandering around the room " +
                "as if one leg were a foot longer than the " +
                "other, staggering in aimless circles.\n");
            tell_room(environment(TP), QCTNAME(TP) + " begins " +
                "wandering around the room as if one leg were " +
                "one foot longer than the other, staggering " +
                "about in aimless circles.\n", TP);
            return 1;
        case 1:
            write("You begin walking noplace in particular, " +
                "attempting to walk by stepping over your " +
                "own shoulders.\n");
            tell_room(environment(TP), QCTNAME(TP) + " begins " +
                "walking noplace in particular, attempting to " +
                "walk by stepping over " + TP->query_possessive() +
                " shoulders, it seems.\n", TP);
            return 1;
        case 2:
            write("You begin walking around, but you seem unable " +
                "to move anything higher than your ankle, and " +
                "wobble around like a penguin.\n");
            tell_room(environment(TP), QCTNAME(TP) + " begins " +
                "walking around, but seems to be unable to move " +
                "anything but " + TP->query_possessive() + " toes, " +
                "and wobbles about much like a drunken penguin.\n", TP);
            return 1;
    }

    return 0;
}

int
do_begperil(string str)
{
    object *who;
    NF("Beg who for peril?\n");
    if (!str || str == "")
        return 0;
    
    who = parse_this(str, " %l");
    if (!sizeof(who)) 
        return 0;
    
    actor("You beg",who,": Oh please, just a little bit of peril?");
    target(" begs you: Oh please, just a little bit of peril?",who);
    all2actbb(" begs",who,": Oh please, just a little bit of peril?");
    return 1;
}

int
do_giveherring(string str)
{
    object *who;
    NF("Give a herring to who?\n");
    if (!str || str == "")
        return 0;
    
    who = parse_this(str, " %l");
    if (!sizeof(who)) 
        return 0;
    
    if (sizeof(who) > 1)
    {
        NF("You can only give a herring to one person at a time.\n");
        return 0;
    }

    actor("You challenge",who,": You must cut down the mightiest " +
        "tree in the forest with...a herring!");
    target(" challenges you: You must cut down the mightiest tree " +
        "in the forest with...a herring!",who);
    all2actbb(" challenges",who,": You must cut down the mightiest " +
        "tree in the forest with...a herring!");
    tell_room(environment(TP), "You hear a dramatic chord of music!\n");
    setuid(); seteuid(getuid());
    clone_object("/d/Khalakhor/khail/pythonclub/herring")->move(TP);
    TP->command("give herring to " + OB_NAME(who[0]));
    return 1;
}

public int
do_lumberjack(string str)
{
    object singer;

    NF("Lumberjack what? Start, stop, or join?\n");

    if (!str || !strlen(str))
        return 0;

    if (str == "start");
    {
        setuid(); seteuid(getuid());
        singer = clone_object("/d/Khalakhor/khail/pythonclub/lumberjack");
        singer->move(environment(TP));
        singer->start_singing(TP);
        return 1;
    }

    if (str == "stop");
    {
        present("_lumberjack_singer", environment(TP))->stop_singing(TP);
        return 1;
    }

    if (str == "join")
    {
        present("_lumberjack_singer", environment(TP))->add_singer(TP);
        return 1;
    }
    return 0;
}

public int
do_squash(string str)
{
    object to_squash;

    NF("Squash what?\n");
    if (!str || !strlen(str))
        return 0;

    if (!objectp(to_squash = present(str, environment(TP))))
        return 0;

    write("You summon the giant foot! It descends from the sky, " +
        "and squashes the " + to_squash->short() + " out of " +
        "existance!\n");
    tell_room(environment(TP), QCTNAME(TP) + " screams 'Ni!' and " +
        "points at the " + to_squash->short() + ". A massive foot, " +
        "oddly seeming to have only two dimensions, descends from " +
        "the sky and squashes it out of existance!\n", TP);
    to_squash->remove_object();
    return 1;
}
/*
 * Function name: query_cmdlist
 * Description  : Returns a mapping of all the commands provided
 *                by this soul.
 * Arguments    : n/a
 * Returns      : As described above.
 */       
public mapping
query_cmdlist()
{
    return ([
        "sillywalk"    : "do_sillywalk",
        "begperil"     : "do_begperil",
        "giveherring"  : "do_giveherring",
        "lumberjack"   : "do_lumberjack",
        "squash"       : "do_squash",
        ]);
}
