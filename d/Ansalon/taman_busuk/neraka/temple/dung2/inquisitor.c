/*
 * 2004-10-31 - Cotillion
 * - Fixed bugs that made the room grow huge.
 */

#pragma strict_types

#include "../defs.h"
#include "/d/Ansalon/guild/pot/guild.h"
#include <macros.h>

inherit TEMPLE + "std_base.c";
inherit TEMPLE + "/lib/seats.c";

mapping gDescs = ([ ]);

void
restore_vars()
{
    setuid();
    seteuid(getuid());

    gDescs = restore_map(MASTER);
}

void
save_vars()
{
    setuid();
    seteuid(getuid());
    
    save_map(gDescs, MASTER);
}

void
update_room_desc()
{
    int x, size;

    if (stringp(gDescs["room"]))
        set_long(gDescs["room"] + "\n");
    
    for (x = 0, size = sizeof(gDescs["items"]) ; x < size ; x++)
    {
        remove_item(gDescs["items"][x][0]);
        add_item(gDescs["items"][x][0], gDescs["items"][x][1] + "\n");
    }
}    

void
create_temple_room()
{
    object door;
    
    set_short("Inquisitor's room");
    set_long("This is the room of the Inquisitor.\n");

    restore_vars();
    update_room_desc();

    set_chairs(({"heavy throne-like chair", "simple wooden chair",
        "simple wooden chair"}));

    door = clone_object( DOOR + "inquisitor2.c" );
    door->move(this_object());
}

int
do_undecorate(string arg)
{
    int x, size;
    
    if (!this_player()->query_wiz_level() &&
        GUILD_ADMIN->query_council_seat("inquisitor") !=
        this_player()->query_real_name())
        return 0;

    if (!arg)
    {
        notify_fail("Undecorate what?\n");
        return 0;
    }
    
    if (arg == "room")
    {
        write("You undecorate the room.\n");
        say(QCTNAME(this_player()) + " undecorates the room.\n");
        gDescs["room"] = 0;
        save_vars();
        update_room_desc();

        return 1;
    }
    else
    {
        for (x = 0, size = sizeof(gDescs["items"]) ; x < size ; x++)
        {
            if (member_array(arg, gDescs["items"][x][0]) >= 0)
            {
                write("You undecorate " + arg + ".\n");
                say(QCTNAME(this_player()) + " undecorates " + arg + ".\n");

                remove_item(arg);
                gDescs["items"] = exclude_array(gDescs["items"], x, x);
                save_vars();
                update_room_desc();
                
                return 1;
            }
        }
    }                    

    notify_fail("You do not find any " + arg + " to undecorate.\n");
    return 0;
}

int
do_decorate(string arg)
{
    int x, size;
    string what, desc, *arr;
    string *items;

    if (!this_player()->query_wiz_level() &&
        GUILD_ADMIN->query_council_seat("inquisitor") != 
        this_player()->query_real_name())
        return 0;

    if (!arg || !parse_command(arg, this_player(), "%s 'with' %s", what, desc))
    {
        notify_fail("Decorate what item with what description?\n");
        return 0;
    }

    items = explode(what, " and ");
    
    for (x = 0, size = sizeof(gDescs["items"]) ; x < size ; x++)
    {

        if (sizeof(gDescs["items"][x][0] & items))
        {
            write("The " + implode(items, " or ") +
                " is already decorated, undecorate first.\n");
            return 1;
        }
    }
    
    
    write("You decorate " + LANG_ADDART(what) + " as being " + desc + "\n");
    say(QCTNAME(this_player()) + " decorates " + LANG_ADDART(what) + ".\n");

    if (what == "room")
        gDescs["room"] = desc;
    else
    {
        if (!gDescs["items"])
            gDescs["items"] = ({ ({ explode(what, " and "), desc }) });
        else
            gDescs["items"] += ({ ({ explode(what, " and "), desc }) });
    }
    
    update_room_desc();

    save_vars();
    return 1;
}

void
enter_inv(object ob, object from)
{
    if (GUILD_ADMIN->query_council_seat("inquisitor") ==
        ob->query_real_name())
    {
        set_alarm(0.1, 0.0, &(ob)->catch_tell("Being the owner of the " +
            "room you could decorate to your liking and later undecorate " +
            "features of it.\n"));
    }
    
    ::enter_inv(ob, from);
}

void
leave_inv(object ob, object to)
{
    seats_leave_inv(ob, to);
    ::leave_inv(ob, to);
}

void
init()
{
    ::init();

    seats_init();    
    add_action(do_decorate, "decorate");
    add_action(do_undecorate, "undecorate");
}
