#pragma save_binary
#pragma strict_types
inherit "/std/object";
#include "/d/Avenir/common/common.h"
#include <config.h>
#include <cmdparse.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>
int tie_chain(string str);

public void
init()
{
    ::init();
    add_action(tie_chain, "tie");
    add_action(tie_chain, "secure");
    add_action(tie_chain, "fasten");
    add_action(tie_chain, "attach");
}

void
create_object()
{
    set_name("chain");
    add_adj("iron");
    set_long("This is a long iron chain. Being made of iron its " +
        "far more slender and graceful than one would expect. " +
        "Perhaps it isnt iron after all, but you cannot really say " +
        "for sure. Right now it has snapped from where it was secured " +
        "in one end, but appart from that it looks to be in a " +
        "good condition.\n");
    add_prop(OBJ_I_WEIGHT, 2000); /* 20 kg */
    add_prop(OBJ_I_VOLUME, 1000); /* 10 l */
    add_prop(OBJ_I_VALUE, 0); /* 0 copper */
}

int
tie_chain(string str)
{
    NF("Secure what to what?\n");
    object *grapplings, grappling;
    if (!str || str == "")
        return 0;

    if ((str == "chain") || (str == "iron chain"))
    {
        write("You try to secure the chain to the open " +
            "air, but fail to find something to secure " +
            "it to.\n");
        return 1;
    }

    if (!parse_command(str, ENV(TP), "'chain' 'to' %i", grapplings))
        return 0;

    if (!sizeof(grapplings = NORMAL_ACCESS(grapplings, 0, 0) - ({ TO })))
        return 0;
 
    grappling = grapplings[0];

    if (grappling->id("grappling"))
    {
         write("You secure the iron chain to the "
             + LANG_THESHORT(grappling) + ".\n");
        say(QCTNAME(TP) + " secure a chain to an iron grappling.\n");
        grappling->tie_chain();
        grappling->remove_prop("_tried_to_anchor");
        remove_object();
        return 1;
    }
    return 0;
}
