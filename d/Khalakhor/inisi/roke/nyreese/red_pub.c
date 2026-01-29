/*
 * red_pub.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/* Modified copy of inn in solace, coded by Nick */
/* Improved (?) by Ged & Gresolle */

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit "/std/room";
inherit ROKEDIR + "/lib/pub";
inherit "/d/Genesis/delivery/office";

#include <macros.h>
#include <stdproperties.h>

#define CDIR ROKEDIR + "obj/"

object tika, sammy; /* Kalufs */
int keynotsold;

/*
 * Function name: reset_room
 * Description:   Set up the objects at reset
 */
void
reset_room()
{
    keynotsold = 1;

    if (!tika)
    {
        tika = clone_object(ROKEDIR + "npc/joe");  /* sloppy joe :) */
        tika->move_living("home", TO);
    }
    if (!present(tika, TO))
    {
        tika->move_living("home", TO);
    }        
    if (!sammy)
    {
        sammy = clone_object(ROKEDIR + "npc/sammy");
        sammy->move_living("home", TO);
    }

    reset_office();
    add_content(ROKEDIR + "obj/pot");
}

/*
 * Function name: create_room
 * Description:   Set up default trade and cofigure it if wanted.
 */
void
create_room()
{
    config_pub();
    set_short("a rather disgusting bar");
    set_long("Somehow you have managed to get to " +
             "the local pub without getting killed by any of the local" +
             " thugs. There is a rather sloppy bar near the west wall," +
             " with an at least equally sloppy bartender behind it. " +
             "A poster hangs on the wall, offering jobs to those less" +
             " sensitive of what they trade.\n");
    set_office("Sloppy Joe's Bar in Cadu", 5);
    add_item("bar", "A rather disgusting bar. There is a menu on it.\n");
    add_item("menu", "@@read");
    add_cmd_item("menu", "read", "@@read");

    add_article(({"beer", "light", "light beer"}), 
                CDIR + "lightbeer", 10);
    add_article(({"wine", "cheap wine", "homemade wine",
                  "cheap homemade wine"}), 
                CDIR + "cheapwine", 72);
    add_article(({"brew", "bottle", "local brew"}), 
                CDIR + "brew", 21 * 12);

    add_exit("red_r1", "east");

    add_item("poster", "@@delivery_poster@@");
    add_cmd_item("poster", "read", "@@delivery_poster@@");

    add_prop(ROOM_I_INSIDE, 1); /* This is a real room */
    reset_room();
}

/*
 * Function name: init
 * Description:   Initalize the pub actions
 */
void
init()
{
    ::init();
    init_pub();
    init_office();
}

/*
 * Function name: read
 * Description:   Read the menu
 */
string
read()
{
    return
        "   Some light beer                 10 copper\n" +
        "   A glass of cheap homemade wine  72 copper\n" +
        "   A bottle of the local brew      21 silver\n" +
        "\n" + pub_std_usage_string();
}

void
check_key(object key)
{
    if (!objectp(key))
        keynotsold = 1;
}

mixed *
get_order(string order_name)
{
    object ob;

    if (order_name != "key")
        return ::get_order(order_name);
    if (keynotsold)
    {
        ob = clone_object(CDIR + "brewkey");
        set_alarm(1.0, 0.0, &check_key(ob));
        keynotsold = 0;
        return ({ob, 12*12*12});
    }
    notify_fail("The key is sold!");
    return ({0, 0});
}

void
sell_key(object tp)
{
    if (!keynotsold || random(10) < 7)
        return;
    
    if (!objectp(tp) || ENV(tp) != TO)
        return;

    say("Joe whispers something to " + QCTNAME(tp) + ".\n", ({tp}));
    tp->catch_msg("Joe whispers to you: I have the key to the brewery" +
                  " tap.\nJoe whispers to you: It will cost you only one " +
                  "platinum.\n");
}

int
pub_hook_may_order()
{
    if (!tika || !present(tika, TO))
    {
        NF("Joe isn't here to answer your call.\n");
        return 0;
    }
    return 1;
}

void
pub_hook_player_buys(object ob, int price, object *players, object buyer,
                     string pay, mixed change)
{
    write("Joe gets to work.\n");
    ::pub_hook_player_buys(ob, price, players, buyer, pay, change);
    if (keynotsold)
        set_alarm(3.0, 0.0, &sell_key(TP));
}
