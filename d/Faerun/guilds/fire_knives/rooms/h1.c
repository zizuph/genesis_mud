/* /d/Faerun/guilds/fire_knives/rooms/h1.c
 *
 * Bottom of stairs 2nd floor,
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
    
    if (present("fireknives_visit_object_conference", this_player()))
    {
       write("The guard dogs raise their heads to look at you "
       +"suspiciously, but they "
       +"let you pass.\n");
        
        tell_room(environment(this_player()), QCTNAME(this_player())
        +" receives a suspicious glance from the guard dogs, but "
        +"is let through.\n", this_player());
            
        return 0;
    }  
    
    if (FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()) ||
        FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()) ||
        FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) ||
		FIREKNIVES_MASTER->is_occ_fireknife(this_player()->query_name()) ||
        this_player()->query_wiz_level())
    {
        write("The guard dogs raise their heads to look at "
        +"you, then look down "
        +"and turn around in a submissive gesture.\n");
        
        tell_room(environment(this_player()), QCTNAME(this_player())
        +" receives a furtive glance from the dogs before they lower "
        +"their head and turn around in a submissive gesture.\n", 
        this_player());
        
        return 0;
    }
 
    write("The guard dogs slowly pace until they stand in front of you "
    +"while growling softly, their eyes focused on yours. You decide "
    +"to reconsider your option and take a few steps backwards.\n");

    tell_room(environment(this_player()), QCTNAME(this_player()) 
    +" steps backwards from the dogs as they move in front of "
    + this_player()->query_possessive()
    +", blocking the way.\n", this_player());

    return 1;
}


/*
 * Function name: create_warlock_room
 * Description  : Constructor, redefine this to configure your room
 */

public void
create_fireknives_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    set_short("At the bottom of the stairs");
    
    set_long("Standing in front of a long winding stairway "
    +"leading upwards into an eerie "
    +"spiral lit by high hanging torches that "
    +"flicker slightly against the vague "
    +"draft coming from upstairs. To the south "
    +"the hallway barely widens in the "
    +"form of a cone that seems to embrace a wide "
    +"marbel column dominating the "
    +"center of the floor. Soft carpets begin at the "
    +"base of the stairs, covering "
    +"the otherwise cold, stone floor. "
    +"A pair of guard dogs is resting here.\n"); 
    
    add_item(({"wall","walls"}),
    "The stone cold walls seem smooth and clean, the "
    +"distances between its parts "
    +"marked only by equidistant sconces in which "
    +"torches are placed. In between "
    +"them is a thickly framed high portrait.\n");
    
    add_item(({"dog", "dogs", "guard dog", "guard dogs", 
    "vicious guard dogs", "vicious dogs"}),
    "These pair of vicious wolf-like grey dogs paces about the "
    +"area, sniffing and carefully watching the movements "
    +"of any nearby creature. They appear to be guarding "
    +"the entrance to the next floor.\n");

    add_item(({"sconces","sconce"}),
    "The sconces are placed at an equal distant to "
    +"each other along the walls that "
    +"extend from the bottom of the stairs southwards. "
    +"Inside each one of them are "
    +"torches.\n");

    add_item(({"torch","torches"}),
    "Inside each one of the sconces along the wall "
    +"is a torch, currently lit.\n");

    add_item(({"portrait","portaits"}),
    "In between each space inside two sconces is a "
    +"thickly framed high portrait. "
    +"A total of two portraits can be seen here: one "
    +"to the left, and another to "
    +"the right.\n");

    add_item(({"left portrait"}),
    "The portrait to the left depicts a white, almost "
    +"pale face, lacking any "
    +"facial hair whatsoever on its smooth frame. Its "
    +"long, raven-black hair "
    +"falls along each side of its shoulders as a "
    +"crown atop its ebon eyes. Its "
    +"tightly shut lips appear thin in an expression of disdain.\n "
    +"Below the portrait is a small golden plaque.\n");

    add_item(({"golden plaque"}),
    "The golden plaque reads: Prince Mekratrig.");

    add_item(({"right portrait"}),
    "The portrait to the right depicts a tanned, "
    +"almost golden face covered in a "
    +"thin layer of reddish hair. Its thick, "
    +"lustruous lips formed in what can only "
    +"be interpreted as a condescending smile. "
    +"Resting just below the loose bangs "
    +"of its fiery mane are two soft eyes that "
    +"seem to look inside your very soul.\n "
    +"Below the portrait is a small silver plaque. \n");

    add_item(({"silver plaque"}),
    "The silver plaque reads: Lord Cromwell.\n");

    add_item(({"hallway","hall","passage","passageway"}),
    "The hallway extends from the bottom of the stairs towards the south, "
    +"widening in the form of a cone upon reaching a thick marble column.\n");

    add_item(({"column","marble column"}),
    "The column isn't quite clearly visible from here in much detail, but "
    +"it is obviously thick and seems to dominate the area, succumbing all "
    +"around it to its frame.\n");

    add_item(({"floor","carpet", "carpets"}),
    "The floor is covered in soft carpets "
    +"beginning at the base of the stairs, "
    +"muffling the sound of steps and isolating the cold, stone floor.\n");

    add_item(({"stairs","stair","stairway"}),
    "The stairs begin to the north and spiral eerily upwards towards a third "
    +"floor, its winding path visible by the "
    +"light emanating from the torches.\n");

    add_item(({"plaque","plaques"}),
    "There are two of them underneath each one "
    +"of the portraits: the one to the left "
    +"is golden while the one to the right is silver.\n");

    add_exit(FIREKNIVES_ROOMS_DIR + "reception.c", "up", block_check);
    add_exit(FIREKNIVES_ROOMS_DIR + "h2.c", "south");

    reset_faerun_room();
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
}
