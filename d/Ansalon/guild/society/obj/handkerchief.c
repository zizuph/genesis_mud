/* 
 * /d/Ansalon/guild/society/obj/handkerchief.c
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
 * Handkerchief for Kender
 * 
 * Gwyneth, June 1999
 */
inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>

int nose_blown;

void
create_object()
{
    set_name("handkerchief");
    add_name("kerchief");
    add_name("junk");
    add_pname("junks");
    set_adj("soft");
    add_adj("white");
    set_short("soft white handkerchief");
    set_long("This is a soft white handkerchief with flowers stitched " + 
        "onto the edges. @@clean_desc@@\n");
    remove_prop(OBJ_I_VALUE);
    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_I_VOLUME, 20);
    add_cmd_item("nose", "blow", "@@blow_nose");
    nose_blown = 0;
}

string
blow_nose(string str)
{
    if ((!strlen(str)) || (str == "on handkerchief"))
    {
        write("You bring the soft white handkerchief to your face and blow " + 
            "your nose into it.\n");
        say(QCTNAME(this_player()) + " brings the soft white handkerchief to " + 
            this_player()->query_possessive() + " face and blows " + 
            this_player()->query_possessive() + " nose into it.\n");
        nose_blown = 1;
        return "";
    }

    notify_fail("Blow your nose on what?\n");
}

clean_desc()
{
    if (nose_blown)
        return "It looks a bit used.";
    else
        return "It looks clean.";
}

string
query_recover()
{
    return 0;
}

