/*
 * A sea cave in Faerie
 * By Finwe, August 2004
 */

#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#define WELL_PROP "_i_found_the_well_"
#define MIN_AWARE 13

inherit SEA_CAVE_BASE;

void
create_sea_cave_room()
{
    set_short("Inside a sea cave");
    set_long(short() + ". The cave is larger than the others. It is " +
        "irregularly shaped with a low ceiling and rough walls. The " +
        "floor is dirty and littered with rocks and pebbles. It looks " +
        "like the cave was recently used because of extra debris scattered " +
        "in heaps.\n");

    add_item(({"ground", "floor"}),
        "The ground is uneven and dirty. It is littered with rocks, pebbles, and garbage.\n");
    add_item(({"garbage"}),
        "It is piled around on the ground, and is smelly and dirty.\n");

    add_item(({"hole", "opening",}),
        "@@hole_descr");
    add_item(({"ladder", "rusty ladder",}),
        "@@ladder_descr");
    add_item(({"shaft"}),
        "@@shaft_descr");




    add_prop("_obj_s_search_fun","do_search");
    set_cave_room();

    reset_room();

    add_exit(FOREST_DIR + "seacave03", "east");
}

public void
init()
{
    ::init();
    add_action("enter_shaft", "enter");
}

string
do_search(object searcher, string str)
{
    int awareness;

    awareness = searcher->query_skill(SS_AWARENESS);
    if(awareness < MIN_AWARE) return 0;

    if(!str || (str!= "garbage" && str != "ground")) return 0;
        searcher->add_prop(WELL_PROP, 1);
    
    return "You find a hole hidden under the garbage.\n";
}

int
enter_shaft(string str)
{
    if (str =="opening" || str =="hole" ||  str =="shaft" )
    {
    write("You very carefully climb down the ladder. It breaks under your weight and you fall! You land in the water below!\n");
    say(QCTNAME(TP) + " carefully climbs down the ladder. It breaks and " + HIS_HER(TP) + " falls down the shaft, screaming all the way until you hear a muffled splash!.\n");
    
    TP->move_living("M",FOREST_DIR + "rivershaft",1,0);
    
    say(QCTNAME(TP) +" screams as " +  HE_SHE(TP)  +  " plunges down the shaft towards you! " + CAP(HE_SHE(TP)) + " splashes in the water next to you.\n");

    return 1;
    }
    
    write("Enter what?\n");
    return 1;
}

string
hole_descr()
{
    if(TP->query_prop(WELL_PROP))
        return "The hole is partially covered by garbage. It leads down a " +
            "shaft. There is a ladder attached to the inside of the shaft.\n";

    return "You find no hole.\n";
}

string
shaft_descr()
{
    if(TP->query_prop(WELL_PROP))
        return "The shaft is long and plunges deep into the earth. A ladder runs down the inside of the shaft. There is no telling what is at the bottom unless you climb down into the shaft it.\n";

    return "You find no shaft.\n";
}

string
ladder_descr()
{
    if(TP->query_prop(WELL_PROP))
        return "The ladder is attached to the inside of the shaft. It looks rusty and descends deep into the shaft. You can probably climb into the shaft.\n";

    return "You find no ladder.\n";
}