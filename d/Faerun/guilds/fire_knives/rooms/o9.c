/* /d/Faerun/guilds/fire_knives/rooms/o9.c
 *
 * 
 * Room south of the start room and north of the racks
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

    set_short("At the western end of a long corridor");

    set_long("Its path marked by burning torches, from here the long "
    +"corridor extends apparently infinitely towards the east. To your "
    +"west is a rough wall of stone with a rectangular section broken "
    +"into and closed off by "
    +"a wooden plaque. A soft, cold draft enters "
    +"the corridor from it, sucking "
    +"some of the accumulated humidity outwards. To "
    +"the north and south, the "
    +"corridor diverges into narrow openings. The "
    +"coolness emanating from "
    +"the stones around you provide a sense of "
    +"comfort as it is combined with "
    +"the gentle lapping of the torches' flames "
    +"licking at the hall in a "
    +"flickering dance with each drift of air. A "
    +"solid, dark paste with protruding "
    +"pieces of multi colored stones adorn "
    +"random parts of the wall as if replacing "
    +"broken bits and pieces from decay or a "
    +"more immediate type of violence.\n"); 

    add_item(({"plaque", "wooden plaque"}),
    "The wooden plaque on the western wall is loosely "
    +"attached to it, covering an "
    +"opening of rectangular shape which is wide enough "
    +"for your eyes to see through. "
    +"The draft hammers the plaque constantly, making it "
    +"rise and fall against the "
    +"winds' constant buffeting.\n");

    add_item(({"opening","openings"}),
    "Which one of the openings, the one to your south or to your north?\n");

    add_item(({"north opening","northern opening","opening to the north"}),
    "The opening to the north leads into what "
    +"appears to be resting chambers. The "
    +"dim light not allowing you to view more details from here.\n");

    add_item(({"south opening","southern opening","opening to the south"}),
    "The southern opening leads into a brightly lit "
    +"room which appears to be an armory "
    +"by the lines of weapons adorning the walls.\n");

    add_item(({"paste","mortar","dark paste"}),
    "A solidified paste used to bind building blocks "
    +"such as these stones. Due to the "
    +"uneven nature of these random stones "
    +"used to fill decayed parts, their irregular "
    +"gaps have been filled with it.\n");

    add_item(({"air","coolness","cool air"}),
    "The air here is cool and fresh. The thick "
    +"stone of the walls, along with the torches "
    +"burning from sconces lining up the hallway, "
    +"protect you from the cold outside, "
    +"insulating the area.\n");

    add_item(({"torch","torches", "sconce", "sconces","flame","flames"}),
    "Thick wooden torches wrapped in leather "
    +"hang from each one of the bronze sconces found "
    +"lined up along the hallway, each one shedding "
    +"enough light to reach the next one. Here "
    +"the air seems to slap the flames gently, and "
    +"they respond in kind licking the soft "
    +"currents as they flow by. \n");
    
    add_item(({"ground","floor"}),
    "The floor appears smooth and well maintained. "
    +"It is made of flattened stone of various "
    +"types as a mosaic of sorts.\n");

    add_item(({"wall","walls", "stone","stones"}),
    "The walls are uneven, made of scraggly stone worn "
    +"out by the passage of time and the "
    +"harsh weather. Blackish patches of mold are "
    +"seen in the coldest areas, formed most "
    +"likely by the lack of ventilation. Lines here "
    +"and there have been scrawled on some "
    +"parts, but it's impossible to tell if they "
    +"are human made or simply the result of "
    +"scratches left behind. On the west wall is "
    +"a wooden plaque covering an opening from "
    +"which a strong, cold draft enters the hallway.\n");

    add_item(({"hallway","passage","corridor"}),
    "The hallway extends from here to the east under uneven "
    +"archways of heavy stone.\n");

    add_item(({"archway","archways","symbol"}),
    "The ancient archways are rather uneven, creating a "
    +"sense of disatisfaction. It is merely "
    +"superficial, though, due to the discoloration "
    +"of the stone. The one leading to the south "
    +"bears the scratched symbol of a knife wrathed in flames. \n");

    add_exit(FIREKNIVES_ROOMS_DIR + "o8.c", "east");
    add_exit(FIREKNIVES_ROOMS_DIR + "sr1.c", "north");
    add_exit(FIREKNIVES_ROOMS_DIR + "ra1.c", "south");
    add_exit(FIREKNIVES_ROOMS_DIR + "o10", "west");
    
    // Redundant. Info moved and updated in the library. Nerull 2019.
    //room_add_object(FIREKNIVES_OBJ_DIR + "fireknives_book");
    
    room_add_object(FIREKNIVES_BOARDS_DIR + "trainee_board");

    reset_faerun_room();
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
}
