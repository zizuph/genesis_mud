/* A tournote to keep track of the tour the player is doing.
 * Elessar, May 92.
 * Captains number subject to change at any time -- Tapakah.
 * In the end the file should query the master ship object for the ships
 * having "Pelargir" in their route.
 */

inherit "/std/object";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

// Number down to 3 as Earendil (line to Port Macdunn) and Haradacil (Kalad)
// and Sardon to Gont
// is getting shut down until further notice - Tapakah, 05/2009
#define NUM_CAPTAINS	3 

int     tour_no,
        tour_done;
string  task,
        player_name,
       *cnames = ({});

void
create_object()
{
    set_name("note");
    add_name("Pelargir_Tour_Note");
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
    string  ld = "This tour note was given to you as a proof that you "
               + "are working on a task assigned to you by the Lord "
               + "Councillor of Pelargir.";

    ld = BSN(ld)
       + "The task the Lord Councillor asked you to solve is:\n"
       + BSN(task);

    if (tour_done)
        ld += "The task is solved.\n";
    else
        ld += "The task is not solved yet.\n";

    return ld;
}

/*
 * For the captains: (2nd tour)
 */
void
add_captain(string name)
{
    if (member_array(name, cnames) == -1)
        cnames += ({ name });

    if (sizeof(cnames) == NUM_CAPTAINS)
        set_tour_done();
}

string *
query_cnames()
{
    return cnames;
}

