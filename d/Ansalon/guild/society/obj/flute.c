/* 
 * /d/Ansalon/guild/society/obj/flute.c
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
 * Flute for Kender  
 *
 * Gwyneth, June 1999 
 */
inherit "/std/object";
#include <macros.h>
#include <stdproperties.h>

public string
play_flute()
{
    say(QCTNAME(this_player()) + " plays a few notes on " + 
        this_player()->query_possessive() + " silver flute.\n"); 
    return ("You play a few notes on your silver flute.\n");
}

public void
create_object()
{
    set_name("flute");
    add_name("junk");
    add_pname("junks");
    set_adj("silver");
    set_short("silver flute");
    set_long("This is a small silver flute with with delicate etchings " + 
        "of vines wrapping themselves around the hollowed out instrument. " + 
        "Small holes have been carefully drilled into the metal, running " + 
        "up the length of the flute. You could try to play a song on the " + 
        "flute.\n");
    remove_prop(OBJ_I_VALUE);
    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 120);
    add_cmd_item(({"song", "flute"}), "play", &play_flute());
}

public string
query_recover()
{
    return 0;
}

