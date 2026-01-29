/*
 * earthroom.c
 * FIXA
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <language.h>

static string *room_walls;
static string *cmd_walls;
static string *efunc_walls;
static string *tired_walls;
static string *dig_desc;

varargs int
add_wall(string place, string cmd, mixed efunc = 0, mixed tired = 0)
{
    if (query_prop(ROOM_I_NO_EXTRA_EXIT))
        return 0;

    if (pointerp(room_walls))
    {
        room_walls = room_walls + ({place});
        cmd_walls += ({cmd});
        efunc_walls += ({efunc});
    }
    else
    {
        room_walls = ({place});
        cmd_walls = ({cmd});
        efunc_walls = ({efunc});
    }
    if (!pointerp(tired_walls))
        tired_walls = ({});
    if (tired)
        tired_walls += ({tired});
    else
        tired_walls += ({1});         /* Standard cost for walking. */

    return 1;
}

string
opposite(string s)
{
    if (s == "east")
        return "west";
    if (s == "west")
        return "east";
    if (s == "north")
        return "south";
    if (s == "south")
        return "north";
    if (s == "down")
        return "up";
    if (s == "up")
        return "down";
}

int
do_dig(string direct, int how, int i)
{
    int index;

    NF("You poke in the ground with the shovel. Not very amusing though.\n");
    if (how)
        return 0;

    NF("You can't dig in that direction!\n");
    if (!room_walls)
        return 0;

    if ((index = member_array(direct, cmd_walls)) < 0)
        return 0;

    if (!i)
    {
        TP->catch_msg("You dig " + direct +
                      " and create a passage in that direction.\n");
        say(QCTNAME(TP) + " digs " + direct +
            " and creates a passage in that direction.\n");
    }
    else
        tell_room(TO, "Someone digs through the " + direct +
                  " wall from the other side.\n");

    add_exit(room_walls[index], cmd_walls[index], efunc_walls[index],
             tired_walls[index]);

    if (!i)
        room_walls[index]->do_dig(opposite(direct), 0, 1);

    cmd_walls = exclude_array(cmd_walls, index, index);
    room_walls = exclude_array(room_walls, index, index);
    efunc_walls = exclude_array(efunc_walls, index, index);
    tired_walls = exclude_array(tired_walls, index, index);

    if (pointerp(dig_desc))
        dig_desc += ({direct});
    else
        dig_desc = ({direct});

    return 1;
}

int
ddo_exa(string s)
{
    string what, where;

    NF("exa what?\n");
    if (!parse_command(s, TO, "%w %w", where, what))
        return 0;

    if (what == "wall")
    {
        if (member_array(where, dig_desc) > -1)
        {
            TP->catch_msg("Someone has dug a hole in it.\n");
            return 1;
        }
        else if (member_array(where, cmd_walls) > -1)
        {
            TP->catch_msg("It looks soft and diggable.\n");
            return 1;
        }
        TP->catch_msg("It looks rather hard.\n");
        return 1;
    }
    if (what == "hole")
        if (member_array(where, dig_desc) > -1)
        {
            TP->catch_msg("It is a rather large hole, which looks about your size.\n");
            return 1;
        }
        else
        {
            TP->catch_msg("That hole exists only in your imagination!\n");
            return 1;
        }
    NF("Exa what?\n");
}

void
create_earthroom()
{
}

string
long(string str, object for_obj)
{
    string s;
    int i, j;

    if (str)
        return ::long (str, for_obj);

    s = ::long();

    j = sizeof(dig_desc);

    if (!j)
        return s;

    if (j == 1)
        return s + "Someone has dug a hole leading " + dig_desc[0] + ".\n";

    s += "Someone has dug " + LANG_WNUM(j) + " holes leading ";

    for (i = 0; i < j - 1; i++)
    {
        s += dig_desc[i];
        if (i != j - 2)
            s += ", ";
    }
    s += " and " + dig_desc[j - 1] + ".\n";

    return s;
}

string
ch()
{
    if (sizeof(dig_desc))
        return "They are fairly large, and most likely enterable.\n";
    return "What holes?\n";
}

nomask void
create_room()
{
    set_long("In a small hole in the ground.\n");
    set_short("dirty hole");

    set_noshow_obvious(1);

    add_item("walls", "The walls look rather interesting.\n");
    add_item("holes", "@@ch");

    create_earthroom();

    add_prop(ROOM_I_DIG_FUN, "do_dig");
    INSIDE;
}

void
init()
{
    ::init();

    add_action("ddo_exa", "exa", 1);
    add_action("digdig", "dig");
}

int
digdig()
{
    notify_fail("It is a lot easier to use a shovel for digging.\n");
    return 0;
}
