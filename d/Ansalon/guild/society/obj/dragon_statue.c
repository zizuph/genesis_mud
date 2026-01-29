/*
 * /d/Ansalon/guild/society/obj/dragon_box.c
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
 * Dragon statue that eats things, garbage can...
 *
 * Gwyneth, 2001
 */
inherit "/std/container";

#include <cmdparse.h>
#include <macros.h>
#include <stdproperties.h>

static int gResetAlarm = 0, gRemoveAlarm = 0;
object gWho;

void
create_container()
{
    set_name(({"dragon", "statue", "mouth"}));
    set_adj(({"mysterious", "brass", "dragon"}));
    set_short("mysterious dragon statue");
    set_long("This mysterious statue, that looks an awful lot like a brass " +
        "dragon, was found by a nameless kender many years ago from an " +
        "irresponsible wizard who lost it. Its mouth is open wide, perhaps " +
        "hoping you will give it some otherwise useless junk to eat.\n");

    add_prop(CONT_I_MAX_WEIGHT, 900000);
    add_prop(CONT_I_MAX_VOLUME, 900000);
    add_prop(CONT_I_WEIGHT, 500000);
    add_prop(CONT_I_VOLUME, 500000);
    add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_M_NO_GET, "You get the mysterious dragon statue.\n" +
        "The mysterious dragon statue comes to life briefly and " +
        "hops out of your hands.\n");
}

void
reset_hum()
{
    gWho = this_object();
    gResetAlarm = 0;
}

public void
dragon_remove()
{
    int index, size;
    object *contents = all_inventory(this_object());

    gRemoveAlarm = 0;
    size = sizeof(contents);

    if (!size)
        return;
    contents->remove_object();
}

public void
enter_inv(object ob, object from)
{
    int *alarms = query_alarms();
    string message;
    object statue = this_object();

    ::enter_inv(ob, from);

    if (gWho == from)
    {
        return;
    }

    message = one_of_list(({"emits puffs of smoke", "rumbles loudly",
              "shakes violently", "squirms around happily", 
              "bounces around slightly", "shoots out steam",
              "changes to all the colours of the rainbow briefly",
              "swells up, then shrinks again",
              "shoots fireballs around the room", "hiccups uncontrollably",
              "sings a dragon drinking song", "brightens noticeably",
              "chortles with glee", "dances around excitedly", 
              "flips head over heels", "gives you a fond hug",
              "grins, showing pointy teeth", "licks its lips",
              "looks hopefully around for more", 
              "sniffs at your pockets, hoping for more"}));
    
    set_alarm(0.4, 0.0, &tell_room(environment(statue), "The mysterious " +
        "dragon statue comes to life for a moment and " + message + 
        " as it is fed.\n"));


    if (!gRemoveAlarm)
    {
        gRemoveAlarm = set_alarm(30.0, 0.0, &dragon_remove());
    }

    if (!gResetAlarm)
    {
        gWho = from;
        gResetAlarm = set_alarm(1.0, 0.0, &reset_hum());
        return;
    }
    
    gWho = from;
    return;
}

public int
hug_dragon(string str)
{
    object who = this_player();
    object *dragon = FIND_STR_IN_OBJECT(str, environment(this_object()));

    if (member_array(this_object(), dragon) != -1)
    {
        set_alarm(0.9, 0.0, &tell_object(who, "The mysterious dragon statue " +
            "comes to life briefly and hugs you.\n"));
        set_alarm(0.9, 0.0, &tell_room(environment(who), "The mysterious " +
            "dragon statue comes to life briefly and hugs " + QTNAME(who) +
            ".\n", who));
        return 0;
    }

    return 0;
}

public void
init()
{
    ::init();

    add_action(hug_dragon, "hug");
}
