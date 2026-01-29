/*
 * snail.c
 *
 * Used in wild/f5.c wild/fh.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/food";

#include "defs.h"

#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>

void
create_food()
{
    set_name("snail");
    set_short("wet snail");
    set_adj("wet");

    set_long("This snail is grey, with a bluish shell. It looks " +
             "quite edible. Perhaps you would like to eat it and try some " +
             "escargot?\n");

    add_prop(OBJ_I_WEIGHT, 3);
    add_prop(OBJ_I_VOLUME, 3);

}

void
init()
{
    ::init();
    add_action("kill", "kill");
    add_action("catch_me", "catch");
}

int
catch_me(string s)
{
    return TP->command("$get " + s);
}

int
kill(string s)
{
    NF("Kill what?\n");
    if (s != "snail")
        return 0;

    write("You crush the snail with your right foot!\n");
    say(QCTNAME(TP) + " crushes the snail with " +
        TP->query_possessive() + " right foot!\n");

    remove_object();
    return 1;
}
