/* 
 * /d/Ansalon/guild/society/obj/pit.c
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
 * Cherry pit from cherries 
 * Gwyneth, September 1999 
 */
inherit "/std/object";

#include <macros.h>
#include <cmdparse.h>
#include <stdproperties.h>

string shoot_pit(string str);

void
create_object()
{
    set_name("pit");
    add_name("junk");
    add_pname("junks");
    set_adj("cherry");
    set_short("cherry pit");
    set_long("This is the pit from a cherry. You could probably shoot it " + 
        "at someone.\n");
    remove_prop(OBJ_I_VALUE);
    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_I_VOLUME, 40);
}

int
shoot_pit(string str)
{
    object *oblist;

    oblist = PARSE_THIS(str, "[pit] [at] %l");

    if (!sizeof(oblist))
    {
        notify_fail("Shoot pit at who?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        notify_fail("You can only shoot at one person at a time.\n");
        return 0;
    }

    if (random(2))
    {
        oblist[0]->catch_tell(this_player()->query_The_name(oblist[0]) + 
            " shoots a cherry pit at your head. It hits, and sticks in " +
            "your hair.\n");
        tell_room(environment(this_player()), QCTNAME(this_player()) + 
            " shoots a cherry pit at " + QTPNAME(oblist[0]) +" head. It " +
            "hits, and sticks in " + oblist[0]->query_possessive() +
            " hair.\n", ({ oblist[0], this_player() }));
        write("You shoot a cherry pit at " + 
            oblist[0]->query_the_possessive_name(this_player()) + " head. " +
            "It hits, and sticks in " + oblist[0]->query_possessive() +
            " hair.\n");
        oblist[0]->add_prop(LIVE_S_EXTRA_SHORT, " with a cherry pit " + 
                "stuck in " + oblist[0]->query_possessive() + " hair");
        set_alarm(0.1, 0.0, &remove_object());
        return 1;
    }
    else
    {
        oblist[0]->catch_tell(this_player()->query_The_name(oblist[0]) + 
            " shoots a cherry pit at your head, but it misses and falls " +
            "to the ground where it rolls out of sight.\n");
        tell_room(environment(this_player()), QCTNAME(this_player()) + 
            " shoots a cherry pit at " + QTPNAME(oblist[0]) +" head, but " +
            "it misses and falls to the ground where it rolls out of " +
            "sight.\n", ({ oblist[0], this_player() }));
        write("You shoot a cherry pit at " + 
            oblist[0]->query_the_possessive_name(this_player()) +
            " head, but it misses and falls to the ground where it " + 
            "rolls out of sight.\n");
        set_alarm(0.1, 0.0, &remove_object());
        return 1;
    }
}

string
query_recover()
{
    return 0;
}

public void
init()
{
    ::init();
    add_action(shoot_pit, "shoot");
}

