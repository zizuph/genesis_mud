/*
 * /d/Ansalon/guild/society/obj/tester_case.c
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
 * A ring given as reward to Belnop for excellent work as
 * a guild tester for the Secret Society of Uncle Trapspringer.
 *
 * Coded by Gwyneth on May 6, 2000
 */
inherit "/std/armour";

#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

void
create_armour()
{
    set_name("case");
    remove_name("armour");

    set_adj("golden");
    add_adj("map");
    add_adj("shiny");

    set_short("shiny golden map case");
    set_pshort("shiny golden map cases");

    set_long("This shiny golden map case is attatched to a small " +
        "leather belt which allows you to wear it around your waist.\n");

    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_VALUE, 1000);
    add_prop(OBJ_I_VOLUME, 10);
    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_S_WIZINFO, "This case was made for Belnop for " +
        "excellent work as guild tester of the Secret Society of " +
        "Uncle Trapspringer. It is dropable, but autoloadable. It " +
        "is not to be replaced if lost, unless it is lost by a bug.\n");

    set_at(A_WAIST);
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
    if(environment(this_object())->query_real_name() == "belnop")
    {
        return MASTER;
    }
}

mixed
wear(object ob)
{
    if(ob != this_object())
    {
        return 0;
    }

    write("You tie the " + short() + " around your waist.\n");
    say(QCTNAME(this_player()) + " ties the " + short() + " around " +
        this_player()->query_possessive() + " waist.\n");

    add_prop(OBJ_M_NO_DROP, "The map case is securely tied around " +
        "your waist. You must remove it first!\n");

    worn = 1;
    return 1;
}

mixed
remove(object ob)
{
    if(ob != this_object())
        return 0;

    write("You untie the " + short() + " from around your waist.\n");
    say(QCTNAME(this_player()) + " unties the " + short() + " from around " +
        this_player()->query_possessive() + " waist.\n");

    remove_prop(OBJ_M_NO_DROP);

    worn = 0;
    return 1;
}

int
scribble()
{
    write("You take out a piece of paper and quill from your map " +
        "case and study your surroundings closely. You furrow your " +
        "brow in concentration as you scribble on the paper.\n");
    say(QCTNAME(this_player()) + " takes out a piece of paper and quill from " +
        this_player()->query_possessive() + " map case and studies " + 
        this_player()->query_possessive() + " surroundings closely. " +
        capitalize(this_player()->query_pronoun()) + " furrows " + 
        this_player()->query_possessive() + " brow in concentration as " + 
        this_player()->query_pronoun() + " scribbles on the paper.\n");
    return 1;
}

int
explain()
{
    write("You get a map from your map case, unroll it on the ground " +
        "and expertly explain how to get to the destination.\n");
    say(QCTNAME(this_player()) + " gets a map from " + 
        this_player()->query_possessive() + " map case, unrolls it on " +
        "the ground and starts to explain in a stream of gibberish how " +
        "to get to the destination.\n");
    return 1;
}

int
drum(string map_case)
{
    if(!parse_command(map_case, ({}), "[the] [shiny [golden] [map] 'case'"))
    {
        return 0;
    }

    write("You start to drum a fast rhythm on your map case " +
        "while singing a merry song.\n");
    say(QCTNAME(this_player()) + " starts to drum a fast rhythm on " +
        this_player()->query_possessive() + " map case while singing a " +
        "merry song.\n");
    return 1;
}

public void
init()
{
    ::init();

    add_action(scribble, "scribble");
    add_action(explain, "explain");
    add_action(drum, "drum");
}
