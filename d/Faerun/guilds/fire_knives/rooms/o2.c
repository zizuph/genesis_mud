/* /d/Faerun/guilds/fire_knives/rooms/o2.c
 *
 * Nerull 2019
 *
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "../guild.h";

inherit FIREKNIVES_STD_ROOM;

public int
block_check()
{
    if (FIREKNIVES_MASTER->is_occ_fireknife(this_player()->query_name()) == 0)
    {
        if (!this_player()->query_wiz_level())
        {
            write("The guard dogs slowly pace until "
            +"they stand in front of you "
            +"while growling softly, their eyes "
            +"focused on yours. You decide "
            +"to reconsider your option and take a "
            +"few steps backwards.\n");

            tell_room(environment(this_player()), QCTNAME(this_player()) 
            +" steps backwards from the dogs as they move in front of "
            + this_player()->query_possessive()
            +", blocking the way.\n", this_player());

            return 1;
        }
    }
      
    write("The guard dogs raise their heads to look at you, then look down "
    +"and turn around in a submissive gesture.\n");
    
    tell_room(environment(this_player()), QCTNAME(this_player())
    +" receives a furtive glance from the dogs before they lower "
    +"their head and turn around in a submissive gesture.\n", this_player());
        
    return 0;
}


/*
 * Function name: create_warlock_room
 * Description  : Constructor, redefine this to configure your room
 */

public void
create_fireknives_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    set_short("At an end of the long corridor");

    set_long("The corridor comes to an intersection "
    +"past a sharp turn, opening "
    +"two new passages: one to the west along "
    +"a straight hall and a shorter one "
    +"to the south past an uneven archway. The "
    +"coolness emanating from the stone "
    +"provides a sense of comfort as it is combined "
    +"with the gentle lapping of the "
    +"torches' flames licking at the hall in a "
    +"flickering dance with each drift of "
    +"air. A solid, dark paste with protruding "
    +"pieces of multi colored stones adorn "
    +"random parts of the wall as if replacing "
    +"broken bits and pieces from decay or "
    +"a more immediate type of violence. A pair of guard "
    +"dogs patrol the area.\n");

    add_item(({"paste","mortar","dark paste"}),
    "A solidified paste used to bind building blocks "
    +"such as these stones. Due to the "
    +"uneven nature of these random stones used "
    +"to fill decayed parts, their irregular "
    +"gaps have been filled with it.\n");
    
    add_item(({"dog", "dogs", "guard dog", "guard dogs", 
    "vicious guard dogs", "vicious dogs"}),
    "These pair of vicious wolf-like grey dogs paces about the "
    +"area, sniffing and carefully watching the movements "
    +"of any nearby creature. They appear to be guarding "
    +"the entrance to the south.\n");

    add_item(({"intersection"}),
    "The intersection is formed by the meeting of "
    +"various possible corridors extending "
    +"in various directions, from here leading to "
    +"the west along a straight hall, while "
    +"another to the south goes into a narrow one.\n");

    add_item(({"air","coolness","cool air"}),
    "The air here is cool and fresh. The thick "
    +"stone of the walls, along with the torches "
    +"burning from sconces lining up the hallway, "
    +"protect you from the cold outside, "
    +"insulating the area.\n");

    add_item(({"torch","torches", "sconce", "sconces","flame","flames"}),
    "Thick wooden torches wrapped in leather hang "
    +"from each one of the bronze sconces found "
    +"lined up along the hallway, each one shedding "
    +"enough light to reach the next one. Here "
    +"the air seems to slap the flames gently, and "
    +"they respond in kind licking the soft "
    +"currents as they flow by. \n");
    
    add_item(({"ground","floor"}),
    "The floor appears smooth and well maintained. It "
    +"is made of flattened stone of various "
    +"types as a mosaic of sorts.\n");

    add_item(({"wall","walls", "stone","stones"}),
    "The walls are uneven, made of scraggly stone "
    +"worn out by the passage of time and the "
    +"harsh weather. Blackish patches of mold are "
    +"seen in the coldest areas, formed most "
    +"likely by the lack of ventilation. Lines here "
    +"and there have been scrawled on some "
    +"parts, but it's impossible to tell if they are "
    +"human made or simply the result of "
    +"scratches left behind.\n");

    add_item(({"hallway","passage","corridor"}),
    "The hallway extends from here to the southwest "
    +"under uneven archways of heavy stone.\n");

    add_item(({"archway","archways"}),
    "The ancient archways are rather uneven, creating "
    +"a sense of disatisfaction. It is merely "
    +"superficial, though, due to the discoloration of the stone.\n");

    add_exit(FIREKNIVES_ROOMS_DIR + "o1.c", "northeast");
    add_exit(FIREKNIVES_ROOMS_DIR + "o3.c", "south", block_check);
    add_exit(FIREKNIVES_ROOMS_DIR + "o7", "west");

    reset_faerun_room();
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
}
