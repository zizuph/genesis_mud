/*
 *  /d/Gondor/guilds/rangers/obj/join_scroll.c
 *
 *  Scroll given to new rangers when they join the guild.
 *
 *  Originally coded by:  Elessar?  (no credit given)
 *
 *  Modification log:
 *     Alto, 19-Mar-02, move, modify to fit new rangers code.
 */
inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "../rangers.h"

int do_destruct();

void
create_object()
{
    set_name("scroll");
    add_name("ranger-scroll");
    add_name("ranger_scroll");
    set_short("scroll of the Westland Rangers");
    set_long("This scroll was given to you as an introduction to your new " +
        "guild, the Rangers of the Westlands. There is some important " +
        "text on it, which you may read.\n");
    add_prop(OBJ_I_VALUE,   0);
    add_prop(OBJ_I_WEIGHT,  10);
    add_prop(OBJ_I_VOLUME,  10);
    add_prop(OBJ_I_NO_DROP, &do_destruct());
}

int
read_scroll(string str)
{
    if (!strlen(str))
    {
        notify_fail("Read what?\n");
        return 0;
    }

    if (str=="scroll" || str == "text" || str == "text on scroll")
    {
        cat(RANGERS_TEXT + "join_scroll.txt");
        return 1;
    }

    return 0;
}

void
destruct_me()
{
    object room = environment();

    while (!room->query_prop(ROOM_I_IS))
        room = environment(room);

    tell_room(room, "The scroll suddenly catches fire, and burns to " +
        "dust in a flash!\n");

    remove_object();
}

int
do_destruct()
{
    set_alarm(2.0, 0.0, destruct_me);
    return 0;
}

void
init()
{
    add_action(read_scroll, "read");
}

