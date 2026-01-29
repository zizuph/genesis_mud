#pragma strict_types

inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>      /* All prop definitions */
#include <cmdparse.h>           /* The FIND_STR_IN_OBJECT macro */

#include "defs.h"

string str;
object orc;

void
create_object()
{
    seteuid(getuid());
    set_name("figurine");
    add_name("genfigure");
    set_short("miniature figurine");
    set_long("It is a small broken figurine of a proud "+
             "orc in his youth.\n");
    set_adj("miniature");
    add_adj("broken");
    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 2);
    add_prop(OBJ_I_VALUE, 0);

}

int
smash_figurine(string str)
{
    if ((str == "figurine") || (str == "miniature figurine")){
        write("You viciously smash the figurine into oblivion.\n");
        say(QCTNAME(TP) + " smashes the figurine into many small pices.\n");
        remove_object();
        return 1;
    }
    return 0;
}

int
break_figurine(string str)
{
    if ((str == "figurine") || (str == "miniature figurine")){
        write("You easily break the statue between your fingers.\n");
        say(QCTNAME(TP) + " breaks the figurine in half, destroying it.\n");
        remove_object();
        return 1;
    }
    return 0;
}

void
init()
{
    ::init();

    add_action(smash_figurine,"smash");
    add_action(break_figurine,"break");
}

