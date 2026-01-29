/* 
 * /d/Ansalon/guild/society/obj/marble.c
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
 * Marble for Kender 
 * Gwyneth, June 1999 
 */
inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>

string
shoot_marble()
{
    write("You kneel down and shoot the small agate marble across " + 
        "the floor with your middle finger. You run after it and pick " + 
        "it up again.\n");
    say(QCTNAME(this_player()) + " kneels down and shoots the small " +
        "agate marble across the floor with " + 
        this_player()->query_possessive() + " middle finger. " + 
        capitalize(this_player()->query_pronoun()) + " runs after it " +
        "and picks it up again.\n");
    return "";
}

void
create_object()
{
    set_name("marble");
    add_name("junk");
    add_pname("junks");
    set_adj("small");
    add_adj("agate");
    set_short("small agate marble");
    set_long("This small agate marble is translucent beige with bands " + 
        "of colour running through it. It has a small chip, but is " + 
        "otherwise unflawed.\n");
    remove_prop(OBJ_I_VALUE);
    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_I_VOLUME, 20);
    add_cmd_item("marble", "shoot", &shoot_marble());
}

string
query_recover()
{
    return 0;
}

