/*
 * This is the standard packet which is taken around between the offices.
 * Created by Aridor, 05/95
 *
 * It is possible to inherit this object and add other features, but it
 * is NOT advised that these objects are of any real use!!
 *
 * This file modified for Gondor, Olorin, 11-may-1995
 */

#include "/d/Gondor/defs.h"
#include <language.h>
#include <stdproperties.h>
#define ADJ_LIST ({"green","blue","red","orange","violet","purple",\
		   "black","white","golden",})

inherit "/std/object";

private string  origin;
private string  destination;
private int     start_time;

void
create_packet()
{
}

void    set_start_time(int time) { start_time = time; }

nomask void
create_object()
{
    set_name("packet");
    add_adj(ADJ_LIST[random(sizeof(ADJ_LIST))]);
    set_long("This is " + LANG_ADDART(query_adj()) + " packet. It is not very "
      + "big and you can carry it fairly easily. It has a label stamped onto "
      + "it, with the origin of packet saying '@@query_origin_string@@' and "
      + "the destination of the object is marked as '@@query_destination_string@@'.\n");
    add_prop(OBJ_I_WEIGHT,  2000);
    add_prop(OBJ_I_VOLUME, 10000);
    create_packet();
    add_prop(OBJ_I_VALUE,      0);
    set_start_time(time());
}

public nomask string
query_origin_string()
{
    return origin;
}

public nomask void
set_origin_string(string str)
{
    if (!strlen(origin))
        origin = str;
}

public nomask string
query_destination_string()
{
    return destination;
}

public nomask int
query_delivery_packet()
{
    return 1;
}

public nomask void
set_destination_string(string str)
{
    if (!strlen(destination))
        destination = str;
}

public nomask int
query_start_time_packet()
{
    return start_time;
}
