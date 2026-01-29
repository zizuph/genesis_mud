/*
 * cas_t14.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/*  Ged & Gresolle */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"
#include <macros.h>

int grating;

void reset_room();

string
gratdesc()
{
    string s;

    s = "An old iron grating, covering a hole in the floor. Although " +
            "it is very rusty, it looks really sturdy.\n";

    if (grating)
        s += "It is open.\n";
    else
        s += "It is closed.\n";

    return s;
}

string
opengrating()
{
    if (MAL("guard"))
        return "The guard won't let you!\n";

    if (grating)
        return "But it is already open...\n";

    if (!present("gratingkey_cadu", TP))
        return "The grating is locked, get the key first.\n";

    TP->catch_msg("You open the grating and reveal the dark hole below.\n");
    say(QCTNAME(TP) + " opens the grating.\n");

    grating = 1;
    return "";
}

string
closegrating()
{
    tell_room(TO, "The grating slams shut.\n");
    grating = 0;
    return "";
}

void
create_room()
{
    set_short("Tower of the castle");
    set_long("You are in the southeast tower of the Castle in Cadu.\n" +
             "Its circular walls are stained with blood from many battles. " +
             "There is a small window in the wall, leading to the outside. " +
             "Right under your feet is an old rusty iron grating leading " +
             "down into a black hole.\n");

    add_item("window", "You can look through it.\n");
    add_cmd_item(({"window", "through window"}), "look",
                 "You see a small road leading towards the wilderness.\n");

    add_item("grating", "@@gratdesc");
    add_cmd_item("grating", "open", "@@opengrating");
    add_cmd_item("grating", "close", "@@closegrating");
    add_cmd_item("grate", "open", "@@opengrating");

    add_exit("cas_a12", "northwest");
    add_exit("cas_dung1", "down", "@@block", 1, 1);
    INSIDE;
    reset_room();
}

int
block()
{
    if (!grating)
    {
        TP->catch_msg("You try to drive your skull through the grating but fail.\n");
        return 1;
    }
    if (TP->query_invis())
        return 0;

    if (!MAL("guard"))
        return 0;

    TP->catch_msg("The guard stops you!\n");
    say(QCTNAME(TP) + " tries to go down, but is stopped by the guard.\n");
    return 1;
}

void
reset_room()
{
    if (MAL("guard"))
        return;

    clone_object(ROKEDIR + "npc/towerg1")->move(TO);
    tell_room(TO, "The tower guard arrives.\n");
    grating = 0;                /* closed */
}
