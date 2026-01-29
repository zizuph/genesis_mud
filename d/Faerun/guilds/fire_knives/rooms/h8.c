/* /d/Faerun/guilds/fire_knives/rooms/h8.c
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
    if (FIREKNIVES_MAPPINGS->query_assassin_rank(this_player()->query_name()) <= MAX_PROSPECT_RANK)
    {
        if (!this_player()->query_wiz_level())
        {
            write("The guard dogs slowly pace until "
            +"they stand in front of you "
            +"while growling softly, their eyes "
            +"focused on yours. You decide "
            +"to reconsider your option and take "
            +"a few steps backwards.\n");

            tell_room(environment(this_player()), QCTNAME(this_player()) 
            +"steps backwards from the dogs as they move in front of "
            +this_player()->query_possessive()
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

    set_short("At the top of the stairs to the first floor");

    set_long("Standing in front of a long winding "
    +"stairway leading downwards into "
    +"an eerie spiral lit by high hanging "
    +"torches that flicker slightly against the vague "
    +"draft coming from downstairs. To the "
    +"north the hallway barely widens in the "
    +"form of a cone that seems to embrace a "
    +"wide marbel column dominating the "
    +"center of the floor. One narrow passageway "
    +"opens to the west from "
    +"here into into a spacious yet "
    +"quiet chamber. Soft carpets begin at "
    +"the base of the stairs, covering "
    +"the otherwise cold, stone floor.\n"); 

    add_item(({"column","marble column"}),
    "The column isn't quite clearly visible from here in much detail, but "
    +"it is obviously thick and seems to dominate the area, succumbing all "
    +"around it to its frame.\n");

    add_item(({"wall","walls"}),
    "The stone cold walls seem smooth and clean, "
    +"the distances between its parts "
    +"marked only by equidistant sconces in which "
    +"torches are placed. In between "
    +"them is a thickly framed high portrait.\n");

    add_item(({"sconces","sconce"}),
    "The sconces are placed at an equal distant to "
    +"each other along the walls that "
    +"extend from the bottom of the stairs "
    +"southwards. Inside each one of them are "
    +"torches.\n");

    add_item(({"torch","torches"}),
    "Inside each one of the sconces along the "
    +"wall is a torch, currently lit.\n");

    add_item(({"portrait","portaits"}),
    "In between each space inside two sconces "
    +"is a thickly framed high portrait. "
    +"A total of two portraits can be seen "
    +"here: one to the left, and another to "
    +"the right.\n");

    add_item(({"floor","carpet", "carpets"}),
    "The floor is covered in soft carpets "
    +"beginning at the base of the stairs, "
    +"muffling the sound of steps and isolating the cold, stone floor.\n");

    add_item(({"stairs","stair","stairway"}),
    "The stairs begin to the south and spiral "
    +"eerily downwards towards the first "
    +"floor, its winding path visible by the "
    +"light emanating from the torches.\n");

    add_item(({"plaque","plaques"}),
    "There are two of them underneath each one "
    +"of the portraits: the one to the left "
    +"is golden while the one to the right is silver.\n");

    add_item(({"left portrait"}),
    "The portrait to the left depicts a long, "
    +"black-haired woman of fine features "
    +"with wide eyes and a calm expression on her face.\n"
    +"Below the portrait is a golden plaque.\n");

    add_item(({"golden plaque"}),
    "The golden plaque reads: Vorcan.");

    add_item(({"right portrait"}),
    "The portrait to the right depicts a bullish, round-faced man of rough "
    +"features and a receding hairline.\n" 
    +"Below the portrait is a silver plaque.\n");

    add_item(({"silver plaque"}),
    "The silver plaque reads: Seba.\n");

    add_exit(FIREKNIVES_ROOMS_DIR + "sr", "west", block_check);
    add_exit(FIREKNIVES_ROOMS_DIR + "o8", "down");
    add_exit(FIREKNIVES_ROOMS_DIR + "h5", "north");
    reset_faerun_room();
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
}
