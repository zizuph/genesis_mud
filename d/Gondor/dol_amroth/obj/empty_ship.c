/* -*- Mode: C -*-
 *
 * obj/empty_ship.c
 *
 * By Skippern 20(c)01
 *
 * A ship object to be seen in the room, this ship should add the board and
 * enter commands, but reject the players from entering the ships.
 */
inherit "/std/object";

#include "../defs.h"
#include <language.h>
#include <macros.h>
#include <stdproperties.h>

/* Global variables */
       string       Short, Long;

/* Prototypes */
       int          no_enter(string str);

void set_short_desc(string a) { Short = a; }
void set_long_desc(string a) { Long = a; }
string query_long() { return Long; }
string query_short() { return Short; }

string
short_desc()
{
    return Short;
}

string
long_desc()
{
    return CAP(Short) + ". " + Long + "\n";
}

/*
 * Function name:    create_object()
 * Description  :    Creates the object.
 */
public void
create_object()
{
    set_short(&short_desc());
    set_long(&long_desc());

    add_prop(OBJ_I_NO_GET, 1);

}

init()
{
    ::init();
    add_action(no_enter, "enter");
    add_action(no_enter, "board");
}

int
no_enter(string str)
{
    notify_fail("A sailor prevents you from entering the ship.\n");
    return 0;
}
