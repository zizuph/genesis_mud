/*  /d/Faerun/phlan/rooms/phlanboard.c
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


void
create_phlan_room()
{
    set_long("Phlan bulletin board.\n"
        +"This the the city bulletin board. Any announcements to the public or"
        +" by the public will be found here. There are several tables with"
        +" needed implements for writing notes. Lamps hang from ceiling beams"
        +" to assist reading and writing.\n");
    
    set_short("Phlan bulletin board");
    
        
    add_item(({"walls", "wall"}),
        "The walls are rough cut cedar. They give off an aromatic scent that"
        +" is supposed to keep away moths, thus protecting the notes from"
        +" possible damage.\n");

    add_item(({"beam", "beams"}),
        "Large cedar beams support the peaked ceiling. There are nails"
        +" sticking out where posters and other announcements have been"
        +" hung in the past. Currently only a quartet of lamps are."
        +" suspended from them.\n");

    add_item(({"floor", "ground"}),
        "The floor is plain unadorned wood. It is clean but not polished."
        +" There are various ink stains from accidental spills. This is"
        +" probably why they are not polished or carpeted.\n");

    add_item(({"ink", "stain", "stains", "ink stains"}),
        "Black ink forms patterns here and there were an occasional"
        +" quill has been dropped or inkpot spilled. One of them looks"
        +" kind of like an orc. Another reminds you of a puppy. You"
        +" wonder if that means anything.\n");

    add_item(({"table", "tabless"}),
        "Two basic four-legged tables stand near the walls. They are"
        +" slightly higher than waist height and don't look like they"
        +" were made to support much weight. There are quills, inkpots"
        +" and sheets of parchment for composing notes.\n");

    add_item(({"ceiling"}),
        "The ceiling is made of the same material as the walls. It seems"
        +" to be cleaned regularly as there are no cobwebs or dust.\n");

    add_item(({"lamp", "lamps", "crystal"}),
        "A quartet of lamps hang from the beams supporting the ceiling."
        +" They are plain blackened iron suspended on nails. They provide"
        +" considerable light allowing for easy reading and writing.\n");

    add_item(({"nail", "nails"}),
        "Iron nails protrude from the ceiling beams where posters"
        +" or banners may have been hung in the past. The four largest"
        +" have iron lamps hanging from them.\n");
        
    add_item(({"quill", "quills"}),
        "Feathered quills sit on the table for use in writing posts.\n");

    add_item(({"inkpot", "inkpots"}),
        "Small pots of ink are available for writing notes.\n");
        
    add_item(({"sheets", "parchment", "sheets of parchment"}),
        "Sheets of parchment are neatly stacked for use in publishing"
        +" announcements on the board.\n");        

    add_item(({"door", "doors"}),
        "The door stands to the north and will take you back to the street.\n");   

    room_add_object(BOARDS_DIR + "phlan_board1");        

    reset_faerun_room();
        
    add_exit(ROOM_DIR + "road19", "north");

}


void
reset_faerun_room()
{
    set_searched(0);
}