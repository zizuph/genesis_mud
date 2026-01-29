/* /d/Raumdor/common/vallaki/outdoor/road02.c
*
*
* Nerull 2021
*
*/

#include "../defs.h"

inherit VALLAKI_ROAD_STD_ROOM;


void
create_room()
{
    ::create_room();
    
    int area;
    
    // Orientation / area
    // 1 = south, 2 = southwest, 3 = west, 4 = northwest
    // 5 = north, 6 = northeast, 7 = east, 8 = southeast
    area = 1;
    
    string *long_descriptor = ROAD_LONG_DESC[area];   
    string long_desc;
    long_desc = long_descriptor[random(sizeof(long_descriptor))];
    
    string *short_descriptor = ROAD_SHORT_DESC[area];   
    string short_desc;
    short_desc = short_descriptor[random(sizeof(short_descriptor))];

    // South direction, inside outer wall.
    if (area == 1)
    {
        add_item(({"great wall","wall"}),"The great wall that protects the "+
        "city from the savages that lie outside. Guards patrol the tops, "+
        "keeping an eye out for trouble.\n");
        
        if (random(2) == 1)
        {
            add_item(({"scaffold", "scaffolds"}),"This old and rotten wooden "
            +"framework has seen better days. It looks unstable "
            +"and dangerous to use.\n");
        
            long_desc = long_desc + "Old wooden scaffolds are raised for wall "
            +"maintenance in this area.";
        }
    }
    
    set_long(long_desc + "\n");
    set_short(short_desc);
    
    add_exit(VALLAKI_OUTDOOR_DIR + "road01","south");
    
    reset_room();
}


void reset_room()
{
}
