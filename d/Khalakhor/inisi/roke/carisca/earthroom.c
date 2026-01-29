/*
 * earthroom.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <filepath.h>

static string *room_walls;
static string *cmd_walls;
static string *efunc_walls;
static string *tired_walls;
static string *dig_desc;

varargs int
add_wall(string place, string cmd, mixed efunc = 0, mixed tired = 0)
{
    string dir;

    if (query_prop(ROOM_I_NO_EXTRA_EXIT))
        return 0;

    /* If the place can consist of only the filename. Then we should add the
     * complete path name from the filename from this room.
     */
    if (stringp(place) &&
	(place[0] != '/') &&
	(place[0] != '@'))
    {
	dir = implode(explode(file_name(this_object()), "/")[..-2], "/");
        place = FPATH(dir, place);
    }

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

string
expand_dir(string s)
{
    switch(s)
    {
      case "e": return "east";
      case "w": return "west";
      case "n": return "north";
      case "s": return "south";
      case "u": return "up";
      case "d": return "down";
    }
    return s;
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

    direct = expand_dir(direct);
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
ddo_exa(string where, string what)
{
    where = expand_dir(where);
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
    return 0;
}

int
do_look(string s)
{
    string what, where;
    
    NF("Look what?\n");
    if (!strlen(s))
        return 0;
    if (!parse_command(s, TO, "'at' %w %w", where, what))
        return 0;

    return ddo_exa(where, what);
}

int
do_exa(string s)
{
    string what, where;
    
    NF("Exa what?\n");
    if (!strlen(s))
        return 0;
    if (!parse_command(s, TO, "%w %w", where, what))
        return 0;

    return ddo_exa(where, what);
}

void
create_earthroom()
{
}

string
er_long()
{
    string s;
    int i, j;

    j = sizeof(dig_desc);

    if (!j)
        return "";

    if (j == 1)
        return "Someone has dug a hole leading " + dig_desc[0] + ".\n";

    s = "Someone has dug " + LANG_WNUM(j) + " holes leading ";

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
    mixed s;

    set_long("In a small hole in the ground.\n");
    set_short("dirty hole");

    set_noshow_obvious(1);

    add_item("walls", "The walls look rather interesting.\n");
    add_item("holes", "@@ch");

    create_earthroom();

    s = query_long();
    if (stringp(s))
        set_long(s + VBFC_ME("er_long"));
    add_prop(ROOM_I_DIG_FUN, "do_dig");
    INSIDE;
}

void
init()
{
    ::init();

    add_action("do_look", "look");
    add_action("do_exa", "exa", 1);
    add_action("digdig", "dig");
}

int
digdig()
{
    notify_fail("It is a lot easier to use a shovel for digging.\n");
    return 0;
}
