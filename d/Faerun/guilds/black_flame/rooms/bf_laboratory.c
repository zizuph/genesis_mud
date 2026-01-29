/* /d/Faerun/guilds/black_flame/rooms/bf_laboratory.c
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
    
    set_short("An alchemical laboratory");
    
    set_long("You are standing in a separate room, in what "
    +"looks like an addition to the otherwise circular shape. The "
    +"east and south walls are lined with shelves with various "
    +"jars and various alchemical paraphernalia. Herbs are hung "
    +"in batches from strings in the ceiling, which gives off "
    +"a pungent smell throughout the room. The room is "
    +"comfortably lit with torches everywhere.\n");
    
    add_item(({"roof", "ceiling"}),
        "The ceiling is almost hidden in the rows of various "
        +"dried herbs hung from leather strings attached to "
        +"many small hooks embedded in the ceiling.\n");
        
    add_item(({"shelf", "shelves", "paraphernalia"}),
        "Various vials, beakers, flasks, jars and strange "
        +"devices are organized neatly in the shelves. You also "
        +"see odd things like a cage filled with rats, dead "
        +"lizards, and some feathers, as well as pages with "
        +"various designs and scribbles.\n");
        
    add_item(({"recipe", "recipes", "pages", "papers",
        "designs", "scribbles"}),
        "The many pages strewn throughout the shelves seem "
        +"to be notes or part of alchemical recipes, but "
        +"it seems impossible to decipher the writings.\n");
        
    add_item(({"jar", "jars"}),
        "Jars, flasks and beakers stand organized neatly on "
        +"the shelves. The beakers and flasks are empty, "
        +"while the jars contain various coloured liquids "
        +"and powdered materials. Some metallic, some clearly "
        +"organic, some quite impossible to place.\n");
        
    add_item(({"slab", "bench", "workbench", "table"}),
        "A long slab of some hard stone is set here as a "
        +"workbench. It seems like it was cut from some "
        +"unknown rock with slivers of glimmering veins "
        +"woven into the dark rock. It is thick, heavy "
        +"and extremely hard, yet you see traces where "
        +"the surface is cracked and somehow melted. You "
        +"have no doubt it will last for years and years though.\n");
        
    
    add_exit(BF_ROOMS_DIR + "bf_train", "northwest");
       
    
    //room_add_object(BF_GUILD_DIR + "obj/bf_laboratory");
                      
    
    reset_faerun_room();
}