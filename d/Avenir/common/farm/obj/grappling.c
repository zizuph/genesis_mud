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
int is_tied = 0;  // A chain is secured to the grappling if 1.

void
create_object()
{

    set_short("small grappling iron");
    set_long("@@long_desc");
    add_name("grappling");
    add_name("iron");
    add_prop(OBJ_I_VOLUME, 5000);  // Five cubic decimeter
    add_prop(OBJ_I_WEIGHT, 1000);    // Grappling weights 10 Kg
    setuid();
    seteuid(getuid());
}

string
long_desc()
{
string text;

text = "This is a small grappling iron used to anchor " +
             "smaller boats in shallow waters.";
    if (is_tied)
        text += " A long iron chain is secured to the " +
            "grappling, making it ready to use.";
    text += "\n";
    return text;
}

void
tie_chain()
{
    // set_no_show_composite(1);
    is_tied = 1;
    add_prop(OBJ_I_VOLUME, 15000);
    add_prop(OBJ_I_WEIGHT, 3000);    // Grappling weights 30 Kg with chain
}

int
query_tied()
{
    return is_tied;
}
