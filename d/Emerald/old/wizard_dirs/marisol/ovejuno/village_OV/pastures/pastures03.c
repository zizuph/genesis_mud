/* Re Albi's pasture III
 * Coded by Marisol (04/29/98)
 * Modified by Marisol (08/05/98) to be used in the village of
 * Ovejuno in Emerald.
 * Copyright (c) Marisol Ramos 1998 */

#pragma strict_types
#include "defs.h"
#include "/d/Emerald/sys/macros.h"
#define SHEPHERD2 OV_VILLAGE_NPC + "shepherd02.c"
inherit OV_PASTURES;
#include <stdproperties.h>

object shepherd2;

void reset_room()
{
if(!objectp(shepherd2))
 {
 shepherd2=clone_object(SHEPHERD2);
 shepherd2->move(TO);
 shepherd2->command("emote walks in.");
 }
}

void
create_emerald_pasture()
{

    set_em_long("@@special_long@@This hills are part of the Cayeyi, the "+
        "mountain range where the village and its pasture are nested. "+
        "A shepherd is sitting in one of the outcrops with his staff "+
        "watching the sheep.");

    add_item(({"shepherd", "staff"}),
        "A boy, not more than twelve years old sits in a huge "+
        "rocky outcrop watching the sheep with a dreamy look on his face. "+
        "He holds a sturdy staff over his lap. Look like a very "+
        "good staff, maybe made of rowan wood.\n");


    add_exit("pastures02.c", "east");
    add_exit("pastures04.c", "south");
    add_exit("pastures01.c", "southeast");

    reset_room();

}
                                     
                                                     
string
special_long()
{
    object last_room = this_player()->query_prop(LIVE_O_LAST_ROOM);
    string filename;

    if (!last_room)
    {
    return "As you follow the hilly contour of the pasture, you can "+
    "see the dark bulk of the castle. ";
    }

    filename = file_name(last_room);

    if (filename == ("pasture/pastures02"))
    {

    return "As you follow the hilly contour of the pasture, you can "+
    "see the dark bulk of the castle. ";
    }

    if (filename == ("pasture/pastures04"))
    {
    return "The grassy parcel rises slowly over the hills, and here "+
    "and there, outcrops dot the pasture. ";
    }

    return "The grassy parcel rises slowly over the hills, and here "+
    "and there, outcrops dot the pasture. ";

    if (filename == ("pasture/pastures01"))
    {
    return "The grassy parcel rises slowly over the hills, and here "+
    "and there, outcrops dot the pasture. ";
    }

    return "The grassy parcel rises slowly over the hills, and here "+
    "and there, outcrops dot the pasture. ";

}


