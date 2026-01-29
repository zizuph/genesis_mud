/*
 * Copyright notice, please read.
 *
 * Copyright Chalmers Datorf|rening, 1992
 *
 * You are welcome to read this file for information & education purposes.
 * However, you are expressly forbidden to copy this code for use in any
 * other mud. This code is part of Genesis and we want Genesis to remain
 * unique. You must invent your own world on your own mud.
 *
 */

#pragma save_binary

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>

#include "defs.h"

#define BLOB_SUBLOC	"_dwarf_start_blob"
#define DROP_TIME	50.0

void
create_object()
{
    set_name("blob");
    set_adj(({"stinking", "yucky", "gooey"}));
    set_long("A stinking yucky gooey blob, godsnot probably.\n");
    set_no_show();

    add_prop(OBJ_M_NO_DROP, "The blob is very sticky and hard to get a grip on.\n");
    add_prop(OBJ_M_NO_GET, "The blob is very sticky and hard to get a grip on.\n");
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 20);
}

void
get_rid_of_blob(int left)
{
    if (--left > 0)
        set_alarm(DROP_TIME, 0.0, &get_rid_of_blob(left));
    else
        remove_object();

    write("A small part of the gooey blob drops off.\n");
    say("A gooey blob drops from " + QTNAME(TP) + ".\n");
}

void
enter_env(mixed env, object old)
{
    TP->add_subloc(BLOB_SUBLOC, TO);
    set_alarm(DROP_TIME, 0.0, &get_rid_of_blob(10));
}

void
leave_env(object from, object to)
{
    TP->remove_subloc(BLOB_SUBLOC);
}

string
show_subloc(string subloc, object on, object for_obj)
{
    string data;

    if (for_obj == on)
        data = "You have ";
    else
        data = capitalize(environment(TO)->query_pronoun()) + " has ";

    data += "a stinking yucky gooey blob smeared all over ";

    if (for_obj == on)
        data += "your face.\n";
    else
        data += environment(TO)->query_possessive() + " face.\n";

    return data;
}

