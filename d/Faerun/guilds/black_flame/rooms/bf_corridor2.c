/* /d/Faerun/guilds/black_flame/rooms/bf_corridor2.c
 *
 * Nerull 2022
 *
 */

inherit "/d/Faerun/guilds/black_flame/rooms/std/bf_std_room";

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "../guild.h";

/*
 * Function name: create_warlock_room
 * Description  : Constructor, redefine this to configure your room
 */

public void
create_bf_room()
{
    seteuid(getuid());
    
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
    
    set_short("A bend in the Temple of Kossuth");
    
    set_long("You find yourself in a pretty empty, windowless, "
    +"curved hallway. There’s not much to notice here, apart "
    +"from the many torches on both sides lighting the area. "
    +"The curved nature of the hallway completely hides what "
    +"lies around the corner, but you can proceed west "
    +"or southeast to find out.\n");
    
    add_item(({"torch", "torches"}),
        "Pretty standard, wall-hung torches light up the "
        +"area. You’re fairly sure they contribute to the "
        +"heating as well.\n");
        
    add_item(({"wall", "walls"}),
        "The walls are smooth and white, made from some kind "
        +"of dense stone.\n");
        
    add_item(({"floor", "ground"}),
        "The floor is made up of very dark granite. In "
        +"contrast to the white walls, the floor almost "
        +"looks black.\n");
        
    
    add_exit(BF_ROOMS_DIR + "bf_boardroom", "west");
    add_exit(BF_ROOMS_DIR + "bf_train", "southeast");
                          
    
    reset_faerun_room();
}