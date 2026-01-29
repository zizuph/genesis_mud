/* /d/Faerun/guilds/black_flame/rooms/bf_rackroom2.c
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
    
    set_short("A room with racks and sofa");
    
    set_long("This room is large and luxurious. The floor "
    +"is covered from wall to wall with an expensive looking rug, "
    +"and in the west wall you see a fireplace. In front of "
    +"the fireplace there is a sitting group with a small "
    +"oak table, a leather sofa and two matching comfortable "
    +"looking armchairs. On the south, north and east "
    +"wall, there are torches lit. Along the north wall is a "
    +"rack made of mahogany with large mahogany-framed glass "
    +"doors allowing for full view of what's inside.\n");
    
    add_item(({"torch", "torches"}),
        "Pretty standard, wall-hung torches light up the area. "
        +"You’re fairly sure they contribute to the "
        +"heating as well.\n");
        
    add_item(({"wall", "walls"}),
        "The walls are smooth and white, made from some kind "
        +"of dense stone. Along the north wall is a mahogany "
        +"weapon rack.\n");
        
    add_item(({"floor", "ground"}),
        "The floor is made up of very dark granite. In contrast "
        +"to the white walls, the floor almost looks black. "
        +"Most of it is covered by an expensive looking "
        +"rug though.\n");
        
    add_item(({"rug"}),
        "This large rug is eggshell-coloured. It looks quite "
        +"sturdy, but still luxurious. In the middle of the "
        +"carpet a large twisting black flame is embroidered.\n");
        
    add_item(({"sofa"}),
        "A comfortable looking leather sofa standing next to "
        +"the fireplace. Looks like a good place to sit.\n");
        
    add_item(({"armchair", "armchairs"}),
        "These are large and luxurious leather armchairs, "
        +"oxblood coloured. They are probably quite comfortable "
        +"to sit in.\n");
        
    add_item(({"fireplace"}),
        "a crackling fire is burning in the fireplace, "
        +"spreading warmth in the room.\n");
        
    
    add_exit(BF_ROOMS_DIR + "bf_rackroom1", "south");
       
    
    room_add_object(BF_GUILD_DIR + "obj/bf2_rack");
                      
    
    reset_faerun_room();
}