/*
 * locationhandler.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

//FIXA
#pragma save_binary

#include "defs.h"

string *str = ({
    "A place below stone and might, a place where brave men fight.\n" +
    "The place where heroes descend, a place to let the battle end.\n",

    "High up on a mountain top, where the ride of the spirit stop.\n" +
    "Many creatures may be seen, through the hot white volcano steam.\n",

    "Close to the blue deep sea, where the orc children dig.\n" +
    "A bold hero should wander, to search for his goal.\n",

    "Below the highest cliff, south to the place that smell,\n" +
    "that is the way to the place, where the trolls dwell.\n",

    "Between the high green trees where a small pond live,\n" +
    "the damp grass hides what you seek.\n",

    "Where sheep are hiding from the wolves and herbs are growing green,\n" +
    "residing in a place where evil has never been.\n"});

string *locs = ({NYREESEDIR + "stable", 
                 CARISCADIR + "t", 
                 NYREESEDIR + "orc_sand", 
                 WILDDIR    + "p2",
                 NYREESEDIR + "for_fb", 
                 NYREESEDIR + "thwil_p1"});

string
give_room(int i)
{
    return locs[i];
}

string
give_location(int i)
{
    return str[i];
}

int
assign_nummer()
{
    return random(sizeof(locs));
}
