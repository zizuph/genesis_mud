/*
 * /d/Ansalon/guild/society/obj/tester_ring.c
 *
 * Copyright (c) 2001 by Alyssa Hardy
 *
 * Copyright notice, please read.
 *
 * You are welcome to read this file for information & education purposes.
 * However, you are expressly forbidden to copy this code for use in any
 * other mud. This code is part of Genesis and we want Genesis to remain
 * unique. You must invent your own world on your own mud.
 *
 * A ring given as reward to Meercat for excellent work as
 * a guild tester for the Secret Society of Uncle Trapspringer.
 *
 * Coded by Gwyneth on May 6, 2000
 */

inherit "/std/armour";

#include "/d/Ansalon/common/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

void
create_armour()
{
    set_name("ring");
    remove_name("armour");

    set_adj("silver");
    add_adj("dragon");
    add_adj("onyx");

    set_short("silver onyx dragon ring");
    set_pshort("silver onyx dragon rings");

    set_long("This elegantly crafted silver ring has onyx dragons " +
        "circling the outside, entertwining in an intricate dance. " +
        "A feeling of magic eminates from the dragons.\n");

    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_VALUE, 10000);
    add_prop(OBJ_I_VOLUME, 10);
    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_S_WIZINFO, "This ring was made for Meercat for " +
        "excellent work as guild tester of the Secret Society of " +
        "Uncle Trapspringer. It is dropable, but autoloadable. It " +
        "is not to be replaced if lost, unless it is lost by a bug.\n");

    set_at(A_ANY_FINGER);
    set_ac(0);
    set_af(this_object());
}

string
query_recover()
{
    return 0;
}

string
query_auto_load()
{
    if(environment(this_object())->query_real_name() == "meercat")
        return MASTER;
}

mixed
wear(object ob)
{
    if(ob != this_object())
    {
        return 0;
    }

    write("You slip the " + short() + " onto your finger and " +
        "tingle with the feeling of magic.\n");
    say(QCTNAME(this_player()) + " slips the " + short() + " onto " +
        this_player()->query_possessive() + " finger and tingles with " +
        "the feeling of magic.\n");

    add_prop(OBJ_M_NO_DROP, "You must remove the ring first!\n");

    worn = 1;
    return 1;
}

mixed
remove(object ob)
{
    if(ob != this_object())
        return 0;

    write("You slide the " + short() + " off of your finger and " +
        "feel somewhat naked without it.\n");
    say(QCTNAME(this_player()) + " slides the " + short() + " off of " +
        this_player()->query_possessive() + " finger and looks a bit " +
        "downcast.\n");

    remove_prop(OBJ_M_NO_DROP);

    worn = 0;
    return 1;
}

int
twist_ring(string ring)
{
    if(!parse_command(ring, ({}), "[the] [silver] [dragon] 'ring'"))
    {
        return 0;
    }

    write("You twist the silver onyx dragon ring habitually " +
        "between your fingers\n");
    say(QCTNAME(this_player()) + " twists the silver onyx dragon ring " +
        "habitually between " + this_player()->query_possessive() + 
        " fingers.\n");
    return 1;
}

int
trace_ring(string ring)
{
    if(!parse_command(ring, ({}), "[the] [silver] [dragon] 'ring'"))
    {
        return 0;
    }

    write("You trace the onyx dragons on your silver ring " +
        "with awe and excitement at the magic that lies beneath.\n");
    say(QCTNAME(this_player()) + " traces the onyx dragons on " + 
        this_player()->query_possessive() + " silver ring with awe " +
        "and excitement at the magic that lies beneath.\n");
    return 1;
}

public void
init()
{
    ::init();

    add_action("twist_ring", "twist");
    add_action("trace_ring", "trace");
}
