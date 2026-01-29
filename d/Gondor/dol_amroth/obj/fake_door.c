/* -*- Mode: C -*-
 * obj/fake_door.c
 *
 * By Skippern 20(c)01
 *
 * A fake door to look just like a door but rejects being picked or opened.
 */
inherit "/std/object";

#include "../defs.h"
#include <language.h>
#include <macros.h>
#include <stdproperties.h>

/* Global variables */
       string       Short, Long, NoPick, OtherSide;

/* Prototypes */
       int          no_pick(string str);

void set_short_desc(string a)      { Short = a; }
void set_long_desc(string a)       { Long = a; }
void set_no_pick_reason(string a)  { NoPick = a; }
void set_other_side(string a)      { OtherSide = a; }
string query_long()                { return Long; }
string query_short()               { return Short; }
string query_no_pick_reason()      { return NoPick; }
string query_other_side()          { return OtherSide; }

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
    add_action(do_verb, "open");
    add_action(do_verb, "knock");
    add_action(do_verb, "close");
    add_action(do_verb, "lock");
    add_action(do_verb, "unlock");
    add_action(no_pick, "pick");
}

int
no_pick(string str)
{
    notify_fail("A sailor prevents you from entering the ship.\n");
    return 0;
}

int
do_verb(string str)
{
    notify_fail("Pick what?\n");
    if (str == "lock")
        notify_fail(NoPick);
    return 0;
}
