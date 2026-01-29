/* /d/Faerun/guilds/fire_knives/rooms/o0.c
 *
 * Nerull 2019
 *
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "../guild.h";

inherit FIREKNIVES_STD_ROOM;


/*
 * Function name: create_warlock_room
 * Description  : Constructor, redefine this to configure your room
 */

public void
create_fireknives_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    set_short("At the top of the stone stairway");
    
    set_long("Leading down below into the darkness "
    +"are thick and wide steps that seem "
    +"more natural than made made. The steps at the "
    +"top seem clean and cared for even "
    +"if the passage of time has left its mark on "
    +"them, chipped and cracked on some "
    +"areas as they are. From below rises an acrid "
    +"smell that drifts in the coolness "
    +"of the air in this first floor, blowing off "
    +"through the hallway that extends to the "
    +"southwest in a passage wide enough for two "
    +"to walk side by side through archways "
    +"at each intersection. The ground seems "
    +"polished and smooth, while the walls to each "
    +"side are uneven by the aging of the great "
    +"stones they are made of.\n");

    add_item(({"darkness"}),
    "Down below where the stairs lead to, everything "
    +"seems covered in a dark gloom "
    +"that hinders your view. The steps disappear "
    +"into it as they enter it, along "
    +"with any clear notion of what lies beyond.\n");

    add_item(({"steps"}),
    "The steps are thick and wide, made of a stone "
    +"formation that appears more natural "
    +"than man made. They are clean and well "
    +"cared for, if old and worn out by time.\n");

    add_item(({"chips","cracks"}),
    "Here and there you find tiny chips and cracks "
    +"on the stone steps, evidencing the "
    +"passage of time.\n");

    add_item(({"smell","acrid smell"}),
    "The smell comes up from below and mixes with "
    +"the cool air here, disappearing, but "
    +"not without leaving its imprint on your senses.\n");

    add_item(({"air","coolness","cool air"}),
    "The air here is cool and fresh. The thick "
    +"stone of the walls, along with the torches "
    +"burning from sconces lining up the hallway, "
    +"protect you from the cold outside, "
    +"insulating the area.\n");

    add_item(({"torch","torches", "sconce", "sconces"}),
    "Thick wooden torches wrapped in leather hang "
    +"from each one of the bronze sconces found "
    +"lined up along the hallway, each one shedding "
    +"enough light to reach the next one.\n");
    
    add_item(({"ground","floor"}),
    "The floor appears smooth and well maintained. "
    +"It is made of flattened stone of various "
    +"types as a mosaic of sorts.\n");

    add_item(({"wall","walls", "stone","stones"}),
    "The walls are uneven, made of scraggly stone "
    +"worn out by the passage of time and the "
    +"harsh weather. Blackish patches of mold "
    +"are seen in the coldest areas, formed most "
    +"likely by the lack of ventilation. Lines "
    +"here and there have been scrawled on some "
    +"parts, but it's impossible to tell if they "
    +"are human made or simply the result of "
    +"scratches left behind.\n");

    add_item(({"hallway","passage","corridor"}),
    "The hallway extends from here to the southwest "
    +"under uneven archways of heavy stone.\n");

    add_item(({"archway","archways"}),
    "The ancient archways are rather uneven, creating "
    +"a sense of disatisfaction. It is merely "
    +"superficial, though, due to the discoloration of the stone.\n");

    add_exit(FIREKNIVES_ROOMS_DIR + "o2.c", "southwest");
    add_exit(FIREKNIVES_ROOMS_DIR + "c1.c", "down");

    reset_faerun_room();
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
}
