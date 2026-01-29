/* /d/Faerun/guilds/fire_knives/rooms/o8.c
 *
 * 
 * Fourth and last room en route to the second floor.
 * This one is a guarded exit to use the stairs and travel
 * upwards to the second floor, which is for full members.
 * 
 * Nerull 2019
 *
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "../guild.h";

inherit FIREKNIVES_STD_ROOM;

public int
block_check2()
{
    // Guild has no council, therefore anyone can go upstairs
    if (FIREKNIVES_MASTER->no_boss() == 1 
    && FIREKNIVES_MASTER->no_fist() == 1 
    && FIREKNIVES_MASTER->no_mentor() == 1)
    {
        write("The guard dogs raise their heads to look at you "
        +"suspiciously, but they "
        +"let you pass.\n");
        
        tell_room(environment(this_player()), QCTNAME(this_player())
        +" receives a suspicious glance from the guard dogs, but "
        +"is let through.\n", this_player());
            
        return 0;
    }  
    
    if (FIREKNIVES_MASTER->is_occ_fireknife(this_player()->query_name()) == 0)
    {
        if (!this_player()->query_wiz_level())
        {
            write("The guard dogs slowly pace until they stand "
            +"in front of you "
            +"while growling softly, their eyes focused on yours. You decide "
            +"to reconsider your option and take a few steps backwards.\n");

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


public int
block_check()
{
    if (present("fireknives_visit_object_conference", this_player()))
    {
       write("The guard dogs raise their heads to look "
       +"at you suspiciously, but they "
       +"let you pass.\n");
        
        tell_room(environment(this_player()), QCTNAME(this_player())
        +" receives a suspicious glance from the guard dogs, but "
        +"is let through.\n", this_player());
            
        return 0;
    }  
    
    if (FIREKNIVES_MAPPINGS->query_assassin_rank(this_player()->query_name()) <= MAX_PROSPECT_RANK)
    {
        if (!this_player()->query_wiz_level())
        {
            write("The guard dogs slowly pace until they "
            +"stand in front of you "
            +"while growling softly, their eyes focused on yours. You decide "
            +"to reconsider your option and take a few steps backwards.\n");

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

    set_short("Before a narrow stairway to the north");
    
    set_long("The corridor comes to a halt before an imposing "
    +"yet narrow stairway running upstairs to your north before "
    +"continuing its expansion further westwards. Compared to "
    +"the rest of the structure here, the stairway is clearly "
    +"better maintained and often retouched by caring hands. The railing "
    +"is of a smooth wooden material that seems to shine in "
    +"spite of its darkness, and "
    +"the steps themselves are of an alabaster hue. At its "
    +"top is a square archway "
    +"bearing the clear symbol of a black dagger rising "
    +"from enraged flames. A pair of guard "
    +"dogs patrol the area.\n");

    add_item(({"archway","archways","symbol"}),
    "Unlike the other archways, this one is square "
    +"and well-maintained. At its top is "
    +"the symbol of a black dagger rising from enraged flames.\n");

    add_item(({"stairway","stairs","steps","step"}),
    "The stairway leading upstairs is narrow and "
    +"well-maintained. Its steps are of a "
    +"fine alabaster hue that seems to shine "
    +"against the light of the torches.\n");
    
    add_item(({"dog", "dogs", "guard dog", "guard dogs", 
    "vicious guard dogs", "vicious dogs"}),
    "These pair of vicious wolf-like grey dogs paces about the "
    +"area, sniffing and carefully watching the movements "
    +"of any nearby creature. They appear to be guarding "
    +"the entrance to the west and the stairway.\n");

    add_item(({"railing"}),
    "The stairway's railing is of a smooth wooden "
    +"material that resembles rosewood, "
    +"yet somewhat darker as if holding within it the "
    +"sap of the tree it was made from. "
    +"In spite of its darkness, it seems to shine "
    +"against the light of the torches.\n");

    add_item(({"paste","mortar","dark paste"}),
    "A solidified paste used to bind building blocks "
    +"such as these stones. Due to the "
    +"uneven nature of these random stones used to "
    +"fill decayed parts, their irregular "
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
    +"the air seems to slap the flames gently, and "
    +"they respond in kind licking the soft "
    +"currents as they flow by. \n");
    
    add_item(({"ground","floor"}),
    "The floor appears smooth and well maintained. It "
    +"is made of flattened stone of various "
    +"types as a mosaic of sorts. The change is "
    +"drastic once the stairs are met, the tone "
    +"changing from a stoney mosaic to a shiny alabaster hue.\n");

    add_item(({"wall","walls", "stone","stones"}),
    "The walls are uneven, made of scraggly stone "
    +"worn out by the passage of time and the "
    +"harsh weather. Blackish patches of mold are "
    +"seen in the coldest areas, formed most "
    +"likely by the lack of ventilation. Lines here "
    +"and there have been scrawled on some "
    +"parts, but it's impossible to tell if they "
    +"are human made or simply the result of "
    +"scratches left behind.\n");

    add_item(({"hallway","passage","corridor"}),
    "The hallway extends from here to the southwest "
    +"under uneven archways of heavy stone.\n");

    add_exit(FIREKNIVES_ROOMS_DIR + "h8", "up", block_check);
    add_exit(FIREKNIVES_ROOMS_DIR + "o9", "west", block_check2);
    add_exit(FIREKNIVES_ROOMS_DIR + "o7", "east");
	
	//room_add_object(FIREKNIVES_OBJ_DIR + "magical_trash_can");

    reset_faerun_room();
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
}
