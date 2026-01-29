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
#pragma strict_binary

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>

#include "../defs.h"

static string owner;	/* The true owner of the note */

public void
create_object()
{
    set_name("note");
    set_adj("small");

    set_long(BS("A small note of low quality paper. There is something written on it in flowering script.\n"));

    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 1);

    owner = "";
}

public int
read_it(string what)
{
    if (what != "note")
	return 0;

    if (owner != TP->query_real_name())
    {
	write("Something is written on the note, only trouble is: you can't read it.\n");
	return 1;
    }

    write("A hard day's work\n\tthat dwarves may ride\n\t\tin caverns cold.\n\nWill truly bring\n\tfor elf so high\n\t\treward of mind.\n\nUpon contemplation\n\tin cleansing waters\n\t\twhen work is done.\n");
    return 1;
}

public void
init()
{
    ::init();
    
    if (ETO == TP)
	add_action(read_it, "read");
}

public void
set_owner(string the_owner)
{
    if (!strlen(owner))
	owner = the_owner;
}

public string
query_owner()
{
    return owner;
}
