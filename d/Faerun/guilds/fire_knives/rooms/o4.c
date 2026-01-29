/* /d/Faerun/guilds/fire_knives/rooms/o4.c
 *
 * 
 * Nerull 2019
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

    set_short("Southeastern point in the sanctuary");
    
    set_long("The spacious, rectangular area revolves around a statue "
    +"centered atop a marble block in the middle of the scope of "
    +"this area. It seems unfinished and raw, yet the features are "
    +"already distinctive enough to make out. Spanning around it is "
    +"a circular concourse with six narrow passageways opening past "
    +"stoney archways that seemed to have sustained the passage of "
    +"time. Between each of them is a massive wall with an iron sconce "
    +"from which a thick, wooden torch hangs high, shedding off light "
    +"to the area. To the east you can hear the sounds of clanking pots "
    +"and thuds on what seems to be wood. A welcoming warmth "
    +"emanates from it and makes your stomach rumble, to the north the "
    +"concourse continues around the statue, while to the south a narrow "
    +"hallway leads into a trader's room.\n");

    add_item(({"area"}),
    "The area is spacious and rectangular in its form. "
    +"A dominant statue centered atop "
    +"a marble block is found in the middle of it, "
    +"while the concourse in which you are "
    +"in revolves around it in a circular fashion.\n");

    add_item(({"statue"}),
    "The statue seems unfinished, raw even, yet the "
    +"features are already distinctive "
    +"enough to depict a hooded man crouching down as "
    +"if ready to spring off in the "
    +"distance. A double belt crosses his back, "
    +"leaving low-hanging sheaths at each "
    +"side of his torso, while another can be "
    +"seen strapped around his left leg "
    +"standing a tad behind the other and "
    +"escaping the cover of his long robes. In "
    +"his hands is a loaded crossbow.\n");

    add_item(({"block"}),
    "The marble block serves as a pedestal for the "
    +"statue. At its base is an inscription.\n");

    /* Add action to 'read inscription', returning 'Altair Ibn-La'Ahad' */ 

    add_item(({"concourse"}),
    "The concourse revolves around the statue "
    +"in a circular fashion, its walls cut six times "
    +"by arching frames that allow passage into other areas.\n");

    add_item(({"passageways","passageway"}),
    "The passageways lead into six different "
    +"directions around the area, past arching frames. "
    +"From this point you can reach three of them: north "
    +"and west further along the circular "
    +"concourse, while to the east is what appears "
    +"to be a mess hall.\n");

    add_item(({"archway","archways","frames"}),
    "The archways crown the exits into other "
    +"areas covered from here by the darkness brought "
    +"forth by the absence of light.\n");

    add_item(({"paste","mortar","dark paste"}),
    "A solidified paste used to bind building blocks "
    +"such as these stones. Due to the "
    +"uneven nature of these random stones used "
    +"to fill decayed parts, their irregular "
    +"gaps have been filled with it.\n");

    add_item(({"air","coolness","cool air"}),
    "The air here is cool and fresh. The thick stone "
    +"of the walls, along with the torches "
    +"burning from sconces lining up the hallway, "
    +"protect you from the cold outside, "
    +"insulating the area.\n");

    add_item(({"torch","torches", "sconce", "sconces","flame","flames"}),
    "Thick wooden torches wrapped in leather hang "
    +"from each one of the bronze sconces found "
    +"lined up along the hallway, each one shedding "
    +"enough light to reach the next one. Here "
    +"the air seems to slap the flames gently, "
    +"and they respond in kind licking the soft "
    +"currents as they flow by. \n");

    add_item(({"ground","floor"}),
    "The floor appears smooth and well maintained. "
    +"It is made of flattened stone of various "
    +"types as a mosaic of sorts.\n");

    add_item(({"wall","walls", "stone","stones"}),
    "The walls are uneven, made of scraggly stone "
    +"worn out by the passage of time and the "
    +"harsh weather. Blackish patches of mold "
    +"are seen in the coldest areas, formed most "
    +"likely by the lack of ventilation. Lines here "
    +"and there have been scrawled on some "
    +"parts, but it's impossible to tell if they "
    +"are human made or simply the result of "
    +"scratches left behind.\n");

    add_exit(FIREKNIVES_ROOMS_DIR + "o3.c", "north");
    add_exit(FIREKNIVES_ROOMS_DIR + "mh.c", "east");
    add_exit(FIREKNIVES_ROOMS_DIR + "gen_shop.c", "south");
    add_exit(FIREKNIVES_ROOMS_DIR + "o5.c", "west");

    reset_faerun_room();
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
}
