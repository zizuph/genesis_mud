/*
 * Base Room for High Road
 * -- Finwe, July 2006
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit "/d/Faerun/highroad/std/base_common.c";
inherit FAERUN_OUTDOOR_BASE;

void
create_road()
{
}


void
create_faerun_room()
{
    setuid(); 
    seteuid(getuid());
    
    ::create_faerun_room();
//    add_prop(ROOM_S_MAP_FILE,"highroad_map.txt");

    extraline = "Room description goes here.";

    set_short("Along the High Road");
//    set_long(short() + ". " + extra_line + "\n");
    create_road();
}

/*
 * Function name : add_highway
 * Description   : adds descr of highway
 */
void add_highway()
{
}


// north Highroad descriptions
string nrd_desc1(string str)
{
    return "The road is a wide track of trampled grass. It passes through grasslands and is well traveled. Some scrub bushes dot the land. " + str;
}

string nrd_desc2(string str)
{
    return "The road runs through the fertile grasslands. It is a wide area of trampled grass. On either side of the road tall grass waves in the breeze. " + str;
}

string nrd_desc3(string str)
{
    return "The grasslands stretch out in all directions as the road runs through it. Wildflowers and bushes dot the grassland. " + str;
}

string nrd_desc4(string str)
{
    return "The grass waves in the breeze alongside the road. It runs north and south in a general direction. " + str;
}