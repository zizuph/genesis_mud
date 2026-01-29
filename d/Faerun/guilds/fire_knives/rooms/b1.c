/* /d/Faerun/guilds/fire_knives/rooms/b1.c
 *
 * Hallway between reception and Inquisitor's room
 *
 * Nerull 2019
 *
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "../guild.h";

inherit FIREKNIVES_STD_ROOM;

public int
block_check()
{
    if (present("fireknives_visit_object_mentor", this_player()))
    {
       write("The guard dogs raise their heads to look at you "
       +"suspiciously, but they "
       +"let you pass.\n");
        
        tell_room(environment(this_player()), QCTNAME(this_player())
        +" receives a suspicious glance from the guard dogs, but "
        +"is let through.\n", this_player());
            
        return 0;
    }  
    
    if (FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()) ||
        FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()))
    {
        write("The guard dogs raise their heads to look "
        +"at you, then look down "
        +"and turn around in a submissive gesture.\n");
    
        tell_room(environment(this_player()), QCTNAME(this_player())
        +" receives a furtive glance from the dogs before they lower "
        +"their head and turn around in a "
        +"submissive gesture.\n", this_player());
        
        return 0;
    }
      
    write("The guard dogs slowly pace until they stand in front of you "
    +"while growling softly, their eyes focused on yours. You decide "
    +"to reconsider your option and take a few steps backwards.\n");

    tell_room(environment(this_player()), QCTNAME(this_player()) 
    +" steps backwards from the dogs as they move in front of "
    + this_player()->query_possessive()
    +", blocking the way.\n", this_player());
        
    return 1;
}


/*
 * Function name: create_warlock_room
 * Description  : Constructor, redefine this to configure your room
 */

public void
create_fireknives_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    set_short("A dark hallway");
    set_long("A simple hallway extending west to the conference chamber "
    +" Its walls are bare save for the "
    +"torches resting in sconces in its walls. "
    +"A pair of guard dogs is resting here. "
    +"To the east the halls come to a halt upon a door. \n");    

    add_item(({"floor"}),
    "The room is covered in a simple black carpet the muffles all sound "
    +"and provides protection against the coldness "
    +"of the stone underneath it.\n");
    
    add_item(({"dog", "dogs", "guard dog", "guard dogs", 
    "vicious guard dogs", "vicious dogs"}),
    "These pair of vicious wolf-like grey dogs paces about the "
    +"area, sniffing and carefully watching the movements "
    +"of any nearby creature. They appear to be guarding "
    +"the entrance to the east.\n");
    
    add_item(({"stone","stones"}),
    "The stone of the floor of the old keep is covered in carpets.\n");
    
    add_item(({"sconces","sconce"}),
    "The sconces hang on the walls, holding torches.\n");
    
    add_item(({"torches","torch"}),
    "The torches hang on the sconces. They are currently lit.\n");
    
    add_item(({"walls","wall"}),
    "The walls of the chamber are simple and bare, devoid of decorations.\n");
    
    add_item(({"door"}),
    "The door lies to the east. It bears the symbol of "
    +"a pen with an eye in its center.\n");

    add_exit(FIREKNIVES_ROOMS_DIR + "inquisitor.c", "east", block_check);
    add_exit(FIREKNIVES_ROOMS_DIR + "reception.c", "west");
    reset_faerun_room();
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
}
