#pragma strict_types
#include "/d/Avenir/common/common.h"
#include "../defs.h"
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>
#include <language.h>
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>
#include <terrain.h>

inherit "/std/object";


object *victims;

void
create_object()
{

    set_short("table cloth");
    add_name("cloth");
    add_name("_red_cloth");
    add_adj("red");
    set_long("This is a red table cloth, probably used during a " +
             "big fiesta considering all the stains on it.\n");
}

void
init()
{
    ::init();
        add_action("wave_cloth","wave");
        add_action("wave_cloth","shake");

}

int
wave_cloth(string str)
{
    string player, command;
    object bull;
    int counter, diff, prop, tid;

    NF("Wave what at whom?\n");
    if (!str || str == "")
        return 0;
    if (TP->query_prop("_prevent_wave_cloth"))
    {
         tid = time();
         prop = (TP->query_prop("_prevent_wave_cloth"));
        diff = (tid - prop);
        if ((diff) < 7)
        {
            write("You wave the cloth again, but doing it " +
                "so soon after the last try makes you stop " +
              "and concentrate a bit more.\n");
            return 1;
        }
    }
    if ((str == "cloth") || (str == "table cloth"))
    {
        write("You wave the cloth at no one in particular.\n");
        if (present("_bull", ENV(TP)))
        {
            bull = present("_bull", ENV(TP));
            if (bull)
                bull->react_cloth(TP);
        }
        say(QCTNAME(TP) + " waves the " + str + " in the " +
            "air.\n");
        return 1;
    }

    if (!parse_command(str, ENV(TP), "'cloth' 'at' %l", victims))
        return 0;

    victims -= ({TP});
    victims = exclude_array(victims, 0, 0);
    TP->catch_msg("You take a stance like a matador and wave the " +
        "red table cloth at " + COMPOSITE_LIVE(victims) + ".\n");
    victims->catch_msg(QCTNAME(TP) + " takes a stance like a " +
        "matador and waves a red table cloth in your direction.\n");
    if (victims->id("_bull"))
    {
        TP->add_prop("_prevent_wave_cloth", time());
        victims->bull1(TP);
        return 1;
    }

}


