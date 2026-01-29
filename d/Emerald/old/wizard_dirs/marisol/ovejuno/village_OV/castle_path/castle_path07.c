/* Path to the Lord's manor VII
 * Coded by Marisol (06/30/98)
 * Modified by Marisol (07/10/98) for the Castle's path in Emerald.
 * Copyright (c) Marisol Ramos 1998 */

inherit "/d/Emerald/std/room";
#include "defs.h"
#pragma strict_types
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

    set_short("The castle's entrance.");
    set_em_long("@@special_long@@ Piedbald marbles columns stand guard "+
        "while supporting the portico's wooden roof.");

    add_item(({"path", "stone_hewn path"}),
        "The path is made of perfect cut square stones, set so "+
        "flawlessly together that you cannot see any fisure between "+
        "the stones. The path is covered with dirt. Dry and rotten "+
        "leaves carpeted the ground, giving the path an appearance "+
        "of neglect.\n");


    add_item("castle",
        "To call this residence a castle is a little exagerated. "+
        "But as the official residence of the elven lords from "+
        "Telberin, is an impossing, although neglected residence. "+
        "The marble, instead to be white gleaming, is all covered "+
        "with dark lichen, mold and mildew, making the stone looks "+
        "like a cancerous skin, sucking the sunlight instead to "+
        "reflect it. The simple human villagers of Ovejuno think of "+
        "this structure as one of the fabulous castles of fairy "+
        "tales. But, for the lords holding this post, high in the "+
        "mountains, this residence although beautiful as elven "+
        "residences are expected, is a far cry to a castle. Indeed "+
        "this residence is the proof of the lowly status of this post "+
        "and the present condition will insult any elven sensibilities. "+
        "Still this residence in its heyday would have been quite "+
        "enchanting.\n");

    add_item(({"porch", "roof", "wooden roof", "portico"}),
        "A old portico stands majestic, even in its decay, in front of "+
        "you. Dirty marble columns support a wooden porch. The porch "+
        "is a triangular structure called garble, a favorite "+
        "among the nobles in Telberin quite a long time ago. The roof "+
        "of the porch rests over the marble columns that enclosed the "+
        "steps. The wooden structure seems to have been something in "+
        "its glory days, you can still spy beautiful carvings in the "+
        "wood painted with what was once white paint. Vines and other "+
        "plants creep over the top of the porch, some of them creeping "+
        "around the columns. An once proud residence now languishes "+
        "here.\n");

    add_item(({"columns", "marble columns", "lichen", "mold", "mildew"}),
        "These stout marble columns support the roof of the porch. The "+
        "marble surface is hard to see because unhealthy lichen, mold "+
        "and mildew overlay the once gleaming stone. Now a motley of "+
        "white, grey, black and green cover the surface of the columns "+
        "giving it a look of disease and decay.\n");

    add_item(({"carvings", "wooden carvings"}),
        "As you look the carving you can make up the form of fade "+
        "roses and leaves.\n");

    add_item(({"marble steps", "steps"}),
        "The marble steps look as neglected as the marble columns. "+
        "Cracks crisscross the once beautiful white marble. Dirt "+
        "and rotten leaves add to the abandoned of the steps. "+
        "You wonder if the castle lacks people to maintance this "+
        "place clean or if just the excentric predilection of the "+
        "lord of the house.\n");

    add_item(({"door", "oak door", "huge oak door"}),
        "The door surprisingly is free of vines and dirt. It stands "+
        "proudly, old but magnificent. A copper door knocker is set "+
        "at the center of the door.\n");

    add_item(({"copper door knocker", "door knocker"}),
        "A ugly copper face sticks its tongue at you. Through its nose "+
        "an copper ring rests waiting for someone to clang it.\n");

    add_exit("castle_path06.c", "southwest");


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
        return "The path ends in front of the castle. Marble steps "+
           "rises under a portico to the front door. Inside the "+
           "portico, it is dark and the air is damp. A huge oak door "+
           "stands tall. A metal door knocker waits silently for "+
           "someone to use it.";
    }

    filename = file_name(last_room);

    if (filename == (OV_PATH + "castle_path06"))
    {
    return "The path ends in front of the castle. Marble steps "+
           "rises under a portico to the front door. Inside the "+
           "portico, it is dark and the air is damp. A huge oak door "+
           "stands tall. A metal door knocker waits silently for "+
           "someone to use it.";
    }

    if (filename == (OV_PATH + "(doorentrance)"))
    {
    return "You leave the marble steps and walk away from the castle. "+
           "The portico is still dark and damp. The oak door remind "+
           "tall and the solitary door knocker smiles mysteriously.";

    }

    return "You leave the marble steps and walk away from the castle. "+
           "The portico is still dark and damp. The oak door remind "+
           "tall and the solitary door knocker smiles mysteriously.";

}
