/* /d/Faerun/guilds/black_flame/rooms/bf_boardroom.c
 *
 * Nerull 2022
 *
 */

inherit "/d/Faerun/guilds/black_flame/rooms/std/bf_std_room";

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "../guild.h";

/*
 * Function name: create_bf_room
 * Description  : Constructor, redefine this to configure your room
 */

public void
create_bf_room()
{
    seteuid(getuid());
    
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
    
    set_short("A room with a notice board");
    
    set_long("This room acts mainly as a corridor with exits "
    +"in all four walls, though there is a small alcove that "
    +"holds a notice board. It is a large wooden board, "
    +"made with dark sturdy wood. There are notes pinned to it, "
    +"and plenty of space for more, should you wish to add "
    +"one yourself. Many torches light up the room, and "
    +"especially the area around the notice board.\n");
    
    add_item(({"torch", "torches"}),
        "Pretty standard, wall-hung torches light up the area. "
        +"You’re fairly sure they contribute to the "
        +"heating as well.\n");
        
    add_item(({"wall", "walls"}),
        "The walls are smooth and white, made from some kind "
        +"of dense stone.\n");
        
    add_item(({"floor", "ground"}),
        "The floor is made up of very dark granite. In "
        +"contrast to the white walls, the floor almost "
        +"looks black.\n");
    
    
    add_exit(BF_ROOMS_DIR + "bf_start", "north");
    add_exit(BF_ROOMS_DIR + "bf_join", "south");
    add_exit(BF_ROOMS_DIR + "bf_corridor2", "east");
    add_exit(BF_ROOMS_DIR + "bf_corridor1", "west");
       
    room_add_object(BF_GUILD_DIR + "boards/bf_board");
    
    reset_faerun_room();
}
