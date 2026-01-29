/*
 * The Beach of Faerie, beneath the second pier
 * By Finwe, April 2005
 */
 
#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
 
inherit BEACH_BASE;

int do_climb(string str);
int test_tour(object player);


void
create_beach_room()
{
    FIXEUID;
    add_prop(ROOM_S_MAP_FILE, "faerie_map_east.txt");
    set_short("A jetty overlooking a lake");
    set_long(short() + ". " + s_desc_sky_outside_sky() + 
    "It's a large piece of rock overlooking the beach. The exposed portion "+
    "is roughly oval and rough. There are paths that lead from it down to "+
    "the beach below. There is a pier north of here.\n" );

    reset_room();
    
    set_add_beach();
    set_add_forest();


    add_item(({"beach"}),
        "The beach is wide and runs out into the water from under the " +
        "landing. It is yellow colored and looks clean from the tides. " +
        "Bits of flotsam and jetsam are washed up on the beach.\n");
    add_item(({"road"}),
        "The road runs south into the forest. It is wide and looks well " +
        "used from many travellers.\n");

    add_exit(FOREST_DIR + "pier01n", "north");
    add_exit(FOREST_DIR + "pier00", "northeast");
    add_exit(FOREST_DIR + "ctroad21", "south");
    add_exit(FOREST_DIR + "beach01s", "east");
    add_exit(FOREST_DIR + "beach01n", "northwest");
}
void
reset_room()
{
}

void
init()
{
    ::init();
    add_action("do_climb","climb");
    test_tour(TP);

}

int
do_climb(string str)
{
    if (!str)
    {
	    write("Climb what, the pier?\n");
	    return 1;
    }
    if (!parse_command(str, ({}),
        "[landing] [down] [pier] [log] [logs] [piles] [piling] [pilings] [grooves] "))
    {
	    write("Climb what?\n");
	    return 1;
    }

    write("With great effort, you carefully climb down the side of the " +
        "landing.\n");
    say(QCTNAME(TP) + " climbs carefully down the side of the landing.\n");
    TP->move_living("M",FOREST_DIR + "beach00",1,0);
    say(QCTNAME(TP) +" arrives climbing down from the landing.\n");
    return 1;
}
void
tour_done(object player)
{
    player->catch_msg("This is the Landing Area of the piers of Faerie. " +
        "Countless travellers come this way. You can now return and " +
        "report to the Chief Delegate that you were here.\n");
}

void
test_tour(object player)
{
     object  note;

     if (!objectp(note = present("faerie_tour_note", TP)))
        return;

    if ((note->query_tour_no() != PIERS_TOUR_NUM) || (note->query_tour_done()))
    return;

    note->set_tour_done();

    set_alarm(2.0, 0.0, &tour_done(TP));
}

