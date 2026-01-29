/*
 * Fire Knives, Crow's club house / lodging
 *
 * Nerull 2020
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <macros.h>
#include <money.h>
#include <stdproperties.h>
#include <terrain.h>

inherit FAERUN_INDOORS_BASE;


#define WIZARD_ENTRY_BACKROOM_LOG(x,y)   write_file("/d/Faerun/private/restrictlog/guilds/fire_knives/" + x, extract(ctime(time()), \
                            4, 15) +" "+ y )


void
create_indoor_room()
{
    set_short("The Crow's Hideout");
	
    set_extraline("In this hidden room behind the curtains of the small "
    +"hut reigns an atmosphere of quietness and solitude. The wooden "
    +"walls surrounding the area are sturdy and look freshly made. "
    +"Crowning the walls, a domed ceiling seems to absorb the dim "
    +"light filtered by the curtains from the pub. Simplicity would "
    +"define this room at best. A place where whispers are absorbed "
    +"by the very air and where it is best not to linger too long once "
    +"business is concluded. A pair of guard dogs are watching "
    +"you carefully..");

    add_item(({"walls", "wall"}),
    "The wooden walls are sturdy and effective.\n");
    
    add_item(({"roof", "ceiling"}),
    "The domed ceiling crowns the walls and seems alive by virtue "
    +"of the shadows cast from the dim light.\n");

    add_item(({"dog", "dogs", "pair of guard dogs", "guard dogs"}),
    "Powerful, attentive and vicious, these guard dogs ensure the "
    +"absolute peace in the room.\n");

    add_item(({"curtains"}),
    "The heavy curtains divide this hideout from the pub. Thick "
    +"and heavy, they muffle all sounds from escaping.\n");

    add_item(({"pub"}),
    "Behind the curtains is the pub where you safely go back.\n");

    add_item(({"lights", "light"}),
    "The light from the pub is dimmed by the thick and heavy"
    +"curtains separating the rooms. Only enough filters to "
    +"see the contour of your peers.\n");
    
    add_item(({"floor", "ground"}),
        "The floor is swept clean. It is made of hard-packed dirt and is oddly warm.\n");

    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
	
    add_prop(ROOM_I_NO_ATTACK, "The guard dogs are watching your every move. You "
    +"would rather try violent behaviours elsewhere!\n");
	
    add_prop(ROOM_I_NO_STEAL, "The guard dogs are watching your every move. You "
    +"would rather try your luck elsewhere.\n");
	
	room_add_object("/d/Faerun/guilds/fire_knives/obj/" + "crows_rack");
	room_add_object("/d/Faerun/guilds/fire_knives/boards/" + "crows_board");
	
    add_exit(HR_DIR + "hut_food", "south");

    reset_faerun_room();
}


void
reset_faerun_room()
{
 
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    if (interactive(ob))
    {
        if (ob->query_wiz_level())
        {
            WIZARD_ENTRY_BACKROOM_LOG("wizard_entry_backroom_log",
            "The immortal " +ob->query_name() 
            +" entered the Fire Knives Crows club room in the village.\n");
            
            ob->catch_tell(" >>> YOUR ENTRY HAS BEEN LOGGED. UNLESS YOU HAVE BUSINESS "
            +"HERE, PLEASE IMMEDATELY MOVE ELSEWHERE! <<<\n");
        } 
    }
}


void
init()
{
    ::init();
    //add_action("do_read", "read", 0);
}
