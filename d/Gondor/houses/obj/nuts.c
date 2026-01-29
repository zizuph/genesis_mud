/*
 * OBJ + nuts.c
 *
 * Varian - Jan 2020
 */

#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <files.h>
#include "/d/Gondor/met_defs.h"
#include "/d/Gondor/defs.h"
#include "defs.h"

inherit "/std/food";

int do_pop(string str);
int do_munch(string str);

void
create_food() 
{
    set_name("bowl_of_nuts");
    add_name( ({"nuts", "nut", "bowl", "nut bowl", "bowl of nuts"}) );
    set_short("nut bowl");
    set_adj("nut");
    set_long("This is a bowl full of different types of nuts. " +
    	"It looks like a wonderful snack to munch on at home " +
    	"or to carry with you on the road. If you are feeling " +
    	"bored, you could always pop some nuts into your mouth.\n");

    set_amount(50);
    add_prop(OBJ_I_WEIGHT, 75);
    add_prop(OBJ_I_VOLUME, 90);
    add_prop(OBJ_I_VALUE, 35);
}

init()
{
    ::init();
    add_action("do_pop","pop");
    add_action("do_munch","munch");
}

int
do_pop(string str)
{

    if (!str || !strlen(str)) 
    {
        notify_fail("Pop what?\n");
        return 0;
    }

    if (!id(str))
    {
        notify_fail("Pop what?\n");
        return 0;
    }

    if(environment(this_object()) == this_player())
    {
        write("Grabbing a handful of nuts from your bowl, you eat them " +
    	    "one at a time by casually throwing them up in the air " +
    	    "and catching them with your mouth.\n");
        SAYBB(" tosses a nut into the air and catches it in their mouth.");
        return 1;
    }

    if(environment(this_object()) != this_player())
    {
        this_player()->catch_tell("But... you don't have anything to pop?\n");
        return 1;
    }

    notify_fail("Sadly, you failed to pop a nut.\n");
    return 0;
}

int
do_munch(string str)
{

    if (!str || !strlen(str)) 
    {
        notify_fail("Munch what?\n");
        return 0;
    }

    if (!id(str)) 
    {
        notify_fail("Munch what?\n");
        return 0;
    }

    if(environment(this_object()) == this_player())
    {
    write("Feeling a need to snack, you grab your bowl of nuts " +
    	"and start munching constantly on them until you " +
    	"suddenly notice the bowl is empty and your snack is " +
    	"finished!\n");
    SAYBB(" greedily starts munching on a bowl of nuts.");
    this_player()->command("eat bowl_of_nuts");
    write("you toss away the empty bowl.\n");
    return 1;
    }

    if(environment(this_object()) != this_player())
    {
        this_player()->catch_tell("You don't have any nuts " +
            "to munch on right now.\n");
        return 1;
    }

    notify_fail("You are not able to munch anything at this time.\n");
    return 0;
}