/* 
 * Tour note given to players to keep of tours in Faerie.
 * Based on the tournote from Pelargir, originally coded by Elessar, May 92.
 * -- Finwe, April 2005
 */

inherit "/std/object";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

int     tour_no,
        tour_done;
string  task,
        player_name,
       *cnames = ({});

void
create_object()
{
    set_name("note");
    add_name("faerie_tour_note");
    set_short("@@short_desc@@");
    set_pshort("tour notes");
    set_long("@@long_desc@@");
    add_prop(OBJ_I_VOLUME, 20);
    add_prop(OBJ_I_WEIGHT, 20);
}

void
set_tour_no(int i)
{
    tour_no = i;
}

int
query_tour_no()
{
    return tour_no;
}

void
set_tour_done()
{
    tour_done = 1;
}

void
set_player_name(string str)
{
    player_name = str;
}

string
query_player_name()
{
    return player_name;
}

int
query_tour_done()
{
    return tour_done;
}

void
set_task(string s)
{
    task = s;
}

string
query_task()
{
    return task;
}

string
short_desc()
{
    if (tour_done)
        return "tour note (solved)";
    return "tour note (unsolved)";
}

string
long_desc()
{
    string  ld = "This is a tour note given to you by the Chief Delegate of " +
        "Faerie. It is proof of the tour assigned to you. ";

    ld += "The task she asked you to solve is this:\n\n" + task;

    if (tour_done)
        ld += "\nThe task is now solved. Return to the Chief Delegate for your " +
        "reward.\n";
    else
        ld += "\nThe task is not solved yet.\n";

    return ld;
}
