/*
 * wasp_nest.c
 *
 * Created with help by a doggystick.c from Roke
 * by Ibun
 *
 *
 */

#pragma save_binary
#pragma strict_types
#include "/d/Avenir/common/common.h"

inherit "/std/object";

#include "../defs.h"
#include <cmdparse.h>
#include <macros.h>
#include <composite.h>

int destroy_nest(object victims);
int show_nest(string str);
int scare_bull(object obj);


void
create_object()
{
    set_short("wasp nest");
    set_name("nest");
    add_name("wasp nest");
    set_long("This is a large and very fragile wasp nest that seems to " +
        "collapse any minute in your hands. When you examine it closer, " +
        "you notice some wasps moving inside the hole in the bottom.\n");
    add_prop("_wasp_nest", 1);
}


mixed
hurl_at(string s)
{
    mixed   victims;

    NF("Throw what at whom?\n");
    if (!s || s == "")
        return 0;

    if (!parse_command(s, ENV(TP), "'nest' 'at' %l", victims))
        return 0;

    if (!sizeof(victims = NORMAL_ACCESS(victims, 0, 0) - ({ TP })))
    {
        return 0;
    }

    victims = victims[0];

    TP->catch_msg("You throw the nest at " +COMPOSITE_LIVE(victims)+ ".\n");
    tell_room(ENV(TP), QCTNAME(TP) + " throws a wasp nest at the " +
        victims->short()+ ".\n", ({victims, TP}));
    victims->catch_msg(QCTNAME(TP) + " throws a large wasp nest at you!\n");
    set_alarm(3.0, 0.0, &destroy_nest(victims));
    return 1;

}

void
init()
{
    ::init();
    add_action("hurl_at", "throw");
    add_action("hurl_at", "hurl");
    add_action("show_nest","show");
}

int
destroy_nest(object victims)
{
    object bull;

    tell_room(ENV(TO), "The nest falls apart and some wasps fly out.\n");

    if (victims->id("_bull"))
    {
        tell_room(ENV(TO), "The wasps flies up to the bull and " +
            "stings him.\n");
        victims->panic();
    }
    remove_object();
}

int
show_nest(string str)
{
object bull;

    if (!str)
        return 0;

    if ((str == "nest at bull") || (str == "nest to bull") || (str == "nest"))
    {
        bull = (present("_bull", ENV(ENV(TO))));
        if (bull)
        {
            say(QCTNAME(TP) + " shows a wasp nest in the " +
                "air.\n");
            set_alarm(1.0, 0.0, &scare_bull(bull));
            return 1;
        }
        return 0;
    }
    return 0;
}

int
scare_bull(object bull)
{
    bull->scared_bull();
}
