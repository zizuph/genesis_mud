/*
 * fishingnet.c
 *
 * Used in nyreese/cadu_h2.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include "defs.h"
#include <stdproperties.h>
#include <macros.h>

int
examine(string str)
{
    if ((str != "net") && (str != "fishing net"))
        return 0;

    if (TP->query_stat(0) > 12)
    { /* check player's strength */

        if (query_prop(428))
        {
            TP->catch_msg("You find nothing in the net.\n");
            say(QCTNAME(TP) + " searches a fishing net but finds nothing.\n");
    
            return 1;
        } 
        TP->catch_msg("When you search the net you find a small leather " + 
                      "pouch. You take it and hide it quickly in your " +
                      "pocket.\n");
        say(QCTNAME(TP) + " finds something in the net.\n");
        clone_object(ROKEDIR + "obj/pouch")->move(TP);
        add_prop(428, 1); /* searched */
    } 
    else
    {
        TP->catch_msg("The net is too heavy to be searched.\n");
        say(QCTNAME(TP) + " tries to search the net but fails.\n");
    }
    return 1;
}

void
create_object()
{
    set_name("net");
    set_adj("fishing");
    set_short("fishing net");
    set_long("It's a standard fishing net, used by the fishermen in Cadu.\n");

    add_prop(OBJ_I_VALUE, 200);
    add_prop(OBJ_I_WEIGHT, 35001);
    add_prop(OBJ_I_VOLUME, 10000);
    add_prop(428,0 ); /* not searched */
}

int
fish()
{
    TP->catch_msg("You take a second look at the net and realize that " +
                  "it is too old and tangled to be of any use.\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(examine, "examine"); 
    add_action(examine, "exa"); 
    add_action(fish, "fish");
}
