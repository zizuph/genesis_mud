/* Path to the Lord's manor VI
 * Coded by Marisol (06/24/98)
 * Copyright (c) Marisol Ramos 1998 */

#include "defs.h"
#pragma strict_types
inherit "/d/Emerald/std/room";
inherit "/d/Emerald/lib/room_tell.c";
#include <stdproperties.h>
#include <cmdparse.h>
#include <macros.h>
#include "/d/Emerald/marisol/ovejuno/village_OV/castle_path/c2tells.h"

void
create_cpath_room()
{
}

void
create_emerald_room()
{

    int i;

    set_short("The castle's path."); 
    set_em_long("@@special_long@@"+
        "The path is not clean as befit to the demesne of an elven "+
        "lord. The grass, on both side of the path, is overgrown. The "+
        "castle doesn't look better either. Although imposing in its "+
        "size, looks also rundown, like its better days were far gone.");

    add_item("castle",
        "This structure doesn't deserve the name castle. It is more "+
        "like a palatial residence, but run down, far away from its "+
        "heyday. It seems that for the human villagers of Ovejuna this "+
        "old place looks like a castle, but for any elves this would be "+
        "an overstatement. But as a residence, this must has been a "+
        "charming place, like a fairy-tale castle of yore. Now, its "+
        "just the shadow of its better days.\n");


    add_item(({"path", "stone_hewn path", "ground"}),
        "The path is made of perfect cut square stones, set so "+
        "flawlessly together that you cannot see any fisure between "+
        "the stones. The path is covered with dirt. Dry and rotten "+
        "leaves carpetted the ground, giving the path an appearance "+
        "of neglect.\n");

    add_item("grass",
        "Green lush grass extend on both side of the path. Seems that "+
        "there is not a gardener in charge of this premise to maintain "+
        "the landscape.\n");                     


    add_exit("castle_path05.c", "southeast");
    add_exit("castle_path07.c", "northeast");


    reset_room();

    create_cpath_room();

    set_tell_time(60);
    for(i = 0; i <4; i++)
    add_tell(C2TELLS[random(sizeof(C2TELLS))]);

}                                    
string
special_long()
{
    object last_room = this_player()->query_prop(LIVE_O_LAST_ROOM);
    string filename;

    if (!last_room)
    {
        return "As you walk toward the castle, the quality of the path "+
               "changed from packed earth to a stone-hewn path. ";
    }

    filename = file_name(last_room);

    if (filename == (OV_PATH + "castle_path05"))
    {
    return "As you walk toward the castle, the quality of the path "+
           "changed from packed earth to a stone-hewn path. ";
    }

    if (filename == (OV_PATH + "castle_path07"))
    {
    return "As you walk away from the castle, you leave the stone-hewn "+
           "path. ";
    }

    return "As you walk away from the castle, you leave the stone-hewn "+
           "path. ";
}
