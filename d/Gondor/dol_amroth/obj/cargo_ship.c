/* -*- Mode: C -*-
 *
 * obj/cargo_ship.c
 *
 * By Skippern 20(c)01
 *
 * A ship object to be seen in the room, this ship should add the board and
 * enter commands, and move the players to the deck of a cargo ship.
 */
inherit "/std/object";

#include "../defs.h"
#include <language.h>
#include <macros.h>
#include <stdproperties.h>

/* Global variables */
       string       Short, Long, Dest;

/* Prototypes */
       int          enter(string str);

void set_short_desc(string a) { Short = a; }
void set_long_desc(string a) { Long = a; }
void set_dest(string a) { Dest = a; }
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
    add_action(enter, "enter");
    add_action(enter, "board");
}

int
enter(string str)
{
    write("You enter the "+Short+".\n");
    say(QCTNAME(this_player()) + " enters the "+Short+".\n");
    this_player()->move_living("M", Dest, 0, 0);
    say(QCTNAME(this_player()) + " arrives.\n");
    return 1;

    notify_fail("A sailor prevents you from entering the ship.\n");
    return 0;
}



