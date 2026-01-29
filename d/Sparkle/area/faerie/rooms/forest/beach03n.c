/*
 * The Beach of Faerie, beneath the second pier
 * By Finwe, April 2005
 */
 
#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
 
inherit BEACH_BASE;

#define BUSH_PROP "_i_found_the_cave_"
#define MIN_AWARE 13

void
create_beach_room()
{
    FIXEUID;
    add_prop(ROOM_S_MAP_FILE, "faerie_map_east.txt");
    set_short("A sandy beach alongside a lake");
    set_long(short() + ". " + s_desc_sky_outside_sky() + "The waves lap " +
        "onto the yellow sand. The beach runs alongside the lake and " +
        "slopes gently into the water. Some scraggy bushes grow along the " +
        "ridge. In the distance, vessels can be seen on the lake. Some " +
        "sail into the horizon or bob on the water.\n");

    reset_room();
    add_item(({"bushes", "scraggy bushes"}),
        "They are windswept and unusually scraggly. They grow at the " +
        "edge of the beach and are slowly creeping onto the beach.\n");
//    add_prop("_obj_s_search_fun","do_search");

    
    set_add_beach();
    set_add_forest();

    add_exit(FOREST_DIR + "beach04n",  "north");
    add_exit(FOREST_DIR + "beach02n", "southeast");


}
void
reset_room()
{
}

string
do_search(object searcher, string str)
{
    int awareness;

    awareness = searcher->query_skill(SS_AWARENESS);
    if(awareness < MIN_AWARE) return 0;

    if(!str || (str!= "bushes" && str != "scraggly bushes")) return 0;
        searcher->add_prop(BUSH_PROP, 1);
    
    return "You find a cave behind the bushes.\n";
}

void
init()
{   
    ::init();
 
//    add_action("enter_cave", "enter");
}

int
enter_cave(string str)
{
    if(str=="cave" ||
       str=="opening" || 
       str=="bushes")
    {
        if(TP->query_prop(BUSH_PROP))
        {    
            write("You enter the hidden cave.\n");
            say(QCTNAME(TP)+" disappears into the bushes.\n");
            tell_room(FOREST_DIR +"seacave01",QCTNAME(TP) + " arrives.\n");
	        TP->move_living("M", FOREST_DIR +"seacave01",1);
	   
            return 1;
        }
        else
        write("You can't seem to do that.\n");
        return 1;
    }
    notify_fail("Enter what?\n");
    return 0;
}
