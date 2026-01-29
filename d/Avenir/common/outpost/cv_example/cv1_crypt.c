/* /d/Faerun/guilds/vampires/rooms/cv1_crypt.c
 *
 * Nerull 2021
 *
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "../guild.h";

inherit VAMPIRES_STD_ROOM;


/*
 * Function name: create_vampires_room
 * Description  : Constructor, redefine this to configure your room
 */

public void
create_vampires_room()
{
    seteuid(getuid());
    
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    
    remove_prop(ROOM_M_NO_TELEPORT);
    remove_prop(ROOM_M_NO_TELEPORT_TO);
    remove_prop(ROOM_M_NO_TELEPORT_FROM);

    set_short("crypt");
    
    set_long("Completely carved from surrounding stone, this room "
    +"lacks any ornamentation or adornment and serves merely as a "
    +"well-used warehouse for coffins. There are numerous biers "
    +"positioned purposefully on a multi-level dais. There is a "
    +"thick layer of mist roughly a hand's width above the floor, "
    +"occluding all view of it. The mist serves as a barrier to "
    +"any infiltrating heat, leaving behind an intentionally cold "
    +"feeling. The walls are hewn of the same stone and are "
    +"smooth and polished, lacking any other discerning details.\n");
    
    add_item(({"stone" }),
        "The stone of the entire room is a flat grey in color "
        +"and has been polished smooth.\n");

    add_item(({"biers" }),
        "Different biers, designed to support a coffin, are arranged "
        +"on a mult-tiered dais. They seem to be made of stone.\n");
        
    add_item(({"dais" }),
        "The mult-tiered levels of stone, seemingly carved from the stone "
        +"itself, serve as a ranking and racking system for the various "
        +"biers.\n");
        
    add_item(({"mist" }),
        "A deep cold mist lay above the floor blocking view and "
        +"serving as a barrier for any infiltrating heat.\n");
        
    add_item(({"floor", "ground" }),
        "The floor is indiscernable because of the thick layer "
        +"of mist hovering above it.\n");

    add_item(({"walls", "walls"}),
        "The walls are hewn from the same grey stone as the rest "
        +"of the chamber, polished smooth and without detail.\n");
           
    add_item(({"doorway" }),
        "An opening cut into the middle of the west wall leading "
        +"into the entryway.\n");
                      
     add_item(({"ceiling", "roof" }),
       "The ceiling seems to be wrought from stone and polished "
       +"to a smooth luster.\n");
                      

    add_exit(VAMPIRES_GUILD_DIR + "rooms/cv1_entryway", "west");
    
    reset_faerun_room();
}