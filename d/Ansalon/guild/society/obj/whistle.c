/* 
 * /d/Ansalon/guild/society/obj/whistle.c 
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
 * Whistle for Kender 
 * Gwyneth, June 1999 
 */
inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>

string
blow_whistle()
{
    write("You puff out your cheeks and blow as hard as you can into " + 
        "the small silver whistle, making " + 
        "a loud piercing trill.\n");
    say(QCTNAME(this_player()) + " puffs out " + 
        this_player()->query_possessive() + " cheeks and blows " + 
        "into the whistle as hard as " + this_player()->query_pronoun() + 
        " can, making a loud piercing trill.\n");
    return "";
}

void
create_object()
{
    set_name("whistle");
    add_name("junk");
    add_pname("junks");
    set_adj("small");
    add_adj("silver");
    set_short("small silver whistle");
    set_long("This is a small silver whistle. It could be very fun to " + 
        "blow!\n");
    remove_prop(OBJ_I_VALUE);                                                  
    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_I_VOLUME, 20);
    add_cmd_item("whistle", "blow", &blow_whistle());
}

string
query_recover()
{
    return 0;
}

