/* Mountain trail room, credit to Sarr and Nerull */
#pragma strict_types
#include "defs.h"
inherit MTRAIL_ROOM;

void
create_room()
{
    ::create_room();
    
    set_long("You stand in the middle of a rocky trail. Well, more of the "
    +"remnants of a road. You start to wonder what forces it must "
    +"have taken to carve this perilous pathway in this rather hostile "
    +"environment. Shrouded in an eerie fog you see "
    +"the resemblance of a castle to the northeast. The "
    +"trail leads north and south.\n");
    
    
    add_item("castle","Too far away to make out any details, the castle "
    +"looks eerie and shrouded in fog.\n");
    
    add_item("cliffs","The cliffsides are present all around the plateau, and "
    +"they all considerably drops into far below the mountainside.\n");
    
    add_item(({"ground", "groves", "large groves"}),"The ground here looks "
    +"rather well travelled judging by the groves and marks in the "
    +"mud all around "
    +"the area. Horses, carriages, and machines of war and boots probably.\n");
    
    add_item(({"rock", "rocks", "boulder", "boulders"}),"Littered "
    +"everywhere in this area, in different sizes and shapes, befitting the "
    +"natural environment.\n");
       
    add_item(({"mountain", "mountains"}),"The mountain landscape is both "
    +"pretty and scary at the same time. The tops are sporadically clad in "
    +"snow and ice, sprinkled with boulders and deep crevisses, comforted "
    +"by large steep drops into various abysses of sharp rocks.\n");
       
    add_item(({"mud"}),"While it's higher up in the mountains, melted "
    +"water mixed "
    +"with dust and other particules have created a thin slurry covering much "
    +"of the ground.\n");
    
    add_exit(MTRAIL_DIR + "mtrail_path3", "northeast");
    add_exit(MTRAIL_DIR + "mtrail_path1", "south");
}