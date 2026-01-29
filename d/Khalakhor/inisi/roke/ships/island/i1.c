/*
 * i1.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "../../defs.h"
#include <macros.h>

#define ISLAND_LOG ROKEDIR + "log/island"

void boat_comes();
void rescue();
void goaway(object * ob);
void arrived(object * ob);

string
mylong()
{
    return "You are standing on a small beach. There is lots of wreckage " +
        "spread all over the beach. Back west you can see a ship far away" +
        (((SHIPDIR + "island/i2")->query_hydra())?
         (", and to the east you hear frightening sounds.\n") : (".\n"));
}

void
create_room()
{
    set_short("beach");
    set_long("@@mylong");

    add_item("wreckage",
             "There is definitely enough of wood here to light a fire\n");

    add_exit("i2", "east");

    BEACH;
}

void
init()
{
    ::init();

    add_action("lighta", "light");
}

int
lighta(string s)
{
    if (s != "fire")
    {
        NF("Light what? A fire?\n");
        return 0;
    }
    else
    {
        write("You gather some wood and light a fire by rubbing two very " +
              "dry sticks.\n");
        say(QCTNAME(TP) + "lights a fire by rubbing some sticks.\n");

        set_alarm(5.0, 0.0, boat_comes);
        write_file(ISLAND_LOG,
                   sprintf("%s: %-11s left the island\n",
                           ctime(time()), 
                           capitalize(this_player()->query_real_name())));
        return 1;
    }
}

void
boat_comes()
{
    tell_room(TO, "A small rowing-boat arrives.\n");
    set_alarm(3.0, 0.0, rescue);
}

void
rescue()
{
    object *obs, *ob;
    int i;

    tell_room(TO,
              "A huge sailor jumps out of the small rowing-boat and grabs you.\n" +
              "The huge sailor says: I will rescue you.\n" +
              "Then he throws you in the boat.\n");

    obs = all_inventory(TO);
    ob = ({});
    for (i = 0; i < sizeof(obs); i++)
        if (interactive(obs[i]))
            ob += ({obs[i]});

    ob->move_living("M", SHIPDIR + "island/boat");

    set_alarm(2.0, 0.0, &goaway(ob));
}

void
goaway(object * ob)
{
    tell_room(SHIPDIR + "island/boat",
              "The huge sailor starts to row towards Cadu with a speed " +
              "which is much faster than you thought was possible.\n");
    set_alarm(5.0, 0.0, &arrived(ob));
}

void
arrived(object * ob)
{
    tell_room(SHIPDIR + "island/boat",
              "You arrive at Cadu and the sailor throws you up on the shore " +
              "then he and his boat disappears in a puff of smoke.\n");

    ob->move_living("M", NYREESEDIR + "cadu_b2");
}
