/*
 * waterroom.c
 *
 * This is part of the water area between Cadu and Carisca
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit ROKEDIR + "lib/stdwater";

#include <macros.h>

#include "../nyreese/bridgedefs.h"

#undef FTOGOUP
#define FTOGOUP 30
#undef FTODROWN
#define FTODROWN 1

int x,y;

void
set_which(int i, int j)
{
    x=i; y=j;
}

string
wiz()
{
    return "(" + x + "," + y + ")";
}

void
create_waterroom()
{
    set_long("You are in the middle of the sea.\n" +
             "You can swim in all directions.\n");
    set_short("Water");
    add_prop(OBJ_S_WIZINFO, "@@wiz");
    WATER;

    set_f_to_be_tired(FTOGOUP);
    set_f_to_drown(FTODROWN);

    add_prop(ROOM_I_NO_CLEANUP, 1);
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

void
drown(object obj)
{
    say(QCTNAME(obj)+
        " is almost drowning, and shouts loudly for help.\n", ({obj}));
    obj->catch_msg("You almost drown as you are carried away by a huge wave.\n" +
                   "As you are too exhausted to swim, you can do nothing but " +
                   "hope that you will land in a friendly place.\n\n");
  
    obj->move_living("M", SHOREROOM);
    obj->reduce_hit_point(obj->query_max_hp() / 10);
    obj->remove_prop(IS_NOTIFIED);
}

int
n()
{
    int i;
    i = y - 1;
    
    (CARISCADIR + "waterhandler")->trans("north", x, i);
    return 1;
}

int
nw()
{
    int i, j;
    i = y - 1;
    j = x - 1;

    (CARISCADIR + "waterhandler")->trans("northwest", j, i);
    return 1;
}

int
ne()
{
    int i, j;
    i = x - 1;
    j = y + 1;

    (CARISCADIR + "waterhandler")->trans("northeast", i, j);
    return 1;
}

int
e()
{
    int i;
    i = x + 1;
  
    (CARISCADIR + "waterhandler")->trans("east", i, y);
    return 1;
}

int
se()
{
    int i, j;
    i = x + 1;
    j = y + 1;

    (CARISCADIR + "waterhandler")->trans("southeast", i, j);
    return 1;
}

int
s()
{
    int i;
    i = y + 1;

    (CARISCADIR + "waterhandler")->trans("south", x, i);
    return 1;
}

int
sw()
{
    int i, j;
    i = y + 1;
    j = x - 1;
  
    (CARISCADIR + "waterhandler")->trans("southwest", j, i);
    return 1;
}

int
w()
{
    int i;
    i = x - 1;
    
    (CARISCADIR + "waterhandler")->trans("west", i, y);
    return 1;
}

void
init()
{
    ::init();

    add_action(nw, "northwest");
    add_action(n , "north");
    add_action(s , "south");
    add_action(e , "east");
    add_action(w , "west");
    add_action(ne, "northeast");
    add_action(se, "southeast");
    add_action(sw, "southwest");
}

void
remove(object o)
{
    tell_room(TO, "The " + s->query_name() + " sinks to the bottom.\n");
    o->remove_object();
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    if (!from)
        return;

    if (living(ob))
        return;

    if (member_array("ship", ob->query_names()) > -1)
        return;

    if (member_array("boat", ob->query_names()) > -1)
        return;

    if (ob->query_prop(OBJ_I_VOLUME))
        if ((ob->query_prop(OBJ_I_WEIGHT) * 100) / 
            (ob->query_prop(OBJ_I_VOLUME)) < 100)
            return;

    set_alarm(1.0, 0.0, &remove(ob));
}
