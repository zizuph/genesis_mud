/* 
 * /d/Ansalon/guild/society/obj/ball.c
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
 * Coloured ball for Kendermore, Gwyneth, June 1999 
 *
 * Gwyneth, 1999
 */
inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>

/* Randomizes the ball colour */
string *colour=({"red", "orange", "yellow", "green", "blue", "purple"});

string
toss_ball()
{
    write("You toss the " + short() + " high in the air, catching it as " + 
        "it falls back down to the ground.\n");
    say(QCTNAME(this_player()) + " tosses the " + short() + " high into " +
        "the air, catching it as it falls back down to the ground.\n");
    return "";
}

string
roll_ball()
{
    write("You roll the " + short() + " around on the ground.\n");
    say(QCTNAME(this_player()) + " rolls the " + short() + " around on " +
        "the ground.\n");
    return "";
}

string
bounce_ball()
{
    write("You bounce the " + short() + " on the ground.\n");
    say(QCTNAME(this_player()) + " bounces the " + short()+ " on the " +
        "ground.\n");
    return "";
}
void
create_object()
{
    string adj = colour[random(6)];

    set_name("ball");
    add_name("junk");
    add_pname("junks");
    set_adj(adj);
    set_short("bright " + adj + " ball");
    set_long("It's a brightly coloured ball. It looks fun to play with! " + 
        "You could roll it on the ground, bounce it or toss it in the air.\n");
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 15);
    add_cmd_item("ball", "toss", &toss_ball());
    add_cmd_item("ball", "roll", &roll_ball());
    add_cmd_item("ball", "bounce", &bounce_ball());
}

