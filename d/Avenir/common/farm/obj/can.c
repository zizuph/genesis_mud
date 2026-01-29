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

inherit "/std/container";

int dung = 0;

void
create_container()
{

    set_short("small metal can");
    add_name("can");
    add_name("_can");
    set_long("@@desc_long");
    add_prop(CONT_I_MAX_VOLUME, 1000); // One litre
    add_prop(CONT_I_MAX_WEIGHT, 2000); // Two Kg
    add_prop(CONT_I_WEIGHT, 50);       // Bucket weights 50 g
    add_prop(CONT_I_VOLUME, 50);       // Volume of the metal = 50ml
    add_prop(CONT_I_RIGID, 1);         // Fixed size
    add_prop(CONT_I_TRANSP, 0);        // Opaque
    setuid();
    seteuid(getuid());
}


void
enter_inv(object obj, object from)
{
    if (obj->id("_maggot") && obj->query_kill_id())
    {
        obj->remove_kill();
    }
}

void
leave_inv(object obj, object to)
{
    if (obj->id("_maggot"))
    {
        obj->kill_maggot();
    }
}


string
desc_long()
{
    string text;

    text = "This is a small metal can. Its hard to see " +
        "what it was used for.";

    if (dung)
        text+= " Right now the can is filled with horsedung. " +
            "Obviously someone likes to fish and wants to " +
            "keep his or her maggots alive inside the can.";
    else
        text+= " You try to smell inside " +
        "but you fail to detect any smell at all. The sharp " +
        "edges of the lid might hurt anyone who isnt " +
        "careful, but as the lid has been folded back, " +
        "it looks safe to keep the can for later use.";

    text+="\n";
    return text;
}

int
add_dung()
{
    dung = 1;
}

int
query_dung()
{
    return dung;
}
