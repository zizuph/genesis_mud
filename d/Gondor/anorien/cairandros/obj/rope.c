/*
 * /d/Gondor/anorien/cairandros/obj/knotrope.c
 *
 * A knotted piece of rope. Will someone ask the right
 * NPC about it?
 *
 *   Varian - April 2020
 */

#pragma strict_types

#include "../../defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/std/object";

int do_untie(string str);

public void
create_object() 
{
    set_name("rope");
    add_adj( ({"knotted", "hemp"}) );

    set_short("knotted rope");
    set_long("This is a length of hemp rope with some very " +
    	"tight knots tied into it. It looks like someone " +
    	"has been trying to untie it without any success.\n");
}

public int
do_untie(string str)
{

    if (!str || !strlen(str)) 
    {
        notify_fail("Untie what? The rope?\n");
        return 0;
    }

    if (!id(str))
    {
        notify_fail("Untie what? The rope?\n");
        return 0;
    }

    if(environment(this_object()) == this_player())
    {
        write("You do your best to work the knots loose so that " +
        	"you can untie the rope, but you don't have much " +
        	"success unfortunately. Maybe next time.\n");
        SAYBB(" tries to untie a knotted length of rope.");
        return 1;
    }

    if(environment(this_object()) != this_player())
    {
        this_player()->catch_tell("You don't have any rope " +
        	"in your possession.\n");
        return 1;
    }

    notify_fail("Unfortunately, you were unable to untie the " +
    	"rope.\n");
    return 0;
}

public void
init()
{
    ::init();
    add_action("do_untie", "untie");
}