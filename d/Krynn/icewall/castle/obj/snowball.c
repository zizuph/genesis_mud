/*
 * a snowball for lots of fun! 
 * created by Stevenson for Icewall
 */

#include "/d/Krynn/icewall/local.h"
#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>

inherit "/std/object";
inherit "/lib/commands";
inherit PLAINS_O + "icy_objects_base";


void
create_object()
{
    set_name("snowball");
    set_short("snowball");
    set_long("It is a perfectly round snowball, just perfect for throwing.\n");
   
    add_prop(OBJ_I_VOLUME, 50);
    add_prop(OBJ_I_WEIGHT, 100);
    make_me_meltable();
}

int
throw_fun(string arg) {
    object *victim;
   
    notify_fail("Throw what at whom?\n");
    victim = PARSE_THIS(arg, "'snowball' 'at' / 'toward' [the] %l");
    if (!sizeof(victim))
        return 0;
    if (sizeof(victim) > 1)
    {
        notify_fail("Pick one target to throw the snowball at.\n");
        return 0;
    }
   
    if (random(10) > 8)
    {
        actor("You throw a snowball at", victim, " and it wizzes "
            + "past "+OBJECTIVE(victim[0])+".\n");
        target(" throws a snowball at you but it misses.",victim);
        say(QCTNAME(TP)+" throws a big wet snowball at "
            + QTNAME(victim[0])+" but it misses.\n",({victim[0],TP}));
    }
    else
    {
        actor("You throw a snowball at", victim, "'s face.");
        target(" smashes you in your face with a big wet snowball.", victim);
        say(QCTNAME(this_player()) + " throws a big wet snowball at " +
            QTNAME(victim[0]) + "'s face.\n", ({ victim[0], this_player() }));
    }
    this_object()->remove_object();
    return 1;
}

int
drop(string arg)
{
    if (arg == "snowball") {
        write("You drop the snowball and it mysteriously vanishes " +
            "into the air.\n");
        TO->remove_object();
        return 1;
    }

    NF("Drop what?\n");
    return 0;
}

void
init()
{
    add_action(throw_fun, "throw");
    add_action(drop, "drop");
    ::init();
}
