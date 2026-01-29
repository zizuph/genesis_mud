/* /d/Faerun/guilds/warlocks/rooms/post.c
 *
 * Room in the guildhall.
 * Nerull 2018
 *
 */

#include "/d/Faerun/defs.h"
#include "../guild.h";
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <composite.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <tasks.h>
#include <macros.h>

inherit WARLOCK_STD_ROOM;
inherit "/d/Genesis/lib/post";


/*
 * Function name: create_warlock_room
 * Description  : Constructor, redefine this to configure your room
 */
public void
create_warlock_room()
{
    object board;

    add_prop(ROOM_I_INSIDE, 1);

    set_short("In a small improvised claystone post office");
    
    set_long("In a small improvised claystone post office. A few "
    +"wooden tables with lit oil lamps and chairs are the only "
    +"remarkable features here that occupy the room beside an odd "
    +"mural that pride the west wall. There are sheets of paper and "
    +"inkwells on the tables for warlocks to compose letters. Some warlocks "
    +"are sitting comfortable while reading incoming mail from afar "
    +"as well.\nExamine the mailreader for instructions.\n");
    
    add_item(({"ceiling", "roof"}),
    "The ceiling is rather smoothed over for edges, giving a rather "
    +"fine finish. Else, there is nothing remarkable about it.\n");
    
    add_item(({"ground", "floor"}),
    "The ground seems to be recently swept by someone, as it's "
    +"completely free for dust and other debris.\n");
    
    add_item(({"walls"}),
    "The walls here are smooth and contain no shelves or other "
    +"visible features with the exception of the west wall, which has "
    +"an odd mural painted on it.\n");
    
    add_item(({"west wall"}),
    "The smooth surface of the west wall contains an odd mural of sorts.\n");
    
    add_item(({"odd mural", "mural", "woman", "pallid-masked figure",
    "young woman"}),
    "The odd mural on the west wall depicts a hazed yellow pallid-masked "
    +"figure whispering something to a young woman wearing a "
    +"red dress. It seems the woman is depicted as being outright "
    +"terrified, or maybe overwhelmed with dreadful horror.\n");
    
    add_item(({"warlocks"}),
    "Several other warlocks sit here and either write or compose "
    +"letters. They are quite busy with what they are doing.\n");
    
    add_item(({"chair", "chairs", "wooden chairs", "wooden chair"}),
    "The simple chairs are made of wood, firmly bolted together "
    +"with iron nails. They appear relatively weak in construction, and "
    +"some have seen better days.\n");
    
    add_item(({"inkwell", "inkwells"}),
    "These small black metal containers keep ink and feathers for "
    +"the warlocks to use for writing letters.\n");
    
    add_item(({"paper", "sheets of paper", "sheet of paper"}),
    "They seem to be of ordinary quality and lies spread out "
    +"on the tables. Warlocks use these when they compose letters.\n");
    
    add_item(({"lamp", "lamps", "oil lamp", "oil lamps"}),
    "The oil lamps you see on the tables are made of bronze and "
    +"of simple construction. They provide enough light for "
    +"warlocks to compose and read letters.\n");

    add_item(({"table", "tables"}),
    "The tables are made of ornately carved wood. They are about waist " 
    +"high and are spread around the post office. The tables are used " 
    +"to write correspondences that are then mailed out. On top of each "
    +"table you see lit oil lamps, sheets of paper and inkwells lying "
    +"around.\n");
        
    add_item(({"wood", "ornately carved wood", "carved wood"}),
    "The wood is carved into ornate shapes that resemble vines and " 
    +"other organic shapes.\n");

    add_exit(WARLOCK_ROOMS_DIR + "hall03", "south");

    reset_faerun_room();
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
}


void
init()
{
    ::init();

    post_init();
}

void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    post_leave_inv(ob, to);
}
