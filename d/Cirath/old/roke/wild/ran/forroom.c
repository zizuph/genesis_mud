/*
 * forroom.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "randefs.h"
#include <language.h>
#include <macros.h>

object *items, *owner;
mixed ants;

void reset_room();
void follow(object who, object tp, object *objs);

void
create_forroom()
{
}

nomask void
create_room()
{
    create_forroom();
    set_alarm(6.0, 0.0, reset_room);
    add_cmd_item(({"rose", "flower"}), "pick",
                 "A small gnome smites your fingers with a ruler.\n");
}

mixed
query_ants()
{
    return ants;
}

void
check_ants()
{
    int t;
    mixed apa = ({});
    for (t = 0; t < sizeof(ants); t++)
        if (objectp(ants[t]))
            apa += ({ants[t]});
    ants = apa;
}

void
reset_room()
{
    int t;
    object ant;

    if (!pointerp(ants))
        ants = ({});

    check_ants();
    if (sizeof(ants))
        return;
    tell_room(this_object(), "Some ants crawls up from the ground.\n");

    seteuid(getuid());
    for (t = 0; t < 3; t++)
    {
        ant = clone_object(ROKEDIR + "npc/ant");
        ant->move(this_object());
        ants += ({ant});
    }
}

int
clean_up()
{
    int t;
    if (sizeof(filter(all_inventory(this_object()),
                      "filt_ant", this_object())) != 0)
        return 1;
    remove_object();
}

int
filt_ant(object ob)
{
    if (interactive(ob))
        return 1;
    if (!ob->id("ant"))
        return 1;
    return 0;
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!living(from))
        return;

    if (sizeof(items) == 0)
    {
        items = ({ob});
        owner = ({from});
    }
    else
    {
        items += ({ob});
        owner += ({from});
    }
}

void
leave_inv(object ob, object to)
{
    int d;
    object *objs;

    ::leave_inv(ob, to);

    objs = ({});

    if (living(ob))
    {
        while ((d = member_array(ob, owner)) != -1)
        {
            if (items[d])
                objs += ({items[d]});
            items = exclude_array(items, d, d);
            owner = exclude_array(owner, d, d);
        }
        if (sizeof(objs))
            set_alarm(1.0, 0.0, &follow(ob, to, objs));
    }
    else
    {
        if ((d = member_array(ob, items)) == -1)
            return;
        items = exclude_array(items, d, d);
        owner = exclude_array(owner, d, d);
    }
}

void
follow(object who, object to, object *objs)
{
    object gnome;
    int t;

    if (!who)
        return;

    seteuid(getuid());
    gnome = clone_object(ROKEDIR + "npc/gnome");
    gnome->move_living("M", TO);
    tell_room(TO, "A small gnome arrives.\n");
    for (t = 0; t < sizeof(objs); t++)
    {
        if (objs[t])
        {
            objs[t]->move(gnome);
            tell_room(TO, "The small gnome picks up " +
                      LANG_ASHORT(objs[t]) + ".\n");
        }
    }
    gnome->move_living("somewhere", E(who));
    gnome->command("say Hey, you dropped something.");
    for (t = 0; t < sizeof(objs); t++)
    {
        if (objs[t])
        {
            objs[t]->move(who);
            tell_room(to, "The small gnome gives " +
                      LANG_ASHORT(objs[t]) + " to " + QCTNAME(who) + ".\n", ({who}));
            who->catch_msg("The small gnome gives you " +
                           LANG_ASHORT(objs[t]) +
                           ".\n");
        }
    }
    gnome->command("say CU.");
    gnome->command("wave " + who->query_real_name());
    tell_room(to, "The small gnome disappears between some trees.\n");
    gnome->remove_object();
}
