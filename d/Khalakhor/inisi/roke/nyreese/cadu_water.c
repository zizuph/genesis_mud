/*
 * cadu_water.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit ROKEDIR + "lib/stdwater";

#include <ss_types.h>
#include <macros.h>
#include <formulas.h>
#include <filter_funs.h>
#include "bridgedefs.h"

void
create_waterroom()
{
    set_short("Water");
    set_long("You are swimming in the water below the pier. " +
             "There is a ladder here that leads up on the pier. " +
             "South of you is the open sea, where you can swim if " +
             "you want.\n");
  
    add_exit("cadu_b3", "up", "@@move_up");

    set_f_to_be_tired(FTOGOUP);
    set_f_to_drown(FTODROWN);

    add_item("ladder", "It is a sturdy wooden ladder, leading out of the water.\n");
}

void
remove(object ob)
{
    tell_room(this_object(),
              "The " + ob->query_name() + " sinks to the bottom of the sea.\n");
    ob->remove_object(); 
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (living(ob)) return;

    set_alarm(1.0, 0.0, &remove(ob));
}

int
swim(string s)
{
    NF("Swim where?\n");

    if (s != "s" && s != "south")
        return 0;

    (CARISCADIR + "waterhandler")->trans("south", 1, 0);
    return 1;
}

int
south(string s)
{
    (CARISCADIR + "waterhandler")->trans("south", 1, 0);
    return 1;
}  

int
move_up()
{
    if (TP->query_fatigue() < FTOGOUP)
    {
        write("You are too tired to climb up.\n");
        return 1;
    }
    TP->remove_prop(IS_NOTIFIED);
    return 0;
}

int 
rescue(string str)
{
    object *ob;

    if (!str)
    {
        NF("Rescue who?\n");
        return 0;
    }

    if (!parse_command(lower_case(str), ENV(TP), "%l", ob))
    {
        NF("Rescue who?\n");
        return 0;
    }
  
    if (sizeof(ob) < 2 || !objectp(ob[1]))
    {
        NF("Rescue who?\n");
        return 0;
    }

    if (TP->query_fatigue() < FTOGOUP)
    {
        write("You are to tired to rescue anyone.\n");
        return 1;
    }

    TP->catch_msg("You heroically rescue " + QTNAME(ob[1]) + " and bring " +
                  ob[1]->query_objective() + " up on the pier.\n");
    ob[1]->catch_msg(QCTNAME(TP) + " heroically rescues you and brings " +
                     "you up on the pier.\n");
    say(QCTNAME(TP) + " heroically rescues " + QTNAME(ob[1]) +
        " and brings " + ob[1]->query_objective() + " up on the pier.\n",
        ({TP, ob[1]}));
    tell_room(BRIDGEROOM, QCNAME(TP) + " comes up from the water, bringing " +
              QNAME(ob[1]) + " with " + TP->query_objective() + ".\n");
    TP->move_living("M", BRIDGEROOM);
    ob[1]->move_living("M", BRIDGEROOM);
    TP->remove_prop(IS_NOTIFIED);
    ob[1]->remove_prop(IS_NOTIFIED);
    return 1;
}

void
obj_is_tired(object obj)
{
    if (!obj->query_prop(IS_NOTIFIED))
    {
        obj->catch_msg("You have been swimming too long, you are very tired.\n");
        obj->add_prop(IS_NOTIFIED, 1);
    }
}
 
void drown_him(object obj);

void
drown(object obj)
{
    object guard;

    if (obj->query_prop(IS_DROWNED)) return;
    obj->add_prop(IS_DROWNED, 1);

    obj->catch_msg("You are now too exhausted to swim any longer.\n" +
                   "Desperatly you try to get up on the pier but you fail.\n" +
                   "In a last desperate try to stay alive you " +
                   "shout loudly for help.\n");
    tell_room(this_object(), QCTNAME(obj) +
        " is almost drowning, and shouts loudly for help.\n", ({obj}));
    tell_room(BRIDGEROOM,
              "Someone in the water shouts loudly for help.\n");
    if (guard = BRIDGEROOM->query_guard_present())
    {
        guard->rescue(obj);
        obj->remove_prop(IS_DROWNED);
        obj->remove_prop(IS_NOTIFIED);
    }
    else 
    {
        set_alarm(2.0, 0.0, &drown_him(obj));
    }
    obj->reduce_hit_point(obj->query_max_hp()/10);
}

void
drown_him(object obj)
{
    obj->catch_msg("Lucky as you are you don't drown. Instead " +
                   "you are brought up on the shore by the waves.\n\n");
    tell_room(this_object(), QCTNAME(obj) +
              " is brought away by the waves.\n", ({obj}));
    tell_room(SHOREROOM, QCNAME(obj) + " is brought to land by the waves.\n");
  
    obj->move_living("M", SHOREROOM);
    obj->remove_prop(IS_DROWNED);
    obj->remove_prop(IS_NOTIFIED);
}

void
init()
{
    ::init();
    add_action(rescue, "rescue");
    add_action(swim,   "swim");
    add_action(south,  "south");
}
