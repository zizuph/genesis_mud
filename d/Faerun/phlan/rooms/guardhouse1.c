/*  /d/Faerun/phlan/rooms/guardhouse1.c
*
*   By Tharizdun, 2021
* 
*/

#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include <terrain.h>
#include "defs.h"

inherit BASE_PHLAN_INDOOR;

/*
*   Setting up for the guards
*/

object guard1;
object guard2;
object guard3;
object leader;

void
create_phlan_room()
{
    set_long("Guardhouse main floor.\n"
        +"The guardhouse is imposing if nothing else. It is twenty feet"
        +" square with a ten foot high ceiling. A staircase wide enough for"
        +" two soldiers abreast to use leads to the upper floor. Many"
        +" defensive structures are built by highly sought after dwarven"
        +" stonemasons but this is gnomish built, obvious by the use of"
        +" magic. Invisible from the outside, arrow slits covered by"
        +" one-way illusions allow the guards to remain safely behind the"
        +" walls and still command the gate area. Mounted on the ceiling"
        +" are glowing bars that provide tactical lighting. The inner walls,"
        +" north and east have 4 bunk beds against them allowing 8 guards to"
        +" stay here indefinitely. A barrel and several boxes sit off to the"
        +" sides and a table with four chairs sits in the middle of the"
        +" floor. The only other entrance is east, back to the street.\n");
    
    set_short("Guardhouse main floor");
 
/*
*   Decorations
*/ 
        
    add_item(({"walls", "wall"}),
        "The walls are of tightly fitted stone  blocks, precisely shaped"
        +" to only require mortar for repairs. They are rough-finished"
        +" so as to somewhat subdue a sonic attack and minimize reflection"
        +" of beam or lightning attacks. There are several arrow slits in"
        +" the south wall and you would estimate the west wall butts"
        +" against the city wall itself.\n");

    add_item(({"stone", "stones", "block", "blocks"}),
        "You cannot determine the specific type of stone used in"
        +" these blcoks, but the small tight grain would indicate"
        +" at some point it formed relatively quickly and under"
        +" pressure. It is quite strong and possibly magically"
        +" reinforced.\n");

    add_item(({"floor", "ground"}),
        "The floor is of larger blocks of the same stone used in the"
        +" walls, only cut into paving style stones.\n");

    add_item(({"ceiling"}),
        "The ceiling is of the same stone as the floors and walls. There"
        +" are glowing bars mounted on the ceiling that supply tactical"
        +" lighting for the room.\n");

    add_item(({"staircase"}),
        "The stone staircase is wide enough to allow two fully armed"
        +" and armoured men to travel abreast or to pass each other"
        +" if going in opposite directions.\n");

    add_item(({"slit", "slits", "arrow slit", "arrow slits"}),
        "Slits shaped into the wall, approximately one foot wide on the"
        +" inner side of the wall and two inches on the outer side. They"
        +" sit two feed off the floor and rise to eight feet. A slight"
        +" haze seems to form at the outer side, the result of a"
        +" permanent illusion spell which totally hides them from outside"
        +" view.\n");

    add_item(({"bar", "bars"}),
        "Four bars, six foot long each and four inches in diameter, are"
        +" mounted to the ceiling. They give off a red light, which"
        +" illuminates the room but does not interfere with night vision"
        +" or infravision.\n");

    add_item(({"bed", "beds", "bunk bed", "bunk beds", "bunk", "bunks"}),
        "Simple bunkbeds with no mattresses allow the soldiers to stay"
        +" here for long periods of time if needed. They do not look"
        +" particularly comfortable, but it beats sleeping on the floor.\n");
        
    add_item(({"barrel"}),
        "The barrel contains drinking water for the soldiers.\n");

    add_item(({"box", "boxes"}),
        "The boxes contain fresh fruits and dried meats for the soldiers"
        +" to eat while on duty.\n");

    add_item(({"table"}),
        "A simple sturdy table for the guards to use. It is surrounded"
        +" by four chairs.\n");   
        
    add_item(({"chair", "chairs"}),
        "Four simple sturdy chairs that can support an armoured man sit"
        +" around the table in the center of the room.\n"); 

    add_item(({"entrance"}),
        "The entrance to the east leads back out to the street.\n");        
   
    add_exit(ROOM_DIR + "guardhouse2", "up");
    add_exit(ROOM_DIR + "road5", "east");
    
    reset_faerun_room();        
}

void
reset_faerun_room()
{
    ::reset_faerun_room();

/*
*   Guards and leader
*/    
    
    if (!guard1)
    {
        guard1 = clone_object(NPC_DIR + "phlan_city_guard");
        guard1->move(this_object(), 1);
    }
    
    if (!guard2)
    {
        guard2 = clone_object(NPC_DIR + "phlan_city_guard2");
        guard2->move(this_object(), 1);
    }
    if (!guard3)
    {
        guard3 = clone_object(NPC_DIR + "phlan_city_guard3");
        guard3->move(this_object(), 1);
    } 
    if (!leader)
    {
        leader = clone_object(NPC_DIR + "phlan_city_guard_leader");
        leader->move(this_object(), 1);
    }    
}