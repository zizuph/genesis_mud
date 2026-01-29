/* 
 * Room where the door to the Ritual Chamber resides - Thanar Cathedral
 * /d/Kalad/common/guilds/new_thanar/ritual_entrance
 */

#include "../local.h"

inherit THANAR_BASE_STD; 

/*
 * Function name: create_std_thanar()
 * Description  : Constructor for the room, modify this to change room.
 */
create_std_thanar()
{
    set_short("Before the Ritual Chamber");
    set_long("This room is not like the others within this dungeon "
    + "basement. While the majority of the rest of this area is used "
    + "to creatively question prisoners, this room appears to be one "
    + "that is held in some regard. While it is ancient, and appears "
    + "to be why the Cathedral was built upon this location, it seems "
    + "new. The door within this room is polished and gilded. It stands "
    + "strong before you. The rest of the room is mostly barren drawing "
    + "all attention to the door.\n");  
    
    add_item(({"walls", "wall", "the walls", "the wall"}), "Constructed from "
        + "some unknown material, the walls are bare and appear to have been"
        + "formed naturally. Lanterns have been attached to the walls as with "
        + "the rest of the area but otherwise the walls are bare.\n");
    add_item(({"floor", "floors"}), "The floors are of an unknown material "
        + "and appear to have existed for eternity. They are barren and "
        + "unnaturally smooth.\n");
           
    add_exit(BASE + "se_basement5","northwest");
    add_exit(BASE + "sw_basement5","northeast");
    
    clone_object(DOORS + "ritual_door")->move(TO);
        
    //sets the no exit message
    set_no_exit_msg(get_all_no_exits(({"nw","ne","s"})),
    "The walls block your path.\n");
    reset_room();
}

