/* /d/Faerun/guilds/black_flame/rooms/bf_start.c
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
    
    set_short("Sleeping chambers");
    
    set_long("This chamber has got alcoves carved into the "
    +"walls with bunks in them. Six beds in each wall to the "
    +"east, west and north. A heavy rug covers the floor, "
    +"and sounds from the rest of the complex are surprisingly "
    +"well muffled by the heavy curtain covering the south "
    +"exit. Some dedicated Zealots have found it "
    +"convenient to <start here>.\n");
    
    add_item(({"chamber"}),
        "The chamber is kept clean and clear. The center "
        +"area is dominated by a rug on the floor and obviously "
        +"the bunks carved into the walls.\n");
        
    add_item(({"wall", "walls"}),
        "The walls are solid stone while at the same time "
        +"don’t feel very cold. The room is lit by the same "
        +"kind of torches as in the rest of the temple, "
        +"albeit fewer to cater to the sleeping Zealots.\n");
        
    add_item(({"bunk", "bunks", "bed", "beds"}),
        "While the mattresses hardly are the pinnacle of luxury, "
        +"the thick straw in them will provide enough comfort for "
        +"a dedicated Zealot.\n");
        
    add_item(({"curtain"}),
        "The south exit is covered with a heavy, dark curtain, "
        +"which dampens a lot of the sound from the rest of the "
        +"temple, making this room fairly silent and peaceful.\n");
        
    
    add_exit(BF_ROOMS_DIR + "bf_boardroom", "south");
       
   
    reset_faerun_room();
}


int
do_start(string str)
{
    if (str != "here")
    {
        write("<start here>, perhaps?\n");
        return 1;
    }

    if (BF_MASTER->is_lay_bf(this_player()->query_name()))
    {
        this_player()->set_default_start_location(file_name(this_object()));
        write("From now on, you will start here when entering the game.\n");
        return 1;
    }
    
    write("You are not a member of this guild!\n");
    return 1;
}


void init()
{
    ::init();
    add_action(do_start, "start");
}